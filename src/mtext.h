/*!
 * \file mtext.h
 *
 * \author Copyright (C) 2012, 2013, 2014, 2015, 2016, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF mtext entity (\c MTEXT).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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


#ifndef LIBDXF_SRC_MTEXT_H
#define LIBDXF_SRC_MTEXT_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD mtext entity (\c MTEXT).
 */
typedef struct
dxf_mtext_struct
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification code for the entity.\n
                 * This is to be an unique sequential code in the DXF
                 * file (the number can be hexadecimal).\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double elevation;
                /*!< Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                * Group code = 39. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67. */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        /* Specific members for a DXF mtext. */
        char *text_value;
                /*!< Text string.\n
                 * If the text string is less than 250 characters, all
                 * characters appear in group 1.\n
                 * If the text string is greater than 250 characters,
                 * the string is divided into 250-character chunks,
                 * which appear in one or more group 3 codes.\n
                 * If group 3 codes are used, the last group is a group
                 * 1 and has fewer than 250 characters.\n
                 * Group code = 1. */
        char *text_additional_value[DXF_MAX_PARAM];
                /*!< Optional, only if the text string in group 1 is
                 * greater than 250 characters.\n
                 * Group code = 3. */
        char *text_style;
                /*!< Text style.\n
                 * Optional, defaults to \c STANDARD.\n
                 * Group code = 7. */
        double x0;
                /*!< Insertion point.\n
                 * Group code = 10. */
        double y0;
                /*!< Insertion point.\n
                 * Group code = 20. */
        double z0;
                /*!< Insertion point.\n
                 * Group code = 30. */
        double x1;
                /*!< X-axis direction vector, expressed in World
                 * Coordinate System (WCS).\n
                 * A group code 50 (rotation angle in radians) passed as
                 * DXF input is converted to the equivalent direction
                 * vector (if both a code 50 and codes 11, 21, 31 are
                 * passed, the last one wins).\n
                 * This is provided as a convenience for conversions
                 * from text objects.\n
                 * Group code = 11. */
        double y1;
                /*!< X-axis direction vector, expressed in World
                 * Coordinate System (WCS).\n
                 * Group code = 21. */
        double z1;
                /*!< X-axis direction vector, expressed in World
                 * Coordinate System (WCS).\n
                 * Group code = 31. */
        double height;
                /*!< Nominal (initial) text height.\n
                 * Group code = 40. */
        double rectangle_width;
                /*!< Reference rectangle width.\n
                 * Group code = 41. */
        double horizontal_width;
                /*!< Horizontal width of the characters that make up the
                 * mtext entity.\n
                 * This value will always be equal to or less than the
                 * value of group code 41 (read-only, ignored if
                 * supplied).\n
                 * Group code = 42. */
        double rectangle_height;
                /*!< Vertical height of the mtext entity (read-only,
                 * ignored if supplied).\n
                 * Group code = 43. */
        double spacing_factor;
                /*!< Text line spacing factor (optional):\n
                 * Percentage of default (3-on-5) line spacing to be
                 * applied.\n
                 * Valid values range from 0.25 to 4.00.\n
                 * Group code = 44. */
        double box_scale;
                /*!< Optional, fill box scale:\n
                 * Determines how much border is around the text.\n
                 * Group code = 45.  */
        double column_width;
                /*!< Column width.\n
                 * Group code = 48. */
        double column_gutter;
                /*!< Column gutter.\n
                 * Group code = 49. */
        double column_heights;
                /*!< Column heights this code is followed by a column
                 * count (Int16), and then the number of column heights.\n
                 * Group code = 50. */
        double rot_angle;
                /*!< Rotation angle in radians.\n
                 * Group code = 50. */
        int background_color;
                /*!< Background fill color (optional).\n
                 * Color to use for background fill when group code 90
                 * is 1.\n
                 * Group code = 63. */
        int attachment_point;
                /*!< Attachment point:\n
                 * <ol>
                 * <li value = "1"> Top left.</li>
                 * <li value = "2"> Top center.</li>
                 * <li value = "3"> Top right.</li>
                 * <li value = "4"> Middle left.</li>
                 * <li value = "5"> Middle center.</li>
                 * <li value = "6"> Middle right.</li>
                 * <li value = "7"> Bottom left.</li>
                 * <li value = "8"> Bottom center.</li>
                 * <li value = "9"> Bottom right.</li>
                 * </ol>
                 * Group code = 71. */
        int drawing_direction;
                /*!< Drawing direction:\n
                 * <ol>
                 * <li value = "1"> Left to right.</li>
                 * <li value = "2"> Right to left (obsolete as of R14).</li>
                 * <li value = "3"> Top to bottom.</li>
                 * <li value = "4"> Bottom to top (obsolete as of R14)</li>
                 * <li value = "5"> By style (the flow direction is
                 * inherited from the associated text style, added as of
                 * R14).</li>
                 * </ol>
                 * Group code = 72. */
        int spacing_style;
                /*!< Optional, mtext line spacing style:\n
                 * <ol>
                 * <li value = "1"> At least (taller characters will
                 * override).</li>
                 * <li value = "2"> Exact (taller characters will not
                 * override).</li>
                 * </ol>
                 * Group code = 73. */
        int column_type;
                /*!< Column type.\n
                 * Group code = 75. */
        int column_count;
                /*!< Column count.\n
                 * Group code = 76. */
        int column_flow;
                /*!< Column flow reversed.\n
                 * Group code = 78. */
        int column_autoheight;
                /*!< Column autoheight.\n
                 * Group code = 79. */
        int background_fill;
                /*!< Background fill setting:\n
                 * <ol>
                 * <li value = "0"> Background fill off.</li>
                 * <li value = "1"> Use background fill color.</li>
                 * <li value = "2"> Use drawing window color as
                 * background fill color.</li>
                 * </ol>
                 * Group code = 90. */
        double extr_x0;
                /*!< X-value of the extrusion direction.\n
                 * Optional, defaults to 0.0.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion direction.\n
                 * Optional, defaults to 0.0.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion direction.\n
                 * Optional, defaults to 1.0.\n
                 * Group code = 230. */
        int32_t background_color_rgb;
                /*!< Background color (if RGB color).\n
                 * Group code = 420-429. */
        char *background_color_name;
                /*!< Background color (if color name).\n
                 * Group code = 430-439. */
        int32_t background_transparency;
                /*!< Transparency of background fill color.\n
                 * Not yet implemented in AutoCAD.\n
                 * Group code = 441. */
        struct DxfMtext *next;
                /*!< pointer to the next DxfMtext.\n
                 * \c NULL in the last DxfMtext. */
} DxfMtext;


DxfMtext *
dxf_mtext_new ();
DxfMtext *
dxf_mtext_init
(
        DxfMtext *mtext
);
DxfMtext *
dxf_mtext_read
(
        DxfFile *fp,
        DxfMtext *mtext
);
int
dxf_mtext_write
(
        DxfFile *fp,
        DxfMtext *mtext
);
int
dxf_mtext_free
(
        DxfMtext *mtext
);
void
dxf_mtext_free_chain
(
        DxfMtext *mtexts
);
int
dxf_mtext_get_id_code
(
        DxfMtext *mtext
);
DxfMtext *
dxf_mtext_set_id_code
(
        DxfMtext *mtext,
        int id_code
);
char *
dxf_mtext_get_linetype
(
        DxfMtext *mtext
);
DxfMtext *
dxf_mtext_set_linetype
(
        DxfMtext *mtext,
        char *linetype
);
char *
dxf_mtext_get_layer
(
        DxfMtext *mtext
);
DxfMtext *
dxf_mtext_set_layer
(
        DxfMtext *mtext,
        char *layer
);
double
dxf_mtext_get_elevation
(
        DxfMtext *mtext
);
DxfMtext *
dxf_mtext_set_elevation
(
        DxfMtext *mtext,
        double elevation
);
double
dxf_mtext_get_thickness
(
        DxfMtext *mtext
);
DxfMtext *
dxf_mtext_set_thickness
(
        DxfMtext *mtext,
        double thickness
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_MTEXT_H */


/* EOF */
