/*!
 * \file mesh.h
 *
 * \author Copyright (C) 2018, 2020
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF mesh entity (\c MESH).
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


#ifndef LIBDXF_SRC_MESH_H
#define LIBDXF_SRC_MESH_H


#include "global.h"
#include "binary_data.h"
#include "point.h"
#include "util.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD mesh entity (\c MESH).
 */
typedef struct
dxf_mesh_struct
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double elevation;
                /*!< Elevation of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38.\n
                 * \deprecated As of version R11. */
        double thickness;
                /*!< Thickness of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48.\n
                 * \since Introduced in version R13. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60.\n
                 * \since Introduced in version R13. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67.\n
                 * \since Introduced in version R13. */
        int graphics_data_size;
                /*!< Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).\n
                 * Group code = 92.\n
                 * \since Introduced in version R2000.\n
                 * \warning On some 64 bit workstations output is
                 * generated with group code "160", thus omitting group
                 * code "92". */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284.\n
                 * \since Introduced in version R2009. */
        DxfBinaryData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330.\n
                 * \since Introduced in version R14. */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle  to owner BLOCK_RECORD object.\n
                 * Group code = 330.\n
                 * \since Introduced in version R2000. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347.\n
                 * \since Introduced in version R2008. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360.\n
                 * \since Introduced in version R14. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370.\n
                 * \since Introduced in version R2002. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390.\n
                 * \since Introduced in version R2009. */
        long color_value;
                /*!< A 24-bit color value that should be dealt with in
                 * terms of bytes with values of 0 to 255.\n
                 * The lowest byte is the blue value, the middle byte is
                 * the green value, and the third byte is the red value.\n
                 * The top byte is always 0.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 420.\n
                 * \since Introduced in version R2004. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430.\n
                 * \since Introduced in version R2004. */
        long transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
        /* Specific members for a DXF mesh. */
        DxfPoint *p0;
                /*!< Vertex position.\n
                 * Group codes = 10, 20 and 30.*/
        int16_t version;
                /*!< Version number.\n
                 * Group code = 71. */
        int16_t blend_crease_property;
                /*!< "Blend Crease" property:
                 * <ol>
                 *   <li value=0>Turn off.</li>
                 *   <li value=1>Turn on.</li>
                 * </ol>
                 * Group code = 72. */
        DxfInt32 *face_list_item;
                /*!< Face list item.\n
                 * Group code = 90. */
        DxfInt32 *edge_vertex_index;
                /*!< Vertex index of each edge (multiple entries ?).\n
                 * Group code = 90.
                 * \todo Solve multiple group code issue. */
        int32_t number_of_property_overridden_sub_entities;
                /*!< Count of sub-entity which property has been
                 * overridden.\n
                 * Group code = 90.
                 * \todo Solve multiple group code issue. */
        int32_t property_type;
                /*!< Property type:
                 * <ol>
                 *   <li value=0>Color.</li>
                 *   <li value=1>Material.</li>
                 *   <li value=2>Transparency.</li>
                 *   <li value=3>Material mapper.</li>
                 * </ol>
                 * Group code = 90.
                 * \todo Solve multiple group code issue. */
        int32_t subdivision_level;
                /*!< Number of subdivision level.\n
                 * Group code = 91. */
        int32_t sub_entity_marker;
                /*!< Sub-entity marker.\n
                 * Group code = 91.
                 * \todo Solve multiple group code issue. */
        int32_t vertex_count_level_0;
                /*!< Vertex count of level 0.\n
                 * Group code = 92. */
        int32_t count_of_property_overridden;
                /*!< Count of property was overridden.\n
                 * Group code = 92.
                 * \todo Solve multiple group code issue. */
        int32_t face_list_size_level_0;
                /*!< Size of face list of level 0.\n
                 * Group code = 93. */
        int32_t edge_count_level_0;
                /*!< Edge count of level 0.\n
                 * Group code = 94. */
        int32_t edge_crease_count_level_0;
                /*!< Edge crease count of level 0.\n
                 * Group code = 95. */
        DxfDouble *edge_create_value;
                /*!< Edge create value.\n
                 * Group code = 140. */
        struct DxfMesh *next;
                /*!< Pointer to the next DxfMesh.\n
                 * \c NULL in the last DxfMesh. */
} DxfMesh;


DxfMesh *dxf_mesh_new ();
DxfMesh *dxf_mesh_init (DxfMesh *mesh);
DxfMesh *dxf_mesh_read (DxfFile *fp, DxfMesh *mesh);
int dxf_mesh_write (DxfFile *fp, DxfMesh *mesh);
int dxf_mesh_free (DxfMesh *mesh);
void dxf_mesh_free_list (DxfMesh *meshes);
int dxf_mesh_get_id_code (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_id_code (DxfMesh *mesh, int id_code);
char *dxf_mesh_get_linetype (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_linetype (DxfMesh *mesh, char *linetype);
char *dxf_mesh_get_layer (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_layer (DxfMesh *mesh, char *layer);
double dxf_mesh_get_elevation (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_elevation (DxfMesh *mesh, double elevation);
double dxf_mesh_get_thickness (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_thickness (DxfMesh *mesh, double thickness);
double dxf_mesh_get_linetype_scale (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_linetype_scale (DxfMesh *mesh, double linetype_scale);
int16_t dxf_mesh_get_visibility (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_visibility (DxfMesh *mesh, int16_t visibility);
int dxf_mesh_get_color (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_color (DxfMesh *mesh, int color);
int dxf_mesh_get_paperspace (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_paperspace (DxfMesh *mesh, int paperspace);
int dxf_mesh_get_graphics_data_size (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_graphics_data_size (DxfMesh *mesh, int graphics_data_size);
int16_t dxf_mesh_get_shadow_mode (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_shadow_mode (DxfMesh *mesh, int16_t shadow_mode);
DxfBinaryData *dxf_mesh_get_binary_graphics_data (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_binary_graphics_data (DxfMesh *mesh, DxfBinaryData *data);
char *dxf_mesh_get_dictionary_owner_soft (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_dictionary_owner_soft (DxfMesh *mesh, char *dictionary_owner_soft);
char *dxf_mesh_get_object_owner_soft (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_object_owner_soft (DxfMesh *mesh, char *object_owner_soft);
char *dxf_mesh_get_material (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_material (DxfMesh *mesh, char *material);
char *dxf_mesh_get_dictionary_owner_hard (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_dictionary_owner_hard (DxfMesh *mesh, char *dictionary_owner_hard);
int16_t dxf_mesh_get_lineweight (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_lineweight (DxfMesh *mesh, int16_t lineweight);
char *dxf_mesh_get_plot_style_name (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_plot_style_name (DxfMesh *mesh, char *plot_style_name);
long dxf_mesh_get_color_value (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_color_value (DxfMesh *mesh, long color_value);
char *dxf_mesh_get_color_name (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_color_name (DxfMesh *mesh, char *color_name);
long dxf_mesh_get_transparency (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_transparency (DxfMesh *mesh, long transparency);
DxfPoint *dxf_mesh_get_p0 (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_p0 (DxfMesh *mesh, DxfPoint *p0);
double dxf_mesh_get_x0 (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_x0 (DxfMesh *mesh, double x0);
double dxf_mesh_get_y0 (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_y0 (DxfMesh *mesh, double y0);
double dxf_mesh_get_z0 (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_z0 (DxfMesh *mesh, double z0);
int16_t dxf_mesh_get_version (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_version (DxfMesh *mesh, int16_t version);
int16_t dxf_mesh_get_blend_crease_property (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_blend_crease_property (DxfMesh *mesh, int16_t blend_crease_property);
DxfInt32 *dxf_mesh_get_face_list_item (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_face_list_item (DxfMesh *mesh, DxfInt32 *face_list_item);
DxfInt32 *dxf_mesh_get_edge_vertex_index (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_edge_vertex_index (DxfMesh *mesh, DxfInt32 *edge_vertex_index);
int32_t dxf_mesh_get_number_of_property_overridden_sub_entities (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_number_of_property_overridden_sub_entities (DxfMesh *mesh, int32_t number_of_property_overridden_sub_entities);
int32_t dxf_mesh_get_property_type (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_property_type (DxfMesh *mesh, int32_t property_type);
int32_t dxf_mesh_get_subdivision_level (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_subdivision_level (DxfMesh *mesh, int32_t subdivision_level);
int32_t dxf_mesh_get_sub_entity_marker (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_sub_entity_marker (DxfMesh *mesh, int32_t sub_entity_marker);
int32_t dxf_mesh_get_vertex_count_level_0 (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_vertex_count_level_0 (DxfMesh *mesh, int32_t vertex_count_level_0);
int32_t dxf_mesh_get_count_of_property_overridden (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_count_of_property_overridden (DxfMesh *mesh, int32_t count_of_property_overridden);
int32_t dxf_mesh_get_face_list_size_level_0 (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_face_list_size_level_0 (DxfMesh *mesh, int32_t face_list_size_level_0);
int32_t dxf_mesh_get_edge_count_level_0 (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_edge_count_level_0 (DxfMesh *mesh, int32_t edge_count_level_0);
int32_t dxf_mesh_get_edge_crease_count_level_0 (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_edge_crease_count_level_0 (DxfMesh *mesh, int32_t edge_crease_count_level_0);
DxfDouble *dxf_mesh_get_edge_create_value (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_edge_create_value (DxfMesh *mesh, DxfDouble *edge_create_value);
DxfMesh *dxf_mesh_get_next (DxfMesh *mesh);
DxfMesh *dxf_mesh_set_next (DxfMesh *mesh, DxfMesh *next);
DxfMesh *dxf_mesh_get_last (DxfMesh *mesh);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_MESH_H */


/* EOF */
