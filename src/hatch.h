/*!
 * \file hatch.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF hatch entity (\c HATCH).
 *
 * \warning The hatch entity requires AutoCAD version R14 or higher.\n
 *
 * \htmlinclude "../doc/hatch.html"
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


#include "global.h"


#define DXF_MAX_HATCH_PATTERN_DEF_LINE_DASH_ITEMS 16


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge arc.
 */
typedef struct
dxf_hatch_boundary_path_edge_arc
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = 10\n
                 * X-value of center point coordinate. */
        double y0;
                /*!< group code = 20\n
                 * Y-value of center point coordinate. */
        double radius;
                /*!< group code = 40. */
        double start_angle;
                /*!< group code = 50. */
        double end_angle;
                /*!< group code = 51. */
        int is_ccw;
                /*!< group code = 73\n
                 * arc is counterclockwise flag. */
        struct DxfHatchBoundaryPathEdgeArc *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeArc.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeArc. */
} DxfHatchBoundaryPathEdgeArc, * DxfHatchBoundaryPathEdgeArcPtr;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge ellipse.
 */
typedef struct
dxf_hatch_boundary_path_edge_ellipse
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = 10\n
                 * X-value of center point coordinate. */
        double y0;
                /*!< group code = 20\n
                 * Y-value of center point coordinate. */
        double x1;
                /*!< group code = 11\n
                 * X-value of end point coordinate of major axis (relative to
                 * center point. */
        double y1;
                /*!< group code = 21\n
                 * Y-value of end point coordinate of major axis (relative to
                 * center point. */
        double minor_axis;
                /*!< group code = 40\n
                 * length of minor axis (percentage of major axis length). */
        double start_angle;
                /*!< group code = 50. */
        double end_angle;
                /*!< group code = 51. */
        int is_ccw;
                /*!< group code = 73\n
                 * ellipse is counterclockwise flag. */
        struct DxfHatchBoundaryPathEdgeEllipse *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeEllipse.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeEllipse. */
} DxfHatchBoundaryPathEdgeEllipse, * DxfHatchBoundaryPathEdgeEllipsePtr;


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
} DxfHatchBoundaryPathEdgeLine, * DxfHatchBoundaryPathEdgeLinePtr;


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
        int knots;
                /*!< group code = 95\n
                 * number of knots. */
        int control_points;
                /*!< group code = 96\n
                 * number of control points. */
        struct DxfHatchBoundaryPathEdgeSpline *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeSpline.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeSpline. */
} DxfHatchBoundaryPathEdgeSpline, * DxfHatchBoundaryPathEdgeSplinePtr;


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
                /*!< group code = 10. */
        double y0;
                /*!< group code = 20. */
        double weight;
                /*!< group code = 42\n
                 * optional, defaults to 1.0. */
        struct DxfHatchBoundaryPathEdgeSplineCp *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeSplineCp.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeSplineCp. */
} DxfHatchBoundaryPathEdgeSplineCp, * DxfHatchBoundaryPathEdgeSplineCpPtr;


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
} DxfHatchBoundaryPathEdge, * DxfHatchBoundaryPathEdgePtr;


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
                 * array of hatch pattern definition line angles. */
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
} DxfHatchPatternDefLine, * DxfHatchPatternDefLinePtr;


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
                /*!< pointer to array of hatch pattern definition lines. */
        double **length;
                /*!< group code = 49\n
                 * array of dash lengths for an array of hatch pattern
                 * definition lines. */
        struct DxfHatchPattern *next;
                /*!< pointer to the next DxfHatchPattern.\n
                 * \c NULL if the last DxfHatchPattern. */
} DxfHatchPattern, * DxfHatchPatternPtr;


/*!
 * \brief DXF definition of an AutoCAD hatch seed point.
 */
typedef struct
dxf_hatch_seed_point
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = 10\n
                 * seed point X-value. */
        double y0;
                /*!< group code = 20\n
                 * seed point Y-value. */
        struct DxfHatchSeedPoint *next;
                /*!< pointer to the next DxfHatchSeedPoint.\n
                 * \c NULL if the last DxfHatchSeedPoint. */
} DxfHatchSeedPoint, * DxfHatchSeedPointPtr;


/*!
 * \brief DXF definition of an AutoCAD hatch entity.
 */
typedef struct
dxf_hatch
{
        char *pattern_name;
                /*!< group code = 2. */
        int id_code;
                /*!< group code = 5. */
        char *linetype;
                /*!< group code = 6\n
                 * optional, defaults to BYLAYER. */
        char *layer;
                /*!< group code = 8. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
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
        double thickness;
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double hatch_pattern_scale;
                /*!< group code 41\n
                 * pattern fill only. */
        double pixel_size;
                /*!< group code 47 */
        double hatch_pattern_angle;
                /*!< group code 52\n
                 * pattern fill only. */
        int color;
                /*!< group code = 62\n
                 * optional, defaults to BYLAYER. */
        int paperspace;
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int solid_fill;
                /*!< group code = 70\n
                 * 0 = pattern fill\n
                 * 1 = solid fill. */
        int associative;
                /*!< group code = 71\n
                 * 0 = non-associative\n
                 * 1 = associative. */
        int style;
                /*!< group code = 75\n
                 * 0 = hatch "odd parity" area (Normal style)\n
                 * 1 = hatch outermost area only (Outer style)\n
                 * 2 = hatch through entire area (Ignore style). */
        int pattern_style;
                /*!< group code = 76\n
                 * 0 = user defined\n
                 * 1 = predefined\n
                 * 2 = custom. */
        int pattern_double;
                /*!< group code = 77\n
                 * pattern fill only\n
                 * 0 = not double\n
                 * 1 = double. */
        int pattern_def_lines;
                /*!< group code = 78\n
                 * number of pattern definition lines. */
        int boundary_paths;
                /*!< group code = 91\n
                 * number of boundary paths (loops). */
        int seed_points;
                /*!< group code = 98\n
                 * number of seed points. */
        struct DxfHatchSeedPoint *points;
                /*!< pointer to the  DxfHatchSeedPoints. */
        struct DxfHatch *next;
                /*!< pointer to the next DxfHatch.\n
                 * \c NULL if the last DxfHatch. */
} DxfHatch, * DxfHatchPtr;


int
dxf_hatch_write
(
        FILE *fp,
        char *pattern_name,
        int id_code,
        char *linetype,
        char *layer,
        double x0,
        double y0,
        double z0,
        double extr_x0,
        double extr_y0,
        double extr_z0,
        double thickness,
        double pattern_scale,
        double pixel_size,
        double pattern_angle,
        int color,
        int paperspace,
        int solid_fill,
        int associative,
        int style,
        int pattern_style,
        int pattern_double,
        int pattern_def_lines,
        int pattern_boundary_paths,
        int seed_points,
                double *seed_x0,
                double *seed_y0
);
int
dxf_hatch_write_boundaries
(
        FILE *fp,
        int hatch_boundary_paths,
        int hatch_boundary_path_type_flag,
                int hatch_boundary_path_edges,
                int hatch_boundary_path_edge_type,
                        double hatch_boundary_path_edge_line_x0,
                        double hatch_boundary_path_edge_line_y0,
                        double hatch_boundary_path_edge_line_x1,
                        double hatch_boundary_path_edge_line_y1,
                        double hatch_boundary_path_edge_arc_x0,
                        double hatch_boundary_path_edge_arc_y0,
                        double hatch_boundary_path_edge_arc_radius,
                        double hatch_boundary_path_edge_arc_start_angle,
                        double hatch_boundary_path_edge_arc_end_angle,
                        int hatch_boundary_path_edge_arc_is_ccw,
                        double hatch_boundary_path_edge_ellipse_x0,
                        double hatch_boundary_path_edge_ellipse_y0,
                        double hatch_boundary_path_edge_ellipse_x1,
                        double hatch_boundary_path_edge_ellipse_y1,
                        double boundary_path_edge_ellipse_minor_axis,
                        double hatch_boundary_path_edge_ellipse_start_angle,
                        double hatch_boundary_path_edge_ellipse_end_angle,
                        int hatch_boundary_path_edge_ellipse_is_ccw,
                        int hatch_boundary_path_edge_spline_degree,
                        int hatch_boundary_path_edge_spline_rational,
                        int hatch_boundary_path_edge_spline_periodic,
                        int hatch_boundary_path_edge_spline_knots,
                        int hatch_boundary_path_edge_spline_control_points,
                                int *hatch_boundary_path_edge_spline_knot_value,
                                double *hatch_boundary_path_edge_spline_cp_x0,
                                double *hatch_boundary_path_edge_spline_cp_y0,
                                double *hatch_boundary_path_edge_spline_cp_weight,
                int hatch_boundary_path_polyline_has_bulge,
                int hatch_boundary_path_polyline_is_closed,
                int hatch_boundary_path_polyline_vertices,
                        double *hatch_boundary_path_polyline_x0,
                        double *hatch_boundary_path_polyline_y0,
                        double *hatch_boundary_path_polyline_bulge,
        int hatch_boundary_objects,
        char *hatch_boundary_objects_ref
);
int
dxf_hatch_write_boundary_path_polyline (FILE *fp,
                                            int has_bulge,
                                            int is_closed,
                                            int vertices,
                                            double *x0,
                                            double *y0,
                                            double *bulge );
int
dxf_hatch_write_boundary_path_polyline_vertex
(
        FILE *fp,
        double x0,
        double y0,
        double bulge
);
int
dxf_hatch_write_pattern_data
(
        FILE *fp,
        int def_lines,
        double *def_line_angle,
        double *def_line_x0,
        double *def_line_y0,
        double *def_line_x1,
        double *def_line_y1,
        int *def_line_dash_items,
        double **def_line_dash_length
);


/* EOF */
