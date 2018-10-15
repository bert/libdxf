/*!
 * \file color.h
 *
 * \author Copyright (C) 2008, 2009, 2010, 2012, 2014, 2015, 2016, 2017,
 * 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of DXF color values.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * These definitions contain the following:\n
 * <ul>
 * <li>Colors mapping to standard pen widths.\n
 * <li>Colors according to the AutoCAD Color Index (ACI).\n
 * </ul>
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.\n
 * \n
 * Drawing eXchange Format (DXF) is a defacto industry standard for the
 * exchange of drawing files between various Computer Aided Drafting
 * programs.\n
 * DXF is an industry standard designed by Autodesk(TM).\n
 * For more details see http://www.autodesk.com.\n\n
 * <hr>
 */


#ifndef LIBDXF_SRC_COLOR_H
#define LIBDXF_SRC_COLOR_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of a color.
 */
typedef struct
{
        uint8_t r;
                /*!< Red value for the color. */
        uint8_t g;
                /*!< Green value for the color. */
        uint8_t b;
                /*!< Blue value for the color. */
        uint8_t unused;
                /*!< Unused, could be used for the alpha value (future). */
        char *name;
                /*!< Name of the color. */
        struct DxfRGBColor *next;
                /*!< Pointer to the next DxfRGBColor.\n
                 * \c NULL in the last DxfRGBColor. */
} DxfRGBColor;


char *dxf_RGB_color_get_name (int RGB_color_hex_triplet);
DxfRGBColor *dxf_RGB_color_new ();
DxfRGBColor *dxf_RGB_color_set (int red, int green, int blue);
int dxf_ACI_init (DxfRGBColor *ACI[DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS]);
int dxf_RGB_to_triplet (int red, int green, int blue);
int dxf_RGB_color_free (DxfRGBColor *RGB_color);
void dxf_RGB_color_free_list (DxfRGBColor *colors);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_COLOR_H */


/* EOF */
