/*!
 * \file surface.c
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF surface entity (\c SURFACE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * \since The \c SURFACE entity was introduced in DXF R2007.
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


#include "surface.h"


/*!
 * \brief Allocate memory for a DXF \c SURFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurface *
dxf_surface_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSurface *surface = NULL;
        size_t size;

        size = sizeof (DxfSurface);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((surface = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                surface = NULL;
        }
        else
        {
                memset (surface, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SURFACE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurface *
dxf_surface_init
(
        DxfSurface *surface
                /*!< a pointer to the DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                surface = dxf_surface_new ();
        }
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        surface->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (surface->binary_graphics_data);
        if (surface->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->proprietary_data = (DxfProprietaryData *) dxf_proprietary_data_init (surface->proprietary_data);
        if (surface->proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->additional_proprietary_data = (DxfProprietaryData *) dxf_proprietary_data_init (surface->additional_proprietary_data);
        if (surface->additional_proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        surface->id_code = 0;
        surface->linetype = strdup (DXF_DEFAULT_LINETYPE);
        surface->layer = strdup (DXF_DEFAULT_LAYER);
        surface->elevation = 0.0;
        surface->thickness = 0.0;
        surface->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        surface->visibility = DXF_DEFAULT_VISIBILITY;
        surface->color = DXF_COLOR_BYLAYER;
        surface->paperspace = DXF_MODELSPACE;
        surface->graphics_data_size = 0;
        surface->shadow_mode = 0;
        surface->dictionary_owner_soft = strdup ("");
        surface->object_owner_soft = strdup ("");
        surface->material = strdup ("");
        surface->dictionary_owner_hard = strdup ("");
        surface->lineweight = 0;
        surface->plot_style_name = strdup ("");
        surface->color_value = 0;
        surface->color_name = strdup ("");
        surface->transparency = 0;
        surface->modeler_format_version_number = 1;
        surface->number_of_U_isolines = 0;
        surface->number_of_V_isolines = 0;
        surface->type = 0;
        surface->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Free the allocated memory for a DXF \c SURFACE entity and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_surface_free
(
        DxfSurface *surface
                /*!< a pointer to the memory occupied by the DXF
                 * \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (surface->linetype);
        free (surface->layer);
        free (surface->dictionary_owner_soft);
        free (surface->object_owner_soft);
        free (surface->material);
        free (surface->dictionary_owner_hard);
        free (surface->plot_style_name);
        free (surface->color_name);
        dxf_proprietary_data_free_list (surface->proprietary_data);
        dxf_proprietary_data_free_list (surface->additional_proprietary_data);
        free (surface);
        surface = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SURFACE entities and all their data fields.
 */
void
dxf_surface_free_list
(
        DxfSurface *surfaces
                /*!< a pointer to the single linked list of DXF
                 * \c SURFACE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (surfaces != NULL)
        {
                DxfSurface *iter = (DxfSurface *) surfaces->next;
                dxf_surface_free (surfaces);
                surfaces = (DxfSurface *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SURFACE entity.
 *
 * \return \c id_code.
 */
int
dxf_surface_get_id_code
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_id_code
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
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
        if (surface == NULL)
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
        surface->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c linetype from a DXF \c SURFACE entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_surface_get_linetype
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 *
 * \note the pointer to \c linetype is not freed.
 */
DxfSurface *
dxf_surface_set_linetype
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c layer from a DXF \c SURFACE entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_surface_get_layer
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_layer
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c elevation from a DXF \c SURFACE entity.
 *
 * \return \c elevation.
 */
double
dxf_surface_get_elevation
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_elevation
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c thickness from a DXF \c SURFACE entity.
 *
 * \return \c thickness.
 */
double
dxf_surface_get_thickness
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->thickness == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_thickness
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        if (thickness == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        surface->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c SURFACE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_surface_get_linetype_scale
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->linetype_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_linetype_scale
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        if (linetype_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        surface->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c visibility from a DXF \c SURFACE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_surface_get_visibility
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_visibility
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c color from a DXF \c SURFACE entity.
 *
 * \return color.
 */
int16_t
dxf_surface_get_color
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->color);
}


/*!
 * \brief Set the \c color for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_color
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c SURFACE entity.
 *
 * \return \c paperspace flag value.
 */
int16_t
dxf_surface_get_paperspace
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_paperspace
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c SURFACE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_surface_get_graphics_data_size
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c SURFACE
 * entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_graphics_data_size
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c SURFACE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_surface_get_shadow_mode
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_shadow_mode
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c SURFACE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_surface_get_binary_graphics_data
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) surface->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_binary_graphics_data
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SURFACE entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_surface_get_dictionary_owner_soft
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_dictionary_owner_soft
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c SURFACE entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_surface_get_object_owner_soft
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c SURFACE entity.
 */
DxfSurface *
dxf_surface_set_object_owner_soft
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c SURFACE
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_surface_get_material
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c SURFACE
 * entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_material
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SURFACE entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_surface_get_dictionary_owner_hard
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_dictionary_owner_hard
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c lineweight from a DXF \c SURFACE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_surface_get_lineweight
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_lineweight
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c SURFACE entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_surface_get_plot_style_name
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_plot_style_name
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c color_value from a DXF \c SURFACE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_surface_get_color_value
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_color_value
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c color_name from a DXF \c SURFACE entity.
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_surface_get_color_name
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_color_name
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c transparency from a DXF \c SURFACE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_surface_get_transparency
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_transparency
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c proprietary_data from a DXF \c
 * SURFACE entity.
 *
 * \return pointer to the \c proprietary_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfProprietaryData *
dxf_surface_get_proprietary_data
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->proprietary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfProprietaryData *) surface->proprietary_data);
}


/*!
 * \brief Set the proprietary data for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_proprietary_data
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        DxfProprietaryData *proprietary_data
                /*!< a pointer to a linked list containing the
                 * \c proprietary_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->proprietary_data = proprietary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c additional_proprietary_data from a DXF \c SURFACE
 * entity.
 *
 * \return pointer to the \c additional_proprietary_data.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
DxfProprietaryData *
dxf_surface_get_additional_proprietary_data
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->additional_proprietary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfProprietaryData *) surface->additional_proprietary_data);
}


/*!
 * \brief Set the pointer to the additional proprietary data for a DXF
 * \c SURFACE entity.
 */
DxfSurface *
dxf_surface_set_additional_proprietary_data
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        DxfProprietaryData *additional_proprietary_data
                /*!< an array containing the additional proprietary data
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (additional_proprietary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->additional_proprietary_data = additional_proprietary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the modeler format version number from a DXF \c SURFACE
 * entity.
 *
 * \return \c modeler_format_version_number.
 */
int16_t
dxf_surface_get_modeler_format_version_number
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->modeler_format_version_number != 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->modeler_format_version_number);
}


/*!
 * \brief Set the modeler format version number for a DXF \c SURFACE
 * entity.
 */
DxfSurface *
dxf_surface_set_modeler_format_version_number
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t modeler_format_version_number
                /*!< Modeler format version number (currently = 1). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (modeler_format_version_number != 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->modeler_format_version_number = modeler_format_version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the number of U isolines from a DXF \c SURFACE entity.
 *
 * \return \c number_of_U_isolines.
 */
int16_t
dxf_surface_get_number_of_U_isolines
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->number_of_U_isolines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->number_of_U_isolines == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->number_of_U_isolines);
}


/*!
 * \brief Set the number of U isolines for a DXF \c SURFACE entity.
 */
DxfSurface *
dxf_surface_set_number_of_U_isolines
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t number_of_U_isolines
                /*!< Number of U isolines. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_U_isolines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (number_of_U_isolines == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        surface->number_of_U_isolines = number_of_U_isolines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the number of V isolines from a DXF \c SURFACE entity.
 *
 * \return \c number_of_V_isolines.
 */
int16_t
dxf_surface_get_number_of_V_isolines
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->number_of_V_isolines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->number_of_V_isolines == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->number_of_V_isolines);
}


/*!
 * \brief Set the number of V isolines for a DXF \c SURFACE entity.
 */
DxfSurface *
dxf_surface_set_number_of_V_isolines
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t number_of_V_isolines
                /*!< Number of V isolines. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_V_isolines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (number_of_V_isolines == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        surface->number_of_V_isolines = number_of_V_isolines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the next \c SURFACE entity from a DXF 
 * \c SURFACE entity.
 *
 * \return pointer to the next \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurface *
dxf_surface_get_next
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurface *) surface->next);
}


/*!
 * \brief Set the pointer to the next \c SURFACE for a DXF \c SURFACE
 * entity.
 */
DxfSurface *
dxf_surface_set_next
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        DxfSurface *next
                /*!< a pointer to the next \c SURFACE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->next = (struct DxfSurface *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the last \c SURFACE entity from a linked list
 * of DXF \c SURFACE entities.
 *
 * \return pointer to the last \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurface *
dxf_surface_get_last
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfSurface *) surface);
        }
        DxfSurface *iter = (DxfSurface *) surface->next;
        while (iter->next != NULL)
        {
                iter = (DxfSurface *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurface *) iter);
}


/*!
 * \brief Allocate memory for a DXF extruded \c SURFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSurfaceExtruded *extruded_surface = NULL;
        size_t size;

        size = sizeof (DxfSurfaceExtruded);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((extruded_surface = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                extruded_surface = NULL;
        }
        else
        {
                memset (extruded_surface, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * extruded \c SURFACE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_init
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to the DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                extruded_surface = dxf_surface_extruded_new ();
        }
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        extruded_surface->p0 = (DxfPoint *) dxf_point_init (extruded_surface->p0);
        if (extruded_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->p1 = (DxfPoint *) dxf_point_init (extruded_surface->p1);
        if (extruded_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->transform_matrix = (DxfDouble *) dxf_double_init (extruded_surface->transform_matrix);
        if (extruded_surface->transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->sweep_matrix = (DxfDouble *) dxf_double_init (extruded_surface->sweep_matrix);
        if (extruded_surface->sweep_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->path_matrix = (DxfDouble *) dxf_double_init (extruded_surface->path_matrix);
        if (extruded_surface->path_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->binary_data = (DxfBinaryData *) dxf_binary_data_init (extruded_surface->binary_data);
        if (extruded_surface->binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        extruded_surface->draft_angle = 0.0;
        extruded_surface->draft_start_distance = 0.0;
        extruded_surface->draft_end_distance = 0.0;
        extruded_surface->twist_angle = 0.0;
        extruded_surface->scale_factor = 0.0;
        extruded_surface->align_angle = 0.0;
        extruded_surface->sweep_alignment_option = 0;
        extruded_surface->class_ID = 0;
        extruded_surface->binary_data_size = 0;
        extruded_surface->solid_flag =0;
        extruded_surface->align_start_flag = 0;
        extruded_surface->bank_flag = 0;
        extruded_surface->base_point_set_flag = 0;
        extruded_surface->sweep_transform_computed_flag = 0;
        extruded_surface->path_transform_computed_flag = 0;
        extruded_surface->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Free the allocated memory for a DXF extruded \c SURFACE entity
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_surface_extruded_free
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to the memory occupied by the DXF
                 * extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_point_free (extruded_surface->p0);
        dxf_point_free (extruded_surface->p1);
        dxf_double_free (extruded_surface->transform_matrix);
        dxf_double_free (extruded_surface->sweep_matrix);
        dxf_double_free (extruded_surface->path_matrix);
        dxf_binary_data_free_list (extruded_surface->binary_data);
        free (extruded_surface);
        extruded_surface = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * extruded \c SURFACE entities and all their data fields.
 */
void
dxf_surface_extruded_free_list
(
        DxfSurfaceExtruded *extruded_surfaces
                /*!< a pointer to the single linked list of DXF
                 * extruded \c SURFACE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (extruded_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (extruded_surfaces != NULL)
        {
                DxfSurfaceExtruded *iter = (DxfSurfaceExtruded *) extruded_surfaces->next;
                dxf_surface_extruded_free (extruded_surfaces);
                extruded_surfaces = (DxfSurfaceExtruded *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/* EOF */
