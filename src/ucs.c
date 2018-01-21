/*!
 * \file ucs.c
 *
 * \author Copyright (C) 2014, 2015, 2017, 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF User Coordinate System entity (\c UCS).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
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


#include "ucs.h"


/*!
 * \brief Allocate memory for a DXF \c UCS.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfUcs *
dxf_ucs_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfUcs *ucs = NULL;
        size_t size;

        size = sizeof (DxfUcs);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ucs = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfUcs struct.\n")),
                  __FUNCTION__);
                ucs = NULL;
        }
        else
        {
                memset (ucs, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c UCS
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfUcs *
dxf_ucs_init
(
        DxfUcs *ucs
                /*!< a pointer to the DXF \c UCS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ucs = dxf_ucs_new ();
        }
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfUcs struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ucs->id_code = 0;
        ucs->UCS_name = strdup ("");
        ucs->x_origin = 0.0;
        ucs->y_origin = 0.0;
        ucs->z_origin = 0.0;
        ucs->x_X_dir = 0.0;
        ucs->y_X_dir = 0.0;
        ucs->z_X_dir = 0.0;
        ucs->x_Y_dir = 0.0;
        ucs->y_Y_dir = 0.0;
        ucs->z_Y_dir = 0.0;
        ucs->flag = 0;
        ucs->dictionary_owner_soft = strdup ("");
        ucs->dictionary_owner_hard = strdup ("");
        ucs->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs);
}


/*!
 * \brief Read data from a DXF file into a DXF \c UCS entity.
 *
 * The last line read from file contained the string "UCS". \n
 * Now follows some data for the \c UCS, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c ucs. \n
 *
 * \return a pointer to \c ucs.
 */
DxfUcs *
dxf_ucs_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfUcs *ucs
                /*!< a pointer to the DXF \c UCS symbol table entry. */
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
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ucs = dxf_ucs_new ();
                ucs = dxf_ucs_init (ucs);
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
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &ucs->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing an UCS
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ucs->UCS_name);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->x_origin);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->y_origin);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->z_origin);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the reference point for the
                         * X-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->x_X_dir);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the reference point for the
                         * X-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->y_X_dir);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the reference point for the
                         * X-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->z_X_dir);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the reference point for the
                         * Y-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->x_Y_dir);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the reference point for the
                         * Y-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->y_Y_dir);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the reference point for the
                         * Y-axis direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ucs->z_Y_dir);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ucs->flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTableRecord") != 0)
                        && ((strcmp (temp_string, "AcDbUCSTableRecord") != 0)))
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
                        fscanf (fp->fp, "%s\n", ucs->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ucs->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
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
        return (ucs);
}


/*!
 * \brief Write DXF output to a file for a DXF \c UCS entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ucs_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfUcs *ucs
                /*!< a pointer to the DXF \c UCS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("UCS");

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
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((ucs->UCS_name == NULL)
          || (strcmp (ucs->UCS_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty UCS name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ucs->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (ucs->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", ucs->id_code);
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
        if ((strcmp (ucs->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", ucs->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (ucs->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", ucs->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbUCSTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", ucs->UCS_name);
        fprintf (fp->fp, " 70\n%d\n", ucs->flag);
        fprintf (fp->fp, " 10\n%f\n", ucs->x_origin);
        fprintf (fp->fp, " 20\n%f\n", ucs->y_origin);
        fprintf (fp->fp, " 30\n%f\n", ucs->z_origin);
        fprintf (fp->fp, " 11\n%f\n", ucs->x_X_dir);
        fprintf (fp->fp, " 21\n%f\n", ucs->y_X_dir);
        fprintf (fp->fp, " 31\n%f\n", ucs->z_X_dir);
        fprintf (fp->fp, " 12\n%f\n", ucs->x_Y_dir);
        fprintf (fp->fp, " 22\n%f\n", ucs->y_Y_dir);
        fprintf (fp->fp, " 32\n%f\n", ucs->z_Y_dir);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c UCS and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ucs_free
(
        DxfUcs *ucs
                /*!< a pointer to the memory occupied by the DXF \c UCS
                 * symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ucs->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (ucs->UCS_name);
        free (ucs->dictionary_owner_soft);
        free (ucs->dictionary_owner_hard);
        free (ucs);
        ucs = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c UCS
 * symbol table and all their data fields.
 */
void
dxf_ucs_free_chain
(
        DxfUcs *ucss
                /*!< a pointer to the chain of DXF \c UCS symbol table
                 * entries. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ucss == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (ucss != NULL)
        {
                struct DxfUcs *iter = ucss->next;
                dxf_ucs_free (ucss);
                ucss = (DxfUcs *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c UCS symbol table entry.
 *
 * \return \c id_code.
 */
int
dxf_ucs_get_id_code
(
        DxfUcs *ucs
                /*!< a pointer to a DXF \c UCS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ucs->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c UCS symbol table entry.
 */
DxfUcs *
dxf_ucs_set_id_code
(
        DxfUcs *ucs,
                /*!< a pointer to a DXF \c UCS symbol table entry. */
        int id_code
                /*!< the \c id_code to be set for the entry.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        ucs->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs);
}


/*!
 * \brief Get the \c UCS_name from a DXF \c UCS symbol table entry.
 *
 * \return \c UCS_name when sucessful, \c NULL when an error occurred.
 */
char *
dxf_ucs_get_UCS_name
(
        DxfUcs *ucs
                /*!< a pointer to a DXF \c UCS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ucs->UCS_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ucs->UCS_name));
}


/*!
 * \brief Set the \c UCS_name for a DXF \c UCS symbol table entry.
 */
DxfUcs *
dxf_ucs_set_UCS_name
(
        DxfUcs *ucs,
                /*!< a pointer to a DXF \c UCS symbol table entry. */
        char *UCS_name
                /*!< a pointer to a string containing the \c UCS_name
                 * to be set for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (UCS_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ucs->UCS_name = strdup (UCS_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs);
}


/*!
 * \brief Get the base point \c origin of a DXF \c UCS symbol table
 * entry.
 *
 * \return the base point \c origin.
 */
DxfPoint *
dxf_ucs_get_origin
(
        DxfUcs *ucs
                /*!< a pointer to a DXF \c UCS symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ucs->origin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs->origin);
}


/*!
 * \brief Set the base point \c origin of a DXF \c UCS symbol table
 * entry.
 *
 * \return a pointer to a DXF \c UCS symbol table entry.
 */
DxfUcs *
dxf_ucs_set_origin
(
        DxfUcs *ucs,
                /*!< a pointer to a DXF \c UCS symbol table entry. */
        DxfPoint *origin
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (origin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ucs->origin = origin;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs);
}


/*!
 * \brief Get the X-value of the base point \c origin of a DXF \c UCS
 * symbol table entry.
 *
 * \return the X-value of the base point \c origin.
 */
double
dxf_ucs_get_origin_x
(
        DxfUcs *ucs
                /*!< a pointer to a DXF \c UCS symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ucs->origin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs->origin->x0);
}


/*!
 * \brief Set the X-value of the base point \c origin of a DXF \c UCS
 * symbol table entry.
 *
 * \return a pointer to \c ucs when successful, or \c NULL when an
 * error occurred.
 */
DxfUcs *
dxf_ucs_set_origin_x
(
        DxfUcs *ucs,
                /*!< a pointer to a DXF \c UCS symbol table entry. */
        double x
                /*!< the X-value of the base point \c origin of a DXF
                 * \c UCS symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ucs->origin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ucs->origin->x0 = x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs);
}


/*!
 * \brief Get the Y-value of the base point \c origin of a DXF \c UCS
 * symbol table entry.
 *
 * \return the Y-value of the base point \c origin.
 */
double
dxf_ucs_get_origin_y
(
        DxfUcs *ucs
                /*!< a pointer to a DXF \c UCS symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ucs->origin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs->origin->y0);
}


/*!
 * \brief Set the Y-value of the base point \c origin of a DXF \c UCS
 * symbol table entry.
 *
 * \return a pointer to \c ucs when successful, or \c NULL when an
 * error occurred.
 */
DxfUcs *
dxf_ucs_set_origin_y
(
        DxfUcs *ucs,
                /*!< a pointer to a DXF \c UCS symbol table entry. */
        double y
                /*!< the Y-value of the base point \c origin of a DXF
                 * \c UCS symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ucs->origin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ucs->origin->y0 = y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs);
}


/*!
 * \brief Get the Z-value of the base point \c origin of a DXF \c UCS
 * symbol table entry.
 *
 * \return the Z-value of the base point \c origin.
 */
double
dxf_ucs_get_origin_z
(
        DxfUcs *ucs
                /*!< a pointer to a DXF \c UCS symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ucs->origin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ucs->origin->z0);
}


/* EOF */
