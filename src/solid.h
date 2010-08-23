/*!
 * \file solid.h
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Definition of a DXF solid entity (\c SOLID).
 *
 * A DXF \c SOLID entity is a filled shape made with up to four point
 * (X, Y, Z)-coordinates.\n
 * A filled triangle can be formed by duplicating the third coordinate at the
 * fourth coordinate position.\n
 * A diabolo shaped solid can be formed by "twisting" the \SHAPE form in it's
 * plane, by "swapping" the third and fourth coordinate set.
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


#ifndef _SOLID_H
#define _SOLID_H


#include "global.h"
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD solid entity.
 *
 * If only three points are entered (forming a triangular \c SOLID), the
 * third and fourth points will coincide.
 */
typedef struct
dxf_solid
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double x1;
                /*!< group code = 11\n
                 * alignment point. */
        double y1;
                /*!< group code = 21\n
                 * alignment point. */
        double z1;
                /*!< group code = 31\n
                 * alignment point. */
        double x2;
                /*!< group code = 12\n
                 * alignment point. */
        double y2;
                /*!< group code = 22\n
                 * alignment point. */
        double z2;
                /*!< group code = 32\n
                 * alignment point. */
        double x3;
                /*!< group code = 13\n
                 * alignment point. */
        double y3;
                /*!< group code = 23\n
                 * alignment point. */
        double z3;
                /*!< group code = 33\n
                 * alignment point. */
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
} DxfSolid, * DxfSolidPtr;


DxfSolid *
dxf_malloc_solid ();
DxfSolid *
dxf_init_solid_struct
(
        DxfSolid *dxf_solid
);
int
dxf_write_solid
(
        FILE *fp,
        int id_code,
        char *linetype,
        char *layer,
        double x0,
        double y0,
        double z0,
        double x1,
        double y1,
        double z1,
        double x2,
        double y2,
        double z2,
        double x3,
        double y3,
        double z3,
        double thickness,
        int color,
        int paperspace
);
int
dxf_write_solid_struct
(
        FILE *fp,
        DxfSolid dxf_solid
);


#endif /* _SOLID_H */


/* EOF */
