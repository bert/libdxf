/*!
 * \file color.h
 * \author Copyright (C) 2008 ... 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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


/*!
 * \brief DXF color definitions mapping to standard pen widths.
 */
typedef enum
dxf_color
{
        DXF_COLOR_BYBLOCK = 0,
                /*!< color of the entity follows the color definition of the
                 * block in which it resides. */
        DXF_COLOR_RED = 1,
                /*!< 0.18 mm pen width. */
        DXF_COLOR_YELLOW = 2,
                /*!< 0.35 mm pen width. */
        DXF_COLOR_GREEN = 3,
                /*!< 0.50 mm pen width. */
        DXF_COLOR_CYAN = 4,
                /*!< 0.70 mm pen width. */
        DXF_COLOR_BLUE = 5,
                /*!< 1.00 mm pen width. */
        DXF_COLOR_MAGENTA = 6,
                /*!< 0.18 mm pen width. */
        DXF_COLOR_WHITE = 7,
                /*!< 0.25 mm pen width. */
        DXF_COLOR_GREY = 8,
                /*!< 0.15 mm pen width. */
        DXF_COLOR_BYLAYER = 256
                /*!< color of the entity follows the color definition of the
                 * layer on which it resides. */
} DxfColor;


/*!
 * \brief Colors according to the AutoCAD Color Index (ACI).
 *
 * These colors are defined by:\n
 * \c dxf_ACI_color[index_number]: RGBColor (as in red value, green value, blue
 * value) and contain no alpha value.
 */
typedef enum
dxf_ACI_color
{
        dxf_ACI_color[00] = RGBColor (0,0,0),
        dxf_ACI_color[01] = RGBColor (255,0,0),
        dxf_ACI_color[02] = RGBColor (255,255,0),
        dxf_ACI_color[03] = RGBColor (0,255,0),
        dxf_ACI_color[04] = RGBColor (0,255,255),
        dxf_ACI_color[05] = RGBColor (0,0,255),
        dxf_ACI_color[06] = RGBColor (255,0,255),
        dxf_ACI_color[07] = RGBColor (255,255,255),
        dxf_ACI_color[08] = RGBColor (128,128,128),
        dxf_ACI_color[09] = RGBColor (192,192,192),
        dxf_ACI_color[10] = RGBColor (255,0,0),
        dxf_ACI_color[11] = RGBColor (255,127,127),
        dxf_ACI_color[12] = RGBColor (204,0,0),
        dxf_ACI_color[13] = RGBColor (204,102,102),
        dxf_ACI_color[14] = RGBColor (153,0,0),
        dxf_ACI_color[15] = RGBColor (153,76,76),
        dxf_ACI_color[16] = RGBColor (127,0,0),
        dxf_ACI_color[17] = RGBColor (127,63,63),
        dxf_ACI_color[18] = RGBColor (76,0,0),
        dxf_ACI_color[19] = RGBColor (76,38,38),
        dxf_ACI_color[20] = RGBColor (255,63,0),
        dxf_ACI_color[21] = RGBColor (255,159,127),
        dxf_ACI_color[22] = RGBColor (204,51,0),
        dxf_ACI_color[23] = RGBColor (204,127,102),
        dxf_ACI_color[24] = RGBColor (153,38,0),
        dxf_ACI_color[25] = RGBColor (153,95,76),
        dxf_ACI_color[26] = RGBColor (127,31,0),
        dxf_ACI_color[27] = RGBColor (127,79,63),
        dxf_ACI_color[28] = RGBColor (76,19,0),
        dxf_ACI_color[29] = RGBColor (76,47,38),
#if 0 // Work In Progress
        dxf_ACI_color[30] = RGBColor (),
        dxf_ACI_color[31] = RGBColor (),
        dxf_ACI_color[32] = RGBColor (),
        dxf_ACI_color[33] = RGBColor (),
        dxf_ACI_color[34] = RGBColor (),
        dxf_ACI_color[35] = RGBColor (),
        dxf_ACI_color[36] = RGBColor (),
        dxf_ACI_color[37] = RGBColor (),
        dxf_ACI_color[38] = RGBColor (),
        dxf_ACI_color[39] = RGBColor (),
        dxf_ACI_color[40] = RGBColor (),
        dxf_ACI_color[41] = RGBColor (),
        dxf_ACI_color[42] = RGBColor (),
        dxf_ACI_color[43] = RGBColor (),
        dxf_ACI_color[44] = RGBColor (),
        dxf_ACI_color[45] = RGBColor (),
        dxf_ACI_color[46] = RGBColor (),
        dxf_ACI_color[47] = RGBColor (),
        dxf_ACI_color[48] = RGBColor (),
        dxf_ACI_color[49] = RGBColor (),
        dxf_ACI_color[50] = RGBColor (),
        dxf_ACI_color[51] = RGBColor (),
        dxf_ACI_color[52] = RGBColor (),
        dxf_ACI_color[53] = RGBColor (),
        dxf_ACI_color[54] = RGBColor (),
        dxf_ACI_color[55] = RGBColor (),
        dxf_ACI_color[56] = RGBColor (),
        dxf_ACI_color[57] = RGBColor (),
        dxf_ACI_color[58] = RGBColor (),
        dxf_ACI_color[59] = RGBColor (),
        dxf_ACI_color[60] = RGBColor (),
        dxf_ACI_color[61] = RGBColor (),
        dxf_ACI_color[62] = RGBColor (),
        dxf_ACI_color[63] = RGBColor (),
        dxf_ACI_color[64] = RGBColor (),
        dxf_ACI_color[65] = RGBColor (),
        dxf_ACI_color[66] = RGBColor (),
        dxf_ACI_color[67] = RGBColor (),
        dxf_ACI_color[68] = RGBColor (),
        dxf_ACI_color[69] = RGBColor (),
        dxf_ACI_color[70] = RGBColor (),
        dxf_ACI_color[] = RGBColor (),
#endif
        dxf_ACI_color[255] = RGBColor (255,255,255)
}
DxfACIColor;

/* EOF */
