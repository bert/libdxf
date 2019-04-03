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


/*!
 * \brief Free the allocated memory for a DXF \c SUN entity and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_sun_free
(
        DxfSun *sun
                /*!< a pointer to the memory occupied by the DXF \c SUN
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (sun->linetype);
        free (sun->layer);
        free (sun->dictionary_owner_soft);
        free (sun->object_owner_soft);
        free (sun->material);
        free (sun->dictionary_owner_hard);
        free (sun->plot_style_name);
        free (sun->color_name);
        free (sun);
        sun = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SUN entities and all their data fields.
 */
void
dxf_sun_free_list
(
        DxfSun *suns
                /*!< a pointer to the single linked list of DXF
                 * \c SUN entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (suns == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (suns != NULL)
        {
                DxfSun *iter = (DxfSun *) suns->next;
                dxf_sun_free (suns);
                suns = (DxfSun *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SUN entity.
 *
 * \return \c id_code.
 */
int
dxf_sun_get_id_code
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_id_code
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int id_code
                /*!< the \c id_code to be set for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        sun->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c linetype from a DXF \c SUN entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_sun_get_linetype
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_linetype
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c layer from a DXF \c SUN entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_sun_get_layer
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_layer
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c elevation from a DXF \c SUN entity.
 *
 * \return \c elevation.
 */
double
dxf_sun_get_elevation
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_elevation
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c thickness from a DXF \c SUN entity.
 *
 * \return \c thickness.
 */
double
dxf_sun_get_thickness
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_thickness
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        sun->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c SUN entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_sun_get_linetype_scale
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_linetype_scale
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        sun->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c visibility from a DXF \c SUN entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_sun_get_visibility
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_visibility
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        sun->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c color from a DXF \c SUN entity.
 *
 * \return color.
 */
int
dxf_sun_get_color
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->color);
}


/*!
 * \brief Set the \c color for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_color
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        sun->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c SUN entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_sun_get_paperspace
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_paperspace
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        sun->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c SUN entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_sun_get_graphics_data_size
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_graphics_data_size
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        sun->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c SUN entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_sun_get_shadow_mode
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_shadow_mode
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        sun->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c SUN entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_sun_get_binary_graphics_data
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) sun->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_binary_graphics_data
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SUN entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sun_get_dictionary_owner_soft
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_dictionary_owner_soft
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c SUN entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sun_get_object_owner_soft
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c SUN entity.
 */
DxfSun *
dxf_sun_set_object_owner_soft
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c SUN entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_sun_get_material
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_material
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SUN entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sun_get_dictionary_owner_hard
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_dictionary_owner_hard
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c lineweight from a DXF \c SUN entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_sun_get_lineweight
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_lineweight
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c SUN entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_sun_get_plot_style_name
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_plot_style_name
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/* EOF */
