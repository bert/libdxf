/*!
 * \file mesh.c
 *
 * \author Copyright (C) 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mesh entity (\c MESH).
 *
 * \since The \c MESH entity was introduced in DXF R2011.
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


#include "mesh.h"


/*!
 * \brief Allocate memory for a DXF \c MESH entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMesh *
dxf_mesh_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMesh *mesh = NULL;
        size_t size;

        size = sizeof (DxfMesh);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mesh = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                mesh = NULL;
        }
        else
        {
                memset (mesh, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c MESH
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMesh *
dxf_mesh_init
(
        DxfMesh *mesh
                /*!< a pointer to the DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mesh = dxf_mesh_new ();
        }
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        mesh->id_code = 0;
        mesh->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mesh->layer = strdup (DXF_DEFAULT_LAYER);
        mesh->elevation = 0.0;
        mesh->thickness = 0.0;
        mesh->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        mesh->visibility = DXF_DEFAULT_VISIBILITY;
        mesh->color = DXF_COLOR_BYLAYER;
        mesh->paperspace = DXF_MODELSPACE;
        mesh->graphics_data_size = 0;
        mesh->shadow_mode = 0;
        mesh->dictionary_owner_soft = strdup ("");
        mesh->object_owner_soft = strdup ("");
        mesh->material = strdup ("");
        mesh->dictionary_owner_hard = strdup ("");
        mesh->lineweight = 0;
        mesh->plot_style_name = strdup ("");
        mesh->color_value = 0;
        mesh->color_name = strdup ("");
        mesh->transparency = 0;
        mesh->p0 = dxf_point_new ();
        mesh->p0 = dxf_point_init (mesh->p0);
        mesh->p0->x0 = 0.0;
        mesh->p0->y0 = 0.0;
        mesh->p0->z0 = 0.0;
        mesh->version = 0;
        mesh->blend_crease_property = 0;
        mesh->face_list_item = dxf_int32_new ();
        mesh->face_list_item = dxf_int32_init (mesh->face_list_item);
        mesh->edge_vertex_index = dxf_int32_new ();
        mesh->edge_vertex_index = dxf_int32_init (mesh->edge_vertex_index);
        mesh->number_of_property_overridden_sub_entities = 0;
        mesh->property_type = 0;
        mesh->subdivision_level = 0;
        mesh->sub_entity_marker = 0;
        mesh->vertex_count_level_0 = 0;
        mesh->count_of_property_overridden = 0;
        mesh->face_list_size_level_0 = 0;
        mesh->edge_count_level_0 = 0;
        mesh->edge_crease_count_level_0 = 0;
        mesh->edge_create_value = dxf_double_new ();
        mesh->edge_create_value = dxf_double_init (mesh->edge_create_value);
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        mesh->binary_graphics_data = NULL;
        mesh->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Read data from a DXF file into a DXF \c MESH entity.
 *
 * The last line read from file contained the string "MESH". \n
 * Now follows some data for the \c MESH, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c mesh. \n
 *
 * \return a pointer to \c mesh.
 */
DxfMesh *
dxf_mesh_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfMesh *mesh
                /*!< a pointer to the DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfBinaryData *iter310 = NULL;
        int iter330;

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
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mesh = dxf_mesh_init (mesh);
        }
        if (mesh->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                mesh->binary_graphics_data = dxf_binary_data_init (mesh->binary_graphics_data);
                if (mesh->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                mesh->p0 = dxf_point_init (mesh->p0);
                if (mesh->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) mesh->binary_graphics_data;
        iter330 = 0;
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
                        fscanf (fp->fp, "%x\n", (uint *) &mesh->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mesh->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mesh->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mesh->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mesh->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mesh->p0->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mesh->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mesh->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mesh->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mesh->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mesh->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mesh->paperspace);
                }
                /*! \todo Implement Group codes 90 - 95 in a proper way. */
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mesh->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "AcDbSubMesh") != 0)
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
                        fscanf (fp->fp, "%d\n", &mesh->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mesh->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_data_init ((DxfBinaryData *) iter310->next);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mesh->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mesh->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mesh->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mesh->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mesh->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mesh->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &mesh->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mesh->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &mesh->transparency);
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
        if (strcmp (mesh->linetype, "") == 0)
        {
                mesh->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (mesh->layer, "") == 0)
        {
                mesh->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Write DXF output for a DXF \c MESH entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mesh_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfMesh *mesh
                /*!< a pointer to the DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("MESH");

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
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (mesh->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, mesh->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                mesh->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (mesh->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, mesh->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                mesh->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (mesh->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", mesh->id_code);
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
        if ((strcmp (mesh->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", mesh->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (mesh->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", mesh->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (mesh->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", mesh->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (mesh->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", mesh->layer);
        if (strcmp (mesh->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", mesh->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (mesh->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", mesh->material);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (mesh->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", mesh->elevation);
        }
        if (mesh->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", mesh->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", mesh->lineweight);
        }
        if (mesh->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", mesh->linetype_scale);
        }
        if (mesh->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", mesh->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", mesh->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", mesh->graphics_data_size);
#endif
                if (mesh->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) mesh->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", mesh->color_value);
                fprintf (fp->fp, "430\n%s\n", mesh->color_name);
                fprintf (fp->fp, "440\n%ld\n", mesh->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", mesh->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", mesh->shadow_mode);
        }
        if (mesh->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", mesh->thickness);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSubMesh\n");
        }
        fprintf (fp->fp, " 71\n%d\n", mesh->version);
        fprintf (fp->fp, " 72\n%d\n", mesh->blend_crease_property);
        fprintf (fp->fp, " 91\n%d\n", mesh->subdivision_level);
        fprintf (fp->fp, " 92\n%d\n", mesh->vertex_count_level_0);
        if (mesh->p0 != NULL)
        {
                DxfPoint *p0_iter;
                p0_iter = (DxfPoint *) mesh->p0;
                while (p0_iter != NULL)
                {
                        fprintf (fp->fp, " 10\n%f\n", mesh->p0->x0);
                        fprintf (fp->fp, " 20\n%f\n", mesh->p0->y0);
                        fprintf (fp->fp, " 30\n%f\n", mesh->p0->z0);
                        p0_iter = (DxfPoint *) p0_iter->next;
                }
        }
        fprintf (fp->fp, " 93\n%d\n", mesh->face_list_size_level_0);
        if (mesh->face_list_item != NULL)
        {
                DxfInt32 *face_list_item_iter;
                face_list_item_iter = (DxfInt32 *) mesh->face_list_item;
                while (face_list_item_iter != NULL)
                {
                        fprintf (fp->fp, " 90\n%d\n", face_list_item_iter->value);
                        face_list_item_iter = (DxfInt32 *) face_list_item_iter->next;
                }
        }
        fprintf (fp->fp, " 94\n%d\n", mesh->edge_count_level_0);
        if (mesh->edge_vertex_index != NULL)
        {
                DxfInt32 *edge_vertex_index_iter;
                edge_vertex_index_iter = (DxfInt32 *) mesh->edge_vertex_index;
                while (edge_vertex_index_iter != NULL)
                {
                        fprintf (fp->fp, " 90\n%d\n", edge_vertex_index_iter->value);
                        edge_vertex_index_iter = (DxfInt32 *) edge_vertex_index_iter->next;
                }
        }
        fprintf (fp->fp, " 95\n%d\n", mesh->edge_crease_count_level_0);
        if (mesh->edge_create_value != NULL)
        {
                DxfDouble *edge_create_value_iter;
                edge_create_value_iter = (DxfDouble *) mesh->edge_create_value;
                while (edge_create_value_iter != NULL)
                {
                        fprintf (fp->fp, "140\n%f\n", mesh->edge_create_value->value);
                        edge_create_value_iter = (DxfDouble *) edge_create_value_iter->next;
                }
        }
        fprintf (fp->fp, " 90\n%d\n", mesh->number_of_property_overridden_sub_entities);
        fprintf (fp->fp, " 91\n%d\n", mesh->sub_entity_marker);
        fprintf (fp->fp, " 92\n%d\n", mesh->count_of_property_overridden);
        fprintf (fp->fp, " 90\n%d\n", mesh->property_type);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c MESH entity and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mesh_free
(
        DxfMesh *mesh
                /*!< a pointer to the memory occupied by the DXF \c MESH
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (mesh->linetype);
        free (mesh->layer);
        dxf_binary_data_free_list (mesh->binary_graphics_data);
        free (mesh->dictionary_owner_soft);
        free (mesh->object_owner_soft);
        free (mesh->material);
        free (mesh->dictionary_owner_hard);
        free (mesh->plot_style_name);
        free (mesh->color_name);
        dxf_point_free_list (mesh->p0);
        dxf_int32_free_list (mesh->face_list_item);
        dxf_int32_free_list (mesh->edge_vertex_index);
        dxf_double_free_list (mesh->edge_create_value);
        free (mesh);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c MESH entities and all their data fields.
 */
void
dxf_mesh_free_list
(
        DxfMesh *meshes
                /*!< a pointer to the single linked list of DXF
                 * \c MESH entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (meshes == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (meshes != NULL)
        {
                DxfMesh *iter = (DxfMesh *) meshes->next;
                dxf_mesh_free (meshes);
                meshes = (DxfMesh *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c MESH entity.
 *
 * \return \c id_code.
 */
int
dxf_mesh_get_id_code
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_id_code
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
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
        if (mesh == NULL)
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
        mesh->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c linetype from a DXF \c MESH entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_mesh_get_linetype
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_linetype
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c layer from a DXF \c MESH entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_mesh_get_layer
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_layer
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c elevation from a DXF \c MESH entity.
 *
 * \return \c elevation.
 */
double
dxf_mesh_get_elevation
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_elevation
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c thickness from a DXF \c MESH entity.
 *
 * \return \c thickness.
 */
double
dxf_mesh_get_thickness
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_thickness
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c MESH entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_mesh_get_linetype_scale
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_linetype_scale
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c visibility from a DXF \c MESH entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_mesh_get_visibility
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_visibility
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c color from a DXF \c MESH entity.
 *
 * \return color.
 */
int
dxf_mesh_get_color
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->color);
}


/*!
 * \brief Set the \c color for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_color
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c MESH entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_mesh_get_paperspace
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_paperspace
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c MESH entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_mesh_get_graphics_data_size
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_graphics_data_size
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c MESH entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mesh_get_shadow_mode
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_shadow_mode
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c MESH entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_mesh_get_binary_graphics_data
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) mesh->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_binary_graphics_data
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c MESH entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mesh_get_dictionary_owner_soft
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_dictionary_owner_soft
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c MESH entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mesh_get_object_owner_soft
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_object_owner_soft
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c MESH entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_mesh_get_material
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_material
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c MESH entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mesh_get_dictionary_owner_hard
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_dictionary_owner_hard
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c lineweight from a DXF \c MESH entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mesh_get_lineweight
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_lineweight
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c MESH entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_mesh_get_plot_style_name
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_plot_style_name
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c color_value from a DXF \c MESH entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mesh_get_color_value
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_color_value
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c color_name from a DXF \c MESH entity.
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mesh_get_color_name
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_color_name
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c transparency from a DXF \c MESH entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mesh_get_transparency
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_transparency
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the vertex position \c p0 of a DXF \c MESH entity.
 *
 * \return the vertex position \c p0.
 */
DxfPoint *
dxf_mesh_get_p0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->p0);
}


/*!
 * \brief Set the vertex position \c p0 of a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_p0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the X-value of the vertex position \c x0 of a DXF \c MESH
 * entity.
 *
 * \return the X-value of the vertex position \c x0.
 */
double
dxf_mesh_get_x0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->p0->x0);
}


/*!
 * \brief Set the X-value of the vertex position \c x0 of a DXF \c MESH
 * entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_x0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double x0
                /*!< the X-value of the vertex position \c x0 of a DXF
                 * \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                mesh->p0 = dxf_point_init (mesh->p0);
                if (mesh->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        mesh->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the Y-value of the vertex position \c y0 of a DXF \c MESH
 * entity.
 *
 * \return the Y-value of the vertex position \c y0.
 */
double
dxf_mesh_get_y0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->p0->y0);
}


/*!
 * \brief Set the Y-value of the vertex position \c y0 of a DXF \c MESH
 * entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_y0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double y0
                /*!< the Y-value of the vertex position \c y0 of a DXF
                 * \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                mesh->p0 = dxf_point_init (mesh->p0);
                if (mesh->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        mesh->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the Z-value of the vertex position \c z0 of a DXF \c MESH
 * entity.
 *
 * \return the Z-value of the vertex position \c z0.
 */
double
dxf_mesh_get_z0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->p0->z0);
}


/*!
 * \brief Set the Z-value of the vertex position \c z0 of a DXF \c MESH
 * entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_z0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double z0
                /*!< the Z-value of the vertex position \c z0 of a DXF
                 * \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                mesh->p0 = dxf_point_init (mesh->p0);
                if (mesh->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        mesh->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c version from a DXF \c MESH entity.
 *
 * \return \c version.
 */
int16_t
dxf_mesh_get_version
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->version < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->version);
}


/*!
 * \brief Set the \c version for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_version
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t version
                /*!< the \c version to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (version < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->version = version;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c blend_crease_property from a DXF \c MESH entity.
 *
 * \return \c blend_crease_property.
 */
int16_t
dxf_mesh_get_blend_crease_property
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->blend_crease_property < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->blend_crease_property > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->blend_crease_property);
}


/*!
 * \brief Set the \c blend_crease_property for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_blend_crease_property
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t blend_crease_property
                /*!< the \c blend_crease_property to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (blend_crease_property < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (blend_crease_property > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
        mesh->blend_crease_property = blend_crease_property;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to a linked list of \c face_list_item from a
 * DXF \c MESH entity.
 *
 * \return \c face_list_item.
 */
DxfInt32 *
dxf_mesh_get_face_list_item
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt32 *) mesh->face_list_item);
}


/*!
 * \brief Set the pointer to a linked list of \c face_list_item for a
 * DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_face_list_item
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        DxfInt32 *face_list_item
                /*!< the \c face_list_item to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->face_list_item = face_list_item;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c edge_vertex_index from a DXF \c MESH entity.
 *
 * \return \c edge_vertex_index.
 */
DxfInt32 *
dxf_mesh_get_edge_vertex_index
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->edge_vertex_index);
}


/*!
 * \brief Set the \c edge_vertex_index for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_edge_vertex_index
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        DxfInt32 *edge_vertex_index
                /*!< the \c edge_vertex_index to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->edge_vertex_index = (DxfInt32 *) edge_vertex_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c number_of_property_overridden_sub_entities from a
 * DXF \c MESH entity.
 *
 * \return \c number_of_property_overridden_sub_entities.
 */
int32_t
dxf_mesh_get_number_of_property_overridden_sub_entities
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->number_of_property_overridden_sub_entities);
}


/*!
 * \brief Set the \c number_of_property_overridden_sub_entities for a
 * DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_number_of_property_overridden_sub_entities
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t number_of_property_overridden_sub_entities
                /*!< the \c number_of_property_overridden_sub_entities
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->number_of_property_overridden_sub_entities = number_of_property_overridden_sub_entities;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c property_type from a DXF \c MESH entity.
 *
 * \return \c property_type.
 */
int32_t
dxf_mesh_get_property_type
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->property_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->property_type > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->property_type);
}


/*!
 * \brief Set the \c property_type for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_property_type
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t property_type
                /*!< the \c property_type to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (property_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (property_type > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
        mesh->property_type = property_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c subdivision_level from a DXF \c MESH entity.
 *
 * \return \c subdivision_level.
 */
int32_t
dxf_mesh_get_subdivision_level
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->subdivision_level);
}


/*!
 * \brief Set the \c subdivision_level for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_subdivision_level
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t subdivision_level
                /*!< the \c subdivision_level to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->subdivision_level = subdivision_level;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c sub_entity_marker from a DXF \c MESH entity.
 *
 * \return \c sub_entity_marker.
 */
int32_t
dxf_mesh_get_sub_entity_marker
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->sub_entity_marker);
}


/*!
 * \brief Set the \c sub_entity_marker for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_sub_entity_marker
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t sub_entity_marker
                /*!< the \c sub_entity_marker to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->sub_entity_marker = sub_entity_marker;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c vertex_count_level_0 from a DXF \c MESH entity.
 *
 * \return \c vertex_count_level_0.
 */
int32_t
dxf_mesh_get_vertex_count_level_0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->vertex_count_level_0);
}


/*!
 * \brief Set the \c vertex_count_level_0 for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_vertex_count_level_0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t vertex_count_level_0
                /*!< the \c vertex_count_level_0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->vertex_count_level_0 = vertex_count_level_0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c count_of_property_overridden from a DXF \c MESH
 * entity.
 *
 * \return \c count_of_property_overridden.
 */
int32_t
dxf_mesh_get_count_of_property_overridden
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->count_of_property_overridden);
}


/*!
 * \brief Set the \c count_of_property_overridden for a DXF \c MESH
 * entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_count_of_property_overridden
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t count_of_property_overridden
                /*!< the \c count_of_property_overridden to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->count_of_property_overridden = count_of_property_overridden;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c face_list_size_level_0 from a DXF \c MESH entity.
 *
 * \return \c face_list_size_level_0.
 */
int32_t
dxf_mesh_get_face_list_size_level_0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->face_list_size_level_0);
}


/*!
 * \brief Set the \c face_list_size_level_0 for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_face_list_size_level_0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t face_list_size_level_0
                /*!< the \c face_list_size_level_0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->face_list_size_level_0 = face_list_size_level_0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c edge_count_level_0 from a DXF \c MESH entity.
 *
 * \return \c edge_count_level_0.
 */
int32_t
dxf_mesh_get_edge_count_level_0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->edge_count_level_0);
}


/*!
 * \brief Set the \c edge_count_level_0 for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_edge_count_level_0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t edge_count_level_0
                /*!< the \c edge_count_level_0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->edge_count_level_0 = edge_count_level_0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c edge_crease_count_level_0 from a DXF \c MESH entity.
 *
 * \return \c edge_crease_count_level_0.
 */
int32_t
dxf_mesh_get_edge_crease_count_level_0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->edge_crease_count_level_0);
}


/*!
 * \brief Set the \c edge_crease_count_level_0 for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_edge_crease_count_level_0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t edge_crease_count_level_0
                /*!< the \c edge_crease_count_level_0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->edge_crease_count_level_0 = edge_crease_count_level_0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c edge_create_value of a DXF \c MESH entity.
 *
 * \return \c edge_create_value.
 */
DxfDouble *
dxf_mesh_get_edge_create_value
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) mesh->edge_create_value);
}


/*!
 * \brief Set the \c edge_create_value of a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_edge_create_value
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        DxfDouble *edge_create_value
                /*!< the \c edge_create_value of a DXF \c MESH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->edge_create_value = edge_create_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the next \c MESH entity from a DXF
 * \c MESH entity.
 *
 * \return pointer to the next \c MESH entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMesh *
dxf_mesh_get_next
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMesh *) mesh->next);
}


/*!
 * \brief Set the pointer to the next \c MESH for a DXF \c MESH
 * entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_next
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        DxfMesh *next
                /*!< a pointer to the next \c MESH for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->next = (struct DxfMesh *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the last \c MESH entity from a linked list
 * of DXF \c MESH entities.
 *
 * \return pointer to the last \c MESH entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMesh *
dxf_mesh_get_last
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMesh *) mesh);
        }
        DxfMesh *iter = (DxfMesh *) mesh->next;
        while (iter->next != NULL)
        {
                iter = (DxfMesh *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMesh *) iter);
}


/* EOF*/
