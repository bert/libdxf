/*!
 * \file point.h
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Definition of a DXF point entity (\c POINT).
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

#ifndef POINT_H
#define POINT_H


#include "global.h"
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD point entity.
 *
 * \c POINT entities have an optional 50 group that determines the
 * orientation of PDMODE images.\n
 * The group value is the negative of the Entity Coordinate Systems (ECS)
 * angle of the UCS X axis in effect when the point was drawn.\n
 * The X axis of the UCS in effect when the point was drawn is always
 * parallel to the XY plane for the point's ECS, and the angle between the
 * UCS X axis and the ECS X axis is a single 2D angle.\n
 * The value in group 50 is the angle from horizontal (the effective X axis)
 * to the ECS X axis.\n
 * Entity Coordinate Systems (ECS) are described in the UCS section.\n
 */
typedef struct
dxf_point
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
        double x0;
                /*!< group code = 10. */
        double y0;
                /*!< group code = 20. */
        double z0;
                /*!< group code = 30. */
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
} DxfPoint, * DxfPointPtr;


DxfPoint *
dxf_malloc_point ();
DxfPoint *
dxf_init_point_struct
(
        DxfPoint *dxf_point
);
static int
dxf_read_point_struct
(
        char *filename,
        FILE *fp,
        int line_number,
        DxfPoint *dxf_point,
        int acad_version_number
);
int
dxf_write_point
(
        FILE *fp,
        int id_code,
        char *layer,
        double x0,
        double y0,
        double z0,
        double thickness,
        int color,
        int paperspace
);
int
dxf_write_point_struct
(
        FILE *fp,
        DxfPoint dxf_point
);


#endif /* POINT_H */


/* EOF */
