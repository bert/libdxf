/*!
 * \file polyline.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF polyline entity (\c PLINE).
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


#ifndef LIBDXF_SRC_POLYLINE_H
#define LIBDXF_SRC_POLYLINE_H


#include "global.h"
#include "binary_graphics_data.h"
#include "vertex.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of a DXF polyline entity.
 *
 * A polyface mesh is represented in \c DXF as a variant of a Polyline
 * entity.\n
 * The Polyline header is identified as introducing a polyface mesh by the
 * presence of the 64 bit in the Polyline flags (70) group.\n
 * The 71 group specifies the number of vertices in the mesh, and the 72
 * group, the number of faces.\n
 * While these counts are correct for all meshes created with the \c PFACE
 * command, applications are not required to place correct values in these
 * fields, and AutoCAD actually never relies upon their accuracy.\n
 * \n
 * Following the Polyline header is a sequence of Vertex entities that
 * specify the vertex coordinates and faces that compose the mesh.\n
 * Vertices such as these are described in the following subsection on
 * Vertex.\n
 * \n
 * Applications might want to represent polygons with an arbitrarily large
 * number of sides in polyface meshes.\n
 * However, the AutoCAD entity structure imposes a limit on the number of
 * vertices that a given face entity can specify.\n
 * You can represent more complex polygons by decomposing them into
 * triangular wedges.\n
 * Their edges should be made invisible to prevent visible artifacts of this
 * subdivision from being drawn.\n
 * The \c PFACE command performs this subdivision automatically, but when
 * applications generate polyface meshes directly, the applications must do
 * this themselves.\n
 * \n
 * The number of vertices per face is the key parameter in this subdivision
 * process.\n
 * The \c PFACEVMAX system variable provides an application with the number
 * of vertices per face entity.\n
 * This value is read-only, and is set to 4.\n
 * \n
 * Polyface meshes created with the \c PFACE command are always generated
 * with all the vertex coordinate entities first, followed by the face
 * definition entities.\n
 * The code within AutoCAD that processes polyface meshes does not, at
 * present, require this ordering; it works even with interleaved vertex
 * coordinates and face definitions as long as no face specifies a vertex
 * with an index that appears after it in the database.\n
 * Programs that read polyface meshes from \c DXF would be wise to be as
 * tolerant of odd vertex and face ordering as AutoCAD is.\n
 */
typedef struct
dxf_polyline_struct
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
                /*!< Thickness of the arc in the local Z-direction.\n
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
        /* Specific members for a DXF polyline. */
        DxfPoint *p0;
                /*!< Insertion point for the polyline.\n
                 * The \c z0 value of \c p0 is the default elevation for
                 * vertices.\n
                 * Group codes = 10, 20 and 30.*/
        double start_width;
                /*!< Optional, defaults to 0.0\n
                 * The default widths apply to any vertex that doesn't supply
                 * widths.\n
                 * Group code = 40. */
        double end_width;
                /*!< Optional, defaults to 0.0\n
                 * The default widths apply to any vertex that doesn't supply
                 * widths.\n
                 * Group code = 41. */
        int vertices_follow;
                /*!< Always 1\n
                 * The "vertices follow" flag is always 1, indicating that a
                 * series of Vertex entities is expected to follow the
                 * \c Polyline, terminated by a "sequence end" entity.\n
                 * Group code = 66.\n
                 * \deprecated As of version 2002. */
        int flag;
                /*!< Optional, defaults to 0\n
                 * bit coded:\n
                 * 1 = This is a closed Polyline (or a polygon mesh closed in
                 * the M direction)\n
                 * 2 = Curve-fit vertices have been added\n
                 * 4 = Spline-fit vertices have been added\n
                 * 8 = This is a 3D Polyline\n
                 * 16 = This is a 3D polygon mesh\n
                 * 32 = The polygon mesh is closed in the N direction\n
                 * 64 = This Polyline is a polyface mesh\n
                 * 128 = The linetype pattern is generated continuously
                 *       around the vertices of this Polyline\n.
                 * Group code = 70. */
        int polygon_mesh_M_vertex_count;
                /*!< Optional, defaults to 0.\n
                 * Group code = 71. */
        int polygon_mesh_N_vertex_count;
                /*!< Optional, defaults to 0.\n
                 * Group code = 72. */
        int smooth_M_surface_density;
                /*!< Optional, defaults to 0.\n
                 * Group code = 73. */
        int smooth_N_surface_density;
                /*!< Optional, defaults to 0.\n
                 * Group code = 74. */
        int surface_type;
                /*!< Optional, defaults to 0\n
                 * bit coded:\n
                 * 0 = no smooth surface fitted\n
                 * 5 = quadratic B-spline surface\n
                 * 6 = cubic B-spline surface\n
                 * 8 = Bezier surface.\n
                 * Group code = 75. */
        double extr_x0;
                /*!< Extrusion direction (optional; default = 0, 0, 1)\n
                 * DXF: X value;\n
                 * APP: 3D vector\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< DXF: Y value of extrusion direction (optional).\n
                 * Group code = 220. */
        double extr_z0;
                /*!< DXF: Z value of extrusion direction (optional).\n
                 * Group code = 230. */
        DxfVertex *vertices;
                /*!< Pointer to the first DxfVertex of the polyline.\n
                 * \c NULL in the last DxfVertex.\n
                 * \note Not all members of the DxfVertex struct are
                 * used for polylines. */
        struct DxfPolyline *next;
                /*!< pointer to the next DxfPolyline.\n
                 * \c NULL in the last DxfPolyline. */
} DxfPolyline;


DxfPolyline *dxf_polyline_new ();
DxfPolyline *dxf_polyline_init (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_read (DxfFile *fp, DxfPolyline *polyline);
int dxf_polyline_write (DxfFile *fp, DxfPolyline *polyline);
int dxf_polyline_free (DxfPolyline *polyline);
void dxf_polyline_free_list (DxfPolyline *polylines);
int dxf_polyline_get_id_code (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_id_code (DxfPolyline *polyline, int id_code);
char *dxf_polyline_get_linetype (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_linetype (DxfPolyline *polyline, char *linetype);
char *dxf_polyline_get_layer (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_layer (DxfPolyline *polyline, char *layer);
double dxf_polyline_get_elevation (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_elevation (DxfPolyline *polyline, double elevation);
double dxf_polyline_get_thickness (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_thickness (DxfPolyline *polyline, double thickness);
double dxf_polyline_get_linetype_scale (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_linetype_scale (DxfPolyline *polyline, double linetype_scale);
int16_t dxf_polyline_get_visibility (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_visibility (DxfPolyline *polyline, int16_t visibility);
int dxf_polyline_get_color (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_color (DxfPolyline *polyline, int color);
int dxf_polyline_get_paperspace (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_paperspace (DxfPolyline *polyline, int paperspace);
int dxf_polyline_get_graphics_data_size (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_graphics_data_size (DxfPolyline *polyline, int graphics_data_size);
int16_t dxf_polyline_get_shadow_mode (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_shadow_mode (DxfPolyline *polyline, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_polyline_get_binary_graphics_data (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_binary_graphics_data (DxfPolyline *polyline, DxfBinaryGraphicsData *data);
char *dxf_polyline_get_dictionary_owner_soft (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_dictionary_owner_soft (DxfPolyline *polyline, char *dictionary_owner_soft);
char *dxf_polyline_get_material (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_material (DxfPolyline *polyline, char *material);
char *dxf_polyline_get_dictionary_owner_hard (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_dictionary_owner_hard (DxfPolyline *polyline, char *dictionary_owner_hard);
int16_t dxf_polyline_get_lineweight (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_lineweight (DxfPolyline *polyline, int16_t lineweight);
char *dxf_polyline_get_plot_style_name (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_plot_style_name (DxfPolyline *polyline, char *plot_style_name);
long dxf_polyline_get_color_value (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_color_value (DxfPolyline *polyline, long color_value);
char *dxf_polyline_get_color_name (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_color_name (DxfPolyline *polyline, char *color_name);
long dxf_polyline_get_transparency (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_transparency (DxfPolyline *polyline, long transparency);
DxfPoint *dxf_polyline_get_p0 (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_p0 (DxfPolyline *polyline, DxfPoint *p0);
double dxf_polyline_get_x0 (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_x0 (DxfPolyline *polyline, double x0);
double dxf_polyline_get_y0 (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_y0 (DxfPolyline *polyline, double y0);
double dxf_polyline_get_z0 (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_z0 (DxfPolyline *polyline, double z0);
double dxf_polyline_get_start_width (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_start_width (DxfPolyline *polyline, double start_width);
double dxf_polyline_get_end_width (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_end_width (DxfPolyline *polyline, double end_width);
int dxf_polyline_get_vertices_follow (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_vertices_follow (DxfPolyline *polyline, int vertices_follow);
int dxf_polyline_get_flag (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_flag (DxfPolyline *polyline, int flag);
int dxf_polyline_get_polygon_mesh_M_vertex_count (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_polygon_mesh_M_vertex_count (DxfPolyline *polyline, int polygon_mesh_M_vertex_count);
int dxf_polyline_get_polygon_mesh_N_vertex_count (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_polygon_mesh_N_vertex_count (DxfPolyline *polyline, int polygon_mesh_N_vertex_count);
int dxf_polyline_get_smooth_M_surface_density (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_smooth_M_surface_density (DxfPolyline *polyline, int smooth_M_surface_density);
int dxf_polyline_get_smooth_N_surface_density (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_smooth_N_surface_density (DxfPolyline *polyline, int smooth_N_surface_density);
int dxf_polyline_get_surface_type (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_surface_type (DxfPolyline *polyline, int surface_type);
double dxf_polyline_get_extr_x0 (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_extr_x0 (DxfPolyline *polyline, double extr_x0);
double dxf_polyline_get_extr_y0 (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_extr_y0 (DxfPolyline *polyline, double extr_y0);
double dxf_polyline_get_extr_z0 (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_extr_z0 (DxfPolyline *polyline, double extr_z0);
DxfVertex *dxf_polyline_get_vertices (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_vertices (DxfPolyline *polyline, DxfVertex *vertices);
DxfPolyline *dxf_polyline_get_next (DxfPolyline *polyline);
DxfPolyline *dxf_polyline_set_next (DxfPolyline *polyline, DxfPolyline *next);
DxfPolyline *dxf_polyline_get_last (DxfPolyline *polyline);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_POLYLINE_H */


/* EOF */
