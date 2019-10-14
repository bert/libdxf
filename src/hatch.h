/*!
 * \file hatch.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015, 2016, 2017, 2018, 2019
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Definition of a DXF hatch entity (\c HATCH).
 *
 * \warning The hatch entity requires AutoCAD version R14 or higher.\n
 *
 * \htmlinclude "hatch.html"
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


#ifndef LIBDXF_SRC_HATCH_H
#define LIBDXF_SRC_HATCH_H


#include <math.h>

#include "global.h"
#include "point.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


#define DXF_MAX_HATCH_PATTERN_DEF_LINE_DASH_ITEMS 16
#define DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS 64


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge arc.
 */
typedef struct
dxf_hatch_boundary_path_edge_arc_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file.\n
                 * Group code = 5. */
        double x0;
                /*!< X-value of the center point coordinate.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the center point coordinate.\n
                 * Group code = 20. */
        double radius;
                /*!< group code = 40. */
        double start_angle;
                /*!< group code = 50. */
        double end_angle;
                /*!< group code = 51. */
        int16_t is_ccw;
                /*!< Arc is counterclockwise flag.\n
                 * Group code = 73. */
        struct DxfHatchBoundaryPathEdgeArc *next;
                /*!< Pointer to the next DxfHatchBoundaryPathEdgeArc.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeArc. */
} DxfHatchBoundaryPathEdgeArc;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge ellipse.
 */
typedef struct
dxf_hatch_boundary_path_edge_ellipse_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file.\n
                 * Group code = 5. */
        double x0;
                /*!< X-value of center point coordinate.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of center point coordinate.\n
                 * Group code = 20. */
        double x1;
                /*!< X-value of end point coordinate of major axis
                 * (relative to center point.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of end point coordinate of major axis
                 * (relative to center point.\n
                 * Group code = 21. */
        double ratio;
                /*!< Ratio of minor axis to major axis.\n
                 * Group code = 40. */
        double start_angle;
                /*!< Group code = 50. */
        double end_angle;
                /*!< Group code = 51. */
        int16_t is_ccw;
                /*!< Ellipse is counterclockwise flag.\n
                 * Group code = 73. */
        struct DxfHatchBoundaryPathEdgeEllipse *next;
                /*!< Pointer to the next DxfHatchBoundaryPathEdgeEllipse.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeEllipse. */
} DxfHatchBoundaryPathEdgeEllipse;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge line.
 */
typedef struct
dxf_hatch_boundary_path_edge_line_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file.\n
                 * Group code = 5. */
        double x0;
                /*!< X-value of the coordinate of the start point.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the coordinate of the start point.\n
                 * Group code = 20. */
        double x1;
                /*!< X-value of the coordinate of the end point.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of the coordinate of the end point.\n
                 * Group code = 21. */
        struct DxfHatchBoundaryPathEdgeLine *next;
                /*!< Pointer to the next DxfHatchBoundaryPathEdgeLine.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeLine. */
} DxfHatchBoundaryPathEdgeLine;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge spline
 * control point.
 */
typedef struct
dxf_hatch_boundary_path_edge_spline_cp_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file.\n
                 * Group code = 5. */
        double x0;
                /*!< X value of the coordinate of the control point.\n
                 * Group code = 10. */
        double y0;
                /*!< Y value of the coordinate of the control point.\n
                 * Group code = 20. */
        double weight;
                /*!< Optional, defaults to 1.0.\n
                 * Group code = 42. */
        struct DxfHatchBoundaryPathEdgeSplineCp *next;
                /*!< Pointer to the next DxfHatchBoundaryPathEdgeSplineCp.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeSplineCp. */
} DxfHatchBoundaryPathEdgeSplineCp;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge spline.
 */
typedef struct
dxf_hatch_boundary_path_edge_spline_struct
{
        int id_code;
                /*!< group code = 5. */
        int32_t degree;
                /*!< group code = 94. */
        int16_t rational;
                /*!< group code = 73. */
        int16_t periodic;
                /*!< group code = 74. */
        int32_t number_of_knots;
                /*!< Number of knots.\n
                 * Group code = 95. */
        double knots[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS];
                /*!< Knot values control the shape of the curve as it
                 * passes through the control points.\n
                 * Group code = 40. */
        int32_t number_of_control_points;
                /*!< Number of control points.\n
                 * Group code = 96. */
        struct DxfHatchBoundaryPathEdgeSplineCp *control_points;
                /*!< Pointer to the first DxfHatchBoundaryPathEdgeSplineCp.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeSplineCp
                 * in the DxfHatchBoundaryPathEdgeSpline. */
        struct DxfHatchBoundaryPathEdgeSpline *next;
                /*!< Pointer to the next DxfHatchBoundaryPathEdgeSpline.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeSpline. */
} DxfHatchBoundaryPathEdgeSpline;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge
 * (composite of arcs, ellipses, lines or splines).
 */
typedef struct
dxf_hatch_boundary_path_edge_struct
{
        int id_code;
                /*!< Treat the boundary path edge as if it were a single
                 * (composite) entity.\n
                 * Group code = 5. */
        struct DxfHatchBoundaryPathEdgeArc *arcs;
                /*!< Pointer to the first DxfHatchBoundaryPathEdgeArc.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeArc in
                 * the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeEllipse *ellipses;
                /*!< Pointer to the first DxfHatchBoundaryPathEdgeEllipse.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeEllipse
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeLine * lines;
                /*!< Pointer to the first DxfHatchBoundaryPathEdgeLine.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeLine
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeSpline *splines;
                /*!< Pointer to the first DxfHatchBoundaryPathEdgeSpline.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeSpline
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdge *next;
                /*!< Pointer to the next DxfHatchBoundaryPathEdge.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdge. */
} DxfHatchBoundaryPathEdge;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path polyline
 * vertex.
 */
typedef struct
dxf_hatch_boundary_path_polyline_vertex_struct
{
        int id_code;
                /*!< Group code = 5.*/
        double x0;
                /*!< Group code = 10. */
        double y0;
                /*!< Group code = 20. */
        double bulge;
                /*!< Optional, default = 0.\n
                 * Group code = 42. */
        int16_t has_bulge;
                /*!< The segment formed by previous vertex and current
                 * vertex has a bulge is set.\n
                 * The first vertex of a polyline has no bulge by
                 * definition.\n
                 * Group code = 72. */
        struct DxfHatchBoundaryPathPolylineVertex *next;
                /*!< Pointer to the next DxfHatchBoundaryPathPolylineVertex.\n
                 * \c NULL if the last DxfHatchBoundaryPathPolylineVertex. */
} DxfHatchBoundaryPathPolylineVertex;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path polyline.
 */
typedef struct
dxf_hatch_boundary_path_polyline_struct
{
        int id_code;
                /*!< Group code = 5. */
        int16_t is_closed;
                /*!< Group code = 73. */
        int32_t number_of_vertices;
                /*!< Number of polyline vertices in
                 * DxfHatchBoundaryPathPolyline.\n
                 * Group code = 93. */
        struct DxfHatchBoundaryPathPolylineVertex *vertices;
                /*!< Pointer to the first
                 * DxfHatchBoundaryPathPolylineVertex.\n
                 * \c NULL if there is no
                 * DxfHatchBoundaryPathPolylineVertex in the
                 * DxfHatchBoundaryPathPolyline. */
        struct DxfHatchBoundaryPathPolyline *next;
                /*!< Pointer to the next DxfHatchBoundaryPathPolyline.\n
                 * \c NULL if the last DxfHatchBoundaryPathPolyline. */
} DxfHatchBoundaryPathPolyline;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path (or loop)
 * (composite of a closed series of edges, and/or a polyline).
 */
typedef struct
dxf_hatch_boundary_path_struct
{
        int id_code;
                /*!< Treat the boundary path as if it were a single
                 * (composite) entity.\n
                 * Group code = 5. */
        struct DxfHatchBoundaryPathEdge *edges;
                /*!< Pointer to the first DxfHatchBoundaryPathEdge.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdge in
                 * the DxfHatchBoundaryPath. */
        struct DxfHatchBoundaryPathPolyline *polylines;
                /*!< Pointer to the first DxfHatchBoundaryPathPolyline.\n
                 * \c NULL if there is no DxfHatchBoundaryPathPolyline
                 * in the DxfHatchBoundaryPath. */
        struct DxfHatchBoundaryPath *next;
                /*!< Pointer to the next DxfHatchBoundaryPath.\n
                 * \c NULL if the last DxfHatchBoundaryPath. */
} DxfHatchBoundaryPath;


/*!
 * \brief DXF definition of an AutoCAD hatch pattern definition line
 * dash.
 */
typedef struct
dxf_hatch_pattern_def_line_dash_struct
{
        double length;
                /*!< Dash length for a hatch pattern definition line.\n
                 * Group code = 49. */
        struct DxfHatchPatternDefLineDash *next;
                /*!< Pointer to the next DxfHatchPatternDefLineDash.\n
                 * \c NULL if the last DxfHatchPatternDefLineDash. */
} DxfHatchPatternDefLineDash;


/*!
 * \brief DXF definition of an AutoCAD hatch pattern definition line.
 */
typedef struct
dxf_hatch_pattern_def_line_struct
{
        int id_code;
                /*!< group code = 5. */
        double angle;
                /*!< Hatch pattern line angle.\n
                 * Group code = 53. */
        double x0;
                /*!< Hatch pattern line base point X-value.\n
                 * Group code = 43. */
        double y0;
                /*!< Hatch pattern line base point Y-value.\n
                 * Group code = 44. */
        double x1;
                /*!< Hatch pattern line offset point X-value.\n
                 * Group code = 45. */
        double y1;
                /*!< Hatch pattern line offset point Y-value.\n
                 * Group code = 46. */
        int16_t number_of_dash_items;
                /*!< Number of hatch pattern definition line dash items.\n
                 * Group code = 79. */
        struct DxfHatchPatternDefLineDash *dashes;
                /*!< Pointer to the first dash.\n
                 * \c NULL if the last DxfHatchPatternDefLineDash. */
        struct DxfHatchPatternDefLine *next;
                /*!< Pointer to the next DxfHatchPatternDefLine.\n
                 * \c NULL if the last DxfHatchPatternDefLine. */
} DxfHatchPatternDefLine;


/*!
 * \brief DXF definition of an AutoCAD hatch seed point.
 */
typedef struct
dxf_hatch_pattern_seedpoint_struct
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< Seed point X-value.\n
                 * Group code = 10. */
        double y0;
                /*!< Seed point Y-value.\n
                 * Group code = 20. */
        struct DxfHatchPatternSeedPoint *next;
                /*!< Pointer to the next DxfHatchSeedPoint.\n
                 * \c NULL if the last DxfHatchSeedPoint. */
} DxfHatchPatternSeedPoint;


/*!
 * \brief DXF definition of an AutoCAD hatch pattern.
 */
typedef struct
dxf_hatch_pattern_struct
{
        int id_code;
                /*!< group code = 5. */
        int16_t number_of_def_lines;
                /*!< Number of hatch pattern definition lines.\n
                 * Group code = 78. */
        struct DxfHatchPatternDefLine *def_lines;
                /*!< Pointer to the first \c DxfHatchPatterDefLine. */
        int32_t number_of_seed_points;
                /*!< Number of seed points.\n
                 * Group code = 98. */
        struct DxfHatchPatternSeedPoint *seed_points;
                /*!< Pointer to the first \c DxfHatchSeedPoint. */
        struct DxfHatchPattern *next;
                /*!< Pointer to the next DxfHatchPattern.\n
                 * \c NULL if the last DxfHatchPattern. */
} DxfHatchPattern;


/*!
 * \brief DXF definition of an AutoCAD hatch entity.
 */
typedef struct
dxf_hatch_struct
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
                /*!< Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60. */
        int16_t color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int16_t paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67.\n
                 * \since Introduced in version R13. */
        int32_t graphics_data_size;
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
        int32_t color_value;
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
        int32_t transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
        /* Specific members for a DXF hatch. */
        char *pattern_name;
                /*!< group code = 2. */
        DxfPoint *p0;
                /*!< Base point.\n
                 * Group codes = 10, 20 and 30.*/
        double pattern_scale;
                /*!< Pattern fill only.\n
                 * Group code 41. */
        double pixel_size;
                /*!< group code 47 */
        double pattern_angle;
                /*!< Pattern fill only.\n
                 * Group code 52. */
        int16_t solid_fill;
                /*!< 0 = pattern fill\n
                 * 1 = solid fill.\n
                 * Group code = 70. */
        int16_t associative;
                /*!< 0 = non-associative\n
                 * 1 = associative.\n
                 * Group code = 71. */
        int16_t hatch_style;
                /*!< 0 = hatch "odd parity" area (Normal style)\n
                 * 1 = hatch outermost area only (Outer style)\n
                 * 2 = hatch through entire area (Ignore style).\n
                 * Group code = 75. */
        int16_t hatch_pattern_type;
                /*!< 0 = user defined\n
                 * 1 = predefined\n
                 * 2 = custom.\n
                 * Group code = 76. */
        int16_t pattern_double;
                /*!< Pattern fill only\n
                 * 0 = not double\n
                 * 1 = double.\n
                 * Group code = 77. */
        int16_t number_of_pattern_def_lines;
                /*!< Number of pattern definition lines.\n
                 * Group code = 78. */
        int32_t number_of_boundary_paths;
                /*!< Number of boundary paths (loops).\n
                 * Group code = 91. */
        int32_t number_of_seed_points;
                /*!< Number of seed points.\n
                 * Group code = 98. */
        double extr_x0;
                /*!< Extrusion direction\n
                 * optional, if omitted defaults to 0.0.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Extrusion direction\n
                 * optional, if omitted defaults to 0.0.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Extrusion direction\n
                 * optional, if omitted defaults to 1.0.\n
                 * Group code = 230. */
        struct DxfHatchBoundaryPath *paths;
                /*!< Pointer to the first DxfHatchBoundaryPath.\n
                 * \c NULL if there is no DxfHatchBoundaryPath in the
                 * DxfHatch. */
        struct DxfHatchPattern *patterns;
                /*!< Pointer to the first DxfHatchPattern.\n
                 * \c NULL if there is no DxfHatchPattern in the
                 * DxfHatch. */
        struct DxfHatchPatternDefLine *def_lines;
                /*!< Pointer to the first DxfHatchPatternDefLine.\n
                 * \c NULL if there is no DxfHatchPatternDefLine in the
                 * DxfHatch. */
        struct DxfHatchPatternSeedPoint *seed_points;
                /*!< Pointer to the first DxfHatchSeedPoint. */
        struct DxfHatch *next;
                /*!< Pointer to the next DxfHatch.\n
                 * \c NULL if the last DxfHatch. */
} DxfHatch;


/* dxf_hatch functions. */
DxfHatch *dxf_hatch_new ();
DxfHatch *dxf_hatch_init (DxfHatch *hatch);
int dxf_hatch_write (DxfFile *fp, DxfHatch *hatch);
int dxf_hatch_free (DxfHatch *hatch);
void dxf_hatch_free_list (DxfHatch *hatches);
int dxf_hatch_get_id_code (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_id_code (DxfHatch *hatch, int id_code);
char *dxf_hatch_get_linetype (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_linetype (DxfHatch *hatch, char *linetype);
char *dxf_hatch_get_layer (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_layer (DxfHatch *hatch, char *layer);
double dxf_hatch_get_elevation (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_elevation (DxfHatch *hatch, double elevation);
double dxf_hatch_get_thickness (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_thickness (DxfHatch *hatch, double thickness);
double dxf_hatch_get_linetype_scale (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_linetype_scale (DxfHatch *hatch, double linetype_scale);
int16_t dxf_hatch_get_visibility (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_visibility (DxfHatch *hatch, int16_t visibility);
int16_t dxf_hatch_get_color (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_color (DxfHatch *hatch, int16_t color);
int16_t dxf_hatch_get_paperspace (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_paperspace (DxfHatch *hatch, int16_t paperspace);
int32_t dxf_hatch_get_graphics_data_size (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_graphics_data_size (DxfHatch *hatch, int32_t graphics_data_size);
DxfBinaryData *dxf_hatch_get_binary_graphics_data (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_binary_graphics_data (DxfHatch *hatch, DxfBinaryData *data);
char *dxf_hatch_get_dictionary_owner_soft (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_dictionary_owner_soft (DxfHatch *hatch, char *dictionary_owner_soft);
char *dxf_hatch_get_object_owner_soft (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_object_owner_soft (DxfHatch *hatch, char *object_owner_soft);
char *dxf_hatch_get_material (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_material (DxfHatch *hatch, char *material);
char *dxf_hatch_get_dictionary_owner_hard (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_dictionary_owner_hard (DxfHatch *hatch, char *dictionary_owner_hard);
int16_t dxf_hatch_get_lineweight (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_lineweight (DxfHatch *hatch, int16_t lineweight);
char *dxf_hatch_get_plot_style_name (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_plot_style_name (DxfHatch *hatch, char *plot_style_name);
int32_t dxf_hatch_get_color_value (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_color_value (DxfHatch *hatch, int32_t color_value);
char *dxf_hatch_get_color_name (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_color_name (DxfHatch *hatch, char *color_name);
int32_t dxf_hatch_get_transparency (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_transparency (DxfHatch *hatch, int32_t transparency);
char *dxf_hatch_get_pattern_name (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_pattern_name (DxfHatch *hatch, char *pattern_name);
DxfPoint *dxf_hatch_get_p0 (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_p0 (DxfHatch *hatch, DxfPoint *point);
double dxf_hatch_get_x0 (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_x0 (DxfHatch *hatch, double x0);
double dxf_hatch_get_y0 (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_y0 (DxfHatch *hatch, double y0);
double dxf_hatch_get_z0 (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_z0 (DxfHatch *hatch, double z0);
double dxf_hatch_get_pattern_scale (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_pattern_scale (DxfHatch *hatch, double pattern_scale);
double dxf_hatch_get_pixel_size (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_pixel_size (DxfHatch *hatch, double pattern_scale);
double dxf_hatch_get_pattern_angle (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_pattern_angle (DxfHatch *hatch, double pattern_angle);
int16_t dxf_hatch_get_solid_fill (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_solid_fill (DxfHatch *hatch, int16_t solid_fill);
int16_t dxf_hatch_get_associative (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_associative (DxfHatch *hatch, int16_t associative);
int16_t dxf_hatch_get_hatch_style (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_hatch_style (DxfHatch *hatch, int16_t hatch_style);
int16_t dxf_hatch_get_hatch_pattern_type (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_hatch_pattern_type (DxfHatch *hatch, int16_t hatch_pattern_type);
int16_t dxf_hatch_get_pattern_double (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_pattern_double (DxfHatch *hatch, int16_t pattern_double);
double dxf_hatch_get_extr_x0 (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_extr_x0 (DxfHatch *hatch, double extr_x0);
double dxf_hatch_get_extr_y0 (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_extr_y0 (DxfHatch *hatch, double extr_y0);
double dxf_hatch_get_extr_z0 (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_extr_z0 (DxfHatch *hatch, double extr_z0);
DxfHatchBoundaryPath *dxf_hatch_get_boundary_paths (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_boundary_paths (DxfHatch *hatch, DxfHatchBoundaryPath *paths);
DxfHatchPattern *dxf_hatch_get_patterns (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_patterns (DxfHatch *hatch, DxfHatchPattern *patterns);
DxfHatch *dxf_hatch_get_next (DxfHatch *hatch);
DxfHatch *dxf_hatch_set_next (DxfHatch *hatch, DxfHatch *next);
DxfHatch *dxf_hatch_get_last (DxfHatch *hatch);
/* dxf_hatch_pattern functions. */
DxfHatchPattern *dxf_hatch_pattern_new ();
DxfHatchPattern *dxf_hatch_pattern_init (DxfHatchPattern *pattern);
int dxf_hatch_pattern_free (DxfHatchPattern *pattern);
void dxf_hatch_pattern_free_list (DxfHatchPattern *patterns);
int dxf_hatch_pattern_get_id_code (DxfHatchPattern *pattern);
DxfHatchPattern *dxf_hatch_pattern_set_id_code (DxfHatchPattern *pattern, int id_code);
int16_t dxf_hatch_pattern_get_number_of_def_lines (DxfHatchPattern *pattern);
DxfHatchPattern *dxf_hatch_pattern_set_number_of_def_lines (DxfHatchPattern *pattern, int16_t number_of_def_lines);
DxfHatchPatternDefLine *dxf_hatch_pattern_get_def_lines (DxfHatchPattern *pattern);
DxfHatchPattern *dxf_hatch_pattern_set_def_lines (DxfHatchPattern *pattern, DxfHatchPatternDefLine *def_lines);
int32_t dxf_hatch_pattern_get_number_of_seed_points (DxfHatchPattern *pattern);
DxfHatchPattern *dxf_hatch_pattern_set_number_of_seed_points (DxfHatchPattern *pattern, int32_t number_of_seed_points);
DxfHatchPatternSeedPoint *dxf_hatch_pattern_get_seed_points (DxfHatchPattern *pattern);
DxfHatchPattern *dxf_hatch_pattern_set_seed_points (DxfHatchPattern *pattern, DxfHatchPatternSeedPoint *seed_points);
DxfHatchPattern *dxf_hatch_pattern_get_next (DxfHatchPattern *pattern);
DxfHatchPattern *dxf_hatch_pattern_set_next (DxfHatchPattern *pattern, DxfHatchPatternDefLine *next);
DxfHatchPattern *dxf_hatch_pattern_get_last (DxfHatchPattern *pattern);
/* dxf_hatch_pattern_def_line_dash functions. */
DxfHatchPatternDefLineDash *dxf_hatch_pattern_def_line_dash_new ();
DxfHatchPatternDefLineDash *dxf_hatch_pattern_def_line_dash_init (DxfHatchPatternDefLineDash *dash);
int dxf_hatch_pattern_def_line_dash_free (DxfHatchPatternDefLineDash *dash);
void dxf_hatch_pattern_def_line_dash_free_list (DxfHatchPatternDefLineDash *dashes);
double dxf_hatch_pattern_def_line_dash_get_length (DxfHatchPatternDefLineDash *dash);
DxfHatchPatternDefLineDash *dxf_hatch_pattern_def_line_dash_set_length (DxfHatchPatternDefLineDash *dash, double length);
DxfHatchPatternDefLineDash *dxf_hatch_pattern_def_line_dash_get_next (DxfHatchPatternDefLineDash *dash);
DxfHatchPatternDefLineDash *dxf_hatch_pattern_def_line_dash_set_next (DxfHatchPatternDefLineDash *dash, DxfHatchPatternDefLineDash *next);
DxfHatchPatternDefLineDash *dxf_hatch_pattern_def_line_dash_get_last (DxfHatchPatternDefLineDash *dash);
/* dxf_hatch_pattern_def_line functions. */
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_new ();
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_init (DxfHatchPatternDefLine *line);
int dxf_hatch_pattern_def_line_write (DxfFile *fp, DxfHatchPatternDefLine *line);
int dxf_hatch_pattern_def_line_free (DxfHatchPatternDefLine *line);
void dxf_hatch_pattern_def_line_free_list (DxfHatchPatternDefLine *lines);
int dxf_hatch_pattern_def_line_get_id_code (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_id_code (DxfHatchPatternDefLine *line, int id_code);
double dxf_hatch_pattern_def_line_get_angle (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_angle (DxfHatchPatternDefLine *line, double angle);
double dxf_hatch_pattern_def_line_get_x0 (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_x0 (DxfHatchPatternDefLine *line, double x0);
double dxf_hatch_pattern_def_line_get_y0 (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_y0 (DxfHatchPatternDefLine *line, double y0);
double dxf_hatch_pattern_def_line_get_x1 (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_x1 (DxfHatchPatternDefLine *line, double x1);
double dxf_hatch_pattern_def_line_get_y1 (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_y1 (DxfHatchPatternDefLine *line, double y1);
int16_t dxf_hatch_pattern_def_line_get_number_of_dash_items (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_number_of_dash_items (DxfHatchPatternDefLine *line, int16_t number_of_dash_items);
DxfHatchPatternDefLineDash *dxf_hatch_pattern_def_line_get_dashes (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_dashes (DxfHatchPatternDefLine *line, DxfHatchPatternDefLineDash *dashes);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_get_next (DxfHatchPatternDefLine *line);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_set_next (DxfHatchPatternDefLine *line, DxfHatchPatternDefLine *next);
DxfHatchPatternDefLine *dxf_hatch_pattern_def_line_get_last (DxfHatchPatternDefLine *line);
/* dxf_hatch_pattern_seedpoint functions. */
DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint_new ();
DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint_init (DxfHatchPatternSeedPoint *seedpoint);
int dxf_hatch_pattern_seedpoint_write (DxfFile *fp, DxfHatchPatternSeedPoint *seedpoint);
int dxf_hatch_pattern_seedpoint_free (DxfHatchPatternSeedPoint *seedpoint);
void dxf_hatch_pattern_seedpoint_free_list (DxfHatchPatternSeedPoint *hatch_pattern_seed_points);
int dxf_hatch_pattern_seedpoint_get_id_code (DxfHatchPatternSeedPoint *point);
DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint_set_id_code (DxfHatchPatternSeedPoint *point, int id_code);
double dxf_hatch_pattern_seedpoint_get_x0 (DxfHatchPatternSeedPoint *point);
DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint_set_x0 (DxfHatchPatternSeedPoint *point, double x0);
double dxf_hatch_pattern_seedpoint_get_y0 (DxfHatchPatternSeedPoint *point);
DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint_set_y0 (DxfHatchPatternSeedPoint *point, double y0);
DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint_get_next (DxfHatchPatternSeedPoint *point);
DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint_set_next (DxfHatchPatternSeedPoint *point, DxfHatchPatternSeedPoint *next);
DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint_get_last (DxfHatchPatternSeedPoint *point);
/* dxf_hatch_boundary_path functions. */
DxfHatchBoundaryPath *dxf_hatch_boundary_path_new ();
DxfHatchBoundaryPath *dxf_hatch_boundary_path_init (DxfHatchBoundaryPath *path);
int dxf_hatch_boundary_path_write (DxfFile *fp, DxfHatchBoundaryPath *path);
int dxf_hatch_boundary_path_free (DxfHatchBoundaryPath *path);
void dxf_hatch_boundary_path_free_list (DxfHatchBoundaryPath *hatch_boundary_paths);
int dxf_hatch_boundary_path_get_id_code (DxfHatchBoundaryPath *path);
DxfHatchBoundaryPath *dxf_hatch_boundary_path_set_id_code (DxfHatchBoundaryPath *path, int id_code);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_get_edges (DxfHatchBoundaryPath *path);
DxfHatchBoundaryPath *dxf_hatch_boundary_path_set_edges (DxfHatchBoundaryPath *path, DxfHatchBoundaryPathEdge *edges);
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_get_polylines (DxfHatchBoundaryPath *path);
DxfHatchBoundaryPath *dxf_hatch_boundary_path_set_polylines (DxfHatchBoundaryPath *path, DxfHatchBoundaryPathPolyline *polylines);
DxfHatchBoundaryPath *dxf_hatch_boundary_path_get_next (DxfHatchBoundaryPath *path);
DxfHatchBoundaryPath *dxf_hatch_boundary_path_set_next (DxfHatchBoundaryPath *path, DxfHatchBoundaryPath *next);
DxfHatchBoundaryPath *dxf_hatch_boundary_path_get_last (DxfHatchBoundaryPath *path);
/* dxf_hatch_boundary_path_polyline functions. */
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_new ();
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_init (DxfHatchBoundaryPathPolyline *polyline);
int dxf_hatch_boundary_path_polyline_write (DxfFile *fp, DxfHatchBoundaryPathPolyline *polyline);
int dxf_hatch_boundary_path_polyline_free (DxfHatchBoundaryPathPolyline *polyline);
void dxf_hatch_boundary_path_polyline_free_list (DxfHatchBoundaryPathPolyline *polylines);
int dxf_hatch_boundary_path_polyline_get_id_code (DxfHatchBoundaryPathPolyline *polyline);
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_set_id_code (DxfHatchBoundaryPathPolyline *polyline, int id_code);
int16_t dxf_hatch_boundary_path_polyline_get_is_closed (DxfHatchBoundaryPathPolyline *polyline);
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_set_is_closed (DxfHatchBoundaryPathPolyline *polyline, int16_t is_closed);
int32_t dxf_hatch_boundary_path_polyline_get_number_of_vertices (DxfHatchBoundaryPathPolyline *polyline);
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_set_number_of_vertices (DxfHatchBoundaryPathPolyline *polyline, int32_t number_of_vertices);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_get_vertices (DxfHatchBoundaryPathPolyline *polyline);
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_set_vertices (DxfHatchBoundaryPathPolyline *polyline, DxfHatchBoundaryPathPolylineVertex *vertices);
int dxf_hatch_boundary_path_polyline_close_polyline (DxfHatchBoundaryPathPolyline *polyline);
int dxf_hatch_boundary_path_polyline_point_inside_polyline (DxfHatchBoundaryPathPolyline *polyline, DxfPoint *point);
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_get_next (DxfHatchBoundaryPathPolyline *polyline);
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_set_next (DxfHatchBoundaryPathPolyline *polyline, DxfHatchBoundaryPathPolyline *next);
DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline_get_last (DxfHatchBoundaryPathPolyline *polyline);
/* dxf_hatch_boundary_pathPolyline_vertex functions. */
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_new ();
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_init (DxfHatchBoundaryPathPolylineVertex *vertex);
int dxf_hatch_boundary_path_polyline_vertex_write (DxfFile *fp, DxfHatchBoundaryPathPolylineVertex *vertex);
int dxf_hatch_boundary_path_polyline_vertex_free (DxfHatchBoundaryPathPolylineVertex *vertex);
void dxf_hatch_boundary_path_polyline_vertex_free_list (DxfHatchBoundaryPathPolylineVertex *hatch_boundary_path_polyline_vertices);
int dxf_hatch_boundary_path_polyline_vertex_get_id_code (DxfHatchBoundaryPathPolylineVertex *vertex);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_set_id_code (DxfHatchBoundaryPathPolylineVertex *vertex, int id_code);
double dxf_hatch_boundary_path_polyline_vertex_get_x0 (DxfHatchBoundaryPathPolylineVertex *vertex);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_set_x0 (DxfHatchBoundaryPathPolylineVertex *vertex, double x0);
double dxf_hatch_boundary_path_polyline_vertex_get_y0 (DxfHatchBoundaryPathPolylineVertex *vertex);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_set_y0 (DxfHatchBoundaryPathPolylineVertex *vertex, double y0);
double dxf_hatch_boundary_path_polyline_vertex_get_bulge (DxfHatchBoundaryPathPolylineVertex *vertex);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_set_bulge (DxfHatchBoundaryPathPolylineVertex *vertex, double bulge);
int16_t dxf_hatch_boundary_path_polyline_vertex_get_has_bulge (DxfHatchBoundaryPathPolylineVertex *vertex);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_set_has_bulge (DxfHatchBoundaryPathPolylineVertex *vertex, int16_t has_bulge);
double dxf_hatch_boundary_path_polyline_vertex_angle (DxfHatchBoundaryPathPolylineVertex *vertex_0, DxfHatchBoundaryPathPolylineVertex *vertex_1);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_get_next (DxfHatchBoundaryPathPolylineVertex *vertex);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_set_next (DxfHatchBoundaryPathPolylineVertex *vertex, DxfHatchBoundaryPathPolylineVertex *next);
DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_get_last (DxfHatchBoundaryPathPolylineVertex *vertex);
/* dxf_hatch_boundary_path_edge functions. */
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_new ();
DxfHatchBoundaryPathEdge * dxf_hatch_boundary_path_edge_init (DxfHatchBoundaryPathEdge *edge);
int dxf_hatch_boundary_path_edge_free (DxfHatchBoundaryPathEdge *edge);
void dxf_hatch_boundary_path_edge_free_list (DxfHatchBoundaryPathEdge *edges);
int dxf_hatch_boundary_path_edge_get_id_code (DxfHatchBoundaryPathEdge *edge);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_set_id_code (DxfHatchBoundaryPathEdge *edge, int id_code);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_get_arcs (DxfHatchBoundaryPathEdge *edge);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_set_arcs (DxfHatchBoundaryPathEdge *edge, DxfHatchBoundaryPathEdgeArc *arcs);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_get_ellipses (DxfHatchBoundaryPathEdge *edge);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_set_ellipses (DxfHatchBoundaryPathEdge *edge, DxfHatchBoundaryPathEdgeEllipse *ellipses);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_get_lines (DxfHatchBoundaryPathEdge *edge);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_set_lines (DxfHatchBoundaryPathEdge *edge, DxfHatchBoundaryPathEdgeLine *lines);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_get_splines (DxfHatchBoundaryPathEdge *edge);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_set_splines (DxfHatchBoundaryPathEdge *edge, DxfHatchBoundaryPathEdgeSpline *splines);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_get_next (DxfHatchBoundaryPathEdge *edge);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_set_next (DxfHatchBoundaryPathEdge *edge, DxfHatchBoundaryPathEdge *next);
DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge_get_last (DxfHatchBoundaryPathEdge *edge);
/* dxf_hatch_boundary_path_edge_arc functions. */
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_new ();
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_init (DxfHatchBoundaryPathEdgeArc *arc);
int dxf_hatch_boundary_path_edge_arc_free (DxfHatchBoundaryPathEdgeArc *arc);
void dxf_hatch_boundary_path_edge_arc_free_list (DxfHatchBoundaryPathEdgeArc *hatch_boundary_path_edge_arcs);
int dxf_hatch_boundary_path_edge_arc_get_id_code (DxfHatchBoundaryPathEdgeArc *arc);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_id_code (DxfHatchBoundaryPathEdgeArc *arc, int id_code);
double dxf_hatch_boundary_path_edge_arc_get_x0 (DxfHatchBoundaryPathEdgeArc *arc);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_x0 (DxfHatchBoundaryPathEdgeArc *arc, double x0);
double dxf_hatch_boundary_path_edge_arc_get_y0 (DxfHatchBoundaryPathEdgeArc *arc);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_y0 (DxfHatchBoundaryPathEdgeArc *arc, double y0);
DxfPoint *dxf_hatch_boundary_path_edge_arc_get_center_point (DxfHatchBoundaryPathEdgeArc *arc, int id_code);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_center_point (DxfHatchBoundaryPathEdgeArc *arc, DxfPoint *point);
double dxf_hatch_boundary_path_edge_arc_get_radius (DxfHatchBoundaryPathEdgeArc *arc);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_radius (DxfHatchBoundaryPathEdgeArc *arc, double radius);
double dxf_hatch_boundary_path_edge_arc_get_start_angle (DxfHatchBoundaryPathEdgeArc *arc);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_start_angle (DxfHatchBoundaryPathEdgeArc *arc, double start_angle);
double dxf_hatch_boundary_path_edge_arc_get_end_angle (DxfHatchBoundaryPathEdgeArc *arc);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_end_angle (DxfHatchBoundaryPathEdgeArc *arc, double end_angle);
int16_t dxf_hatch_boundary_path_edge_arc_get_is_ccw (DxfHatchBoundaryPathEdgeArc *arc);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_is_ccw (DxfHatchBoundaryPathEdgeArc *arc, int16_t is_ccw);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_get_next (DxfHatchBoundaryPathEdgeArc *arc);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_set_next (DxfHatchBoundaryPathEdgeArc *arc, DxfHatchBoundaryPathEdgeArc *next);
DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc_get_last (DxfHatchBoundaryPathEdgeArc *arc);
/* dxf_hatch_boundary_path_edge_ellipse functions. */
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_new ();
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_init (DxfHatchBoundaryPathEdgeEllipse *ellipse);
int dxf_hatch_boundary_path_edge_ellipse_free (DxfHatchBoundaryPathEdgeEllipse *ellipse);
void dxf_hatch_boundary_path_edge_ellipse_free_list (DxfHatchBoundaryPathEdgeEllipse *hatch_boundary_path_edge_ellipses);
int dxf_hatch_boundary_path_edge_ellipse_get_id_code (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_id_code (DxfHatchBoundaryPathEdgeEllipse *ellipse, int id_code);
double dxf_hatch_boundary_path_edge_ellipse_get_x0 (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_x0 (DxfHatchBoundaryPathEdgeEllipse *ellipse, double x0);
double dxf_hatch_boundary_path_edge_ellipse_get_y0 (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_y0 (DxfHatchBoundaryPathEdgeEllipse *ellipse, double y0);
DxfPoint *dxf_hatch_boundary_path_edge_ellipse_get_center_point (DxfHatchBoundaryPathEdgeEllipse *ellipse, int id_code);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_center_point (DxfHatchBoundaryPathEdgeEllipse *ellipse, DxfPoint *point);
double dxf_hatch_boundary_path_edge_ellipse_get_x1 (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_x1 (DxfHatchBoundaryPathEdgeEllipse *ellipse, double x1);
double dxf_hatch_boundary_path_edge_ellipse_get_y1 (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_y1 (DxfHatchBoundaryPathEdgeEllipse *ellipse, double y1);
DxfPoint *dxf_hatch_boundary_path_edge_ellipse_get_end_point (DxfHatchBoundaryPathEdgeEllipse *ellipse, int id_code);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_end_point (DxfHatchBoundaryPathEdgeEllipse *ellipse, DxfPoint *point);
double dxf_hatch_boundary_path_edge_ellipse_get_ratio (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_ratio (DxfHatchBoundaryPathEdgeEllipse *ellipse, double ratio);
double dxf_hatch_boundary_path_edge_ellipse_get_start_angle (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_start_angle (DxfHatchBoundaryPathEdgeEllipse *ellipse, double start_angle);
double dxf_hatch_boundary_path_edge_ellipse_get_end_angle (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_end_angle (DxfHatchBoundaryPathEdgeEllipse *ellipse, double end_angle);
int16_t dxf_hatch_boundary_path_edge_ellipse_get_is_ccw (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_is_ccw (DxfHatchBoundaryPathEdgeEllipse *ellipse, int16_t is_ccw);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_get_next (DxfHatchBoundaryPathEdgeEllipse *ellipse);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_set_next (DxfHatchBoundaryPathEdgeEllipse *ellipse, DxfHatchBoundaryPathEdgeEllipse *next);
DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse_get_last (DxfHatchBoundaryPathEdgeEllipse *ellipse);
/* dxf_hatch_boundary_path_edge_line functions. */
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_new ();
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_init (DxfHatchBoundaryPathEdgeLine *line);
int dxf_hatch_boundary_path_edge_line_free (DxfHatchBoundaryPathEdgeLine *line);
void dxf_hatch_boundary_path_edge_line_free_list (DxfHatchBoundaryPathEdgeLine *hatch_boundary_path_edge_lines);
int dxf_hatch_boundary_path_edge_line_get_id_code (DxfHatchBoundaryPathEdgeLine *line);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_set_id_code (DxfHatchBoundaryPathEdgeLine *line, int id_code);
double dxf_hatch_boundary_path_edge_line_get_x0 (DxfHatchBoundaryPathEdgeLine *line);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_set_x0 (DxfHatchBoundaryPathEdgeLine *line, double x0);
double dxf_hatch_boundary_path_edge_line_get_y0 (DxfHatchBoundaryPathEdgeLine *line);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_set_y0 (DxfHatchBoundaryPathEdgeLine *line, double y0);
DxfPoint *dxf_hatch_boundary_path_edge_line_get_start_point (DxfHatchBoundaryPathEdgeLine *line, int id_code);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_set_start_point (DxfHatchBoundaryPathEdgeLine *line, DxfPoint *point);
double dxf_hatch_boundary_path_edge_line_get_x1 (DxfHatchBoundaryPathEdgeLine *line);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_set_x1 (DxfHatchBoundaryPathEdgeLine *line, double x1);
double dxf_hatch_boundary_path_edge_line_get_y1 (DxfHatchBoundaryPathEdgeLine *line);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_set_y1 (DxfHatchBoundaryPathEdgeLine *line, double y1);
DxfPoint *dxf_hatch_boundary_path_edge_line_get_end_point (DxfHatchBoundaryPathEdgeLine *line, int id_code);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_set_end_point (DxfHatchBoundaryPathEdgeLine *line, DxfPoint *point);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_get_next (DxfHatchBoundaryPathEdgeLine *line);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_set_next (DxfHatchBoundaryPathEdgeLine *line, DxfHatchBoundaryPathEdgeLine *next);
DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line_get_last (DxfHatchBoundaryPathEdgeLine *line);
/* dxf_hatch_boundary_path_edge_spline functions. */
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_new ();
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_init (DxfHatchBoundaryPathEdgeSpline *spline);
int dxf_hatch_boundary_path_edge_spline_free (DxfHatchBoundaryPathEdgeSpline *spline);
void dxf_hatch_boundary_path_edge_spline_free_list (DxfHatchBoundaryPathEdgeSpline *hatch_boundary_path_edge_splines);
int dxf_hatch_boundary_path_edge_spline_get_id_code (DxfHatchBoundaryPathEdgeSpline *spline);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_id_code (DxfHatchBoundaryPathEdgeSpline *spline, int id_code);
int32_t dxf_hatch_boundary_path_edge_spline_get_degree (DxfHatchBoundaryPathEdgeSpline *spline);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_degree (DxfHatchBoundaryPathEdgeSpline *spline, int32_t degree);
int16_t dxf_hatch_boundary_path_edge_spline_get_rational (DxfHatchBoundaryPathEdgeSpline *spline);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_rational (DxfHatchBoundaryPathEdgeSpline *spline, int16_t rational);
int16_t dxf_hatch_boundary_path_edge_spline_get_periodic (DxfHatchBoundaryPathEdgeSpline *spline);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_periodic (DxfHatchBoundaryPathEdgeSpline *spline, int16_t periodic);
int32_t dxf_hatch_boundary_path_edge_spline_get_number_of_knots (DxfHatchBoundaryPathEdgeSpline *spline);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_number_of_knots (DxfHatchBoundaryPathEdgeSpline *spline, int32_t number_of_knots);
int dxf_hatch_boundary_path_edge_spline_get_knots (DxfHatchBoundaryPathEdgeSpline *spline, double knots[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_knots (DxfHatchBoundaryPathEdgeSpline *spline, double knots[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]);
int32_t dxf_hatch_boundary_path_edge_spline_get_number_of_control_points (DxfHatchBoundaryPathEdgeSpline *spline);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_number_of_control_points (DxfHatchBoundaryPathEdgeSpline *spline, int32_t number_of_control_points);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_get_control_points (DxfHatchBoundaryPathEdgeSpline *spline);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_control_points (DxfHatchBoundaryPathEdgeSpline *spline, DxfHatchBoundaryPathEdgeSplineCp *control_points);
int dxf_hatch_boundary_path_edge_spline_append_control_point (DxfHatchBoundaryPathEdgeSpline *spline, DxfHatchBoundaryPathEdgeSplineCp *control_point);
int dxf_hatch_boundary_path_edge_spline_prepend_control_point (DxfHatchBoundaryPathEdgeSpline *spline, DxfHatchBoundaryPathEdgeSplineCp *control_point);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_get_control_point (DxfHatchBoundaryPathEdgeSpline *spline, int position);
int dxf_hatch_boundary_path_edge_spline_set_control_point (DxfHatchBoundaryPathEdgeSpline *spline, int position, DxfHatchBoundaryPathEdgeSplineCp *control_point);
int dxf_hatch_boundary_path_edge_spline_insert_control_point (DxfHatchBoundaryPathEdgeSpline *spline, int position, DxfHatchBoundaryPathEdgeSplineCp *control_point);
int dxf_hatch_boundary_path_edge_spline_remove_control_point (DxfHatchBoundaryPathEdgeSpline *spline, int position);
DxfHatchBoundaryPathEdgeSplineCp * dxf_hatch_boundary_path_edge_spline_copy_control_points (DxfHatchBoundaryPathEdgeSpline *spline);
int dxf_hatch_boundary_path_edge_spline_append_knot_value (DxfHatchBoundaryPathEdgeSpline *spline, double knot_value);
int dxf_hatch_boundary_path_edge_spline_prepend_knot_value (DxfHatchBoundaryPathEdgeSpline *spline, double knot_value);
double dxf_hatch_boundary_path_edge_spline_get_knot_value (DxfHatchBoundaryPathEdgeSpline *spline, int position);
int dxf_hatch_boundary_path_edge_spline_set_knot_value (DxfHatchBoundaryPathEdgeSpline *spline, int position, double knot_value);
int dxf_hatch_boundary_path_edge_spline_insert_knot_value (DxfHatchBoundaryPathEdgeSpline *spline, int position, double knot_value);
int dxf_hatch_boundary_path_edge_spline_remove_knot_value (DxfHatchBoundaryPathEdgeSpline *spline, int position);
int dxf_hatch_boundary_path_edge_spline_copy_knot_values (DxfHatchBoundaryPathEdgeSpline *spline, double *knot_values[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_get_next (DxfHatchBoundaryPathEdgeSpline *spline);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_set_next (DxfHatchBoundaryPathEdgeSpline *spline, DxfHatchBoundaryPathEdgeSpline *next);
DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline_get_last (DxfHatchBoundaryPathEdgeSpline *spline);
/* dxf_hatch_boundary_path_edge_spline_control_point functions. */
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_control_point_new ();
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_control_point_init (DxfHatchBoundaryPathEdgeSplineCp *control_point);
int dxf_hatch_boundary_path_edge_spline_control_point_free (DxfHatchBoundaryPathEdgeSplineCp *control_point);
void dxf_hatch_boundary_path_edge_spline_control_point_free_list (DxfHatchBoundaryPathEdgeSplineCp *hatch_boundary_path_edge_spline_control_points);
int dxf_hatch_boundary_path_edge_spline_cp_get_id_code (DxfHatchBoundaryPathEdgeSplineCp *control_point);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp_set_id_code (DxfHatchBoundaryPathEdgeSplineCp *control_point, int id_code);
double dxf_hatch_boundary_path_edge_spline_cp_get_x0 (DxfHatchBoundaryPathEdgeSplineCp *control_point);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp_set_x0 (DxfHatchBoundaryPathEdgeSplineCp *control_point, double x0);
double dxf_hatch_boundary_path_edge_spline_cp_get_y0 (DxfHatchBoundaryPathEdgeSplineCp *control_point);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp_set_y0 (DxfHatchBoundaryPathEdgeSplineCp *control_point, double y0);
DxfPoint *dxf_hatch_boundary_path_edge_spline_cp_get_point (DxfHatchBoundaryPathEdgeSplineCp *control_point, int id_code);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp_set_point (DxfHatchBoundaryPathEdgeSplineCp *control_point, DxfPoint *point);
double dxf_hatch_boundary_path_edge_spline_cp_get_weight (DxfHatchBoundaryPathEdgeSplineCp *control_point);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp_set_weight (DxfHatchBoundaryPathEdgeSplineCp *control_point, double weight);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp_get_next (DxfHatchBoundaryPathEdgeSplineCp *control_point);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp_set_next (DxfHatchBoundaryPathEdgeSplineCp *control_point, DxfHatchBoundaryPathEdgeSplineCp *next);
DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp_get_last (DxfHatchBoundaryPathEdgeSplineCp *control_point);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_HATCH_H */


/* EOF */
