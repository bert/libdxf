/*!
 * \file style.c
 *
 * \author Copyright (C) 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF style entity (\c STYLE).
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#include "style.h"


/*!
 * \brief Allocate memory for a DXF \c STYLE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfStyle *
dxf_style_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfStyle *dxf_style = NULL;
        size_t size;

        size = sizeof (DxfStyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_style = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfStyle struct.\n")),
                  __FUNCTION__);
                dxf_style = NULL;
        }
        else
        {
                memset (dxf_style, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_style);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c STYLE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfStyle *
dxf_style_init
(
        DxfStyle *dxf_style
                /*!< DXF style entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_style == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_style = dxf_style_new ();
        }
        if (dxf_style == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfStyle struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_style->id_code = 0;
        dxf_style->style_name = strdup ("");
        dxf_style->primary_font_filename = strdup ("");
        dxf_style->big_font_filename = strdup ("");
        dxf_style->height = 0.0;
        dxf_style->width = 0.0;
        dxf_style->last_height = 0.0;
        dxf_style->oblique_angle = 0.0;
        dxf_style->flag = 0;
        dxf_style->text_generation_flag = 0;
        dxf_style->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_style);
}


/* EOF*/
