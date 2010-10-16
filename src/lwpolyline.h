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
#include "entity.h"


/*!
 * \brief Definition of a DXF light weight polyline entity.
 */
typedef struct
dxf_lwpolyline
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
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


DxfLWPolyline *
dxf_lwpolyline_new ();
DxfLWPolyline *
dxf_lwpolyline_init
(
        DxfLWPolyline *dxf_lwpolyline
);
int
dxf_lwpolyline_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfLWPolyline *dxf_lwpolyline,
        int acad_version_number
);
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
