/*!
 * \file vertex.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
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


#ifndef LIBDXF_SRC_VERTEX_H
#define LIBDXF_SRC_VERTEX_H


#include "global.h"


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
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
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
        int acad_version_number;
                /*!< AutoCAD version number. */
        /* Specific members for a DXF vertex. */
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
                 * Optional, defaults to 0\n
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
                 * </ol> */
        int polyface_mesh_vertex_index_1;
                /*!< group code = 71\n
                 * optional, defaults to 0. */
        int polyface_mesh_vertex_index_2;
                /*!< group code = 72\n
                 * optional, defaults to 0. */
        int polyface_mesh_vertex_index_3;
                /*!< group code = 73\n
                 * optional, defaults to 0. */
        int polyface_mesh_vertex_index_4;
                /*!< group code = 74\n
                 * optional, defaults to 0. */
        struct DxfVertex *next;
                /*!< pointer to the next DxfVertex.\n
                 * \c NULL in the last DxfVertex. */
} DxfVertex;


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
        DxfFile *fp,
        DxfVertex *dxf_vertex
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
        DxfFile *fp,
        DxfVertex *dxf_vertex
);
int
dxf_vertex_free
(
        DxfVertex *dxf_vertex
);


#endif /* LIBDXF_SRC_VERTEX_H */


/* EOF */
