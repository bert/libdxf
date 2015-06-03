/*!
 * \file xrecord.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF xrecord object (\c XRECORD).
 *
 * \version The \c XRECORD object was introduced in DXF R13.
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


#include "xrecord.h"


/*!
 * \brief Allocate memory for a \c DxfXrecord.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfXrecord *
dxf_xrecord_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfXrecord *xrecord = NULL;
        size_t size;

        size = sizeof (DxfXrecord);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((xrecord = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfXrecord struct.\n")),
                  __FUNCTION__);
                xrecord = NULL;
        }
        else
        {
                memset (xrecord, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xrecord);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c XRECORD
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfXrecord *
dxf_xrecord_init
(
        DxfXrecord *xrecord
                /*!< DXF \c XRECORD object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xrecord == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                xrecord = dxf_xrecord_new ();
        }
        if (xrecord == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfXrecord struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xrecord->id_code = 0;
        xrecord->dictionary_owner_soft = strdup ("");
        xrecord->dictionary_owner_hard = strdup ("");
        xrecord->I8 = 0;
        xrecord->I16 = 0;
        xrecord->I32 = 0;
        xrecord->D = 0.0;
        xrecord->F = 0.0;
        xrecord->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xrecord);
}


/*!
 * \brief Read data from a DXF file into a DXF \c XRECORD object.
 *
 * The last line read from file contained the string "XRECORD". \n
 * Now follows some data for the \c XRECORD, to be terminated with a
 * "  0" string announcing the following object, or the end of the
 * \c OBJECTS section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c xrecord. \n
 *
 * \return a pointer to \c xrecord.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfXrecord *
dxf_xrecord_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfXrecord *xrecord
                /*!< DXF \c XRECORD object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

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
        if (xrecord == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                xrecord = dxf_xrecord_new ();
                xrecord = dxf_xrecord_init (xrecord);
        }
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
                        fscanf (fp->fp, "%x\n", &xrecord->id_code);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbXrecord") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", xrecord->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", xrecord->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else if
                  (
                    ((scanf (temp_string, "%d") >= 1) &&  (scanf (temp_string, "%d") <= 9))
                    || (strcmp (temp_string, "102") == 0)
                    || (strcmp (temp_string, "105") == 0)
                    || ((scanf (temp_string, "%d") >= 300) &&  (scanf (temp_string, "%d") <= 369))
                  )
                {
                        xrecord->group_code = scanf (temp_string, "%d");
                        /* Now follows a string value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", xrecord->S);
                }
                else if
                  (
                    ((scanf (temp_string, "%d") >= 10) &&  (scanf (temp_string, "%d") <= 59))
                  )
                {
                        xrecord->group_code = scanf (temp_string, "%d");
                        /* Now follows a double value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xrecord->D);
                }
                else if
                  (
                    ((scanf (temp_string, "%d") >= 60) &&  (scanf (temp_string, "%d") <= 79))
                    || ((scanf (temp_string, "%d") >= 170) &&  (scanf (temp_string, "%d") <= 175))
                  )
                {
                        xrecord->group_code = scanf (temp_string, "%d");
                        /* Now follows a 16-bit integer value.. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi16 "\n", &xrecord->I16);
                }
                else if
                  (
                    ((scanf (temp_string, "%d") >= 90) &&  (scanf (temp_string, "%d") <= 99))
                  )
                {
                        xrecord->group_code = scanf (temp_string, "%d");
                        /* Now follows a 32-bit integer value.. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &xrecord->I32);
                }
                else if
                  (
                    ((scanf (temp_string, "%d") >= 140) &&  (scanf (temp_string, "%d") <= 147))
                  )
                {
                        xrecord->group_code = scanf (temp_string, "%d");
                        /* Now follows a float value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%f\n", &xrecord->F);
                }
                else if
                  (
                    ((scanf (temp_string, "%d") >= 280) &&  (scanf (temp_string, "%d") <= 289))
                  )
                {
                        xrecord->group_code = scanf (temp_string, "%d");
                        /* Now follows a 8-bit integer value.. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi8 "\n", &xrecord->I8);
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
        return (xrecord);
}


/*!
 * \brief Free the allocated memory for a DXF \c XRECORD and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_xrecord_free
(
        DxfXrecord *xrecord
                /*!< Pointer to the memory occupied by the DXF
                 * \c XRECORD object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xrecord->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfXrecord was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (xrecord->dictionary_owner_soft);
        free (xrecord->dictionary_owner_hard);
        free (xrecord);
        xrecord = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
