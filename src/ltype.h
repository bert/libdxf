/*!
 * \file ltype.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF ltype entity.
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


#ifndef _LTYPE_H
#define _LTYPE_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD linetype.
 */
typedef struct
dxf_ltype
{
        int id_code;
                /*!< group code = 5.\n
                 * Entity handle; text string of up to 16 hexadecimal
                 * digits (fixed) */
        char *linetype_name;
                /*!< group code = 2. */
        char *description;
                /*!< group code = 3.\n
                 * Descriptive text for linetype. */
        char *complex_text_string[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 9.\n
                 * Text string (one per element if code 74 = 2). */
        double total_pattern_length;
                /*!< group code = 40. */
        double complex_x_offset[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 44.\n
                 * X offset value (optional).\n
                 * Multiple entries can exist. */
        double complex_y_offset[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 45.\n
                 * Y offset value (optional).\n
                 * Multiple entries can exist. */
        double complex_scale[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 46.\n
                 * Scale value (optional).\n
                 * Multiple entries can exist. */
        double dash_length[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 49.\n
                 * Dash, dot or space length (one entry per element). */
        double complex_rotation[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 50.\n
                 * R = (relative) or A = (absolute) rotation value in radians
                 * of embedded shape or text.\n
                 * One per element if code 74 specifies an embedded shape
                 * or text string. */
        int flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 16 = if set, table entry is externally dependent on an
                 *      Xref\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved\n
                 * 64 = if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.\n
                 * This flag is for the benefit of AutoCAD commands; it can
                 * be ignored by most programs that read DXF files, and need
                 * not be set by programs that write DXF files. */
        int alignment;
                /*!< group code = 72\n
                 * always 65; ASCII code for 'A'. */
        int number_of_dash_length_items;
                /*!< group code = 73. */
        int complex_element[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 74.\n
                 * Complex linetype element type (one per element).\n
                 * Default is 0 (no embedded shape/text).\n
                 * The following codes are bit values:\n
                 * 1 = If set, group code 50 specifies an absolute
                 *     rotation; if not set, group code 50 specifies a
                 *     relative rotation.\n
                 * 2 = Embedded element is a text string.\n
                 * 4 = Embedded element is a shape. */
        int complex_shape_number[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 75.\n
                 * Shape number (one per element) if code 74 specifies
                 * an embedded shape.\n
                 * If code 74 specifies an embedded text string, this
                 * value is set to 0.\n
                 * If code 74 is set to 0, code 75 is omitted. */
        char *complex_style_pointer[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 340.\n
                 * Pointer to \c STYLE object.\n
                 * One per element if group code 74 > 0. */
        int acad_version_number;
                /*!< AutoCAD version number. */
} DxfLType, * DxfLTypePtr;


DxfLType *
dxf_ltype_new ();
DxfLType *
dxf_ltype_init
(
        DxfLType *dxf_ltype
);
int
dxf_ltype_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *linetype_name,
        char *description,
        int flag,
        int alignment,
        double total_pattern_length,
        int number_of_dash_length_items,
        char *complex_text_string[number_of_dash_length_items],
        double complex_x_offset[number_of_dash_length_items],
        double complex_y_offset[number_of_dash_length_items],
        double complex_scale[number_of_dash_length_items],
        double dash_length[number_of_dash_length_items],
        double complex_rotation[number_of_dash_length_items],
        int complex_element[number_of_dash_length_items],
        int complex_shape_number[number_of_dash_length_items],
        char *complex_style_pointer[number_of_dash_length_items],
        int acad_version_number
);


#endif /* _LTYPE_H */


/* EOF */
