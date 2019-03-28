/*!
 * \file rtext.c
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF rtext entity (\c RTEXT).
 *
 * \version According to DXF R15.
 * \version According to DXF R2000.
 *
 * \since Introduced in version R15.
 *
 * \deprecated As of version R2002.
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


#include "rtext.h"


/*!
 * \brief Allocate memory for a \c DxfRText.
 *
 * Fill the memory contents with zeros.
 */
DxfRText *
dxf_rtext_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfRText *rtext = NULL;
        size_t size;

        size = sizeof (DxfRText);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((rtext = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRText struct.\n")),
                  __FUNCTION__);
                rtext = NULL;
        }
        else
        {
                memset (rtext, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c RTEXT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfRText *
dxf_rtext_init
(
        DxfRText *rtext
                /*!< a pointer to the DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                rtext = dxf_rtext_new ();
        }
        if (rtext == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfRText struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        rtext->id_code = 0;
        rtext->linetype = strdup (DXF_DEFAULT_LINETYPE);
        rtext->layer = strdup (DXF_DEFAULT_LAYER);
        rtext->elevation = 0.0;
        rtext->thickness = 0.0;
        rtext->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        rtext->visibility = DXF_DEFAULT_VISIBILITY;
        rtext->color = DXF_COLOR_BYLAYER;
        rtext->paperspace = DXF_MODELSPACE;
        rtext->graphics_data_size = 0;
        rtext->shadow_mode = 0;
        rtext->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        rtext->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) rtext->binary_graphics_data);
        rtext->dictionary_owner_soft = strdup ("");
        rtext->material = strdup ("");
        rtext->dictionary_owner_hard = strdup ("");
        rtext->lineweight = 0;
        rtext->plot_style_name = strdup ("");
        rtext->color_value = 0;
        rtext->color_name = strdup ("");
        rtext->transparency = 0;
        rtext->text_value = strdup ("");
        rtext->text_style = strdup ("");
        rtext->p0 = (DxfPoint *) dxf_point_new ();
        rtext->p0 = dxf_point_init ((DxfPoint *) rtext->p0);
        rtext->p0->x0 = 0.0;
        rtext->p0->y0 = 0.0;
        rtext->p0->z0 = 0.0;
        rtext->height = 0.0;
        rtext->rot_angle = 0.0;
        rtext->type_flags = 0;
        rtext->extr_x0 = 0.0;
        rtext->extr_y0 = 0.0;
        rtext->extr_z0 = 0.0;
        rtext->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Free the allocated memory for a DXF \c RTEXT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_rtext_free
(
        DxfRText *rtext
                /*!< a pointer to the memory occupied by the DXF
                 * \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (rtext->linetype);
        free (rtext->layer);
        dxf_binary_graphics_data_free_list (rtext->binary_graphics_data);
        free (rtext->dictionary_owner_soft);
        free (rtext->material);
        free (rtext->dictionary_owner_hard);
        free (rtext->plot_style_name);
        free (rtext->color_name);
        free (rtext->text_value);
        free (rtext->text_style);
        dxf_point_free (rtext->p0);
        free (rtext);
        rtext = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c RTEXT entities and all their data fields.
 */
void
dxf_rtext_free_list
(
        DxfRText *rtexts
                /*!< a pointer to the single linked list of DXF \c RTEXT
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (rtexts == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (rtexts != NULL)
        {
                DxfRText *iter = (DxfRText *) rtexts->next;
                dxf_rtext_free (rtexts);
                rtexts = (DxfRText *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c RTEXT entity.
 *
 * \return \c id_code.
 */
int
dxf_rtext_get_id_code
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_id_code
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
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
        if (rtext == NULL)
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
        rtext->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c linetype from a DXF \c RTEXT entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_rtext_get_linetype
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_linetype
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c layer from a DXF \c RTEXT entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_rtext_get_layer
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_layer
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c elevation from a DXF \c RTEXT entity.
 *
 * \return \c elevation.
 */
double
dxf_rtext_get_elevation
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_elevation
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c thickness from a DXF \c RTEXT entity.
 *
 * \return \c thickness.
 */
double
dxf_rtext_get_thickness
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_thickness
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c RTEXT entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_rtext_get_linetype_scale
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_linetype_scale
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c visibility from a DXF \c RTEXT entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_rtext_get_visibility
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (rtext->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_visibility
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c color from a DXF \c RTEXT entity.
 *
 * \return \c color.
 */
int
dxf_rtext_get_color
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->color);
}


/*!
 * \brief Set the \c color for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_color
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c RTEXT entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_rtext_get_paperspace
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (rtext->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_paperspace
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c RTEXT entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_rtext_get_graphics_data_size
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (rtext->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_graphics_data_size
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c RTEXT entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_rtext_get_shadow_mode
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (rtext->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_shadow_mode
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c RTEXT entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_rtext_get_binary_graphics_data
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) rtext->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_binary_graphics_data
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c RTEXT entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_rtext_get_dictionary_owner_soft
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_dictionary_owner_soft
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c RTEXT entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_rtext_get_material
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_material
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c RTEXT entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_rtext_get_dictionary_owner_hard
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_dictionary_owner_hard
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c lineweight from a DXF \c RTEXT entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_rtext_get_lineweight
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_lineweight
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c RTEXT entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_rtext_get_plot_style_name
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_plot_style_name
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c color_value from a DXF \c RTEXT entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_rtext_get_color_value
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_color_value
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c color_name from a DXF \c RTEXT entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_rtext_get_color_name
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_color_name
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
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
        rtext->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c transparency from a DXF \c RTEXT entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_rtext_get_transparency
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_transparency
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c text_value from a DXF \c RTEXT entity.
 *
 * \return \c text_value when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_rtext_get_text_value
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->text_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->text_value));
}


/*!
 * \brief Set the \c text_value for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_text_value
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *text_value
                /*!< a string containing the \c text_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->text_value = strdup (text_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c text_style from a DXF \c RTEXT entity.
 *
 * \return \c text_style when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_rtext_get_text_style
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->text_style ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (rtext->text_style));
}


/*!
 * \brief Set the \c text_style for a DXF \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_text_style
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        char *text_style
                /*!< a string containing the \c text_style for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->text_style = strdup (text_style);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the insertion point \c p0 of a DXF \c RTEXT entity.
 *
 * \return the insertion point \c p0.
 */
DxfPoint *
dxf_rtext_get_p0
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a DXF \c RTEXT entity.
 *
 * \return a pointer to a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_p0
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a DXF \c RTEXT
 * entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_rtext_get_x0
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a DXF \c RTEXT
 * entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_x0
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double x0
                /*!< the X-value of the insertion point \c x0 of a DXF
                 * \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a DXF \c RTEXT
 * entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_rtext_get_y0
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a DXF \c RTEXT
 * entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_y0
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a DXF
                 * \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a DXF \c RTEXT
 * entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_rtext_get_z0
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a DXF \c RTEXT
 * entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_z0
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double z0
                /*!< the Z-value of the insertion point \c z0 of a DXF
                 * \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c height from a DXF \c RTEXT entity.
 *
 * \return \c height.
 */
double
dxf_rtext_get_height
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (rtext->height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->height);
}


/*!
 * \brief Set the \c height for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_height
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double height
                /*!< the \c height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        rtext->height = height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c rot_angle from a DXF \c RTEXT entity.
 *
 * \return \c rot_angle.
 */
double
dxf_rtext_get_rot_angle
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->rot_angle < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->rot_angle);
}


/*!
 * \brief Set the \c rot_angle for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_rot_angle
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double rot_angle
                /*!< the \c rot_angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rot_angle < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        rtext->rot_angle = rot_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the \c type_flags from a DXF \c RTEXT entity.
 *
 * \return \c type_flags.
 */
int
dxf_rtext_get_type_flags
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->type_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (rtext->type_flags > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->type_flags);
}


/*!
 * \brief Set the \c type_flags for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_type_flags
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        int type_flags
                /*!< the \c type_flags to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (type_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (type_flags > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        rtext->type_flags = type_flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c RTEXT entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_rtext_get_extr_x0
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_extr_x0
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c RTEXT entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_rtext_get_extr_y0
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_extr_y0
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c RTEXT entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_rtext_get_extr_z0
(
        DxfRText *rtext
                /*!< a pointer to a DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c RTEXT entity.
 *
 * \return a pointer to \c rtext when successful, or \c NULL when an
 * error occurred.
 */
DxfRText *
dxf_rtext_set_extr_z0
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c RTEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF
 * \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_extrusion_vector_from_point
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->extr_x0 = (double) point->x0;
        rtext->extr_y0 = (double) point->y0;
        rtext->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Set the extrusion vector for a DXF \c RTEXT entity.
 */
DxfRText *
dxf_rtext_set_extrusion_vector
(
        DxfRText *rtext,
                /*!< a pointer to a DXF \c RTEXT entity. */
        double extr_x0,
                /*!<  X-value of the extrusion direction. */
        double extr_y0,
                /*!<  Y-value of the extrusion direction. */
        double extr_z0
                /*!<  Z-value of the extrusion direction. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rtext->extr_x0 = extr_x0;
        rtext->extr_y0 = extr_y0;
        rtext->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/* EOF */
