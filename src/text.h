/*!
 * \file text.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF text entity (\c TEXT).
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


#ifndef _TEXT_H
#define _TEXT_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD text entity.
 *
 * DXFOUT handles ASCII control characters in text strings by expanding the
 * character into a ^ (caret) followed by the appropriate letter.\n
 * For example, an ASCII Control-G (BEL, decimal code 7) is output as ^G.\n
 * If the text itself contains a caret character, it is expanded to ^ (caret,
 * space).\n
 * DXFIN performs the complementary conversion.
 */
typedef struct
dxf_text
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
        /* Specific members for a DXF text. */
        char *text_value;
                /*!< group code = 1. */
        char *text_style;
                /*!< group code = 7\n
                 * optional, defaults to \c STANDARD. */
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
                 * alignment point, appears only if 72 or 73 group code is
                 * present and nonzero. */
        double y1;
                /*!< group code = 21\n
                 * alignment point, appears only if 72 or 73 group code is
                 * present and nonzero. */
        double z1;
                /*!< group code = 31\n
                 * alignment point, appears only if 72 or 73 group code is
                 * present and nonzero. */
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
        int vert_align;
                /*!< group code = 73\n
                 * added on DXF R12 and later\n
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
        struct DxfText *next;
                /*!< pointer to the next DxfText.\n
                 * \c NULL in the last DxfText. */
} DxfText, * DxfTextPtr;


DxfText *
dxf_text_new ();
DxfText *
dxf_text_init
(
        DxfText *dxf_text
);
int
dxf_text_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfText *dxf_text
);
int
dxf_text_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *text_value,
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
        int text_flags,
        int hor_align,
        int vert_align
);
int
dxf_text_write
(
        FILE *fp,
        DxfText *dxf_text
);


#endif /* _TEXT_H */


/* EOF */
