/*!
 * \file mleader.c
 *
 * \author Copyright (C) 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mleader entity (\c MLEADER).
 *
 * \since The \c MLEADER entity was introduced in DXF R2007.
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


#include "mleader.h"


/*!
 * \brief Allocate memory for a DXF \c MLEADER entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeader *
dxf_mleader_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMLeader *mleader = NULL;
        size_t size;

        size = sizeof (DxfMLeader);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mleader = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                mleader = NULL;
        }
        else
        {
                memset (mleader, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c MLEADER
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeader *
dxf_mleader_init
(
        DxfMLeader *mleader
                /*!< a pointer to the DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mleader = dxf_mleader_new ();
        }
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->id_code = 0;
        mleader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mleader->layer = strdup (DXF_DEFAULT_LAYER);
        mleader->elevation = 0.0;
        mleader->thickness = 0.0;
        mleader->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        mleader->visibility = DXF_DEFAULT_VISIBILITY;
        mleader->color = DXF_COLOR_BYLAYER;
        mleader->paperspace = DXF_MODELSPACE;
        mleader->graphics_data_size = 0;
        mleader->shadow_mode = 0;
        mleader->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        mleader->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (mleader->binary_graphics_data);
        mleader->dictionary_owner_soft = strdup ("");
        mleader->object_owner_soft = strdup ("");
        mleader->material = strdup ("");
        mleader->dictionary_owner_hard = strdup ("");
        mleader->lineweight = 0;
        mleader->plot_style_name = strdup ("");
        mleader->color_value = 0;
        mleader->color_name = strdup ("");
        mleader->transparency = 0;
        mleader->block_content_scale = 0.0;
        mleader->dogleg_length = 0.0;
        mleader->arrowhead_size = 0.0;
        mleader->block_content_rotation = 0.0;
        mleader->block_attribute_width = 0.0;
        mleader->property_override_flag = 0;
        mleader->leader_line_color = 0;
        mleader->text_color = 0;
        mleader->block_content_color = 0;
        mleader->arrowhead_index = 0;
        mleader->text_right_attachment_type = 0;
        mleader->leader_linetype_style = 0;
        mleader->leader_line_weight = 0;
        mleader->content_type = 0;
        mleader->text_left_attachment_type = 0;
        mleader->text_angle_type = 0;
        mleader->text_alignment_type = 0;
        mleader->block_content_connection_type = 0;
        mleader->block_attribute_index = 0;
        mleader->text_align_in_IPE = 0;
        mleader->text_attachment_point = 0;
        mleader->text_attachment_direction = 0;
        mleader->bottom_text_attachment_direction = 0;
        mleader->top_text_attachment_direction = 0;
        mleader->enable_landing = 0;
        mleader->enable_dogleg = 0;
        mleader->enable_frame_text = 0;
        mleader->enable_annotation_scale = 0;
        mleader->text_direction_negative = 0;
        mleader->block_attribute_text_string = strdup ("");
        mleader->block_attribute_id = strdup ("");
        mleader->leader_style_id = strdup ("");
        mleader->arrowhead_id = strdup ("");
        mleader->text_style_id = strdup ("");
        mleader->block_content_id = strdup ("");
        mleader->arrow_head_id = strdup ("");
        mleader->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Free the allocated memory for a DXF \c MLEADER entity and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mleader_free
(
        DxfMLeader *mleader
                /*!< a pointer to the memory occupied by the DXF
                 * \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (mleader->linetype);
        free (mleader->layer);
        dxf_binary_graphics_data_free_list (mleader->binary_graphics_data);
        free (mleader->dictionary_owner_soft);
        free (mleader->object_owner_soft);
        free (mleader->material);
        free (mleader->dictionary_owner_hard);
        free (mleader->plot_style_name);
        free (mleader->color_name);
        free (mleader->block_attribute_text_string);
        free (mleader->block_attribute_id);
        free (mleader->leader_style_id);
        free (mleader->leader_linetype_id);
        free (mleader->arrowhead_id);
        free (mleader->text_style_id);
        free (mleader->block_content_id);
        free (mleader->arrow_head_id);
        free (mleader);
        mleader = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c MLEADER entities and all their data fields.
 */
void
dxf_mleader_free_list
(
        DxfMLeader *mleaders
                /*!< a pointer to the single linked list of DXF
                 * \c MLEADER entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (mleaders == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (mleaders != NULL)
        {
                DxfMLeader *iter = (DxfMLeader *) mleaders->next;
                dxf_mleader_free (mleaders);
                mleaders = (DxfMLeader *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c MLEADER entity.
 *
 * \return \c id_code.
 */
int
dxf_mleader_get_id_code
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mleader->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_id_code
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
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
        if (mleader == NULL)
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
        mleader->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c linetype from a DXF \c MLEADER entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_mleader_get_linetype
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_linetype
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
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
        mleader->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c layer from a DXF \c MLEADER entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_mleader_get_layer
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mleader->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->layer));
}


/* EOF*/
