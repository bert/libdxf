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


/* EOF */