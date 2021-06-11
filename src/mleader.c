/*!
 * \file mleader.c
 *
 * \author Copyright (C) 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * \brief Read data from a DXF file into an \c MLEADER entity.
 *
 * The last line read from file contained the string "MLEADER". \n
 * Now follows some data for the \c MLEADER, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c mleader.
 *
 * \return a pointer to \c mleader.
 */
DxfMLeader *
dxf_mleader_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfMLeader *mleader
                /*!< DXF mleader entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfBinaryGraphicsData *iter310 = NULL;
        int iter92;
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
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mleader = dxf_mleader_init (mleader);
        }
        iter310 = (DxfBinaryGraphicsData *) mleader->binary_graphics_data;
        iter92 = 0;
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
                        fscanf (fp->fp, "%x\n", (uint *) &mleader->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * Block content scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleader->block_content_scale);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleader->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleader->thickness);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * Dogleg length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleader->dogleg_length);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * Arrowhead size. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleader->arrowhead_size);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * Block content rotation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleader->block_content_rotation);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the
                         * Block attribute width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleader->block_attribute_width);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mleader->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->paperspace);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * Property override flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->property_override_flag);
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing the
                         * Leader line color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->leader_line_color);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        if (iter92 == 0)
                        {
                                /* Now follows a string containing the
                                 * graphics data size value. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%d\n", &mleader->graphics_data_size);
                        }
                        if (iter92 == 1)
                        {
                                /* Now follows a string containing the
                                 * text color. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%d\n", &mleader->text_color);
                        }
                        iter92++;
                }
                else if (strcmp (temp_string, "93") == 0)
                {
                        /* Now follows a string containing the
                         * Block content color. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->block_content_color);
                }
                else if (strcmp (temp_string, "94") == 0)
                {
                        /* Now follows a string containing the
                         * Arrowhead index. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->arrowhead_index);
                }
                else if (strcmp (temp_string, "95") == 0)
                {
                        /* Now follows a string containing the
                         * Text right attachment type value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->text_right_attachment_type);
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->graphics_data_size);
                }
                else if (strcmp (temp_string, "170") == 0)
                {
                        /* Now follows a string containing the
                         * Leader linetype style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->leader_linetype_style);
                }
                else if (strcmp (temp_string, "171") == 0)
                {
                        /* Now follows a string containing the
                         * Leader line weight. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->leader_line_weight);
                }
                else if (strcmp (temp_string, "172") == 0)
                {
                        /* Now follows a string containing the
                         * Content type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->content_type);
                }
                else if (strcmp (temp_string, "173") == 0)
                {
                        /* Now follows a string containing the
                         * Text left attachment type value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->text_left_attachment_type);
                }
                else if (strcmp (temp_string, "174") == 0)
                {
                        /* Now follows a string containing the
                         * Text angle type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->text_angle_type);
                }
                else if (strcmp (temp_string, "175") == 0)
                {
                        /* Now follows a string containing the
                         * Text alignment type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->text_alignment_type);
                }
                else if (strcmp (temp_string, "176") == 0)
                {
                        /* Now follows a string containing the
                         * Block content connection type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->block_content_connection_type);
                }
                else if (strcmp (temp_string, "177") == 0)
                {
                        /* Now follows a string containing the
                         * Block attribute index. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->block_attribute_index);
                }
                else if (strcmp (temp_string, "178") == 0)
                {
                        /* Now follows a string containing the
                         * Text align in IPE. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->text_align_in_IPE);
                }
                else if (strcmp (temp_string, "179") == 0)
                {
                        /* Now follows a string containing the
                         * Text attachment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->text_attachment_point);
                }
                else if (strcmp (temp_string, "271") == 0)
                {
                        /* Now follows a string containing the
                         * Text attachment direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->text_attachment_direction);
                }
                else if (strcmp (temp_string, "272") == 0)
                {
                        /* Now follows a string containing the
                         * Bottom text attachment direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->bottom_text_attachment_direction);
                }
                else if (strcmp (temp_string, "273") == 0)
                {
                        /* Now follows a string containing the
                         * Top text attachment direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->top_text_attachment_direction);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->shadow_mode);
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the
                         * Enable landing value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->enable_landing);
                }
                else if (strcmp (temp_string, "291") == 0)
                {
                        /* Now follows a string containing the
                         * Enable dogleg value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->enable_dogleg);
                }
                else if (strcmp (temp_string, "292") == 0)
                {
                        /* Now follows a string containing the
                         * Enable frame text value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->enable_frame_text);
                }
                else if (strcmp (temp_string, "293") == 0)
                {
                        /* Now follows a string containing the
                         * Enable annotation scale value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->enable_annotation_scale);
                }
                else if (strcmp (temp_string, "294") == 0)
                {
                        /* Now follows a string containing the
                         * Text direction negative value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mleader->text_direction_negative);
                }
                else if (strcmp (temp_string, "302") == 0)
                {
                        /* Now follows a string containing a
                         * Block attribute text string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->block_attribute_text_string);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->object_owner_soft);
                        }
                        if (iter330 == 2)
                        {
                                /* Now follows a string containing a
                                 * Block attribute ID. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->block_attribute_id);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a
                         * Leader style ID. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->leader_style_id);
                }
                else if (strcmp (temp_string, "341") == 0)
                {
                        /* Now follows a string containing a
                         * Leader linetype ID. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->leader_linetype_id);
                }
                else if (strcmp (temp_string, "342") == 0)
                {
                        /* Now follows a string containing a
                         * Arrowhead ID. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->arrowhead_id);
                }
                else if (strcmp (temp_string, "343") == 0)
                {
                        /* Now follows a string containing a
                         * Text style ID. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->text_style_id);
                }
                else if (strcmp (temp_string, "344") == 0)
                {
                        /* Now follows a string containing a
                         * Block content ID. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->block_content_id);
                }
                else if (strcmp (temp_string, "345") == 0)
                {
                        /* Now follows a string containing a
                         * Arrow head ID. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->arrow_head_id);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mleader->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &mleader->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mleader->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &mleader->transparency);
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
        if (strcmp (mleader->linetype, "") == 0)
        {
                mleader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (mleader->layer, "") == 0)
        {
                mleader->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleader);
}


/*!
 * \brief Write DXF output to a file for a DXF \c MLEADE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mleader_write
(
        DxfFile *fp,
                /*!< a DXF \c FILE pointer to an output file (or device). */
        DxfMLeader *mleader
                /*!< a pointer to a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("MLEADER");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (mleader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((strcmp (mleader->layer, "") == 0) || (mleader->layer == NULL))
        {
                fprintf (stderr,
                  (_("Warning in %s () invalid layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, mleader->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                mleader->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (mleader->linetype == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () invalid linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, mleader->id_code);
                fprintf (stderr,
                  (_("\t%s linetype is set to %s\n")),
                  dxf_entity_name, DXF_DEFAULT_LINETYPE);
                mleader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (mleader->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", mleader->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (mleader->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", mleader->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (mleader->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", mleader->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (mleader->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", mleader->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (mleader->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", mleader->layer);
        if (strcmp (mleader->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", mleader->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (mleader->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", mleader->material);
        }
        if (mleader->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", mleader->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", mleader->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (mleader->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", mleader->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (mleader->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", mleader->thickness);
        }
        if (mleader->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", mleader->linetype_scale);
        }
        if (mleader->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", mleader->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", mleader->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", mleader->graphics_data_size);
#endif
                if (mleader->binary_graphics_data != NULL)
                {
                        DxfBinaryGraphicsData *iter;
                        iter = (DxfBinaryGraphicsData *) mleader->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryGraphicsData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", mleader->color_value);
                fprintf (fp->fp, "430\n%s\n", mleader->color_name);
                fprintf (fp->fp, "440\n%ld\n", mleader->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", mleader->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", mleader->shadow_mode);
        }
        /* Clean up. */
        free (dxf_entity_name);
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
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
        data->has_Mtext = 0;
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


/*!
 * \brief Get the Y-value \c y1 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y1.
 */
double
dxf_mleader_context_data_get_y1
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
        return (data->p1->y0);
}


/*!
 * \brief Set the Y-value \c y1 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_y1
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double y1
                /*!< the Y-value of the \c y1 of a DxfMLeaderContextData
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
        data->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Z-value \c z1 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z1.
 */
double
dxf_mleader_context_data_get_z1
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
        return (data->p1->z0);
}


/*!
 * \brief Set the Z-value \c z1 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_z1
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double z1
                /*!< the Z-value of the \c z1 of a DxfMLeaderContextData
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
        data->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c p2 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p2.
 */
DxfPoint *
dxf_mleader_context_data_get_p2
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
        if (data->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p2);
}


/*!
 * \brief Set the \c p2 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_p2
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a \c DxfMLeaderContextData object. */
        DxfPoint *p2
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
        if (p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p2 = p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the X-value \c x2 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x2.
 */
double
dxf_mleader_context_data_get_x2
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
        if (data->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p2->x0);
}


/*!
 * \brief Set the X-value \c x2 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_x2
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double x2
                /*!< the X-value of the \c x2 of a DxfMLeaderContextData
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
        if (data->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Y-value \c y2 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y2.
 */
double
dxf_mleader_context_data_get_y2
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
        if (data->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p2->y0);
}


/*!
 * \brief Set the Y-value \c y2 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_y2
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double y2
                /*!< the Y-value of the \c y2 of a DxfMLeaderContextData
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
        if (data->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Z-value \c z2 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z2.
 */
double
dxf_mleader_context_data_get_z2
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
        if (data->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p2->z0);
}


/*!
 * \brief Set the Z-value \c z2 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_z2
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double z2
                /*!< the Z-value of the \c z2 of a DxfMLeaderContextData
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
        if (data->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c p3 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p3.
 */
DxfPoint *
dxf_mleader_context_data_get_p3
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
        if (data->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p3);
}


/*!
 * \brief Set the \c p3 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_p3
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a \c DxfMLeaderContextData object. */
        DxfPoint *p3
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
        if (p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p3 = p3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the X-value \c x3 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x3.
 */
double
dxf_mleader_context_data_get_x3
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
        if (data->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p3->x0);
}


/*!
 * \brief Set the X-value \c x3 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_x3
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double x3
                /*!< the X-value of the \c x3 of a DxfMLeaderContextData
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
        if (data->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p3->x0 = x3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Y-value \c y3 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y3.
 */
double
dxf_mleader_context_data_get_y3
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
        if (data->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p3->y0);
}


/*!
 * \brief Set the Y-value \c y3 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_y3
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double y3
                /*!< the Y-value of the \c y3 of a DxfMLeaderContextData
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
        if (data->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p3->y0 = y3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Z-value \c z3 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z3.
 */
double
dxf_mleader_context_data_get_z3
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
        if (data->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p3->z0);
}


/*!
 * \brief Set the Z-value \c z3 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_z3
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double z3
                /*!< the Z-value of the \c z3 of a DxfMLeaderContextData
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
        if (data->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p3->z0 = z3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c p4 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p4.
 */
DxfPoint *
dxf_mleader_context_data_get_p4
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
        if (data->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p4);
}


/*!
 * \brief Set the \c p4 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_p4
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a \c DxfMLeaderContextData object. */
        DxfPoint *p4
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
        if (p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p4 = p4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the X-value \c x4 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x4.
 */
double
dxf_mleader_context_data_get_x4
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
        if (data->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p4->x0);
}


/*!
 * \brief Set the X-value \c x4 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_x4
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double x4
                /*!< the X-value of the \c x4 of a DxfMLeaderContextData
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
        if (data->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p4->x0 = x4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Y-value \c y4 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y4.
 */
double
dxf_mleader_context_data_get_y4
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
        if (data->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p4->y0);
}


/*!
 * \brief Set the Y-value \c y4 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_y4
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double y4
                /*!< the Y-value of the \c y4 of a DxfMLeaderContextData
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
        if (data->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p4->y0 = y4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Z-value \c z4 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z4.
 */
double
dxf_mleader_context_data_get_z4
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
        if (data->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p4->z0);
}


/*!
 * \brief Set the Z-value \c z4 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_z4
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double z4
                /*!< the Z-value of the \c z4 of a DxfMLeaderContextData
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
        if (data->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p4->z0 = z4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c p5 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p5.
 */
DxfPoint *
dxf_mleader_context_data_get_p5
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
        if (data->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p5);
}


/*!
 * \brief Set the \c p5 of a \c DxfMLeaderContextData object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_p5
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a \c DxfMLeaderContextData object. */
        DxfPoint *p5
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
        if (p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p5 = p5;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the X-value \c x5 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x5.
 */
double
dxf_mleader_context_data_get_x5
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
        if (data->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p5->x0);
}


/*!
 * \brief Set the X-value \c x5 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_x5
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double x5
                /*!< the X-value of the \c x5 of a DxfMLeaderContextData
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
        if (data->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p5->x0 = x5;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Y-value \c y5 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y5.
 */
double
dxf_mleader_context_data_get_y5
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
        if (data->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p5->y0);
}


/*!
 * \brief Set the Y-value \c y5 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_y5
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double y5
                /*!< the Y-value of the \c y5 of a DxfMLeaderContextData
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
        if (data->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p5->y0 = y5;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the Z-value \c z5 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z5.
 */
double
dxf_mleader_context_data_get_z5
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
        if (data->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->p5->z0);
}


/*!
 * \brief Set the Z-value \c z5 of a DxfMLeaderContextData object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_z5
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DxfMLeaderContextData object. */
        double z5
                /*!< the Z-value of the \c z5 of a DxfMLeaderContextData
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
        if (data->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->p5->z0 = z5;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c block_content_scale of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c block_content_scale.
 */
double
dxf_mleader_context_data_get_block_content_scale
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->block_content_scale);
}


/*!
 * \brief Set the \c block_content_scale of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_block_content_scale
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double block_content_scale
                /*!< the \c block_content_scale. */
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
        data->block_content_scale = block_content_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c content_scale of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return the \c content_scale.
 */
double
dxf_mleader_context_data_get_content_scale
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->content_scale);
}


/*!
 * \brief Set the \c content_scale of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_content_scale
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double content_scale
                /*!< the \c content_scale of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->content_scale = content_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_height of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return the \c text_height.
 */
double
dxf_mleader_context_data_get_text_height
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_height);
}


/*!
 * \brief Set the \c text_height of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_height
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_height
                /*!< the \c text_height of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_height = text_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_rotation of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return the \c text_rotation.
 */
double
dxf_mleader_context_data_get_text_rotation
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_rotation);
}


/*!
 * \brief Set the \c text_rotation of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_rotation
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_rotation
                /*!< the \c text_rotation of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_rotation = text_rotation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_width of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return the \c text_width.
 */
double
dxf_mleader_context_data_get_text_width
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_width);
}


/*!
 * \brief Set the \c text_width of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_width
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_width
                /*!< the \c text_width of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_width = text_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_height2 of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return the \c text_height2.
 */
double
dxf_mleader_context_data_get_text_height2
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_height2);
}


/*!
 * \brief Set the \c text_height2 of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_height2
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_height2
                /*!< the \c text_height2 of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_height2 = text_height2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_line_spacing_factor of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c text_line_spacing_factor.
 */
double
dxf_mleader_context_data_get_text_line_spacing_factor
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_line_spacing_factor);
}


/*!
 * \brief Set the \c text_line_spacing_factor of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_line_spacing_factor
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_line_spacing_factor
                /*!< the \c text_line_spacing_factor of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_line_spacing_factor = text_line_spacing_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c block_content_rotation of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c block_content_rotation.
 */
double
dxf_mleader_context_data_get_block_content_rotation
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->block_content_rotation);
}


/*!
 * \brief Set the \c block_content_rotation of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_block_content_rotation
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double block_content_rotation
                /*!< the \c block_content_rotation of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->block_content_rotation = block_content_rotation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c block_transformation_matrix of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c block_transformation_matrix.
 */
double
dxf_mleader_context_data_get_block_transformation_matrix
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->block_transformation_matrix);
}


/*!
 * \brief Set the \c block_transformation_matrix of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_block_transformation_matrix
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double block_transformation_matrix
                /*!< the \c block_transformation_matrix of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->block_transformation_matrix = block_transformation_matrix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_color of a DXF \c DxfMLeaderContextData object.
 *
 * \return \c text_color.
 */
int32_t
dxf_mleader_context_data_get_text_color
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_color);
}


/*!
 * \brief Set the \c text_color of a DXF \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_color
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int32_t text_color
                /*!< the \c text_color to be set for the
                 * object. */
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
                return (NULL);
        }
        data->text_color = text_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c break_point_index of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return \c break_point_index.
 */
int32_t
dxf_mleader_context_data_get_break_point_index
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->break_point_index);
}


/*!
 * \brief Set the \c break_point_index of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_break_point_index
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int32_t break_point_index
                /*!< the \c break_point_index to be set for the
                 * object. */
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
                return (NULL);
        }
        data->break_point_index = break_point_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_background_color of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c text_background_color.
 */
int32_t
dxf_mleader_context_data_get_text_background_color
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_background_color);
}


/*!
 * \brief Set the \c text_background_color of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_background_color
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int32_t text_background_color
                /*!< the \c text_background_color to be set for the
                 * object. */
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
                return (NULL);
        }
        data->text_background_color = text_background_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_background_transparency of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c text_background_transparency.
 */
int32_t
dxf_mleader_context_data_get_text_background_transparency
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_background_transparency);
}


/*!
 * \brief Set the \c text_background_transparency of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_background_transparency
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int32_t text_background_transparency
                /*!< the \c text_background_transparency to be set for
                 * the object. */
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
                return (NULL);
        }
        data->text_background_transparency = text_background_transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c block_content_color of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c block_content_color.
 */
int32_t
dxf_mleader_context_data_get_block_content_color
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->block_content_color);
}


/*!
 * \brief Set the \c block_content_color of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_block_content_color
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int32_t block_content_color
                /*!< the \c block_content_color to be set for the object. */
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
                return (NULL);
        }
        data->block_content_color = block_content_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c MLeader_plane_origin_point of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c MLeader_plane_origin_point.
 */
double
dxf_mleader_context_data_get_MLeader_plane_origin_point
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->MLeader_plane_origin_point);
}


/*!
 * \brief Set the \c MLeader_plane_origin_point of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_MLeader_plane_origin_point
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double MLeader_plane_origin_point
                /*!< the \c MLeader_plane_origin_point of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->MLeader_plane_origin_point = MLeader_plane_origin_point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c MLeader_plane_X_axis_direction of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c MLeader_plane_X_axis_direction.
 */
double
dxf_mleader_context_data_get_MLeader_plane_X_axis_direction
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->MLeader_plane_X_axis_direction);
}


/*!
 * \brief Set the \c MLeader_plane_X_axis_direction of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_MLeader_plane_X_axis_direction
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double MLeader_plane_X_axis_direction
                /*!< the \c MLeader_plane_X_axis_direction of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->MLeader_plane_X_axis_direction = MLeader_plane_X_axis_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c MLeader_plane_Y_axis_direction of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c MLeader_plane_Y_axis_direction.
 */
double
dxf_mleader_context_data_get_MLeader_plane_Y_axis_direction
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->MLeader_plane_Y_axis_direction);
}


/*!
 * \brief Set the \c MLeader_plane_Y_axis_direction of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_MLeader_plane_Y_axis_direction
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double MLeader_plane_Y_axis_direction
                /*!< the \c MLeader_plane_Y_axis_direction of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->MLeader_plane_Y_axis_direction = MLeader_plane_Y_axis_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c arrowhead_size of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return the \c arrowhead_size.
 */
double
dxf_mleader_context_data_get_arrowhead_size
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->arrowhead_size);
}


/*!
 * \brief Set the \c arrowhead_size of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_arrowhead_size
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double arrowhead_size
                /*!< the \c arrowhead_size of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->arrowhead_size = arrowhead_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_background_scale_factor of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c text_background_scale_factor.
 */
double
dxf_mleader_context_data_get_text_background_scale_factor
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_background_scale_factor);
}


/*!
 * \brief Set the \c text_background_scale_factor of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_background_scale_factor
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_background_scale_factor
                /*!< the \c text_background_scale_factor of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_background_scale_factor = text_background_scale_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_column_width of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return the \c text_column_width.
 */
double
dxf_mleader_context_data_get_text_column_width
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_column_width);
}


/*!
 * \brief Set the \c text_column_width of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_column_width
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_column_width
                /*!< the \c text_column_width of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_column_width = text_column_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_column_gutter_width of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c text_column_gutter_width.
 */
double
dxf_mleader_context_data_get_text_column_gutter_width
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_column_gutter_width);
}


/*!
 * \brief Set the \c text_column_gutter_width of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_column_gutter_width
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_column_gutter_width
                /*!< the \c text_column_gutter_width of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_column_gutter_width = text_column_gutter_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_column_gutter_width of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return the \c text_column_height.
 */
double
dxf_mleader_context_data_get_text_column_height
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_column_height);
}


/*!
 * \brief Set the \c text_column_height of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_column_height
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double text_column_height
                /*!< the \c text_column_height of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->text_column_height = text_column_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c landing_gap of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return the \c landing_gap.
 */
double
dxf_mleader_context_data_get_landing_gap
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->landing_gap);
}


/*!
 * \brief Set the \c landing_gap of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_landing_gap
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        double landing_gap
                /*!< the \c landing_gap of a DXF
                 * \c DxfMLeaderContextData object. */
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
        data->landing_gap = landing_gap;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_line_spacing_style of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c text_line_spacing_style.
 */
int16_t
dxf_mleader_context_data_get_text_line_spacing_style
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_line_spacing_style);
}


/*!
 * \brief Set the \c text_line_spacing_style of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_line_spacing_style
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int16_t text_line_spacing_style
                /*!< the \c text_line_spacing_style to be set for the
                 * object. */
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
                return (NULL);
        }
        data->text_line_spacing_style = text_line_spacing_style;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_attachment of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return \c text_attachment.
 */
int16_t
dxf_mleader_context_data_get_text_attachment
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_attachment);
}


/*!
 * \brief Set the \c text_attachment of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_attachment
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int16_t text_attachment
                /*!< the \c text_attachment to be set for the object. */
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
                return (NULL);
        }
        data->text_attachment = text_attachment;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_flow_direction of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c text_flow_direction.
 */
int16_t
dxf_mleader_context_data_get_text_flow_direction
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_flow_direction);
}


/*!
 * \brief Set the \c text_flow_direction of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_flow_direction
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int16_t text_flow_direction
                /*!< the \c text_flow_direction to be set for the object. */
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
                return (NULL);
        }
        data->text_flow_direction = text_flow_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_column_type of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return \c text_column_type.
 */
int16_t
dxf_mleader_context_data_get_text_column_type
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_column_type);
}


/*!
 * \brief Set the \c text_column_type of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_column_type
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int16_t text_column_type
                /*!< the \c text_column_type to be set for the object. */
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
                return (NULL);
        }
        data->text_column_type = text_column_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c has_Mtext of a DXF \c DxfMLeaderContextData object.
 *
 * \return \c has_Mtext.
 */
int
dxf_mleader_context_data_get_has_Mtext
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->has_Mtext);
}


/*!
 * \brief Set the \c has_Mtext of a DXF \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_has_Mtext
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int has_Mtext
                /*!< the \c has_Mtext to be set for the object. */
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
                return (NULL);
        }
        data->has_Mtext = has_Mtext;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c is_text_background_color_on of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c is_text_background_color_on.
 */
int
dxf_mleader_context_data_get_is_text_background_color_on
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->is_text_background_color_on);
}


/*!
 * \brief Set the \c is_text_background_color_on of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_is_text_background_color_on
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int is_text_background_color_on
                /*!< the \c is_text_background_color_on to be set for
                 * the object. */
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
                return (NULL);
        }
        data->is_text_background_color_on = is_text_background_color_on;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c is_text_background_fill_on of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c is_text_background_fill_on.
 */
int
dxf_mleader_context_data_get_is_text_background_fill_on
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->is_text_background_fill_on);
}


/*!
 * \brief Set the \c is_text_background_fill_on of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_is_text_background_fill_on
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int is_text_background_fill_on
                /*!< the \c is_text_background_fill_on to be set for
                 * the object. */
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
                return (NULL);
        }
        data->is_text_background_fill_on = is_text_background_fill_on;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c use_text_auto_height of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c use_text_auto_height.
 */
int
dxf_mleader_context_data_get_use_text_auto_height
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->use_text_auto_height);
}


/*!
 * \brief Set the \c use_text_auto_height of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_use_text_auto_height
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int use_text_auto_height
                /*!< the \c use_text_auto_height to be set for the
                 * object. */
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
                return (NULL);
        }
        data->use_text_auto_height = use_text_auto_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_column_flow_reversed of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c text_column_flow_reversed.
 */
int
dxf_mleader_context_data_get_text_column_flow_reversed
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_column_flow_reversed);
}


/*!
 * \brief Set the \c text_column_flow_reversed of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_column_flow_reversed
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int text_column_flow_reversed
                /*!< the \c text_column_flow_reversed to be set for the
                 * object. */
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
                return (NULL);
        }
        data->text_column_flow_reversed = text_column_flow_reversed;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c text_use_word_break of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c text_use_word_break.
 */
int
dxf_mleader_context_data_get_text_use_word_break
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->text_use_word_break);
}


/*!
 * \brief Set the \c text_use_word_break of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_text_use_word_break
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int text_use_word_break
                /*!< the \c text_use_word_break to be set for the
                 * object. */
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
                return (NULL);
        }
        data->text_use_word_break = text_use_word_break;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c has_block of a DXF \c DxfMLeaderContextData object.
 *
 * \return \c has_block.
 */
int
dxf_mleader_context_data_get_has_block
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->has_block);
}


/*!
 * \brief Set the \c has_block of a DXF \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_has_block
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int has_block
                /*!< the \c has_block to be set for the object. */
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
                return (NULL);
        }
        data->has_block = has_block;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c MLeader_plane_normal_reversed of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c MLeader_plane_normal_reversed.
 */
int
dxf_mleader_context_data_get_MLeader_plane_normal_reversed
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->MLeader_plane_normal_reversed);
}


/*!
 * \brief Set the \c MLeader_plane_normal_reversed of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_MLeader_plane_normal_reversed
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        int MLeader_plane_normal_reversed
                /*!< the \c MLeader_plane_normal_reversed to be set for
                 * the object. */
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
                return (NULL);
        }
        data->MLeader_plane_normal_reversed = MLeader_plane_normal_reversed;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c default_text_contents of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return \c default_text_contents.
 */
char *
dxf_mleader_context_data_get_default_text_contents
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->default_text_contents);
}


/*!
 * \brief Set the \c default_text_contents of a DXF
 * \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_default_text_contents
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        char *default_text_contents
                /*!< the \c default_text_contents to be set for the
                 * object. */
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
                return (NULL);
        }
        data->default_text_contents = default_text_contents;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c type_style_id of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return \c type_style_id.
 */
char *
dxf_mleader_context_data_get_type_style_id
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->type_style_id);
}


/*!
 * \brief Set the \c type_style_id of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_type_style_id
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        char *type_style_id
                /*!< the \c type_style_id to be set for the object. */
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
                return (NULL);
        }
        data->type_style_id = type_style_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the \c block_content_id of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return \c block_content_id.
 */
char *
dxf_mleader_context_data_get_block_content_id
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->block_content_id);
}


/*!
 * \brief Set the \c block_content_id of a DXF \c DxfMLeaderContextData
 * object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_block_content_id
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        char *block_content_id
                /*!< the \c block_content_id to be set for the object. */
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
                return (NULL);
        }
        data->block_content_id = block_content_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the pointer to the next \c DxfMLeaderContextData object
 * from a DXF \c DxfMLeaderContextData object.
 *
 * \return pointer to the next \c DxfMLeaderContextData object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_get_next
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
                return (NULL);
        }
        if (data->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeaderContextData *) data->next);
}


/*!
 * \brief Set the pointer to the next \c DxfMLeaderContextData object
 * for a DXF \c DxfMLeaderContextData object.
 *
 * \return a pointer to \c data when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_set_next
(
        DxfMLeaderContextData *data,
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
        DxfMLeaderContextData *next
                /*!< a pointer to the next \c DxfMLeaderContextData
                 * object for the DxfMLeaderContextData object. */
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
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        data->next = (struct DxfMLeaderContextData *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Get the pointer to the last \c DxfMLeaderContextData object
 * from a linked list of DXF \c DxfMLeaderContextData objects.
 *
 * \return pointer to the last \c DxfMLeaderContextData object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeaderContextData *
dxf_mleader_context_data_get_last
(
        DxfMLeaderContextData *data
                /*!< a pointer to a DXF \c DxfMLeaderContextData object. */
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
                return (NULL);
        }
        if (data->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMLeaderContextData *) data);
        }
        DxfMLeaderContextData *iter = (DxfMLeaderContextData *) data->next;
        while (iter->next != NULL)
        {
                iter = (DxfMLeaderContextData *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeaderContextData *) iter);
}


/*!
 * \brief Allocate memory for a \c DxfMLeaderLeaderNode object for a DXF
 * \c MLEADER entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMLeaderLeaderNode *node = NULL;
        size_t size;

        size = sizeof (DxfMLeaderLeaderNode);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((node = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                node = NULL;
        }
        else
        {
                memset (node, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Allocate memory and initialize data fields in a
 * \c DxfMLeaderLeaderNode object for a DXF \c MLEADER entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_init
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to the \c DxfMLeaderLeaderNode object for
                 * the DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                node = dxf_mleader_leader_node_new ();
        }
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p0 = dxf_point_new ();
        node->p0 = dxf_point_init (node->p0);
        node->p1 = dxf_point_new ();
        node->p1 = dxf_point_init (node->p1);
        node->p2 = dxf_point_new ();
        node->p2 = dxf_point_init (node->p2);
        node->p3 = dxf_point_new ();
        node->p3 = dxf_point_init (node->p3);
        node->dogleg_length = 0.0;
        node->leader_branch_index = 0;
        node->has_set_last_leader_line_point = 0;
        node->has_set_dogleg_vector = 0;
        node->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Free the allocated memory for a \c DxfMLeaderLeaderNode object
 * of a DXF \c MLEADER entity and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mleader_leader_node_free
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to the memory occupied by the
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_point_free_list (node->p0);
        dxf_point_free_list (node->p1);
        dxf_point_free_list (node->p2);
        dxf_point_free_list (node->p3);
        free (node);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of \c
 * DxfMLeaderLeaderNode objects of a DXF \c MLEADER entity and all
 * their data fields.
 */
void
dxf_mleader_leader_node_free_list
(
        DxfMLeaderLeaderNode *nodes
                /*!< a pointer to the single linked list of
                 * \c DxfMLeaderLeaderNode objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (nodes == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (nodes != NULL)
        {
                DxfMLeaderLeaderNode *iter = (DxfMLeaderLeaderNode *) nodes->next;
                dxf_mleader_leader_node_free (nodes);
                nodes = (DxfMLeaderLeaderNode *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c p0 of a \c DxfMLeaderLeaderNode object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p0.
 */
DxfPoint *
dxf_mleader_leader_node_get_p0
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p0);
}


/*!
 * \brief Set the \c p0 of a \c DxfMLeaderLeaderNode object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_p0
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
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
        node->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the X-value \c x0 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x0.
 */
double
dxf_mleader_leader_node_get_x0
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p0->x0);
}


/*!
 * \brief Set the X-value of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_x0
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double x0
                /*!< the X-value of the \c x0 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the Y-value \c y0 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y0.
 */
double
dxf_mleader_leader_node_get_y0
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p0->y0);
}


/*!
 * \brief Set the Y-value of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_y0
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double y0
                /*!< the Y-value of the \c y0 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the Z-value \c z0 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z0.
 */
double
dxf_mleader_leader_node_get_z0
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p0->z0);
}


/*!
 * \brief Set the Z-value of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_z0
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double z0
                /*!< the Z-value of the \c z0 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the \c p1 of a \c DxfMLeaderLeaderNode object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p1.
 */
DxfPoint *
dxf_mleader_leader_node_get_p1
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p1);
}


/*!
 * \brief Set the \c p1 of a \c DxfMLeaderLeaderNode object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_p1
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
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
        node->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the X-value \c x1 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x1.
 */
double
dxf_mleader_leader_node_get_x1
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p1->x0);
}


/*!
 * \brief Set the X-value \c x1 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_x1
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double x1
                /*!< the X-value of the \c x1 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the Y-value \c y1 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y1.
 */
double
dxf_mleader_leader_node_get_y1
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p1->y0);
}


/*!
 * \brief Set the Y-value \c y1 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_y1
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double y1
                /*!< the Y-value of the \c y1 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the Z-value \c z1 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z1.
 */
double
dxf_mleader_leader_node_get_z1
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p1->z0);
}


/*!
 * \brief Set the Z-value \c z1 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_z1
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double z1
                /*!< the Z-value of the \c z1 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the \c p2 of a \c DxfMLeaderLeaderNode object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p2.
 */
DxfPoint *
dxf_mleader_leader_node_get_p2
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p2);
}


/*!
 * \brief Set the \c p2 of a \c DxfMLeaderLeaderNode object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_p2
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        DxfPoint *p2
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p2 = p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the X-value \c x2 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x2.
 */
double
dxf_mleader_leader_node_get_x2
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p2->x0);
}


/*!
 * \brief Set the X-value \c x2 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_x2
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double x2
                /*!< the X-value of the \c x2 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the Y-value \c y2 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y2.
 */
double
dxf_mleader_leader_node_get_y2
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p2->y0);
}


/*!
 * \brief Set the Y-value \c y2 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_y2
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double y2
                /*!< the Y-value of the \c y2 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the Z-value \c z2 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z2.
 */
double
dxf_mleader_leader_node_get_z2
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p2->z0);
}


/*!
 * \brief Set the Z-value \c z2 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_z2
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double z2
                /*!< the Z-value of the \c z2 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the \c p3 of a \c DxfMLeaderLeaderNode object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p3.
 */
DxfPoint *
dxf_mleader_leader_node_get_p3
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p3);
}


/*!
 * \brief Set the \c p3 of a \c DxfMLeaderLeaderNode object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_p3
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        DxfPoint *p3
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p3 = p3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the X-value \c x3 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x3.
 */
double
dxf_mleader_leader_node_get_x3
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p3->x0);
}


/*!
 * \brief Set the X-value \c x3 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_x3
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double x3
                /*!< the X-value of the \c x3 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p3->x0 = x3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the Y-value \c y3 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y3.
 */
double
dxf_mleader_leader_node_get_y3
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p3->y0);
}


/*!
 * \brief Set the Y-value \c y3 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_y3
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double y3
                /*!< the Y-value of the \c y3 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p3->y0 = y3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the Z-value \c z3 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z3.
 */
double
dxf_mleader_leader_node_get_z3
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (node->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->p3->z0);
}


/*!
 * \brief Set the Z-value \c z3 of a \c DxfMLeaderLeaderNode object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_z3
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double z3
                /*!< the Z-value of the \c z3 of a
                 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->p3->z0 = z3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the \c dogleg_length of a \c DxfMLeaderLeaderNode object
 * of a DXF \c MLEADER entity.
 *
 * \return the \c dogleg_length.
 */
double
dxf_mleader_leader_node_get_dogleg_length
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->dogleg_length);
}


/*!
 * \brief Set the \c dogleg_length of a \c DxfMLeaderLeaderNode object
 * of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_dogleg_length
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        double dogleg_length
                /*!< the \c dogleg_length of a \c DxfMLeaderLeaderNode
                 * object of a DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->dogleg_length = dogleg_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the \c leader_branch_index of a DXF
 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER entity.
 *
 * \return \c leader_branch_index.
 */
int32_t
dxf_mleader_leader_node_get_leader_branch_index
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->leader_branch_index);
}


/*!
 * \brief Set the \c leader_branch_index of a DXF
 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_context_data_set_leader_branch_index
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        int32_t leader_branch_index
                /*!< the \c leader_branch_index to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->leader_branch_index = leader_branch_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the \c has_set_last_leader_line_point of a DXF
 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER entity.
 *
 * \return \c has_set_last_leader_line_point.
 */
int
dxf_mleader_leader_node_get_has_set_last_leader_line_point
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->has_set_last_leader_line_point);
}


/*!
 * \brief Set the \c has_set_last_leader_line_point of a DXF
 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_context_data_set_has_set_last_leader_line_point
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        int has_set_last_leader_line_point
                /*!< the \c has_set_last_leader_line_point to be set
                 * for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->has_set_last_leader_line_point = has_set_last_leader_line_point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the \c has_set_dogleg_vector of a DXF
 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER entity.
 *
 * \return \c has_set_dogleg_vector.
 */
int
dxf_mleader_leader_node_get_has_set_dogleg_vector
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node->has_set_dogleg_vector);
}


/*!
 * \brief Set the \c has_set_dogleg_vector of a DXF
 * \c DxfMLeaderLeaderNode object of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_context_data_set_has_set_dogleg_vector
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a \c DxfMLeaderLeaderNode object. */
        int has_set_dogleg_vector
                /*!< the \c has_set_dogleg_vector to be set for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        node->has_set_dogleg_vector = has_set_dogleg_vector;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the pointer to the next \c DxfMLeaderLeaderNode object
 * from a DXF \c DxfMLeaderLeaderNode object.
 *
 * \return pointer to the next \c DxfMLeaderLeaderNode object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_get_next
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a DXF \c DxfMLeaderLeaderNode object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeaderLeaderNode *) node->next);
}


/*!
 * \brief Set the pointer to the next \c DxfMLeaderLeaderNode object
 * for a DXF \c DxfMLeaderLeaderNode object.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_set_next
(
        DxfMLeaderLeaderNode *node,
                /*!< a pointer to a DXF \c DxfMLeaderLeaderNode object. */
        DxfMLeaderLeaderNode *next
                /*!< a pointer to the next \c DxfMLeaderLeaderNode
                 * object for the DxfMLeaderLeaderNode object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
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
        node->next = (struct DxfMLeaderLeaderNode *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (node);
}


/*!
 * \brief Get the pointer to the last \c DxfMLeaderLeaderNode object
 * from a linked list of DXF \c DxfMLeaderLeaderNode objects.
 *
 * \return pointer to the last \c DxfMLeaderLeaderNode object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeaderLeaderNode *
dxf_mleader_leader_node_get_last
(
        DxfMLeaderLeaderNode *node
                /*!< a pointer to a DXF \c DxfMLeaderLeaderNode object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (node == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (node->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMLeaderLeaderNode *) node);
        }
        DxfMLeaderLeaderNode *iter = (DxfMLeaderLeaderNode *) node->next;
        while (iter->next != NULL)
        {
                iter = (DxfMLeaderLeaderNode *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeaderLeaderNode *) iter);
}


/*!
 * \brief Allocate memory for a \c DxfMLeaderLeaderLine object for a DXF
 * \c MLEADER entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMLeaderLeaderLine *line = NULL;
        size_t size;

        size = sizeof (DxfMLeaderLeaderLine);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((line = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                line = NULL;
        }
        else
        {
                memset (line, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Allocate memory and initialize data fields in a
 * \c DxfMLeaderLeaderLine object for a DXF \c MLEADER entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_init
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to the \c DxfMLeaderLeaderLine object for
                 * the DXF \c MLEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                line = dxf_mleader_leader_line_new ();
        }
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p0 = dxf_point_new ();
        line->p0 = dxf_point_init (line->p0);
        line->p1 = dxf_point_new ();
        line->p1 = dxf_point_init (line->p1);
        line->p2 = dxf_point_new ();
        line->p2 = dxf_point_init (line->p2);
        line->break_point_index = 0;
        line->leader_line_index = 0;
        line->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Free the allocated memory for a \c DxfMLeaderLeaderLine object
 * of a DXF \c MLEADER entity and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mleader_leader_line_free
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to the memory occupied by the
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_point_free_list (line->p0);
        dxf_point_free_list (line->p1);
        dxf_point_free_list (line->p2);
        free (line);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of \c
 * DxfMLeaderLeaderLine objects of a DXF \c MLEADER entity and all
 * their data fields.
 */
void
dxf_mleader_leader_line_free_list
(
        DxfMLeaderLeaderLine *lines
                /*!< a pointer to the single linked list of
                 * \c DxfMLeaderLeaderLine objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (lines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (lines != NULL)
        {
                DxfMLeaderLeaderLine *iter = (DxfMLeaderLeaderLine *) lines->next;
                dxf_mleader_leader_line_free (lines);
                lines = (DxfMLeaderLeaderLine *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c p0 of a \c DxfMLeaderLeaderLine object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p0.
 */
DxfPoint *
dxf_mleader_leader_line_get_p0
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p0);
}


/*!
 * \brief Set the \c p0 of a \c DxfMLeaderLeaderLine object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_p0
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
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
        line->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the X-value \c x0 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x0.
 */
double
dxf_mleader_leader_line_get_x0
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p0->x0);
}


/*!
 * \brief Set the X-value \c x0 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_x0
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double x0
                /*!< the X-value of the \c x0 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Y-value \c y0 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y0.
 */
double
dxf_mleader_leader_line_get_y0
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p0->y0);
}


/*!
 * \brief Set the Y-value \c y0 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_y0
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double y0
                /*!< the Y-value of the \c y0 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Z-value \c z0 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the Z-value \c z0.
 */
double
dxf_mleader_leader_line_get_z0
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p0->z0);
}


/*!
 * \brief Set the Z-value \c z0 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_z0
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double z0
                /*!< the Z-value of the \c z0 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c p1 of a \c DxfMLeaderLeaderLine object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p1.
 */
DxfPoint *
dxf_mleader_leader_line_get_p1
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p1);
}


/*!
 * \brief Set the \c p1 of a \c DxfMLeaderLeaderLine object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_p1
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
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
        line->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the X-value \c x1 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x1.
 */
double
dxf_mleader_leader_line_get_x1
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p1->x0);
}


/*!
 * \brief Set the X-value \c x1 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_x1
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double x1
                /*!< the X-value of the \c x1 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Y-value \c y1 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y1.
 */
double
dxf_mleader_leader_line_get_y1
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p1->y0);
}


/*!
 * \brief Set the Y-value \c y1 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_y1
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double y1
                /*!< the Y-value of the \c y1 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Z-value \c z1 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c z1.
 */
double
dxf_mleader_leader_line_get_z1
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p1->z0);
}


/*!
 * \brief Set the Z-value \c z1 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_z1
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double z1
                /*!< the Z-value of the \c z1 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c p2 of a \c DxfMLeaderLeaderLine object of a DXF
 * \c MLEADER entity.
 *
 * \return \c p2.
 */
DxfPoint *
dxf_mleader_leader_line_get_p2
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object of a
                 * DXF \c MLEADER entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p2);
}


/*!
 * \brief Set the \c p2 of a \c DxfMLeaderLeaderLine object of a DXF
 * \c MLEADER entity.
 *
 * \return a pointer to \c node when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_p2
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        DxfPoint *p2
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p2 = p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the X-value \c x2 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the X-value \c x2.
 */
double
dxf_mleader_leader_line_get_x2
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p2->x0);
}


/*!
 * \brief Set the X-value \c x2 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_x2
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double x2
                /*!< the X-value of the \c x2 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Y-value \c y2 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c y2.
 */
double
dxf_mleader_leader_line_get_y2
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p2->y0);
}


/*!
 * \brief Set the Y-value \c y2 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_y2
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double y2
                /*!< the Y-value of the \c y2 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Z-value \c z2 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return the Y-value \c z2.
 */
double
dxf_mleader_leader_line_get_z2
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p2->z0);
}


/*!
 * \brief Set the Z-value \c z2 of a \c DxfMLeaderLeaderLine object of a
 * DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_z2
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        double z2
                /*!< the Z-value of the \c z2 of a
                 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c break_point_index of a DXF
 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER entity.
 *
 * \return \c break_point_index.
 */
int32_t
dxf_mleader_leader_line_get_break_point_index
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->break_point_index);
}


/*!
 * \brief Set the \c break_point_index of a DXF
 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_break_point_index
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        int32_t break_point_index
                /*!< the \c leader_branch_index to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->break_point_index = break_point_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c leader_line_index of a DXF
 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER entity.
 *
 * \return \c leader_line_index.
 */
int32_t
dxf_mleader_leader_line_get_leader_line_index
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->leader_line_index);
}


/*!
 * \brief Set the \c leader_line_index of a DXF
 * \c DxfMLeaderLeaderLine object of a DXF \c MLEADER entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_leader_line_index
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a \c DxfMLeaderLeaderLine object. */
        int32_t leader_line_index
                /*!< the \c leader_line_index to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->leader_line_index = leader_line_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the next \c DxfMLeaderLeaderLine object
 * from a DXF \c DxfMLeaderLeaderLine object.
 *
 * \return pointer to the next \c DxfMLeaderLeaderLine object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_get_next
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a DXF \c DxfMLeaderLeaderLine object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeaderLeaderLine *) line->next);
}


/*!
 * \brief Set the pointer to the next \c DxfMLeaderLeaderLine object
 * for a DXF \c DxfMLeaderLeaderLine object.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_set_next
(
        DxfMLeaderLeaderLine *line,
                /*!< a pointer to a DXF \c DxfMLeaderLeaderLine object. */
        DxfMLeaderLeaderLine *next
                /*!< a pointer to the next \c DxfMLeaderLeaderLine
                 * object for the DxfMLeaderLeaderLine object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
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
        line->next = (struct DxfMLeaderLeaderLine *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the last \c DxfMLeaderLeaderLine object
 * from a linked list of DXF \c DxfMLeaderLeaderLine objects.
 *
 * \return pointer to the last \c DxfMLeaderLeaderLine object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMLeaderLeaderLine *
dxf_mleader_leader_line_get_last
(
        DxfMLeaderLeaderLine *line
                /*!< a pointer to a DXF \c DxfMLeaderLeaderLine object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMLeaderLeaderLine *) line);
        }
        DxfMLeaderLeaderLine *iter = (DxfMLeaderLeaderLine *) line->next;
        while (iter->next != NULL)
        {
                iter = (DxfMLeaderLeaderLine *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMLeaderLeaderLine *) iter);
}


/* EOF*/
