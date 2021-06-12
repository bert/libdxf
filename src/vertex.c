/*!
 * \file vertex.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2017, 2018,
 * 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF vertex entity (\c VERTEX).
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


#include "vertex.h"


/*!
 * \brief Allocate memory for a \c DxfVertex.
 *
 * Fill the memory contents with zeros.
 */
DxfVertex *
dxf_vertex_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfVertex *vertex = NULL;
        size_t size;

        size = sizeof (DxfVertex);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((vertex = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfVertex struct.\n")),
                  __FUNCTION__);
                vertex = NULL;
        }
        else
        {
                memset (vertex, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c VERTEX entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfVertex *
dxf_vertex_init
(
        DxfVertex *vertex
                /*!< a pointer to the DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                vertex = dxf_vertex_new ();
        }
        if (vertex == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfVertex struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        vertex->id_code = 0;
        vertex->linetype = strdup (DXF_DEFAULT_LINETYPE);
        vertex->layer = strdup (DXF_DEFAULT_LAYER);
        vertex->elevation = 0.0;
        vertex->thickness = 0.0;
        vertex->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        vertex->visibility = DXF_DEFAULT_VISIBILITY;
        vertex->color = DXF_COLOR_BYLAYER;
        vertex->paperspace = DXF_MODELSPACE;
        vertex->graphics_data_size = 0;
        vertex->shadow_mode = 0;
        vertex->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        vertex->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) vertex->binary_graphics_data);
        vertex->dictionary_owner_soft = strdup ("");
        vertex->material = strdup ("");
        vertex->dictionary_owner_hard = strdup ("");
        vertex->lineweight = 0;
        vertex->plot_style_name = strdup ("");
        vertex->color_value = 0;
        vertex->color_name = strdup ("");
        vertex->transparency = 0;
        vertex->p0 = (DxfPoint *) dxf_point_new ();
        vertex->p0 = dxf_point_init ((DxfPoint *) vertex->p0);
        vertex->p0->x0 = 0.0;
        vertex->p0->y0 = 0.0;
        vertex->p0->z0 = 0.0;
        vertex->start_width = 0.0;
        vertex->end_width = 0.0;
        vertex->bulge = 0.0;
        vertex->curve_fit_tangent_direction = 0.0;
        vertex->flag = 0;
        vertex->polyface_mesh_vertex_index_1 = 0;
        vertex->polyface_mesh_vertex_index_2 = 0;
        vertex->polyface_mesh_vertex_index_3 = 0;
        vertex->polyface_mesh_vertex_index_4 = 0;
        vertex->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Read data from a DXF file into an \c VERTEX entity.
 *
 * The last line read from file contained the string "VERTEX". \n
 * Now follows some data for the \c VERTEX, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c vertex. \n
 *
 * \return a pointer to \c vertex.
 */
DxfVertex *
dxf_vertex_read
(
        DxfFile *fp,
                /*!< filepointer to the input file (or device). */
        DxfVertex *vertex
                /*!< a pointer to the DXF \c VERTEX entity. */
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
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                vertex = dxf_vertex_init (vertex);
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
                        fscanf (fp->fp, "%x\n", (uint *) &vertex->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, vertex->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, vertex->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->p0->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (vertex->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * start width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->start_width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * end width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->end_width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * bulge. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->bulge);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * curve fitting tangent. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &vertex->curve_fit_tangent_direction);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &vertex->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the flag
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the Polyface
                         * mesh vertex index value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->polyface_mesh_vertex_index_1);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the Polyface
                         * mesh vertex index value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->polyface_mesh_vertex_index_2);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the Polyface
                         * mesh vertex index value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->polyface_mesh_vertex_index_3);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the Polyface
                         * mesh vertex index value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->polyface_mesh_vertex_index_4);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbVertex") != 0)
                        && (strcmp (temp_string, "AcDb2dVertex") != 0)
                        && (strcmp (temp_string, "AcDb3dPolylineVertex") != 0))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &vertex->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &vertex->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, vertex->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) vertex->binary_graphics_data->next);
                        vertex->binary_graphics_data = (DxfBinaryGraphicsData *) vertex->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, vertex->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, vertex->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, vertex->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &vertex->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, vertex->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &vertex->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, vertex->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &vertex->transparency);
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
        if (strcmp (vertex->linetype, "") == 0)
        {
                vertex->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (vertex->layer, "") == 0)
        {
                vertex->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Write DXF output to fp for a vertex entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_vertex_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfVertex *vertex
                /*!< a pointer to the DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("VERTEX");

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
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (vertex->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, vertex->id_code);
                fprintf (stderr,
                  (_("    %s entity is reset to default linetype")),
                  dxf_entity_name);
                vertex->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (vertex->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, vertex->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0")),
                  dxf_entity_name);
                vertex->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (vertex->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", vertex->id_code);
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
        if ((strcmp (vertex->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", vertex->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (vertex->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", vertex->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (vertex->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", vertex->layer);
        if (strcmp (vertex->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", vertex->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (vertex->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", vertex->elevation);
        }
        if (vertex->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", vertex->color);
        }
        if (vertex->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", vertex->linetype_scale);
        }
        if (vertex->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", vertex->visibility);
        }
        /*! \todo Put \c thickness in the correct order. */ 
        if (vertex->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", vertex->thickness);
        }
        fprintf (fp->fp, "100\nAcDbVertex\n");
        if ((DXF_CHECK_BIT (vertex->flag, 0))
          || (DXF_CHECK_BIT (vertex->flag, 1))
          || (DXF_CHECK_BIT (vertex->flag, 2))
          || (DXF_CHECK_BIT (vertex->flag, 3))
          || (DXF_CHECK_BIT (vertex->flag, 4)))
        {
                fprintf (fp->fp, "100\nAcDb2dVertex\n");
        }
        if ((DXF_CHECK_BIT (vertex->flag, 5))
          || (DXF_CHECK_BIT (vertex->flag, 6))
          || (DXF_CHECK_BIT (vertex->flag, 7)))
        {
                fprintf (fp->fp, "100\nAcDb3dPolylineVertex\n");
        }
        fprintf (fp->fp, "100\nAcDb3dPolylineVertex\n");
        fprintf (fp->fp, " 10\n%f\n", vertex->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", vertex->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", vertex->p0->z0);
        if (vertex->start_width != 0.0)
        {
                fprintf (fp->fp, " 40\n%f\n", vertex->start_width);
        }
        if (vertex->end_width != 0.0)
        {
                fprintf (fp->fp, " 41\n%f\n", vertex->end_width);
        }
        if (vertex->bulge != 0.0)
        {
                fprintf (fp->fp, " 42\n%f\n", vertex->bulge);
        }
        fprintf (fp->fp, " 70\n%d\n", vertex->flag);
        if (vertex->curve_fit_tangent_direction != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", vertex->curve_fit_tangent_direction);
        }
        if (vertex->polyface_mesh_vertex_index_1 != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", vertex->polyface_mesh_vertex_index_1);
        }
        if (vertex->polyface_mesh_vertex_index_2 != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", vertex->polyface_mesh_vertex_index_2);
        }
        if (vertex->polyface_mesh_vertex_index_3 != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", vertex->polyface_mesh_vertex_index_3);
        }
        if (vertex->polyface_mesh_vertex_index_4 != 0)
        {
                fprintf (fp->fp, " 74\n%d\n", vertex->polyface_mesh_vertex_index_4);
        }
        fprintf (fp->fp, " 91\n%d\n", vertex->vertex_identifier);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a \c VERTEX entity and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_vertex_free
(
        DxfVertex *vertex
                /*!< a pointer to the DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->next != NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (vertex->linetype);
        free (vertex->layer);
        dxf_binary_graphics_data_free_list (vertex->binary_graphics_data);
        free (vertex->dictionary_owner_soft);
        free (vertex->material);
        free (vertex->dictionary_owner_hard);
        free (vertex->plot_style_name);
        free (vertex->color_name);
        dxf_point_free (vertex->p0);
        free (vertex);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c VERTEX entities and all their data fields.
 */
void
dxf_vertex_free_list
(
        DxfVertex *vertices
                /*!< a pointer to the single linked list of DXF
                 * \c VERTEX entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (vertices == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (vertices != NULL)
        {
                DxfVertex *iter = (DxfVertex *) vertices->next;
                dxf_vertex_free (vertices);
                vertices = (DxfVertex *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c VERTEX entity.
 *
 * \return \c id_code.
 */
int
dxf_vertex_get_id_code
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_id_code
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
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
        if (vertex == NULL)
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
        vertex->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c linetype from a DXF \c VERTEX entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_vertex_get_linetype
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (vertex->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_linetype
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c layer from a DXF \c VERTEX entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_vertex_get_layer
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (vertex->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_layer
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c elevation from a DXF \c VERTEX entity.
 *
 * \return \c elevation.
 */
double
dxf_vertex_get_elevation
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_elevation
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c thickness from a DXF \c VERTEX entity.
 *
 * \return \c thickness.
 */
double
dxf_vertex_get_thickness
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_thickness
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c VERTEX entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_vertex_get_linetype_scale
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_linetype_scale
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c visibility from a DXF \c VERTEX entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_vertex_get_visibility
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (vertex->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_visibility
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c color from a DXF \c VERTEX entity.
 *
 * \return color.
 */
int
dxf_vertex_get_color
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->color);
}


/*!
 * \brief Set the \c color for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_color
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c VERTEX entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_vertex_get_paperspace
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (vertex->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_paperspace
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c VERTEX
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_vertex_get_graphics_data_size
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (vertex->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c VERTEX entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_graphics_data_size
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        vertex->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c VERTEX entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_vertex_get_shadow_mode
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c VERTEX entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_shadow_mode
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c VERTEX entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_vertex_get_binary_graphics_data
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) vertex->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_binary_graphics_data
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c VERTEX entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_vertex_get_dictionary_owner_soft
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (vertex->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_dictionary_owner_soft
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c VERTEX entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_vertex_get_material
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (vertex->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c VERTEX entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_material
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c VERTEX entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_vertex_get_dictionary_owner_hard
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (vertex->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_dictionary_owner_hard
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c lineweight from a DXF \c VERTEX entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_vertex_get_lineweight
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c VERTEX entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_lineweight
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c VERTEX entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_vertex_get_plot_style_name
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (vertex->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c VERTEX entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_plot_style_name
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c color_value from a DXF \c VERTEX entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_vertex_get_color_value
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c VERTEX entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_color_value
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c color_name from a DXF \c VERTEX entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_vertex_get_color_name
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (vertex->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c VERTEX entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_color_name
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c transparency from a DXF \c VERTEX entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_vertex_get_transparency
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c VERTEX entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_transparency
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the location point \c p0 of a DXF \c VERTEX entity.
 *
 * \return the location point \c p0.
 */
DxfPoint *
dxf_vertex_get_p0
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->p0);
}


/*!
 * \brief Set the location point \c p0 of a DXF \c VERTEX entity.
 *
 * \return a pointer to a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_p0
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the X-value of the location point \c x0 of a DXF \c VERTEX
 * entity.
 *
 * \return the X-value of the location point \c x0.
 */
double
dxf_vertex_get_x0
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->p0->x0);
}


/*!
 * \brief Set the X-value of the location point \c x0 of a DXF \c VERTEX
 * entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_x0
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double x0
                /*!< the X-value of the location point \c x0 of a DXF
                 * \c VERTEX entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the Y-value of the location point \c y0 of a DXF \c VERTEX
 * entity.
 *
 * \return the Y-value of the location point \c y0.
 */
double
dxf_vertex_get_y0
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->p0->y0);
}


/*!
 * \brief Set the Y-value of the location point \c y0 of a DXF \c VERTEX
 * entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_y0
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double y0
                /*!< the Y-value of the location point \c y0 of a DXF
                 * \c VERTEX entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the Z-value of the location point \c z0 of a DXF \c VERTEX
 * entity.
 *
 * \return the Z-value of the location point \c z0.
 */
double
dxf_vertex_get_z0
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->p0->z0);
}


/*!
 * \brief Set the Z-value of the location point \c z0 of a DXF \c VERTEX
 * entity.
 *
 * \return a pointer to \c vertex when successful, or \c NULL when an
 * error occurred.
 */
DxfVertex *
dxf_vertex_set_z0
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double z0
                /*!< the Z-value of the location point \c z0 of a DXF
                 * \c VERTEX entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c start_width from a DXF \c VERTEX entity.
 *
 * \return \c start_width.
 */
double
dxf_vertex_get_start_width
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->start_width);
}


/*!
 * \brief Set the \c start_width for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_start_width
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double start_width
                /*!< the \c start_width to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->start_width = start_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c end_width from a DXF \c VERTEX entity.
 *
 * \return \c end_width.
 */
double
dxf_vertex_get_end_width
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->end_width);
}


/*!
 * \brief Set the \c end_width for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_end_width
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double end_width
                /*!< the \c end_width to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->end_width = end_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c bulge from a DXF \c VERTEX entity.
 *
 * \return \c bulge.
 */
double
dxf_vertex_get_bulge
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->bulge);
}


/*!
 * \brief Set the \c bulge for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_bulge
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double bulge
                /*!< the \c bulge to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->bulge = bulge;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c curve_fit_tangent_direction from a DXF \c VERTEX
 * entity.
 *
 * \return \c curve_fit_tangent_direction.
 */
double
dxf_vertex_get_curve_fit_tangent_direction
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->curve_fit_tangent_direction);
}


/*!
 * \brief Set the \c curve_fit_tangent_direction for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_curve_fit_tangent_direction
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        double curve_fit_tangent_direction
                /*!< the \c curve_fit_tangent_direction to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->curve_fit_tangent_direction = curve_fit_tangent_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c flag from a DXF \c VERTEX entity.
 *
 * \return \c flag.
 */
int
dxf_vertex_get_flag
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (vertex->flag > 0x11111111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->flag);
}


/*!
 * \brief Set the \c flag for a DXF \c VERTEX entity.
 */
DxfVertex *
dxf_vertex_set_flag
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int flag
                /*!< the \c flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        if (flag > 0x11111111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        vertex->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c polyface_mesh_vertex_index_1 from a DXF \c VERTEX
 * entity.
 *
 * \return \c polyface_mesh_vertex_index_1.
 */
int
dxf_vertex_get_polyface_mesh_vertex_index_1
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->polyface_mesh_vertex_index_1 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->polyface_mesh_vertex_index_1);
}


/*!
 * \brief Set the \c polyface_mesh_vertex_index_1 for a DXF \c VERTEX
 * entity.
 */
DxfVertex *
dxf_vertex_set_polyface_mesh_vertex_index_1
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int polyface_mesh_vertex_index_1
                /*!< the \c polyface_mesh_vertex_index_1 to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyface_mesh_vertex_index_1 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        vertex->polyface_mesh_vertex_index_1 = polyface_mesh_vertex_index_1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c polyface_mesh_vertex_index_2 from a DXF \c VERTEX
 * entity.
 *
 * \return \c polyface_mesh_vertex_index_2.
 */
int
dxf_vertex_get_polyface_mesh_vertex_index_2
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->polyface_mesh_vertex_index_2 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->polyface_mesh_vertex_index_2);
}


/*!
 * \brief Set the \c polyface_mesh_vertex_index_2 for a DXF \c VERTEX
 * entity.
 */
DxfVertex *
dxf_vertex_set_polyface_mesh_vertex_index_2
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int polyface_mesh_vertex_index_2
                /*!< the \c polyface_mesh_vertex_index_2 to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyface_mesh_vertex_index_2 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        vertex->polyface_mesh_vertex_index_2 = polyface_mesh_vertex_index_2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c polyface_mesh_vertex_index_3 from a DXF \c VERTEX
 * entity.
 *
 * \return \c polyface_mesh_vertex_index_3.
 */
int
dxf_vertex_get_polyface_mesh_vertex_index_3
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->polyface_mesh_vertex_index_3 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->polyface_mesh_vertex_index_3);
}


/*!
 * \brief Set the \c polyface_mesh_vertex_index_3 for a DXF \c VERTEX
 * entity.
 */
DxfVertex *
dxf_vertex_set_polyface_mesh_vertex_index_3
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int polyface_mesh_vertex_index_3
                /*!< the \c polyface_mesh_vertex_index_3 to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyface_mesh_vertex_index_3 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        vertex->polyface_mesh_vertex_index_3 = polyface_mesh_vertex_index_3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the \c polyface_mesh_vertex_index_4 from a DXF \c VERTEX
 * entity.
 *
 * \return \c polyface_mesh_vertex_index_4.
 */
int
dxf_vertex_get_polyface_mesh_vertex_index_4
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->polyface_mesh_vertex_index_4 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->polyface_mesh_vertex_index_4);
}


/*!
 * \brief Set the \c polyface_mesh_vertex_index_4 for a DXF \c VERTEX
 * entity.
 */
DxfVertex *
dxf_vertex_set_polyface_mesh_vertex_index_4
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        int polyface_mesh_vertex_index_4
                /*!< the \c polyface_mesh_vertex_index_4 to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyface_mesh_vertex_index_4 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        vertex->polyface_mesh_vertex_index_4 = polyface_mesh_vertex_index_4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the pointer to the next \c VERTEX entity from a DXF
 * \c VERTEX entity.
 *
 * \return pointer to the next \c VERTEX entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfVertex *
dxf_vertex_get_next
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfVertex *) vertex->next);
}


/*!
 * \brief Set the pointer to the next \c VERTEX for a DXF \c VERTEX
 * entity.
 */
DxfVertex *
dxf_vertex_set_next
(
        DxfVertex *vertex,
                /*!< a pointer to a DXF \c VERTEX entity. */
        DxfVertex *next
                /*!< a pointer to the next \c VERTEX for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->next = (struct DxfVertex *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the pointer to the last \c VERTEX entity from a linked list
 * of DXF \c VERTEX entities.
 *
 * \return pointer to the last \c VERTEX entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfVertex *
dxf_vertex_get_last
(
        DxfVertex *vertex
                /*!< a pointer to a DXF \c VERTEX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfVertex *) vertex);
        }
        DxfVertex *iter = (DxfVertex *) vertex->next;
        while (iter->next != NULL)
        {
                iter = (DxfVertex *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfVertex *) iter);
}


/* EOF */
