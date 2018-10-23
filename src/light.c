/*!
 * \file light.c
 *
 * \author Copyright (C) 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF light entity (\c LIGHT).
 *
 * \since The \c LIGHT entity was introduced in DXF R2007.
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


#include "light.h"


/*!
 * \brief Allocate memory for a DXF \c LIGHT.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLight *
dxf_light_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLight *light = NULL;
        size_t size;

        size = sizeof (DxfLight);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((light = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                light = NULL;
        }
        else
        {
                memset (light, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LIGHT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLight *
dxf_light_init
(
        DxfLight *light
                /*!< DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                light = dxf_light_new ();
        }
        if (light == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        light->id_code = 0;
        light->linetype = strdup (DXF_DEFAULT_LINETYPE);
        light->layer = strdup (DXF_DEFAULT_LAYER);
        light->thickness = 0.0;
        light->linetype_scale = 0.0;
        light->visibility = 0;
        light->color = DXF_COLOR_BYLAYER;
        light->paperspace = DXF_MODELSPACE;
        light->graphics_data_size = 0;
        light->shadow_mode = 0;
        light->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (light->binary_graphics_data);
        light->dictionary_owner_hard = strdup ("");
        light->material = strdup ("");
        light->dictionary_owner_soft = strdup ("");
        light->lineweight = 0;
        light->plot_style_name = strdup ("");
        light->color_value = 0;
        light->color_name = strdup ("");
        light->transparency = 0;
        light->light_name = strdup ("");
        light->p0 = dxf_point_init (light->p0);
        light->p1 = dxf_point_init (light->p1);
        light->intensity = 0.0;
        light->attenuation_start_limit = 0.0;
        light->attenuation_end_limit = 0.0;
        light->hotspot_angle = 0.0;
        light->falloff_angle = 0.0;
        light->light_type = 0;
        light->attenuation_type = 0;
        light->shadow_type = 0;
        light->version_number = 0;
        light->shadow_map_size = 0;
        light->shadow_map_softness = 0;
        light->status = 0;
        light->plot_glyph = 0;
        light->use_attenuation_limits = 0;
        light->cast_shadows =0;
        light->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/* EOF*/
