/*!
 * \file lwpolyline.h
 * \author Copyright (C) 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Header file for a DXF light weight polyline entity (\c LWPOLYLINE).
 *
 * \warning This entity requires AutoCAD version 2004 or higher.
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


#ifndef _LWPOLYLINE_H
#define _LWPOLYLINE_H


#include "global.h"


/*!
 * \brief Definition of a DXF light weight polyline entity.
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
dxf_lwpolyline
{
        int id_code;
                /*!< group code = 5. */
        char *linetype;
                /*!< group code = 6\n
                 * optional, defaults to \c BYLAYER. */
        char *layer;
                /*!< group code = 8. */
        double x0;
                /*!< group code = 10\n
                 * Vertex coordinates (in OCS), multiple entries;\n
                 * one entry for each vertex\n
                 * DXF: X value;\n
                 * APP: 2D point. */
        double y0;
                /*!< group code = 20\n
                 * DXF: Y value of vertex coordinates (in OCS),
                 * multiple entries; one entry for each vertex. */
        double thickness;
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double start_width;
                /*!< group code = 40\n
                 * optional, defaults to 0.0\n
                 * the default widths apply to any vertex that doesn't
                 * supply widths.\n */
        double end_width;
                /*!< group code = 41\n
                 * optional, defaults to 0.0\n
                 * the default widths apply to any vertex that doesn't
                 * supply widths.\n */
        double constant_width;
                /*!< group code = 43\n
                 * optional, defaults to 0.0\n
                 * Not used if variable width (codes 40 and/or 41) is
                 * set the default widths apply to any vertex that
                 * doesn't supply widths.\n */
        int color;
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER. */
        int paperspace;
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int flag;
                /*!< group code = 70\n
                 * optional, defaults to 0\n
                 * bit coded:\n
                 * 1 = Closed.\n
                 * 128 = Plingen\n. */
        int number_vertices;
                /*!< group code = 90. */
        double extr_x0;
                /*!< group code = 210\n
                 * Extrusion direction (optional; default = 0, 0, 1)\n
                 * DXF: X value;\n
                 * APP: 3D vector\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double extr_y0;
                /*!< group code = 220
                 * DXF: Y value of extrusion direction (optional). */
        double extr_z0;
                /*!< group code = 230
                 * DXF: Z value of extrusion direction (optional). */
} DxfLWPolyline, * DxfLWPolylinePtr;


int
dxf_lwpolyline_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *linetype,
        char *layer,
        double x0,
        double y0,
        double thickness,
        double start_width,
        double end_width,
        double constant_width,
        int color,
        int paperspace,
        int flag,
        int number_vertices,
        double extr_x0,
        double extr_y0,
        double extr_z0,
        int acad_version_number
);
int
dxf_lwpolyline_write
(
        FILE *fp,
        DxfLWPolyline dxf_lwpolyline,
        int acad_version_number
);


#endif /* _LWPOLYLINE_H */


/* EOF */
