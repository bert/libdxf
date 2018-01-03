/*!
 * \file tolerance.c
 *
 * \author Copyright (C) 2015, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF tolerance entity (\c TOLERANCE).
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


#include "tolerance.h"


/*!
 * \brief Allocate memory for a DXF \c TOLERANCE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfTolerance *
dxf_tolerance_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTolerance *tolerance = NULL;
        size_t size;

        size = sizeof (DxfTolerance);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((tolerance = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTolerance struct.\n")),
                  __FUNCTION__);
                tolerance = NULL;
        }
        else
        {
                memset (tolerance, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c TOLERANCE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfTolerance *
dxf_tolerance_init
(
        DxfTolerance *tolerance
                /*!< a pointer to the DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                tolerance = dxf_tolerance_new ();
        }
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTolerance struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->dimstyle_name = strdup ("");
        tolerance->id_code = 0;
        tolerance->linetype = strdup (DXF_DEFAULT_LINETYPE);
        tolerance->layer = strdup (DXF_DEFAULT_LAYER);
        tolerance->x0 = 0.0;
        tolerance->y0 = 0.0;
        tolerance->z0 = 0.0;
        tolerance->x1 = 0.0;
        tolerance->y1 = 0.0;
        tolerance->z1 = 0.0;
        tolerance->extr_x0 = 0.0;
        tolerance->extr_y0 = 0.0;
        tolerance->extr_z0 = 0.0;
        tolerance->elevation = 0.0;
        tolerance->thickness = 0.0;
        tolerance->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        tolerance->visibility = DXF_DEFAULT_VISIBILITY;
        tolerance->color = DXF_COLOR_BYLAYER;
        tolerance->paperspace = DXF_MODELSPACE;
        tolerance->dictionary_owner_soft = strdup ("");
        tolerance->dictionary_owner_hard = strdup ("");
        tolerance->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Read data from a DXF file into a DXF \c TOLERANCE entity.
 *
 * The last line read from file contained the string "TOLERANCE". \n
 * Now follows some data for the \c TOLERANCE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c tolerance. \n
 *
 * \return a pointer to \c tolerance, \c NULL if an error occurred.
 */
DxfTolerance *
dxf_tolerance_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfTolerance *tolerance
                /*!< a pointer to the DXF \c TOLERANCE entity. */
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
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                tolerance = dxf_tolerance_new ();
                tolerance = dxf_tolerance_init (tolerance);
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
                if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing the dimension
                         * style name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", tolerance->dimstyle_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &tolerance->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", tolerance->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", tolerance->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &tolerance->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &tolerance->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &tolerance->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbFcf") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &tolerance->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", tolerance->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", tolerance->dictionary_owner_hard);
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
        /* Handle omitted members and/or illegal values. */
        if (strcmp (tolerance->dimstyle_name, "") == 0)
        {
                return (NULL);
        }
        if (strcmp (tolerance->linetype, "") == 0)
        {
                tolerance->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (tolerance->layer, "") == 0)
        {
                tolerance->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Write DXF output for a DXF \c TOLERANCE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_tolerance_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfTolerance *tolerance
                /*!< a pointer to the DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("TOLERANCE");

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
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (tolerance->dimstyle_name, "") == 0)
        {
                fprintf (stderr, "Error in dxf_tolerance_write () empty dimstyle name for the %s entity with id-code: %x.\n",
                        dxf_entity_name, tolerance->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (tolerance->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, tolerance->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                tolerance->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (tolerance->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, tolerance->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                tolerance->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (tolerance->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", tolerance->id_code);
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
        if ((strcmp (tolerance->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", tolerance->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (tolerance->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", tolerance->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (tolerance->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", tolerance->layer);
        if (strcmp (tolerance->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", tolerance->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (tolerance->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", tolerance->elevation);
        }
        if (tolerance->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", tolerance->color);
        }
        if (tolerance->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", tolerance->linetype_scale);
        }
        if (tolerance->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", tolerance->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbFcf\n");
        }
        if (tolerance->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", tolerance->thickness);
        }
        fprintf (fp->fp, "  3\n%s\n", tolerance->dimstyle_name);
        fprintf (fp->fp, " 10\n%f\n", tolerance->x0);
        fprintf (fp->fp, " 20\n%f\n", tolerance->y0);
        fprintf (fp->fp, " 30\n%f\n", tolerance->z0);
        if ((fp->acad_version_number >= AutoCAD_12)
                && (tolerance->extr_x0 != 0.0)
                && (tolerance->extr_y0 != 0.0)
                && (tolerance->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", tolerance->extr_x0);
                fprintf (fp->fp, "220\n%f\n", tolerance->extr_y0);
                fprintf (fp->fp, "230\n%f\n", tolerance->extr_z0);
        }
        fprintf (fp->fp, " 11\n%f\n", tolerance->x1);
        fprintf (fp->fp, " 21\n%f\n", tolerance->y1);
        fprintf (fp->fp, " 31\n%f\n", tolerance->z1);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c TOLERANCE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_tolerance_free
(
        DxfTolerance *tolerance
                /*!< a pointer to the memory occupied by the DXF 
                 * \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (tolerance->dimstyle_name);
        free (tolerance->linetype);
        free (tolerance->layer);
        free (tolerance->dictionary_owner_soft);
        free (tolerance->dictionary_owner_hard);
        free (tolerance);
        tolerance = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c TOLERANCE
 * entities and all their data fields.
 */
void
dxf_tolerance_free_chain
(
        DxfTolerance *tolerances
                /*!< a pointer to the chain of DXF \c TOLERANCE
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (tolerances == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (tolerances != NULL)
        {
                struct DxfTolerance *iter = tolerances->next;
                dxf_tolerance_free (tolerances);
                tolerances = (DxfTolerance *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c TOLERANCE entity.
 *
 * \return \c id_code.
 */
int
dxf_tolerance_get_id_code
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_id_code
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        int id_code
                /*!< the \c id_code to be set for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
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
        tolerance->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c linetype from a DXF \c TOLERANCE entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_tolerance_get_linetype
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (tolerance->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_linetype
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c layer from a DXF \c TOLERANCE entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_tolerance_get_layer
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (tolerance->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_layer
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c elevation from a DXF \c TOLERANCE entity.
 *
 * \return \c elevation.
 */
double
dxf_tolerance_get_elevation
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_elevation
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c thickness from a DXF \c TOLERANCE entity.
 *
 * \return \c thickness.
 */
double
dxf_tolerance_get_thickness
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_thickness
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        tolerance->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c TOLERANCE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_tolerance_get_linetype_scale
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_linetype_scale
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        tolerance->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c visibility from a DXF \c TOLERANCE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_tolerance_get_visibility
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (tolerance->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_visibility
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        tolerance->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c color from a DXF \c TOLERANCE entity.
 *
 * \return \c color.
 */
int
dxf_tolerance_get_color
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->color);
}


/*!
 * \brief Set the \c color for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_color
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        tolerance->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c TOLERANCE
 * entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_tolerance_get_paperspace
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (tolerance->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_paperspace
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        tolerance->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c TOLERANCE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_tolerance_get_graphics_data_size
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (tolerance->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c TOLERANCE
 * entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_graphics_data_size
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        tolerance->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c TOLERANCE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_tolerance_get_shadow_mode
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (tolerance->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_shadow_mode
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        tolerance->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c TOLERANCE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_tolerance_get_binary_graphics_data
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) tolerance->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_binary_graphics_data
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c TOLERANCE entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_tolerance_get_dictionary_owner_soft
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (tolerance->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_dictionary_owner_soft
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c TOLERANCE
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_tolerance_get_material
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (tolerance->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c TOLERANCE
 * entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_material
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c TOLERANCE entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_tolerance_get_dictionary_owner_hard
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (tolerance->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_dictionary_owner_hard
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c lineweight from a DXF \c TOLERANCE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_tolerance_get_lineweight
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_lineweight
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c TOLERANCE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_tolerance_get_plot_style_name
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (tolerance->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_plot_style_name
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c color_value from a DXF \c TOLERANCE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_tolerance_get_color_value
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_color_value
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c color_name from a DXF \c TOLERANCE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_tolerance_get_color_name
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (tolerance->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_color_name
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c transparency from a DXF \c TOLERANCE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_tolerance_get_transparency
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_transparency
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the \c dimstyle_name from a DXF \c TOLERANCE entity.
 *
 * \return \c dimstyle_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_tolerance_get_dimstyle_name
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->dimstyle_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (tolerance->dimstyle_name));
}


/*!
 * \brief Set the \c dimstyle_name for a DXF \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_dimstyle_name
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        char *dimstyle_name
                /*!< a string containing the \c dimstyle_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->dimstyle_name = strdup (dimstyle_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the insertion point \c p0 of a DXF \c TOLERANCE entity.
 *
 * \return the center point \c p0.
 */
DxfPoint *
dxf_tolerance_get_p0
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a DXF \c TOLERANCE entity.
 *
 * \return a pointer to a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_p0
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a DXF
 * \c TOLERANCE entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_tolerance_get_x0
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a DXF
 * \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_x0
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        double x0
                /*!< the X-value of the insertion point \c x0 of a DXF
                 * \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a DXF
 * \c TOLERANCE entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_tolerance_get_y0
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a DXF
 * \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_y0
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a DXF
                 * \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a DXF
 * \c TOLERANCE entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_tolerance_get_z0
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a DXF
 * \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_z0
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        double z0
                /*!< the Z-value of the insertion point \c z0 of a DXF
                 * \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the direction vector \c p1 of a DXF \c TOLERANCE entity.
 *
 * \return the direction vector \c p1.
 */
DxfPoint *
dxf_tolerance_get_p1
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->p1);
}


/*!
 * \brief Set the direction vector \c p1 of a DXF \c TOLERANCE entity.
 *
 * \return a pointer to a DXF \c TOLERANCE entity.
 */
DxfTolerance *
dxf_tolerance_set_p1
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the X-value of the direction vector \c x1 of a DXF
 * \c TOLERANCE entity.
 *
 * \return the X-value of the direction vector \c x1.
 */
double
dxf_tolerance_get_x1
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->p1->x0);
}


/*!
 * \brief Set the X-value of the direction vector \c x1 of a DXF
 * \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_x1
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        double x1
                /*!< the X-value of the direction vector \c x1 of a DXF
                 * \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Get the Y-value of the direction vector \c y1 of a DXF
 * \c TOLERANCE entity.
 *
 * \return the Y-value of the direction vector \c y1.
 */
double
dxf_tolerance_get_y1
(
        DxfTolerance *tolerance
                /*!< a pointer to a DXF \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tolerance->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance->p1->y0);
}


/*!
 * \brief Set the Y-value of the direction vector \c y1 of a DXF
 * \c TOLERANCE entity.
 *
 * \return a pointer to \c tolerance when successful, or \c NULL when an
 * error occurred.
 */
DxfTolerance *
dxf_tolerance_set_y1
(
        DxfTolerance *tolerance,
                /*!< a pointer to a DXF \c TOLERANCE entity. */
        double y1
                /*!< the Y-value of the direction vector \c y1 of a DXF
                 * \c TOLERANCE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tolerance->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/* EOF*/
