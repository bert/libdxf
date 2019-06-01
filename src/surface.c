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
 * \return a pointer to \c surface when successful, or \c NULL when an error
 * occurred.
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
 * \return a pointer to \c surface when successful, or \c NULL when an error
 * occurred.
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
 * \return a pointer to \c surface when successful, or \c NULL when an error
 * occurred.
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


/* EOF */
