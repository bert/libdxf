/*!
 * \file mtext.h
 *
 * \author Copyright (C) 2012 ... 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF mtext entity (\c MTEXT).
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


#ifndef _MTEXT_H
#define _MTEXT_H


#include "global.h"


#define MAX_NUMBER_ADDITIONAL 1024


typedef struct
dxf_mtext
{
        /* Members common for all DXF drawable entities. */
        int id_code;
        /*!< Identification number for the entity.\n
         * This is to be an unique (sequential) number in the DXF
         * file.\n
         * Group code = 5. */
        char *linetype;
        /*!< The linetype of the entity.\n
         * Defaults to \c BYLAYER if ommitted in the DXF file.\n
         * Group code = 6. */
        char *layer;
        /*!< Layer on which the entity is drawn.\n
         * Defaults to layer "0" if no valid layername is given.\n
         * Group code = 8. */
        double thickness;
        /*!< Thickness of the arc in the local Z-direction.\n
         * Defaults to 0.0 if ommitted in the DXF file.\n
         * Group code = 39. */
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
        char *text_value;
                /*!< group code = 1\n
                 * Text string.\n
                 * If the text string is less than 250 characters, all
                 * characters appear in group 1.\n
                 * If the text string is greater than 250 characters,
                 * the string is divided into 250-character chunks,
                 * which appear in one or more group 3 codes.\n
                 * If group 3 codes are used, the last group is a group
                 * 1 and has fewer than 250 characters. */
        char *text_additional_value[MAX_NUMBER_ADDITIONAL];
                /*!< group code = 3\n
                 * Optional, only if the text string in group 1 is
                 * greater than 250 characters. */
        char *text_style;
                /*!< group code = 7\n
                 * Optional, defaults to \c STANDARD. */
        double x0;
                /*!< group code = 10\n
                 * Insertion point. */
        double y0;
                /*!< group code = 20\n
                 * Insertion point. */
        double z0;
                /*!< group code = 30\n
                 * Insertion point. */
        double x1;
                /*!< group code = 11\n
                 * X-axis direction vector, expressed in World
                 * Coordinate System (WCS).\n
                 * A group code 50 (rotation angle in radians) passed as
                 * DXF input is converted to the equivalent direction
                 * vector (if both a code 50 and codes 11, 21, 31 are
                 * passed, the last one wins).\n
                 * This is provided as a convenience for conversions
                 * from text objects. */
        double y1;
                /*!< group code = 21\n
                 * X-axis direction vector, expressed in World
                 * Coordinate System (WCS). */
        double z1;
                /*!< group code = 31\n
                 * X-axis direction vector, expressed in World
                 * Coordinate System (WCS). */
        double height;
                /*!< group code = 40\n 
                 * Nominal (initial) text height. */
        double rectangle_width;
                /*!< group code = 41\n
                 * Reference rectangle width. */
        double horizontal_width;
                /*!< group code = 42\n
                 * Horizontal width of the characters that make up the
                 * mtext entity.\n
                 * This value will always be equal to or less than the
                 * value of group code 41 (read-only, ignored if
                 * supplied). */
        double rectangle_height;
                /*!< group code = 43\n
                 * Vertical height of the mtext entity (read-only,
                 * ignored if supplied). */
        double spacing_factor;
                /*!< group code = 44\n
                 * Added in DXF 2000 and later.\n
                 * Text line spacing factor (optional):\n
                 * Percentage of default (3-on-5) line spacing to be
                 * applied.\n
                 * Valid values range from 0.25 to 4.00. */
        double box_scale;
                /*!< group code = 45\n
                 * Added in DXF 2007 and later.\n
                 * Optional, fill box scale:\n
                 * Determines how much border is around the text.  */
        double column_width;
                /*!< group code = 48\n
                 * Added in DXF 2007 and later.\n
                 * Column width. */
        double column_gutter;
                /*!< group code = 49\n
                 * added on DXF 2007 and later\n
                 * column gutter. */
        double column_heights;
                /*!< group code = 50\n
                 * Added in DXF 2007 and later.\n
                 * Column heights this code is followed by a column
                 * count (Int16), and then the number of column heights. */
        double rot_angle;
                /*!< group code = 50\n
                 * Rotation angle in radians. */
        int background_color;
                /*!< group code = 63\n
                 * Added in DXF 2007 and later.\n
                 * Optional, background fill color:\n
                 * Color to use for background fill when group code 90
                 * is 1. */
        int attachment_point;
                /*!< group code = 71\n
                 * Attachment point:\n
                 * 1 = Top left.\n
                 * 2 = Top center.\n
                 * 3 = Top right.\n
                 * 4 = Middle left.\n
                 * 5 = Middle center.\n
                 * 6 = Middle right.\n
                 * 7 = Bottom left.\n
                 * 8 = Bottom center.\n
                 * 9 = Bottom right. */
        int drawing_direction;
                /*!< group code = 72\n
                 * 2 and 4 removed on DXF R14 and later\n
                 * 5 added on DXF R14 and later\n
                 * drawing direction:\n
                 * 1 = Left to right\n
                 * 2 = Right to left (removed)\n
                 * 3 = Top to bottom\n
                 * 4 = Bottom to top (removed)\n
                 * 5 = By style (the flow direction is inherited from the associated text style). */
        int spacing_style;
                /*!< group code = 73\n
                 * added on DXF 2000 and later\n
                 * Optional, mtext line spacing style:\n
                 * 1 = At least (taller characters will override).\n
                 * 2 = Exact (taller characters will not override). */
        int column_type;
                /*!< group code = 75\n
                 * Added in DXF 2007 and later.\n
                 * Column type. */
        int column_count;
                /*!< group code = 76\n
                 * Added in DXF 2007 and later.\n
                 * Column count. */
        int column_flow;
                /*!< group code = 78\n
                 * Added in DXF 2007 and later.\n
                 * Column flow reversed. */
        int column_autoheight;
                /*!< group code = 79\n
                 * Added in DXF 2007 and later.\n
                 * Column autoheight. */
        int background_fill;
                /*!< group code = 90\n
                 * Added in DXF 2007 and later.\n
                 * Background fill setting:\n
                 * 0 = Background fill off.\n
                 * 1 = Use background fill color.\n
                 * 2 = Use drawing window color as background fill color. */
        double extr_x0;
                /*!< group code = 210\n
                 * Optional, defaults to 0.0.\n
                 * X-value of the extrusion direction. */
        double extr_y0;
                /*!< group code = 220\n
                 * Optional, defaults to 0.0.\n
                 * Y-value of the extrusion direction. */
        double extr_z0;
                /*!< group code = 230\n
                 * Optional, defaults to 1.0.\n
                 * Z-value of the extrusion direction. */
        int32_t background_color_rgb;
                /*!< group code = 420-429\n
                 * added on DXF 2007 and later\n
                 * background color (if RGB color).\n
                 * I don't know how is it... */
        char *background_color_name;
                /*!< group code = 430-439\n
                 * added on DXF 2007 and later\n
                 * background color (if color name).\n
                 * I don't know how is it... */
        int32_t background_transparency;
                /*!< group code = 441\n
                 * added on DXF 2007 and later\n
                 * transparency of background fill color.\n
                 * (not implemented in AutoCAD). */
} DxfMtext, * DxfMtextPtr;


DxfMtext *
dxf_mtext_new ();
DxfMtext *
dxf_mtext_init
(
        DxfMtext *dxf_mtext
);
int
dxf_mtext_read
(
        char *filename,
        DxfFile *fp,
        int *line_number,
        DxfMtext *dxf_mtext
);
int
dxf_mtext_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *text_value;
        char *text_additional_value[MAX_NUMBER_ADDITIONAL];
        char *text_style;
        char *layer,
        double x0;
        double y0;
        double z0;
        double x1;
        double y1;
        double z1;
        double height;
        double rectangle_width;
        double horizontal_width;
        double rectangle_height;
        double spacing_factor;
        double box_scale;
        double column_width;
        double column_gutter;
        double column_heights;
        double rot_angle;
        int color,
        short int background_color;
        int paperspace,
        short int attachment_point;
        short int drawing_direction;
        short int spacing_style;
        short int column_type;
        short int column_count;
        short int column_flow;
        short int column_autoheight;
        int background_fill;
        double extr_x0;
        double extr_y0;
        double extr_z0;
        int32_t background_color_rgb;
        char background_color_name;
        int32_t background_transparency;
);
int
dxf_mtext_write
(
        DxfFile *fp,
        DxfMtext *dxf_mtext
);
int
dxf_mtext_free
(
        DxfMtext *dxf_mtext
);


#endif /* _MTEXT_H */


/* EOF */
