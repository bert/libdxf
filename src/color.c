/*!
 * \file color.c
 *
 * \author Copyright (C) 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for DXF colors.
 *
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


#include "color.h"


/*!
 * \brief Allocate memory for a DXF color.
 *
 * Fill the memory contents with zeros.
 */
DxfRGBColor *
dxf_RGB_color_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_RGB_color_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfRGBColor *dxf_RGB_color = NULL;
        size_t size;

        size = sizeof (DxfRGBColor);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_RGB_color = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_RGB_color_new () could not allocate memory for a DxfRGBCcolor struct.\n");
                dxf_RGB_color = NULL;
        }
        else
        {
                memset (dxf_RGB_color, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_RGB_color_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_RGB_color);
}


/*!
 * \brief Set the passed integer values for a DXF color.
 */
DxfRGBColor *
dxf_RGB_color_set
(
        int red,
                /*!< Red value for the color. */
        int green,
                /*!< Green value for the color. */
        int blue
                /*!< Blue value for the color. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_RGB_color_set () function.\n",
                __FILE__, __LINE__);
#endif
        DxfRGBColor *dxf_RGB_color;

        dxf_RGB_color = dxf_RGB_color_new ();
        if ((red <= 255) || (red >= 0))
        {
                dxf_RGB_color->r = red;
        }
        else
        {
                fprintf (stderr, "ERROR color value in dxf_RGB_color_set () out of range.\n");
                return (NULL);
        }
        if ((green <= 255) || (green >= 0))
        {
                dxf_RGB_color->g = green;
        }
        else
        {
                fprintf (stderr, "ERROR color value in dxf_RGB_color_set () out of range.\n");
                return (NULL);
        }
        if ((blue <= 255) || (blue >= 0))
        {
                dxf_RGB_color->b = blue;
        }
        else
        {
                fprintf (stderr, "ERROR color value in dxf_RGB_color_set () out of range.\n");
                return (NULL);
        }

#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_RGB_color_set () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_RGB_color);
}


/*!
 * \brief Initialise an array of colors according to the AutoCAD Color
 * Index (ACI).
 *
 * These colors are defined by red value, green value, blue value and
 * contain no alpha value (see also http://www.isctex.com/acadcolors.php).
 */
int
dxf_ACI_init
(
        DxfRGBColor *dxf_ACI[DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS]
)
{
        size_t size;

        size = sizeof (DxfRGBColor);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_ACI = malloc (size * DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_ACI_init () could not allocate memory for a DxfRGBCcolor array.\n");
                dxf_ACI = NULL;
                return (EXIT_FAILURE);
        }
        else
        {
                dxf_ACI[0] = dxf_RGB_color_set (0,0,0);
                dxf_ACI[1] = dxf_RGB_color_set (255,0,0);
                dxf_ACI[2] = dxf_RGB_color_set (255,255,0);
                dxf_ACI[3] = dxf_RGB_color_set (0,255,0);
                dxf_ACI[4] = dxf_RGB_color_set (0,255,255);
                dxf_ACI[5] = dxf_RGB_color_set (0,0,255);
                dxf_ACI[6] = dxf_RGB_color_set (255,0,255);
                dxf_ACI[7] = dxf_RGB_color_set (255,255,255);
                dxf_ACI[8] = dxf_RGB_color_set (128,128,128);
                dxf_ACI[9] = dxf_RGB_color_set (192,192,192);
                dxf_ACI[10] = dxf_RGB_color_set (255,0,0);
                dxf_ACI[11] = dxf_RGB_color_set (255,127,127);
                dxf_ACI[12] = dxf_RGB_color_set (204,0,0);
                dxf_ACI[13] = dxf_RGB_color_set (204,102,102);
                dxf_ACI[14] = dxf_RGB_color_set (153,0,0);
                dxf_ACI[15] = dxf_RGB_color_set (153,76,76);
                dxf_ACI[16] = dxf_RGB_color_set (127,0,0);
                dxf_ACI[17] = dxf_RGB_color_set (127,63,63);
                dxf_ACI[18] = dxf_RGB_color_set (76,0,0);
                dxf_ACI[19] = dxf_RGB_color_set (76,38,38);
                dxf_ACI[20] = dxf_RGB_color_set (255,63,0);
                dxf_ACI[21] = dxf_RGB_color_set (255,159,127);
                dxf_ACI[22] = dxf_RGB_color_set (204,51,0);
                dxf_ACI[23] = dxf_RGB_color_set (204,127,102);
                dxf_ACI[24] = dxf_RGB_color_set (153,38,0);
                dxf_ACI[25] = dxf_RGB_color_set (153,95,76);
                dxf_ACI[26] = dxf_RGB_color_set (127,31,0);
                dxf_ACI[27] = dxf_RGB_color_set (127,79,63);
                dxf_ACI[28] = dxf_RGB_color_set (76,19,0);
                dxf_ACI[29] = dxf_RGB_color_set (76,47,38);
                dxf_ACI[30] = dxf_RGB_color_set (255,127,0);
                dxf_ACI[31] = dxf_RGB_color_set (255,191,127);
                dxf_ACI[32] = dxf_RGB_color_set (204,102,0);
                dxf_ACI[33] = dxf_RGB_color_set (204,153,102);
                dxf_ACI[34] = dxf_RGB_color_set (153,76,0);
                dxf_ACI[35] = dxf_RGB_color_set (153,114,76);
                dxf_ACI[36] = dxf_RGB_color_set (127,63,0);
                dxf_ACI[37] = dxf_RGB_color_set (127,95,63);
                dxf_ACI[38] = dxf_RGB_color_set (76,38,0);
                dxf_ACI[39] = dxf_RGB_color_set (76,57,38);
                dxf_ACI[40] = dxf_RGB_color_set (255,191,0);
                dxf_ACI[41] = dxf_RGB_color_set (255,223,127);
                dxf_ACI[42] = dxf_RGB_color_set (204,153,0);
                dxf_ACI[43] = dxf_RGB_color_set (204,178,102);
                dxf_ACI[44] = dxf_RGB_color_set (153,114,0);
                dxf_ACI[45] = dxf_RGB_color_set (153,133,76);
                dxf_ACI[46] = dxf_RGB_color_set (127,95,0);
                dxf_ACI[47] = dxf_RGB_color_set (127,111,63);
                dxf_ACI[48] = dxf_RGB_color_set (76,57,0);
                dxf_ACI[49] = dxf_RGB_color_set (76,66,38);
                dxf_ACI[50] = dxf_RGB_color_set (255,255,0);
                dxf_ACI[51] = dxf_RGB_color_set (255,255,127);
                dxf_ACI[52] = dxf_RGB_color_set (204,204,0);
                dxf_ACI[53] = dxf_RGB_color_set (204,204,102);
                dxf_ACI[54] = dxf_RGB_color_set (153,153,0);
                dxf_ACI[55] = dxf_RGB_color_set (153,153,76);
                dxf_ACI[56] = dxf_RGB_color_set (127,127,0);
                dxf_ACI[57] = dxf_RGB_color_set (127,127,63);
                dxf_ACI[58] = dxf_RGB_color_set (76,76,0);
                dxf_ACI[59] = dxf_RGB_color_set (76,76,38);
                dxf_ACI[60] = dxf_RGB_color_set (191,255,0);
                dxf_ACI[61] = dxf_RGB_color_set (223,255,127);
                dxf_ACI[62] = dxf_RGB_color_set (153,204,0);
                dxf_ACI[63] = dxf_RGB_color_set (178,204,102);
                dxf_ACI[64] = dxf_RGB_color_set (114,153,0);
                dxf_ACI[65] = dxf_RGB_color_set (133,153,76);
                dxf_ACI[66] = dxf_RGB_color_set (95,127,0);
                dxf_ACI[67] = dxf_RGB_color_set (111,127,63);
                dxf_ACI[68] = dxf_RGB_color_set (57,76,0);
                dxf_ACI[69] = dxf_RGB_color_set (66,76,38);
                dxf_ACI[70] = dxf_RGB_color_set (127,255,0);
                dxf_ACI[71] = dxf_RGB_color_set (191,255,127);
                dxf_ACI[72] = dxf_RGB_color_set (102,204,0);
                dxf_ACI[73] = dxf_RGB_color_set (153,204,102);
                dxf_ACI[74] = dxf_RGB_color_set (76,153,0);
                dxf_ACI[75] = dxf_RGB_color_set (114,153,76);
                dxf_ACI[76] = dxf_RGB_color_set (63,127,0);
                dxf_ACI[77] = dxf_RGB_color_set (95,127,63);
                dxf_ACI[78] = dxf_RGB_color_set (38,76,0);
                dxf_ACI[79] = dxf_RGB_color_set (57,76,38);
                dxf_ACI[80] = dxf_RGB_color_set (63,255,0);
                dxf_ACI[81] = dxf_RGB_color_set (159,255,127);
                dxf_ACI[82] = dxf_RGB_color_set (51,204,0);
                dxf_ACI[83] = dxf_RGB_color_set (127,204,102);
                dxf_ACI[84] = dxf_RGB_color_set (38,153,0);
                dxf_ACI[85] = dxf_RGB_color_set (95,153,76);
                dxf_ACI[86] = dxf_RGB_color_set (31,127,0);
                dxf_ACI[87] = dxf_RGB_color_set (79,127,63);
                dxf_ACI[88] = dxf_RGB_color_set (19,76,0);
                dxf_ACI[89] = dxf_RGB_color_set (47,76,38);
                dxf_ACI[90] = dxf_RGB_color_set (0,255,0);
                dxf_ACI[91] = dxf_RGB_color_set (127,255,127);
                dxf_ACI[92] = dxf_RGB_color_set (0,204,0);
                dxf_ACI[93] = dxf_RGB_color_set (102,204,102);
                dxf_ACI[94] = dxf_RGB_color_set (0,153,0);
                dxf_ACI[95] = dxf_RGB_color_set (76,153,76);
                dxf_ACI[96] = dxf_RGB_color_set (0,127,0);
                dxf_ACI[97] = dxf_RGB_color_set (63,127,63);
                dxf_ACI[98] = dxf_RGB_color_set (0,76,0);
                dxf_ACI[99] = dxf_RGB_color_set (38,76,38);
                dxf_ACI[100] = dxf_RGB_color_set (0,255,63);
                dxf_ACI[101] = dxf_RGB_color_set (127,255,159);
                dxf_ACI[102] = dxf_RGB_color_set (0,204,51);
                dxf_ACI[103] = dxf_RGB_color_set (102,204,127);
                dxf_ACI[104] = dxf_RGB_color_set (0,153,38);
                dxf_ACI[105] = dxf_RGB_color_set (76,153,95);
                dxf_ACI[106] = dxf_RGB_color_set (0,127,31);
                dxf_ACI[107] = dxf_RGB_color_set (63,127,79);
                dxf_ACI[108] = dxf_RGB_color_set (0,76,19);
                dxf_ACI[109] = dxf_RGB_color_set (38,76,47);
                dxf_ACI[110] = dxf_RGB_color_set (0,255,127);
                dxf_ACI[111] = dxf_RGB_color_set (127,255,191);
                dxf_ACI[112] = dxf_RGB_color_set (0,204,102);
                dxf_ACI[113] = dxf_RGB_color_set (102,204,153);
                dxf_ACI[114] = dxf_RGB_color_set (0,153,76);
                dxf_ACI[115] = dxf_RGB_color_set (76,153,114);
                dxf_ACI[116] = dxf_RGB_color_set (0,127,63);
                dxf_ACI[117] = dxf_RGB_color_set (63,127,95);
                dxf_ACI[118] = dxf_RGB_color_set (0,76,38);
                dxf_ACI[119] = dxf_RGB_color_set (38,76,57);
                dxf_ACI[120] = dxf_RGB_color_set (0,255,191);
                dxf_ACI[121] = dxf_RGB_color_set (127,255,223);
                dxf_ACI[122] = dxf_RGB_color_set (0,204,153);
                dxf_ACI[123] = dxf_RGB_color_set (102,204,178);
                dxf_ACI[124] = dxf_RGB_color_set (0,153,114);
                dxf_ACI[125] = dxf_RGB_color_set (76,153,133);
                dxf_ACI[126] = dxf_RGB_color_set (0,127,95);
                dxf_ACI[127] = dxf_RGB_color_set (63,127,111);
                dxf_ACI[128] = dxf_RGB_color_set (0,76,57);
                dxf_ACI[129] = dxf_RGB_color_set (38,76,66);
                dxf_ACI[130] = dxf_RGB_color_set (0,255,255);
                dxf_ACI[131] = dxf_RGB_color_set (127,255,255);
                dxf_ACI[132] = dxf_RGB_color_set (0,204,204);
                dxf_ACI[133] = dxf_RGB_color_set (102,204,204);
                dxf_ACI[134] = dxf_RGB_color_set (0,153,153);
                dxf_ACI[135] = dxf_RGB_color_set (76,153,153);
                dxf_ACI[136] = dxf_RGB_color_set (0,127,127);
                dxf_ACI[137] = dxf_RGB_color_set (63,127,127);
                dxf_ACI[138] = dxf_RGB_color_set (0,76,76);
                dxf_ACI[139] = dxf_RGB_color_set (38,76,76);
                dxf_ACI[140] = dxf_RGB_color_set (0,191,255);
                dxf_ACI[141] = dxf_RGB_color_set (127,223,255);
                dxf_ACI[142] = dxf_RGB_color_set (0,153,204);
                dxf_ACI[143] = dxf_RGB_color_set (102,178,204);
                dxf_ACI[144] = dxf_RGB_color_set (0,114,153);
                dxf_ACI[145] = dxf_RGB_color_set (76,133,153);
                dxf_ACI[146] = dxf_RGB_color_set (0,95,127);
                dxf_ACI[147] = dxf_RGB_color_set (63,111,127);
                dxf_ACI[148] = dxf_RGB_color_set (0,57,76);
                dxf_ACI[149] = dxf_RGB_color_set (38,66,76);
                dxf_ACI[150] = dxf_RGB_color_set (0,127,255);
                dxf_ACI[151] = dxf_RGB_color_set (127,191,255);
                dxf_ACI[152] = dxf_RGB_color_set (0,102,204);
                dxf_ACI[153] = dxf_RGB_color_set (102,153,204);
                dxf_ACI[154] = dxf_RGB_color_set (0,76,153);
                dxf_ACI[155] = dxf_RGB_color_set (76,114,153);
                dxf_ACI[156] = dxf_RGB_color_set (0,63,127);
                dxf_ACI[157] = dxf_RGB_color_set (63,95,127);
                dxf_ACI[158] = dxf_RGB_color_set (0,38,76);
                dxf_ACI[159] = dxf_RGB_color_set (38,57,76);
                dxf_ACI[160] = dxf_RGB_color_set (0,63,255);
                dxf_ACI[161] = dxf_RGB_color_set (127,159,255);
                dxf_ACI[162] = dxf_RGB_color_set (0,51,204);
                dxf_ACI[163] = dxf_RGB_color_set (102,127,204);
                dxf_ACI[164] = dxf_RGB_color_set (0,38,153);
                dxf_ACI[165] = dxf_RGB_color_set (76,95,153);
                dxf_ACI[166] = dxf_RGB_color_set (0,31,127);
                dxf_ACI[167] = dxf_RGB_color_set (63,79,127);
                dxf_ACI[168] = dxf_RGB_color_set (0,19,76);
                dxf_ACI[169] = dxf_RGB_color_set (38,47,76);
                dxf_ACI[170] = dxf_RGB_color_set (0,0,255);
                dxf_ACI[171] = dxf_RGB_color_set (170,170,255);
                dxf_ACI[172] = dxf_RGB_color_set (0,0,189);
                dxf_ACI[173] = dxf_RGB_color_set (126,126,189);
                dxf_ACI[174] = dxf_RGB_color_set (0,0,129);
                dxf_ACI[175] = dxf_RGB_color_set (86,86,129);
                dxf_ACI[176] = dxf_RGB_color_set (0,0,104);
                dxf_ACI[177] = dxf_RGB_color_set (69,69,104);
                dxf_ACI[178] = dxf_RGB_color_set (0,0,79);
                dxf_ACI[179] = dxf_RGB_color_set (53,53,79);
                dxf_ACI[180] = dxf_RGB_color_set (63,0,255);
                dxf_ACI[181] = dxf_RGB_color_set (191,170,255);
                dxf_ACI[182] = dxf_RGB_color_set (46,0,189);
                dxf_ACI[183] = dxf_RGB_color_set (141,126,189);
                dxf_ACI[184] = dxf_RGB_color_set (31,0,129);
                dxf_ACI[185] = dxf_RGB_color_set (96,86,129);
                dxf_ACI[186] = dxf_RGB_color_set (25,0,104);
                dxf_ACI[187] = dxf_RGB_color_set (78,69,104);
                dxf_ACI[188] = dxf_RGB_color_set (19,0,79);
                dxf_ACI[189] = dxf_RGB_color_set (59,53,79);
                dxf_ACI[190] = dxf_RGB_color_set (127,0,255);
                dxf_ACI[191] = dxf_RGB_color_set (212,170,255);
                dxf_ACI[192] = dxf_RGB_color_set (94,0,189);
                dxf_ACI[193] = dxf_RGB_color_set (157,126,189);
                dxf_ACI[194] = dxf_RGB_color_set (64,0,129);
                dxf_ACI[195] = dxf_RGB_color_set (107,86,129);
                dxf_ACI[196] = dxf_RGB_color_set (52,0,104);
                dxf_ACI[197] = dxf_RGB_color_set (86,69,104);
                dxf_ACI[198] = dxf_RGB_color_set (39,0,79);
                dxf_ACI[199] = dxf_RGB_color_set (66,53,79);
                dxf_ACI[200] = dxf_RGB_color_set (191,0,255);
                dxf_ACI[201] = dxf_RGB_color_set (234,170,255);
                dxf_ACI[202] = dxf_RGB_color_set (141,0,189);
                dxf_ACI[203] = dxf_RGB_color_set (173,126,189);
                dxf_ACI[204] = dxf_RGB_color_set (96,0,129);
                dxf_ACI[205] = dxf_RGB_color_set (118,86,129);
                dxf_ACI[206] = dxf_RGB_color_set (78,0,104);
                dxf_ACI[207] = dxf_RGB_color_set (95,69,104);
                dxf_ACI[208] = dxf_RGB_color_set (59,0,79);
                dxf_ACI[209] = dxf_RGB_color_set (73,53,79);
                dxf_ACI[210] = dxf_RGB_color_set (255,0,255);
                dxf_ACI[211] = dxf_RGB_color_set (255,170,255);
                dxf_ACI[212] = dxf_RGB_color_set (189,0,189);
                dxf_ACI[213] = dxf_RGB_color_set (189,126,189);
                dxf_ACI[214] = dxf_RGB_color_set (129,0,129);
                dxf_ACI[215] = dxf_RGB_color_set (129,86,129);
                dxf_ACI[216] = dxf_RGB_color_set (104,0,104);
                dxf_ACI[217] = dxf_RGB_color_set (104,69,104);
                dxf_ACI[218] = dxf_RGB_color_set (79,0,79);
                dxf_ACI[219] = dxf_RGB_color_set (79,53,79);
                dxf_ACI[220] = dxf_RGB_color_set (255,0,191);
                dxf_ACI[221] = dxf_RGB_color_set (255,170,234);
                dxf_ACI[222] = dxf_RGB_color_set (189,0,141);
                dxf_ACI[223] = dxf_RGB_color_set (189,126,173);
                dxf_ACI[224] = dxf_RGB_color_set (129,0,96);
                dxf_ACI[225] = dxf_RGB_color_set (129,86,118);
                dxf_ACI[226] = dxf_RGB_color_set (104,0,78);
                dxf_ACI[227] = dxf_RGB_color_set (104,69,95);
                dxf_ACI[228] = dxf_RGB_color_set (79,0,59);
                dxf_ACI[229] = dxf_RGB_color_set (79,53,73);
                dxf_ACI[230] = dxf_RGB_color_set (255,0,127);
                dxf_ACI[231] = dxf_RGB_color_set (255,170,212);
                dxf_ACI[232] = dxf_RGB_color_set (189,0,94);
                dxf_ACI[233] = dxf_RGB_color_set (189,126,157);
                dxf_ACI[234] = dxf_RGB_color_set (129,0,64);
                dxf_ACI[235] = dxf_RGB_color_set (129,86,107);
                dxf_ACI[236] = dxf_RGB_color_set (104,0,52);
                dxf_ACI[237] = dxf_RGB_color_set (104,69,86);
                dxf_ACI[238] = dxf_RGB_color_set (79,0,39);
                dxf_ACI[239] = dxf_RGB_color_set (79,53,66);
                dxf_ACI[240] = dxf_RGB_color_set (255,0,63);
                dxf_ACI[241] = dxf_RGB_color_set (255,170,191);
                dxf_ACI[242] = dxf_RGB_color_set (189,0,46);
                dxf_ACI[243] = dxf_RGB_color_set (189,126,141);
                dxf_ACI[244] = dxf_RGB_color_set (129,0,31);
                dxf_ACI[245] = dxf_RGB_color_set (129,86,96);
                dxf_ACI[246] = dxf_RGB_color_set (104,0,25);
                dxf_ACI[247] = dxf_RGB_color_set (104,69,78);
                dxf_ACI[248] = dxf_RGB_color_set (79,0,19);
                dxf_ACI[249] = dxf_RGB_color_set (79,53,59);
                dxf_ACI[250] = dxf_RGB_color_set (51,51,51);
                dxf_ACI[251] = dxf_RGB_color_set (80,80,80);
                dxf_ACI[252] = dxf_RGB_color_set (105,105,105);
                dxf_ACI[253] = dxf_RGB_color_set (130,130,130);
                dxf_ACI[254] = dxf_RGB_color_set (190,190,190);
                dxf_ACI[255] = dxf_RGB_color_set (255,255,255);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Color names according to the Wikipedia List of Colors.
 *
 * These color names are defined by Wikipedia's
 * <a href="http://en.wikipedia.org/wiki/List_of_colors">
 * List of colors</a>\n
 * \c dxf_RGB_color_name[hex_triplet], where \c hex_triplet are the
 * hexadecimal values as in red value, green value, blue value
 * (0xRRGGBB) and this index contains no alpha values.
typedef enum
dxf_RGB_color_name
{
        dxf_RGB_color_name[0xF0F8FF] = "Alice blue",
        dxf_RGB_color_name[0xE32636] = "Alizarin",
        dxf_RGB_color_name[0xE52B50] = "Amaranth",
        dxf_RGB_color_name[0xF19CBB] = "Amaranth Pink",
        dxf_RGB_color_name[0xFFBF00] = "Amber",
        dxf_RGB_color_name[0x9966CC] = "Amethyst",
        dxf_RGB_color_name[0xFBCEB1] = "Apricot",
        dxf_RGB_color_name[0x00FFFF] = "Aqua",
        dxf_RGB_color_name[0x7FFFD4] = "Aquamarine"
        dxf_RGB_color_name[0x4B5320] = "Aemy green",
        dxf_RGB_color_name[0x7BA05B] = "Asparagus",
        dxf_RGB_color_name[0xFF9966] = "Atomic tangerine",
        dxf_RGB_color_name[0x6D351A] = "Auburn",
        dxf_RGB_color_name[0x007FFF] = "Azure (color wheel)",
        dxf_RGB_color_name[0xF0FFFF] = "Azure (web)",
        dxf_RGB_color_name[0xE0FFFF] = "Baby blue",
        dxf_RGB_color_name[0xF5F5DC] = "Beige",
        dxf_RGB_color_name[0x3D2B1F] = "Bistre",
        dxf_RGB_color_name[0x000000] = "Black",
        dxf_RGB_color_name[0x0000FF] = "Blue",
        dxf_RGB_color_name[0x333399] = "Blue (pigment)",
        dxf_RGB_color_name[0x0247FE] = "Blue (RYB)",
        dxf_RGB_color_name[0x00DDDD] = "Blue-green",
        dxf_RGB_color_name[0x8A2BE2] = "Blue-violet",
        dxf_RGB_color_name[0x0095B6] = "Bondi blue",
        dxf_RGB_color_name[0xB5A642] = "Brass",
        dxf_RGB_color_name[0x66FF00] = "Bright green",
        dxf_RGB_color_name[0xFF007F] = "Bright pink",
        dxf_RGB_color_name[0x08E8DE] = "Bright turquoise",
        dxf_RGB_color_name[0xFF55A3] = "Brilliant rose",
        dxf_RGB_color_name[0xFB607F] = "Brink pink",
        dxf_RGB_color_name[0xCD7F32] = "Bronze",
        dxf_RGB_color_name[0x964B00] = "Brown",
        dxf_RGB_color_name[0xF0DC82] = "Buff",
        dxf_RGB_color_name[0x900020] = "Burgundy",
        dxf_RGB_color_name[0xCC5500] = "Burnt orange",
        dxf_RGB_color_name[0xE97451] = "Burnt sienna",
        dxf_RGB_color_name[0x8A3324] = "Burnt umber",
        dxf_RGB_color_name[0x78866B] = "Camouflage green",
        dxf_RGB_color_name[0x592720] = "Caput mortuum",
        dxf_RGB_color_name[0xC41E3A] = "Cardinal",
        dxf_RGB_color_name[0x960018] = "Carmine",
        dxf_RGB_color_name[0xEB4C42] = "Carmine Pink",
        dxf_RGB_color_name[0xFFA6C9] = "Carnation pink",
        dxf_RGB_color_name[0x99BADD] = "Carolina blue",
        dxf_RGB_color_name[0xED9121] = "Carrot orange",
        dxf_RGB_color_name[0xACE1AF] = "Celadon",
        dxf_RGB_color_name[0xDE3163] = "Cerise",
        dxf_RGB_color_name[0xEC3B83] = "Cerise Pink",
        dxf_RGB_color_name[0x007BA7] = "Cerulean",
        dxf_RGB_color_name[0x2A52BE] = "Cerulean blue",
        dxf_RGB_color_name[0xF7E7CE] = "Champagne",
        dxf_RGB_color_name[0x464646] = "Charcoal",
        dxf_RGB_color_name[0xDFFF00] = "Chartreuse (traditional)",
        dxf_RGB_color_name[0x7FFF00] = "Chartreuse (web)",
        dxf_RGB_color_name[0xFFB7C5] = "Cherry blossom pink",
        dxf_RGB_color_name[0xCD5C5C] = "Chestnut",
        dxf_RGB_color_name[0x7B3F00] = "Chocolate",
        dxf_RGB_color_name[0xE34234] = "Cinnabar",
        dxf_RGB_color_name[0xD2691E] = "Cinnamon",
        dxf_RGB_color_name[0x0047AB] = "Cobalt",
        dxf_RGB_color_name[0x9BDDFF] = "Columbia blue",
        dxf_RGB_color_name[0xB87333] = "Copper",
        dxf_RGB_color_name[0x996666] = "Copper rose",
        dxf_RGB_color_name[0xFF7F50] = "Coral",
        dxf_RGB_color_name[0xF88379] = "Coral pink",
        dxf_RGB_color_name[0xFF4040] = "Coral red",
        dxf_RGB_color_name[0xFBEC5D] = "Corn",
        dxf_RGB_color_name[0x6495ED] = "Cornflower blue",
        dxf_RGB_color_name[0xFFF8E7] = "Cosmic latte",
        dxf_RGB_color_name[0xFFFDD0] = "Cream",
        dxf_RGB_color_name[0xDC143C] = "Crimson",
        dxf_RGB_color_name[0x00FFFF] = "Cyan",
        dxf_RGB_color_name[0x00B7EB] = "Cyan (process)",
        dxf_RGB_color_name[0x00008B] = "Dark blue",
        dxf_RGB_color_name[0x654321] = "Dark brown",
        dxf_RGB_color_name[0x08457E] = "Dark cerulean",
        dxf_RGB_color_name[0x986960] = "Dark chestnut",
        dxf_RGB_color_name[0xCD5B45] = "Dark coral",
        dxf_RGB_color_name[0xB8860B] = "Dark goldenrod",
        dxf_RGB_color_name[0x013220] = "Dark green",
        dxf_RGB_color_name[0xBDB76B] = "Dark khaki",
        dxf_RGB_color_name[0x8B008B] = "Dark magenta",
        dxf_RGB_color_name[0x03C03C] = "Dark pastel green",
        dxf_RGB_color_name[0xE75480] = "Dark pink",
        dxf_RGB_color_name[0x560319] = "Dark scarlet",
        dxf_RGB_color_name[0xE9967A] = "Dark salmon",
        dxf_RGB_color_name[0x2F4F4F] = "Dark slate gray",
        dxf_RGB_color_name[0x177245] = "Dark spring green",
        dxf_RGB_color_name[0x918151] = "Dark tan",
        dxf_RGB_color_name[0x00CED1] = "Dark turquoise",
        dxf_RGB_color_name[0x9400D3] = "Dark violet",
        dxf_RGB_color_name[0xEF3038] = "Deep Carmine Pink",
        dxf_RGB_color_name[0xDA3287] = "Deep cerise",
        dxf_RGB_color_name[0xB94E48] = "Deep chestnut",
        dxf_RGB_color_name[0xC154C1] = "Deep fuchsia",
        dxf_RGB_color_name[0x9955BB] = "Deep lilac",
        dxf_RGB_color_name[0xCD00CC] = "Deep magenta",
        dxf_RGB_color_name[0xFFCBA4] = "Deep peach",
        dxf_RGB_color_name[0xFF1493] = "Deep pink",
        dxf_RGB_color_name[0x1560BD] = "Denim",
        dxf_RGB_color_name[0x1E90FF] = "Dodger blue",
        dxf_RGB_color_name[0xC2B280] = "Ecru",
        dxf_RGB_color_name[0x1034A6] = "Egyptian blue",
        dxf_RGB_color_name[0x7DF9FF] = "Electric blue",
        dxf_RGB_color_name[0x00FF00] = "Electric green (X11 green)",
        dxf_RGB_color_name[0x6600FF] = "Electric indigo",
        dxf_RGB_color_name[0xCCFF00] = "Electric lime",
        dxf_RGB_color_name[0xBF00FF] = "Electric purple",
        dxf_RGB_color_name[0x50C878] = "Emerald",
        dxf_RGB_color_name[0x614051] = "Eggplant",
        dxf_RGB_color_name[0x801818] = "Falu red",
        dxf_RGB_color_name[0x4F7942] = "Fern green",
        dxf_RGB_color_name[0xB22222] = "Firebrick",
        dxf_RGB_color_name[0xEEDC82] = "Flax",
        dxf_RGB_color_name[0x228B22] = "Forrest green",
        dxf_RGB_color_name[0xF64A8A] = "French Rose",
        dxf_RGB_color_name[0xFF00FF] = "Fuchsia",
        dxf_RGB_color_name[0xFF77FF] = "Fuchsia Pink",
        dxf_RGB_color_name[0xE49B0F] = "Gamboge",
        dxf_RGB_color_name[0xD4AF37] = "Gold (metallic)",
        dxf_RGB_color_name[0xFFD700] = "Gold (web) (Golden)",
        dxf_RGB_color_name[0x996515] = "Golden brown",
        dxf_RGB_color_name[0xFFDF00] = "Golden yellow",
        dxf_RGB_color_name[0xDAA520] = "Goldenrod",
        dxf_RGB_color_name[0x465945] = "Gray-asparagus",
        dxf_RGB_color_name[0x00FF00] = "Green (color wheel) (X11 green)",
        dxf_RGB_color_name[0x008000] = "Green (HTML/CSS green)",
        dxf_RGB_color_name[0x00A550] = "Green (pigment)",
        dxf_RGB_color_name[0x66B032] = "Green (RYB)",
        dxf_RGB_color_name[0xADFF2F] = "Green-yellow",
        dxf_RGB_color_name[0x808080] = "Gray",
        dxf_RGB_color_name[0x5218FA] = "Han Purple",
        dxf_RGB_color_name[0x3FFF00] = "Harlequin",
        dxf_RGB_color_name[0xDF73FF] = "Heliotrope",
        dxf_RGB_color_name[0xF400A1] = "Hollywood Cerise",
        dxf_RGB_color_name[0xFF00CC] = "Hot Magenta",
        dxf_RGB_color_name[0xFF69B4] = "Hot Pink",
        dxf_RGB_color_name[0x00416A] = "Indigo (dye)",
        dxf_RGB_color_name[0x4B0082] = "Indigo (web)",
        dxf_RGB_color_name[0x002FA7] = "International Klein Blue",
        dxf_RGB_color_name[0xFF4F00] = "International orange",
        dxf_RGB_color_name[0x009000] = "Islamic green",
        dxf_RGB_color_name[0xFFFFF0] = "Ivory",
        dxf_RGB_color_name[0x00A86B] = "Jade",
        dxf_RGB_color_name[0x4CBB17] = "Kelly green",
        dxf_RGB_color_name[0xC3B091] = "Khaki",
        dxf_RGB_color_name[0xF0E68C] = "Khaki (X11) (Light khaki)",
        dxf_RGB_color_name[0xB57EDC] = "Lavender (floral)",
        dxf_RGB_color_name[0xE6E6FA] = "Lavender (web)",
        dxf_RGB_color_name[0xCCCCFF] = "Lavender blue",
        dxf_RGB_color_name[0xFFF0F5] = "Lavender blush",
        dxf_RGB_color_name[0xC4C3D0] = "Lavender gray",
        dxf_RGB_color_name[0xEE82EE] = "Lavender magenta",
        dxf_RGB_color_name[0xFBAED2] = "Lavender pink",
        dxf_RGB_color_name[0x967BB6] = "Lavender purple",
        dxf_RGB_color_name[0xFBA0E3] = "Lavender rose",
        dxf_RGB_color_name[0x7CFC00] = "Lawn green",
        dxf_RGB_color_name[0xFDE910] = "Lemon",
        dxf_RGB_color_name[0xFFFACD] = "Lemon chifton",
        dxf_RGB_color_name[0xADD8E6] = "Light blue",
        dxf_RGB_color_name[0xFFB6C1] = "Light pink",
        dxf_RGB_color_name[0xC8A2C8] = "Lilac",
        dxf_RGB_color_name[0xBFFF00] = "Lime (color wheel)",
        dxf_RGB_color_name[0x00FF00] = "Lime (web) (X11 green)",
        dxf_RGB_color_name[0x32CD32] = "Lime green",
        dxf_RGB_color_name[0xFAF0E6] = "Linen",
        dxf_RGB_color_name[0xFF00FF] = "Magenta",
        dxf_RGB_color_name[0xCA1F7B] = "Magenta (dye)",
        dxf_RGB_color_name[0xFF0090] = "Magenta (process)",
        dxf_RGB_color_name[0xAAF0D1] = "Magic mint",
        dxf_RGB_color_name[0xF8F4FF] = "Magnolia",
        dxf_RGB_color_name[0x0BDA51] = "Malachite",
        dxf_RGB_color_name[0x800000] = "Maroon (HTML/CSS)",
        dxf_RGB_color_name[0xB03060] = "Maroon (X11)",
        dxf_RGB_color_name[0x73C2FB] = "Maya blue",
        dxf_RGB_color_name[0xE0B0FF] = "Mauve",
        dxf_RGB_color_name[0x915F6D] = "Mauve Taupe",
        dxf_RGB_color_name[0x0000CD] = "Medium blue",
        dxf_RGB_color_name[0xAF4035] = "Medium carmine",
        dxf_RGB_color_name[0xCC99CC] = "Medium lavender magenta",
        dxf_RGB_color_name[0x9370DB] = "Medium purple",
        dxf_RGB_color_name[0x00FA9A] = "Medium spring green",
        dxf_RGB_color_name[0x191970] = "Midnight Blue",
        dxf_RGB_color_name[0x004953] = "Midnight Green (Eagle Green)",
        dxf_RGB_color_name[0x98FF98] = "Mint green",
        dxf_RGB_color_name[0xFFE4E1] = "Misty rose",
        dxf_RGB_color_name[0xADDFAD] = "Moss green",
        dxf_RGB_color_name[0x997A8D] = "Mountbatten pink",
        dxf_RGB_color_name[0xFFDB58] = "Mustard",
        dxf_RGB_color_name[0x21421E] = "Myrtle",
        dxf_RGB_color_name[0x006633] = "MSU Green",
        dxf_RGB_color_name[0xFFDEAD] = "Navajo white",
        dxf_RGB_color_name[0x000080] = "Navy Blue",
        dxf_RGB_color_name[0xCC7722] = "Ochre",
        dxf_RGB_color_name[0x008000] = "Office green",
        dxf_RGB_color_name[0xCFB53B] = "Old Gold",
        dxf_RGB_color_name[0xFDF5E6] = "Old Lace",
        dxf_RGB_color_name[0x796878] = "Old Lavender",
        dxf_RGB_color_name[0xC08081] = "Old Rose",
        dxf_RGB_color_name[0x808000] = "Olive",
        dxf_RGB_color_name[0x6B8E23] = "Olive Drab",
        dxf_RGB_color_name[0x9AB973] = "Olivine",
        dxf_RGB_color_name[0xFF7F00] = "Orange (color wheel)",
        dxf_RGB_color_name[0xFB9902] = "Orange (RYB)",
        dxf_RGB_color_name[0xFFA500] = "Orange (web)",
        dxf_RGB_color_name[0xFFA000] = "Orange Peel",
        dxf_RGB_color_name[0xFF4500] = "Orange-Red",
        dxf_RGB_color_name[0xDA70D6] = "Orchid",
        dxf_RGB_color_name[0xAFEEEE] = "Pale blue",
        dxf_RGB_color_name[0x987654] = "Pale brown",
        dxf_RGB_color_name[0xAF4035] = "Pale carmine",
        dxf_RGB_color_name[0xDDADAF] = "Pale chestnut",
        dxf_RGB_color_name[0xABCDEF] = "Pale cornflower blue",
        dxf_RGB_color_name[0xF984E5] = "Pale magenta",
        dxf_RGB_color_name[0xFADADD] = "Pale pink",
        dxf_RGB_color_name[0xDB7093] = "Pale red-violet",
        dxf_RGB_color_name[0xBC987E] = "Pale taupe",
        dxf_RGB_color_name[0xFFEFD5] = "Papaya whip",
        dxf_RGB_color_name[0x77DD77] = "Pastel green",
        dxf_RGB_color_name[0xFFD1DC] = "Pastel pink",
        dxf_RGB_color_name[0x40404F] = "Payne's grey",
        dxf_RGB_color_name[0xFFE5B4] = "Peach",
        dxf_RGB_color_name[0xFFCC99] = "Peach-orange",
        dxf_RGB_color_name[0xFADFAD] = "Peach-yellow",
        dxf_RGB_color_name[0xD1E231] = "Pear",
        dxf_RGB_color_name[0xCCCCFF] = "Periwinkle",
        dxf_RGB_color_name[0x1C39BB] = "Persian blue",
        dxf_RGB_color_name[0x00A693] = "Persian green",
        dxf_RGB_color_name[0x32127A] = "Persian indigo",
        dxf_RGB_color_name[0xD99058] = "Persian orange",
        dxf_RGB_color_name[0xCC3333] = "Persian red",
        dxf_RGB_color_name[0xF77FBE] = "Persian pink",
        dxf_RGB_color_name[0xFE28A2] = "Persian rose",
        dxf_RGB_color_name[0xEC5800] = "Persimmon",
        dxf_RGB_color_name[0x01796F] = "Pine green",
        dxf_RGB_color_name[0xFFC0CB] = "Pink",
        dxf_RGB_color_name[0xFF9966] = "Pink-orange",
        dxf_RGB_color_name[0xE5E4E2] = "Platinum",
        dxf_RGB_color_name[0xCC99CC] = "Plum (web)",
        dxf_RGB_color_name[0xFF5A36] = "Portland Orange",
        dxf_RGB_color_name[0xB0E0E6] = "Powder blue (web)",
        dxf_RGB_color_name[0xCC8899] = "Puce",
        dxf_RGB_color_name[0x003153] = "Prusian blue",
        dxf_RGB_color_name[0xDD00FF] = "Psychedelic purple",
        dxf_RGB_color_name[0xFF7518] = "Pumpkin",
        dxf_RGB_color_name[0x7F007F] = "Purple (HTML/CSS)",
        dxf_RGB_color_name[0xA020F0] = "Purple (X11)",
        dxf_RGB_color_name[0x50404D] = "Purple Taupe",
        dxf_RGB_color_name[0xE30B5C] = "Raspberry",
        dxf_RGB_color_name[0x734A12] = "Raw umber",
        dxf_RGB_color_name[0xE3256B] = "Razzmatazz",
        dxf_RGB_color_name[0xFF0000] = "Red",
        dxf_RGB_color_name[0xED1C24] = "Red (pigment)",
        dxf_RGB_color_name[0xFE2712] = "Red (RYB)",
        dxf_RGB_color_name[0xC71585] = "Red-violet",
        dxf_RGB_color_name[0xD70040] = "Rich carmine",
        dxf_RGB_color_name[0x00CCCC] = "Robin egg blue",
        dxf_RGB_color_name[0xFF007F] = "Rose",
        dxf_RGB_color_name[0xE32636] = "Rose Madder",
        dxf_RGB_color_name[0xFF66CC] = "Rose pink",
        dxf_RGB_color_name[0xAA98A9] = "Rose quartz",
        dxf_RGB_color_name[0x905D5D] = "Rose Taupe",
        dxf_RGB_color_name[0x4169E1] = "Royal blue",
        dxf_RGB_color_name[0x6B3FA0] = "Royal purple",
        dxf_RGB_color_name[0xE0115F] = "Ruby",
        dxf_RGB_color_name[0x80461B] = "Russet",
        dxf_RGB_color_name[0xB7410E] = "Rust",
        dxf_RGB_color_name[0xFF6600] = "Safety orange (blaze orange)",
        dxf_RGB_color_name[0xF4C430] = "Saffron",
        dxf_RGB_color_name[0xFF8C69] = "Salmon",
        dxf_RGB_color_name[0xFF91A4] = "Salmon pink",
        dxf_RGB_color_name[0xF4A460] = "Sandy brown",
        dxf_RGB_color_name[0x92000A] = "Sangria",
        dxf_RGB_color_name[0x082567] = "Sapphire",
        dxf_RGB_color_name[0xFF2400] = "Scarlet",
        dxf_RGB_color_name[0xFFD800] = "School bus yellow",
        dxf_RGB_color_name[0x2E8B57] = "Sea green",
        dxf_RGB_color_name[0x321414] = "Seal brown",
        dxf_RGB_color_name[0xFFF5EE] = "Seashell",
        dxf_RGB_color_name[0xFFBA00] = "Selective yellow",
        dxf_RGB_color_name[0x704214] = "Sepia",
        dxf_RGB_color_name[0x009E60] = "Shamrock green",
        dxf_RGB_color_name[0xFC0FC0] = "Shocking pink",
        dxf_RGB_color_name[0xA0522D] = "Sienna",
        dxf_RGB_color_name[0xC0C0C0] = "Silver",
        dxf_RGB_color_name[0x87CEEB] = "Sky Blue",
        dxf_RGB_color_name[0x708090] = "Slate grey",
        dxf_RGB_color_name[0x003399] = "Smalt (Dark powder blue)",
        dxf_RGB_color_name[0xA7FC00] = "Spring bud",
        dxf_RGB_color_name[0x00FF7F] = "Spring green",
        dxf_RGB_color_name[0x4682B4] = "Steel blue",
        dxf_RGB_color_name[0xD2B48C] = "Tan",
        dxf_RGB_color_name[0xF28500] = "Tangerine",
        dxf_RGB_color_name[0xFFCC00] = "Tangerine yellow",
        dxf_RGB_color_name[0x483C32] = "Taupe",
        dxf_RGB_color_name[0x8B8589] = "Taupe gray",
        dxf_RGB_color_name[0xD0F0C0] = "Tea green",
        dxf_RGB_color_name[0xF88379] = "Tea rose (orange)",
        dxf_RGB_color_name[0xF4C2C2] = "Tea rose (rose)",
        dxf_RGB_color_name[0x008080] = "Teal",
        dxf_RGB_color_name[0xCD5700] = "Tenné (Tawny)",
        dxf_RGB_color_name[0xE2725B] = "Terra cotta",
        dxf_RGB_color_name[0xD8BFD8] = "Thistle",
        dxf_RGB_color_name[0xDE6FA1] = "Thullian pink",
        dxf_RGB_color_name[0xFF6347] = "Tomato",
        dxf_RGB_color_name[0x30D5C8] = "Turquoise",
        dxf_RGB_color_name[0x66023C] = "Tyrian Purple",
        dxf_RGB_color_name[0x120A8F] = "Ultramarine",
        dxf_RGB_color_name[0xFF6FFF] = "Ultra pink",
        dxf_RGB_color_name[0x5B92E5] = "United Nations blue",
        dxf_RGB_color_name[0xAE2029] = "Upsdell red",
        dxf_RGB_color_name[0xC5B358] = "Vegas Gold",
        dxf_RGB_color_name[0xC80815] = "Venetian red",
        dxf_RGB_color_name[0xE34234] = "Vermilion",
        dxf_RGB_color_name[0x8B00FF] = "Violet",
        dxf_RGB_color_name[0xEE82EE] = "Violet (web)",
        dxf_RGB_color_name[0x8601AF] = "Violet (RYB)",
        dxf_RGB_color_name[0x40826D] = "Viridian",
        dxf_RGB_color_name[0xF5DEB3] = "Wheat",
        dxf_RGB_color_name[0xFFFFFF] = "White",
        dxf_RGB_color_name[0xC9A0DC] = "Wisteria",
        dxf_RGB_color_name[0x738678] = "Xanadu",
        dxf_RGB_color_name[0x0F4D92] = "Yale Blue",
        dxf_RGB_color_name[0xFFFF00] = "Yellow",
        dxf_RGB_color_name[0xFFEF00] = "Yellow (process)",
        dxf_RGB_color_name[0xFEFE33] = "Yellow (RYB)",
        dxf_RGB_color_name[0x9ACD32] = "Yellow-green"
}
DxfRGBColorName;
 */


/* EOF */
