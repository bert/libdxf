/*!
 * \file vertex.h
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Header file for a DXF vertex entity (\c VERTEX).
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


#ifndef _VERTEX_H
#define _VERTEX_H


#include "global.h"
#include "entity.h"


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
dxf_vertex
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
        double x0;
                /*!< group code = 10. */
        double y0;
                /*!< group code = 20. */
        double z0;
                /*!< group code = 30. */
        double start_width;
                /*!< group code = 40\n
                 * optional, defaults to 0.0. */
        double end_width;
                /*!< group code = 41\n
                 * optional, defaults to 0.0. */
        double bulge;
                /*!< group code = 42\n
                 * optional, defaults to 0.0\n
                 * the bulge is the tangent of 1/4 the included angle for an
                 * arc segment, made negative if the arc goes clockwise from
                 * the start point to the endpoint; a bulge of 0 indicates a
                 * straight segment, and a bulge of 1 is a semicircle. */
        double curve_fit_tangent_direction;
                /*!< group code = 50\n
                 * optional. */
        int flag;
                /*!< group code = 70\n
                 * optional, defaults to 0\n
                 * bit coded:\n
                 * 1 = extra vertex created by curve-fitting
                 * 2 = curve-fit tangent defined for this vertex.
                 *     A curve-fit tangent direction of 0 may be omitted from
                 *     the DXF output, but is significant if this bit is set\n
                 * 4 = unused (never set in DXF files)
                 * 8 = spline vertex created by spline-fitting
                 * 16 = spline frame control point
                 * 32 = 3D Polyline vertex
                 * 64 = 3D polygon mesh vertex
                 * 128 = polyface mesh vertex.\n */
} DxfVertex, * DxfVertexPtr;


DxfVertex *
dxf_vertex_new ();
DxfVertex *
dxf_vertex_init
(
        DxfVertex *dxf_vertex
);
int
dxf_vertex_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfVertex *dxf_vertex,
        int acad_version_number
);
int
dxf_vertex_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *linetype,
        char *layer,
        double x0,
        double y0,
        double z0,
        double thickness,
        double start_width,
        double end_width,
        double bulge,
        double curve_fit_tangent_direction,
        int color,
        int paperspace,
        int flag
);
int
dxf_vertex_write
(
        FILE *fp,
        DxfVertex dxf_vertex
);


#endif /* _VERTEX_H */


/* EOF */
