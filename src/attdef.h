/*!
 * \file attdef.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF attribute definition entity (\c ATTDEF).
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


#ifndef _ATTDEF_H
#define _ATTDEF_H


/*!
 * \brief Definition of an AutoCAD attribute definition entity
 * (\c ATTDEF).
 */
typedef struct
dxf_attdef
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
        /* Specific members for a DXF attdef. */
        char *default_value;
                /*!< group code = 1\n
                 * Default value for the attribute. */
        char *tag_value;
                /*!< group code = 2\n
                 * Tagname for the attribute. */
        char *prompt_value;
                /*!< group code = 3\n
                 * Prompt text for the value to be stored in the attribute. */
        char *text_style;
                /*!< group code = 7\n
                 * The style used for the presentation of the value of the
                 * attribute.\n
                 * Defaults to \c STANDARD if  ommitted in the DXF file. */
        double x0;
                /*!< group code = 10\n
                 * X-value of the starting point coordinate. */
        double y0;
                /*!< group code = 20\n
                 * Y-value of the starting point coordinate. */
        double z0;
                /*!< group code = 30\n
                 * Z-value of the starting point coordinate. */
        double x1;
                /*!< group code = 11\n
                 * X-value of the alignment point coordinate. */
        double y1;
                /*!< group code = 21\n
                 * Y-value of the alignment point coordinate. */
        double z1;
                /*!< Z-value of the alignment point coordinate.\n
                 * Group code = 31. */
        double height;
                /*!< group code = 40\n
                 * Character height of the attribute value. */
        double rel_x_scale;
                /*!< group code = 41\n
                 * Relative scale in the X-direction.\n
                 * Defaults to 1.0 if ommitted from DXF file. */
        double rot_angle;
                /*!< group code = 50\n
                 * Rotation angle of the attribute value.\n
                 * Defaults to 0.0 if ommitted from DXF file. */
        double obl_angle;
                /*!< group code = 51\n
                 * Oblique angle of the attribute value.\n
                 * Defaults to 0.0 if ommitted from DXF file. */
        int attr_flags;
                /*!< group code = 70\n
                 * Attribute flags.\n
                 * Bit coded:\n
                 * 1 = attribute is invisible (does not display).\n
                 * 2 = this is a constant attribute.\n
                 * 4 = verification is required on input of this attribute.\n
                 * 8 = attribute is preset (no prompt during insertion). */
        int text_flags;
                /*!< group code = 71\n
                 * Text flags.\n
                 * Bit coded:\n
                 * 2 = text is backward (mirrored in X).\n
                 * 4 = text is upside down (mirrored in Y).\n
                 * Defaults to 0 if ommited from DXF file. */
        int hor_align;
                /*!< group code = 72\n
                 * Horizontal alignment.\n
                 * Bit coded:\n
                 * 0 = left.\n
                 * 1 = center.\n
                 * 2 = right.\n
                 * 3 = aligned, only when vert_align = 0.\n
                 * 4 = middle, only when vert_align = 0.\n
                 * 5 = fit, only when vert_align = 0. \n
                 * Defaults to 0 if ommitted from DXF file. */
        int field_length;
                /*!< group code = 73\n
                 * Field length.\n
                 * Defaults to 0 if ommitted from DXF file. */
        int vert_align;
                /*!< group code = 74\n
                 * added on DXF R12 and later\n
                 * Vertical alignment.\n
                 * Bit coded:\n
                 * 0 = baseline.\n
                 * 1 = bottom.\n
                 * 2 = middle.\n
                 * 3 = top.\n
                 * Defaults to 0 if ommitted from DXF file. */
        double extr_x0;
                /*!< group code = 210\n
                 * X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double extr_y0;
                /*!< group code = 220\n
                 * Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double extr_z0;
                /*!< group code = 230\n
                 * Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file. */
        struct DxfAttdef *next;
                /*!< pointer to the next DxfAttdef.\n
                 * \c NULL in the last DxfAttdef. */
} DxfAttdef, * DxfAttdefPtr;


DxfAttdef *
dxf_attdef_new ();
DxfAttdef *
dxf_attdef_init
(
        DxfAttdef *dxf_attdef
);
int
dxf_attdef_read
(
        DxfFile *fp,
        DxfAttdef *dxf_attdef
);
int
dxf_attdef_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *default_value,
        char *tag_value,
        char *prompt_value,
        char *linetype,
        char *text_style,
        char *layer,
        double x0,
        double y0,
        double z0,
        double x1,
        double y1,
        double z1,
        double extr_x0,
        double extr_y0,
        double extr_z0,
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
        int vert_align,
        int acad_version_number

);
int
dxf_attdef_write
(
        DxfFile *fp,
        DxfAttdef *dxf_attdef
);
int
dxf_attdef_free
(
        DxfAttdef *dxf_attdef
);


#endif /* _ATTDEF_H */


/* EOF */
