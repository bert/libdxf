/*!
 * \file polyline.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015 2016, 2017, 2018,
 * 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF polyline entity (\c POLYLINE).
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#include "polyline.h"


/*!
 * \brief Allocate memory for a \c DxfPolyline.
 *
 * Fill the memory contents with zeros.
 */
DxfPolyline *
dxf_polyline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPolyline *polyline = NULL;
        size_t size;

        size = sizeof (DxfPolyline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((polyline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfArc struct.\n")),
                  __FUNCTION__);
                polyline = NULL;
        }
        else
        {
                memset (polyline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c POLYLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfPolyline *
dxf_polyline_init
(
        DxfPolyline *polyline
                /*!< a pointer to the DXF polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                polyline = dxf_polyline_new ();
        }
        if (polyline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfPolyline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_polyline_set_id_code (polyline, 0);
        dxf_polyline_set_linetype (polyline, strdup (DXF_DEFAULT_LINETYPE));
        dxf_polyline_set_layer (polyline, strdup (DXF_DEFAULT_LAYER));
        dxf_polyline_set_elevation (polyline, 0.0);
        dxf_polyline_set_thickness (polyline, 0.0);
        dxf_polyline_set_linetype_scale (polyline, DXF_DEFAULT_LINETYPE_SCALE);
        dxf_polyline_set_visibility (polyline, DXF_DEFAULT_VISIBILITY);
        dxf_polyline_set_color (polyline, DXF_COLOR_BYLAYER);
        dxf_polyline_set_paperspace (polyline, DXF_MODELSPACE);
        dxf_polyline_set_graphics_data_size (polyline, 0);
        dxf_polyline_set_shadow_mode (polyline, 0);
        dxf_polyline_set_binary_graphics_data (polyline, (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ());
        dxf_polyline_set_dictionary_owner_soft (polyline, strdup (""));
        dxf_polyline_set_material (polyline, strdup (""));
        dxf_polyline_set_dictionary_owner_hard (polyline, strdup (""));
        dxf_polyline_set_lineweight (polyline, 0);
        dxf_polyline_set_plot_style_name (polyline, strdup (""));
        dxf_polyline_set_color_value (polyline, 0);
        dxf_polyline_set_color_name (polyline, strdup (""));
        dxf_polyline_set_transparency (polyline, 0);
        dxf_polyline_set_p0 (polyline, (DxfPoint *) dxf_point_new ());
        dxf_point_init ((DxfPoint *) dxf_polyline_get_p0 (polyline));
        dxf_polyline_set_x0 (polyline, 0.0);
        dxf_polyline_set_y0 (polyline, 0.0);
        dxf_polyline_set_z0 (polyline, 0.0);
        dxf_polyline_set_start_width (polyline, 0.0);
        dxf_polyline_set_end_width (polyline, 0.0);
        dxf_polyline_set_vertices_follow (polyline, 1);
        dxf_polyline_set_flag (polyline, 0);
        dxf_polyline_set_polygon_mesh_M_vertex_count (polyline, 0);
        dxf_polyline_set_polygon_mesh_N_vertex_count (polyline, 0);
        dxf_polyline_set_smooth_M_surface_density (polyline, 0);
        dxf_polyline_set_smooth_N_surface_density (polyline, 0);
        dxf_polyline_set_surface_type (polyline, 0);
        dxf_polyline_set_extr_x0 (polyline, 0.0);
        dxf_polyline_set_extr_y0 (polyline, 0.0);
        dxf_polyline_set_extr_z0 (polyline, 0.0);
        dxf_polyline_set_vertices (polyline, (DxfVertex *) dxf_vertex_new ());
        dxf_vertex_init ((DxfVertex *) dxf_polyline_get_vertices (polyline));
        dxf_polyline_set_next (polyline, NULL);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}



/*!
 * \brief Read data from a DXF file into an \c POLYLINE entity.
 *
 * The last line read from file contained the string "POLYLINE". \n
 * Now follows some data for the \c POLYLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c polyline. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfPolyline *polyline
                /*!< a pointer to the DXF polyline entity. */
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
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                polyline = dxf_polyline_init (polyline);
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
                        fscanf (fp->fp, "%x\n", (uint *) &polyline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, polyline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, polyline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the primary point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the primary point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the primary point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->p0->z0);
                }
                else if (strcmp (temp_string, "38") == 0)
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * starting width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->start_width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * end width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->end_width);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &polyline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->color);
                }
                else if (strcmp (temp_string, "66") == 0)
                {
                        /* Now follows a string containing the
                         * vertces follow flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->vertices_follow);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the polygon
                         * mesh M vertex count value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->polygon_mesh_M_vertex_count);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the polygon
                         * mesh N vertex count value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->polygon_mesh_N_vertex_count);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the smooth M
                         * surface density value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->smooth_M_surface_density);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the smooth N
                         * surface density value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->smooth_M_surface_density);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the surface
                         * type value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->surface_type);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, polyline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, polyline->dictionary_owner_hard);
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
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (dxf_polyline_get_linetype (polyline), "") == 0)
        {
                dxf_polyline_set_linetype (polyline, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_polyline_get_layer (polyline), "") == 0)
        {
                dxf_polyline_set_layer (polyline, strdup (DXF_DEFAULT_LAYER));
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Write DXF output to fp for a polyline entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_polyline_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfPolyline *polyline
                /*!< a pointer to the DXF polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("POLYLINE");
        DxfVertex *iter = NULL;

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
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_polyline_get_x0 (polyline) != 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () start point has an invalid X-value for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_polyline_get_id_code (polyline));
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_polyline_get_y0 (polyline) != 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () start point has an invalid Y-value for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_polyline_get_id_code (polyline));
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_polyline_get_vertices_follow (polyline) != 1)
        {
                fprintf (stderr,
                  (_("Error in %s () vertices follow flag has an invalid value for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_polyline_get_id_code (polyline));
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_polyline_get_linetype (polyline), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_polyline_get_id_code (polyline));
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_polyline_set_linetype (polyline, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_polyline_get_layer (polyline), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_polyline_get_id_code (polyline));
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                dxf_polyline_set_layer (polyline, strdup (DXF_DEFAULT_LAYER));
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_polyline_get_id_code (polyline) != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_polyline_get_id_code (polyline));
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
        if ((strcmp (polyline->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_polyline_get_dictionary_owner_soft (polyline));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (polyline->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_polyline_get_dictionary_owner_hard (polyline));
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_polyline_get_paperspace (polyline) == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_polyline_get_layer (polyline));
        if (strcmp (dxf_polyline_get_linetype (polyline), DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_polyline_get_linetype (polyline));
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_polyline_get_elevation (polyline) != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_polyline_get_elevation (polyline));
        }
        if (dxf_polyline_get_color (polyline) != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_polyline_get_color (polyline));
        }
        if (dxf_polyline_get_linetype_scale (polyline) != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_polyline_get_linetype_scale (polyline));
        }
        if (dxf_polyline_get_visibility (polyline) != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_polyline_get_visibility (polyline));
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDb3dPolyline\n");
        }
        if (fp->acad_version_number < AutoCAD_2002)
        {
                fprintf (fp->fp, " 66\n%d\n", dxf_polyline_get_vertices_follow (polyline));
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_polyline_get_x0 (polyline));
        fprintf (fp->fp, " 20\n%f\n", dxf_polyline_get_y0 (polyline));
        fprintf (fp->fp, " 30\n%f\n", dxf_polyline_get_z0 (polyline));
        if (dxf_polyline_get_thickness (polyline) != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_polyline_get_thickness (polyline));
        }
        fprintf (fp->fp, " 70\n%d\n", dxf_polyline_get_flag (polyline));
        if (dxf_polyline_get_start_width (polyline) != 0.0)
        {
                fprintf (fp->fp, " 40\n%f\n", dxf_polyline_get_start_width (polyline));
        }
        if (dxf_polyline_get_end_width (polyline) != 0.0)
        {
                fprintf (fp->fp, " 41\n%f\n", dxf_polyline_get_end_width (polyline));
        }
        fprintf (fp->fp, " 71\n%d\n", dxf_polyline_get_polygon_mesh_M_vertex_count (polyline));
        fprintf (fp->fp, " 72\n%d\n", dxf_polyline_get_polygon_mesh_N_vertex_count (polyline));
        fprintf (fp->fp, " 73\n%d\n", dxf_polyline_get_smooth_M_surface_density (polyline));
        fprintf (fp->fp, " 74\n%d\n", dxf_polyline_get_smooth_N_surface_density (polyline));
        fprintf (fp->fp, " 75\n%d\n", dxf_polyline_get_surface_type (polyline));
        if ((fp->acad_version_number >= AutoCAD_12)
                && (dxf_polyline_get_extr_x0 (polyline) != 0.0)
                && (dxf_polyline_get_extr_y0 (polyline) != 0.0)
                && (dxf_polyline_get_extr_z0 (polyline) != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", dxf_polyline_get_extr_x0 (polyline));
                fprintf (fp->fp, "220\n%f\n", dxf_polyline_get_extr_y0 (polyline));
                fprintf (fp->fp, "230\n%f\n", dxf_polyline_get_extr_z0 (polyline));
        }
        /* Start of writing (multiple) vertices. */
        iter = (DxfVertex *) dxf_polyline_get_vertices (polyline);
        while (iter != NULL)
        {
                dxf_vertex_write (fp, iter);
                iter = (DxfVertex *) iter->next;
        }
        dxf_vertex_free (iter);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c POLYLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_polyline_free
(
        DxfPolyline *polyline
                /*!< a pointer to the memory occupied by the DXF
                 * \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_polyline_get_linetype (polyline));
        free (dxf_polyline_get_layer (polyline));
        dxf_binary_graphics_data_free_list (dxf_polyline_get_binary_graphics_data (polyline));
        free (dxf_polyline_get_dictionary_owner_soft (polyline));
        free (dxf_polyline_get_material (polyline));
        free (dxf_polyline_get_dictionary_owner_hard (polyline));
        free (dxf_polyline_get_plot_style_name (polyline));
        free (dxf_polyline_get_color_name (polyline));
        dxf_point_free (dxf_polyline_get_p0 (polyline));
        dxf_vertex_free_list (dxf_polyline_get_vertices (polyline));
        free (polyline);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c POLYLINE entities and all their data fields.
 */
void
dxf_polyline_free_list
(
        DxfPolyline *polylines
                /*!< a pointer to the single linked list of DXF
                 * \c POLYLINE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (polylines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (polylines != NULL)
        {
                DxfPolyline *iter = (DxfPolyline *) polylines->next;
                dxf_polyline_free (polylines);
                polylines = (DxfPolyline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c POLYLINE entity.
 *
 * \return \c id_code.
 */
int
dxf_polyline_get_id_code
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_id_code
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
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
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the linetype from a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c linetype when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_polyline_get_linetype
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c linetype variable is not freed by this
 * function.
 */
DxfPolyline *
dxf_polyline_set_linetype
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c layer from a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c layer when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_polyline_get_layer
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c layer variable is not freed by this function.
 */
DxfPolyline *
dxf_polyline_set_layer
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c elevation a this DXF \c POLYLINE entity.
 *
 * \return \c elevation.
 */
double
dxf_polyline_get_elevation
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_elevation
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c thickness from a DXF \c POLYLINE entity.
 *
 * \return \c thickness.
 */
double
dxf_polyline_get_thickness
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_thickness
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c POLYLINE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_polyline_get_linetype_scale
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the linetype_scale member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_linetype_scale
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative linetype_scale value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c visibility from a DXF \c POLYLINE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_polyline_get_visibility
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_visibility
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c color from a DXF \c POLYLINE entity.
 *
 * \return \c color.
 */
int
dxf_polyline_get_color
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->color);
}


/*!
 * \brief Set the \c color for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_color
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c POLYLINE
 * entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_polyline_get_paperspace
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (polyline->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_paperspace
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c POLYLINE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_polyline_get_graphics_data_size
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        if (polyline->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_graphics_data_size
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
                  (_("Warning in %s () a zero graphics_data_size value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c POLYLINE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_polyline_get_shadow_mode
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_shadow_mode
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c POLYLINE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_polyline_get_binary_graphics_data
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the binary_graphics_data member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) polyline->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c POLYLINE entity.
 */
DxfPolyline *
dxf_polyline_set_binary_graphics_data
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the soft pointer to the \c dictionary_owner_soft from a
 * DXF \c POLYLINE entity.
 *
 * \return a pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_polyline_get_dictionary_owner_soft
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c POLYLINE entity.
 */
DxfPolyline *
dxf_polyline_set_dictionary_owner_soft
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_polyline_get_material
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the material member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_material
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c POLYLINE entity.
 *
 * \return a pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_polyline_get_dictionary_owner_hard
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_dictionary_owner_hard
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c lineweight from a DXF \c POLYLINE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_polyline_get_lineweight
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_lineweight
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_polyline_get_plot_style_name
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the plot_style_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_plot_style_name
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c color_value from a DXF \c POLYLINE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_polyline_get_color_value
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_color_value
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c color_name from a DXF \c POLYLINE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_polyline_get_color_name
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the color_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_color_name
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c transparency from a DXF \c POLYLINE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_polyline_get_transparency
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_transparency
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the insertion point of a DXF \c POLYLINE entity.
 *
 * \return the insertion point \c p0.
 */
DxfPoint *
dxf_polyline_get_p0
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_p0
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->p0 = (DxfPoint *) p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a DXF
 * \c POLYLINE entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_polyline_get_x0
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a DXF
 * \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_x0
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double x0
                /*!< the X-value of the insertion point \c x0 of a
                 * DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a DXF
 * \c POLYLINE entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_polyline_get_y0
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a DXF
 * \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_y0
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a
                 * DXF \c polyline entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a DXF
 * \c POLYLINE entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_polyline_get_z0
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a DXF
 * \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_z0
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double z0
                /*!< the Z-value of the insertion point \c z0 of a
                 * DXF \c polyline entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c start_width of a DXF \c POLYLINE entity.
 *
 * \return the \c start_width.
 */
double
dxf_polyline_get_start_width
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->start_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a start width smaller than 0.0 was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->start_width);
}


/*!
 * \brief Set the \c start_width of a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_start_width
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double start_width
                /*!< the \c start_width of a DXF \c polyline entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (start_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a start_width smaller than 0.0 was passed.\n")),
                  __FUNCTION__);
        }
        polyline->start_width = start_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c end_width of a DXF \c POLYLINE entity.
 *
 * \return the \c end_width.
 */
double
dxf_polyline_get_end_width
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->end_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a end width smaller than 0.0 was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->end_width);
}


/*!
 * \brief Set the \c end_width of a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when successful, or \c NULL when an
 * error occurred.
 */
DxfPolyline *
dxf_polyline_set_end_width
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double end_width
                /*!< the \c end_width of a DXF \c polyline entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (end_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an end_width smaller than 0.0 was passed.\n")),
                  __FUNCTION__);
        }
        polyline->end_width = end_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c vertices_follow from a DXF \c POLYLINE entity.
 *
 * \return \c vertices_follow.
 */
int
dxf_polyline_get_vertices_follow
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->vertices_follow < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the vertices_follow member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->vertices_follow);
}


/*!
 * \brief Set the \c vertices_follow for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_vertices_follow
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int vertices_follow
                /*!< \c vertices_follow. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertices_follow < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative vertices_follow value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->vertices_follow = vertices_follow;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c flag from a DXF \c POLYLINE entity.
 *
 * \return \c flag.
 */
int
dxf_polyline_get_flag
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the flag member.\n")),
                  __FUNCTION__);
        }
        if (polyline->flag > 255)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the flag member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->flag);
}


/*!
 * \brief Set the \c flag for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_flag
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int flag
                /*!< \c flag. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (flag > 255)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c polygon_mesh_M_vertex_count from a DXF \c POLYLINE entity.
 *
 * \return \c polygon_mesh_M_vertex_count.
 */
int
dxf_polyline_get_polygon_mesh_M_vertex_count
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->polygon_mesh_M_vertex_count < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the polygon_mesh_M_vertex_count member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->polygon_mesh_M_vertex_count);
}


/*!
 * \brief Set the \c polygon_mesh_M_vertex_count for a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_polygon_mesh_M_vertex_count
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int polygon_mesh_M_vertex_count
                /*!< \c polygon_mesh_M_vertex_count. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polygon_mesh_M_vertex_count < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->polygon_mesh_M_vertex_count = polygon_mesh_M_vertex_count;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c polygon_mesh_N_vertex_count from a DXF \c POLYLINE entity.
 *
 * \return \c polygon_mesh_N_vertex_count.
 */
int
dxf_polyline_get_polygon_mesh_N_vertex_count
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->polygon_mesh_N_vertex_count < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the polygon_mesh_N_vertex_count member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->polygon_mesh_N_vertex_count);
}


/*!
 * \brief Set the \c polygon_mesh_N_vertex_count for a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_polygon_mesh_N_vertex_count
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int polygon_mesh_N_vertex_count
                /*!< \c polygon_mesh_N_vertex_count. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polygon_mesh_N_vertex_count < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->polygon_mesh_N_vertex_count = polygon_mesh_N_vertex_count;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c smooth_M_surface_density from a DXF \c POLYLINE entity.
 *
 * \return \c smooth_M_surface_density.
 */
int
dxf_polyline_get_smooth_M_surface_density
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->smooth_M_surface_density < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the smooth_M_surface_density member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->smooth_M_surface_density);
}


/*!
 * \brief Set the \c smooth_M_surface_density for a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_smooth_M_surface_density
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int smooth_M_surface_density
                /*!< \c smooth_M_surface_density. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (smooth_M_surface_density < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->smooth_M_surface_density = smooth_M_surface_density;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c smooth_N_surface_density from a DXF \c POLYLINE
 * entity.
 *
 * \return \c smooth_N_surface_density.
 */
int
dxf_polyline_get_smooth_N_surface_density
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->smooth_N_surface_density < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the smooth_N_surface_density member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->smooth_N_surface_density);
}


/*!
 * \brief Set the \c smooth_N_surface_density for a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_smooth_N_surface_density
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int smooth_N_surface_density
                /*!< \c smooth_N_surface_density. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (smooth_N_surface_density < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->smooth_N_surface_density = smooth_N_surface_density;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c surface_type from a DXF \c POLYLINE entity.
 *
 * \return \c surface_type.
 */
int
dxf_polyline_get_surface_type
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->surface_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the surface_type member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->surface_type);
}


/*!
 * \brief Set the \c surface_type for a DXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_surface_type
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        int surface_type
                /*!< \c surface_type. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->surface_type = surface_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the X-value of the extrusion vector of a DXF \c POLYLINE
 * entity.
 *
 * \return the X-value of the extrusion vector.
 */
double
dxf_polyline_get_extr_x0
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector of a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to a DXF \c POLYLINE entity when successful, \c NULL
 * when an error occurred.
 */
DxfPolyline *
dxf_polyline_set_extr_x0
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector of a DXF
                 * \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the Y-value of the extrusion vector of a DXF \c POLYLINE
 * entity.
 *
 * \return the Y-value of the extrusion vector.
 */
double
dxf_polyline_get_extr_y0
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector of a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to a DXF \c POLYLINE entity when successful, \c NULL
 * when an error occurred.
 */
DxfPolyline *
dxf_polyline_set_extr_y0
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector of a DXF
                 * \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the Z-value of the extrusion vector of a DXF \c POLYLINE
 * entity.
 *
 * \return the Z-value of the extrusion vector.
 */
double
dxf_polyline_get_extr_z0
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector of a DXF \c POLYLINE
 * entity.
 *
 * \return a pointer to a DXF \c POLYLINE entity when successful, \c NULL
 * when an error occurred.
 */
DxfPolyline *
dxf_polyline_set_extr_z0
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector of a DXF
                 * \c POLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the pointer to the first vertex of a linked list of
 * \c vertices from a DXF \c POLYLINE entity.
 *
 * \return pointer to the first vertex of a linked list of \c vertices.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfVertex *
dxf_polyline_get_vertices
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->vertices == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the vertices member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfVertex *) polyline->vertices);
}


/*!
 * \brief Set the pointer to the first vertex of a linked list of
 * \c vertices for a DXF \c POLYLINE entity.
 */
DxfPolyline *
dxf_polyline_set_vertices
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        DxfVertex *vertices
                /*!< a pointer to the first vertex of a linked list of
                 * \c vertices. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertices == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->vertices = (DxfVertex *) vertices;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the pointer to the next \c POLYLINE entity from a DXF 
 * \c POLYLINE entity.
 *
 * \return pointer to the next \c POLYLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfPolyline *
dxf_polyline_get_next
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPolyline *) polyline->next);
}


/*!
 * \brief Set the pointer to the next \c POLYLINE for a DXF \c POLYLINE
 * entity.
 */
DxfPolyline *
dxf_polyline_set_next
(
        DxfPolyline *polyline,
                /*!< a pointer to a DXF \c POLYLINE entity. */
        DxfPolyline *next
                /*!< a pointer to the next \c POLYLINE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->next = (struct DxfPolyline *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the pointer to the last \c POLYLINE entity from a linked
 * list of DXF \c POLYLINE entities.
 *
 * \return pointer to the last \c POLYLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfPolyline *
dxf_polyline_get_last
(
        DxfPolyline *polyline
                /*!< a pointer to a DXF \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfPolyline *) polyline);
        }
        DxfPolyline *iter = (DxfPolyline *) polyline->next;
        while (iter->next != NULL)
        {
                iter = (DxfPolyline *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPolyline *) iter);
}


/* EOF */
