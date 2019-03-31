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


/* EOF */
