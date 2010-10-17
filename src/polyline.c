/*!
 * \file polyline.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF polyline entity (\c POLYLINE).
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_polyline_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfPolyline *dxf_polyline = NULL;
        size_t size;

        size = sizeof (DxfPolyline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_polyline = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_polyline_new () could not allocate memory for a DxfArc struct.\n");
                dxf_polyline = NULL;
        }
        else
        {
                memset (dxf_polyline, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_polyline_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_polyline);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c POLYLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfPolyline *
dxf_polyline_init
(
        DxfPolyline *dxf_polyline
                /*!< DXF polyline entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_polyline_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_polyline = dxf_polyline_new ();
        if (dxf_polyline == NULL)
        {
              fprintf (stderr, "ERROR in dxf_polyline_init () could not allocate memory for a DxfPolyline struct.\n");
              return (NULL);
        }
        dxf_polyline->common.id_code = 0;
        dxf_polyline->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_polyline->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_polyline->x0 = 0.0;
        dxf_polyline->y0 = 0.0;
        dxf_polyline->z0 = 0.0;
        dxf_polyline->common.thickness = 0.0;
        dxf_polyline->start_width = 0.0;
        dxf_polyline->end_width = 0.0;
        dxf_polyline->vertices_follow = 1;
        dxf_polyline->common.color = DXF_COLOR_BYLAYER;
        dxf_polyline->common.paperspace = DXF_MODELSPACE;
        dxf_polyline->flag = 0;
        dxf_polyline->polygon_mesh_M_vertex_count = 0;
        dxf_polyline->polygon_mesh_N_vertex_count = 0;
        dxf_polyline->smooth_M_surface_density = 0;
        dxf_polyline->smooth_N_surface_density = 0;
        dxf_polyline->surface_type = 0;
        dxf_polyline->extr_x0 = 0.0;
        dxf_polyline->extr_y0 = 0.0;
        dxf_polyline->extr_z0 = 0.0;
        dxf_polyline->common.acad_version_number = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_polyline_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_polyline);
}



/*!
 * \brief Read data from a DXF file into an \c POLYLINE entity.
 *
 * The last line read from file contained the string "POLYLINE". \n
 * Now follows some data for the \c POLYLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_polyline. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_polyline_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfPolyline *dxf_polyline,
                /*!< DXF polyline entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_polyline_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_polyline)
        {
                dxf_polyline = dxf_polyline_new ();
        }
        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_polyline_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_polyline->common.id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_polyline->common.linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_polyline->common.layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the primary point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the primary point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the primary point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->common.thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * starting width. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->start_width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * end width. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->end_width);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->common.color);
                }
                else if (strcmp (temp_string, "66") == 0)
                {
                        /* Now follows a string containing the
                         * vertces follow flag. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->vertices_follow);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->common.paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the polygon
                         * mesh M vertex count value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->polygon_mesh_M_vertex_count);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the polygon
                         * mesh N vertex count value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->polygon_mesh_N_vertex_count);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the smooth M
                         * surface density value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->smooth_M_surface_density);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the smooth N
                         * surface density value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->smooth_M_surface_density);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the surface
                         * type value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_polyline->surface_type);
                }
                else if ((acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_polyline->extr_z0);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr, "Warning: in dxf_lwpolyline_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_lwpolyline_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a polyline entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_polyline_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, if omitted defaults to \c BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * if omitted defaults to 0.0. */
        double y0,
                /*!< group code = 20\n
                 * if omitted defaults to 0.0. */
        double z0,
                /*!< group code = 30\n
                 * default elevation for vertices. */
        double thickness,
                /*!< group code = 39\n
                 * optional, if omitted defaults to 0.0. */
        double start_width,
                /*!< group code = 40\n
                 * optional, if omitted defaults to 0.0. */
        double end_width,
                /*!< group code = 41\n
                 * optional, if omitted defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, if omitted defaults to \c BYLAYER. */
        int vertices_follow,
                /*!< group code = 66\n
                 * mandatory, always 1 (one or more vertices make up a
                 * polyline). */
        int paperspace,
                /*!< group code = 67\n
                 * optional, if omitted defaults to 0 (modelspace). */
        int flag,
                /*!< group code = 70\n
                 * optional, if omitted defaults to 0. */
        int polygon_mesh_M_vertex_count,
                /*!< group code = 71\n
                 * optional, if omitted defaults to 0. */
        int polygon_mesh_N_vertex_count,
                /*!< group code = 72\n
                 * optional, if omitted defaults to 0. */
        int smooth_M_surface_density,
                /*!< group code = 73\n
                 * optional, if omitted defaults to 0. */
        int smooth_N_surface_density,
                /*!< group code = 74\n
                 * optional, if omitted defaults to 0. */
        int surface_type
                /*!< group code = 75\n
                 * optional, if omitted defaults to 0. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_polyline_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("POLYLINE");

        if (x0 != 0.0)
        {
                fprintf (stderr, "Error in dxf_polyline_write_lowlevel () start point has an invalid X-value for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (y0 != 0.0)
        {
                fprintf (stderr, "Error in dxf_polyline_write_lowlevel () start point has an invalid Y-value for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_polyline_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n",
                        dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (vertices_follow != 1)
        {
                fprintf (stderr, "Error in dxf_polyline_write_lowlevel () vertices follow flag has an invalid value for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        if (start_width != 0.0)
        {
                fprintf (fp, " 40\n%f\n", start_width);
        }
        if (end_width != 0.0)
        {
                fprintf (fp, " 41\n%f\n", end_width);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        fprintf (fp, " 66\n%d\n", vertices_follow);
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", flag);
        fprintf (fp, " 71\n%d\n", polygon_mesh_M_vertex_count);
        fprintf (fp, " 72\n%d\n", polygon_mesh_N_vertex_count);
        fprintf (fp, " 73\n%d\n", smooth_M_surface_density);
        fprintf (fp, " 74\n%d\n", smooth_N_surface_density);
        fprintf (fp, " 75\n%d\n", surface_type);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_polyline_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
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
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfPolyline dxf_polyline
                /*!< DXF polyline entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_polyline_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("POLYLINE");

        if (dxf_polyline.x0 != 0.0)
        {
                fprintf (stderr, "Error in dxf_polyline_write () start point has an invalid X-value for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_polyline.common.id_code);
                return (EXIT_FAILURE);
        }
        if (dxf_polyline.y0 != 0.0)
        {
                fprintf (stderr, "Error in dxf_polyline_write () start point has an invalid Y-value for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_polyline.common.id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_polyline.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_polyline_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_polyline.common.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n",
                        dxf_entity_name);
                dxf_polyline.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_polyline.vertices_follow != 1)
        {
                fprintf (stderr, "Error in dxf_polyline_write () vertices follow flag has an invalid value for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_polyline.common.id_code);
                return (EXIT_FAILURE);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_polyline.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_polyline.common.id_code);
        }
        if (strcmp (dxf_polyline.common.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_polyline.common.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_polyline.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_polyline.x0);
        fprintf (fp, " 20\n%f\n", dxf_polyline.y0);
        fprintf (fp, " 30\n%f\n", dxf_polyline.z0);
        if (dxf_polyline.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_polyline.common.thickness);
        }
        if (dxf_polyline.start_width != 0.0)
        {
                fprintf (fp, " 40\n%f\n", dxf_polyline.start_width);
        }
        if (dxf_polyline.end_width != 0.0)
        {
                fprintf (fp, " 41\n%f\n", dxf_polyline.end_width);
        }
        if (dxf_polyline.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_polyline.common.color);
        }
        fprintf (fp, " 66\n%d\n", dxf_polyline.vertices_follow);
        if (dxf_polyline.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", dxf_polyline.flag);
        fprintf (fp, " 71\n%d\n", dxf_polyline.polygon_mesh_M_vertex_count);
        fprintf (fp, " 72\n%d\n", dxf_polyline.polygon_mesh_N_vertex_count);
        fprintf (fp, " 73\n%d\n", dxf_polyline.smooth_M_surface_density);
        fprintf (fp, " 74\n%d\n", dxf_polyline.smooth_N_surface_density);
        fprintf (fp, " 75\n%d\n", dxf_polyline.surface_type);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_polyline_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
