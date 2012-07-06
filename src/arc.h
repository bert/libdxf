/*!
 * \file arc.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF arc entity (\c ARC).
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


#ifndef _ARC_H
#define _ARC_H


#include "global.h"
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD arc entity.
 */
typedef struct
dxf_arc
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
        double x0;
                /*!< X-value of the starting point coordinate.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the starting point coordinate.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the starting point coordinate.\n
                 * Group code = 30. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file.\n
                 * Group code = 230. */
        double radius;
                /*!< Radius of the arc.\n
                 * Group code = 40. */
        double start_angle;
                /*!< Start angle of the arc.\n
                 * Group code = 50. */
        double end_angle;
                /*!< End angle of the arc.\n
                 * Group code = 51. */
} DxfArc, * DxfArcPtr;


DxfArc *
dxf_arc_new ();
DxfArc *
dxf_arc_init
(
        DxfArc *dxf_arc
);
int
dxf_arc_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfArc *dxf_arc,
        int acad_version_number
);
int
dxf_arc_write_lowlevel
(
        FILE *fp,
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
        double radius,
        double start_angle,
        double end_angle,
        int color,
        int paperspace,
        int acad_version_number
);
int
dxf_arc_write
(
        FILE *fp,
        DxfArc dxf_arc
);
int
dxf_arc_free
(
        DxfArc *dxf_arc
);


#endif /* _ARC_H */


/* EOF */
