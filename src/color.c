/*!
 * \file color.c
 *
 * \author Copyright (C) 2012, 2014, 2015, 2017, 2018, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for DXF colors.
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
        DXF_DEBUG_BEGIN
#endif
        DxfRGBColor *RGB_color = NULL;
        size_t size;

        size = sizeof (DxfRGBColor);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((RGB_color = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRGBCcolor struct.\n")),
                  __FUNCTION__);
                RGB_color = NULL;
        }
        else
        {
                memset (RGB_color, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (RGB_color);
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
        DXF_DEBUG_BEGIN
#endif
        DxfRGBColor *RGB_color;
        int triplet;
        char *name = NULL;

        RGB_color = dxf_RGB_color_new ();
        if (red < 0)
        {
                fprintf (stderr,
                  (_("Error red color value in %s () is negative.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else if (red > 255)
        {
                fprintf (stderr,
                  (_("Error red color value in %s () is out of range.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                RGB_color->r = red;
        }
        if (green < 0)
        {
                fprintf (stderr,
                  (_("Error green color value in %s () is negative.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else if (green > 255)
        {
                fprintf (stderr,
                  (_("Error green color value in %s () is out of range.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                RGB_color->g = green;
        }
        if (blue < 0)
        {
                fprintf (stderr,
                  (_("Error blue color value in %s () is negative.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else if (blue > 255)
        {
                fprintf (stderr,
                  (_("Error blue color value in %s () is out of range.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                RGB_color->b = blue;
        }
        triplet = dxf_RGB_to_triplet (red, green, blue);
        name = dxf_RGB_color_get_name (triplet);
        if (name == NULL)
        {
                fprintf (stderr,
                  (_("Error name value in %s () contains a NULL pointer.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                RGB_color->name = strdup (name);
                free (name);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (RGB_color);
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
        DxfRGBColor *ACI[DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS]
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        size_t size;

        size = sizeof (DxfRGBColor);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ACI = malloc (size * DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRGBCcolor array.\n")),
                  __FUNCTION__);
                ACI = NULL;
                return (EXIT_FAILURE);
        }
        else
        {
                ACI[0] = dxf_RGB_color_set (0,0,0);
                ACI[1] = dxf_RGB_color_set (255,0,0);
                ACI[2] = dxf_RGB_color_set (255,255,0);
                ACI[3] = dxf_RGB_color_set (0,255,0);
                ACI[4] = dxf_RGB_color_set (0,255,255);
                ACI[5] = dxf_RGB_color_set (0,0,255);
                ACI[6] = dxf_RGB_color_set (255,0,255);
                ACI[7] = dxf_RGB_color_set (255,255,255);
                ACI[8] = dxf_RGB_color_set (128,128,128);
                ACI[9] = dxf_RGB_color_set (192,192,192);
                ACI[10] = dxf_RGB_color_set (255,0,0);
                ACI[11] = dxf_RGB_color_set (255,127,127);
                ACI[12] = dxf_RGB_color_set (204,0,0);
                ACI[13] = dxf_RGB_color_set (204,102,102);
                ACI[14] = dxf_RGB_color_set (153,0,0);
                ACI[15] = dxf_RGB_color_set (153,76,76);
                ACI[16] = dxf_RGB_color_set (127,0,0);
                ACI[17] = dxf_RGB_color_set (127,63,63);
                ACI[18] = dxf_RGB_color_set (76,0,0);
                ACI[19] = dxf_RGB_color_set (76,38,38);
                ACI[20] = dxf_RGB_color_set (255,63,0);
                ACI[21] = dxf_RGB_color_set (255,159,127);
                ACI[22] = dxf_RGB_color_set (204,51,0);
                ACI[23] = dxf_RGB_color_set (204,127,102);
                ACI[24] = dxf_RGB_color_set (153,38,0);
                ACI[25] = dxf_RGB_color_set (153,95,76);
                ACI[26] = dxf_RGB_color_set (127,31,0);
                ACI[27] = dxf_RGB_color_set (127,79,63);
                ACI[28] = dxf_RGB_color_set (76,19,0);
                ACI[29] = dxf_RGB_color_set (76,47,38);
                ACI[30] = dxf_RGB_color_set (255,127,0);
                ACI[31] = dxf_RGB_color_set (255,191,127);
                ACI[32] = dxf_RGB_color_set (204,102,0);
                ACI[33] = dxf_RGB_color_set (204,153,102);
                ACI[34] = dxf_RGB_color_set (153,76,0);
                ACI[35] = dxf_RGB_color_set (153,114,76);
                ACI[36] = dxf_RGB_color_set (127,63,0);
                ACI[37] = dxf_RGB_color_set (127,95,63);
                ACI[38] = dxf_RGB_color_set (76,38,0);
                ACI[39] = dxf_RGB_color_set (76,57,38);
                ACI[40] = dxf_RGB_color_set (255,191,0);
                ACI[41] = dxf_RGB_color_set (255,223,127);
                ACI[42] = dxf_RGB_color_set (204,153,0);
                ACI[43] = dxf_RGB_color_set (204,178,102);
                ACI[44] = dxf_RGB_color_set (153,114,0);
                ACI[45] = dxf_RGB_color_set (153,133,76);
                ACI[46] = dxf_RGB_color_set (127,95,0);
                ACI[47] = dxf_RGB_color_set (127,111,63);
                ACI[48] = dxf_RGB_color_set (76,57,0);
                ACI[49] = dxf_RGB_color_set (76,66,38);
                ACI[50] = dxf_RGB_color_set (255,255,0);
                ACI[51] = dxf_RGB_color_set (255,255,127);
                ACI[52] = dxf_RGB_color_set (204,204,0);
                ACI[53] = dxf_RGB_color_set (204,204,102);
                ACI[54] = dxf_RGB_color_set (153,153,0);
                ACI[55] = dxf_RGB_color_set (153,153,76);
                ACI[56] = dxf_RGB_color_set (127,127,0);
                ACI[57] = dxf_RGB_color_set (127,127,63);
                ACI[58] = dxf_RGB_color_set (76,76,0);
                ACI[59] = dxf_RGB_color_set (76,76,38);
                ACI[60] = dxf_RGB_color_set (191,255,0);
                ACI[61] = dxf_RGB_color_set (223,255,127);
                ACI[62] = dxf_RGB_color_set (153,204,0);
                ACI[63] = dxf_RGB_color_set (178,204,102);
                ACI[64] = dxf_RGB_color_set (114,153,0);
                ACI[65] = dxf_RGB_color_set (133,153,76);
                ACI[66] = dxf_RGB_color_set (95,127,0);
                ACI[67] = dxf_RGB_color_set (111,127,63);
                ACI[68] = dxf_RGB_color_set (57,76,0);
                ACI[69] = dxf_RGB_color_set (66,76,38);
                ACI[70] = dxf_RGB_color_set (127,255,0);
                ACI[71] = dxf_RGB_color_set (191,255,127);
                ACI[72] = dxf_RGB_color_set (102,204,0);
                ACI[73] = dxf_RGB_color_set (153,204,102);
                ACI[74] = dxf_RGB_color_set (76,153,0);
                ACI[75] = dxf_RGB_color_set (114,153,76);
                ACI[76] = dxf_RGB_color_set (63,127,0);
                ACI[77] = dxf_RGB_color_set (95,127,63);
                ACI[78] = dxf_RGB_color_set (38,76,0);
                ACI[79] = dxf_RGB_color_set (57,76,38);
                ACI[80] = dxf_RGB_color_set (63,255,0);
                ACI[81] = dxf_RGB_color_set (159,255,127);
                ACI[82] = dxf_RGB_color_set (51,204,0);
                ACI[83] = dxf_RGB_color_set (127,204,102);
                ACI[84] = dxf_RGB_color_set (38,153,0);
                ACI[85] = dxf_RGB_color_set (95,153,76);
                ACI[86] = dxf_RGB_color_set (31,127,0);
                ACI[87] = dxf_RGB_color_set (79,127,63);
                ACI[88] = dxf_RGB_color_set (19,76,0);
                ACI[89] = dxf_RGB_color_set (47,76,38);
                ACI[90] = dxf_RGB_color_set (0,255,0);
                ACI[91] = dxf_RGB_color_set (127,255,127);
                ACI[92] = dxf_RGB_color_set (0,204,0);
                ACI[93] = dxf_RGB_color_set (102,204,102);
                ACI[94] = dxf_RGB_color_set (0,153,0);
                ACI[95] = dxf_RGB_color_set (76,153,76);
                ACI[96] = dxf_RGB_color_set (0,127,0);
                ACI[97] = dxf_RGB_color_set (63,127,63);
                ACI[98] = dxf_RGB_color_set (0,76,0);
                ACI[99] = dxf_RGB_color_set (38,76,38);
                ACI[100] = dxf_RGB_color_set (0,255,63);
                ACI[101] = dxf_RGB_color_set (127,255,159);
                ACI[102] = dxf_RGB_color_set (0,204,51);
                ACI[103] = dxf_RGB_color_set (102,204,127);
                ACI[104] = dxf_RGB_color_set (0,153,38);
                ACI[105] = dxf_RGB_color_set (76,153,95);
                ACI[106] = dxf_RGB_color_set (0,127,31);
                ACI[107] = dxf_RGB_color_set (63,127,79);
                ACI[108] = dxf_RGB_color_set (0,76,19);
                ACI[109] = dxf_RGB_color_set (38,76,47);
                ACI[110] = dxf_RGB_color_set (0,255,127);
                ACI[111] = dxf_RGB_color_set (127,255,191);
                ACI[112] = dxf_RGB_color_set (0,204,102);
                ACI[113] = dxf_RGB_color_set (102,204,153);
                ACI[114] = dxf_RGB_color_set (0,153,76);
                ACI[115] = dxf_RGB_color_set (76,153,114);
                ACI[116] = dxf_RGB_color_set (0,127,63);
                ACI[117] = dxf_RGB_color_set (63,127,95);
                ACI[118] = dxf_RGB_color_set (0,76,38);
                ACI[119] = dxf_RGB_color_set (38,76,57);
                ACI[120] = dxf_RGB_color_set (0,255,191);
                ACI[121] = dxf_RGB_color_set (127,255,223);
                ACI[122] = dxf_RGB_color_set (0,204,153);
                ACI[123] = dxf_RGB_color_set (102,204,178);
                ACI[124] = dxf_RGB_color_set (0,153,114);
                ACI[125] = dxf_RGB_color_set (76,153,133);
                ACI[126] = dxf_RGB_color_set (0,127,95);
                ACI[127] = dxf_RGB_color_set (63,127,111);
                ACI[128] = dxf_RGB_color_set (0,76,57);
                ACI[129] = dxf_RGB_color_set (38,76,66);
                ACI[130] = dxf_RGB_color_set (0,255,255);
                ACI[131] = dxf_RGB_color_set (127,255,255);
                ACI[132] = dxf_RGB_color_set (0,204,204);
                ACI[133] = dxf_RGB_color_set (102,204,204);
                ACI[134] = dxf_RGB_color_set (0,153,153);
                ACI[135] = dxf_RGB_color_set (76,153,153);
                ACI[136] = dxf_RGB_color_set (0,127,127);
                ACI[137] = dxf_RGB_color_set (63,127,127);
                ACI[138] = dxf_RGB_color_set (0,76,76);
                ACI[139] = dxf_RGB_color_set (38,76,76);
                ACI[140] = dxf_RGB_color_set (0,191,255);
                ACI[141] = dxf_RGB_color_set (127,223,255);
                ACI[142] = dxf_RGB_color_set (0,153,204);
                ACI[143] = dxf_RGB_color_set (102,178,204);
                ACI[144] = dxf_RGB_color_set (0,114,153);
                ACI[145] = dxf_RGB_color_set (76,133,153);
                ACI[146] = dxf_RGB_color_set (0,95,127);
                ACI[147] = dxf_RGB_color_set (63,111,127);
                ACI[148] = dxf_RGB_color_set (0,57,76);
                ACI[149] = dxf_RGB_color_set (38,66,76);
                ACI[150] = dxf_RGB_color_set (0,127,255);
                ACI[151] = dxf_RGB_color_set (127,191,255);
                ACI[152] = dxf_RGB_color_set (0,102,204);
                ACI[153] = dxf_RGB_color_set (102,153,204);
                ACI[154] = dxf_RGB_color_set (0,76,153);
                ACI[155] = dxf_RGB_color_set (76,114,153);
                ACI[156] = dxf_RGB_color_set (0,63,127);
                ACI[157] = dxf_RGB_color_set (63,95,127);
                ACI[158] = dxf_RGB_color_set (0,38,76);
                ACI[159] = dxf_RGB_color_set (38,57,76);
                ACI[160] = dxf_RGB_color_set (0,63,255);
                ACI[161] = dxf_RGB_color_set (127,159,255);
                ACI[162] = dxf_RGB_color_set (0,51,204);
                ACI[163] = dxf_RGB_color_set (102,127,204);
                ACI[164] = dxf_RGB_color_set (0,38,153);
                ACI[165] = dxf_RGB_color_set (76,95,153);
                ACI[166] = dxf_RGB_color_set (0,31,127);
                ACI[167] = dxf_RGB_color_set (63,79,127);
                ACI[168] = dxf_RGB_color_set (0,19,76);
                ACI[169] = dxf_RGB_color_set (38,47,76);
                ACI[170] = dxf_RGB_color_set (0,0,255);
                ACI[171] = dxf_RGB_color_set (170,170,255);
                ACI[172] = dxf_RGB_color_set (0,0,189);
                ACI[173] = dxf_RGB_color_set (126,126,189);
                ACI[174] = dxf_RGB_color_set (0,0,129);
                ACI[175] = dxf_RGB_color_set (86,86,129);
                ACI[176] = dxf_RGB_color_set (0,0,104);
                ACI[177] = dxf_RGB_color_set (69,69,104);
                ACI[178] = dxf_RGB_color_set (0,0,79);
                ACI[179] = dxf_RGB_color_set (53,53,79);
                ACI[180] = dxf_RGB_color_set (63,0,255);
                ACI[181] = dxf_RGB_color_set (191,170,255);
                ACI[182] = dxf_RGB_color_set (46,0,189);
                ACI[183] = dxf_RGB_color_set (141,126,189);
                ACI[184] = dxf_RGB_color_set (31,0,129);
                ACI[185] = dxf_RGB_color_set (96,86,129);
                ACI[186] = dxf_RGB_color_set (25,0,104);
                ACI[187] = dxf_RGB_color_set (78,69,104);
                ACI[188] = dxf_RGB_color_set (19,0,79);
                ACI[189] = dxf_RGB_color_set (59,53,79);
                ACI[190] = dxf_RGB_color_set (127,0,255);
                ACI[191] = dxf_RGB_color_set (212,170,255);
                ACI[192] = dxf_RGB_color_set (94,0,189);
                ACI[193] = dxf_RGB_color_set (157,126,189);
                ACI[194] = dxf_RGB_color_set (64,0,129);
                ACI[195] = dxf_RGB_color_set (107,86,129);
                ACI[196] = dxf_RGB_color_set (52,0,104);
                ACI[197] = dxf_RGB_color_set (86,69,104);
                ACI[198] = dxf_RGB_color_set (39,0,79);
                ACI[199] = dxf_RGB_color_set (66,53,79);
                ACI[200] = dxf_RGB_color_set (191,0,255);
                ACI[201] = dxf_RGB_color_set (234,170,255);
                ACI[202] = dxf_RGB_color_set (141,0,189);
                ACI[203] = dxf_RGB_color_set (173,126,189);
                ACI[204] = dxf_RGB_color_set (96,0,129);
                ACI[205] = dxf_RGB_color_set (118,86,129);
                ACI[206] = dxf_RGB_color_set (78,0,104);
                ACI[207] = dxf_RGB_color_set (95,69,104);
                ACI[208] = dxf_RGB_color_set (59,0,79);
                ACI[209] = dxf_RGB_color_set (73,53,79);
                ACI[210] = dxf_RGB_color_set (255,0,255);
                ACI[211] = dxf_RGB_color_set (255,170,255);
                ACI[212] = dxf_RGB_color_set (189,0,189);
                ACI[213] = dxf_RGB_color_set (189,126,189);
                ACI[214] = dxf_RGB_color_set (129,0,129);
                ACI[215] = dxf_RGB_color_set (129,86,129);
                ACI[216] = dxf_RGB_color_set (104,0,104);
                ACI[217] = dxf_RGB_color_set (104,69,104);
                ACI[218] = dxf_RGB_color_set (79,0,79);
                ACI[219] = dxf_RGB_color_set (79,53,79);
                ACI[220] = dxf_RGB_color_set (255,0,191);
                ACI[221] = dxf_RGB_color_set (255,170,234);
                ACI[222] = dxf_RGB_color_set (189,0,141);
                ACI[223] = dxf_RGB_color_set (189,126,173);
                ACI[224] = dxf_RGB_color_set (129,0,96);
                ACI[225] = dxf_RGB_color_set (129,86,118);
                ACI[226] = dxf_RGB_color_set (104,0,78);
                ACI[227] = dxf_RGB_color_set (104,69,95);
                ACI[228] = dxf_RGB_color_set (79,0,59);
                ACI[229] = dxf_RGB_color_set (79,53,73);
                ACI[230] = dxf_RGB_color_set (255,0,127);
                ACI[231] = dxf_RGB_color_set (255,170,212);
                ACI[232] = dxf_RGB_color_set (189,0,94);
                ACI[233] = dxf_RGB_color_set (189,126,157);
                ACI[234] = dxf_RGB_color_set (129,0,64);
                ACI[235] = dxf_RGB_color_set (129,86,107);
                ACI[236] = dxf_RGB_color_set (104,0,52);
                ACI[237] = dxf_RGB_color_set (104,69,86);
                ACI[238] = dxf_RGB_color_set (79,0,39);
                ACI[239] = dxf_RGB_color_set (79,53,66);
                ACI[240] = dxf_RGB_color_set (255,0,63);
                ACI[241] = dxf_RGB_color_set (255,170,191);
                ACI[242] = dxf_RGB_color_set (189,0,46);
                ACI[243] = dxf_RGB_color_set (189,126,141);
                ACI[244] = dxf_RGB_color_set (129,0,31);
                ACI[245] = dxf_RGB_color_set (129,86,96);
                ACI[246] = dxf_RGB_color_set (104,0,25);
                ACI[247] = dxf_RGB_color_set (104,69,78);
                ACI[248] = dxf_RGB_color_set (79,0,19);
                ACI[249] = dxf_RGB_color_set (79,53,59);
                ACI[250] = dxf_RGB_color_set (51,51,51);
                ACI[251] = dxf_RGB_color_set (80,80,80);
                ACI[252] = dxf_RGB_color_set (105,105,105);
                ACI[253] = dxf_RGB_color_set (130,130,130);
                ACI[254] = dxf_RGB_color_set (190,190,190);
                ACI[255] = dxf_RGB_color_set (255,255,255);
        }
#if DEBUG
        DXF_DEBUG_END
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
        DXF_DEBUG_BEGIN
#endif
        int triplet;

        if (red < 0)
        {
                fprintf (stderr,
                  (_("Error color value in %s () is negative.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        else if (red > 255)
        {
                fprintf (stderr,
                  (_("Error color value in %s () is out of range.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        else
        {
                triplet = red * 65536;
        }
        if (green < 0)
        {
                fprintf (stderr,
                  (_("Error color value in %s () is negative.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        else if (green > 255)
        {
                fprintf (stderr,
                  (_("Error color value in %s () is out of range.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        else
        {
                triplet += green * 256;
        }
        if (blue < 0)
        {
                fprintf (stderr,
                  (_("Error color value in %s () is negative.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        else if (blue > 255)
        {
                fprintf (stderr,
                  (_("Error color value in %s () is out of range.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        else
        {
                triplet += blue;
        }
#if DEBUG
        DXF_DEBUG_END
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
 *
 * \return a pointer to the color name string, or \c NULL if unknown.
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
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *RGB_color_name;

        switch (RGB_color_hex_triplet)
        {
                case 0xF0F8FF :
                {
                        RGB_color_name = strdup ("Alice blue");
                        return (RGB_color_name);
                }
/*
                case 0xE32636 :
                {
                        RGB_color_name = strdup ("Alizarin");
                        return (RGB_color_name);
                }
*/
                case 0xE52B50 :
                {
                        RGB_color_name = strdup ("Amaranth");
                        return (RGB_color_name);
                }
                case 0xF19CBB :
                {
                        RGB_color_name = strdup ("Amaranth Pink");
                        return (RGB_color_name);
                }
                case 0xFFBF00 :
                {
                        RGB_color_name = strdup ("Amber");
                        return (RGB_color_name);
                }
                case 0x9966CC :
                {
                        RGB_color_name = strdup ("Amethyst");
                        return (RGB_color_name);
                }
                case 0xFBCEB1 :
                {
                        RGB_color_name = strdup ("Apricot");
                        return (RGB_color_name);
                }
/*
                case 0x00FFFF :
                {
                        RGB_color_name = strdup ("Aqua");
                        return (RGB_color_name);
                }
*/
                case 0x7FFFD4 :
                {
                        RGB_color_name = strdup ("Aquamarine");
                        return (RGB_color_name);
                }
                case 0x4B5320 :
                {
                        RGB_color_name = strdup ("Aemy green");
                        return (RGB_color_name);
                }
                case 0x7BA05B :
                {
                        RGB_color_name = strdup ("Asparagus");
                        return (RGB_color_name);
                }
/*
                case 0xFF9966 :
                {
                        RGB_color_name = strdup ("Atomic tangerine");
                        return (RGB_color_name);
                }
*/
                case 0x6D351A :
                {
                        RGB_color_name = strdup ("Auburn");
                        return (RGB_color_name);
                }
                case 0x007FFF :
                {
                        RGB_color_name = strdup ("Azure (color wheel)");
                        return (RGB_color_name);
                }
                case 0xF0FFFF :
                {
                        RGB_color_name = strdup ("Azure (web)");
                        return (RGB_color_name);
                }
                case 0xE0FFFF :
                {
                        RGB_color_name = strdup ("Baby blue");
                        return (RGB_color_name);
                }
                case 0xF5F5DC :
                {
                        RGB_color_name = strdup ("Beige");
                        return (RGB_color_name);
                }
                case 0x3D2B1F :
                {
                        RGB_color_name = strdup ("Bistre");
                        return (RGB_color_name);
                }
                case 0x000000 :
                {
                        RGB_color_name = strdup ("Black");
                        return (RGB_color_name);
                }
                case 0x0000FF :
                {
                        RGB_color_name = strdup ("Blue");
                        return (RGB_color_name);
                }
                case 0x333399 :
                {
                        RGB_color_name = strdup ("Blue (pigment)");
                        return (RGB_color_name);
                }
                case 0x0247FE :
                {
                        RGB_color_name = strdup ("Blue (RYB)");
                        return (RGB_color_name);
                }
                case 0x00DDDD :
                {
                        RGB_color_name = strdup ("Blue-green");
                        return (RGB_color_name);
                }
                case 0x8A2BE2 :
                {
                        RGB_color_name = strdup ("Blue-violet");
                        return (RGB_color_name);
                }
                case 0x0095B6 :
                {
                        RGB_color_name = strdup ("Bondi blue");
                        return (RGB_color_name);
                }
                case 0xB5A642 :
                {
                        RGB_color_name = strdup ("Brass");
                        return (RGB_color_name);
                }
                case 0x66FF00 :
                {
                        RGB_color_name = strdup ("Bright green");
                        return (RGB_color_name);
                }
/*
                case 0xFF007F :
                {
                        RGB_color_name = strdup ("Bright pink");
                        return (RGB_color_name);
                }
*/
                case 0x08E8DE :
                {
                        RGB_color_name = strdup ("Bright turquoise");
                        return (RGB_color_name);
                }
                case 0xFF55A3 :
                {
                        RGB_color_name = strdup ("Brilliant rose");
                        return (RGB_color_name);
                }
                case 0xFB607F :
                {
                        RGB_color_name = strdup ("Brink pink");
                        return (RGB_color_name);
                }
                case 0xCD7F32 :
                {
                        RGB_color_name = strdup ("Bronze");
                        return (RGB_color_name);
                }
                case 0x964B00 :
                {
                        RGB_color_name = strdup ("Brown");
                        return (RGB_color_name);
                }
                case 0xF0DC82 :
                {
                        RGB_color_name = strdup ("Buff");
                        return (RGB_color_name);
                }
                case 0x900020 :
                {
                        RGB_color_name = strdup ("Burgundy");
                        return (RGB_color_name);
                }
                case 0xCC5500 :
                {
                        RGB_color_name = strdup ("Burnt orange");
                        return (RGB_color_name);
                }
                case 0xE97451 :
                {
                        RGB_color_name = strdup ("Burnt sienna");
                        return (RGB_color_name);
                }
                case 0x8A3324 :
                {
                        RGB_color_name = strdup ("Burnt umber");
                        return (RGB_color_name);
                }
                case 0x78866B :
                {
                        RGB_color_name = strdup ("Camouflage green");
                        return (RGB_color_name);
                }
                case 0x592720 :
                {
                        RGB_color_name = strdup ("Caput mortuum");
                        return (RGB_color_name);
                }
                case 0xC41E3A :
                {
                        RGB_color_name = strdup ("Cardinal");
                        return (RGB_color_name);
                }
                case 0x960018 :
                {
                        RGB_color_name = strdup ("Carmine");
                        return (RGB_color_name);
                }
                case 0xEB4C42 :
                {
                        RGB_color_name = strdup ("Carmine Pink");
                        return (RGB_color_name);
                }
                case 0xFFA6C9 :
                {
                        RGB_color_name = strdup ("Carnation pink");
                        return (RGB_color_name);
                }
                case 0x99BADD :
                {
                        RGB_color_name = strdup ("Carolina blue");
                        return (RGB_color_name);
                }
                case 0xED9121 :
                {
                        RGB_color_name = strdup ("Carrot orange");
                        return (RGB_color_name);
                }
                case 0xACE1AF :
                {
                        RGB_color_name = strdup ("Celadon");
                        return (RGB_color_name);
                }
                case 0xDE3163 :
                {
                        RGB_color_name = strdup ("Cerise");
                        return (RGB_color_name);
                }
                case 0xEC3B83 :
                {
                        RGB_color_name = strdup ("Cerise Pink");
                        return (RGB_color_name);
                }
                case 0x007BA7 :
                {
                        RGB_color_name = strdup ("Cerulean");
                        return (RGB_color_name);
                }
                case 0x2A52BE :
                {
                        RGB_color_name = strdup ("Cerulean blue");
                        return (RGB_color_name);
                }
                case 0xF7E7CE :
                {
                        RGB_color_name = strdup ("Champagne");
                        return (RGB_color_name);
                }
                case 0x464646 :
                {
                        RGB_color_name = strdup ("Charcoal");
                        return (RGB_color_name);
                }
                case 0xDFFF00 :
                {
                        RGB_color_name = strdup ("Chartreuse (traditional)");
                        return (RGB_color_name);
                }
                case 0x7FFF00 :
                {
                        RGB_color_name = strdup ("Chartreuse (web)");
                        return (RGB_color_name);
                }
                case 0xFFB7C5 :
                {
                        RGB_color_name = strdup ("Cherry blossom pink");
                        return (RGB_color_name);
                }
                case 0xCD5C5C :
                {
                        RGB_color_name = strdup ("Chestnut");
                        return (RGB_color_name);
                }
                case 0x7B3F00 :
                {
                        RGB_color_name = strdup ("Chocolate");
                        return (RGB_color_name);
                }
/*
                case 0xE34234 :
                {
                        RGB_color_name = strdup ("Cinnabar");
                        return (RGB_color_name);
                }
*/
                case 0xD2691E :
                {
                        RGB_color_name = strdup ("Cinnamon");
                        return (RGB_color_name);
                }
                case 0x0047AB :
                {
                        RGB_color_name = strdup ("Cobalt");
                        return (RGB_color_name);
                }
                case 0x9BDDFF :
                {
                        RGB_color_name = strdup ("Columbia blue");
                        return (RGB_color_name);
                }
                case 0xB87333 :
                {
                        RGB_color_name = strdup ("Copper");
                        return (RGB_color_name);
                }
                case 0x996666 :
                {
                        RGB_color_name = strdup ("Copper rose");
                        return (RGB_color_name);
                }
                case 0xFF7F50 :
                {
                        RGB_color_name = strdup ("Coral");
                        return (RGB_color_name);
                }
                case 0xF88379 :
                {
                        RGB_color_name = strdup ("Coral pink");
                        return (RGB_color_name);
                }
                case 0xFF4040 :
                {
                        RGB_color_name = strdup ("Coral red");
                        return (RGB_color_name);
                }
                case 0xFBEC5D :
                {
                        RGB_color_name = strdup ("Corn");
                        return (RGB_color_name);
                }
                case 0x6495ED :
                {
                        RGB_color_name = strdup ("Cornflower blue");
                        return (RGB_color_name);
                }
                case 0xFFF8E7 :
                {
                        RGB_color_name = strdup ("Cosmic latte");
                        return (RGB_color_name);
                }
                case 0xFFFDD0 :
                {
                        RGB_color_name = strdup ("Cream");
                        return (RGB_color_name);
                }
                case 0xDC143C :
                {
                        RGB_color_name = strdup ("Crimson");
                        return (RGB_color_name);
                }
                case 0x00FFFF :
                {
                        RGB_color_name = strdup ("Cyan");
                        return (RGB_color_name);
                }
                case 0x00B7EB :
                {
                        RGB_color_name = strdup ("Cyan (process)");
                        return (RGB_color_name);
                }
                case 0x00008B :
                {
                        RGB_color_name = strdup ("Dark blue");
                        return (RGB_color_name);
                }
                case 0x654321 :
                {
                        RGB_color_name = strdup ("Dark brown");
                        return (RGB_color_name);
                }
                case 0x08457E :
                {
                        RGB_color_name = strdup ("Dark cerulean");
                        return (RGB_color_name);
                }
                case 0x986960 :
                {
                        RGB_color_name = strdup ("Dark chestnut");
                        return (RGB_color_name);
                }
                case 0xCD5B45 :
                {
                        RGB_color_name = strdup ("Dark coral");
                        return (RGB_color_name);
                }
                case 0xB8860B :
                {
                        RGB_color_name = strdup ("Dark goldenrod");
                        return (RGB_color_name);
                }
                case 0x013220 :
                {
                        RGB_color_name = strdup ("Dark green");
                        return (RGB_color_name);
                }
                case 0xBDB76B :
                {
                        RGB_color_name = strdup ("Dark khaki");
                        return (RGB_color_name);
                }
                case 0x8B008B :
                {
                        RGB_color_name = strdup ("Dark magenta");
                        return (RGB_color_name);
                }
                case 0x03C03C :
                {
                        RGB_color_name = strdup ("Dark pastel green");
                        return (RGB_color_name);
                }
                case 0xE75480 :
                {
                        RGB_color_name = strdup ("Dark pink");
                        return (RGB_color_name);
                }
                case 0x560319 :
                {
                        RGB_color_name = strdup ("Dark scarlet");
                        return (RGB_color_name);
                }
                case 0xE9967A :
                {
                        RGB_color_name = strdup ("Dark salmon");
                        return (RGB_color_name);
                }
                case 0x2F4F4F :
                {
                        RGB_color_name = strdup ("Dark slate gray");
                        return (RGB_color_name);
                }
                case 0x177245 :
                {
                        RGB_color_name = strdup ("Dark spring green");
                        return (RGB_color_name);
                }
                case 0x918151 :
                {
                        RGB_color_name = strdup ("Dark tan");
                        return (RGB_color_name);
                }
                case 0x00CED1 :
                {
                        RGB_color_name = strdup ("Dark turquoise");
                        return (RGB_color_name);
                }
                case 0x9400D3 :
                {
                        RGB_color_name = strdup ("Dark violet");
                        return (RGB_color_name);
                }
                case 0xEF3038 :
                {
                        RGB_color_name = strdup ("Deep Carmine Pink");
                        return (RGB_color_name);
                }
                case 0xDA3287 :
                {
                        RGB_color_name = strdup ("Deep cerise");
                        return (RGB_color_name);
                }
                case 0xB94E48 :
                {
                        RGB_color_name = strdup ("Deep chestnut");
                        return (RGB_color_name);
                }
                case 0xC154C1 :
                {
                        RGB_color_name = strdup ("Deep fuchsia");
                        return (RGB_color_name);
                }
                case 0x9955BB :
                {
                        RGB_color_name = strdup ("Deep lilac");
                        return (RGB_color_name);
                }
                case 0xCD00CC :
                {
                        RGB_color_name = strdup ("Deep magenta");
                        return (RGB_color_name);
                }
                case 0xFFCBA4 :
                {
                        RGB_color_name = strdup ("Deep peach");
                        return (RGB_color_name);
                }
                case 0xFF1493 :
                {
                        RGB_color_name = strdup ("Deep pink");
                        return (RGB_color_name);
                }
                case 0x1560BD :
                {
                        RGB_color_name = strdup ("Denim");
                        return (RGB_color_name);
                }
                case 0x1E90FF :
                {
                        RGB_color_name = strdup ("Dodger blue");
                        return (RGB_color_name);
                }
                case 0xC2B280 :
                {
                        RGB_color_name = strdup ("Ecru");
                        return (RGB_color_name);
                }
                case 0x1034A6 :
                {
                        RGB_color_name = strdup ("Egyptian blue");
                        return (RGB_color_name);
                }
                case 0x7DF9FF :
                {
                        RGB_color_name = strdup ("Electric blue");
                        return (RGB_color_name);
                }
/*
                case 0x00FF00 :
                {
                        RGB_color_name = strdup ("Electric green (X11 green)");
                        return (RGB_color_name);
                }
*/
                case 0x6600FF :
                {
                        RGB_color_name = strdup ("Electric indigo");
                        return (RGB_color_name);
                }
                case 0xCCFF00 :
                {
                        RGB_color_name = strdup ("Electric lime");
                        return (RGB_color_name);
                }
                case 0xBF00FF :
                {
                        RGB_color_name = strdup ("Electric purple");
                        return (RGB_color_name);
                }
                case 0x50C878 :
                {
                        RGB_color_name = strdup ("Emerald");
                        return (RGB_color_name);
                }
                case 0x614051 :
                {
                        RGB_color_name = strdup ("Eggplant");
                        return (RGB_color_name);
                }
                case 0x801818 :
                {
                        RGB_color_name = strdup ("Falu red");
                        return (RGB_color_name);
                }
                case 0x4F7942 :
                {
                        RGB_color_name = strdup ("Fern green");
                        return (RGB_color_name);
                }
                case 0xB22222 :
                {
                        RGB_color_name = strdup ("Firebrick");
                        return (RGB_color_name);
                }
                case 0xEEDC82 :
                {
                        RGB_color_name = strdup ("Flax");
                        return (RGB_color_name);
                }
                case 0x228B22 :
                {
                        RGB_color_name = strdup ("Forrest green");
                        return (RGB_color_name);
                }
                case 0xF64A8A :
                {
                        RGB_color_name = strdup ("French Rose");
                        return (RGB_color_name);
                }
/*
                case 0xFF00FF :
                {
                        RGB_color_name = strdup ("Fuchsia");
                        return (RGB_color_name);
                }
*/
                case 0xFF77FF :
                {
                        RGB_color_name = strdup ("Fuchsia Pink");
                        return (RGB_color_name);
                }
                case 0xE49B0F :
                {
                        RGB_color_name = strdup ("Gamboge");
                        return (RGB_color_name);
                }
                case 0xD4AF37 :
                {
                        RGB_color_name = strdup ("Gold (metallic)");
                        return (RGB_color_name);
                }
                case 0xFFD700 :
                {
                        RGB_color_name = strdup ("Gold (web) (Golden)");
                        return (RGB_color_name);
                }
                case 0x996515 :
                {
                        RGB_color_name = strdup ("Golden brown");
                        return (RGB_color_name);
                }
                case 0xFFDF00 :
                {
                        RGB_color_name = strdup ("Golden yellow");
                        return (RGB_color_name);
                }
                case 0xDAA520 :
                {
                        RGB_color_name = strdup ("Goldenrod");
                        return (RGB_color_name);
                }
                case 0x465945 :
                {
                        RGB_color_name = strdup ("Gray-asparagus");
                        return (RGB_color_name);
                }
                case 0x00FF00 :
                {
                        RGB_color_name = strdup ("Green (color wheel) (X11 green)");
                        return (RGB_color_name);
                }
/*
                case 0x008000 :
                {
                        RGB_color_name = strdup ("Green (HTML/CSS green)");
                        return (RGB_color_name);
                }
*/
                case 0x00A550 :
                {
                        RGB_color_name = strdup ("Green (pigment)");
                        return (RGB_color_name);
                }
                case 0x66B032 :
                {
                        RGB_color_name = strdup ("Green (RYB)");
                        return (RGB_color_name);
                }
                case 0xADFF2F :
                {
                        RGB_color_name = strdup ("Green-yellow");
                        return (RGB_color_name);
                }
                case 0x808080 :
                {
                        RGB_color_name = strdup ("Gray");
                        return (RGB_color_name);
                }
                case 0x5218FA :
                {
                        RGB_color_name = strdup ("Han Purple");
                        return (RGB_color_name);
                }
                case 0x3FFF00 :
                {
                        RGB_color_name = strdup ("Harlequin");
                        return (RGB_color_name);
                }
                case 0xDF73FF :
                {
                        RGB_color_name = strdup ("Heliotrope");
                        return (RGB_color_name);
                }
                case 0xF400A1 :
                {
                        RGB_color_name = strdup ("Hollywood Cerise");
                        return (RGB_color_name);
                }
                case 0xFF00CC :
                {
                        RGB_color_name = strdup ("Hot Magenta");
                        return (RGB_color_name);
                }
                case 0xFF69B4 :
                {
                        RGB_color_name = strdup ("Hot Pink");
                        return (RGB_color_name);
                }
                case 0x00416A :
                {
                        RGB_color_name = strdup ("Indigo (dye)");
                        return (RGB_color_name);
                }
                case 0x4B0082 :
                {
                        RGB_color_name = strdup ("Indigo (web)");
                        return (RGB_color_name);
                }
                case 0x002FA7 :
                {
                        RGB_color_name = strdup ("International Klein Blue");
                        return (RGB_color_name);
                }
                case 0xFF4F00 :
                {
                        RGB_color_name = strdup ("International orange");
                        return (RGB_color_name);
                }
                case 0x009000 :
                {
                        RGB_color_name = strdup ("Islamic green");
                        return (RGB_color_name);
                }
                case 0xFFFFF0 :
                {
                        RGB_color_name = strdup ("Ivory");
                        return (RGB_color_name);
                }
                case 0x00A86B :
                {
                        RGB_color_name = strdup ("Jade");
                        return (RGB_color_name);
                }
                case 0x4CBB17 :
                {
                        RGB_color_name = strdup ("Kelly green");
                        return (RGB_color_name);
                }
                case 0xC3B091 :
                {
                        RGB_color_name = strdup ("Khaki");
                        return (RGB_color_name);
                }
                case 0xF0E68C :
                {
                        RGB_color_name = strdup ("Khaki (X11) (Light khaki)");
                        return (RGB_color_name);
                }
                case 0xB57EDC :
                {
                        RGB_color_name = strdup ("Lavender (floral)");
                        return (RGB_color_name);
                }
                case 0xE6E6FA :
                {
                        RGB_color_name = strdup ("Lavender (web)");
                        return (RGB_color_name);
                }
                case 0xCCCCFF :
                {
                        RGB_color_name = strdup ("Lavender blue");
                        return (RGB_color_name);
                }
                case 0xFFF0F5 :
                {
                        RGB_color_name = strdup ("Lavender blush");
                        return (RGB_color_name);
                }
                case 0xC4C3D0 :
                {
                        RGB_color_name = strdup ("Lavender gray");
                        return (RGB_color_name);
                }
                case 0xEE82EE :
                {
                        RGB_color_name = strdup ("Lavender magenta");
                        return (RGB_color_name);
                }
                case 0xFBAED2 :
                {
                        RGB_color_name = strdup ("Lavender pink");
                        return (RGB_color_name);
                }
                case 0x967BB6 :
                {
                        RGB_color_name = strdup ("Lavender purple");
                        return (RGB_color_name);
                }
                case 0xFBA0E3 :
                {
                        RGB_color_name = strdup ("Lavender rose");
                        return (RGB_color_name);
                }
                case 0x7CFC00 :
                {
                        RGB_color_name = strdup ("Lawn green");
                        return (RGB_color_name);
                }
                case 0xFDE910 :
                {
                        RGB_color_name = strdup ("Lemon");
                        return (RGB_color_name);
                }
                case 0xFFFACD :
                {
                        RGB_color_name = strdup ("Lemon chifton");
                        return (RGB_color_name);
                }
                case 0xADD8E6 :
                {
                        RGB_color_name = strdup ("Light blue");
                        return (RGB_color_name);
                }
                case 0xFFB6C1 :
                {
                        RGB_color_name = strdup ("Light pink");
                        return (RGB_color_name);
                }
                case 0xC8A2C8 :
                {
                        RGB_color_name = strdup ("Lilac");
                        return (RGB_color_name);
                }
                case 0xBFFF00 :
                {
                        RGB_color_name = strdup ("Lime (color wheel)");
                        return (RGB_color_name);
                }
/*
                case 0x00FF00 :
                {
                        RGB_color_name = strdup ("Lime (web) (X11 green)");
                        return (RGB_color_name);
                }
*/
                case 0x32CD32 :
                {
                        RGB_color_name = strdup ("Lime green");
                        return (RGB_color_name);
                }
                case 0xFAF0E6 :
                {
                        RGB_color_name = strdup ("Linen");
                        return (RGB_color_name);
                }
                case 0xFF00FF :
                {
                        RGB_color_name = strdup ("Magenta");
                        return (RGB_color_name);
                }
                case 0xCA1F7B :
                {
                        RGB_color_name = strdup ("Magenta (dye)");
                        return (RGB_color_name);
                }
                case 0xFF0090 :
                {
                        RGB_color_name = strdup ("Magenta (process)");
                        return (RGB_color_name);
                }
                case 0xAAF0D1 :
                {
                        RGB_color_name = strdup ("Magic mint");
                        return (RGB_color_name);
                }
                case 0xF8F4FF :
                {
                        RGB_color_name = strdup ("Magnolia");
                        return (RGB_color_name);
                }
                case 0x0BDA51 :
                {
                        RGB_color_name = strdup ("Malachite");
                        return (RGB_color_name);
                }
                case 0x800000 :
                {
                        RGB_color_name = strdup ("Maroon (HTML/CSS)");
                        return (RGB_color_name);
                }
                case 0xB03060 :
                {
                        RGB_color_name = strdup ("Maroon (X11)");
                        return (RGB_color_name);
                }
                case 0x73C2FB :
                {
                        RGB_color_name = strdup ("Maya blue");
                        return (RGB_color_name);
                }
                case 0xE0B0FF :
                {
                        RGB_color_name = strdup ("Mauve");
                        return (RGB_color_name);
                }
                case 0x915F6D :
                {
                        RGB_color_name = strdup ("Mauve Taupe");
                        return (RGB_color_name);
                }
                case 0x0000CD :
                {
                        RGB_color_name = strdup ("Medium blue");
                        return (RGB_color_name);
                }
/*
                case 0xAF4035 :
                {
                        RGB_color_name = strdup ("Medium carmine");
                        return (RGB_color_name);
                }
*/
                case 0xCC99CC :
                {
                        RGB_color_name = strdup ("Medium lavender magenta");
                        return (RGB_color_name);
                }
                case 0x9370DB :
                {
                        RGB_color_name = strdup ("Medium purple");
                        return (RGB_color_name);
                }
                case 0x00FA9A :
                {
                        RGB_color_name = strdup ("Medium spring green");
                        return (RGB_color_name);
                }
                case 0x191970 :
                {
                        RGB_color_name = strdup ("Midnight Blue");
                        return (RGB_color_name);
                }
                case 0x004953 :
                {
                        RGB_color_name = strdup ("Midnight Green (Eagle Green)");
                        return (RGB_color_name);
                }
                case 0x98FF98 :
                {
                        RGB_color_name = strdup ("Mint green");
                        return (RGB_color_name);
                }
                case 0xFFE4E1 :
                {
                        RGB_color_name = strdup ("Misty rose");
                        return (RGB_color_name);
                }
                case 0xADDFAD :
                {
                        RGB_color_name = strdup ("Moss green");
                        return (RGB_color_name);
                }
                case 0x997A8D :
                {
                        RGB_color_name = strdup ("Mountbatten pink");
                        return (RGB_color_name);
                }
                case 0xFFDB58 :
                {
                        RGB_color_name = strdup ("Mustard");
                        return (RGB_color_name);
                }
                case 0x21421E :
                {
                        RGB_color_name = strdup ("Myrtle");
                        return (RGB_color_name);
                }
                case 0x006633 :
                {
                        RGB_color_name = strdup ("MSU Green");
                        return (RGB_color_name);
                }
                case 0xFFDEAD :
                {
                        RGB_color_name = strdup ("Navajo white");
                        return (RGB_color_name);
                }
                case 0x000080 :
                {
                        RGB_color_name = strdup ("Navy Blue");
                        return (RGB_color_name);
                }
                case 0xCC7722 :
                {
                        RGB_color_name = strdup ("Ochre");
                        return (RGB_color_name);
                }
                case 0x008000 :
                {
                        RGB_color_name = strdup ("Office green");
                        return (RGB_color_name);
                }
                case 0xCFB53B :
                {
                        RGB_color_name = strdup ("Old Gold");
                        return (RGB_color_name);
                }
                case 0xFDF5E6 :
                {
                        RGB_color_name = strdup ("Old Lace");
                        return (RGB_color_name);
                }
                case 0x796878 :
                {
                        RGB_color_name = strdup ("Old Lavender");
                        return (RGB_color_name);
                }
                case 0xC08081 :
                {
                        RGB_color_name = strdup ("Old Rose");
                        return (RGB_color_name);
                }
                case 0x808000 :
                {
                        RGB_color_name = strdup ("Olive");
                        return (RGB_color_name);
                }
                case 0x6B8E23 :
                {
                        RGB_color_name = strdup ("Olive Drab");
                        return (RGB_color_name);
                }
                case 0x9AB973 :
                {
                        RGB_color_name = strdup ("Olivine");
                        return (RGB_color_name);
                }
                case 0xFF7F00 :
                {
                        RGB_color_name = strdup ("Orange (color wheel)");
                        return (RGB_color_name);
                }
                case 0xFB9902 :
                {
                        RGB_color_name = strdup ("Orange (RYB)");
                        return (RGB_color_name);
                }
                case 0xFFA500 :
                {
                        RGB_color_name = strdup ("Orange (web)");
                        return (RGB_color_name);
                }
                case 0xFFA000 :
                {
                        RGB_color_name = strdup ("Orange Peel");
                        return (RGB_color_name);
                }
                case 0xFF4500 :
                {
                        RGB_color_name = strdup ("Orange-Red");
                        return (RGB_color_name);
                }
                case 0xDA70D6 :
                {
                        RGB_color_name = strdup ("Orchid");
                        return (RGB_color_name);
                }
                case 0xAFEEEE :
                {
                        RGB_color_name = strdup ("Pale blue");
                        return (RGB_color_name);
                }
                case 0x987654 :
                {
                        RGB_color_name = strdup ("Pale brown");
                        return (RGB_color_name);
                }
                case 0xAF4035 :
                {
                        RGB_color_name = strdup ("Pale carmine");
                        return (RGB_color_name);
                }
                case 0xDDADAF :
                {
                        RGB_color_name = strdup ("Pale chestnut");
                        return (RGB_color_name);
                }
                case 0xABCDEF :
                {
                        RGB_color_name = strdup ("Pale cornflower blue");
                        return (RGB_color_name);
                }
                case 0xF984E5 :
                {
                        RGB_color_name = strdup ("Pale magenta");
                        return (RGB_color_name);
                }
                case 0xFADADD :
                {
                        RGB_color_name = strdup ("Pale pink");
                        return (RGB_color_name);
                }
                case 0xDB7093 :
                {
                        RGB_color_name = strdup ("Pale red-violet");
                        return (RGB_color_name);
                }
                case 0xBC987E :
                {
                        RGB_color_name = strdup ("Pale taupe");
                        return (RGB_color_name);
                }
                case 0xFFEFD5 :
                {
                        RGB_color_name = strdup ("Papaya whip");
                        return (RGB_color_name);
                }
                case 0x77DD77 :
                {
                        RGB_color_name = strdup ("Pastel green");
                        return (RGB_color_name);
                }
                case 0xFFD1DC :
                {
                        RGB_color_name = strdup ("Pastel pink");
                        return (RGB_color_name);
                }
                case 0x40404F :
                {
                        RGB_color_name = strdup ("Payne's grey");
                        return (RGB_color_name);
                }
                case 0xFFE5B4 :
                {
                        RGB_color_name = strdup ("Peach");
                        return (RGB_color_name);
                }
                case 0xFFCC99 :
                {
                        RGB_color_name = strdup ("Peach-orange");
                        return (RGB_color_name);
                }
                case 0xFADFAD :
                {
                        RGB_color_name = strdup ("Peach-yellow");
                        return (RGB_color_name);
                }
                case 0xD1E231 :
                {
                        RGB_color_name = strdup ("Pear");
                        return (RGB_color_name);
                }
/*
                case 0xCCCCFF :
                {
                        RGB_color_name = strdup ("Periwinkle");
                        return (RGB_color_name);
                }
*/
                case 0x1C39BB :
                {
                        RGB_color_name = strdup ("Persian blue");
                        return (RGB_color_name);
                }
                case 0x00A693 :
                {
                        RGB_color_name = strdup ("Persian green");
                        return (RGB_color_name);
                }
                case 0x32127A :
                {
                        RGB_color_name = strdup ("Persian indigo");
                        return (RGB_color_name);
                }
                case 0xD99058 :
                {
                        RGB_color_name = strdup ("Persian orange");
                        return (RGB_color_name);
                }
                case 0xCC3333 :
                {
                        RGB_color_name = strdup ("Persian red");
                        return (RGB_color_name);
                }
                case 0xF77FBE :
                {
                        RGB_color_name = strdup ("Persian pink");
                        return (RGB_color_name);
                }
                case 0xFE28A2 :
                {
                        RGB_color_name = strdup ("Persian rose");
                        return (RGB_color_name);
                }
                case 0xEC5800 :
                {
                        RGB_color_name = strdup ("Persimmon");
                        return (RGB_color_name);
                }
                case 0x01796F :
                {
                        RGB_color_name = strdup ("Pine green");
                        return (RGB_color_name);
                }
                case 0xFFC0CB :
                {
                        RGB_color_name = strdup ("Pink");
                        return (RGB_color_name);
                }
                case 0xFF9966 :
                {
                        RGB_color_name = strdup ("Pink-orange");
                        return (RGB_color_name);
                }
                case 0xE5E4E2 :
                {
                        RGB_color_name = strdup ("Platinum");
                        return (RGB_color_name);
                }
/*
                case 0xCC99CC :
                {
                        RGB_color_name = strdup ("Plum (web)");
                        return (RGB_color_name);
                }
*/
                case 0xFF5A36 :
                {
                        RGB_color_name = strdup ("Portland Orange");
                        return (RGB_color_name);
                }
/*
                case 0xB0E0E6 :
                {
                        RGB_color_name = strdup ("Powder blue (web)");
                        return (RGB_color_name);
                }
*/
                case 0xCC8899 :
                {
                        RGB_color_name = strdup ("Puce");
                        return (RGB_color_name);
                }
                case 0x003153 :
                {
                        RGB_color_name = strdup ("Prusian blue");
                        return (RGB_color_name);
                }
                case 0xDD00FF :
                {
                        RGB_color_name = strdup ("Psychedelic purple");
                        return (RGB_color_name);
                }
                case 0xFF7518 :
                {
                        RGB_color_name = strdup ("Pumpkin");
                        return (RGB_color_name);
                }
                case 0x7F007F :
                {
                        RGB_color_name = strdup ("Purple (HTML/CSS)");
                        return (RGB_color_name);
                }
                case 0xA020F0 :
                {
                        RGB_color_name = strdup ("Purple (X11)");
                        return (RGB_color_name);
                }
                case 0x50404D :
                {
                        RGB_color_name = strdup ("Purple Taupe");
                        return (RGB_color_name);
                }
                case 0xE30B5C :
                {
                        RGB_color_name = strdup ("Raspberry");
                        return (RGB_color_name);
                }
                case 0x734A12 :
                {
                        RGB_color_name = strdup ("Raw umber");
                        return (RGB_color_name);
                }
                case 0xE3256B :
                {
                        RGB_color_name = strdup ("Razzmatazz");
                        return (RGB_color_name);
                }
                case 0xFF0000 :
                {
                        RGB_color_name = strdup ("Red");
                        return (RGB_color_name);
                }
                case 0xED1C24 :
                {
                        RGB_color_name = strdup ("Red (pigment)");
                        return (RGB_color_name);
                }
                case 0xFE2712 :
                {
                        RGB_color_name = strdup ("Red (RYB)");
                        return (RGB_color_name);
                }
                case 0xC71585 :
                {
                        RGB_color_name = strdup ("Red-violet");
                        return (RGB_color_name);
                }
                case 0xD70040 :
                {
                        RGB_color_name = strdup ("Rich carmine");
                        return (RGB_color_name);
                }
                case 0x00CCCC :
                {
                        RGB_color_name = strdup ("Robin egg blue");
                        return (RGB_color_name);
                }
                case 0xFF007F :
                {
                        RGB_color_name = strdup ("Rose");
                        return (RGB_color_name);
                }
                case 0xE32636 :
                {
                        RGB_color_name = strdup ("Rose Madder");
                        return (RGB_color_name);
                }
                case 0xFF66CC :
                {
                        RGB_color_name = strdup ("Rose pink");
                        return (RGB_color_name);
                }
                case 0xAA98A9 :
                {
                        RGB_color_name = strdup ("Rose quartz");
                        return (RGB_color_name);
                }
                case 0x905D5D :
                {
                        RGB_color_name = strdup ("Rose Taupe");
                        return (RGB_color_name);
                }
                case 0x4169E1 :
                {
                        RGB_color_name = strdup ("Royal blue");
                        return (RGB_color_name);
                }
                case 0x6B3FA0 :
                {
                        RGB_color_name = strdup ("Royal purple");
                        return (RGB_color_name);
                }
                case 0xE0115F :
                {
                        RGB_color_name = strdup ("Ruby");
                        return (RGB_color_name);
                }
                case 0x80461B :
                {
                        RGB_color_name = strdup ("Russet");
                        return (RGB_color_name);
                }
                case 0xB7410E :
                {
                        RGB_color_name = strdup ("Rust");
                        return (RGB_color_name);
                }
                case 0xFF6600 :
                {
                        RGB_color_name = strdup ("Safety orange (blaze orange)");
                        return (RGB_color_name);
                }
                case 0xF4C430 :
                {
                        RGB_color_name = strdup ("Saffron");
                        return (RGB_color_name);
                }
                case 0xFF8C69 :
                {
                        RGB_color_name = strdup ("Salmon");
                        return (RGB_color_name);
                }
                case 0xFF91A4 :
                {
                        RGB_color_name = strdup ("Salmon pink");
                        return (RGB_color_name);
                }
                case 0xF4A460 :
                {
                        RGB_color_name = strdup ("Sandy brown");
                        return (RGB_color_name);
                }
                case 0x92000A :
                {
                        RGB_color_name = strdup ("Sangria");
                        return (RGB_color_name);
                }
                case 0x082567 :
                {
                        RGB_color_name = strdup ("Sapphire");
                        return (RGB_color_name);
                }
                case 0xFF2400 :
                {
                        RGB_color_name = strdup ("Scarlet");
                        return (RGB_color_name);
                }
                case 0xFFD800 :
                {
                        RGB_color_name = strdup ("School bus yellow");
                        return (RGB_color_name);
                }
                case 0x2E8B57 :
                {
                        RGB_color_name = strdup ("Sea green");
                        return (RGB_color_name);
                }
                case 0x321414 :
                {
                        RGB_color_name = strdup ("Seal brown");
                        return (RGB_color_name);
                }
                case 0xFFF5EE :
                {
                        RGB_color_name = strdup ("Seashell");
                        return (RGB_color_name);
                }
                case 0xFFBA00 :
                {
                        RGB_color_name = strdup ("Selective yellow");
                        return (RGB_color_name);
                }
                case 0x704214 :
                {
                        RGB_color_name = strdup ("Sepia");
                        return (RGB_color_name);
                }
                case 0x009E60 :
                {
                        RGB_color_name = strdup ("Shamrock green");
                        return (RGB_color_name);
                }
                case 0xFC0FC0 :
                {
                        RGB_color_name = strdup ("Shocking pink");
                        return (RGB_color_name);
                }
                case 0xA0522D :
                {
                        RGB_color_name = strdup ("Sienna");
                        return (RGB_color_name);
                }
                case 0xC0C0C0 :
                {
                        RGB_color_name = strdup ("Silver");
                        return (RGB_color_name);
                }
                case 0x87CEEB :
                {
                        RGB_color_name = strdup ("Sky Blue");
                        return (RGB_color_name);
                }
                case 0x708090 :
                {
                        RGB_color_name = strdup ("Slate grey");
                        return (RGB_color_name);
                }
                case 0x003399 :
                {
                        RGB_color_name = strdup ("Smalt (Dark powder blue)");
                        return (RGB_color_name);
                }
                case 0xA7FC00 :
                {
                        RGB_color_name = strdup ("Spring bud");
                        return (RGB_color_name);
                }
                case 0x00FF7F :
                {
                        RGB_color_name = strdup ("Spring green");
                        return (RGB_color_name);
                }
                case 0x4682B4 :
                {
                        RGB_color_name = strdup ("Steel blue");
                        return (RGB_color_name);
                }
                case 0xD2B48C :
                {
                        RGB_color_name = strdup ("Tan");
                        return (RGB_color_name);
                }
                case 0xF28500 :
                {
                        RGB_color_name = strdup ("Tangerine");
                        return (RGB_color_name);
                }
                case 0xFFCC00 :
                {
                        RGB_color_name = strdup ("Tangerine yellow");
                        return (RGB_color_name);
                }
                case 0x483C32 :
                {
                        RGB_color_name = strdup ("Taupe");
                        return (RGB_color_name);
                }
                case 0x8B8589 :
                {
                        RGB_color_name = strdup ("Taupe gray");
                        return (RGB_color_name);
                }
                case 0xD0F0C0 :
                {
                        RGB_color_name = strdup ("Tea green");
                        return (RGB_color_name);
                }
/*
                case 0xF88379 :
                {
                        RGB_color_name = strdup ("Tea rose (orange)");
                        return (RGB_color_name);
                }
*/
                case 0xF4C2C2 :
                {
                        RGB_color_name = strdup ("Tea rose (rose)");
                        return (RGB_color_name);
                }
                case 0x008080 :
                {
                        RGB_color_name = strdup ("Teal");
                        return (RGB_color_name);
                }
                case 0xCD5700 :
                {
                        RGB_color_name = strdup ("Tenné (Tawny)");
                        return (RGB_color_name);
                }
                case 0xE2725B :
                {
                        RGB_color_name = strdup ("Terra cotta");
                        return (RGB_color_name);
                }
                case 0xD8BFD8 :
                {
                        RGB_color_name = strdup ("Thistle");
                        return (RGB_color_name);
                }
                case 0xDE6FA1 :
                {
                        RGB_color_name = strdup ("Thullian pink");
                        return (RGB_color_name);
                }
                case 0xFF6347 :
                {
                        RGB_color_name = strdup ("Tomato");
                        return (RGB_color_name);
                }
                case 0x30D5C8 :
                {
                        RGB_color_name = strdup ("Turquoise");
                        return (RGB_color_name);
                }
                case 0x66023C :
                {
                        RGB_color_name = strdup ("Tyrian Purple");
                        return (RGB_color_name);
                }
                case 0x120A8F :
                {
                        RGB_color_name = strdup ("Ultramarine");
                        return (RGB_color_name);
                }
                case 0xFF6FFF :
                {
                        RGB_color_name = strdup ("Ultra pink");
                        return (RGB_color_name);
                }
                case 0x5B92E5 :
                {
                        RGB_color_name = strdup ("United Nations blue");
                        return (RGB_color_name);
                }
                case 0xAE2029 :
                {
                        RGB_color_name = strdup ("Upsdell red");
                        return (RGB_color_name);
                }
                case 0xC5B358 :
                {
                        RGB_color_name = strdup ("Vegas Gold");
                        return (RGB_color_name);
                }
                case 0xC80815 :
                {
                        RGB_color_name = strdup ("Venetian red");
                        return (RGB_color_name);
                }
                case 0xE34234 :
                {
                        RGB_color_name = strdup ("Vermilion");
                        return (RGB_color_name);
                }
                case 0x8B00FF :
                {
                        RGB_color_name = strdup ("Violet");
                        return (RGB_color_name);
                }
/*
                case 0xEE82EE :
                {
                        RGB_color_name = strdup ("Violet (web)");
                        return (RGB_color_name);
                }
*/
                case 0x8601AF :
                {
                        RGB_color_name = strdup ("Violet (RYB)");
                        return (RGB_color_name);
                }
                case 0x40826D :
                {
                        RGB_color_name = strdup ("Viridian");
                        return (RGB_color_name);
                }
                case 0xF5DEB3 :
                {
                        RGB_color_name = strdup ("Wheat");
                        return (RGB_color_name);
                }
                case 0xFFFFFF :
                {
                        RGB_color_name = strdup ("White");
                        return (RGB_color_name);
                }
                case 0xC9A0DC :
                {
                        RGB_color_name = strdup ("Wisteria");
                        return (RGB_color_name);
                }
                case 0x738678 :
                {
                        RGB_color_name = strdup ("Xanadu");
                        return (RGB_color_name);
                }
                case 0x0F4D92 :
                {
                        RGB_color_name = strdup ("Yale Blue");
                        return (RGB_color_name);
                }
                case 0xFFFF00 :
                {
                        RGB_color_name = strdup ("Yellow");
                        return (RGB_color_name);
                }
                case 0xFFEF00 :
                {
                        RGB_color_name = strdup ("Yellow (process)");
                        return (RGB_color_name);
                }
                case 0xFEFE33 :
                {
                        RGB_color_name = strdup ("Yellow (RYB)");
                        return (RGB_color_name);
                }
                case 0x9ACD32 :
                {
                        RGB_color_name = strdup ("Yellow-green");
                        return (RGB_color_name);
                }
                default:
                {
                        return (NULL);
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Free the allocated memory for a DXF \c DxfRGBColor and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_RGB_color_free
(
        DxfRGBColor *RGB_color
                /*!< Pointer to the memory occupied by the DXF
                 * RGB Color. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (RGB_color == NULL)
        {
              fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        if (RGB_color->name == NULL)
        {
              fprintf (stderr,
                  (_("Warning in %s () a NULL pointer to a DxfRGBColor name was passed.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (RGB_color->name);
        free (RGB_color);
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c COLOR entities and all their data fields.
 */
void
dxf_RGB_color_free_list
(
        DxfRGBColor *colors
                /*!< a pointer to the single linked list of DXF \c COLOR
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (colors == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (colors != NULL)
        {
                DxfRGBColor *iter = (DxfRGBColor *) colors->next;
                dxf_RGB_color_free (colors);
                colors = (DxfRGBColor *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/* EOF */
