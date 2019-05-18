/*!
 * \file point.c
 *
 * \author Copyright (C) 2008, 2009, 2010, 2012, 2014, 2015, 2016, 2017,
 * 2018, 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF point entity (\c POINT).
 *
 * Point entities have an optional 50 group that determines the
 * orientation of \c PDMODE images.\n
 * The group value is the negative of the Entity Coordinate Systems
 * (ECS) angle of the UCS X axis in effect when the point was drawn.\n
 * The X-axis of the UCS in effect when the point was drawn is always
 * parallel to the XY plane for the point's ECS, and the angle between
 * the UCS X axis and the ECS X axis is a single 2D angle.\n
 * The value in group 50 is the angle from horizontal (the effective
 * X-axis) to the ECS X axis.\n
 *
 * Entity Coordinate Systems (ECS) are described ... somewhere else.
 *
 * \todo Add a link to somewhere else.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2014.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#include "point.h"


/*!
 * \brief Allocate memory for a \c DxfPoint.
 *
 * Fill the memory contents with zeros.
 */
DxfPoint *
dxf_point_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;
        size_t size;

        size = sizeof (DxfPoint);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((point = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                  __FUNCTION__);
                point = NULL;
        }
        else
        {
                memset (point, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c POINT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfPoint *
dxf_point_init
(
        DxfPoint *point
                /*!< a pointer to the DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                point = dxf_point_new ();
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->id_code = 0;
        point->linetype = strdup (DXF_DEFAULT_LINETYPE);
        point->layer = strdup (DXF_DEFAULT_LAYER);
        point->x0 = 0.0;
        point->y0 = 0.0;
        point->z0 = 0.0;
        point->elevation = 0.0;
        point->thickness = 0.0;
        point->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        point->angle_to_X = 0.0;
        point->visibility = DXF_DEFAULT_VISIBILITY;
        point->color = DXF_COLOR_BYLAYER;
        point->paperspace = DXF_MODELSPACE;
        point->extr_x0 = 0.0;
        point->extr_y0 = 0.0;
        point->extr_z0 = 0.0;
        point->dictionary_owner_soft = strdup ("");
        point->dictionary_owner_hard = strdup ("");
        point->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Read data from a DXF file into a \c POINT entity.
 *
 * The last line read from file contained the string "POINT". \n
 * Now follows some data for the \c POINT, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c point. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfPoint *
dxf_point_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfPoint *point
                /*!< a pointer to the DXF \c POINT entity. */
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
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                point = dxf_point_init (point);
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
                        fscanf (fp->fp, "%x\n", &point->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, point->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, point->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (point->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * start angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->angle_to_X);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &point->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &point->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &point->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbPoint") != 0)))
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
                        fscanf (fp->fp, "%lf\n", &point->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &point->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, point->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, point->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning: in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (point->linetype, "") == 0)
        {
                point->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (point->layer, "") == 0)
        {
                point->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Write DXF output to fp for a point entity.
 * 
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_point_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfPoint *point
                /*!< a pointer to the DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("POINT");

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
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (point->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, point->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                point->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (point->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name,
                        point->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                point->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (point->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", point->id_code);
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
        if ((strcmp (point->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", point->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (point->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", point->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (point->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", point->layer);
        if (strcmp (point->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", point->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (point->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", point->elevation);
        }
        if (point->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", point->color);
        }
        if (point->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", point->linetype_scale);
        }
        if (point->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", point->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbPoint\n");
        }
        fprintf (fp->fp, " 10\n%f\n", point->x0);
        fprintf (fp->fp, " 20\n%f\n", point->y0);
        fprintf (fp->fp, " 30\n%f\n", point->z0);
        if (point->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", point->thickness);
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (point->extr_x0 != 0.0)
                && (point->extr_y0 != 0.0)
                && (point->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", point->extr_x0);
                fprintf (fp->fp, "220\n%f\n", point->extr_y0);
                fprintf (fp->fp, "230\n%f\n", point->extr_z0);
        }
        fprintf (fp->fp, " 50\n%f\n", point->angle_to_X);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c POINT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_point_free
(
        DxfPoint *point
                /*!< a pointer to the memory occupied by the DXF \c POINT
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (point->linetype);
        free (point->layer);
        free (point->dictionary_owner_soft);
        free (point->dictionary_owner_hard);
        free (point);
        point = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c POINT entities and all their data fields.
 */
void
dxf_point_free_list
(
        DxfPoint *points
                /*!< a pointer to the single linked list of DXF
                 * \c POINT entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (points == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (points != NULL)
        {
                DxfPoint *iter = (DxfPoint *) points->next;
                dxf_point_free (points);
                points = (DxfPoint *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from this DXF \c POINT entity.
 *
 * \return \c id_code.
 */
int
dxf_point_get_id_code
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c id_code for this DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_id_code
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
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
        if (point == NULL)
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
        point->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c linetype from this DXF \c POINT entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_point_get_linetype
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (point->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c linetype for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_linetype
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c layer from this DXF \c POINT entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_point_get_layer
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (point->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c layer for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_layer
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c elevation from a DXF \c POINT entity.
 *
 * \return \c elevation.
 */
double
dxf_point_get_elevation
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c elevation for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_elevation
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c thickness from a DXF \c POINT entity.
 *
 * \return \c thickness.
 */
double
dxf_point_get_thickness
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c thickness for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_thickness
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c linetype_scale from this DXF \c POINT entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_point_get_linetype_scale
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_linetype_scale
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c visibility from a DXF \c POINT entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_point_get_visibility
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c visibility for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_visibility
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c color from a DXF \c POINT entity.
 *
 * \return \c color.
 */
int
dxf_point_get_color
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = point->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c color for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_color
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        point->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c POINT entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_point_get_paperspace
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (point->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = point->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c paperspace flag for this DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_paperspace
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c POINT entity.
 *
 * \return \c graphics_data_size flag value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_point_get_graphics_data_size
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        if (point->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        result = point->graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_graphics_data_size
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a zero graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c POINT entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_point_get_shadow_mode
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_shadow_mode
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        int16_t shadow_mode
                /*!< the \c shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF 
 * \c POINT entity.
 *
 * \return a pointer to the \c binary_graphics_data when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_point_get_binary_graphics_data
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfBinaryGraphicsData *result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the binary_graphics_data member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfBinaryGraphicsData *) point->binary_graphics_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_binary_graphics_data
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c POINT entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_point_get_dictionary_owner_soft
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (point->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_dictionary_owner_soft
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c POINT entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_point_get_material
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the material member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (point->material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_material
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c POINT entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_point_get_dictionary_owner_hard
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (point->dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_dictionary_owner_hard
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c lineweight from a DXF \c POINT entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_point_get_lineweight
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c lineweight for a DXF \c POINT entity.
 *
 * \return a pointer to \c point successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_lineweight
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c POINT entity.
 *
 * \return \c plot_style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_point_get_plot_style_name
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the plot_style_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (point->plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_plot_style_name
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c color_value from a DXF \c POINT entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_point_get_color_value
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        long result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c color_value for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_color_value
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c color_name from a DXF \c POINT entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_point_get_color_name
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the color_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (point->color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c color_name for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_color_name
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c transparency from a DXF \c POINT entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_point_get_transparency
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        long result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c transparency for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_transparency
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the X coordinate value \c x0 from a DXF \c POINT entity.
 *
 * \return \c x0.
 */
double
dxf_point_get_x0
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the X coordinate value \c x0 for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_x0
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        double x0
                /*!< the X coordinate value \c x0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the Y coordinate value \c y0 from a DXF \c POINT entity.
 *
 * \return \c y0.
 */
double
dxf_point_get_y0
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the Y coordinate value \c y0 for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_y0
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        double y0
                /*!< the Y coordinate value \c y0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the Z coordinate value \c z0 from a DXF \c POINT entity.
 *
 * \return \c z0.
 */
double
dxf_point_get_z0
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the Z coordinate value \c z0 for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_z0
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        double z0
                /*!< the Z coordinate value \c z0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the \c angle_to_X from a DXF \c POINT entity.
 *
 * \return \c angle_to_X.
 */
double
dxf_point_get_angle_to_X
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = point->angle_to_X;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c angle_to_X for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_angle_to_X
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        double angle_to_X
                /*!< the \c angle_to_X to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->angle_to_X = angle_to_X;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c POINT entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_point_get_extrusion_vector_as_point
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *result = NULL;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = dxf_point_init (result);
        if (result == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        result->x0 = point->extr_x0;
        result->y0 = point->extr_y0;
        result->z0 = point->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the extrusion vector for a DXF \c POINT entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_extrusion_vector
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        double extr_x0,
                /*!<  X-value of the extrusion direction. */
        double extr_y0,
                /*!<  Y-value of the extrusion direction. */
        double extr_z0
                /*!<  Z-value of the extrusion direction. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->extr_x0 = extr_x0;
        point->extr_y0 = extr_y0;
        point->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the pointer to the next \c POINT entity from a DXF 
 * \c POINT entity.
 *
 * \return pointer to the next \c POINT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfPoint *
dxf_point_get_next
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *result;

        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfPoint *) point->next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the next \c POINT for a DXF \c POINT
 * entity.
 *
 * \return a pointer to \c point when successful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_point_set_next
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfPoint *next
                /*!< a pointer to the next \c POINT for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->next = (struct DxfPoint *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the pointer to the last \c POINT entity from a linked list
 * of DXF \c POINT entities.
 *
 * \return pointer to the last \c POINT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfPoint *
dxf_point_get_last
(
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfPoint *) point);
        }
        DxfPoint *iter = (DxfPoint *) point->next;
        while (iter->next != NULL)
        {
                iter = (DxfPoint *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) iter);
}


/* EOF */
