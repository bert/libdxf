/*!
 * \file vertex.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017,
 * 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF vertex entity (\c VERTEX).
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


#ifndef LIBDXF_SRC_VERTEX_H
#define LIBDXF_SRC_VERTEX_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD vertex entity.
 *
 * Every \c VERTEX that is part of a polyface mesh has the 128 bit set in its
 * Vertex flags (70) group.\n
 * If the entity specifies the coordinates of a \c VERTEX of the mesh, the
 * 64 bit is set as well and the 10, 20, and 30 groups give the vertex
 * coordinates.\n
 * The \c VERTEX indexes are determined by the order in which the \c VERTEX
 * entities appear within the \c POLYLINE, with the first numbered 1.\n
 * \n
 * If the \c VERTEX defines a face of the mesh, its \c VERTEX flags (70)
 * group has the 128 bit set but not the 64 bit.\n
 * The 10, 20, and 30 (location) groups of the \c FACE entity are irrelevant
 * and are always written as zero in a DXF file.\n
 * The \c VERTEX indexes that define the mesh are given by 71, 72, 73, and 74
 * groups, the values of which are integers specifying one of the previously
 * defined vertices by index.\n
 * If the index is negative, the edge that begins with that \c VERTEX is
 * invisible.\n
 * The first zero \c VERTEX marks the end of the vertices of the face.\n
 * Since the 71 through 74 groups are optional fields with default values of
 * zero, they are present in DXF only if nonzero.
 */
typedef struct
dxf_vertex_struct
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
        DxfBinaryGraphicsData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330.\n
                 * \since Introduced in version R14. */
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
        /* Specific members for a DXF vertex. */
        DxfPoint *p0;
                /*!< Location point.\n
                 * Group codes = 10, 20 and 30.*/
        double start_width;
                /*!< Starting width (optional, defaults to 0.0).\n
                 * Group code = 40. */
        double end_width;
                /*!< Ending width (optional, defaults to 0.0).\n
                 * Group code = 41. */
        double bulge;
                /*!< Bulge (optional, defaults to 0.0).\n
                 * The bulge is the tangent of 1/4 the included angle for an
                 * arc segment, made negative if the arc goes clockwise from
                 * the start point to the endpoint; a bulge of 0 indicates a
                 * straight segment, and a bulge of 1 is a semicircle.\n
                 * Group code = 42. */
        double curve_fit_tangent_direction;
                /*!< Curve fit tangent direction.\n
                 * Group code = 50. */
        int flag;
                /*!< Flag (optional, defaults to 0)\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> Extra vertex created by curve-fitting.</li>
                 * <li value = "2"> Curve-fit tangent defined for this
                 *   vertex.\n
                 *   A curve-fit tangent direction of 0 may be omitted
                 *   from the DXF output, but is significant if this
                 *   bit is set.</li>
                 * <li value = "4"> Unused (never set in DXF files).</li>
                 * <li value = "8"> Spline vertex created by spline-fitting.</li>
                 * <li value = "16"> Spline frame control point.</li>
                 * <li value = "32"> 3D Polyline vertex.</li>
                 * <li value = "64"> 3D polygon mesh vertex.</li>
                 * <li value = "128"> Polyface mesh vertex.</li>
                 * </ol>
                 * Group code = 70. */
        int polyface_mesh_vertex_index_1;
                /*!< Polyface mesh vertex index.\n
                 * Optional.\n
                 * Present only if nonzero.\n
                 * Group code = 71. */
        int polyface_mesh_vertex_index_2;
                /*!< Polyface mesh vertex index.\n
                 * Optional.\n
                 * Present only if nonzero.\n
                 * Group code = 72. */
        int polyface_mesh_vertex_index_3;
                /*!< Polyface mesh vertex index.\n
                 * Optional.\n
                 * Present only if nonzero.\n
                 * Group code = 73. */
        int polyface_mesh_vertex_index_4;
                /*!< Polyface mesh vertex index.\n
                 * Optional.\n
                 * Present only if nonzero.\n
                 * Group code = 74. */
        int vertex_identifier;
                /*!< Vertex identifier.\n
                 * Group code = 91. */

        struct DxfVertex *next;
                /*!< Pointer to the next DxfVertex.\n
                 * \c NULL in the last DxfVertex. */
} DxfVertex;


DxfVertex *dxf_vertex_new ();
DxfVertex *dxf_vertex_init (DxfVertex *vertex);
DxfVertex *dxf_vertex_read (DxfFile *fp, DxfVertex *vertex);
int dxf_vertex_write (DxfFile *fp, DxfVertex *vertex);
int dxf_vertex_free (DxfVertex *vertex);
void dxf_vertex_free_list (DxfVertex *vertices);
int dxf_vertex_get_id_code (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_id_code (DxfVertex *vertex, int id_code);
char *dxf_vertex_get_linetype (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_linetype (DxfVertex *vertex, char *linetype);
char *dxf_vertex_get_layer (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_layer (DxfVertex *vertex, char *layer);
double dxf_vertex_get_elevation (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_elevation (DxfVertex *vertex, double elevation);
double dxf_vertex_get_thickness (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_thickness (DxfVertex *vertex, double thickness);
double dxf_vertex_get_linetype_scale (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_linetype_scale (DxfVertex *vertex, double linetype_scale);
int16_t dxf_vertex_get_visibility (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_visibility (DxfVertex *vertex, int16_t visibility);
int dxf_vertex_get_color (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_color (DxfVertex *vertex, int color);
int dxf_vertex_get_paperspace (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_paperspace (DxfVertex *vertex, int paperspace);
int dxf_vertex_get_graphics_data_size (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_graphics_data_size (DxfVertex *vertex, int graphics_data_size);
int16_t dxf_vertex_get_shadow_mode (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_shadow_mode (DxfVertex *vertex, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_vertex_get_binary_graphics_data (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_binary_graphics_data (DxfVertex *vertex, DxfBinaryGraphicsData *data);
char *dxf_vertex_get_dictionary_owner_soft (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_dictionary_owner_soft (DxfVertex *vertex, char *dictionary_owner_soft);
char *dxf_vertex_get_material (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_material (DxfVertex *vertex, char *material);
char *dxf_vertex_get_dictionary_owner_hard (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_dictionary_owner_hard (DxfVertex *vertex, char *dictionary_owner_hard);
int16_t dxf_vertex_get_lineweight (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_lineweight (DxfVertex *vertex, int16_t lineweight);
char *dxf_vertex_get_plot_style_name (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_plot_style_name (DxfVertex *vertex, char *plot_style_name);
long dxf_vertex_get_color_value (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_color_value (DxfVertex *vertex, long color_value);
char *dxf_vertex_get_color_name (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_color_name (DxfVertex *vertex, char *color_name);
long dxf_vertex_get_transparency (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_transparency (DxfVertex *vertex, long transparency);
DxfPoint *dxf_vertex_get_p0 (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_p0 (DxfVertex *vertex, DxfPoint *p0);
double dxf_vertex_get_x0 (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_x0 (DxfVertex *vertex, double x0);
double dxf_vertex_get_y0 (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_y0 (DxfVertex *vertex, double y0);
double dxf_vertex_get_z0 (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_z0 (DxfVertex *vertex, double z0);
double dxf_vertex_get_start_width (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_start_width (DxfVertex *vertex, double start_width);
double dxf_vertex_get_end_width (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_end_width (DxfVertex *vertex, double end_width);
double dxf_vertex_get_bulge (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_bulge (DxfVertex *vertex, double bulge);
double dxf_vertex_get_curve_fit_tangent_direction (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_curve_fit_tangent_direction (DxfVertex *vertex, double curve_fit_tangent_direction);
int dxf_vertex_get_flag (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_flag (DxfVertex *vertex, int flag);
int dxf_vertex_get_polyface_mesh_vertex_index_1 (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_polyface_mesh_vertex_index_1 (DxfVertex *vertex, int polyface_mesh_vertex_index_1);
int dxf_vertex_get_polyface_mesh_vertex_index_2 (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_polyface_mesh_vertex_index_2 (DxfVertex *vertex, int polyface_mesh_vertex_index_2);
int dxf_vertex_get_polyface_mesh_vertex_index_3 (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_polyface_mesh_vertex_index_3 (DxfVertex *vertex, int polyface_mesh_vertex_index_3);
int dxf_vertex_get_polyface_mesh_vertex_index_4 (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_polyface_mesh_vertex_index_4 (DxfVertex *vertex, int polyface_mesh_vertex_index_4);
DxfVertex *dxf_vertex_get_next (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_next (DxfVertex *vertex, DxfVertex *next);
DxfVertex *dxf_vertex_get_last (DxfVertex *vertex);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_VERTEX_H */


/* EOF */
