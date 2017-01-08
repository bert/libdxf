/*!
 * \file imagedef_reactor.c
 *
 * \author Copyright (C) 2015 ... 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF imagedef_reactor object (\c IMAGEDEF_REACTOR).
 *
 * \since The \c IMAGEDEF_REACTOR object was introduced in DXF R14.
 *
 * \warning The \c IMAGEDEF_REACTOR object requires AutoCAD version R14
 * or higher.
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


#include "imagedef_reactor.h"


/*!
 * \brief Allocate memory for a \c DxfImagedefReactor.
 *
 * Fill the memory contents with zeros.
 */
DxfImagedefReactor *
dxf_imagedef_reactor_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfImagedefReactor *imagedef_reactor = NULL;
        size_t size;

        size = sizeof (DxfImagedefReactor);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((imagedef_reactor = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfImagedefReactor struct.\n")),
                  __FUNCTION__);
                imagedef_reactor = NULL;
        }
        else
        {
                memset (imagedef_reactor, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (imagedef_reactor);
}


/*!
 * \brief Allocate memory and initialize data fields in a
 * \c IMAGEDEF_REACTOR object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfImagedefReactor *
dxf_imagedef_reactor_init
(
        DxfImagedefReactor *imagedef_reactor
                /*!< DXF \c IMAGEDEF_REACTOR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (imagedef_reactor == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                imagedef_reactor = dxf_imagedef_reactor_new ();
        }
        if (imagedef_reactor == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfImagedefReactor struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        imagedef_reactor->id_code = 0;
        imagedef_reactor->dictionary_owner_soft = strdup ("");
        imagedef_reactor->dictionary_owner_hard = strdup ("");
        imagedef_reactor->class_version = 0;
        imagedef_reactor->associated_image_object = strdup ("");
        imagedef_reactor->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (imagedef_reactor);
}


/*!
 * \brief Read data from a DXF file into a DXF \c IMAGEDEF_REACTOR
 * object.
 *
 * The last line read from file contained the string "IMAGEDEF_REACTOR". \n
 * Now follows some data for the \c IMAGEDEF_REACTOR, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c imagedef_reactor. \n
 *
 * \return \c a pointer to \c imagedef_reactor.
 */
DxfImagedefReactor *
dxf_imagedef_reactor_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfImagedefReactor *imagedef_reactor
                /*!< DXF \c IMAGEDEF_REACTOR object. */
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
        if (imagedef_reactor == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                imagedef_reactor = dxf_imagedef_reactor_new ();
                imagedef_reactor = dxf_imagedef_reactor_init (imagedef_reactor);
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
                        fscanf (fp->fp, "%x\n", &imagedef_reactor->id_code);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * value of class version. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &imagedef_reactor->class_version);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbRasterImageDef") != 0)
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
                        fscanf (fp->fp, "%s\n", imagedef_reactor->dictionary_owner_soft);
                        i++;
                }
                else if ((strcmp (temp_string, "330") == 0)
                  && (i == 1))
                {
                        /* Now follows a string containing object ID for
                         * associated image object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", imagedef_reactor->associated_image_object);
                        i++;
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", imagedef_reactor->dictionary_owner_hard);
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
        return (imagedef_reactor);
}


/*!
 * \brief Write DXF output to a file for a DXF \c IMAGEDEF_REACTOR
 * object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_imagedef_reactor_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfImagedefReactor *imagedef_reactor
                /*!< DXF \c IMAGEDEF_REACTOR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("IMAGEDEF_REACTOR");

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
        if (imagedef_reactor == NULL)
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
                  __FUNCTION__, dxf_entity_name, imagedef_reactor->id_code);
        }
        if (fp->acad_version_number == AutoCAD_14)
        {
                imagedef_reactor->class_version = 2;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (imagedef_reactor->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", imagedef_reactor->id_code);
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
        if ((strcmp (imagedef_reactor->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", imagedef_reactor->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (imagedef_reactor->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", imagedef_reactor->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbRasterImageDefReactor\n");
        }
        fprintf (fp->fp, " 90\n%d\n", imagedef_reactor->class_version);
        fprintf (fp->fp, "330\n%s\n", imagedef_reactor->associated_image_object);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c IMAGEDEF_REACTOR and
 * all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_imagedef_reactor_free
(
        DxfImagedefReactor *imagedef_reactor
                /*!< Pointer to the memory occupied by the DXF
                 * \c IMAGEDEF_REACTOR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (imagedef_reactor->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfImagedefReactor was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (imagedef_reactor->dictionary_owner_soft);
        free (imagedef_reactor->dictionary_owner_hard);
        free (imagedef_reactor->associated_image_object);
        free (imagedef_reactor);
        imagedef_reactor = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c IMAGEDEF_REACTOR
 * objects and all their data fields.
 */
void
dxf_imagedef_reactor_free_chain
(
        DxfImagedefReactor *imagedef_reactors
                /*!< pointer to the chain of DXF \c IMAGEDEF_REACTOR
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (imagedef_reactors == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (imagedef_reactors != NULL)
        {
                struct DxfImagedefReactor *iter = imagedef_reactors->next;
                dxf_imagedef_reactor_free (imagedef_reactors);
                imagedef_reactors = (DxfImagedefReactor *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c IMAGEDEF_REACTOR object.
 *
 * \return \c id_code when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_imagedef_reactor_get_id_code
(
        DxfImagedefReactor *imagedef_reactor
                /*!< a pointer to a DXF \c IMAGEDEF_REACTOR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (imagedef_reactor == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (imagedef_reactor->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id_code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (imagedef_reactor->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c IMAGEDEF_REACTOR object.
 *
 * \return a pointer to \c imagedef_reactor when successful, or \c NULL when an
 * error occurred.
 */
DxfImagedefReactor *
dxf_imagedef_reactor_set_id_code
(
        DxfImagedefReactor *imagedef_reactor,
                /*!< a pointer to a DXF \c IMAGEDEF_REACTOR object. */
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
        if (imagedef_reactor == NULL)
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
        imagedef_reactor->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (imagedef_reactor);
}


/* EOF*/
