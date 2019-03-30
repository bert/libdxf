/*!
 * \file sun.c
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF sun entity (\c SUN).
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


#include "sun.h"


/*!
 * \brief Allocate memory for a DXF \c SUN entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSun *
dxf_sun_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSun *sun = NULL;
        size_t size;

        size = sizeof (DxfSun);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((sun = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                sun = NULL;
        }
        else
        {
                memset (sun, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SUN
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSun *
dxf_sun_init
(
        DxfSun *sun
                /*!< a pointer to the DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                sun = dxf_sun_new ();
        }
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->id_code = 0;
        sun->linetype = strdup (DXF_DEFAULT_LINETYPE);
        sun->layer = strdup (DXF_DEFAULT_LAYER);
        sun->elevation = 0.0;
        sun->thickness = 0.0;
        sun->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        sun->visibility = DXF_DEFAULT_VISIBILITY;
        sun->color = DXF_COLOR_BYLAYER;
        sun->paperspace = DXF_MODELSPACE;
        sun->graphics_data_size = 0;
        sun->shadow_mode = 0;
        sun->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        sun->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (sun->binary_graphics_data);
        sun->dictionary_owner_soft = strdup ("");
        sun->object_owner_soft = strdup ("");
        sun->material = strdup ("");
        sun->dictionary_owner_hard = strdup ("");
        sun->lineweight = 0;
        sun->plot_style_name = strdup ("");
        sun->color_value = 0;
        sun->color_name = strdup ("");
        sun->transparency = 0;
        sun->intensity = 0.0;
        sun->sun_color = DXF_COLOR_BYLAYER;
        sun->shadow_type = 0;
        sun->shadow_map_size = 0;
        sun->version = 0;
        sun->julian_day = 0;
        sun->time = 0;
        sun->shadow_softness = 0;
        sun->status = 0;
        sun->shadows = 0;
        sun->daylight_savings_time = 0;
        sun->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/* EOF */
