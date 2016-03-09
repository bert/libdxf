/*!
 * \file idbuffer.c
 *
 * \author Copyright (C) 2015 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF idbuffer object (\c IDBUFFER).
 *
 * \version The \c IDBUFFER object was introduced in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.\n\n
 * This program is distributed in the hope that it will be useful, but
 * <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
 * <b>MERCHANTABILITY</b> or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.\n
 * See the GNU General Public License for more details.\n\n
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to:\n
 * Free Software Foundation, Inc.,\n
 * 59 Temple Place,\n
 * Suite 330,\n
 * Boston,\n
 * MA 02111 USA.\n
 * \n
 * Drawing eXchange Format (DXF) is a defacto industry standard for the
 * exchange of drawing files between various Computer Aided Drafting
 * programs.\n
 * DXF is an industry standard designed by Autodesk(TM).\n
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#include "idbuffer.h"


/*!
 * \brief Allocate memory for a \c DxfIdbuffer.
 *
 * Fill the memory contents with zeros.
 */
DxfIdbuffer *
dxf_idbuffer_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfIdbuffer *idbuffer = NULL;
        size_t size;

        size = sizeof (DxfIdbuffer);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((idbuffer = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfIdbuffer struct.\n")),
                  __FUNCTION__);
                idbuffer = NULL;
        }
        else
        {
                memset (idbuffer, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c IDBUFFER
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfIdbuffer *
dxf_idbuffer_init
(
        DxfIdbuffer *idbuffer
                /*!< DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                idbuffer = dxf_idbuffer_new ();
        }
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfIdbuffer struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        idbuffer->id_code = 0;
        idbuffer->dictionary_owner_soft = strdup ("");
        idbuffer->dictionary_owner_hard = strdup ("");
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                idbuffer->entity_pointer[i] = strdup ("");
        }
        idbuffer->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Read data from a DXF file into a DXF \c IDBUFFER object.
 *
 * The last line read from file contained the string "IDBUFFER". \n
 * Now follows some data for the \c IDBUFFER, to be terminated with a
 * "  0" string announcing the following object, or the end of the
 * \c OBJECTS section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c idbuffer. \n
 *
 * \return a pointer to \c idbuffer.
 */
DxfIdbuffer *
dxf_idbuffer_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfIdbuffer *idbuffer
                /*!< DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                idbuffer = dxf_idbuffer_new ();
                idbuffer = dxf_idbuffer_init (idbuffer);
        }
        i = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &idbuffer->id_code);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbIdBuffer") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if ((strcmp (temp_string, "330") == 0)
                  && (i == 0))
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", idbuffer->dictionary_owner_soft);
                        i++;
                }
                else if ((strcmp (temp_string, "330") == 0)
                  && (i > 0))
                {
                        /* Now follows a string containing a Soft
                         * pointer reference to entity. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", idbuffer->entity_pointer[i]);
                        i++;
                        /*! \todo Check for overrun of array index. */
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", idbuffer->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Write DXF output to a file for a DXF \c IDBUFFER object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_idbuffer_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfIdbuffer *idbuffer
                /*!< DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("IDBUFFER");
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, idbuffer->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (idbuffer->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", idbuffer->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (idbuffer->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", idbuffer->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (idbuffer->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", idbuffer->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbIdBuffer\n");
        }
        i = 0;
        while (strlen (idbuffer->entity_pointer[i]) > 0)
        {
                fprintf (fp->fp, "330\n%s\n", idbuffer->entity_pointer[i]);
                i++;
                /*! \todo Check for overrun of array index. */
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c IDBUFFER object and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_idbuffer_free
(
        DxfIdbuffer *idbuffer
                /*!< Pointer to the memory occupied by the DXF
                 * \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (idbuffer->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfIdbuffer was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (idbuffer->dictionary_owner_soft);
        free (idbuffer->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (idbuffer->entity_pointer[i]);
        }
        free (idbuffer);
        idbuffer = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c IDBUFFER
 * objects and all their data fields.
 */
void
dxf_idbuffer_free_chain
(
        DxfIdbuffer *id_buffers
                /*!< pointer to the chain of DXF \c IDBUFFER objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (id_buffers == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (id_buffers != NULL)
        {
                struct DxfIdbuffer *iter = id_buffers->next;
                dxf_idbuffer_free (id_buffers);
                id_buffers = (DxfIdbuffer *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c IDBUFFER object.
 *
 * \return \c id_code when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_idbuffer_get_id_code
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (idbuffer->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id_code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = idbuffer->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c id_code for a DXF \c IDBUFFER object.
 *
 * \return a pointer to \c idbuffer when successful, or \c NULL when an
 * error occurred.
 */
DxfIdbuffer *
dxf_idbuffer_set_id_code
(
        DxfIdbuffer *idbuffer,
                /*!< a pointer to a DXF \c IDBUFFER. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        idbuffer->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF
 * \c IDBUFFER object.
 *
 * \return a pointer to \c dictionary_owner_soft when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_idbuffer_get_dictionary_owner_soft
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (idbuffer->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (idbuffer->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF*/
