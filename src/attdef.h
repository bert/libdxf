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
        DxfEntity common;
                /*!< common properties for DXF entities. */
        char *default_value;
                 /*!< Default value for the attribute.\n
                 * Group code = 1. */
        char *tag_value;
                /*!< Tagname for the attribute.\n
                 * Group code = 2. */
        char *prompt_value;
                /*!< Prompt text for the value to be stored in the attribute.\n
                 * Group code = 3. */
        char *text_style;
                /*!< The style used for the presentation of the value of the
                 * attribute.\n
                 * Defaults to \c STANDARD if  ommitted in the DXF file.\n
                 * Group code = 7. */
        double x0;
                /*!< X-value of the starting point coordinate.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the starting point coordinate.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the starting point coordinate.\n
                 * Group code = 30. */
        double x1;
                /*!< X-value of the alignment point coordinate.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of the alignment point coordinate.\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of the alignment point coordinate.\n
                 * Group code = 31. */
        double height;
                /*!< Character height of the attribute value.\n
                 * Group code = 40. */
        double rel_x_scale;
                /*!< Relative scale in the X-direction.\n
                 * Defaults to 1.0 if ommitted from DXF file.\n
                 * Group code = 41. */
        double rot_angle;
                /*!< Rotation angle of the attribute value.\n
                 * Defaults to 0.0 if ommitted from DXF file.\n
                 * Group code = 50. */
        double obl_angle;
                /*!< Oblique angle of the attribute value.\n
                 * Defaults to 0.0 if ommitted from DXF file.\n
                 * Group code = 51. */
        int attr_flags;
                /*!< Attribute flags.\n
                 * Bit coded:\n
                 * 1 = attribute is invisible (does not display).\n
                 * 2 = this is a constant attribute.\n
                 * 4 = verification is required on input of this attribute.\n
                 * 8 = attribute is preset (no prompt during insertion).\n
                 * Group code = 70. */
        int text_flags;
                /*!< Text flags.\n
                 * Bit coded:\n
                 * 2 = text is backward (mirrored in X).\n
                 * 4 = text is upside down (mirrored in Y).\n
                 * Defaults to 0 if ommited from DXF file.\n
                 * Group code = 71. */
        int hor_align;
                /*!< Horizontal alignment.\n
                 * Bit coded:\n
                 * 0 = left.\n
                 * 1 = center.\n
                 * 2 = right.\n
                 * 3 = aligned, only when vert_align = 0.\n
                 * 4 = middle, only when vert_align = 0.\n
                 * 5 = fit, only when vert_align = 0. \n
                 * Defaults to 0 if ommitted from DXF file.\n
                 * Group code = 72. */
        int field_length;
                /*!< Field length.\n
                 * Defaults to 0 if ommitted from DXF file.\n
                 * Group code = 73. */
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
        char *filename,
        FILE *fp,
        int *line_number,
        DxfAttdef *dxf_attdef,
        int acad_version_number
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
        FILE *fp,
        DxfAttdef dxf_attdef
);
int
dxf_attdef_free
(
        DxfAttdef *dxf_attdef
);


#endif /* _ATTDEF_H */


/* EOF */
