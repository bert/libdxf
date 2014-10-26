/*!
 * \file attrib.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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


#ifndef LIBDXF_SRC_ATTRIB_H
#define LIBDXF_SRC_ATTRIB_H


/*!
 * \brief Definition of an AutoCAD attribute entity (\c ATTRIB).
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_attrib
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
                 * Defaults to \c BYLAYER if omitted in the DXF file. */
        char *layer;
                /*!< group code = 8\n
                 * Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given. */
        double elevation;
                /*!< group code = 38\n
                 * Elevation of the 3dface in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default). */
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if omitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        int16_t line_weight;
                /*!< group code = 370\n
                 * Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer. */
        /* Specific members for a DXF attrib. */
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
                 * added on DXF R12 and later\n
                 * optional, defaults to 0\n
                 * not bit coded:\n
                 * 0 = baseline\n
                 * 1 = bottom\n
                 * 2 = middle\n
                 * 3 = top. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        struct DxfAttrib *next;
                /*!< pointer to the next DxfAttrib.\n
                 * \c NULL in the last DxfAttrib. */
} DxfAttrib;


DxfAttrib *
dxf_attrib_new ();
DxfAttrib *
dxf_attrib_init
(
        DxfAttrib *dxf_attrib
);
DxfAttrib *
dxf_attrib_read
(
        DxfFile *fp,
        DxfAttrib *dxf_attrib
);
int
dxf_attrib_write
(
        DxfFile *fp,
        DxfAttrib *dxf_attrib
);
int
dxf_attrib_free
(
        DxfAttrib *dxf_attrib
);


#endif /* LIBDXF_SRC_ATTRIB_H */


/* EOF */
