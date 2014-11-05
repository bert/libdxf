/*!
 * \file point.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF point entity (\c POINT).
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

#ifndef LIBDXF_SRC_POINT_H
#define LIBDXF_SRC_POINT_H


#include "global.h"


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
        /* Specific members for a DXF point. */
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
        struct DxfPoint *next;
                /*!< pointer to the next DxfPoint.\n
                 * \c NULL in the last DxfPoint. */
} DxfPoint;


DxfPoint *
dxf_point_new ();
DxfPoint *
dxf_point_init
(
        DxfPoint *dxf_point
);
int
dxf_point_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfPoint *dxf_point
);
int
dxf_point_write_lowlevel
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
dxf_point_write
(
        FILE *fp,
        DxfPoint *dxf_point
);


#endif /* LIBDXF_SRC_POINT_H */


/* EOF */
