/*!
 * \file hatch.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF hatch entity (\c HATCH).
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


#include "hatch.h"


/*!
 * \brief Allocate memory for a DXF \c HATCH.
 *
 * Fill the memory contents with zeros.
 */
DxfHatch *
dxf_hatch_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatch *hatch = NULL;
        size_t size;

        size = sizeof (DxfHatch);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((hatch = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatch struct.\n")),
                  __FUNCTION__);
                hatch = NULL;
        }
        else
        {
                memset (hatch, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH pattern.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchPattern *
dxf_hatch_pattern_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchPattern *pattern = NULL;
        size_t size;

        size = sizeof (DxfHatchPattern);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((pattern = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchPatternSeedpoint struct.\n")),
                  __FUNCTION__);
                pattern = NULL;
        }
        else
        {
                memset (pattern, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH pattern definition line.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchPatternDefLine *def_line = NULL;
        size_t size;

        size = sizeof (DxfHatchPatternDefLine);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((def_line = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchPatternDefLine struct.\n")),
                  __FUNCTION__);
                def_line = NULL;
        }
        else
        {
                memset (def_line, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (def_line);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH pattern seedpoint.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchPatternSeedPoint *seedpoint = NULL;
        size_t size;

        size = sizeof (DxfHatchPatternSeedPoint);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((seedpoint = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchPatternSeedpoint struct.\n")),
                  __FUNCTION__);
                seedpoint = NULL;
        }
        else
        {
                memset (seedpoint, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seedpoint);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPath *path = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPath);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((path = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPath struct.\n")),
                  __FUNCTION__);
                path = NULL;
        }
        else
        {
                memset (path, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path polyline.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolyline *polyline = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathPolyline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((polyline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathPolyline struct.\n")),
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
 * \brief Allocate memory for a DXF \c HATCH boundary path polyline
 * vertex.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolylineVertex *vertex = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathPolylineVertex);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((vertex = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathPolylineVertex struct.\n")),
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
 * \brief Allocate memory for a DXF \c HATCH boundary path edge.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdge *edge = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdge);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((edge = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdge struct.\n")),
                  __FUNCTION__);
                edge = NULL;
        }
        else
        {
                memset (edge, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge arc.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeArc *arc = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeArc);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((arc = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeArc struct.\n")),
                  __FUNCTION__);
                arc = NULL;
        }
        else
        {
                memset (arc, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge ellipse.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeEllipse *ellipse = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeEllipse);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ellipse = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeEllipse struct.\n")),
                  __FUNCTION__);
                ellipse = NULL;
        }
        else
        {
                memset (ellipse, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge line.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeLine *line = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeLine);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((line = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeLine struct.\n")),
                  __FUNCTION__);
                line = NULL;
        }
        else
        {
                memset (line, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge spline.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeSpline *spline = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeSpline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((spline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeSpline struct.\n")),
                  __FUNCTION__);
                spline = NULL;
        }
        else
        {
                memset (spline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge spline
 * control point.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_control_point_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeSplineCp *control_point = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeSplineCp);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((control_point = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeSplineCp struct.\n")),
                  __FUNCTION__);
                control_point = NULL;
        }
        else
        {
                memset (control_point, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatch *
dxf_hatch_init
(
        DxfHatch *hatch
                /*!< DXF hatch entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                hatch = dxf_hatch_new ();
        }
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatch struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->id_code = 0;
        hatch->linetype = strdup (DXF_DEFAULT_LINETYPE);
        hatch->layer = strdup (DXF_DEFAULT_LAYER);
        hatch->x0 = 0.0;
        hatch->y0 = 0.0;
        hatch->z0 = 0.0;
        hatch->extr_x0 = 0.0;
        hatch->extr_y0 = 0.0;
        hatch->extr_z0 = 0.0;
        hatch->thickness = 0.0;
        hatch->pattern_scale = 1.0;
        hatch->pixel_size = 1.0;
        hatch->pattern_angle = 0.0;
        hatch->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        hatch->visibility = DXF_DEFAULT_VISIBILITY;
        hatch->color = DXF_COLOR_BYLAYER;
        hatch->paperspace = DXF_MODELSPACE;
        hatch->solid_fill = 0;
        hatch->associative = 1;
        hatch->hatch_style = 0;
        hatch->hatch_pattern_type = 0;
        hatch->pattern_double = 0;
        hatch->number_of_pattern_def_lines = 0;
        hatch->def_lines = NULL;
        hatch->number_of_boundary_paths = 0;
        hatch->paths = NULL;
        hatch->number_of_seed_points = 0;
        hatch->seed_points = NULL;
        hatch->graphics_data_size = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                hatch->binary_graphics_data[i] = strdup ("");
        }
        hatch->dictionary_owner_soft = strdup ("");
        hatch->dictionary_owner_hard = strdup ("");
        hatch->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * pattern entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchPattern *
dxf_hatch_pattern_init
(
        DxfHatchPattern *pattern
                /*!< DXF hatch pattern entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                pattern = dxf_hatch_pattern_new ();
        }
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchPattern struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        pattern->id_code = 0;
        pattern->def_lines = 0;
        pattern->lines = NULL;
/*! \todo correction in:
        pattern->length = 0.0;
*/
        pattern->number_of_seed_points = 0;
        pattern->seed_points = NULL;
        pattern->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * pattern definition line entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_init
(
        DxfHatchPatternDefLine *def_line
                /*!< DXF hatch pattern definition line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (def_line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                def_line = dxf_hatch_pattern_def_line_new ();
        }
        if (def_line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchPatternDefLine struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        def_line->id_code = 0;
        def_line->angle = 0.0;
        def_line->x0 = 0.0;
        def_line->y0 = 0.0;
        def_line->x1 = 0.0;
        def_line->y1 = 0.0;
        def_line->dash_items = DXF_MAX_HATCH_PATTERN_DEF_LINE_DASH_ITEMS;
        for (i = 0; i >= DXF_MAX_HATCH_PATTERN_DEF_LINE_DASH_ITEMS; i++)
        {
                def_line->dash_length[i] = 0.0;
        }
        def_line->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (def_line);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * pattern seedpoint entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_init
(
        DxfHatchPatternSeedPoint *seedpoint
                /*!< DXF hatch pattern seedpoint entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seedpoint == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                seedpoint = dxf_hatch_pattern_seedpoint_new ();
        }
        if (seedpoint == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchPatternSeedPoint struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        seedpoint->id_code = 0;
        seedpoint->x0 = 0.0;
        seedpoint->y0 = 0.0;
        seedpoint->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seedpoint);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_init
(
        DxfHatchBoundaryPath *path
                /*!< DXF hatch boundary path entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                path = dxf_hatch_boundary_path_new ();
        }
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPath struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        path->id_code = 0;
        path->edges = NULL;
        path->polylines = NULL;
        path->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path polyline entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_init
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< DXF hatch boundary path polyline entity. */
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
                polyline = dxf_hatch_boundary_path_polyline_new ();
        }
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathPolyline struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->id_code = 0;
        polyline->bulge = 0.0;
        polyline->has_bulge = 0;
        polyline->is_closed = 0;
        polyline->number_of_vertices = 0;
        polyline->vertices = NULL;
        polyline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path polyline vertex entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_init
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< DXF hatch boundary path polyline vertex entity. */
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
                vertex = dxf_hatch_boundary_path_polyline_vertex_new ();
        }
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathPolylineVertex struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->id_code = 0;
        vertex->x0 = 0.0;
        vertex->y0 = 0.0;
        vertex->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_init
(
        DxfHatchBoundaryPathEdge *edge
                /*!< DXF hatch boundary path edge entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                edge = dxf_hatch_boundary_path_edge_new ();
        }
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdge struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        edge->id_code = 0;
        edge->arcs = NULL;
        edge->ellipses = NULL;
        edge->lines = NULL;
        edge->splines = NULL;
        edge->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge arc entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_init
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< DXF hatch boundary path edge arc entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                arc = dxf_hatch_boundary_path_edge_arc_new ();
        }
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeArc struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->id_code = 0;
        arc->x0 = 0.0;
        arc->y0 = 0.0;
        arc->radius = 0.0;
        arc->start_angle = 0.0;
        arc->end_angle = 0.0;
        arc->is_ccw = 0;
        arc->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge ellipse entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_init
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< DXF hatch boundary path edge ellipse entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ellipse = dxf_hatch_boundary_path_edge_ellipse_new ();
        }
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeEllipse struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->id_code = 0;
        ellipse->x0 = 0.0;
        ellipse->y0 = 0.0;
        ellipse->x1 = 0.0;
        ellipse->y1 = 0.0;
        ellipse->minor_axis = 0.0;
        ellipse->start_angle = 0.0;
        ellipse->end_angle = 0.0;
        ellipse->is_ccw = 0;
        ellipse->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge line entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_init
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< DXF hatch boundary path edge line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                line = dxf_hatch_boundary_path_edge_line_new ();
        }
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeLine struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->id_code = 0;
        line->x0 = 0.0;
        line->y0 = 0.0;
        line->x1 = 0.0;
        line->y1 = 0.0;
        line->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge spline entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_init
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< DXF hatch boundary path edge spline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spline = dxf_hatch_boundary_path_edge_spline_new ();
        }
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeSpline struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->id_code = 0;
        spline->degree = 0;
        spline->rational = 0;
        spline->periodic = 0;
        spline->number_of_knots = 0;
        for (i = 0; i >= DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS; i++)
        {
                spline->knots[i] = 0.0;
        }
        spline->number_of_control_points = 0;
        spline->control_points = NULL;
        spline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge spline control point entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_control_point_init
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF hatch boundary path edge spline control point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                control_point = dxf_hatch_boundary_path_edge_spline_control_point_new ();
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHatchBoundaryPathEdgeSplineCp struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        control_point->id_code = 0;
        control_point->x0 = 0.0;
        control_point->y0 = 0.0;
        control_point->weight = 0.0;
        control_point->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Append a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers, both the control point is
 * appended and the \c number_of_control_points is increased by 1.\n
 * \n
 * <h3>Example:</h3>
 * Start situation: a spline with 4 control points, and the control
 * point \c control_point that is to be appended.\n
 * \n
\dot
digraph start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  control_point [shape=record,label="<f0>control_point|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 * \n
 * Finished situation: a spline with the appended fifth control point,
 * the memory for control point \c control_point is freed and set to
 * \c NULL.\n
 * \n
\dot
digraph finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  appended [shape=record,label="<f0>appended|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
  cp4:f1 -> appended:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 *
 * \warning The pointer to the control point \c control_point is freed
 * and set to NULL.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_append_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control point
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline_cp.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so append the first control
                 * point. */
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) control_point;
        }
        else
        {
                /* iterate through all existing pointers to control
                 * points until the pointer to the last control point
                 * containing a NULL ponter in it's "next" member is
                 * found. */
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (;;)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                        if (iter->next == NULL)
                        {
                                break;
                        }
                }
                /* "iter" now contains the pointer to the last known
                 * control point, now we can write the pointer to the
                 * control point that has to be appended in the "next"
                 * member. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                iter->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
                spline->number_of_control_points++;
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (control_point);
                control_point = NULL;
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Append a knot value to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow,
 * both the knot value is appended and the \c number_of_knots is
 * increased by 1.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_append_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        double knot_value
                /*!< knot value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((spline->number_of_knots + 1) > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        spline->knots[spline->number_of_knots + 1] = knot_value;
        spline->number_of_knots++;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Prepend a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers the new control point is
 * prepended and the \c number_of_control_points is increased by 1.\n
 * \n
 * <h3>Example:</h3>
 * Start situation: a spline with 4 control points, and the control
 * point \c control_point that is to be prepended.\n
 * \n
\dot
digraph start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  control_point [shape=record,label="<f0>control_point|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 * \n
 * Finished situation: a spline with the prepended control point
 * totalling 5 control points, the memory for control point
 * \c control_point is freed and set to \c NULL.\n
 * \n
\dot
digraph finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  prepended [shape=record,label="<f0>prepended|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> prepended:f0 [arrowhead="open",style="dashed",color="purple"];
  prepended:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 * \warning The pointer to the control point \c control_point is freed
 * and set to NULL.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_prepend_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control point
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline_cp.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so prepend the first control
                 * point. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
        }
        else
        {
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = spline->control_points;
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
        }
        spline->number_of_control_points++;
        /* clean up. */
        dxf_hatch_boundary_path_edge_spline_control_point_free (control_point);
        control_point = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Prepend a knot value to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, all
 * the \c knots[] values are shifted one position up, the knot value is
 * prepended and the \c number_of_knots is increased by 1.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_prepend_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        double knot_value
                /*!< knot value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((spline->number_of_knots + 1) > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = spline->number_of_knots; i > 0; i--)
        {
                spline->knots[i + 1] = spline->knots[i];
        }
        spline->knots[0] = knot_value;
        spline->number_of_knots++;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers, a pointer to the requested control
 * point is returned.
 *
 * \return a pointer to the requested control point.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_get_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position
                /*!< position of the DXF \c HATCH boundary path edge
                 * spline control point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeSplineCp *control_point = NULL;
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (position <= 0)
        {
                fprintf (stderr,
                  (_("Error in %s () received an invalid value in position.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->number_of_control_points <= position)
        {
                fprintf (stderr,
                  (_("Error in %s () position is greater than the number of control points.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                /* iterate through existing pointers to control points
                 * until the pointer to the requested control point is
                 * reached. */
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                control_point = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (i = 1; i <= position; i++)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                }
                /* "iter" now contains a pointer in "iter->next" to the
                 * requested control point, now we can write the pointer
                 * to control_point and return the pointer value. */
                control_point =  (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Get a knot value from a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, the
 * desired knot value at \c position is returned.
 *
 * \return the knot value.
 */
double
dxf_hatch_boundary_path_edge_spline_get_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position
                /*!< position in the array of knot values [0 .. DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double knot_value;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position <= 0)
        {
                fprintf (stderr,
                  (_("Error in %s () received an invalid value in position.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in  %s () received a position greater than DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        knot_value = spline->knots[position];
#if DEBUG
        DXF_DEBUG_END
#endif
        return (knot_value);
}


/*!
 * \brief Set a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers, the control point is set at the
 * requested position.
 *
 * \warning The pointer to the control point \c cp is freed and set to
 * \c NULL.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_set_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position,
                /*!< position of the DXF \c HATCH boundary path edge
                 * spline control point entity. */
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control
                 * point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position <= 0)
        {
                fprintf (stderr,
                  (_("Error in %s () received an invalid value in position.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in control_point.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->number_of_control_points <= position)
        {
                fprintf (stderr,
                  (_("Error in %s () position is greater than the number of control points.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so set at the first control
                 * point pointer. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
        }
        else
        {
                /* iterate through existing pointers to control points
                 * until the pointer to the requested control point is
                 * reached. */
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (i = 1; i <= position; i++)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                }
                /* "iter" now contains a pointer in "iter->next" to the
                 * requested control point, now we can write the pointer
                 * to control_point and return the pointer value. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                iter->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
                dxf_hatch_boundary_path_edge_spline_control_point_free (control_point);
                control_point = NULL;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Set a knot value to a \c HATCH boundary path edge spline entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, the
 * desired knot value at \c position is set.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_set_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position,
                /*!< position in the array of knot values [0 .. DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]. */
        double knot_value
                /*!< knot value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position <= 0)
        {
                fprintf (stderr,
                  (_("Error in %s () received an invalid value in position.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () received a position greater than DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        spline->knots[position] = knot_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Insert a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers, insert the requested control
 * point at the requested position.\n
 * \n
 * <h3>Example:</h3>
 * Start situation: a spline with 4 control points, and the control
 * point \c control_point that is to be inserted.\n
 * \n
 *
\dot
digraph start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  control_point [shape=record,label="<f0>control_point|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 * \n
 * Finished situation: a spline with the inserted control point between
 * control points cp2 and cp3, totalling 5 control points, the memory
 * for control point \c control_point is freed and set to \c NULL.\n
 * \n
\dot
digraph finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  inserted [shape=record,label="<f0>inserted|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> inserted:f0 [arrowhead="open",style="dashed",color="purple"];
  inserted:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 *
 * \note There are two other possible and distinct scenarios, which
 * result in inserting at the first position (see "prepending"), or
 * result in inserting at the last position (see "appending").\n
 * Both these cases are addressed in this function (see comments in the
 * source code).
 *
 * \warning The pointer to the control point \c control_point is freed
 * and set to NULL.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_insert_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position,
                /*!< position of the DXF \c HATCH boundary path edge
                 * spline control point entity. */
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control
                 * point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position <= 0)
        {
                fprintf (stderr,
                  (_("Error in %s () received an invalid value in position.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () received a position greater than DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in control_point.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_control_points <= position)
        {
                fprintf (stderr,
                  (_("Error in %s () position is greater than the number of control points.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so insert a copy of "cp" at
                 * the first control point pointer. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
        }
        else
        {
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                DxfHatchBoundaryPathEdgeSplineCp *temp = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                temp = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                /* iterate through existing pointers to control points
                 * until the pointer to the requested control point is
                 * reached. */
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (i = 2; i <= position; i++)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                }
                /* "iter" now contains a pointer (in "iter->next") to
                 * the control point with the requested position.
                 * first we have to get a pointer to the next control
                 * point "downward" (if any) of the position of the
                 * requested control point and store this one in a
                 * temporary variable. */
                temp = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                if (temp == NULL)
                {
                        /* "iter" points to the last control point, just
                         * append a copy of "cp". */
                        DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                        new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                        new->id_code = control_point->id_code;
                        new->x0 = control_point->x0;
                        new->y0 = control_point->y0;
                        new->weight = control_point->weight;
                        new->next = NULL;
                        iter->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
                }
                else
                {
                        DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                        new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                        new->id_code = control_point->id_code;
                        new->x0 = control_point->x0;
                        new->y0 = control_point->y0;
                        new->weight = control_point->weight;
                        /* the next step is to connect the "downward chain" to
                         * the to be inserted "control_point->next". */
                        new->next = temp->next;
                        /* the final step is to connect the "upward chain" to
                         * the to be inserted control point. */
                        temp =  new;
                }
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (control_point);
                control_point = NULL;
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Insert a knot value into a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, all
 * the knot values upwards of \c knots[\c position] are shifted one
 * position,  the knot value is inserted at \c knots[\c position] and
 * the  \c number_of_knots is increased by 1.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_insert_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position,
                /*!< position in the array of knot values [0 .. DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]. */
        double knot_value
                /*!< knot value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((spline->number_of_knots + 1) > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position <= 0)
        {
                fprintf (stderr,
                  (_("Error in %s () received an invalid value in position.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position >= DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () received a position greater than DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = spline->number_of_knots; i <= position; i--)
        {
                spline->knots[i + 1] = spline->knots[i];
        }
        spline->knots[position] = knot_value;
        spline->number_of_knots++;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Remove a control point from a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers remove the requested control
 * point.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_remove_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position
                /*!< position of the DXF \c HATCH boundary path edge
                 * spline control point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position <= 0)
        {
                fprintf (stderr,
                  (_("Error in %s () received an invalid value in position.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position >= DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () received a position greater than DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_control_points <= position)
        {
                fprintf (stderr,
                  (_("Error in %s () position is greater than the number of control points.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so there is no control point to
                 * remove. */
                fprintf (stderr,
                  (_("Error in %s () spline contins no control points.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        else
        {
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                DxfHatchBoundaryPathEdgeSplineCp *temp = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                temp = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                /* iterate through existing pointers to control points
                 * until the pointer to the requested control point is
                 * reached. */
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (i = 0; i <= (position - 1); i++)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                        /* "iter" now contains a pointer to the control point
                         * prior to the requested position (the requested
                         * pointer is in "iter->next"). */
                }
                /* first we have to get a pointer to the next control
                 * point in the "downward chain" after the  position
                 * of the requested control point and store this one in
                 * a temporary variable. */
                temp = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                /* the next step is to connect the "downward chain" to
                 * the the contol point before the requested control
                 * point (the pointer to the last control point in the
                 * "upward chain" is in "iter"). */
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) temp->next;
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Remove a knot value from a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, all
 * the knot values upwards of \c knots[\c position] are shifted one
 * position down, and the \c number_of_knots is decreased by 1.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_remove_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position
                /*!< position in the array of knot values [0 .. DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_knots > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((spline->number_of_knots - 1) < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer underflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position <= 0)
        {
                fprintf (stderr,
                  (_("Error in %s () received an invalid value in position.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position >= DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () received a position greater than DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = position; i >= spline->number_of_knots; i++)
        {
                spline->knots[i] = spline->knots[i + 1];
        }
        spline->number_of_knots--;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Copy control points from a \c HATCH boundary path edge spline
 * entity into a new chain of control points.
 *
 * After testing for \c NULL pointers and size of the allocated memory,
 * a new chain of control points (destination) is setup by copying the
 * member values from the control points from the spline (source).\n
 * For each control point in the destination chain new memory is
 * allocated.\n
 * \n
 * <h3>Example:</h3>
 * Start situation: a spline with 4 control points, and the control
 * point \c control_points.\n
 * \n

\dot
digraph dxf_hatch_boundary_path_edge_spline_copy_control_points__spline_start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot

\dot
digraph dxf_hatch_boundary_path_edge_spline_copy_control_points__control_points_start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  control_points [shape=record,label="<f0>control_points|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
}
\enddot

 * \n
 * Finished situation: the unchanged \c spline with 4 control points,
 * and a chain of control points starting at \c control_points.\n
 * \n

\dot
digraph dxf_hatch_boundary_path_edge_spline_copy_control_points__spline_finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot

\dot
digraph dxf_hatch_boundary_path_edge_spline_copy_control_points__controlpoints_finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  control_points [shape=record,label="<f0>control_points=new_cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  new_cp2 [shape=record,label="<f0>new_cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  new_cp3 [shape=record,label="<f0>new_cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  new_cp4 [shape=record,label="<f0>new_cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  control_points:f1 -> new_cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  new_cp2:f1 -> new_cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  new_cp3:f1 -> new_cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot

 * \todo code needs to be checked !
 *
 \return a pointer to the first of the requested control points,
 * \c NULL if no control point was found.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_copy_control_points
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< DXF \c HATCH boundary path edge spline entity
                 * (source). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeSplineCp *control_point = NULL;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so there is no control point
                 * to copy. */
                fprintf (stderr,
                  (_("Error in %s () spline contains no control points.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                /* iterate through all existing pointers to control
                 * points until the pointer to the last control point
                 * containing a NULL pointer in it's "next" member is
                 * found. */
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                DxfHatchBoundaryPathEdgeSplineCp *iter_new = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                iter_new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                control_point = iter_new;
                for (;;)
                {
                        /* copy member contents into new control point. */
                        iter_new->id_code = iter->id_code;
                        iter_new->x0 = iter->x0;
                        iter_new->y0 = iter->y0;
                        iter_new->weight = iter->weight;
                        if (iter->next == NULL)
                        {
                                /* the last control point of the spline
                                 * is reached. */
                                iter_new->next = NULL;
                                break;
                        }
                        else
                        {
                                /* create a new control point in the chain. */
                                iter_new->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) dxf_hatch_boundary_path_edge_spline_control_point_new ();
                        }
                        /* set both iterators to the next control point
                         * in their chain. */
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                        iter_new = (DxfHatchBoundaryPathEdgeSplineCp *) iter_new->next;
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Copy knot values from a \c HATCH boundary path edge spline
 * entity into an array.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, all
 * the knot values from \c spline (source) are copied into an array
 * \c knot_values (destination).
 *
 * \warning Make sure enough memory is allocated for the destination
 * array.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_copy_knot_values
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity (source). */
        double *knot_values[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]
                /*!< Array of knot values (destination). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_knots > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = 0; i < spline->number_of_knots; i++)
        {
                *knot_values[i] = spline->knots[i];
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a hatch entity (\c HATCH).
 */
int
dxf_hatch_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfHatch *hatch
                /*!< DXF hatch entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("HATCH");
        int i;

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
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (hatch->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning: empty layer string for the %s entity with id-code: %x\n")),
                        dxf_entity_name, hatch->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0")),
                        dxf_entity_name);
                hatch->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (strcmp (hatch->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning: empty linetype string for the %s entity with id-code: %x\n")),
                        dxf_entity_name, hatch->id_code);
                fprintf (stderr,
                  (_("    %s entity is reset to default linetype")),
                        dxf_entity_name);
                hatch->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (hatch->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", hatch->id_code);
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
        if ((strcmp (hatch->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", hatch->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (hatch->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", hatch->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (hatch->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", hatch->layer);
        if (strcmp (hatch->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", hatch->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (hatch->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", hatch->elevation);
        }
        if (hatch->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", hatch->thickness);
        }
        if (hatch->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", hatch->color);
        }
        if (hatch->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", hatch->linetype_scale);
        }
        if (hatch->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", hatch->visibility);
        }
        if (hatch->graphics_data_size > 0)
        {
                fprintf (fp->fp, " 92\n%d\n", hatch->graphics_data_size);
        }
        i = 0;
        while (strlen (hatch->binary_graphics_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", hatch->binary_graphics_data[i]);
                i++;
        }
        fprintf (fp->fp, "100\nAcDbHatch\n");
        fprintf (fp->fp, " 10\n%f\n", hatch->x0);
        fprintf (fp->fp, " 20\n%f\n", hatch->y0);
        fprintf (fp->fp, " 30\n%f\n", hatch->z0);
        fprintf (fp->fp, "210\n%f\n", hatch->extr_x0);
        fprintf (fp->fp, "220\n%f\n", hatch->extr_y0);
        fprintf (fp->fp, "230\n%f\n", hatch->extr_z0);
        fprintf (fp->fp, "  2\n%s\n", hatch->pattern_name);
        fprintf (fp->fp, " 70\n%d\n", hatch->solid_fill);
        fprintf (fp->fp, " 71\n%d\n", hatch->associative);
        fprintf (fp->fp, " 91\n%d\n", hatch->number_of_boundary_paths);
        dxf_hatch_boundary_path_write (fp, (DxfHatchBoundaryPath *) hatch->paths);
        fprintf (fp->fp, " 75\n%d\n", hatch->hatch_style);
        fprintf (fp->fp, " 76\n%d\n", hatch->hatch_pattern_type);
        if (!hatch->solid_fill)
        {
                fprintf (fp->fp, " 52\n%f\n", hatch->pattern_angle);
                fprintf (fp->fp, " 41\n%f\n", hatch->pattern_scale);
                fprintf (fp->fp, " 77\n%d\n", hatch->pattern_double);
        }
        fprintf (fp->fp, " 78\n%d\n", hatch->number_of_pattern_def_lines);
        DxfHatchPatternDefLine *line = NULL;
        line = (DxfHatchPatternDefLine *) hatch->def_lines;
        while (line != NULL)
        {
                dxf_hatch_pattern_def_line_write (fp, (DxfHatchPatternDefLine *) line);
                line = (DxfHatchPatternDefLine *) line->next;
        }
        fprintf (fp->fp, " 47\n%f\n", hatch->pixel_size);
        fprintf (fp->fp, " 98\n%d\n", hatch->number_of_seed_points);
        DxfHatchPatternSeedPoint *point = NULL;
        point = (DxfHatchPatternSeedPoint *) hatch->seed_points;
        while (point != NULL)
        {
                dxf_hatch_pattern_seedpoint_write (fp, (DxfHatchPatternSeedPoint *) point);
                point = (DxfHatchPatternSeedPoint *) point->next;
        }
        /* Clean up. */
        dxf_hatch_pattern_def_line_free (line);
        dxf_hatch_pattern_seedpoint_free (point);
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c HATCH pattern definition
 * line.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_def_line_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHatchPatternDefLine *def_line
                /*!< DXF hatch pattern definition line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (def_line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, " 53\n%f\n", def_line->angle);
        fprintf (fp->fp, " 43\n%f\n", def_line->x0);
        fprintf (fp->fp, " 44\n%f\n", def_line->y0);
        fprintf (fp->fp, " 45\n%f\n", def_line->x1);
        fprintf (fp->fp, " 46\n%f\n", def_line->y1);
        fprintf (fp->fp, " 79\n%d\n", def_line->dash_items);
        if (def_line->dash_items > 0)
        {
                /* Draw hatch pattern definition line dash items. */
                for (i = 1; i < def_line->dash_items; i++)
                {
                        fprintf (fp->fp, " 49\n%f\n", def_line->dash_length[i]);
                }
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () no dash length found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c HATCH pattern seed
 * point.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_seedpoint_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHatchPatternSeedPoint *seedpoint
                /*!< DXF hatch pattern seedpoint. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seedpoint == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, " 10\n%f\n", seedpoint->x0);
        fprintf (fp->fp, " 20\n%f\n", seedpoint->y0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for hatch boundary entities.
 *
 * Requires AutoCAD version R14 or higher.
 */
int
dxf_hatch_boundary_path_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHatchBoundaryPath *path
                /*!< Pointer to DXF Boundary paths (loops). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolyline *iter;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        for (;;)
        {
                if (path->next == NULL)
                {
                        fprintf (stderr,
                          (_("Information from %s () last boundary path encountered.\n")),
                          __FUNCTION__);
                        break;
                }
                else
                {
                        /* Test for edge type or polylines type. */
                        if (path->edges != NULL)
                        {
                                /*! \todo Write edges data. */
                        }
                        else if (path->polylines != NULL)
                        {
                                iter = dxf_hatch_boundary_path_polyline_new ();
                                iter = (DxfHatchBoundaryPathPolyline *) path->polylines;
                                for (;;)
                                {
                                        dxf_hatch_boundary_path_polyline_write
                                        (
                                                fp,
                                                iter
                                        );
                                        iter = (DxfHatchBoundaryPathPolyline *) iter->next;
                                        if (iter == NULL)
                                        {
                                                break;
                                        }
                                }
                        }
                        else
                        {
                                fprintf (stderr,
                                  (_("Error in %s () unknown boundary path type encountered.\n")),
                                  __FUNCTION__);
                                return (EXIT_FAILURE);
                        }
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Return the angle between two vertices on a plane (2D).
 *
 * The angle is from \c vertex_0 to \c vertex_1, positive is
 * counterclockwise (CCW).
 *
 * \return The angle value is in the range (\f$ -\pi \cdots \pi \f$) in
 * radians.
 */
double
dxf_hatch_boundary_path_polyline_vertex_angle
(
        DxfHatchBoundaryPathPolylineVertex *vertex_0,
                /*!< The first vertex (of the pair). */
        DxfHatchBoundaryPathPolylineVertex *vertex_1
                /*!< The second vertex (of the pair). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double x0;
        double y0;
        double x1;
        double y1;
        double dtheta;
        double theta0;
        double theta1;

        /* Do some basic checks. */
        if (vertex_0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex_1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((vertex_0->x0 == vertex_1->x0)
          && (vertex_0->y0 == vertex_1->y0))
        {
                fprintf (stderr,
                  (_("Error in %s () identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        x0 = vertex_0->x0;
        y0 = vertex_0->y0;
        x1 = vertex_1->x0;
        y1 = vertex_1->y0;
        theta0 = atan2 (y0, x0);
        theta1 = atan2 (y1, x1);
        dtheta = theta1 - theta0;
        while (dtheta > M_PI)
                dtheta -= 2 * M_PI;
        while (dtheta < -M_PI)
        dtheta += 2 * M_PI;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dtheta);
}


/*!
 * \brief Write DXF output to a file for a hatch boundary polyline
 * vertex.
 */
int
dxf_hatch_boundary_path_polyline_vertex_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< DXF hatch boundary path polyline vertex entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        fprintf (fp->fp, " 10\n%f\n", vertex->x0);
        fprintf (fp->fp, " 20\n%f\n", vertex->y0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Test if a hatch boundary polyline is closed and add the missing
 * vertex.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_polyline_close_polyline
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< DXF hatch boundary path polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () invalid pointer to polyline (NULL).\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->is_closed == 0)
        {
                /* iterate over all vertices until the last vertex,
                 * append a new vertex with values of the first vertex,
                 * and set the "is_closed" member to 1. */
                DxfHatchBoundaryPathPolylineVertex *first;
                DxfHatchBoundaryPathPolylineVertex *iter;
                DxfHatchBoundaryPathPolylineVertex *next;
                first = dxf_hatch_boundary_path_polyline_vertex_new ();
                iter = dxf_hatch_boundary_path_polyline_vertex_new ();
                next = dxf_hatch_boundary_path_polyline_vertex_new ();
                first = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
                iter = first;
                for (;;)
                {
                        if (iter->next == NULL)
                        {
                                next = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                                break;
                        }
                        iter = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                }
                first = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
                 /*! \todo How do we know what's the last id_code ?
                  * This should be taken from a global id_code counter. */
                next->id_code = iter->id_code + 1;
                next->x0 = first->x0;
                next->y0 = first->y0;
                next->next = NULL;
                iter->next = (struct DxfHatchBoundaryPathPolylineVertex *) next;
                polyline->is_closed = 1;
        }
        else
        {
                /* iterate over all vertices until the last vertex,
                 * test if the values of the last are identical with the
                 * first vertex, if not: append a vertex with values of
                 * the first vertex. */
                DxfHatchBoundaryPathPolylineVertex *first;
                DxfHatchBoundaryPathPolylineVertex *iter;
                DxfHatchBoundaryPathPolylineVertex *next;
                first = dxf_hatch_boundary_path_polyline_vertex_new ();
                iter = dxf_hatch_boundary_path_polyline_vertex_new ();
                next = dxf_hatch_boundary_path_polyline_vertex_new ();
                first = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
                iter = first;
                for (;;)
                {
                        if (iter->next == NULL)
                        {
                                next = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                                break;
                        }
                        iter = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                }
                first = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
                if (iter->x0 != first->x0 && iter->y0 != first->y0)
                {
                        /* the first vertex coordinates are identical to
                         * the last vertex coordinates: do nothing and
                         * leave. */
                }
                else
                {
                        /*! \todo How do we know what's the last id_code ?
                         * This should be taken from a global id_code counter. */
                        next->id_code = iter->id_code + 1;
                        next->x0 = (double) first->x0;
                        next->y0 = first->y0;
                        next->next = NULL;
                        iter->next = (struct DxfHatchBoundaryPathPolylineVertex *) next;
                }
                /*! \todo add code here ! */
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Compute if the coordinates of a point \c p lie inside or
 * outside a DXF hatch boundary path polyline \c polyline entity.
 *
 * \author Paul Bourke <http://www.paulbourke.net/geometry/insidepoly/>\n
 * Adapted for libDXF by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * A solution by Philippe Reverdy is to compute the sum of the angles
 * made between the test point and each pair of points making up the
 * polygon.\n
 * If this sum is (\f$ 2\pi \f$) then the point is an interior point,
 * if 0 then the point is an exterior point.\n
 * This also works for polygons with holes given the polygon is defined
 * with a path made up of coincident edges into and out of the hole as
 * is common practice in many CAD packages.\n
 *
 * \note For most of the "point-in-polygon" algorithms there is a
 * pathological case if the point being queries lies exactly on a
 * vertex.\n
 * The easiest way to cope with this is to test that as a separate
 * process and make your own decision as to whether you want to consider
 * them inside or outside.
 *
 * \note It is assumed that the polygon is simple (does not intersect
 * itself).
 *
 * \return \c INSIDE if an interior point, \c OUTSIDE if an exterior
 * point, or \c EXIT_FAILURE if an error occurred.
 */
int
dxf_hatch_boundary_path_polyline_point_inside_polyline
(
        DxfHatchBoundaryPathPolyline *polyline,
                /*!< DXF hatch boundary path polyline entity. */
        DxfPoint *point
                /*!< The point to be tested for. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () invalid pointer to polyline (NULL).\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () invalid pointer to point (NULL).\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->is_closed != 1)
        {
                fprintf (stderr,
                  (_("Error in %s () polyline is not a closed polygon.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        DxfHatchBoundaryPathPolylineVertex *p0;
        DxfHatchBoundaryPathPolylineVertex *p1;
        DxfHatchBoundaryPathPolylineVertex *iter;
        DxfHatchBoundaryPathPolylineVertex *next;
        double angle;
        p0 = dxf_hatch_boundary_path_polyline_vertex_new ();
        p1 = dxf_hatch_boundary_path_polyline_vertex_new ();
        iter = dxf_hatch_boundary_path_polyline_vertex_new ();
        next = dxf_hatch_boundary_path_polyline_vertex_new ();
        iter = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
        next = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
        angle = 0;
        for (;;)
        {
                if (next == NULL)
                {
                        /* iter is the last vertex, no use to continue. */
                        break;
                }
                next = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                p0->x0 = iter->x0 - point->x0;
                p0->y0 = iter->y0 - point->y0;
                p1->x0 = next->x0 - point->x0;
                p1->y0 = next->y0 - point->y0;
                angle += dxf_hatch_boundary_path_polyline_vertex_angle (iter, next);
                iter = next;
        }
        /* clean up. */
        dxf_hatch_boundary_path_polyline_vertex_free (p0);
        dxf_hatch_boundary_path_polyline_vertex_free (p1);
        if (abs (angle) < M_PI)
                return (OUTSIDE);
        else
                return (INSIDE);
#if DEBUG
        DXF_DEBUG_END
#endif
        /*! \todo This is a dead code path. */
        return (EXIT_FAILURE);
}


/*!
 * \brief Write DXF output to a file for a hatch boundary path polyline.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_polyline_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfHatchBoundaryPathPolyline *polyline
                /*!< DXF hatch boundary path polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolylineVertex *iter;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        fprintf (fp->fp, " 72\n%d\n", polyline->has_bulge);
        fprintf (fp->fp, " 73\n%d\n", polyline->is_closed);
        fprintf (fp->fp, " 93\n%d\n", polyline->number_of_vertices);
        /* draw hatch boundary vertices. */
        iter = dxf_hatch_boundary_path_polyline_vertex_new ();
        iter = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
        for (;;)
        {
                dxf_hatch_boundary_path_polyline_vertex_write
                (
                        fp,
                        iter
                );
                iter = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                if (iter == NULL)
                {
                        break;
                }
        }
        /* test for closed polyline: close with first vertex. */
        if (polyline->is_closed)
        {
                dxf_hatch_boundary_path_polyline_vertex_write
                (
                        fp,
                        (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices
                );
        }
        if (polyline->bulge != 0.0)
        {
                fprintf (fp->fp, " 42\n%f\n", polyline->bulge);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_free
(
        DxfHatch *hatch
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatch was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (hatch->pattern_name);
        free (hatch->linetype);
        free (hatch->layer);
        free (hatch->def_lines);
        free (hatch->paths);
        free (hatch->seed_points);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (hatch->binary_graphics_data[i]);
        }
        free (hatch->dictionary_owner_soft);
        free (hatch->dictionary_owner_hard);
        free (hatch);
        hatch = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH pattern and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_free
(
        DxfHatchPattern *pattern
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * pattern entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (pattern->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchPattern was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (pattern->lines);
        free (pattern->seed_points);
        free (pattern);
        pattern = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH pattern
 * definition line and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_def_line_free
(
        DxfHatchPatternDefLine *def_line
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * pattern definition line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (def_line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (def_line->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchPatternDefLine was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (def_line);
        def_line = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH pattern seedpoint
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_seedpoint_free
(
        DxfHatchPatternSeedPoint *seedpoint
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * pattern seedpoint entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seedpoint == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seedpoint->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchPatternSeedPoint was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (seedpoint);
        seedpoint = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path and
 * all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_free
(
        DxfHatchBoundaryPath *path
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (path->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchBoundaryPath was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (path->edges);
        free (path->polylines);
        free (path);
        path = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * polyline and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_polyline_free
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path polyline entity. */
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
                  (_("Error in %s () pointer to next DxfHatchBoundaryPathPolyline was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (polyline->vertices);
        free (polyline);
        polyline = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * polyline vertex and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_polyline_vertex_free
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path polyline vertex entity. */
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
                  (_("Error in %s () pointer to next DxfHatchBoundaryPathPolylineVertex was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (vertex);
        vertex = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_free
(
        DxfHatchBoundaryPathEdge *edge
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (edge->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchBoundaryPathEdge was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (edge->arcs);
        free (edge->ellipses);
        free (edge->lines);
        free (edge->splines);
        free (edge);
        edge = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge arc and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_arc_free
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge arc entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchBoundaryPathEdgeArc was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (arc);
        arc = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge ellipse and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_ellipse_free
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge ellipse entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchBoundaryPathEdgeEllipse was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (ellipse);
        ellipse = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge line and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_line_free
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchBoundaryPathEdgeLine was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (line);
        line = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge spline and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_free
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge spline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchBoundaryPathEdgeSpline was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (spline->control_points);
        free (spline);
        spline = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge spline control point and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_control_point_free
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge spline control point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfHatchBoundaryPathEdgeSplineCp was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (control_point);
        control_point = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH
 * entities and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_free_chain
(
        DxfHatch *hatches
                /*!< pointer to the chain of DXF \c HATCH entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatches == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatches != NULL)
        {
                struct DxfHatch *iter = hatches->next;
                dxf_hatch_free (hatches);
                hatches = (DxfHatch *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH patterns
 * and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_pattern_free_chain
(
        DxfHatchPattern *hatch_patterns
                /*!< pointer to the chain of DXF \c HATCH patterns. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_patterns == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_patterns != NULL)
        {
                struct DxfHatchPattern *iter = hatch_patterns->next;
                dxf_hatch_pattern_free (hatch_patterns);
                hatch_patterns = (DxfHatchPattern *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH pattern
 * definition lines and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_pattern_def_line_free_chain
(
        DxfHatchPatternDefLine *hatch_pattern_def_lines
                /*!< pointer to the chain of DXF \c HATCH pattern
                 * definition lines. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_pattern_def_lines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_pattern_def_lines != NULL)
        {
                struct DxfHatchPatternDefLine *iter = hatch_pattern_def_lines->next;
                dxf_hatch_pattern_def_line_free (hatch_pattern_def_lines);
                hatch_pattern_def_lines = (DxfHatchPatternDefLine *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH pattern
 * seed points and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_pattern_seedpoint_free_chain
(
        DxfHatchPatternSeedPoint *hatch_pattern_seed_points
                /*!< pointer to the chain of DXF \c HATCH pattern seed
                 * points. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_pattern_seed_points == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_pattern_seed_points != NULL)
        {
                struct DxfHatchPatternSeedPoint *iter = hatch_pattern_seed_points->next;
                dxf_hatch_pattern_seedpoint_free (hatch_pattern_seed_points);
                hatch_pattern_seed_points = (DxfHatchPatternSeedPoint *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * paths and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_free_chain
(
        DxfHatchBoundaryPath *hatch_boundary_paths
                /*!< pointer to the chain of DXF \c HATCH boundary paths. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_paths == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_paths != NULL)
        {
                struct DxfHatchBoundaryPath *iter = hatch_boundary_paths->next;
                dxf_hatch_boundary_path_free (hatch_boundary_paths);
                hatch_boundary_paths = (DxfHatchBoundaryPath *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * path polylines and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_polyline_free_chain
(
        DxfHatchBoundaryPathPolyline *hatch_boundary_path_polylines
                /*!< pointer to the chain of DXF \c HATCH boundary path
                 * polylines. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_polylines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_polylines != NULL)
        {
                struct DxfHatchBoundaryPathPolyline *iter = hatch_boundary_path_polylines->next;
                dxf_hatch_boundary_path_polyline_free (hatch_boundary_path_polylines);
                hatch_boundary_path_polylines = (DxfHatchBoundaryPathPolyline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * path polyline vertices and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_polyline_vertex_free_chain
(
        DxfHatchBoundaryPathPolylineVertex *hatch_boundary_path_polyline_vertices
                /*!< pointer to the chain of DXF \c HATCH boundary path
                 * polyline vertices. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_polyline_vertices == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_polyline_vertices != NULL)
        {
                struct DxfHatchBoundaryPathPolylineVertex *iter = hatch_boundary_path_polyline_vertices->next;
                dxf_hatch_boundary_path_polyline_vertex_free (hatch_boundary_path_polyline_vertices);
                hatch_boundary_path_polyline_vertices = (DxfHatchBoundaryPathPolylineVertex *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * path edges and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_edge_free_chain
(
        DxfHatchBoundaryPathEdge *hatch_boundary_path_edges
                /*!< pointer to the chain of DXF \c HATCH boundary path
                 * edges. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edges == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edges != NULL)
        {
                struct DxfHatchBoundaryPathEdge *iter = hatch_boundary_path_edges->next;
                dxf_hatch_boundary_path_edge_free (hatch_boundary_path_edges);
                hatch_boundary_path_edges = (DxfHatchBoundaryPathEdge *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * path edge arcs and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_edge_arc_free_chain
(
        DxfHatchBoundaryPathEdgeArc *hatch_boundary_path_edge_arcs
                /*!< pointer to the chain of DXF \c HATCH boundary path
                 * edge arcs. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_arcs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_arcs != NULL)
        {
                struct DxfHatchBoundaryPathEdgeArc *iter = hatch_boundary_path_edge_arcs->next;
                dxf_hatch_boundary_path_edge_arc_free (hatch_boundary_path_edge_arcs);
                hatch_boundary_path_edge_arcs = (DxfHatchBoundaryPathEdgeArc *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * path edge ellipses and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_edge_ellipse_free_chain
(
        DxfHatchBoundaryPathEdgeEllipse *hatch_boundary_path_edge_ellipses
                /*!< pointer to the chain of DXF \c HATCH boundary path
                 * edge ellipses. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_ellipses == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_ellipses != NULL)
        {
                struct DxfHatchBoundaryPathEdgeEllipse *iter = hatch_boundary_path_edge_ellipses->next;
                dxf_hatch_boundary_path_edge_ellipse_free (hatch_boundary_path_edge_ellipses);
                hatch_boundary_path_edge_ellipses = (DxfHatchBoundaryPathEdgeEllipse *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * path edge lines and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_edge_line_free_chain
(
        DxfHatchBoundaryPathEdgeLine *hatch_boundary_path_edge_lines
                /*!< pointer to the chain of DXF \c HATCH boundary path
                 * edge lines. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_lines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_lines != NULL)
        {
                struct DxfHatchBoundaryPathEdgeLine *iter = hatch_boundary_path_edge_lines->next;
                dxf_hatch_boundary_path_edge_line_free (hatch_boundary_path_edge_lines);
                hatch_boundary_path_edge_lines = (DxfHatchBoundaryPathEdgeLine *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * path edge splines and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_edge_spline_free_chain
(
        DxfHatchBoundaryPathEdgeSpline *hatch_boundary_path_edge_splines
                /*!< pointer to the chain of DXF \c HATCH boundary path
                 * edge splines. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_splines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_splines != NULL)
        {
                struct DxfHatchBoundaryPathEdgeSpline *iter = hatch_boundary_path_edge_splines->next;
                dxf_hatch_boundary_path_edge_spline_free (hatch_boundary_path_edge_splines);
                hatch_boundary_path_edge_splines = (DxfHatchBoundaryPathEdgeSpline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HATCH boundary
 * path edge spline control points and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_hatch_boundary_path_edge_spline_control_point_free_chain
(
        DxfHatchBoundaryPathEdgeSplineCp *hatch_boundary_path_edge_spline_control_points
                /*!< pointer to the chain of DXF \c HATCH boundary path
                 * edge spline control points. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_spline_control_points == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_spline_control_points != NULL)
        {
                struct DxfHatchBoundaryPathEdgeSplineCp *iter = hatch_boundary_path_edge_spline_control_points->next;
                dxf_hatch_boundary_path_edge_spline_control_point_free (hatch_boundary_path_edge_spline_control_points);
                hatch_boundary_path_edge_spline_control_points = (DxfHatchBoundaryPathEdgeSplineCp *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path edge arc.
 *
 * \return ID code.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_hatch_boundary_path_edge_arc_get_id_code
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id_code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = arc->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path edge arc.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_id_code
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
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
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/* EOF */
