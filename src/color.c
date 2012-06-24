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


/* EOF */
