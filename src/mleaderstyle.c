/*!
 * \file mleaderstyle.c
 *
 * \author Copyright (C) 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * \brief Read data from a DXF file into an \c MLEADERSTYLE entity.
 *
 * The last line read from file contained the string "MLEADERSTYLE". \n
 * Now follows some data for the \c MLEADERSTYLE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c mleaderstyle.
 *
 * \return a pointer to \c mleaderstyle.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfMLeaderstyle *mleaderstyle
                /*!< DXF mleaderstyle entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfBinaryGraphicsData *iter310 = NULL;
        int iter330;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mleaderstyle = dxf_mleaderstyle_init (mleaderstyle);
        }
        iter310 = (DxfBinaryGraphicsData *) mleaderstyle->binary_graphics_data;
        iter330 = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &mleaderstyle->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleaderstyle->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleaderstyle->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleaderstyle->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleaderstyle->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleaderstyle->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleaderstyle->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleaderstyle->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleaderstyle->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleaderstyle->graphics_data_size);
                }
                else if (strcmp (temp_string, "93") == 0)
                {
                        /* Now follows a string containing the
                         * text color. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleaderstyle->text_color);
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleaderstyle->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleaderstyle->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) iter310->next);
                        iter310 = (DxfBinaryGraphicsData *) iter310->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleaderstyle->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleaderstyle->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleaderstyle->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleaderstyle->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleaderstyle->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleaderstyle->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &mleaderstyle->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleaderstyle->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &mleaderstyle->transparency);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (mleaderstyle->linetype, "") == 0)
        {
                mleaderstyle->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (mleaderstyle->layer, "") == 0)
        {
                mleaderstyle->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Write DXF output to a file for a DXF \c MLEADESTYLE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mleaderstyle_write
(
        DxfFile *fp,
                /*!< a DXF \c FILE pointer to an output file (or device). */
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("MLEADERSTYLE");

/*! \todo Add code here. */

        /* Clean up. */
        free (dxf_entity_name);
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
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


/*!
 * \brief Set the \c align_space for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_align_space
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double align_space
                /*!< the \c align_space to be set for the entity. */
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
        mleaderstyle->align_space = align_space;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c block_content_scale_x from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c block_content_scale_x.
 */
double
dxf_mleaderstyle_get_block_content_scale_x
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
        return (mleaderstyle->block_content_scale_x);
}


/*!
 * \brief Set the \c block_content_scale_x for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_block_content_scale_x
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double block_content_scale_x
                /*!< the \c block_content_scale_x to be set for the
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
        mleaderstyle->block_content_scale_x = block_content_scale_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c block_content_scale_y from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c block_content_scale_y.
 */
double
dxf_mleaderstyle_get_block_content_scale_y
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
        return (mleaderstyle->block_content_scale_y);
}


/*!
 * \brief Set the \c block_content_scale_y for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_block_content_scale_y
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double block_content_scale_y
                /*!< the \c block_content_scale_y to be set for the
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
        mleaderstyle->block_content_scale_y = block_content_scale_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c block_content_scale_z from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c block_content_scale_z.
 */
double
dxf_mleaderstyle_get_block_content_scale_z
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
        return (mleaderstyle->block_content_scale_z);
}


/*!
 * \brief Set the \c block_content_scale_z for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_block_content_scale_z
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double block_content_scale_z
                /*!< the \c block_content_scale_z to be set for the
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
        mleaderstyle->block_content_scale_z = block_content_scale_z;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c leader_line_weight from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c leader_line_weight.
 */
int32_t
dxf_mleaderstyle_get_leader_line_weight
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
        return (mleaderstyle->leader_line_weight);
}


/*!
 * \brief Set the \c leader_line_weight for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_leader_line_weight
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int32_t leader_line_weight
                /*!< the \c leader_line_weight to be set for the entity. */
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
        mleaderstyle->leader_line_weight = leader_line_weight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c maxleader_segment_points from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c maxleader_segment_points.
 */
int32_t
dxf_mleaderstyle_get_maxleader_segment_points
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
        return (mleaderstyle->maxleader_segment_points);
}


/*!
 * \brief Set the \c maxleader_segment_points for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_maxleader_segment_points
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int32_t maxleader_segment_points
                /*!< the \c maxleader_segment_points to be set for the
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
        mleaderstyle->maxleader_segment_points = maxleader_segment_points;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c text_color from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c text_color.
 */
int32_t
dxf_mleaderstyle_get_text_color
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
        return (mleaderstyle->text_color);
}


/*!
 * \brief Set the \c text_color for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_text_color
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int32_t text_color
                /*!< the \c text_color to be set for the entity. */
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
        mleaderstyle->text_color = text_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c block_content_color from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c block_content_color.
 */
int32_t
dxf_mleaderstyle_get_block_content_color
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
        return (mleaderstyle->block_content_color);
}


/*!
 * \brief Set the \c block_content_color for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_block_content_color
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int32_t block_content_color
                /*!< the \c block_content_color to be set for the entity. */
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
        mleaderstyle->block_content_color = block_content_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c block_content_rotation from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c block_content_rotation.
 */
double
dxf_mleaderstyle_get_block_content_rotation
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
        return (mleaderstyle->block_content_rotation);
}


/*!
 * \brief Set the \c block_content_rotation for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_block_content_rotation
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double block_content_rotation
                /*!< the \c block_content_rotation to be set for the
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
        mleaderstyle->block_content_rotation = block_content_rotation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c scale from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c scale.
 */
double
dxf_mleaderstyle_get_scale
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
        return (mleaderstyle->scale);
}


/*!
 * \brief Set the \c scale for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_scale
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double scale
                /*!< the \c scale to be set for the entity. */
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
        mleaderstyle->scale = scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c break_gap_size from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c break_gap_size.
 */
double
dxf_mleaderstyle_get_break_gap_size
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
        return (mleaderstyle->break_gap_size);
}


/*!
 * \brief Set the \c break_gap_size for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_break_gap_size
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        double break_gap_size
                /*!< the \c break_gap_size to be set for the entity. */
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
        mleaderstyle->break_gap_size = break_gap_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c content_type from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c content_type.
 */
int16_t
dxf_mleaderstyle_get_content_type
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
        return (mleaderstyle->content_type);
}


/*!
 * \brief Set the \c content_type for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_content_type
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t content_type
                /*!< the \c content_type to be set for the entity. */
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
        mleaderstyle->content_type = content_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c draw_mleader_order_type from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c draw_mleader_order_type.
 */
int16_t
dxf_mleaderstyle_get_draw_mleader_order_type
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
        return (mleaderstyle->draw_mleader_order_type);
}


/*!
 * \brief Set the \c draw_mleader_order_type for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_draw_mleader_order_type
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t draw_mleader_order_type
                /*!< the \c draw_mleader_order_type to be set for the
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
        mleaderstyle->draw_mleader_order_type = draw_mleader_order_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c draw_leader_order_type from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c draw_leader_order_type.
 */
int16_t
dxf_mleaderstyle_get_draw_leader_order_type
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
        return (mleaderstyle->draw_leader_order_type);
}


/*!
 * \brief Set the \c draw_leader_order_type for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_draw_leader_order_type
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t draw_leader_order_type
                /*!< the \c draw_leader_order_type to be set for the
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
        mleaderstyle->draw_leader_order_type = draw_leader_order_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c leader_line_color from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c leader_line_color.
 */
int16_t
dxf_mleaderstyle_get_leader_line_color
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
        return (mleaderstyle->leader_line_color);
}


/*!
 * \brief Set the \c leader_line_color for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_leader_line_color
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t leader_line_color
                /*!< the \c leader_line_color to be set for the entity. */
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
        mleaderstyle->leader_line_color = leader_line_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c text_left_attachment_type from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c text_left_attachment_type.
 */
int16_t
dxf_mleaderstyle_get_text_left_attachment_type
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
        return (mleaderstyle->text_left_attachment_type);
}


/*!
 * \brief Set the \c text_left_attachment_type for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_text_left_attachment_type
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t text_left_attachment_type
                /*!< the \c text_left_attachment_type to be set for the
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
        mleaderstyle->text_left_attachment_type = text_left_attachment_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c text_right_attachment_type from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c text_right_attachment_type.
 */
int16_t
dxf_mleaderstyle_get_text_right_attachment_type
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
        return (mleaderstyle->text_right_attachment_type);
}


/*!
 * \brief Set the \c text_right_attachment_type for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_text_right_attachment_type
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t text_right_attachment_type
                /*!< the \c text_right_attachment_type to be set for the
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
        mleaderstyle->text_right_attachment_type = text_right_attachment_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c text_angle_type from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c text_angle_type.
 */
int16_t
dxf_mleaderstyle_get_text_angle_type
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
        return (mleaderstyle->text_angle_type);
}


/*!
 * \brief Set the \c text_angle_type for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_text_angle_type
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t text_angle_type
                /*!< the \c text_angle_type to be set for the entity. */
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
        mleaderstyle->text_angle_type = text_angle_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c text_alignment_type from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c text_alignment_type.
 */
int16_t
dxf_mleaderstyle_get_text_alignment_type
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
        return (mleaderstyle->text_alignment_type);
}


/*!
 * \brief Set the \c text_alignment_type for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_text_alignment_type
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t text_alignment_type
                /*!< the \c text_alignment_type to be set for the entity. */
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
        mleaderstyle->text_alignment_type = text_alignment_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c block_content_connection_type from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c block_content_connection_type.
 */
int16_t
dxf_mleaderstyle_get_block_content_connection_type
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
        return (mleaderstyle->block_content_connection_type);
}


/*!
 * \brief Set the \c block_content_connection_type for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_block_content_connection_type
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t block_content_connection_type
                /*!< the \c block_content_connection_type to be set for
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
        mleaderstyle->block_content_connection_type = block_content_connection_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c text_attachment_direction from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c text_attachment_direction.
 */
int16_t
dxf_mleaderstyle_get_text_attachment_direction
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
        return (mleaderstyle->text_attachment_direction);
}


/*!
 * \brief Set the \c text_attachment_direction for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_text_attachment_direction
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t text_attachment_direction
                /*!< the \c text_attachment_direction to be set for the
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
        mleaderstyle->text_attachment_direction = text_attachment_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c bottom_text_attachment_direction from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c bottom_text_attachment_direction.
 */
int16_t
dxf_mleaderstyle_get_bottom_text_attachment_direction
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
        return (mleaderstyle->bottom_text_attachment_direction);
}


/*!
 * \brief Set the \c bottom_text_attachment_direction for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_bottom_text_attachment_direction
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t bottom_text_attachment_direction
                /*!< the \c bottom_text_attachment_direction to be set
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
        mleaderstyle->bottom_text_attachment_direction = bottom_text_attachment_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c top_text_attachment_direction from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c top_text_attachment_direction.
 */
int16_t
dxf_mleaderstyle_get_top_text_attachment_direction
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
        return (mleaderstyle->top_text_attachment_direction);
}


/*!
 * \brief Set the \c top_text_attachment_direction for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_top_text_attachment_direction
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int16_t top_text_attachment_direction
                /*!< the \c top_text_attachment_direction to be set for
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
        mleaderstyle->top_text_attachment_direction = top_text_attachment_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c enable_landing from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c enable_landing.
 */
int
dxf_mleaderstyle_get_enable_landing
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
        return (mleaderstyle->enable_landing);
}


/*!
 * \brief Set the \c enable_landing for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_enable_landing
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int enable_landing
                /*!< the \c enable_landing to be set for the entity. */
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
        mleaderstyle->enable_landing = enable_landing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c enable_dogleg from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c enable_dogleg.
 */
int
dxf_mleaderstyle_get_enable_dogleg
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
        return (mleaderstyle->enable_dogleg);
}


/*!
 * \brief Set the \c enable_dogleg for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_enable_dogleg
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int enable_dogleg
                /*!< the \c enable_dogleg to be set for the entity. */
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
        mleaderstyle->enable_dogleg = enable_dogleg;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c enable_frame_text from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c enable_frame_text.
 */
int
dxf_mleaderstyle_get_enable_frame_text
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
        return (mleaderstyle->enable_frame_text);
}


/*!
 * \brief Set the \c enable_frame_text for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_enable_frame_text
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int enable_frame_text
                /*!< the \c enable_frame_text to be set for the entity. */
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
        mleaderstyle->enable_frame_text = enable_frame_text;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c enable_block_content_scale from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c enable_block_content_scale.
 */
int
dxf_mleaderstyle_get_enable_block_content_scale
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
        return (mleaderstyle->enable_block_content_scale);
}


/*!
 * \brief Set the \c enable_block_content_scale for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_enable_block_content_scale
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int enable_block_content_scale
                /*!< the \c enable_block_content_scale to be set for the
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
        mleaderstyle->enable_block_content_scale = enable_block_content_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c enable_block_content_rotation from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c enable_block_content_rotation.
 */
int
dxf_mleaderstyle_get_enable_block_content_rotation
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
        return (mleaderstyle->enable_block_content_rotation);
}


/*!
 * \brief Set the \c enable_block_content_rotation for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_enable_block_content_rotation
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int enable_block_content_rotation
                /*!< the \c enable_block_content_rotation to be set for
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
        mleaderstyle->enable_block_content_rotation = enable_block_content_rotation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c overwrite_property_value from a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return \c overwrite_property_value.
 */
int
dxf_mleaderstyle_get_overwrite_property_value
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
        return (mleaderstyle->overwrite_property_value);
}


/*!
 * \brief Set the \c overwrite_property_value for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_overwrite_property_value
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int overwrite_property_value
                /*!< the \c overwrite_property_value to be set for the
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
        mleaderstyle->overwrite_property_value = overwrite_property_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c is_annotative from a DXF \c MLEADERSTYLE entity.
 *
 * \return \c is_annotative.
 */
int
dxf_mleaderstyle_get_is_annotative
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
        return (mleaderstyle->is_annotative);
}


/*!
 * \brief Set the \c is_annotative for a DXF \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_is_annotative
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int is_annotative
                /*!< the \c is_annotative to be set for the entity. */
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
        mleaderstyle->is_annotative = is_annotative;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c text_align_always_left from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c text_align_always_left.
 */
int
dxf_mleaderstyle_get_text_align_always_left
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
        return (mleaderstyle->text_align_always_left);
}


/*!
 * \brief Set the \c text_align_always_left for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_text_align_always_left
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        int text_align_always_left
                /*!< the \c text_align_always_left to be set for the
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
        mleaderstyle->text_align_always_left = text_align_always_left;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c default_mtext_contents from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c default_mtext_contents when successful, \c NULL when an
 * error occurred.
 */
char *
dxf_mleaderstyle_get_default_mtext_contents
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
        if (mleaderstyle->default_mtext_contents ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->default_mtext_contents));
}


/*!
 * \brief Set the \c default_mtext_contents for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_default_mtext_contents
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *default_mtext_contents
                /*!< a pointer to a string containing the
                 * \c default_mtext_contents to be set for the entity. */
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
        if (default_mtext_contents == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->default_mtext_contents = strdup (default_mtext_contents);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c leader_linetype_id from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c leader_linetype_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleaderstyle_get_leader_linetype_id
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
        if (mleaderstyle->leader_linetype_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->leader_linetype_id));
}


/*!
 * \brief Set the \c leader_linetype_id for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_leader_linetype_id
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *leader_linetype_id
                /*!< a pointer to a string containing the
                 * \c leader_linetype_id to be set for the entity. */
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
        if (leader_linetype_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->leader_linetype_id = strdup (leader_linetype_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c arrow_head_id from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c arrow_head_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleaderstyle_get_arrow_head_id
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
        if (mleaderstyle->arrow_head_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->arrow_head_id));
}


/*!
 * \brief Set the \c arrow_head_id for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_arrow_head_id
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *arrow_head_id
                /*!< a pointer to a string containing the
                 * \c arrow_head_id to be set for the entity. */
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
        if (arrow_head_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->arrow_head_id = strdup (arrow_head_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c mtext_style_id from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c mtext_style_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleaderstyle_get_mtext_style_id
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
        if (mleaderstyle->mtext_style_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->mtext_style_id));
}


/*!
 * \brief Set the \c mtext_style_id for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_mtext_style_id
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *mtext_style_id
                /*!< a pointer to a string containing the
                 * \c mtext_style_id to be set for the entity. */
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
        if (mtext_style_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->mtext_style_id = strdup (mtext_style_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the \c block_content_id from a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return \c block_content_id when successful, \c NULL when an error
 * occurred.
 */
char *
dxf_mleaderstyle_get_block_content_id
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
        if (mleaderstyle->block_content_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mleaderstyle->block_content_id));
}


/*!
 * \brief Set the \c block_content_id for a DXF \c MLEADERSTYLE
 * entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_block_content_id
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        char *block_content_id
                /*!< a pointer to a string containing the
                 * \c block_content_id to be set for the entity. */
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
        if (block_content_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->block_content_id = strdup (block_content_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the pointer to the next \c MLEADERSTYLE entity from a DXF
 * \c MLEADER entity.
 *
 * \return pointer to the next \c MLEADERSTYLE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_get_next
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
        if (mleaderstyle->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeaderstyle *) mleaderstyle->next);
}


/*!
 * \brief Set the pointer to the next \c MLEADERSTYLE for a DXF
 * \c MLEADERSTYLE entity.
 *
 * \return a pointer to \c mleaderstyle when successful, or \c NULL when
 * an error occurred.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_set_next
(
        DxfMLeaderstyle *mleaderstyle,
                /*!< a pointer to a DXF \c MLEADERSTYLE entity. */
        DxfMLeaderstyle *next
                /*!< a pointer to the next \c MLEADERSTYLE for the entity. */
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
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->next = (struct DxfMLeaderstyle *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Get the pointer to the last \c MLEADERSTYLE entity from a
 * linked list of DXF \c MLEADERSTYLE entities.
 *
 * \return pointer to the last \c MLEADERSTYLE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_get_last
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
        if (mleaderstyle->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMLeaderstyle *) mleaderstyle);
        }
        DxfMLeaderstyle *iter = (DxfMLeaderstyle *) mleaderstyle->next;
        while (iter->next != NULL)
        {
                iter = (DxfMLeaderstyle *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeaderstyle *) iter);
}


/* EOF*/
