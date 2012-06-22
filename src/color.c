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


/* EOF */
