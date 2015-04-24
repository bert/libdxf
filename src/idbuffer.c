/*!
 * \file idbuffer.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF idbuffer object (\c IDBUFFER).
 *
 * \version The \c IDBUFFER object was introduced in DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c idbuffer. \n
 *
 * \return \c a pointer to \c idbuffer.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
 * \brief Free the allocated memory for a DXF \c IDBUFFER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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


/* EOF*/
