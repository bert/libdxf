/*!
 * \file attrib.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF attribute entity (\c ATTRIB).
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


#include "global.h"
#include "entity.h"


#ifndef _ATTRIB_H
#define _ATTRIB_H


/*!
 * \brief Definition of an AutoCAD attribute entity (\c ATTRIB).
 */
typedef struct
dxf_attrib
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
        char *value;
                /*!< group code = 1. */
        char *tag_value;
                /*!< group code = 2. */
        char *text_style;
                /*!< group code = 7\n
                 * optional, defaults to STANDARD. */
        double x0;
                /*!< group code = 10\n
                 * start point. */
        double y0;
                /*!< group code = 20\n
                 * start point. */
        double z0;
                /*!< group code = 30\n
                 * start point. */
        double x1;
                /*!< group code = 11\n
                 * alignment point. */
        double y1;
                /*!< group code = 21\n
                 * alignment point. */
        double z1;
                /*!< group code = 31\n
                 * alignment point. */
        double height;
                /*!< group code = 40. */
        double rel_x_scale;
                /*!< group code = 41\n
                 * optional, defaults to 1.0. */
        double rot_angle;
                /*!< group code = 50\n
                 * optional, defaults to 0.0. */
        double obl_angle;
                /*!< group code = 51\n
                 * optional, defaults to 0.0. */
        int attr_flags;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 1 = attribute is invisible (does not display)\n
                 * 2 = this is a constant attribute\n
                 * 4 = verification is required on input of this attribute\n
                 * 8 = attribute is preset (no prompt during insertion). */
        int text_flags;
                /*!< group code = 71\n
                 * optional, defaults to 0\n
                 * bit coded:\n
                 * 2 = text is backward (mirrored in X)\n
                 * 4 = text is upside down (mirrored in Y). */
        int hor_align;
                /*!< group code = 72\n
                 * optional, defaults to 0\n
                 * not bit coded:\n
                 * 0 = left\n
                 * 1 = center\n
                 * 2 = right\n
                 * 3 = aligned, only when vert_align = 0\n
                 * 4 = middle, only when vert_align = 0\n
                 * 5 = fit, only when vert_align = 0. */
        int field_length;
                /*!< group code = 73\n
                 * optional, defaults to 0. */
        int vert_align;
                /*!< group code = 74\n
                 * optional, defaults to 0\n
                 * not bit coded:\n
                 * 0 = baseline\n
                 * 1 = bottom\n
                 * 2 = middle\n
                 * 3 = top. */
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
} DxfAttrib, * DxfAttribPtr;


DxfAttrib *
dxf_attrib_new ();
DxfAttrib *
dxf_attrib_init
(
        DxfAttrib *dxf_attrib
);
int
dxf_attrib_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfAttrib *dxf_attrib,
        int acad_version_number
);
int
dxf_attrib_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *value,
        char *tag_value,
        char *linetype,
        char *text_style,
        char *layer,
        double x0,
        double y0,
        double z0,
        double x1,
        double y1,
        double z1,
        double thickness,
        double height,
        double rel_x_scale,
        double rot_angle,
        double obl_angle,
        int color,
        int paperspace,
        int attr_flags,
        int text_flags,
        int hor_align,
        int field_length,
        int vert_align
);
int
dxf_attrib_write
(
        FILE *fp,
        DxfAttrib dxf_attrib
);
int
dxf_attrib_free
(
        DxfAttrib *dxf_attrib
);


#endif /* _ATTRIB_H */


/* EOF */
