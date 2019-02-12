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
 * \brief Free the allocated memory for a DXF \c MLEADERSTYLE entity and all
 * it's data fields.
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
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when an error
 * occurred.
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
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when an
 * error occurred.
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


/* EOF*/
