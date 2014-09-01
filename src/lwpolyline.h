/*!
 * \file lwpolyline.h
 *
 * \author Copyright (C) 2010 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
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
        /* Specific members for a DXF lwpolyline. */
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
                 * supply widths. */
        double end_width;
                /*!< group code = 41\n
                 * optional, defaults to 0.0\n
                 * the default widths apply to any vertex that doesn't
                 * supply widths. */
        double constant_width;
                /*!< group code = 43\n
                 * optional, defaults to 0.0\n
                 * Not used if variable width (codes 40 and/or 41) is
                 * set the default widths apply to any vertex that
                 * doesn't supply widths. */
        int flag;
                /*!< group code = 70\n
                 * optional, defaults to 0\n
                 * bit coded:\n
                 * 1 = Closed.\n
                 * 128 = Plinegen. */
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
        struct DxfLWPolyline *next;
                /*!< pointer to the next DxfLWPolyline.\n
                 * \c NULL in the last DxfLWPolyline. */
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
        DxfLWPolyline *dxf_lwpolyline
);
int
dxf_lwpolyline_write
(
        FILE *fp,
        DxfLWPolyline *dxf_lwpolyline
);


#endif /* _LWPOLYLINE_H */


/* EOF */
