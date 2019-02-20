/*!
 * \file mleaderstyle.c
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mleaderstyle entity (\c MLEADERSTYLE).
 *
 * \since The \c MLEADERSTYLE entity was introduced in DXF R2007.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.\n\n
 * This program is distributed in the hope that it will be useful, but
 * <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
 * <b>MERCHANTABILITY</b> or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.\n
 * See the GNU General Public License for more details.\n\n
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to:\n
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


#include "mleaderstyle.h"


/*!
 * \brief Allocate memory for a DXF \c MLEADERSTYLE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMLeaderstyle *mleaderstyle = NULL;
        size_t size;

        size = sizeof (DxfMLeaderstyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mleaderstyle = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                mleaderstyle = NULL;
        }
        else
        {
                memset (mleaderstyle, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c MLEADERSTYLE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_init
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to the DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mleaderstyle = dxf_mleaderstyle_new ();
        }
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->id_code = 0;
        mleaderstyle->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mleaderstyle->layer = strdup (DXF_DEFAULT_LAYER);
        mleaderstyle->elevation = 0.0;
        mleaderstyle->thickness = 0.0;
        mleaderstyle->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        mleaderstyle->visibility = DXF_DEFAULT_VISIBILITY;
        mleaderstyle->color = DXF_COLOR_BYLAYER;
        mleaderstyle->paperspace = DXF_MODELSPACE;
        mleaderstyle->graphics_data_size = 0;
        mleaderstyle->shadow_mode = 0;
        mleaderstyle->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        mleaderstyle->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (mleaderstyle->binary_graphics_data);
        mleaderstyle->dictionary_owner_soft = strdup ("");
        mleaderstyle->object_owner_soft = strdup ("");
        mleaderstyle->material = strdup ("");
        mleaderstyle->dictionary_owner_hard = strdup ("");
        mleaderstyle->lineweight = 0;
        mleaderstyle->plot_style_name = strdup ("");
        mleaderstyle->color_value = 0;
        mleaderstyle->color_name = strdup ("");
        mleaderstyle->transparency = 0;
        mleaderstyle->mleaderstyle_description = strdup ("");
        mleaderstyle->first_segment_angle_constraint = 0.0;
        mleaderstyle->second_segment_angle_constraint = 0.0;
        mleaderstyle->landing_gap = 0.0;
        mleaderstyle->dogleg_length = 0.0;
        mleaderstyle->arrowhead_size = 0.0;
        mleaderstyle->text_height = 1.0;
        mleaderstyle->align_space = 0.0;
        mleaderstyle->block_content_scale_x = 1.0;
        mleaderstyle->block_content_scale_y = 1.0;
        mleaderstyle->leader_line_weight = 0;
        mleaderstyle->maxleader_segment_points = 1;
        mleaderstyle->text_color = DXF_COLOR_BYLAYER;
        mleaderstyle->block_content_color = DXF_COLOR_BYLAYER;
        mleaderstyle->block_content_scale_z = 1.0;
        mleaderstyle->block_content_rotation = 0.0;
        mleaderstyle->scale = 1.0;
        mleaderstyle->break_gap_size = 0.0;
        mleaderstyle->content_type = 0;
        mleaderstyle->draw_mleader_order_type = 0;
        mleaderstyle->leader_line_color = DXF_COLOR_BYLAYER;
        mleaderstyle->text_left_attachment_type = 0;
        mleaderstyle->text_angle_type = 0;
        mleaderstyle->text_alignment_type = 0;
        mleaderstyle->block_content_connection_type = 0;
        mleaderstyle->text_right_attachment_type = 0;
        mleaderstyle->text_attachment_direction = 0;
        mleaderstyle->bottom_text_attachment_direction = 0;
        mleaderstyle->top_text_attachment_direction = 0;
        mleaderstyle->enable_landing = 1;
        mleaderstyle->enable_dogleg = 1;
        mleaderstyle->enable_frame_text = 1;
        mleaderstyle->enable_block_content_scale = 1;
        mleaderstyle->enable_block_content_rotation = 1;
        mleaderstyle->overwrite_property_value = 1;
        mleaderstyle->is_annotative = 1;
        mleaderstyle->text_align_always_left = 1;
        mleaderstyle->default_mtext_contents = strdup ("");
        mleaderstyle->leader_linetype_id = strdup ("");
        mleaderstyle->arrow_head_id = strdup ("");
        mleaderstyle->mtext_style_id = strdup ("");
        mleaderstyle->block_content_id = strdup ("");
        mleaderstyle->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Free the allocated memory for a DXF \c MLEADERSTYLE entity and
 * all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mleaderstyle_free
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to the memory occupied by the DXF
                 * \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (mleaderstyle->linetype);
        free (mleaderstyle->layer);
        dxf_binary_graphics_data_free_list (mleaderstyle->binary_graphics_data);
        free (mleaderstyle->dictionary_owner_soft);
        free (mleaderstyle->object_owner_soft);
        free (mleaderstyle->material);
        free (mleaderstyle->dictionary_owner_hard);
        free (mleaderstyle->plot_style_name);
        free (mleaderstyle->color_name);
        free (mleaderstyle->mleaderstyle_description);
        free (mleaderstyle->default_mtext_contents);
        free (mleaderstyle->leader_linetype_id);
        free (mleaderstyle->arrow_head_id);
        free (mleaderstyle->mtext_style_id);
        free (mleaderstyle->block_content_id);
        free (mleaderstyle);
        mleaderstyle = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c MLEADERSTYLE entities and all their data fields.
 */
void
dxf_mleaderstyle_free_list
(
        DxfMLeaderstyle *mleaderstyles
                /*!< a pointer to the single linked list of DXF
                 * \c MLEADERSTYLE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (mleaderstyles == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (mleaderstyles != NULL)
        {
                DxfMLeaderstyle *iter = (DxfMLeaderstyle *) mleaderstyles->next;
                dxf_mleaderstyle_free (mleaderstyles);
                mleaderstyles = (DxfMLeaderstyle *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c id_code.
 */
int
dxf_mleaderstyle_get_id_code
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_id_code
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
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
        if (mleaderstyle == NULL)
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
        mleaderstyle->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c linetype from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_mleaderstyle_get_linetype
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_linetype
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c layer from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_mleaderstyle_get_layer
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_layer
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c elevation from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c elevation.
 */
double
dxf_mleaderstyle_get_elevation
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_elevation
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c thickness from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c thickness.
 */
double
dxf_mleaderstyle_get_thickness
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_thickness
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_mleaderstyle_get_linetype_scale
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_linetype_scale
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c visibility from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_mleaderstyle_get_visibility
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleaderstyle->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_visibility
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c color from a DXF \c MLEADERSTYLE entity.
 *
 * \return color.
 */
int
dxf_mleaderstyle_get_color
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->color);
}


/*!
 * \brief Set the \c color for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_color
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_mleaderstyle_get_paperspace
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleaderstyle->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_paperspace
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_mleaderstyle_get_graphics_data_size
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleaderstyle->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_graphics_data_size
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mleaderstyle_get_shadow_mode
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleaderstyle->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleaderstyle->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_shadow_mode
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_mleaderstyle_get_binary_graphics_data
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) mleaderstyle->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_binary_graphics_data
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c MLEADERSTYLE entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleaderstyle_get_dictionary_owner_soft
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_dictionary_owner_soft
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c MLEADERSTYLE entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleaderstyle_get_object_owner_soft
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_object_owner_soft
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_mleaderstyle_get_material
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_material
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c MLEADERSTYLE entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleaderstyle_get_dictionary_owner_hard
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_dictionary_owner_hard
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c lineweight from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mleaderstyle_get_lineweight
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_lineweight
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_mleaderstyle_get_plot_style_name
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_plot_style_name
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c color_value from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mleaderstyle_get_color_value
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_color_value
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c color_name from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mleaderstyle_get_color_name
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_color_name
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
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
        mleaderstyle->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c transparency from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mleaderstyle_get_transparency
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_transparency
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c mleaderstyle_description from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c mleaderstyle_description when successful, \c NULL when an
 * error occurred.
 */
char *
dxf_mleaderstyle_get_mleaderstyle_description
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle->mleaderstyle_description ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->mleaderstyle_description));
}


/*!
 * \brief Set the \c mleaderstyle_description for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_mleaderstyle_description
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *mleaderstyle_description
                /*!< a pointer to a string containing the
                 * \c mleaderstyle_description to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleaderstyle_description == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->mleaderstyle_description = strdup (mleaderstyle_description);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c first_segment_angle_constraint from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c first_segment_angle_constraint.
 */
double
dxf_mleaderstyle_get_first_segment_angle_constraint
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->first_segment_angle_constraint);
}


/*!
 * \brief Set the \c first_segment_angle_constraint for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_first_segment_angle_constraint
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double first_segment_angle_constraint
                /*!< the \c first_segment_angle_constraint to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->first_segment_angle_constraint = first_segment_angle_constraint;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c second_segment_angle_constraint from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c second_segment_angle_constraint.
 */
double
dxf_mleaderstyle_get_second_segment_angle_constraint
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->second_segment_angle_constraint);
}


/*!
 * \brief Set the \c second_segment_angle_constraint for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_second_segment_angle_constraint
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double second_segment_angle_constraint
                /*!< the \c second_segment_angle_constraint to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->second_segment_angle_constraint = second_segment_angle_constraint;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c landing_gap from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c landing_gap.
 */
double
dxf_mleaderstyle_get_landing_gap
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->landing_gap);
}


/*!
 * \brief Set the \c landing_gap for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_landing_gap
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double landing_gap
                /*!< the \c landing_gap to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->landing_gap = landing_gap;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c dogleg_length from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c dogleg_length.
 */
double
dxf_mleaderstyle_get_dogleg_length
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->dogleg_length);
}


/*!
 * \brief Set the \c dogleg_length for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_dogleg_length
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double dogleg_length
                /*!< the \c dogleg_length to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->dogleg_length = dogleg_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c arrowhead_size from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c arrowhead_size.
 */
double
dxf_mleaderstyle_get_arrowhead_size
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->arrowhead_size);
}


/*!
 * \brief Set the \c arrowhead_size for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_arrowhead_size
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double arrowhead_size
                /*!< the \c arrowhead_size to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->arrowhead_size = arrowhead_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c text_height from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c text_height.
 */
double
dxf_mleaderstyle_get_text_height
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->text_height);
}


/*!
 * \brief Set the \c text_height for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_text_height
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double text_height
                /*!< the \c text_height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->text_height = text_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c align_space from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c align_space.
 */
double
dxf_mleaderstyle_get_align_space
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle->align_space);
}


/* EOF*/
