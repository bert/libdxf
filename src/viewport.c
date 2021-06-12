/*!
 * \file viewport.c
 *
 * \author Copyright (C) 2010, 2012, 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF viewport entity (\c VIEWPORT).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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


#include "viewport.h"


/*!
 * \brief Allocate memory for a \c DxfViewport.
 *
 * Fill the memory contents with zeros.
 */
DxfViewport *
dxf_viewport_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfViewport *viewport = NULL;
        size_t size;

        size = sizeof (DxfViewport);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((viewport = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfViewport struct.\n")),
                  __FUNCTION__);
                viewport = NULL;
        }
        else
        {
                memset (viewport, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c VIEWPORT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfViewport *
dxf_viewport_init
(
        DxfViewport *viewport
                /*!< a pointer to the DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                viewport = dxf_viewport_new ();
        }
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfViewport struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->id_code = 0;
        viewport->linetype = strdup (DXF_DEFAULT_LINETYPE);
        viewport->layer = strdup (DXF_DEFAULT_LAYER);
        viewport->center = dxf_point_new ();
        viewport->center = dxf_point_init (viewport->center);
        viewport->center->x0 = 0.0;
        viewport->center->y0 = 0.0;
        viewport->center->z0 = 0.0;
        viewport->elevation = 0.0;
        viewport->thickness = 0.0;
        viewport->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        viewport->visibility = DXF_DEFAULT_VISIBILITY;
        viewport->width = 0.0;
        viewport->height = 0.0;
        viewport->status = 0;
        viewport->id = 1; /* Always 1. */
        viewport->color = DXF_COLOR_BYLAYER;
        viewport->paperspace = DXF_PAPERSPACE; /* Always on PAPERSPACE. */
        viewport->app_name = strdup ("ACAD"); /* Always "ACAD". */
        viewport->viewport_data = strdup ("MVIEW"); /* Always "MVIEW". */
        viewport->window_descriptor_begin = strdup ("{"); /* Always "{". */
        viewport->extended_entity_data_version = 16;
        viewport->target = dxf_point_new ();
        viewport->target = dxf_point_init (viewport->target);
        viewport->target->x0 = 0.0;
        viewport->target->y0 = 0.0;
        viewport->target->z0 = 0.0;
        viewport->direction = dxf_point_new ();
        viewport->direction = dxf_point_init (viewport->direction);
        viewport->direction->x0 = 0.0;
        viewport->direction->y0 = 0.0;
        viewport->direction->z0 = 0.0;
        viewport->view_twist_angle = 0.0;
        viewport->view_height = 0.0;
        viewport->view_center = dxf_point_new ();
        viewport->view_center = dxf_point_init (viewport->view_center);
        viewport->view_center->x0 = 0.0;
        viewport->view_center->y0 = 0.0;
        viewport->perspective_lens_length = 0.0;
        viewport->front_plane_offset = 0.0;
        viewport->back_plane_offset = 0.0;
        viewport->view_mode = 0;
        viewport->circle_zoom_percent = 0;
        viewport->fast_zoom_setting = 0;
        viewport->UCSICON_setting = 0;
        viewport->snap_on = 0;
        viewport->grid_on = 0;
        viewport->snap_style = 0;
        viewport->snap_isopair = 0;
        viewport->snap_rotation_angle = 0.0;
        viewport->snap_base = dxf_point_new ();
        viewport->snap_base = dxf_point_init (viewport->snap_base);
        viewport->snap_base->x0 = 0.0;
        viewport->snap_base->y0 = 0.0;
        viewport->snap_spacing = dxf_point_new ();
        viewport->snap_spacing = dxf_point_init (viewport->snap_spacing);
        viewport->snap_spacing->x0 = 0.0;
        viewport->snap_spacing->y0 = 0.0;
        viewport->grid_spacing = dxf_point_new ();
        viewport->grid_spacing = dxf_point_init (viewport->grid_spacing);
        viewport->grid_spacing->x0 = 0.0;
        viewport->grid_spacing->y0 = 0.0;
        viewport->plot_flag = 0;
        viewport->frozen_layer_list_begin = strdup ("{"); /* Always "{". */
        viewport->frozen_layers = dxf_char_new ();
        viewport->frozen_layers = dxf_char_init (viewport->frozen_layers);
        viewport->frozen_layers->value = strdup ("");
        viewport->frozen_layers->length = 0;
        viewport->frozen_layers->next = NULL;
        viewport->frozen_layer_list_end = strdup ("}"); /* Always "}". */
        viewport->window_descriptor_end = strdup ("}"); /* Always "}". */
        viewport->dictionary_owner_soft = strdup ("");
        viewport->dictionary_owner_hard = strdup ("");
        viewport->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Read data from a DXF file into an \c VIEWPORT entity.
 *
 * The last line read from file contained the string "VIEWPORT". \n
 * Now follows some data for the \c VIEWPORT, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c viewport. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfViewport *
dxf_viewport_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfViewport *viewport
                /*!< a pointer to the DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfChar *iter = NULL;

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
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                viewport = dxf_viewport_init (viewport);
        }
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
                        fscanf (fp->fp, "%x\n", (uint *) &viewport->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, viewport->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, viewport->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->center->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->center->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->center->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->height);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &viewport->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->paperspace);
                }
                else if (strcmp (temp_string, "68") == 0)
                {
                        /* Now follows a string containing the
                         * status value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->status);
                }
                else if (strcmp (temp_string, "69") == 0)
                {
                        /* Now follows a string containing the
                         * id. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->id);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else if (strcmp (temp_string, "1001") == 0)
                {
                        /* Now follows a sequence of ordered data fields. */
                        /* Now follows a string containing the appname,
                         * always "ACAD". */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, viewport->app_name);
                        if (strcmp (viewport->app_name, "ACAD") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string followed after group code 1001.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1000") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the viewport
                         * data, always "MVIEW". */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, viewport->viewport_data);
                        if (strcmp (viewport->viewport_data, "MVIEW") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1002") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the window
                         * begin descriptor, always "{". */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, viewport->window_descriptor_begin);
                        if (strcmp (viewport->window_descriptor_begin, "{") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr, "    unexpected content in string.\n");
                                return (NULL);
                        }
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the extended
                         * entity data version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->extended_entity_data_version);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1010") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the X-target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->target->x0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1020") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the Y-target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->target->y0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1030") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the Z-target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->target->z0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1010") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the X-direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->direction->x0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1020") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the Y-direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->direction->y0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1030") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the Z-direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->direction->z0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the view
                         * twist angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->view_twist_angle);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the view
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->view_height);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the
                         * X-coordinate of the view center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->view_center->x0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the
                         * Y-coordinate of the view center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->view_center->y0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the
                         * perspective lens length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->perspective_lens_length);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the front
                         * clipping plane offset. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->front_plane_offset);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the back
                         * clipping plane offset. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->back_plane_offset);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the view mode. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->view_mode);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the circle
                         * zoom percent. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->circle_zoom_percent);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the fast zoom
                         * setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->fast_zoom_setting);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the ICS ICON
                         * setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->UCSICON_setting);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the snap on
                         * setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->snap_on);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the grid on
                         * setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->grid_on);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the snap
                         * style setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->snap_style);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the snap
                         * isopair setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->snap_isopair);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the snap
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->snap_rotation_angle);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the X snap
                         * base. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->snap_base->x0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the Y snap
                         * base. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->snap_base->y0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the X snap
                         * spacing. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->snap_spacing->x0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the Y snap
                         * spacing. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->snap_spacing->y0);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the plot flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &viewport->plot_flag);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1002") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the frozen
                         * layer list begin descriptor, always "{". */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, viewport->frozen_layer_list_begin);
                        if (strcmp (viewport->frozen_layer_list_begin, "{") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing a group code
                         * value of "1003". */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1003") == 0)
                        {
                                /* Start a loop reading all frozen layer
                                 * names and bail out when a group code
                                 * with a value of "1002" is encountered.*/
                                /*! \todo Do a proper implementation of reading frozen layers.*/
                                iter = (DxfChar *) viewport->frozen_layers;
                                do
                                {
                                        (fp->line_number)++;
                                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter->value);
                                        /* Now follows a string containing a group code. */
                                        (fp->line_number)++;
                                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                                        iter->next = (DxfChar *) dxf_char_init ((DxfChar *) iter->next);
                                        iter = (DxfChar *) iter->next;
                                }
                                while ((strcmp (temp_string, "1003") == 0));
                                /* We have initialised the next DxfChar
                                 * and then left the loop.
                                 * The next DxfChar contains no valid
                                 * value, so we have to clean up. */
                                dxf_char_free ((DxfChar *) iter->next);
                                iter->next = NULL;
                        }
                        else
                        {
                                /* Either we found an empty list or we
                                 * have found an exception. */
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected end of frozen layer list found.\n")));
                                return (NULL);
                        }
                        /* Now we are expecting temp_string to contain a
                         * group code value of "1002". */
                        if (strcmp (temp_string, "1002") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the frozen
                         * layer list end descriptor, always "}". */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, viewport->frozen_layer_list_end);
                        if (strcmp (viewport->frozen_layer_list_end, "}") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "1002") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string sequence found.\n")));
                                return (NULL);
                        }
                        /* Now follows a string containing the window
                         * end descriptor, always "}". */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, viewport->window_descriptor_end);
                        if (strcmp (viewport->window_descriptor_end, "}") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string.\n")));
                                return (NULL);
                        }
                }
                /* End of sequential ordered data fields. */
                else 
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (viewport->linetype, "") == 0)
        {
                viewport->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (viewport->layer, "") == 0)
        {
                viewport->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Write DXF output for a viewport entity ( \c VIEWPORT ).
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_viewport_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfViewport *viewport
                /*!< a pointer to the DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("VIEWPORT");
        DxfChar *iter = NULL;

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
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (viewport->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, viewport->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                viewport->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (viewport->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, viewport->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to default layer.\n")),
                  dxf_entity_name);
                viewport->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (viewport->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", viewport->id_code);
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
        if ((strcmp (viewport->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", viewport->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (viewport->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", viewport->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (viewport->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", viewport->layer);
        if (strcmp (viewport->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", viewport->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (viewport->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", viewport->elevation);
        }
        if (viewport->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", viewport->color);
        }
        if (viewport->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", viewport->linetype_scale);
        }
        if (viewport->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", viewport->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbViewport\n");
        }
        if (viewport->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", viewport->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", viewport->center->x0);
        fprintf (fp->fp, " 20\n%f\n", viewport->center->y0);
        fprintf (fp->fp, " 30\n%f\n", viewport->center->z0);
        fprintf (fp->fp, " 40\n%f\n", viewport->width);
        fprintf (fp->fp, " 41\n%f\n", viewport->height);
        fprintf (fp->fp, " 68\n%d\n", viewport->status);
        fprintf (fp->fp, " 69\n%d\n", viewport->id);
        fprintf (fp->fp, "1001\n%s\n", DXF_VIEWPORT_APP_NAME);
        fprintf (fp->fp, "1000\n%s\n", DXF_VIEWPORT_DATA);
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_WINDOW_BEGIN);
        fprintf (fp->fp, "1070\n%d\n", viewport->extended_entity_data_version);
        fprintf (fp->fp, "1010\n%f\n", viewport->target->x0);
        fprintf (fp->fp, "1020\n%f\n", viewport->target->y0);
        fprintf (fp->fp, "1030\n%f\n", viewport->target->z0);
        fprintf (fp->fp, "1010\n%f\n", viewport->direction->x0);
        fprintf (fp->fp, "1020\n%f\n", viewport->direction->y0);
        fprintf (fp->fp, "1030\n%f\n", viewport->direction->z0);
        fprintf (fp->fp, "1040\n%f\n", viewport->view_twist_angle);
        fprintf (fp->fp, "1040\n%f\n", viewport->view_height);
        fprintf (fp->fp, "1040\n%f\n", viewport->view_center->x0);
        fprintf (fp->fp, "1040\n%f\n", viewport->view_center->y0);
        fprintf (fp->fp, "1040\n%f\n", viewport->perspective_lens_length);
        fprintf (fp->fp, "1040\n%f\n", viewport->front_plane_offset);
        fprintf (fp->fp, "1040\n%f\n", viewport->back_plane_offset);
        fprintf (fp->fp, "1070\n%d\n", viewport->view_mode);
        fprintf (fp->fp, "1070\n%d\n", viewport->circle_zoom_percent);
        fprintf (fp->fp, "1070\n%d\n", viewport->fast_zoom_setting);
        fprintf (fp->fp, "1070\n%d\n", viewport->UCSICON_setting);
        fprintf (fp->fp, "1070\n%d\n", viewport->snap_on);
        fprintf (fp->fp, "1070\n%d\n", viewport->grid_on);
        fprintf (fp->fp, "1070\n%d\n", viewport->snap_style);
        fprintf (fp->fp, "1070\n%d\n", viewport->snap_isopair);
        fprintf (fp->fp, "1040\n%f\n", viewport->snap_rotation_angle);
        fprintf (fp->fp, "1040\n%f\n", viewport->snap_base->x0);
        fprintf (fp->fp, "1040\n%f\n", viewport->snap_base->y0);
        fprintf (fp->fp, "1040\n%f\n", viewport->snap_spacing->x0);
        fprintf (fp->fp, "1040\n%f\n", viewport->snap_spacing->y0);
        fprintf (fp->fp, "1040\n%f\n", viewport->grid_spacing->x0);
        fprintf (fp->fp, "1040\n%f\n", viewport->grid_spacing->y0);
        fprintf (fp->fp, "1070\n%d\n", viewport->plot_flag);
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_FROZEN_LAYER_LIST_BEGIN);
        /* Start a loop writing all frozen layer names. */
        iter = viewport->frozen_layers;
        while ((!iter->value) /* Do not allow NULL pointers. */
          || (strcmp (iter->value, "") == 1)) /* Do not allow empty strings. */
        {
                fprintf (fp->fp, "1003\n%s\n", iter->value);
                iter = (DxfChar *) iter->next;
                if (iter->next == NULL)
                {
                        break;
                }
        }
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_FROZEN_LAYER_LIST_END);
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_WINDOW_END);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c VIEWPORT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_viewport_free
(
        DxfViewport *viewport
                /*!< a pointer to the memory occupied by the DXF
                 * \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (viewport->linetype);
        free (viewport->layer);
        free (viewport->app_name);
        free (viewport->viewport_data);
        free (viewport->window_descriptor_begin);
        free (viewport->frozen_layer_list_begin);
        dxf_char_free_list (viewport->frozen_layers);
        free (viewport->frozen_layer_list_end);
        free (viewport->window_descriptor_end);
        free (viewport);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c VIEWPORT entities and all their data fields.
 */
void
dxf_viewport_free_list
(
        DxfViewport *viewports
                /*!< a pointer to the single linked list of DXF
                 * \c VIEWPORT entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (viewports == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (viewports != NULL)
        {
                DxfViewport *iter = (DxfViewport *) viewports->next;
                dxf_viewport_free (viewports);
                viewports = (DxfViewport *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c VIEWPORT entity.
 *
 * \return \c id_code.
 */
int
dxf_viewport_get_id_code
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_id_code
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
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
        if (viewport == NULL)
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
        viewport->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c linetype from a DXF \c VIEWPORT entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_viewport_get_linetype
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_linetype
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c layer from a DXF \c VIEWPORT entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_viewport_get_layer
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_layer
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c elevation from a DXF \c VIEWPORT entity.
 *
 * \return \c elevation.
 */
double
dxf_viewport_get_elevation
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_elevation
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c thickness from a DXF \c VIEWPORT entity.
 *
 * \return \c thickness.
 */
double
dxf_viewport_get_thickness
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_thickness
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c VIEWPORT entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_viewport_get_linetype_scale
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_linetype_scale
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c visibility from a DXF \c VIEWPORT entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_viewport_get_visibility
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_visibility
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c color from a DXF \c VIEWPORT entity.
 *
 * \return color.
 */
int
dxf_viewport_get_color
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->color);
}


/*!
 * \brief Set the \c color for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_color
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c VIEWPORT entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_viewport_get_paperspace
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (viewport->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_paperspace
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c VIEWPORT
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_viewport_get_graphics_data_size
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (viewport->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_graphics_data_size
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        viewport->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c VIEWPORT entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_viewport_get_shadow_mode
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_shadow_mode
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c VIEWPORT entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_viewport_get_binary_graphics_data
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) viewport->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_binary_graphics_data
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c VIEWPORT entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_viewport_get_dictionary_owner_soft
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_dictionary_owner_soft
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_viewport_get_material
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_material
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c VIEWPORT entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_viewport_get_dictionary_owner_hard
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_dictionary_owner_hard
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c lineweight from a DXF \c VIEWPORT entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_viewport_get_lineweight
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_lineweight
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_viewport_get_plot_style_name
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_plot_style_name
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c color_value from a DXF \c VIEWPORT entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_viewport_get_color_value
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_color_value
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c color_name from a DXF \c VIEWPORT entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_viewport_get_color_name
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_color_name
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c transparency from a DXF \c VIEWPORT entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_viewport_get_transparency
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_transparency
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the center point \c center of a DXF \c VIEWPORT entity in
 * paperspace coordinates.
 *
 * \return the center point \c center.
 */
DxfPoint *
dxf_viewport_get_center
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->center);
}


/*!
 * \brief Set the center point \c center of a DXF \c VIEWPORT entity.
 *
 * \return a pointer to a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_center
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfPoint *center
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->center = center;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the X-value of the center point \c center_x of a DXF \c VIEWPORT
 * entity.
 *
 * \return the X-value of the center point \c center_x.
 */
double
dxf_viewport_get_center_x
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->center->x0);
}


/*!
 * \brief Set the X-value of the center point \c center_x of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_center_x
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double center_x
                /*!< the X-value of the center point \c center_x of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->center->x0 = center_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Y-value of the center point \c center_y of a DXF \c VIEWPORT
 * entity.
 *
 * \return the Y-value of the center point \c center_y.
 */
double
dxf_viewport_get_center_y
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->center->y0);
}


/*!
 * \brief Set the Y-value of the center point \c center_y of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_center_y
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double center_y
                /*!< the Y-value of the center point \c center_y of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->center->y0 = center_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Z-value of the center point \c center_z of a DXF \c VIEWPORT
 * entity.
 *
 * \return the Z-value of the center point \c center_z.
 */
double
dxf_viewport_get_center_z
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->center->z0);
}


/*!
 * \brief Set the Z-value of the center point \c center_z of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_center_z
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double center_z
                /*!< the Z-value of the center point \c center_z of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->center->z0 = center_z;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c width from a DXF \c VIEWPORT entity.
 *
 * \return \c width.
 */
double
dxf_viewport_get_width
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->width);
}


/*!
 * \brief Set the \c width for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_width
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double width
                /*!< the \c width to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->width = width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c height from a DXF \c VIEWPORT entity.
 *
 * \return \c height.
 */
double
dxf_viewport_get_height
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->height);
}


/*!
 * \brief Set the \c height for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_height
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double height
                /*!< the \c height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->height = height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c status from a DXF \c VIEWPORT entity.
 *
 * \return \c status.
 */
int
dxf_viewport_get_status
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->status);
}


/*!
 * \brief Set the \c status for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_status
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int status
                /*!< the \c status to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->status = status;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c id from a DXF \c VIEWPORT entity.
 *
 * \return \c id.
 */
int
dxf_viewport_get_id
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->id);
}


/*!
 * \brief Set the \c id for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_id
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int id
                /*!< the \c id to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->id = id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c app_name from a DXF \c VIEWPORT entity.
 *
 * \return \c app_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_viewport_get_app_name
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->app_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->app_name));
}


/*!
 * \brief Set the \c app_name for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_app_name
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *app_name
                /*!< a string containing the \c app_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (app_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->app_name = strdup (app_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c viewport_data from a DXF \c VIEWPORT entity.
 *
 * \return \c viewport_data when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_viewport_get_viewport_data
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->viewport_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->viewport_data));
}


/*!
 * \brief Set the \c viewport_data for a DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_viewport_data
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *viewport_data
                /*!< a string containing the \c viewport_data for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->viewport_data = strdup (viewport_data);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c window_descriptor_begin from a DXF \c VIEWPORT
 * entity.
 *
 * \return \c window_descriptor_begin when sucessful, or \c NULL when an
 * error occurred.
 */
char *
dxf_viewport_get_window_descriptor_begin
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->window_descriptor_begin ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->window_descriptor_begin));
}


/*!
 * \brief Set the \c window_descriptor_begin for a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_window_descriptor_begin
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *window_descriptor_begin
                /*!< a string containing the \c window_descriptor_begin
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (window_descriptor_begin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->window_descriptor_begin = strdup (window_descriptor_begin);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c extended_entity_data_version from a DXF \c VIEWPORT
 * entity.
 *
 * \return \c extended_entity_data_version.
 */
int
dxf_viewport_get_extended_entity_data_version
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->extended_entity_data_version);
}


/*!
 * \brief Set the \c extended_entity_data_version for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_extended_entity_data_version
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int extended_entity_data_version
                /*!< the \c extended_entity_data_version to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->extended_entity_data_version = extended_entity_data_version;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the target point \c target of a DXF \c VIEWPORT entity.
 *
 * \return the target point \c target.
 */
DxfPoint *
dxf_viewport_get_target
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->target);
}


/*!
 * \brief Set the target point \c target of a DXF \c VIEWPORT entity.
 *
 * \return a pointer to a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_target
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfPoint *target
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->target = target;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the X-value of the target point \c target_x of a DXF \c VIEWPORT
 * entity.
 *
 * \return the X-value of the target point \c target_x.
 */
double
dxf_viewport_get_target_x
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->target->x0);
}


/*!
 * \brief Set the X-value of the target point \c target_x of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_target_x
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double target_x
                /*!< the X-value of the target point \c target_x of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->target->x0 = target_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Y-value of the target point \c target_y of a DXF \c VIEWPORT
 * entity.
 *
 * \return the Y-value of the target point \c target_y.
 */
double
dxf_viewport_get_target_y
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->target->y0);
}


/*!
 * \brief Set the Y-value of the target point \c target_y of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_target_y
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double target_y
                /*!< the Y-value of the target point \c target_y of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->target->y0 = target_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Z-value of the target point \c target_z of a DXF \c VIEWPORT
 * entity.
 *
 * \return the Z-value of the target point \c target_z.
 */
double
dxf_viewport_get_target_z
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->target->z0);
}


/*!
 * \brief Set the Z-value of the target point \c target_z of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_target_z
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double target_z
                /*!< the Z-value of the target point \c target_z of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->target == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->target->z0 = target_z;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the direction from target point \c direction of a DXF \c VIEWPORT
 * entity.
 *
 * \return the direction from target point \c direction.
 */
DxfPoint *
dxf_viewport_get_direction
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->direction);
}


/*!
 * \brief Set the direction from target point \c direction of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_direction
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfPoint *direction
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->direction = direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the X-value of the direction from target point \c direction_x of a
 * DXF \c VIEWPORT entity.
 *
 * \return the X-value of the direction from target point \c direction_x.
 */
double
dxf_viewport_get_direction_x
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->direction->x0);
}


/*!
 * \brief Set the X-value of the direction from target point \c direction_x of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_direction_x
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double direction_x
                /*!< the X-value of the direction from target point
                 * \c direction_x of a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->direction->x0 = direction_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Y-value of the direction from target point \c direction_y of a
 * DXF \c VIEWPORT entity.
 *
 * \return the Y-value of the direction from target point \c direction_y.
 */
double
dxf_viewport_get_direction_y
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->direction->y0);
}


/*!
 * \brief Set the Y-value of the direction from target point \c direction_y of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_direction_y
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double direction_y
                /*!< the Y-value of the direction from target point
                 * \c direction_y of a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->direction->y0 = direction_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Z-value of the direction from target point \c direction_z of a
 * DXF \c VIEWPORT entity.
 *
 * \return the Z-value of the direction from target point \c direction_z.
 */
double
dxf_viewport_get_direction_z
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->direction->z0);
}


/*!
 * \brief Set the Z-value of the direction from target point \c direction_z of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_direction_z
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double direction_z
                /*!< the Z-value of the direction from target point
                 * \c direction_z of a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->direction == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->direction->z0 = direction_z;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c view_twist_angle from a DXF \c VIEWPORT entity.
 *
 * \return \c view_twist_angle.
 */
double
dxf_viewport_get_view_twist_angle
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->view_twist_angle);
}


/*!
 * \brief Set the \c view_twist_angle for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_view_twist_angle
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double view_twist_angle
                /*!< the \c view_twist_angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->view_twist_angle = view_twist_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c view_height from a DXF \c VIEWPORT entity.
 *
 * \return \c view_height.
 */
double
dxf_viewport_get_view_height
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->view_height);
}


/*!
 * \brief Set the \c view_height for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_view_height
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double view_height
                /*!< the \c view_height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->view_height = view_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the view center point \c view_center of a DXF \c VIEWPORT
 * entity.
 *
 * \return the view center point \c view_center.
 */
DxfPoint *
dxf_viewport_get_view_center
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->view_center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->view_center);
}


/*!
 * \brief Set the view center point \c view_center of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_view_center
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfPoint *view_center
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view_center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->view_center = view_center;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the X-value of the view center point \c view_center_x of a DXF
 * \c VIEWPORT entity.
 *
 * \return the X-value of the view center point \c view_center_x.
 */
double
dxf_viewport_get_view_center_x
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->view_center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->view_center->x0);
}


/*!
 * \brief Set the X-value of the view center point \c view_center_x of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_view_center_x
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double view_center_x
                /*!< the X-value of the view center point \c view_center_x of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->view_center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->view_center->x0 = view_center_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Y-value of the view center point \c view_center_y of a DXF
 * \c VIEWPORT entity.
 *
 * \return the Y-value of the view center point \c view_center_y.
 */
double
dxf_viewport_get_view_center_y
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->view_center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->view_center->y0);
}


/*!
 * \brief Set the Y-value of the view center point \c view_center_y of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_view_center_y
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double view_center_y
                /*!< the Y-value of the view center point \c view_center_y of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->view_center == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->view_center->y0 = view_center_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c perspective_lens_length from a DXF \c VIEWPORT
 * entity.
 *
 * \return \c perspective_lens_length.
 */
double
dxf_viewport_get_perspective_lens_length
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->perspective_lens_length);
}


/*!
 * \brief Set the \c perspective_lens_length for a DXF \c VIEWPORT
 * entity.
 */
DxfViewport *
dxf_viewport_set_perspective_lens_length
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double perspective_lens_length
                /*!< the \c perspective_lens_length to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->perspective_lens_length = perspective_lens_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c front_plane_offset from a DXF \c VIEWPORT entity.
 *
 * \return \c front_plane_offset.
 */
double
dxf_viewport_get_front_plane_offset
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->front_plane_offset);
}


/*!
 * \brief Set the \c front_plane_offset for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_front_plane_offset
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double front_plane_offset
                /*!< the \c front_plane_offset to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->front_plane_offset = front_plane_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c back_plane_offset from a DXF \c VIEWPORT entity.
 *
 * \return \c back_plane_offset.
 */
double
dxf_viewport_get_back_plane_offset
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->back_plane_offset);
}


/*!
 * \brief Set the \c back_plane_offset for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_back_plane_offset
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double back_plane_offset
                /*!< the \c back_plane_offset to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->back_plane_offset = back_plane_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c view_mode from a DXF \c VIEWPORT entity.
 *
 * \return \c view_mode.
 */
int
dxf_viewport_get_view_mode
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->view_mode);
}


/*!
 * \brief Set the \c view_mode for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_view_mode
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int view_mode
                /*!< the \c view_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->view_mode = view_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c circle_zoom_percent from a DXF \c VIEWPORT entity.
 *
 * \return \c circle_zoom_percent.
 */
int
dxf_viewport_get_circle_zoom_percent
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->circle_zoom_percent);
}


/*!
 * \brief Set the \c circle_zoom_percent for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_circle_zoom_percent
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int circle_zoom_percent
                /*!< the \c circle_zoom_percent to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->circle_zoom_percent = circle_zoom_percent;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c fast_zoom_setting from a DXF \c VIEWPORT entity.
 *
 * \return \c fast_zoom_setting.
 */
int
dxf_viewport_get_fast_zoom_setting
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->fast_zoom_setting);
}


/*!
 * \brief Set the \c fast_zoom_setting for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_fast_zoom_setting
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int fast_zoom_setting
                /*!< the \c fast_zoom_setting to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->fast_zoom_setting = fast_zoom_setting;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c UCSICON_setting from a DXF \c VIEWPORT entity.
 *
 * \return \c UCSICON_setting.
 */
int
dxf_viewport_get_UCSICON_setting
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->UCSICON_setting);
}


/*!
 * \brief Set the \c UCSICON_setting for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_UCSICON_setting
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int UCSICON_setting
                /*!< the \c UCSICON_setting to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->UCSICON_setting = UCSICON_setting;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c snap_on from a DXF \c VIEWPORT entity.
 *
 * \return \c snap_on.
 */
int
dxf_viewport_get_snap_on
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_on);
}


/*!
 * \brief Set the \c snap_on for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_snap_on
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int snap_on
                /*!< the \c snap_on to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_on = snap_on;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c grid_on from a DXF \c VIEWPORT entity.
 *
 * \return \c grid_on.
 */
int
dxf_viewport_get_grid_on
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->grid_on);
}


/*!
 * \brief Set the \c grid_on for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_grid_on
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int grid_on
                /*!< the \c grid_on to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->grid_on = grid_on;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c snap_style from a DXF \c VIEWPORT entity.
 *
 * \return \c snap_style.
 */
int
dxf_viewport_get_snap_style
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_style);
}


/*!
 * \brief Set the \c snap_style for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_snap_style
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int snap_style
                /*!< the \c snap_style to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_style = snap_style;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c snap_isopair from a DXF \c VIEWPORT entity.
 *
 * \return \c snap_isopair.
 */
int
dxf_viewport_get_snap_isopair
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_isopair);
}


/*!
 * \brief Set the \c snap_isopair for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_snap_isopair
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int snap_isopair
                /*!< the \c snap_isopair to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_isopair = snap_isopair;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c snap_rotation_angle from a DXF \c VIEWPORT entity.
 *
 * \return \c snap_rotation_angle.
 */
double
dxf_viewport_get_snap_rotation_angle
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_rotation_angle);
}


/*!
 * \brief Set the \c snap_rotation_angle for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_snap_rotation_angle
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double snap_rotation_angle
                /*!< the \c snap_rotation_angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_rotation_angle = snap_rotation_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the snap base point \c snap_base of a DXF \c VIEWPORT entity.
 *
 * \return the snap base point \c snap_base.
 */
DxfPoint *
dxf_viewport_get_snap_base
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_base);
}


/*!
 * \brief Set the snap base point \c snap_base of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_snap_base
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfPoint *snap_base
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_base = snap_base;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the X-value of the snap base point \c snap_base_x of a DXF
 * \c VIEWPORT entity.
 *
 * \return the X-value of the snap base point \c snap_base_x.
 */
double
dxf_viewport_get_snap_base_x
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_base->x0);
}


/*!
 * \brief Set the X-value of the snap base point \c snap_base_x of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_snap_base_x
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double snap_base_x
                /*!< the X-value of the snap base point \c snap_base_x of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_base->x0 = snap_base_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Y-value of the snap base point \c snap_base_y of a DXF
 * \c VIEWPORT entity.
 *
 * \return the Y-value of the snap base point \c snap_base_y.
 */
double
dxf_viewport_get_snap_base_y
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_base->y0);
}


/*!
 * \brief Set the Y-value of the snap base point \c snap_base_y of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_snap_base_y
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double snap_base_y
                /*!< the Y-value of the snap base point \c snap_base_y of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->snap_base == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_base->y0 = snap_base_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the snap spacing \c snap_spacing of a DXF \c VIEWPORT entity.
 *
 * \return the snap spacing \c snap_spacing.
 */
DxfPoint *
dxf_viewport_get_snap_spacing
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_spacing);
}


/*!
 * \brief Set the snap spacing \c snap_spacing of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_snap_spacing
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfPoint *snap_spacing
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_spacing = snap_spacing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the X-value of the snap spacing \c snap_spacing_x of a DXF
 * \c VIEWPORT entity.
 *
 * \return the X-value of the snap spacing \c snap_spacing_x.
 */
double
dxf_viewport_get_snap_spacing_x
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_spacing->x0);
}


/*!
 * \brief Set the X-value of the snap spacing \c snap_spacing_x of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_snap_spacing_x
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double snap_spacing_x
                /*!< the X-value of the snap spacing \c snap_spacing_x of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_spacing->x0 = snap_spacing_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Y-value of the snap spacing \c snap_spacing_y of a DXF
 * \c VIEWPORT entity.
 *
 * \return the Y-value of the snap spacing \c snap_spacing_y.
 */
double
dxf_viewport_get_snap_spacing_y
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->snap_spacing->y0);
}


/*!
 * \brief Set the Y-value of the snap spacing \c snap_spacing_y of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_snap_spacing_y
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double snap_spacing_y
                /*!< the Y-value of the snap spacing \c snap_spacing_y of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->snap_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->snap_spacing->y0 = snap_spacing_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the grid spacing \c grid_spacing of a DXF \c VIEWPORT entity.
 *
 * \return the grid spacing \c grid_spacing.
 */
DxfPoint *
dxf_viewport_get_grid_spacing
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->grid_spacing);
}


/*!
 * \brief Set the grid spacing \c grid_spacing of a DXF \c VIEWPORT
 * entity.
 *
 * \return a pointer to a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_grid_spacing
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfPoint *grid_spacing
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->grid_spacing = grid_spacing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the X-value of the grid spacing \c grid_spacing_x of a DXF
 * \c VIEWPORT entity.
 *
 * \return the X-value of the grid spacing \c grid_spacing_x.
 */
double
dxf_viewport_get_grid_spacing_x
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->grid_spacing->x0);
}


/*!
 * \brief Set the X-value of the grid spacing \c grid_spacing_x of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_grid_spacing_x
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double grid_spacing_x
                /*!< the X-value of the grid spacing \c grid_spacing_x of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->grid_spacing->x0 = grid_spacing_x;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the Y-value of the grid spacing \c grid_spacing_y of a DXF
 * \c VIEWPORT entity.
 *
 * \return the Y-value of the grid spacing \c grid_spacing_y.
 */
double
dxf_viewport_get_grid_spacing_y
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (viewport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->grid_spacing->y0);
}


/*!
 * \brief Set the Y-value of the grid spacing \c grid_spacing_y of a
 * DXF \c VIEWPORT entity.
 *
 * \return a pointer to \c viewport when successful, or \c NULL when an
 * error occurred.
 */
DxfViewport *
dxf_viewport_set_grid_spacing_y
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        double grid_spacing_y
                /*!< the Y-value of the grid spacing \c grid_spacing_y of a DXF
                 * \c VIEWPORT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->grid_spacing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->grid_spacing->y0 = grid_spacing_y;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c plot_flag from a DXF \c VIEWPORT entity.
 *
 * \return \c plot_flag.
 */
int
dxf_viewport_get_plot_flag
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->plot_flag);
}


/*!
 * \brief Set the \c plot_flag for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_plot_flag
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        int plot_flag
                /*!< the \c plot_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->plot_flag = plot_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c frozen_layer_list_begin from a DXF \c VIEWPORT
 * entity.
 *
 * \return \c frozen_layer_list_begin when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_viewport_get_frozen_layer_list_begin
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->frozen_layer_list_begin ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->frozen_layer_list_begin));
}


/*!
 * \brief Set the \c frozen_layer_list_begin for a DXF \c VIEWPORT
 * entity.
 */
DxfViewport *
dxf_viewport_set_frozen_layer_list_begin
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *frozen_layer_list_begin
                /*!< a pointer to a string containing the
                 * \c frozen_layer_list_begin to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (frozen_layer_list_begin == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->frozen_layer_list_begin = strdup (frozen_layer_list_begin);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c frozen_layers from a DXF \c VIEWPORT entity.
 *
 * \return \c frozen_layers when sucessful, \c NULL when an
 * error occurred.
 */
DxfChar *
dxf_viewport_get_frozen_layers
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->frozen_layers ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->frozen_layers);
}


/*!
 * \brief Set the \c frozen_layers for a DXF \c VIEWPORT entity.
 */
DxfViewport *
dxf_viewport_set_frozen_layers
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfChar *frozen_layers
                /*!< a pointer to the \c frozen_layers to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (frozen_layers == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->frozen_layers = frozen_layers;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c frozen_layer_list_end from a DXF \c VIEWPORT
 * entity.
 *
 * \return \c frozen_layer_list_end when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_viewport_get_frozen_layer_list_end
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->frozen_layer_list_end ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->frozen_layer_list_end));
}


/*!
 * \brief Set the \c frozen_layer_list_end for a DXF \c VIEWPORT
 * entity.
 */
DxfViewport *
dxf_viewport_set_frozen_layer_list_end
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *frozen_layer_list_end
                /*!< a pointer to a string containing the
                 * \c frozen_layer_list_end to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (frozen_layer_list_end == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->frozen_layer_list_end = strdup (frozen_layer_list_end);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the \c window_descriptor_end from a DXF \c VIEWPORT
 * entity.
 *
 * \return \c window_descriptor_end when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_viewport_get_window_descriptor_end
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->window_descriptor_end ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (viewport->window_descriptor_end));
}


/*!
 * \brief Set the \c window_descriptor_end for a DXF \c VIEWPORT
 * entity.
 */
DxfViewport *
dxf_viewport_set_window_descriptor_end
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        char *window_descriptor_end
                /*!< a pointer to a string containing the
                 * \c window_descriptor_end to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (window_descriptor_end == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        viewport->window_descriptor_end = strdup (window_descriptor_end);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the pointer to the next \c VIEWPORT entity from a DXF
 * \c VIEWPORT entity.
 *
 * \return pointer to the next \c VIEWPORT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfViewport *
dxf_viewport_get_next
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfViewport *) viewport->next);
}


/*!
 * \brief Set the pointer to the next \c VIEWPORT for a DXF \c VIEWPORT
 * entity.
 */
DxfViewport *
dxf_viewport_set_next
(
        DxfViewport *viewport,
                /*!< a pointer to a DXF \c VIEWPORT entity. */
        DxfViewport *next
                /*!< a pointer to the next \c VIEWPORT for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
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
        viewport->next = (struct DxfViewport *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport);
}


/*!
 * \brief Get the pointer to the last \c VIEWPORT entity from a linked
 * list of DXF \c VIEWPORT entities.
 *
 * \return pointer to the last \c VIEWPORT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfViewport *
dxf_viewport_get_last
(
        DxfViewport *viewport
                /*!< a pointer to a DXF \c VIEWPORT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (viewport->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfViewport *) viewport);
        }
        DxfViewport *iter = (DxfViewport *) viewport->next;
        while (iter->next != NULL)
        {
                iter = (DxfViewport *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfViewport *) iter);
}


/* EOF */
