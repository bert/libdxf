/*!
 * \file xrecord.c
 *
 * \author Copyright (C) 2015, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF xrecord object (\c XRECORD).
 *
 * \since The \c XRECORD object was introduced in DXF R13.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
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


#include "xrecord.h"


/*!
 * \brief Allocate memory for a \c DxfXrecord.
 *
 * Fill the memory contents with zeros.
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
 */
DxfXrecord *
dxf_xrecord_init
(
        DxfXrecord *xrecord
                /*!< a pointer to the DXF \c XRECORD object. */
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
 */
DxfXrecord *
dxf_xrecord_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfXrecord *xrecord
                /*!< a pointer to the DXF \c XRECORD object. */
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
                        fscanf (fp->fp, "%hi\n", &xrecord->I16);
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
                        fscanf (fp->fp, "%hhi\n", &xrecord->I8);
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
 * \brief Write DXF output to a file for a DXF \c XRECORD object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_xrecord_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfXrecord *xrecord
                /*!< a pointer to the DXF \c XRECORD object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("XRECORD");

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
        if (xrecord == NULL)
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
                  __FUNCTION__, dxf_entity_name, xrecord->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (xrecord->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", xrecord->id_code);
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
        if ((strcmp (xrecord->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", xrecord->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (xrecord->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", xrecord->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbXrecord\n");
        }
        fprintf (fp->fp, "%d\n", xrecord->group_code);
        if
        (
          ((xrecord->group_code >= 1) && (xrecord->group_code <= 9))
          || (xrecord->group_code == 102)
          || (xrecord->group_code == 105)
          || ((xrecord->group_code >= 300) &&  (xrecord->group_code <= 369))
        )
        {
                fprintf (fp->fp, "%s\n", xrecord->S);
        }
        else if
        (
          ((xrecord->group_code >= 10) && (xrecord->group_code <= 59))
        )
        {
                fprintf (fp->fp, "%lf\n", xrecord->D);
        }
        else if
        (
          ((xrecord->group_code >= 60) && (xrecord->group_code <= 79))
          || ((xrecord->group_code >= 170) && (xrecord->group_code <= 175))
        )
        {
                fprintf (fp->fp, "%" PRIi16 "\n", xrecord->I16);
        }
        else if
        (
          ((xrecord->group_code >= 90) && (xrecord->group_code <= 99))
        )
        {
                fprintf (fp->fp, "%" PRIi32 "\n", xrecord->I32);
        }
        else if
        (
          ((xrecord->group_code >= 140) && (xrecord->group_code <= 147))
        )
        {
                fprintf (fp->fp, "%f\n", xrecord->F);
        }
        else if
        (
          ((xrecord->group_code >= 280) && (xrecord->group_code <= 289))
        )
        {
                fprintf (fp->fp, "%" PRIi8 "\n", xrecord->I8);
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () unknown group code %d found in DxfXrecord struct with id-code: %x.\n")),
                  __FUNCTION__, xrecord->group_code, xrecord->id_code);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c XRECORD and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_xrecord_free
(
        DxfXrecord *xrecord
                /*!< a pointer to the memory occupied by the DXF
                 * \c XRECORD object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xrecord == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xrecord->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
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


/*!
 * \brief Free the allocated memory for a chain of DXF \c XRECORD
 * objects and all their data fields.
 */
void
dxf_xrecord_free_chain
(
        DxfXrecord *xrecords
                /*!< a pointer to the chain of DXF \c XRECORD objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (xrecords == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (xrecords != NULL)
        {
                struct DxfXrecord *iter = xrecords->next;
                dxf_xrecord_free (xrecords);
                xrecords = (DxfXrecord *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/* EOF*/
