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
        int triplet;
        char *name = NULL;

        dxf_RGB_color = dxf_RGB_color_new ();
        if ((red <= 255) || (red >= 0))
        {
                dxf_RGB_color->r = red;
        }
        else
        {
                fprintf (stderr, "ERROR red color value in dxf_RGB_color_set () out of range.\n");
                return (NULL);
        }
        if ((green <= 255) || (green >= 0))
        {
                dxf_RGB_color->g = green;
        }
        else
        {
                fprintf (stderr, "ERROR green color value in dxf_RGB_color_set () out of range.\n");
                return (NULL);
        }
        if ((blue <= 255) || (blue >= 0))
        {
                dxf_RGB_color->b = blue;
        }
        else
        {
                fprintf (stderr, "ERROR blue color value in dxf_RGB_color_set () out of range.\n");
                return (NULL);
        }
        triplet = dxf_RGB_to_triplet (red, green, blue);
        name = dxf_RGB_color_get_name (triplet);
        if (name != NULL)
        {
                dxf_RGB_color->name = strdup (name);
                free (name);
        }
        else
        {
                fprintf (stderr, "ERROR name value in dxf_RGB_color_set () contains a NULL pointer.\n");
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
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ACI_init () function.\n",
                __FILE__, __LINE__);
#endif
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
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ACI_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Convert the passed integer values to a hexadecimal triplet.
 */
int
dxf_RGB_to_triplet
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_RGB_to_triplet () function.\n",
                __FILE__, __LINE__);
#endif
        int triplet;

        if ((red <= 255) || (red >= 0))
        {
                triplet = red * 65536;
        }
        else
        {
                fprintf (stderr, "ERROR red color value in dxf_RGB_to_triplet () out of range.\n");
                return (-1);
        }
        if ((green <= 255) || (green >= 0))
        {
                triplet += green * 256;
        }
        else
        {
                fprintf (stderr, "ERROR green color value in dxf_RGB_to_triplet () out of range.\n");
                return (-2);
        }
        if ((blue <= 255) || (blue >= 0))
        {
                triplet += blue;
        }
        else
        {
                fprintf (stderr, "ERROR blue color value in dxf_RGB_to_triplet () out of range.\n");
                return (-3);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_RGB_to_triplet () function.\n",
                __FILE__, __LINE__);
#endif
        return (triplet);
}


/*!
 * \brief Return the color name according to the Wikipedia List of 
 * Colors.
 *
 * These color names are defined by Wikipedia's
 * <a href="http://en.wikipedia.org/wiki/List_of_colors">
 * List of colors</a>.
 */
char *
dxf_RGB_color_get_name
(
        int RGB_color_hex_triplet
        /*!< \c dxf_RGB_color_hex_triplet is assumed to contain the
         * hexadecimal values as in red value, green value, blue value
         * in the order 0xRRGGBB (contains no alpha values).
         */
)
{
        char *dxf_RGB_color_get_name;

        switch (RGB_color_hex_triplet)
        {
                case 0xF0F8FF :
                {
                        dxf_RGB_color_get_name = strdup ("Alice blue");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xE32636 :
                {
                        dxf_RGB_color_get_name = strdup ("Alizarin");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0xE52B50 :
                {
                        dxf_RGB_color_get_name = strdup ("Amaranth");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF19CBB :
                {
                        dxf_RGB_color_get_name = strdup ("Amaranth Pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFBF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Amber");
                        return (dxf_RGB_color_get_name);
                }
                case 0x9966CC :
                {
                        dxf_RGB_color_get_name = strdup ("Amethyst");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFBCEB1 :
                {
                        dxf_RGB_color_get_name = strdup ("Apricot");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0x00FFFF :
                {
                        dxf_RGB_color_get_name = strdup ("Aqua");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0x7FFFD4 :
                {
                        dxf_RGB_color_get_name = strdup ("Aquamarine");
                        return (dxf_RGB_color_get_name);
                }
                case 0x4B5320 :
                {
                        dxf_RGB_color_get_name = strdup ("Aemy green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x7BA05B :
                {
                        dxf_RGB_color_get_name = strdup ("Asparagus");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xFF9966 :
                {
                        dxf_RGB_color_get_name = strdup ("Atomic tangerine");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0x6D351A :
                {
                        dxf_RGB_color_get_name = strdup ("Auburn");
                        return (dxf_RGB_color_get_name);
                }
                case 0x007FFF :
                {
                        dxf_RGB_color_get_name = strdup ("Azure (color wheel)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF0FFFF :
                {
                        dxf_RGB_color_get_name = strdup ("Azure (web)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE0FFFF :
                {
                        dxf_RGB_color_get_name = strdup ("Baby blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF5F5DC :
                {
                        dxf_RGB_color_get_name = strdup ("Beige");
                        return (dxf_RGB_color_get_name);
                }
                case 0x3D2B1F :
                {
                        dxf_RGB_color_get_name = strdup ("Bistre");
                        return (dxf_RGB_color_get_name);
                }
                case 0x000000 :
                {
                        dxf_RGB_color_get_name = strdup ("Black");
                        return (dxf_RGB_color_get_name);
                }
                case 0x0000FF :
                {
                        dxf_RGB_color_get_name = strdup ("Blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0x333399 :
                {
                        dxf_RGB_color_get_name = strdup ("Blue (pigment)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x0247FE :
                {
                        dxf_RGB_color_get_name = strdup ("Blue (RYB)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00DDDD :
                {
                        dxf_RGB_color_get_name = strdup ("Blue-green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x8A2BE2 :
                {
                        dxf_RGB_color_get_name = strdup ("Blue-violet");
                        return (dxf_RGB_color_get_name);
                }
                case 0x0095B6 :
                {
                        dxf_RGB_color_get_name = strdup ("Bondi blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xB5A642 :
                {
                        dxf_RGB_color_get_name = strdup ("Brass");
                        return (dxf_RGB_color_get_name);
                }
                case 0x66FF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Bright green");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xFF007F :
                {
                        dxf_RGB_color_get_name = strdup ("Bright pink");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0x08E8DE :
                {
                        dxf_RGB_color_get_name = strdup ("Bright turquoise");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF55A3 :
                {
                        dxf_RGB_color_get_name = strdup ("Brilliant rose");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFB607F :
                {
                        dxf_RGB_color_get_name = strdup ("Brink pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCD7F32 :
                {
                        dxf_RGB_color_get_name = strdup ("Bronze");
                        return (dxf_RGB_color_get_name);
                }
                case 0x964B00 :
                {
                        dxf_RGB_color_get_name = strdup ("Brown");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF0DC82 :
                {
                        dxf_RGB_color_get_name = strdup ("Buff");
                        return (dxf_RGB_color_get_name);
                }
                case 0x900020 :
                {
                        dxf_RGB_color_get_name = strdup ("Burgundy");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCC5500 :
                {
                        dxf_RGB_color_get_name = strdup ("Burnt orange");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE97451 :
                {
                        dxf_RGB_color_get_name = strdup ("Burnt sienna");
                        return (dxf_RGB_color_get_name);
                }
                case 0x8A3324 :
                {
                        dxf_RGB_color_get_name = strdup ("Burnt umber");
                        return (dxf_RGB_color_get_name);
                }
                case 0x78866B :
                {
                        dxf_RGB_color_get_name = strdup ("Camouflage green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x592720 :
                {
                        dxf_RGB_color_get_name = strdup ("Caput mortuum");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC41E3A :
                {
                        dxf_RGB_color_get_name = strdup ("Cardinal");
                        return (dxf_RGB_color_get_name);
                }
                case 0x960018 :
                {
                        dxf_RGB_color_get_name = strdup ("Carmine");
                        return (dxf_RGB_color_get_name);
                }
                case 0xEB4C42 :
                {
                        dxf_RGB_color_get_name = strdup ("Carmine Pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFA6C9 :
                {
                        dxf_RGB_color_get_name = strdup ("Carnation pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0x99BADD :
                {
                        dxf_RGB_color_get_name = strdup ("Carolina blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xED9121 :
                {
                        dxf_RGB_color_get_name = strdup ("Carrot orange");
                        return (dxf_RGB_color_get_name);
                }
                case 0xACE1AF :
                {
                        dxf_RGB_color_get_name = strdup ("Celadon");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDE3163 :
                {
                        dxf_RGB_color_get_name = strdup ("Cerise");
                        return (dxf_RGB_color_get_name);
                }
                case 0xEC3B83 :
                {
                        dxf_RGB_color_get_name = strdup ("Cerise Pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0x007BA7 :
                {
                        dxf_RGB_color_get_name = strdup ("Cerulean");
                        return (dxf_RGB_color_get_name);
                }
                case 0x2A52BE :
                {
                        dxf_RGB_color_get_name = strdup ("Cerulean blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF7E7CE :
                {
                        dxf_RGB_color_get_name = strdup ("Champagne");
                        return (dxf_RGB_color_get_name);
                }
                case 0x464646 :
                {
                        dxf_RGB_color_get_name = strdup ("Charcoal");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDFFF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Chartreuse (traditional)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x7FFF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Chartreuse (web)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFB7C5 :
                {
                        dxf_RGB_color_get_name = strdup ("Cherry blossom pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCD5C5C :
                {
                        dxf_RGB_color_get_name = strdup ("Chestnut");
                        return (dxf_RGB_color_get_name);
                }
                case 0x7B3F00 :
                {
                        dxf_RGB_color_get_name = strdup ("Chocolate");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xE34234 :
                {
                        dxf_RGB_color_get_name = strdup ("Cinnabar");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0xD2691E :
                {
                        dxf_RGB_color_get_name = strdup ("Cinnamon");
                        return (dxf_RGB_color_get_name);
                }
                case 0x0047AB :
                {
                        dxf_RGB_color_get_name = strdup ("Cobalt");
                        return (dxf_RGB_color_get_name);
                }
                case 0x9BDDFF :
                {
                        dxf_RGB_color_get_name = strdup ("Columbia blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xB87333 :
                {
                        dxf_RGB_color_get_name = strdup ("Copper");
                        return (dxf_RGB_color_get_name);
                }
                case 0x996666 :
                {
                        dxf_RGB_color_get_name = strdup ("Copper rose");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF7F50 :
                {
                        dxf_RGB_color_get_name = strdup ("Coral");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF88379 :
                {
                        dxf_RGB_color_get_name = strdup ("Coral pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF4040 :
                {
                        dxf_RGB_color_get_name = strdup ("Coral red");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFBEC5D :
                {
                        dxf_RGB_color_get_name = strdup ("Corn");
                        return (dxf_RGB_color_get_name);
                }
                case 0x6495ED :
                {
                        dxf_RGB_color_get_name = strdup ("Cornflower blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFF8E7 :
                {
                        dxf_RGB_color_get_name = strdup ("Cosmic latte");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFFDD0 :
                {
                        dxf_RGB_color_get_name = strdup ("Cream");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDC143C :
                {
                        dxf_RGB_color_get_name = strdup ("Crimson");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00FFFF :
                {
                        dxf_RGB_color_get_name = strdup ("Cyan");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00B7EB :
                {
                        dxf_RGB_color_get_name = strdup ("Cyan (process)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00008B :
                {
                        dxf_RGB_color_get_name = strdup ("Dark blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0x654321 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark brown");
                        return (dxf_RGB_color_get_name);
                }
                case 0x08457E :
                {
                        dxf_RGB_color_get_name = strdup ("Dark cerulean");
                        return (dxf_RGB_color_get_name);
                }
                case 0x986960 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark chestnut");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCD5B45 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark coral");
                        return (dxf_RGB_color_get_name);
                }
                case 0xB8860B :
                {
                        dxf_RGB_color_get_name = strdup ("Dark goldenrod");
                        return (dxf_RGB_color_get_name);
                }
                case 0x013220 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xBDB76B :
                {
                        dxf_RGB_color_get_name = strdup ("Dark khaki");
                        return (dxf_RGB_color_get_name);
                }
                case 0x8B008B :
                {
                        dxf_RGB_color_get_name = strdup ("Dark magenta");
                        return (dxf_RGB_color_get_name);
                }
                case 0x03C03C :
                {
                        dxf_RGB_color_get_name = strdup ("Dark pastel green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE75480 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0x560319 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark scarlet");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE9967A :
                {
                        dxf_RGB_color_get_name = strdup ("Dark salmon");
                        return (dxf_RGB_color_get_name);
                }
                case 0x2F4F4F :
                {
                        dxf_RGB_color_get_name = strdup ("Dark slate gray");
                        return (dxf_RGB_color_get_name);
                }
                case 0x177245 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark spring green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x918151 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark tan");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00CED1 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark turquoise");
                        return (dxf_RGB_color_get_name);
                }
                case 0x9400D3 :
                {
                        dxf_RGB_color_get_name = strdup ("Dark violet");
                        return (dxf_RGB_color_get_name);
                }
                case 0xEF3038 :
                {
                        dxf_RGB_color_get_name = strdup ("Deep Carmine Pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDA3287 :
                {
                        dxf_RGB_color_get_name = strdup ("Deep cerise");
                        return (dxf_RGB_color_get_name);
                }
                case 0xB94E48 :
                {
                        dxf_RGB_color_get_name = strdup ("Deep chestnut");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC154C1 :
                {
                        dxf_RGB_color_get_name = strdup ("Deep fuchsia");
                        return (dxf_RGB_color_get_name);
                }
                case 0x9955BB :
                {
                        dxf_RGB_color_get_name = strdup ("Deep lilac");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCD00CC :
                {
                        dxf_RGB_color_get_name = strdup ("Deep magenta");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFCBA4 :
                {
                        dxf_RGB_color_get_name = strdup ("Deep peach");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF1493 :
                {
                        dxf_RGB_color_get_name = strdup ("Deep pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0x1560BD :
                {
                        dxf_RGB_color_get_name = strdup ("Denim");
                        return (dxf_RGB_color_get_name);
                }
                case 0x1E90FF :
                {
                        dxf_RGB_color_get_name = strdup ("Dodger blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC2B280 :
                {
                        dxf_RGB_color_get_name = strdup ("Ecru");
                        return (dxf_RGB_color_get_name);
                }
                case 0x1034A6 :
                {
                        dxf_RGB_color_get_name = strdup ("Egyptian blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0x7DF9FF :
                {
                        dxf_RGB_color_get_name = strdup ("Electric blue");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0x00FF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Electric green (X11 green)");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0x6600FF :
                {
                        dxf_RGB_color_get_name = strdup ("Electric indigo");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCCFF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Electric lime");
                        return (dxf_RGB_color_get_name);
                }
                case 0xBF00FF :
                {
                        dxf_RGB_color_get_name = strdup ("Electric purple");
                        return (dxf_RGB_color_get_name);
                }
                case 0x50C878 :
                {
                        dxf_RGB_color_get_name = strdup ("Emerald");
                        return (dxf_RGB_color_get_name);
                }
                case 0x614051 :
                {
                        dxf_RGB_color_get_name = strdup ("Eggplant");
                        return (dxf_RGB_color_get_name);
                }
                case 0x801818 :
                {
                        dxf_RGB_color_get_name = strdup ("Falu red");
                        return (dxf_RGB_color_get_name);
                }
                case 0x4F7942 :
                {
                        dxf_RGB_color_get_name = strdup ("Fern green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xB22222 :
                {
                        dxf_RGB_color_get_name = strdup ("Firebrick");
                        return (dxf_RGB_color_get_name);
                }
                case 0xEEDC82 :
                {
                        dxf_RGB_color_get_name = strdup ("Flax");
                        return (dxf_RGB_color_get_name);
                }
                case 0x228B22 :
                {
                        dxf_RGB_color_get_name = strdup ("Forrest green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF64A8A :
                {
                        dxf_RGB_color_get_name = strdup ("French Rose");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xFF00FF :
                {
                        dxf_RGB_color_get_name = strdup ("Fuchsia");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0xFF77FF :
                {
                        dxf_RGB_color_get_name = strdup ("Fuchsia Pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE49B0F :
                {
                        dxf_RGB_color_get_name = strdup ("Gamboge");
                        return (dxf_RGB_color_get_name);
                }
                case 0xD4AF37 :
                {
                        dxf_RGB_color_get_name = strdup ("Gold (metallic)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFD700 :
                {
                        dxf_RGB_color_get_name = strdup ("Gold (web) (Golden)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x996515 :
                {
                        dxf_RGB_color_get_name = strdup ("Golden brown");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFDF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Golden yellow");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDAA520 :
                {
                        dxf_RGB_color_get_name = strdup ("Goldenrod");
                        return (dxf_RGB_color_get_name);
                }
                case 0x465945 :
                {
                        dxf_RGB_color_get_name = strdup ("Gray-asparagus");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00FF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Green (color wheel) (X11 green)");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0x008000 :
                {
                        dxf_RGB_color_get_name = strdup ("Green (HTML/CSS green)");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0x00A550 :
                {
                        dxf_RGB_color_get_name = strdup ("Green (pigment)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x66B032 :
                {
                        dxf_RGB_color_get_name = strdup ("Green (RYB)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xADFF2F :
                {
                        dxf_RGB_color_get_name = strdup ("Green-yellow");
                        return (dxf_RGB_color_get_name);
                }
                case 0x808080 :
                {
                        dxf_RGB_color_get_name = strdup ("Gray");
                        return (dxf_RGB_color_get_name);
                }
                case 0x5218FA :
                {
                        dxf_RGB_color_get_name = strdup ("Han Purple");
                        return (dxf_RGB_color_get_name);
                }
                case 0x3FFF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Harlequin");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDF73FF :
                {
                        dxf_RGB_color_get_name = strdup ("Heliotrope");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF400A1 :
                {
                        dxf_RGB_color_get_name = strdup ("Hollywood Cerise");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF00CC :
                {
                        dxf_RGB_color_get_name = strdup ("Hot Magenta");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF69B4 :
                {
                        dxf_RGB_color_get_name = strdup ("Hot Pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00416A :
                {
                        dxf_RGB_color_get_name = strdup ("Indigo (dye)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x4B0082 :
                {
                        dxf_RGB_color_get_name = strdup ("Indigo (web)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x002FA7 :
                {
                        dxf_RGB_color_get_name = strdup ("International Klein Blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF4F00 :
                {
                        dxf_RGB_color_get_name = strdup ("International orange");
                        return (dxf_RGB_color_get_name);
                }
                case 0x009000 :
                {
                        dxf_RGB_color_get_name = strdup ("Islamic green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFFFF0 :
                {
                        dxf_RGB_color_get_name = strdup ("Ivory");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00A86B :
                {
                        dxf_RGB_color_get_name = strdup ("Jade");
                        return (dxf_RGB_color_get_name);
                }
                case 0x4CBB17 :
                {
                        dxf_RGB_color_get_name = strdup ("Kelly green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC3B091 :
                {
                        dxf_RGB_color_get_name = strdup ("Khaki");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF0E68C :
                {
                        dxf_RGB_color_get_name = strdup ("Khaki (X11) (Light khaki)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xB57EDC :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender (floral)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE6E6FA :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender (web)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCCCCFF :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFF0F5 :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender blush");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC4C3D0 :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender gray");
                        return (dxf_RGB_color_get_name);
                }
                case 0xEE82EE :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender magenta");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFBAED2 :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0x967BB6 :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender purple");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFBA0E3 :
                {
                        dxf_RGB_color_get_name = strdup ("Lavender rose");
                        return (dxf_RGB_color_get_name);
                }
                case 0x7CFC00 :
                {
                        dxf_RGB_color_get_name = strdup ("Lawn green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFDE910 :
                {
                        dxf_RGB_color_get_name = strdup ("Lemon");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFFACD :
                {
                        dxf_RGB_color_get_name = strdup ("Lemon chifton");
                        return (dxf_RGB_color_get_name);
                }
                case 0xADD8E6 :
                {
                        dxf_RGB_color_get_name = strdup ("Light blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFB6C1 :
                {
                        dxf_RGB_color_get_name = strdup ("Light pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC8A2C8 :
                {
                        dxf_RGB_color_get_name = strdup ("Lilac");
                        return (dxf_RGB_color_get_name);
                }
                case 0xBFFF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Lime (color wheel)");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0x00FF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Lime (web) (X11 green)");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0x32CD32 :
                {
                        dxf_RGB_color_get_name = strdup ("Lime green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFAF0E6 :
                {
                        dxf_RGB_color_get_name = strdup ("Linen");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF00FF :
                {
                        dxf_RGB_color_get_name = strdup ("Magenta");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCA1F7B :
                {
                        dxf_RGB_color_get_name = strdup ("Magenta (dye)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF0090 :
                {
                        dxf_RGB_color_get_name = strdup ("Magenta (process)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xAAF0D1 :
                {
                        dxf_RGB_color_get_name = strdup ("Magic mint");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF8F4FF :
                {
                        dxf_RGB_color_get_name = strdup ("Magnolia");
                        return (dxf_RGB_color_get_name);
                }
                case 0x0BDA51 :
                {
                        dxf_RGB_color_get_name = strdup ("Malachite");
                        return (dxf_RGB_color_get_name);
                }
                case 0x800000 :
                {
                        dxf_RGB_color_get_name = strdup ("Maroon (HTML/CSS)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xB03060 :
                {
                        dxf_RGB_color_get_name = strdup ("Maroon (X11)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x73C2FB :
                {
                        dxf_RGB_color_get_name = strdup ("Maya blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE0B0FF :
                {
                        dxf_RGB_color_get_name = strdup ("Mauve");
                        return (dxf_RGB_color_get_name);
                }
                case 0x915F6D :
                {
                        dxf_RGB_color_get_name = strdup ("Mauve Taupe");
                        return (dxf_RGB_color_get_name);
                }
                case 0x0000CD :
                {
                        dxf_RGB_color_get_name = strdup ("Medium blue");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xAF4035 :
                {
                        dxf_RGB_color_get_name = strdup ("Medium carmine");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0xCC99CC :
                {
                        dxf_RGB_color_get_name = strdup ("Medium lavender magenta");
                        return (dxf_RGB_color_get_name);
                }
                case 0x9370DB :
                {
                        dxf_RGB_color_get_name = strdup ("Medium purple");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00FA9A :
                {
                        dxf_RGB_color_get_name = strdup ("Medium spring green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x191970 :
                {
                        dxf_RGB_color_get_name = strdup ("Midnight Blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0x004953 :
                {
                        dxf_RGB_color_get_name = strdup ("Midnight Green (Eagle Green)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x98FF98 :
                {
                        dxf_RGB_color_get_name = strdup ("Mint green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFE4E1 :
                {
                        dxf_RGB_color_get_name = strdup ("Misty rose");
                        return (dxf_RGB_color_get_name);
                }
                case 0xADDFAD :
                {
                        dxf_RGB_color_get_name = strdup ("Moss green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x997A8D :
                {
                        dxf_RGB_color_get_name = strdup ("Mountbatten pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFDB58 :
                {
                        dxf_RGB_color_get_name = strdup ("Mustard");
                        return (dxf_RGB_color_get_name);
                }
                case 0x21421E :
                {
                        dxf_RGB_color_get_name = strdup ("Myrtle");
                        return (dxf_RGB_color_get_name);
                }
                case 0x006633 :
                {
                        dxf_RGB_color_get_name = strdup ("MSU Green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFDEAD :
                {
                        dxf_RGB_color_get_name = strdup ("Navajo white");
                        return (dxf_RGB_color_get_name);
                }
                case 0x000080 :
                {
                        dxf_RGB_color_get_name = strdup ("Navy Blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCC7722 :
                {
                        dxf_RGB_color_get_name = strdup ("Ochre");
                        return (dxf_RGB_color_get_name);
                }
                case 0x008000 :
                {
                        dxf_RGB_color_get_name = strdup ("Office green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCFB53B :
                {
                        dxf_RGB_color_get_name = strdup ("Old Gold");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFDF5E6 :
                {
                        dxf_RGB_color_get_name = strdup ("Old Lace");
                        return (dxf_RGB_color_get_name);
                }
                case 0x796878 :
                {
                        dxf_RGB_color_get_name = strdup ("Old Lavender");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC08081 :
                {
                        dxf_RGB_color_get_name = strdup ("Old Rose");
                        return (dxf_RGB_color_get_name);
                }
                case 0x808000 :
                {
                        dxf_RGB_color_get_name = strdup ("Olive");
                        return (dxf_RGB_color_get_name);
                }
                case 0x6B8E23 :
                {
                        dxf_RGB_color_get_name = strdup ("Olive Drab");
                        return (dxf_RGB_color_get_name);
                }
                case 0x9AB973 :
                {
                        dxf_RGB_color_get_name = strdup ("Olivine");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF7F00 :
                {
                        dxf_RGB_color_get_name = strdup ("Orange (color wheel)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFB9902 :
                {
                        dxf_RGB_color_get_name = strdup ("Orange (RYB)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFA500 :
                {
                        dxf_RGB_color_get_name = strdup ("Orange (web)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFA000 :
                {
                        dxf_RGB_color_get_name = strdup ("Orange Peel");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF4500 :
                {
                        dxf_RGB_color_get_name = strdup ("Orange-Red");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDA70D6 :
                {
                        dxf_RGB_color_get_name = strdup ("Orchid");
                        return (dxf_RGB_color_get_name);
                }
                case 0xAFEEEE :
                {
                        dxf_RGB_color_get_name = strdup ("Pale blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0x987654 :
                {
                        dxf_RGB_color_get_name = strdup ("Pale brown");
                        return (dxf_RGB_color_get_name);
                }
                case 0xAF4035 :
                {
                        dxf_RGB_color_get_name = strdup ("Pale carmine");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDDADAF :
                {
                        dxf_RGB_color_get_name = strdup ("Pale chestnut");
                        return (dxf_RGB_color_get_name);
                }
                case 0xABCDEF :
                {
                        dxf_RGB_color_get_name = strdup ("Pale cornflower blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF984E5 :
                {
                        dxf_RGB_color_get_name = strdup ("Pale magenta");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFADADD :
                {
                        dxf_RGB_color_get_name = strdup ("Pale pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDB7093 :
                {
                        dxf_RGB_color_get_name = strdup ("Pale red-violet");
                        return (dxf_RGB_color_get_name);
                }
                case 0xBC987E :
                {
                        dxf_RGB_color_get_name = strdup ("Pale taupe");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFEFD5 :
                {
                        dxf_RGB_color_get_name = strdup ("Papaya whip");
                        return (dxf_RGB_color_get_name);
                }
                case 0x77DD77 :
                {
                        dxf_RGB_color_get_name = strdup ("Pastel green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFD1DC :
                {
                        dxf_RGB_color_get_name = strdup ("Pastel pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0x40404F :
                {
                        dxf_RGB_color_get_name = strdup ("Payne's grey");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFE5B4 :
                {
                        dxf_RGB_color_get_name = strdup ("Peach");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFCC99 :
                {
                        dxf_RGB_color_get_name = strdup ("Peach-orange");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFADFAD :
                {
                        dxf_RGB_color_get_name = strdup ("Peach-yellow");
                        return (dxf_RGB_color_get_name);
                }
                case 0xD1E231 :
                {
                        dxf_RGB_color_get_name = strdup ("Pear");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xCCCCFF :
                {
                        dxf_RGB_color_get_name = strdup ("Periwinkle");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0x1C39BB :
                {
                        dxf_RGB_color_get_name = strdup ("Persian blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00A693 :
                {
                        dxf_RGB_color_get_name = strdup ("Persian green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x32127A :
                {
                        dxf_RGB_color_get_name = strdup ("Persian indigo");
                        return (dxf_RGB_color_get_name);
                }
                case 0xD99058 :
                {
                        dxf_RGB_color_get_name = strdup ("Persian orange");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCC3333 :
                {
                        dxf_RGB_color_get_name = strdup ("Persian red");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF77FBE :
                {
                        dxf_RGB_color_get_name = strdup ("Persian pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFE28A2 :
                {
                        dxf_RGB_color_get_name = strdup ("Persian rose");
                        return (dxf_RGB_color_get_name);
                }
                case 0xEC5800 :
                {
                        dxf_RGB_color_get_name = strdup ("Persimmon");
                        return (dxf_RGB_color_get_name);
                }
                case 0x01796F :
                {
                        dxf_RGB_color_get_name = strdup ("Pine green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFC0CB :
                {
                        dxf_RGB_color_get_name = strdup ("Pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF9966 :
                {
                        dxf_RGB_color_get_name = strdup ("Pink-orange");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE5E4E2 :
                {
                        dxf_RGB_color_get_name = strdup ("Platinum");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xCC99CC :
                {
                        dxf_RGB_color_get_name = strdup ("Plum (web)");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0xFF5A36 :
                {
                        dxf_RGB_color_get_name = strdup ("Portland Orange");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xB0E0E6 :
                {
                        dxf_RGB_color_get_name = strdup ("Powder blue (web)");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0xCC8899 :
                {
                        dxf_RGB_color_get_name = strdup ("Puce");
                        return (dxf_RGB_color_get_name);
                }
                case 0x003153 :
                {
                        dxf_RGB_color_get_name = strdup ("Prusian blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDD00FF :
                {
                        dxf_RGB_color_get_name = strdup ("Psychedelic purple");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF7518 :
                {
                        dxf_RGB_color_get_name = strdup ("Pumpkin");
                        return (dxf_RGB_color_get_name);
                }
                case 0x7F007F :
                {
                        dxf_RGB_color_get_name = strdup ("Purple (HTML/CSS)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xA020F0 :
                {
                        dxf_RGB_color_get_name = strdup ("Purple (X11)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x50404D :
                {
                        dxf_RGB_color_get_name = strdup ("Purple Taupe");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE30B5C :
                {
                        dxf_RGB_color_get_name = strdup ("Raspberry");
                        return (dxf_RGB_color_get_name);
                }
                case 0x734A12 :
                {
                        dxf_RGB_color_get_name = strdup ("Raw umber");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE3256B :
                {
                        dxf_RGB_color_get_name = strdup ("Razzmatazz");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF0000 :
                {
                        dxf_RGB_color_get_name = strdup ("Red");
                        return (dxf_RGB_color_get_name);
                }
                case 0xED1C24 :
                {
                        dxf_RGB_color_get_name = strdup ("Red (pigment)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFE2712 :
                {
                        dxf_RGB_color_get_name = strdup ("Red (RYB)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC71585 :
                {
                        dxf_RGB_color_get_name = strdup ("Red-violet");
                        return (dxf_RGB_color_get_name);
                }
                case 0xD70040 :
                {
                        dxf_RGB_color_get_name = strdup ("Rich carmine");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00CCCC :
                {
                        dxf_RGB_color_get_name = strdup ("Robin egg blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF007F :
                {
                        dxf_RGB_color_get_name = strdup ("Rose");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE32636 :
                {
                        dxf_RGB_color_get_name = strdup ("Rose Madder");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF66CC :
                {
                        dxf_RGB_color_get_name = strdup ("Rose pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xAA98A9 :
                {
                        dxf_RGB_color_get_name = strdup ("Rose quartz");
                        return (dxf_RGB_color_get_name);
                }
                case 0x905D5D :
                {
                        dxf_RGB_color_get_name = strdup ("Rose Taupe");
                        return (dxf_RGB_color_get_name);
                }
                case 0x4169E1 :
                {
                        dxf_RGB_color_get_name = strdup ("Royal blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0x6B3FA0 :
                {
                        dxf_RGB_color_get_name = strdup ("Royal purple");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE0115F :
                {
                        dxf_RGB_color_get_name = strdup ("Ruby");
                        return (dxf_RGB_color_get_name);
                }
                case 0x80461B :
                {
                        dxf_RGB_color_get_name = strdup ("Russet");
                        return (dxf_RGB_color_get_name);
                }
                case 0xB7410E :
                {
                        dxf_RGB_color_get_name = strdup ("Rust");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF6600 :
                {
                        dxf_RGB_color_get_name = strdup ("Safety orange (blaze orange)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF4C430 :
                {
                        dxf_RGB_color_get_name = strdup ("Saffron");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF8C69 :
                {
                        dxf_RGB_color_get_name = strdup ("Salmon");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF91A4 :
                {
                        dxf_RGB_color_get_name = strdup ("Salmon pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF4A460 :
                {
                        dxf_RGB_color_get_name = strdup ("Sandy brown");
                        return (dxf_RGB_color_get_name);
                }
                case 0x92000A :
                {
                        dxf_RGB_color_get_name = strdup ("Sangria");
                        return (dxf_RGB_color_get_name);
                }
                case 0x082567 :
                {
                        dxf_RGB_color_get_name = strdup ("Sapphire");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF2400 :
                {
                        dxf_RGB_color_get_name = strdup ("Scarlet");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFD800 :
                {
                        dxf_RGB_color_get_name = strdup ("School bus yellow");
                        return (dxf_RGB_color_get_name);
                }
                case 0x2E8B57 :
                {
                        dxf_RGB_color_get_name = strdup ("Sea green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x321414 :
                {
                        dxf_RGB_color_get_name = strdup ("Seal brown");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFF5EE :
                {
                        dxf_RGB_color_get_name = strdup ("Seashell");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFBA00 :
                {
                        dxf_RGB_color_get_name = strdup ("Selective yellow");
                        return (dxf_RGB_color_get_name);
                }
                case 0x704214 :
                {
                        dxf_RGB_color_get_name = strdup ("Sepia");
                        return (dxf_RGB_color_get_name);
                }
                case 0x009E60 :
                {
                        dxf_RGB_color_get_name = strdup ("Shamrock green");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFC0FC0 :
                {
                        dxf_RGB_color_get_name = strdup ("Shocking pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xA0522D :
                {
                        dxf_RGB_color_get_name = strdup ("Sienna");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC0C0C0 :
                {
                        dxf_RGB_color_get_name = strdup ("Silver");
                        return (dxf_RGB_color_get_name);
                }
                case 0x87CEEB :
                {
                        dxf_RGB_color_get_name = strdup ("Sky Blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0x708090 :
                {
                        dxf_RGB_color_get_name = strdup ("Slate grey");
                        return (dxf_RGB_color_get_name);
                }
                case 0x003399 :
                {
                        dxf_RGB_color_get_name = strdup ("Smalt (Dark powder blue)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xA7FC00 :
                {
                        dxf_RGB_color_get_name = strdup ("Spring bud");
                        return (dxf_RGB_color_get_name);
                }
                case 0x00FF7F :
                {
                        dxf_RGB_color_get_name = strdup ("Spring green");
                        return (dxf_RGB_color_get_name);
                }
                case 0x4682B4 :
                {
                        dxf_RGB_color_get_name = strdup ("Steel blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xD2B48C :
                {
                        dxf_RGB_color_get_name = strdup ("Tan");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF28500 :
                {
                        dxf_RGB_color_get_name = strdup ("Tangerine");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFCC00 :
                {
                        dxf_RGB_color_get_name = strdup ("Tangerine yellow");
                        return (dxf_RGB_color_get_name);
                }
                case 0x483C32 :
                {
                        dxf_RGB_color_get_name = strdup ("Taupe");
                        return (dxf_RGB_color_get_name);
                }
                case 0x8B8589 :
                {
                        dxf_RGB_color_get_name = strdup ("Taupe gray");
                        return (dxf_RGB_color_get_name);
                }
                case 0xD0F0C0 :
                {
                        dxf_RGB_color_get_name = strdup ("Tea green");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xF88379 :
                {
                        dxf_RGB_color_get_name = strdup ("Tea rose (orange)");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0xF4C2C2 :
                {
                        dxf_RGB_color_get_name = strdup ("Tea rose (rose)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x008080 :
                {
                        dxf_RGB_color_get_name = strdup ("Teal");
                        return (dxf_RGB_color_get_name);
                }
                case 0xCD5700 :
                {
                        dxf_RGB_color_get_name = strdup ("Tenné (Tawny)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE2725B :
                {
                        dxf_RGB_color_get_name = strdup ("Terra cotta");
                        return (dxf_RGB_color_get_name);
                }
                case 0xD8BFD8 :
                {
                        dxf_RGB_color_get_name = strdup ("Thistle");
                        return (dxf_RGB_color_get_name);
                }
                case 0xDE6FA1 :
                {
                        dxf_RGB_color_get_name = strdup ("Thullian pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF6347 :
                {
                        dxf_RGB_color_get_name = strdup ("Tomato");
                        return (dxf_RGB_color_get_name);
                }
                case 0x30D5C8 :
                {
                        dxf_RGB_color_get_name = strdup ("Turquoise");
                        return (dxf_RGB_color_get_name);
                }
                case 0x66023C :
                {
                        dxf_RGB_color_get_name = strdup ("Tyrian Purple");
                        return (dxf_RGB_color_get_name);
                }
                case 0x120A8F :
                {
                        dxf_RGB_color_get_name = strdup ("Ultramarine");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFF6FFF :
                {
                        dxf_RGB_color_get_name = strdup ("Ultra pink");
                        return (dxf_RGB_color_get_name);
                }
                case 0x5B92E5 :
                {
                        dxf_RGB_color_get_name = strdup ("United Nations blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xAE2029 :
                {
                        dxf_RGB_color_get_name = strdup ("Upsdell red");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC5B358 :
                {
                        dxf_RGB_color_get_name = strdup ("Vegas Gold");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC80815 :
                {
                        dxf_RGB_color_get_name = strdup ("Venetian red");
                        return (dxf_RGB_color_get_name);
                }
                case 0xE34234 :
                {
                        dxf_RGB_color_get_name = strdup ("Vermilion");
                        return (dxf_RGB_color_get_name);
                }
                case 0x8B00FF :
                {
                        dxf_RGB_color_get_name = strdup ("Violet");
                        return (dxf_RGB_color_get_name);
                }
/*
                case 0xEE82EE :
                {
                        dxf_RGB_color_get_name = strdup ("Violet (web)");
                        return (dxf_RGB_color_get_name);
                }
*/
                case 0x8601AF :
                {
                        dxf_RGB_color_get_name = strdup ("Violet (RYB)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x40826D :
                {
                        dxf_RGB_color_get_name = strdup ("Viridian");
                        return (dxf_RGB_color_get_name);
                }
                case 0xF5DEB3 :
                {
                        dxf_RGB_color_get_name = strdup ("Wheat");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFFFFF :
                {
                        dxf_RGB_color_get_name = strdup ("White");
                        return (dxf_RGB_color_get_name);
                }
                case 0xC9A0DC :
                {
                        dxf_RGB_color_get_name = strdup ("Wisteria");
                        return (dxf_RGB_color_get_name);
                }
                case 0x738678 :
                {
                        dxf_RGB_color_get_name = strdup ("Xanadu");
                        return (dxf_RGB_color_get_name);
                }
                case 0x0F4D92 :
                {
                        dxf_RGB_color_get_name = strdup ("Yale Blue");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFFF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Yellow");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFFEF00 :
                {
                        dxf_RGB_color_get_name = strdup ("Yellow (process)");
                        return (dxf_RGB_color_get_name);
                }
                case 0xFEFE33 :
                {
                        dxf_RGB_color_get_name = strdup ("Yellow (RYB)");
                        return (dxf_RGB_color_get_name);
                }
                case 0x9ACD32 :
                {
                        dxf_RGB_color_get_name = strdup ("Yellow-green");
                        return (dxf_RGB_color_get_name);
                }
                default:
                {
                        return (NULL);
                }
        }

}


/* EOF */
