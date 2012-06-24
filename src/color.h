/*!
 * \file color.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of DXF color values.
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


#ifndef _COLOR_H
#define _COLOR_H


#include <inttypes.h>
#include "global.h"


/*!
 * \brief Definition of a color.
 */
typedef struct
{
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t unused;
} DxfRGBColor;


DxfRGBColor *
dxf_RGB_color_new ();
DxfRGBColor *
dxf_RGB_color_set
(
        int red,
        int green,
        int blue
);
int
dxf_ACI_init
(
        DxfRGBColor *dxf_ACI[DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS]
);
int
dxf_RGB_to_triplet
(
        int red,
        int green,
        int blue
);


#endif /* _COLOR_H */


/* EOF */
