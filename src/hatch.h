/*!
 * \file hatch.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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


#define DXF_MAX_HATCH_PATTERN_DEF_LINE_DASH_ITEMS 16
#define DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS 64


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge arc.
 */
typedef struct
dxf_hatch_boundary_path_edge_arc
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
        int is_ccw;
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
dxf_hatch_boundary_path_edge_ellipse
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
        int is_ccw;
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
dxf_hatch_boundary_path_edge_line
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = = 10\n
                 * start point X-value. */
        double y0;
                /*!< group code = 20\n
                 * start point Y-value. */
        double x1;
                /*!< group code = 11\n
                 * end point X-value. */
        double y1;
                /*!< group code = 21\n
                 * end point Y-value. */
        struct DxfHatchBoundaryPathEdgeLine *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeLine.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeLine. */
} DxfHatchBoundaryPathEdgeLine;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge spline
 * control point.
 */
typedef struct
dxf_hatch_boundary_path_edge_spline_cp
{
        int id_code;
                /*!< group code = 5. */
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
                /*!< pointer to the next DxfHatchBoundaryPathEdgeSplineCp.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeSplineCp. */
} DxfHatchBoundaryPathEdgeSplineCp;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge spline.
 */
typedef struct
dxf_hatch_boundary_path_edge_spline
{
        int id_code;
                /*!< group code = 5. */
        int degree;
                /*!< group code = 94. */
        int rational;
                /*!< group code = 73. */
        int periodic;
                /*!< group code = 74. */
        int number_of_knots;
                /*!< group code = 95\n
                 * number of knots. */
        double knots[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS];
                /*!< group code = 40\n
                 * knot values control the shape of the curve as it
                 * passes through the control points. */
        int number_of_control_points;
                /*!< group code = 96\n
                 * number of control points. */
        struct DxfHatchBoundaryPathEdgeSplineCp *control_points;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeSplineCp.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeSplineCp
                 * in the DxfHatchBoundaryPathEdgeSpline. */
        struct DxfHatchBoundaryPathEdgeSpline *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeSpline.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeSpline. */
} DxfHatchBoundaryPathEdgeSpline;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge
 * (composite of arcs, ellipses, lines or splines).
 */
typedef struct
dxf_hatch_boundary_path_edge
{
        int id_code;
                /*!< group code = 5.\n
                 * Treat the boundary path edge as if it were a single
                 * (composite) entity. */
        struct DxfHatchBoundaryPathEdgeArc *arcs;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeArc.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeArc in
                 * the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeEllipse *ellipses;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeEllipse.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeEllipse
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeLine * lines;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeLine.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeLine
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeSpline *splines;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeSpline.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeSpline
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdge *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdge.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdge. */
} DxfHatchBoundaryPathEdge;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path polyline
 * vertex.
 */
typedef struct
dxf_hatch_boundary_path_polyline_vertex
{
        int id_code;
                /*!< group code = 5.*/
        double x0;
                /*!< group code = 10. */
        double y0;
                /*!< group code = 20. */
        struct DxfHatchBoundaryPathPolylineVertex *next;
                /*!< pointer to the next DxfHatchBoundaryPathPolylineVertex.\n
                 * \c NULL if the last DxfHatchBoundaryPathPolylineVertex. */
} DxfHatchBoundaryPathPolylineVertex;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path polyline.
 */
typedef struct
dxf_hatch_boundary_path_polyline
{
        int id_code;
                /*!< group code = 5. */
        double bulge;
                /*!< group code = 42.\n
                 * optional, default = 0. */
        int has_bulge;
                /*!< group code = 72. */
        int is_closed;
                /*!< group code = 73. */
        int number_of_vertices;
                /*!< group code = 93\n
                 * number of polyline vertices in
                 * DxfHatchBoundaryPathPolyline. */
        struct DxfHatchBoundaryPathPolylineVertex *vertices;
                /*!< pointer to the first
                 * DxfHatchBoundaryPathPolylineVertex.\n
                 * \c NULL if there is no
                 * DxfHatchBoundaryPathPolylineVertex in the
                 * DxfHatchBoundaryPathPolyline. */
        struct DxfHatchBoundaryPathPolyline *next;
                /*!< pointer to the next DxfHatchBoundaryPathPolyline.\n
                 * \c NULL if the last DxfHatchBoundaryPathPolyline. */
} DxfHatchBoundaryPathPolyline;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path (or loop)
 * (composite of a closed series of edges, and/or a polyline).
 */
typedef struct
dxf_hatch_boundary_path
{
        int id_code;
                /*!< group code = 5.\n
                 * Treat the boundary path as if it were a single
                 * (composite) entity. */
        struct DxfHatchBoundaryPathEdge *edges;
                /*!< pointer to the first DxfHatchBoundaryPathEdge.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdge in
                 * the DxfHatchBoundaryPath. */
        struct DxfHatchBoundaryPathPolyline *polylines;
                /*!< pointer to the first DxfHatchBoundaryPathPolyline.\n
                 * \c NULL if there is no DxfHatchBoundaryPathPolyline
                 * in the DxfHatchBoundaryPath. */
        struct DxfHatchBoundaryPath *next;
                /*!< pointer to the next DxfHatchBoundaryPath.\n
                 * \c NULL if the last DxfHatchBoundaryPath. */
} DxfHatchBoundaryPath;


/*!
 * \brief DXF definition of an AutoCAD hatch pattern definition line.
 */
typedef struct
dxf_hatch_pattern_def_line
{
        int id_code;
                /*!< group code = 5. */
        double angle;
                /*!< group code = 53\n
                 * hatch pattern line angle. */
        double x0;
                /*!< group code = 43\n
                 * hatch pattern line base point X-value. */
        double y0;
                /*!< group code = 44\n
                 * hatch pattern line base point Y-value. */
        double x1;
                /*!< group code = 45\n
                 * hatch pattern line offset point X-value. */
        double y1;
                /*!< group code = 46\n
                 * hatch pattern line offset point Y-value. */
        int dash_items;
                /*!< group code = 79\n
                 * number of hatch pattern definition line dash items. */
        double dash_length[DXF_MAX_HATCH_PATTERN_DEF_LINE_DASH_ITEMS];
                /*!< group code = 49\n
                 * array of dash lengths for an array of hatch pattern
                 * definition lines. */
        struct DxfHatchPatternDefLine *next;
                /*!< pointer to the next DxfHatchPatternDefLine.\n
                 * \c NULL if the last DxfHatchPatternDefLine. */
} DxfHatchPatternDefLine;


/*!
 * \brief DXF definition of an AutoCAD hatch seed point.
 */
typedef struct
dxf_hatch_pattern_seedpoint
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = 10\n
                 * seed point X-value. */
        double y0;
                /*!< group code = 20\n
                 * seed point Y-value. */
        struct DxfHatchPatternSeedPoint *next;
                /*!< pointer to the next DxfHatchSeedPoint.\n
                 * \c NULL if the last DxfHatchSeedPoint. */
} DxfHatchPatternSeedPoint;


/*!
 * \brief DXF definition of an AutoCAD hatch pattern.
 */
typedef struct
dxf_hatch_pattern
{
        int id_code;
                /*!< group code = 5. */
        int def_lines;
                /*!< group code = 78\n
                 * number of hatch pattern definition lines. */
        struct DxfHatchPatternDefLine *lines;
                /*!< pointer to the first \c DxfHatchPatterDefLine. */
        double **length;
                /*!< group code = 49\n
                 * array of dash lengths for an array of hatch pattern
                 * definition lines. */
        int number_of_seed_points;
                /*!< group code = 98\n
                 * number of seed points. */
        struct DxfHatchPatternSeedPoint *seed_points;
                /*!< pointer to the first \c DxfHatchSeedPoint. */
        struct DxfHatchPattern *next;
                /*!< pointer to the next DxfHatchPattern.\n
                 * \c NULL if the last DxfHatchPattern. */
} DxfHatchPattern;


/*!
 * \brief DXF definition of an AutoCAD hatch entity.
 */
typedef struct
dxf_hatch
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< group code = 5\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        char *linetype;
                /*!< group code = 6\n
                 * The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file. */
        char *layer;
                /*!< group code = 8\n
                 * Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given. */
        double elevation;
                /*!< group code = 38\n
                 * Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default). */
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        int graphics_data_size;
                /*!< group code = 92\n
                 * The number of bytes in the image (and subsequent
                 * binary chunk records) (optional). */
        char *binary_graphics_data[DXF_MAX_PARAM];
                /*!< group code = 310\n
                 * Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional). */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        /* Specific members for a DXF hatch. */
        char *pattern_name;
                /*!< group code = 2. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double pattern_scale;
                /*!< group code 41\n
                 * pattern fill only. */
        double pixel_size;
                /*!< group code 47 */
        double pattern_angle;
                /*!< group code 52\n
                 * pattern fill only. */
        int solid_fill;
                /*!< group code = 70\n
                 * 0 = pattern fill\n
                 * 1 = solid fill. */
        int associative;
                /*!< group code = 71\n
                 * 0 = non-associative\n
                 * 1 = associative. */
        int hatch_style;
                /*!< group code = 75\n
                 * 0 = hatch "odd parity" area (Normal style)\n
                 * 1 = hatch outermost area only (Outer style)\n
                 * 2 = hatch through entire area (Ignore style). */
        int hatch_pattern_type;
                /*!< group code = 76\n
                 * 0 = user defined\n
                 * 1 = predefined\n
                 * 2 = custom. */
        int pattern_double;
                /*!< group code = 77\n
                 * pattern fill only\n
                 * 0 = not double\n
                 * 1 = double. */
        int number_of_pattern_def_lines;
                /*!< group code = 78\n
                 * number of pattern definition lines. */
        int number_of_boundary_paths;
                /*!< group code = 91\n
                 * number of boundary paths (loops). */
        int number_of_seed_points;
                /*!< group code = 98\n
                 * number of seed points. */
        double extr_x0;
                /*!< group code = 210\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_y0;
                /*!< group code = 220\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_z0;
                /*!< group code = 230\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 1.0. */
        struct DxfHatchBoundaryPath *paths;
                /*!< pointer to the first DxfHatchBoundaryPath.\n
                 * \c NULL if there is no DxfHatchBoundaryPath in the
                 * DxfHatch. */
        struct DxfHatchPatternDefLine *def_lines;
                /*!< pointer to the first DxfHatchPatternDefLine.\n
                 * \c NULL if there is no DxfHatchPatternDefLine in the
                 * DxfHatch. */
        struct DxfHatchPatternSeedPoint *seed_points;
                /*!< pointer to the first DxfHatchSeedPoint. */
        struct DxfHatch *next;
                /*!< pointer to the next DxfHatch.\n
                 * \c NULL if the last DxfHatch. */
} DxfHatch;


/* dxf_hatch functions. */
DxfHatch *
dxf_hatch_new ();
DxfHatch *
dxf_hatch_init
(
        DxfHatch *hatch
);
int
dxf_hatch_write
(
        DxfFile *fp,
        DxfHatch *hatch
);
int
dxf_hatch_free
(
        DxfHatch *hatch
);
void
dxf_hatch_free_chain
(
        DxfHatch *hatches
);
/* dxf_hatch_pattern functions. */
DxfHatchPattern *
dxf_hatch_pattern_new ();
DxfHatchPattern *
dxf_hatch_pattern_init
(
        DxfHatchPattern *pattern
);
int
dxf_hatch_pattern_free
(
        DxfHatchPattern *pattern
);
void
dxf_hatch_pattern_free_chain
(
        DxfHatchPattern *hatch_patterns
);
/* dxf_hatch_pattern_def_line functions. */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_new ();
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_init
(
        DxfHatchPatternDefLine *def_line
);
int
dxf_hatch_pattern_def_line_write
(
        DxfFile *fp,
        DxfHatchPatternDefLine *def_line
);
int
dxf_hatch_pattern_def_line_free
(
        DxfHatchPatternDefLine *def_line
);
void
dxf_hatch_pattern_def_line_free_chain
(
        DxfHatchPatternDefLine *hatch_pattern_def_lines
);
/* dxf_hatch_pattern_seedpoint functions. */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_new ();
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_init
(
        DxfHatchPatternSeedPoint *seedpoint
);
int
dxf_hatch_pattern_seedpoint_write
(
        DxfFile *fp,
        DxfHatchPatternSeedPoint *seedpoint
);
int
dxf_hatch_pattern_seedpoint_free
(
        DxfHatchPatternSeedPoint *seedpoint
);
void
dxf_hatch_pattern_seedpoint_free_chain
(
        DxfHatchPatternSeedPoint *hatch_pattern_seed_points
);
/* dxf_hatch_boundary_path functions. */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_new ();
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_init
(
        DxfHatchBoundaryPath *path
);
int
dxf_hatch_boundary_path_write
(
        DxfFile *fp,
        DxfHatchBoundaryPath *path
);
int
dxf_hatch_boundary_path_free
(
        DxfHatchBoundaryPath *path
);
void
dxf_hatch_boundary_path_free_chain
(
        DxfHatchBoundaryPath *hatch_boundary_paths
);
/* dxf_hatch_boundary_path_polyline functions. */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_new ();
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_init
(
        DxfHatchBoundaryPathPolyline *polyline
);
int
dxf_hatch_boundary_path_polyline_write
(
        DxfFile *fp,
        DxfHatchBoundaryPathPolyline *polyline
);
int
dxf_hatch_boundary_path_polyline_free
(
        DxfHatchBoundaryPathPolyline *polyline
);
void
dxf_hatch_boundary_path_polyline_free_chain
(
        DxfHatchBoundaryPathPolyline *hatch_boundary_path_polylines
);
int
dxf_hatch_boundary_path_polyline_close_polyline
(
        DxfHatchBoundaryPathPolyline *polyline
);
int
dxf_hatch_boundary_path_polyline_point_inside_polyline
(
        DxfHatchBoundaryPathPolyline *polyline,
        DxfPoint *point
);
/* dxf_hatch_boundary_pathPolyline_vertex functions. */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_new ();
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_init
(
        DxfHatchBoundaryPathPolylineVertex *vertex
);
int
dxf_hatch_boundary_path_polyline_vertex_write
(
        DxfFile *fp,
        DxfHatchBoundaryPathPolylineVertex *vertex
);
int
dxf_hatch_boundary_path_polyline_vertex_free
(
        DxfHatchBoundaryPathPolylineVertex *vertex
);
void
dxf_hatch_boundary_path_polyline_vertex_free_chain
(
        DxfHatchBoundaryPathPolylineVertex *hatch_boundary_path_polyline_vertices
);
double
dxf_hatch_boundary_path_polyline_vertex_angle
(
        DxfHatchBoundaryPathPolylineVertex *vertex_0,
        DxfHatchBoundaryPathPolylineVertex *vertex_1
);
/* dxf_hatch_boundary_path_edge functions. */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_new ();
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_init
(
        DxfHatchBoundaryPathEdge *edge
);
int
dxf_hatch_boundary_path_edge_free
(
        DxfHatchBoundaryPathEdge *edge
);
void
dxf_hatch_boundary_path_edge_free_chain
(
        DxfHatchBoundaryPathEdge *hatch_boundary_path_edges
);
/* dxf_hatch_boundary_path_edge_arc functions. */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_new ();
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_init
(
        DxfHatchBoundaryPathEdgeArc *arc
);
int
dxf_hatch_boundary_path_edge_arc_free
(
        DxfHatchBoundaryPathEdgeArc *arc
);
void
dxf_hatch_boundary_path_edge_arc_free_chain
(
        DxfHatchBoundaryPathEdgeArc *hatch_boundary_path_edge_arcs
);
int
dxf_hatch_boundary_path_edge_arc_get_id_code
(
        DxfHatchBoundaryPathEdgeArc *arc
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_id_code
(
        DxfHatchBoundaryPathEdgeArc *arc,
        int id_code
);
DxfPoint *
dxf_hatch_boundary_path_edge_arc_get_center_point
(
        DxfHatchBoundaryPathEdgeArc *arc,
        int id_code
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_center_point
(
        DxfHatchBoundaryPathEdgeArc *arc,
        DxfPoint *point
);
double
dxf_hatch_boundary_path_edge_arc_get_radius
(
        DxfHatchBoundaryPathEdgeArc *arc
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_radius
(
        DxfHatchBoundaryPathEdgeArc *arc,
        double radius
);
double
dxf_hatch_boundary_path_edge_arc_get_start_angle
(
        DxfHatchBoundaryPathEdgeArc *arc
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_start_angle
(
        DxfHatchBoundaryPathEdgeArc *arc,
        double start_angle
);
double
dxf_hatch_boundary_path_edge_arc_get_end_angle
(
        DxfHatchBoundaryPathEdgeArc *arc
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_end_angle
(
        DxfHatchBoundaryPathEdgeArc *arc,
        double end_angle
);
int
dxf_hatch_boundary_path_edge_arc_get_is_ccw
(
        DxfHatchBoundaryPathEdgeArc *arc
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_is_ccw
(
        DxfHatchBoundaryPathEdgeArc *arc,
        int is_ccw
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_get_next
(
        DxfHatchBoundaryPathEdgeArc *arc
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_next
(
        DxfHatchBoundaryPathEdgeArc *arc,
        DxfHatchBoundaryPathEdgeArc *next
);
/* dxf_hatch_boundary_path_edge_ellipse functions. */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_new ();
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_init
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
);
int
dxf_hatch_boundary_path_edge_ellipse_free
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
);
void
dxf_hatch_boundary_path_edge_ellipse_free_chain
(
        DxfHatchBoundaryPathEdgeEllipse *hatch_boundary_path_edge_ellipses
);
int
dxf_hatch_boundary_path_edge_ellipse_get_id_code
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_id_code
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        int id_code
);
DxfPoint *
dxf_hatch_boundary_path_edge_ellipse_get_center_point
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        int id_code
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_center_point
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        DxfPoint *point
);
DxfPoint *
dxf_hatch_boundary_path_edge_ellipse_get_end_point
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        int id_code
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_end_point
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        DxfPoint *point
);
double
dxf_hatch_boundary_path_edge_ellipse_get_ratio
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_ratio
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        double ratio
);
double
dxf_hatch_boundary_path_edge_ellipse_get_start_angle
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_start_angle
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        double start_angle
);
double
dxf_hatch_boundary_path_edge_ellipse_get_end_angle
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_end_angle
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        double end_angle
);
int
dxf_hatch_boundary_path_edge_ellipse_get_is_ccw
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_is_ccw
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        int is_ccw
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_get_next
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_next
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
        DxfHatchBoundaryPathEdgeEllipse *next
);
/* dxf_hatch_boundary_path_edge_line functions. */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_new ();
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_init
(
        DxfHatchBoundaryPathEdgeLine *line
);
int
dxf_hatch_boundary_path_edge_line_free
(
        DxfHatchBoundaryPathEdgeLine *line
);
void
dxf_hatch_boundary_path_edge_line_free_chain
(
        DxfHatchBoundaryPathEdgeLine *hatch_boundary_path_edge_lines
);
int
dxf_hatch_boundary_path_edge_line_get_id_code
(
        DxfHatchBoundaryPathEdgeLine *line
);
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_id_code
(
        DxfHatchBoundaryPathEdgeLine *line,
        int id_code
);
DxfPoint *
dxf_hatch_boundary_path_edge_line_get_start_point
(
        DxfHatchBoundaryPathEdgeLine *line,
        int id_code
);
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_start_point
(
        DxfHatchBoundaryPathEdgeLine *line,
        DxfPoint *point
);
DxfPoint *
dxf_hatch_boundary_path_edge_line_get_end_point
(
        DxfHatchBoundaryPathEdgeLine *line,
        int id_code
);
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_end_point
(
        DxfHatchBoundaryPathEdgeLine *line,
        DxfPoint *point
);
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_get_next
(
        DxfHatchBoundaryPathEdgeLine *line
);
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_next
(
        DxfHatchBoundaryPathEdgeLine *line,
        DxfHatchBoundaryPathEdgeLine *next
);
/* dxf_hatch_boundary_path_edge_spline functions. */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_new ();
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_init
(
        DxfHatchBoundaryPathEdgeSpline *spline
);
int
dxf_hatch_boundary_path_edge_spline_free
(
        DxfHatchBoundaryPathEdgeSpline *spline
);
void
dxf_hatch_boundary_path_edge_spline_free_chain
(
        DxfHatchBoundaryPathEdgeSpline *hatch_boundary_path_edge_splines
);
int
dxf_hatch_boundary_path_edge_spline_append_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        DxfHatchBoundaryPathEdgeSplineCp *control_point
);
int
dxf_hatch_boundary_path_edge_spline_prepend_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        DxfHatchBoundaryPathEdgeSplineCp *control_point
);
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_get_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        int position
);
int
dxf_hatch_boundary_path_edge_spline_set_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        int position,
        DxfHatchBoundaryPathEdgeSplineCp *control_point
);
int
dxf_hatch_boundary_path_edge_spline_insert_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        int position,
        DxfHatchBoundaryPathEdgeSplineCp *control_point
);
int
dxf_hatch_boundary_path_edge_spline_remove_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        int position
);
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_copy_control_points
(
        DxfHatchBoundaryPathEdgeSpline *spline
);
int
dxf_hatch_boundary_path_edge_spline_append_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        double knot_value
);
int
dxf_hatch_boundary_path_edge_spline_prepend_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        double knot_value
);
double
dxf_hatch_boundary_path_edge_spline_get_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        int position
);
int
dxf_hatch_boundary_path_edge_spline_set_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        int position,
        double knot_value
);
int
dxf_hatch_boundary_path_edge_spline_insert_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        int position,
        double knot_value
);
int
dxf_hatch_boundary_path_edge_spline_remove_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        int position
);
int
dxf_hatch_boundary_path_edge_spline_copy_knot_values
(
        DxfHatchBoundaryPathEdgeSpline *spline,
        double *knot_values[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]
);
/* dxf_hatch_boundary_path_edge_splie_control_point functions. */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_control_point_new ();
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_control_point_init
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
);
int
dxf_hatch_boundary_path_edge_spline_control_point_free
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
);
void
dxf_hatch_boundary_path_edge_spline_control_point_free_chain
(
        DxfHatchBoundaryPathEdgeSplineCp *hatch_boundary_path_edge_spline_control_points
);
int
dxf_hatch_boundary_path_edge_spline_cp_get_id_code
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
);
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_set_id_code
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point,
        int id_code
);


#endif /* LIBDXF_SRC_HATCH_H */


/* EOF */
