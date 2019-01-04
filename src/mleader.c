/*!
 * \file mleader.c
 *
 * \author Copyright (C) 2018, 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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


/*!
 * \brief Set the \c layer for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_layer
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
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
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c elevation from a DXF \c MLEADER entity.
 *
 * \return \c elevation.
 */
double
dxf_mleader_get_elevation
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_elevation
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
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
        mleader->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c thickness from a DXF \c MLEADER entity.
 *
 * \return \c thickness.
 */
double
dxf_mleader_get_thickness
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
        if (mleader->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_thickness
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
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
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c MLEADER entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_mleader_get_linetype_scale
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
        if (mleader->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_linetype_scale
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
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
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c visibility from a DXF \c MLEADER entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_mleader_get_visibility
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
        if (mleader->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_visibility
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
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
        mleader->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c color from a DXF \c MLEADER entity.
 *
 * \return color.
 */
int
dxf_mleader_get_color
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
        if (mleader->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->color);
}


/*!
 * \brief Set the \c color for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_color
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int color
                /*!< the \c color to be set for the entity. */
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
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c MLEADER entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_mleader_get_paperspace
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
        if (mleader->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_paperspace
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
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
        mleader->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c MLEADER
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_mleader_get_graphics_data_size
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
        if (mleader->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_graphics_data_size
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
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
        mleader->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c MLEADER entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mleader_get_shadow_mode
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
        if (mleader->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_shadow_mode
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
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
        mleader->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c MLEADER entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_mleader_get_binary_graphics_data
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
        if (mleader->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) mleader->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_binary_graphics_data
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
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
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c MLEADER entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleader_get_dictionary_owner_soft
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
        if (mleader->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_dictionary_owner_soft
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
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
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c MLEADER entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleader_get_object_owner_soft
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
        if (mleader->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_object_owner_soft
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
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
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_mleader_get_material
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
        if (mleader->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_material
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
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
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c MLEADER entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mleader_get_dictionary_owner_hard
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
        if (mleader->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_dictionary_owner_hard
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
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
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c lineweight from a DXF \c MLEADER entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mleader_get_lineweight
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_lineweight
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
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
        mleader->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c MLEADER entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_mleader_get_plot_style_name
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
        if (mleader->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_plot_style_name
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
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
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c color_value from a DXF \c MLEADER entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mleader_get_color_value
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_color_value
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
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
        mleader->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c color_name from a DXF \c MLEADER entity.
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_color_name
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
        if (mleader->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_color_name
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
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
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c transparency from a DXF \c MLEADER entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mleader_get_transparency
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_transparency
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
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
        mleader->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_content_scale of a DXF \c MLEADER entity.
 *
 * \return the \c block_content_scale.
 */
double
dxf_mleader_get_block_content_scale
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_content_scale);
}


/*!
 * \brief Set the  \c block_content_scale of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_content_scale
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double block_content_scale
                /*!< the \c block_content_scale of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
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
        mleader->block_content_scale = block_content_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c dogleg_length of a DXF \c MLEADER entity.
 *
 * \return the \c dogleg_length.
 */
double
dxf_mleader_get_dogleg_length
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->dogleg_length);
}


/*!
 * \brief Set the  \c dogleg_length of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_dogleg_length
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double dogleg_length
                /*!< the \c dogleg_length of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
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
        mleader->dogleg_length = dogleg_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c arrowhead_size of a DXF \c MLEADER entity.
 *
 * \return the \c arrowhead_size.
 */
double
dxf_mleader_get_arrowhead_size
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->arrowhead_size);
}


/*!
 * \brief Set the  \c arrowhead_size of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_arrowhead_size
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double arrowhead_size
                /*!< the \c arrowhead_size of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
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
        mleader->arrowhead_size = arrowhead_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_content_rotation of a DXF \c MLEADER entity.
 *
 * \return the \c block_content_rotation.
 */
double
dxf_mleader_get_block_content_rotation
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_content_rotation);
}


/*!
 * \brief Set the  \c block_content_rotation of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_content_rotation
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double block_content_rotation
                /*!< the \c block_content_rotation of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
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
        mleader->block_content_rotation = block_content_rotation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_attribute_width of a DXF \c MLEADER entity.
 *
 * \return the \c block_attribute_width.
 */
double
dxf_mleader_get_block_attribute_width
(
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_attribute_width);
}


/*!
 * \brief Set the  \c block_attribute_width of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_attribute_width
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        double block_attribute_width
                /*!< the \c block_attribute_width of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
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
        mleader->block_attribute_width = block_attribute_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c property_override_flag from a DXF \c MLEADER entity.
 *
 * \return \c property_override_flag.
 */
int32_t
dxf_mleader_get_property_override_flag
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->property_override_flag);
}


/*!
 * \brief Set the \c property_override_flag for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_property_override_flag
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t property_override_flag
                /*!< the \c property_override_flag to be set for the
                 * entity. */
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
        mleader->property_override_flag = property_override_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c leader_line_color from a DXF \c MLEADER entity.
 *
 * \return \c leader_line_color.
 */
int32_t
dxf_mleader_get_leader_line_color
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->leader_line_color);
}


/*!
 * \brief Set the \c leader_line_color for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_leader_line_color
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t leader_line_color
                /*!< the \c leader_line_color to be set for the
                 * entity. */
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
        mleader->leader_line_color = leader_line_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_color from a DXF \c MLEADER entity.
 *
 * \return \c text_color.
 */
int32_t
dxf_mleader_get_text_color
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_color);
}


/*!
 * \brief Set the \c text_color for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_color
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t text_color
                /*!< the \c text_color to be set for the
                 * entity. */
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
        mleader->text_color = text_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_content_color from a DXF \c MLEADER entity.
 *
 * \return \c block_content_color.
 */
int32_t
dxf_mleader_get_block_content_color
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_content_color);
}


/*!
 * \brief Set the \c block_content_color for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_content_color
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t block_content_color
                /*!< the \c block_content_color to be set for the
                 * entity. */
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
        mleader->block_content_color = block_content_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c arrowhead_index from a DXF \c MLEADER entity.
 *
 * \return \c arrowhead_index.
 */
int32_t
dxf_mleader_get_arrowhead_index
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->arrowhead_index);
}


/*!
 * \brief Set the \c arrowhead_index for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_arrowhead_index
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t arrowhead_index
                /*!< the \c arrowhead_index to be set for the
                 * entity. */
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
        mleader->arrowhead_index = arrowhead_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_right_attachment_type from a DXF \c MLEADER
 * entity.
 *
 * \return \c text_right_attachment_type.
 */
int32_t
dxf_mleader_get_text_right_attachment_type
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_right_attachment_type);
}


/*!
 * \brief Set the \c text_right_attachment_type for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_right_attachment_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int32_t text_right_attachment_type
                /*!< the \c text_right_attachment_type to be set for the
                 * entity. */
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
        mleader->text_right_attachment_type = text_right_attachment_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c leader_linetype_style from a DXF \c MLEADER entity.
 *
 * \return \c leader_linetype_style.
 */
int16_t
dxf_mleader_get_leader_linetype_style
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->leader_linetype_style);
}


/*!
 * \brief Set the \c leader_linetype_style for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_leader_linetype_style
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t leader_linetype_style
                /*!< the \c leader_linetype_style to be set for the
                 * entity. */
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
        mleader->leader_linetype_style = leader_linetype_style;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c leader_line_weight from a DXF \c MLEADER entity.
 *
 * \return \c leader_line_weight.
 */
int16_t
dxf_mleader_get_leader_line_weight
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->leader_line_weight);
}


/*!
 * \brief Set the \c leader_line_weight for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_leader_line_weight
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t leader_line_weight
                /*!< the \c leader_line_weight to be set for the
                 * entity. */
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
        mleader->leader_line_weight = leader_line_weight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c content_type from a DXF \c MLEADER entity.
 *
 * \return \c content_type.
 */
int16_t
dxf_mleader_get_content_type
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->content_type);
}


/*!
 * \brief Set the \c content_type for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_content_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t content_type
                /*!< the \c content_type to be set for the
                 * entity. */
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
        mleader->content_type = content_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_left_attachment_type from a DXF \c MLEADER
 * entity.
 *
 * \return \c text_left_attachment_type.
 */
int16_t
dxf_mleader_get_text_left_attachment_type
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_left_attachment_type);
}


/*!
 * \brief Set the \c text_left_attachment_type for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_left_attachment_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t text_left_attachment_type
                /*!< the \c text_left_attachment_type to be set for the
                 * entity. */
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
        mleader->text_left_attachment_type = text_left_attachment_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_angle_type from a DXF \c MLEADER
 * entity.
 *
 * \return \c text_angle_type.
 */
int16_t
dxf_mleader_get_text_angle_type
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_angle_type);
}


/*!
 * \brief Set the \c text_angle_type for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_angle_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t text_angle_type
                /*!< the \c text_angle_type to be set for the
                 * entity. */
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
        mleader->text_angle_type = text_angle_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_alignment_type from a DXF \c MLEADER
 * entity.
 *
 * \return \c text_alignment_type.
 */
int16_t
dxf_mleader_get_text_alignment_type
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_alignment_type);
}


/*!
 * \brief Set the \c text_alignment_type for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_alignment_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t text_alignment_type
                /*!< the \c text_alignment_type to be set for the
                 * entity. */
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
        mleader->text_alignment_type = text_alignment_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_content_connection_type from a DXF \c MLEADER
 * entity.
 *
 * \return \c block_content_connection_type.
 */
int16_t
dxf_mleader_get_block_content_connection_type
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_content_connection_type);
}


/*!
 * \brief Set the \c block_content_connection_type for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_content_connection_type
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t block_content_connection_type
                /*!< the \c block_content_connection_type to be set for the
                 * entity. */
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
        mleader->block_content_connection_type = block_content_connection_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_attribute_index from a DXF \c MLEADER
 * entity.
 *
 * \return \c block_attribute_index.
 */
int16_t
dxf_mleader_get_block_attribute_index
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->block_attribute_index);
}


/*!
 * \brief Set the \c block_attribute_index for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_attribute_index
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t block_attribute_index
                /*!< the \c block_attribute_index to be set for the
                 * entity. */
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
        mleader->block_attribute_index = block_attribute_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_align_in_IPE from a DXF \c MLEADER entity.
 *
 * \return \c text_align_in_IPE.
 */
int16_t
dxf_mleader_get_text_align_in_IPE
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_align_in_IPE);
}


/*!
 * \brief Set the \c text_align_in_IPE for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_align_in_IPE
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t text_align_in_IPE
                /*!< the \c text_align_in_IPE to be set for the
                 * entity. */
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
        mleader->text_align_in_IPE = text_align_in_IPE;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_attachment_point from a DXF \c MLEADER entity.
 *
 * \return \c text_attachment_point.
 */
int16_t
dxf_mleader_get_text_attachment_point
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_attachment_point);
}


/*!
 * \brief Set the \c text_attachment_point for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_attachment_point
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t text_attachment_point
                /*!< the \c text_attachment_point to be set for the
                 * entity. */
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
        mleader->text_attachment_point = text_attachment_point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_attachment_direction from a DXF \c MLEADER
 * entity.
 *
 * \return \c text_attachment_direction.
 */
int16_t
dxf_mleader_get_text_attachment_direction
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
        if (mleader->text_attachment_direction < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->text_attachment_direction > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_attachment_direction);
}


/*!
 * \brief Set the \c text_attachment_direction for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_attachment_direction
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t text_attachment_direction
                /*!< the \c text_attachment_direction to be set for the
                 * entity. */
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
        if (text_attachment_direction < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (text_attachment_direction > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->text_attachment_direction = text_attachment_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c bottom_text_attachment_direction from a DXF
 * \c MLEADER entity.
 *
 * \return \c bottom_text_attachment_direction.
 */
int16_t
dxf_mleader_get_bottom_text_attachment_direction
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->bottom_text_attachment_direction);
}


/*!
 * \brief Set the \c bottom_text_attachment_direction for a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_bottom_text_attachment_direction
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t bottom_text_attachment_direction
                /*!< the \c bottom_text_attachment_direction to be set
                 * for the entity. */
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
        mleader->bottom_text_attachment_direction = bottom_text_attachment_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c top_text_attachment_direction from a DXF \c MLEADER
 * entity.
 *
 * \return \c top_text_attachment_direction.
 */
int16_t
dxf_mleader_get_top_text_attachment_direction
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->top_text_attachment_direction);
}


/*!
 * \brief Set the \c top_text_attachment_direction for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_top_text_attachment_direction
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int16_t top_text_attachment_direction
                /*!< the \c top_text_attachment_direction to be set for
                 * the entity. */
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
        mleader->top_text_attachment_direction = top_text_attachment_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c enable_landing from a DXF \c MLEADER
 * entity.
 *
 * \return \c enable_landing (boolean).
 */
int
dxf_mleader_get_enable_landing
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
        if (mleader->enable_landing < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->enable_landing > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->enable_landing);
}


/*!
 * \brief Set the \c enable_landing for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_enable_landing
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int enable_landing
                /*!< the \c enable_landing to be set for the entity. */
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
        if (enable_landing < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (enable_landing > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->enable_landing = enable_landing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c enable_dogleg from a DXF \c MLEADER entity.
 *
 * \return \c enable_dogleg (boolean).
 */
int
dxf_mleader_get_enable_dogleg
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
        if (mleader->enable_dogleg < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->enable_dogleg > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->enable_dogleg);
}


/*!
 * \brief Set the \c enable_dogleg for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_enable_dogleg
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int enable_dogleg
                /*!< the \c enable_dogleg to be set for the entity. */
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
        if (enable_dogleg < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (enable_dogleg > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->enable_dogleg = enable_dogleg;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c enable_frame_text from a DXF \c MLEADER entity.
 *
 * \return \c enable_frame_text (boolean).
 */
int
dxf_mleader_get_enable_frame_text
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
        if (mleader->enable_frame_text < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->enable_frame_text > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->enable_frame_text);
}


/*!
 * \brief Set the \c enable_frame_text for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_enable_frame_text
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int enable_frame_text
                /*!< the \c enable_frame_text to be set for the entity. */
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
        if (enable_frame_text < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (enable_frame_text > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->enable_frame_text = enable_frame_text;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c enable_annotation_scale from a DXF \c MLEADER
 * entity.
 *
 * \return \c enable_annotation_scale (boolean).
 */
int
dxf_mleader_get_enable_annotation_scale
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
        if (mleader->enable_annotation_scale < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->enable_annotation_scale > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->enable_annotation_scale);
}


/*!
 * \brief Set the \c enable_annotation_scale for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_enable_annotation_scale
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int enable_annotation_scale
                /*!< the \c enable_annotation_scale to be set for the
                 * entity. */
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
        if (enable_annotation_scale < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (enable_annotation_scale > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->enable_annotation_scale = enable_annotation_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_direction_negative from a DXF \c MLEADER
 * entity.
 *
 * \return \c text_direction_negative (boolean).
 */
int
dxf_mleader_get_text_direction_negative
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
        if (mleader->text_direction_negative < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mleader->text_direction_negative > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader->text_direction_negative);
}


/*!
 * \brief Set the \c text_direction_negative for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_direction_negative
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        int text_direction_negative
                /*!< the \c text_direction_negative to be set for the
                 * entity. */
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
        if (text_direction_negative < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (text_direction_negative > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mleader->text_direction_negative = text_direction_negative;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_attribute_text_string from a DXF \c MLEADER
 * entity.
 *
 * \return \c block_attribute_text_string when successful, \c NULL when
 * an error occurred.
 */
char *
dxf_mleader_get_block_attribute_text_string
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
        if (mleader->block_attribute_text_string ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->block_attribute_text_string));
}


/*!
 * \brief Set the \c block_attribute_text_string for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an error
 * occurred.
 */
DxfMLeader *
dxf_mleader_set_block_attribute_text_string
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *block_attribute_text_string
                /*!< a pointer to a string containing the
                 * \c block_attribute_text_string to be set for the
                 * entity. */
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
        if (block_attribute_text_string == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->block_attribute_text_string = strdup (block_attribute_text_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_attribute_id from a DXF \c MLEADER entity.
 *
 * \return \c block_attribute_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_block_attribute_id
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
        if (mleader->block_attribute_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->block_attribute_id));
}


/*!
 * \brief Set the \c block_attribute_id for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_attribute_id
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *block_attribute_id
                /*!< a pointer to a string containing the
                 * \c block_attribute_id to be set for the entity. */
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
        if (block_attribute_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->block_attribute_id = strdup (block_attribute_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c leader_style_id from a DXF \c MLEADER entity.
 *
 * \return \c leader_style_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_leader_style_id
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
        if (mleader->leader_style_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->leader_style_id));
}


/*!
 * \brief Set the \c leader_style_id for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_leader_style_id
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *leader_style_id
                /*!< a pointer to a string containing the
                 * \c leader_style_id to be set for the entity. */
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
        if (leader_style_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->leader_style_id = strdup (leader_style_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c leader_linetype_id from a DXF \c MLEADER entity.
 *
 * \return \c leader_linetype_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_leader_linetype_id
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
        if (mleader->leader_linetype_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->leader_linetype_id));
}


/*!
 * \brief Set the \c leader_linetype_id for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_leader_linetype_id
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *leader_linetype_id
                /*!< a pointer to a string containing the
                 * \c leader_linetype_id to be set for the entity. */
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
        if (leader_linetype_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->leader_linetype_id = strdup (leader_linetype_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c arrowhead_id from a DXF \c MLEADER entity.
 *
 * \return \c arrowhead_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_arrowhead_id
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
        if (mleader->arrowhead_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->arrowhead_id));
}


/*!
 * \brief Set the \c arrowhead_id for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_arrowhead_id
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *arrowhead_id
                /*!< a pointer to a string containing the
                 * \c arrowhead_id to be set for the entity. */
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
        if (arrowhead_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->arrowhead_id = strdup (arrowhead_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c text_style_id from a DXF \c MLEADER entity.
 *
 * \return \c text_style_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_text_style_id
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
        if (mleader->text_style_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->text_style_id));
}


/*!
 * \brief Set the \c text_style_id for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_text_style_id
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *text_style_id
                /*!< a pointer to a string containing the
                 * \c text_style_id to be set for the entity. */
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
        if (text_style_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->text_style_id = strdup (text_style_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c block_content_id from a DXF \c MLEADER entity.
 *
 * \return \c block_content_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_block_content_id
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
        if (mleader->block_content_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->block_content_id));
}


/*!
 * \brief Set the \c block_content_id for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_block_content_id
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *block_content_id
                /*!< a pointer to a string containing the
                 * \c block_content_id to be set for the entity. */
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
        if (block_content_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->block_content_id = strdup (block_content_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the \c arrow_head_id from a DXF \c MLEADER entity.
 *
 * \return \c arrow_head_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleader_get_arrow_head_id
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
        if (mleader->arrow_head_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleader->arrow_head_id));
}


/*!
 * \brief Set the \c arrow_head_id for a DXF \c MLEADER entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_arrow_head_id
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        char *arrow_head_id
                /*!< a pointer to a string containing the
                 * \c arrow_head_id to be set for the entity. */
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
        if (arrow_head_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->arrow_head_id = strdup (arrow_head_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the next \c MLEADER entity from a DXF
 * \c MLEADER entity.
 *
 * \return pointer to the next \c MLEADER entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeader *
dxf_mleader_get_next
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
        if (mleader->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeader *) mleader->next);
}


/*!
 * \brief Set the pointer to the next \c MLEADER for a DXF \c MLEADER
 * entity.
 *
 * \return a pointer to \c mleader when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeader *
dxf_mleader_set_next
(
        DxfMLeader *mleader,
                /*!< a pointer to a DXF \c MLEADER entity. */
        DxfMLeader *next
                /*!< a pointer to the next \c MLEADER for the entity. */
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
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleader->next = (struct DxfMLeader *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Get the pointer to the last \c MLEADER entity from a linked
 * list of DXF \c MLEADER entities.
 *
 * \return pointer to the last \c MLEADER entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeader *
dxf_mleader_get_last
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
        if (mleader->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMLeader *) mleader);
        }
        DxfMLeader *iter = (DxfMLeader *) mleader->next;
        while (iter->next != NULL)
        {
                iter = (DxfMLeader *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeader *) iter);
}


/*!
 * \brief Allocate memory for a DxfMLeaderContextData object for a DXF
 * \c MLEADER entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMLeaderContextData *data = NULL;
        size_t size;

        size = sizeof (DxfMLeaderContextData);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((data = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                data = NULL;
        }
        else
        {
                memset (data, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Allocate memory and initialize data fields in a
 * DxfMLeaderContextData object for a DXF \c MLEADER entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_init
(
        DxfMLeaderContextData *data
                /*!< a pointer to the DxfMLeaderContextData object for
                 * the DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                data = dxf_mleader_context_data_new ();
        }
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p0 = dxf_point_new ();
        data->p0 = dxf_point_init (data->p0);
        data->vertex = dxf_point_new ();
        data->vertex = dxf_point_init (data->vertex);
        data->p1 = dxf_point_new ();
        data->p1 = dxf_point_init (data->p1);
        data->p2 = dxf_point_new ();
        data->p2 = dxf_point_init (data->p2);
        data->p3 = dxf_point_new ();
        data->p3 = dxf_point_init (data->p3);
        data->p4 = dxf_point_new ();
        data->p4 = dxf_point_init (data->p4);
        data->p5 = dxf_point_new ();
        data->p5 = dxf_point_init (data->p5);
        data->block_content_scale = 1.0;
        data->content_scale = 1.0;
        data->text_height = 1.0;
        data->text_rotation = 0.0;
        data->text_width = 1.0;
        data->text_height2 = 1.0;
        data->text_line_spacing_factor = 1.0;
        data->block_content_rotation = 0.0;
        data->block_transformation_matrix = 1.0;
        data->text_color = 0;
        data->break_point_index = 0;
        data->text_background_color = 0;
        data->text_background_transparency = 0;
        data->block_content_color = 0;
        data->MLeader_plane_origin_point = 0.0;
        data->MLeader_plane_X_axis_direction = 0.0;
        data->MLeader_plane_Y_axis_direction = 0.0;
        data->arrowhead_size = 0.0;
        data->text_background_scale_factor = 1.0;
        data->text_column_width = 0.0;
        data->text_column_gutter_width = 0.0;
        data->text_column_height = 0.0;
        data->landing_gap = 0.0;
        data->text_line_spacing_style = 0;
        data->text_attachment = 0;
        data->text_flow_direction = 0;
        data->text_column_type = 0;
        data->hasMtext = 0;
        data->is_text_background_color_on = 0;
        data->is_text_background_fill_on = 0;
        data->use_text_auto_height = 0;
        data->text_column_flow_reversed = 0;
        data->text_use_word_break = 0;
        data->has_block = 0;
        data->MLeader_plane_normal_reversed = 0;
        data->default_text_contents = strdup ("");
        data->type_style_id = strdup ("");
        data->block_content_id = strdup ("");
        data->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Free the allocated memory for a DxfMLeaderContextData object
 * of a DXF \c MLEADER entity and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mleader_context_data_free
(
        DxfMLeaderContextData *data
                /*!< a pointer to the memory occupied by the
                 * DxfMLeaderContextData object of a DXF \c MLEADER
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_point_free_list (data->p0);
        dxf_point_free_list (data->vertex);
        dxf_point_free_list (data->p1);
        dxf_point_free_list (data->p2);
        dxf_point_free_list (data->p3);
        dxf_point_free_list (data->p4);
        dxf_point_free_list (data->p5);
        free (data->default_text_contents);
        free (data->type_style_id);
        free (data->block_content_id);
        free (data);
        data = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of \c
 * DxfMLeaderContextData objects of a DXF \c MLEADER entity and all
 * their data fields.
 */
void
dxf_mleader_context_data_free_list
(
        DxfMLeaderContextData *datas
                /*!< a pointer to the single linked list of
                 * \c DxfMLeaderContextData objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (datas == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (datas != NULL)
        {
                DxfMLeaderContextData *iter = (DxfMLeaderContextData *) datas->next;
                dxf_mleader_context_data_free (datas);
                datas = (DxfMLeaderContextData *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c p0 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p0.
 */
DxfPoint *
dxf_mleader_context_data_get_p0
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p0);
}


/*!
 * \brief Set the \c p0 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_p0
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a \c DxfMLeaderContextData object. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
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
        data->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the X-value \c x0 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x0.
 */
double
dxf_mleader_context_data_get_x0
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p0->x0);
}


/*!
 * \brief Set the X-value of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_x0
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double x0
                /*!< the X-value of the \c x0 of a DxfMLeaderContextData
                 * object of a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Y-value \c y0 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y0.
 */
double
dxf_mleader_context_data_get_y0
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p0->y0);
}


/*!
 * \brief Set the Y-value of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_y0
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double y0
                /*!< the Y-value of the \c y0 of a DxfMLeaderContextData
                 * object of a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Z-value \c z0 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z0.
 */
double
dxf_mleader_context_data_get_z0
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p0->z0);
}


/*!
 * \brief Set the Z-value \c z0 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_z0
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double z0
                /*!< the Z-value of the \c z0 of a DxfMLeaderContextData
                 * object of a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c vertex of a \c DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return \c vertex.
 */
DxfPoint *
dxf_mleader_context_data_get_vertex
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->vertex);
}


/*!
 * \brief Set the \c vertex of a \c DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_vertex
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a \c DxfMLeaderContextData object. */
        DxfPoint *vertex
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->vertex = vertex;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the X-value \c vertex_x0 of a DxfMLeaderContextData object
 * of a DXF \c MLEADER entity.
 *
 * \return the X-value \c vertex_x0.
 */
double
dxf_mleader_context_data_get_vertex_x0
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->vertex->x0);
}


/*!
 * \brief Set the X-value of the \c vertex_x0 of a DxfMLeaderContextData
 * object of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_vertex_x0
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double vertex_x0
                /*!< the X-value of the \c vertex_x0 of a
                 * DxfMLeaderContextData object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->vertex->x0 = vertex_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Y-value \c vertex_y0 of a DxfMLeaderContextData object
 * of a DXF \c MLEADER entity.
 *
 * \return the Y-value \c vertex_y0.
 */
double
dxf_mleader_context_data_get_vertex_y0
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->vertex->y0);
}


/*!
 * \brief Set the Y-value of the \c vertex_y0 of a DxfMLeaderContextData
 * object of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_vertex_y0
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double vertex_y0
                /*!< the Y-value of the \c vertex_y0 of a
                 * DxfMLeaderContextData object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->vertex->y0 = vertex_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Z-value \c vertex_z0 of a DxfMLeaderContextData object
 * of a DXF \c MLEADER entity.
 *
 * \return the Z-value \c vertex_z0.
 */
double
dxf_mleader_context_data_get_vertex_z0
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->vertex->z0);
}


/*!
 * \brief Set the Z-value of the \c vertex_z0 of a DxfMLeaderContextData
 * object of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_vertex_z0
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double vertex_z0
                /*!< the Z-value of the \c vertex_z0 of a
                 * DxfMLeaderContextData object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->vertex->z0 = vertex_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c p1 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p1.
 */
DxfPoint *
dxf_mleader_context_data_get_p1
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p1);
}


/*!
 * \brief Set the \c p1 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_p1
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a \c DxfMLeaderContextData object. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the X-value \c x1 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x1.
 */
double
dxf_mleader_context_data_get_x1
(
        DxfMLeaderContextData *data
                /*!< a pointer to a \c DxfMLeaderContextData object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p1->x0);
}


/*!
 * \brief Set the X-value \c x1 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_x1
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double x1
                /*!< the X-value of the \c x1 of a DxfMLeaderContextData
                 * object of a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/* EOF*/
