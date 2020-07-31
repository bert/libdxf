/*!
 * \file ltype.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015 2016, 2017, 2018, 2020
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF ltype symbol table entry (\c LTYPE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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


#ifndef LIBDXF_SRC_LTYPE_H
#define LIBDXF_SRC_LTYPE_H


#include "global.h"
#include "util.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD linetype symbol table entry.
 */
typedef struct
dxf_ltype_struct
{
        int id_code;
                /*!< Entity handle; text string of up to 16 hexadecimal
                 * digits (fixed).\n
                 * Group code = 5. */
        char *linetype_name;
                /*!< Linetype name.\n
                 * Group code = 2. */
        char *description;
                /*!< Descriptive text for linetype.\n
                 * Group code = 3. */
        DxfChar *complex_text_string;
                /*!< Text string (one per element if code 74 = 2).\n
                 * Group code = 9. */
        double total_pattern_length;
                /*!< Total pattern length.\n
                 * Group code = 40. */
        DxfDouble *complex_x_offset;
                /*!< X offset value (optional).\n
                 * Multiple entries can exist.\n
                 * Group code = 44. */
        DxfDouble *complex_y_offset;
                /*!< Y offset value (optional).\n
                 * Multiple entries can exist.\n
                 * Group code = 45. */
        DxfDouble *complex_scale;
                /*!< Scale value (optional).\n
                 * Multiple entries can exist.\n
                 * Group code = 46. */
        DxfDouble *dash_length;
                /*!< Dash, dot or space length (one entry per element).\n
                 * Group code = 49. */
        DxfDouble *complex_rotation;
                /*!< \n
                 * R = (relative) or A = (absolute) rotation value in radians
                 * of embedded shape or text.\n
                 * One per element if code 74 specifies an embedded shape
                 * or text string.\n
                 * Group code = 50. */
        int flag;
                /*!< Bit coded:\n
                 * <ol>
                 * <li value = "16"> if set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> if this bit and bit 16 are both set,
                 * the externally dependent Xref has been successfully
                 * resolved.</li>
                 * <li value = "64"> if set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * This flag is for the benefit of AutoCAD commands; it can
                 * be ignored by most programs that read DXF files, and need
                 * not be set by programs that write DXF files.\n
                 * Group code = 70. */
        int alignment;
                /*!< Alignment code.\n
                 * Value is always 65, ASCII code for 'A'.\n
                 * Group code = 72. */
        int number_of_linetype_elements;
                /*!< The number of linetype elements.\n
                 * Group code = 73. */
        DxfInt16 *complex_element;
                /*!< Complex linetype element type (one per element).\n
                 * Default is 0 (no embedded shape/text).\n
                 * The following codes are bit values:\n
                 * <ol>
                 * <li value = "1"> If set, group code 50 specifies an
                 * absolute rotation; if not set, group code 50
                 * specifies a relative rotation.</li>
                 * <li value = "2"> Embedded element is a text string.</li>
                 * <li value = "4"> Embedded element is a shape.</li>
                 * </ol>
                 * Group code = 74. */
        DxfInt16 *complex_shape_number;
                /*!< Shape number (one per element) if code 74 specifies
                 * an embedded shape.\n
                 * If code 74 specifies an embedded text string, this
                 * value is set to 0.\n
                 * If code 74 is set to 0, code 75 is omitted.\n
                 * Group code = 75. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        DxfChar *complex_style_pointer;
                /*!< group code = 340.Pointer to \c STYLE object.\n
                 * One per element if group code 74 > 0.\n
                 * Group code = 340. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        struct DxfLType *next;
                /*!< pointer to the next DxfLType.\n
                 * \c NULL in the last DxfLType. */
} DxfLType;


DxfLType *dxf_ltype_new ();
DxfLType *dxf_ltype_init (DxfLType *ltype);
DxfLType *dxf_ltype_read (DxfFile *fp, DxfLType *ltype);
int dxf_ltype_write (DxfFile *fp, DxfLType *ltype);
int dxf_ltype_free (DxfLType *ltype);
void dxf_ltype_free_list (DxfLType *ltypes);
int dxf_ltype_get_id_code (DxfLType *ltype);
DxfLType *dxf_ltype_set_id_code (DxfLType *ltype, int id_code);
char *dxf_ltype_get_linetype_name (DxfLType *ltype);
DxfLType *dxf_ltype_set_linetype_name (DxfLType *ltype, char *linetype_name);
char *dxf_ltype_get_description (DxfLType *ltype);
DxfLType *dxf_ltype_set_description (DxfLType *ltype, char *description);
DxfChar *dxf_ltype_get_complex_text_string (DxfLType *ltype);
DxfLType *dxf_ltype_set_complex_text_string (DxfLType *ltype,DxfChar *complex_text_string);
double dxf_ltype_get_total_pattern_length (DxfLType *ltype);
DxfLType *dxf_ltype_set_total_pattern_length (DxfLType *ltype, double total_pattern_length);
DxfDouble *dxf_ltype_get_complex_x_offset (DxfLType *ltype);
DxfLType *dxf_ltype_set_complex_x_offset (DxfLType *ltype, DxfDouble *complex_x_offset);
DxfDouble *dxf_ltype_get_complex_y_offset (DxfLType *ltype);
DxfLType *dxf_ltype_set_complex_y_offset (DxfLType *ltype, DxfDouble *complex_y_offset);
DxfDouble *dxf_ltype_get_complex_scale (DxfLType *ltype);
DxfLType *dxf_ltype_set_complex_scale (DxfLType *ltype, DxfDouble *complex_scale);
DxfDouble *dxf_ltype_get_dash_length (DxfLType *ltype);
DxfLType *dxf_ltype_set_dash_length (DxfLType *ltype, DxfDouble *dash_length);
DxfDouble *dxf_ltype_get_complex_rotation (DxfLType *ltype);
DxfLType *dxf_ltype_set_complex_rotation (DxfLType *ltype, DxfDouble *complex_rotation);
int dxf_ltype_get_flag (DxfLType *ltype);
DxfLType *dxf_ltype_set_flag (DxfLType *ltype, int flag);
int dxf_ltype_is_xreferenced (DxfLType *ltype);
int dxf_ltype_is_xresolved (DxfLType *ltype);
int dxf_ltype_is_referenced (DxfLType *ltype);
int dxf_ltype_get_alignment (DxfLType *ltype);
DxfLType *dxf_ltype_set_alignment (DxfLType *ltype, int alignment);
int dxf_ltype_get_number_of_linetype_elements (DxfLType *ltype);
DxfLType *dxf_ltype_set_number_of_linetype_elements (DxfLType *ltype, int number_of_linetype_elements);
DxfInt16 *dxf_ltype_get_complex_element (DxfLType *ltype);
DxfLType *dxf_ltype_set_complex_element (DxfLType *ltype, DxfInt16 *complex_element);
DxfInt16 *dxf_ltype_get_complex_shape_number (DxfLType *ltype);
DxfLType *dxf_ltype_set_complex_shape_number (DxfLType *ltype, DxfInt16 *complex_shape_number);
char *dxf_ltype_get_dictionary_owner_soft (DxfLType *ltype);
DxfLType *dxf_ltype_set_dictionary_owner_soft (DxfLType *ltype, char *dictionary_owner_soft);
DxfChar *dxf_ltype_get_complex_style_pointer (DxfLType *ltype);
DxfLType *dxf_ltype_set_complex_style_pointer (DxfLType *ltype, DxfChar *complex_style_pointer);
char *dxf_ltype_get_dictionary_owner_hard (DxfLType *ltype);
DxfLType *dxf_ltype_set_dictionary_owner_hard (DxfLType *ltype, char *dictionary_owner_hard);
DxfLType *dxf_ltype_get_next (DxfLType *ltype);
DxfLType *dxf_ltype_set_next (DxfLType *ltype, DxfLType *next);
DxfLType *dxf_ltype_get_last (DxfLType *ltype);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LTYPE_H */


/* EOF */
