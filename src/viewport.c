/*!
 * \file viewport.c
 *
 * \author Copyright (C) 2010, 2012, 2015, 2017, 2018
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
 * allocated memory when succesful.
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
        viewport->x0 = 0.0;
        viewport->y0 = 0.0;
        viewport->z0 = 0.0;
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
        viewport->x_target = 0.0;
        viewport->y_target = 0.0;
        viewport->z_target = 0.0;
        viewport->x_direction = 0.0;
        viewport->y_direction = 0.0;
        viewport->z_direction = 0.0;
        viewport->view_twist_angle = 0.0;
        viewport->view_height = 0.0;
        viewport->x_center = 0.0;
        viewport->y_center = 0.0;
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
        viewport->x_snap_base = 0.0;
        viewport->y_snap_base = 0.0;
        viewport->x_snap_spacing = 0.0;
        viewport->y_snap_spacing = 0.0;
        viewport->x_grid_spacing = 0.0;
        viewport->y_grid_spacing = 0.0;
        viewport->plot_flag = 0;
        viewport->frozen_layer_list_begin = strdup ("{"); /* Always "{". */
        /*! \todo Implement the number of layers in a more efficient way.
         * A lot of memory is consumed by reserving for DXF_MAX_LAYERS
         * instead of the actual existing number of layers.
         * Maybe this can be solved by dynamically allocating a
         * reasonable number of layers during compile time, and
         * (re-allocating) shrinking when the actual number of layers is
         * known during run time. */
        viewport->frozen_layers = NULL;
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
                viewport = dxf_viewport_new ();
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
                        fscanf (fp->fp, "%x\n", &viewport->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", viewport->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", viewport->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (viewport->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &viewport->z0);
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
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else if (strcmp (temp_string, "1001") == 0)
                {
                        /* Now follows a sequence of ordered data fields. */
                        /* Now follows a string containing the appname,
                         * always "ACAD". */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", viewport->app_name);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", viewport->viewport_data);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", viewport->window_descriptor_begin);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->x_target);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->y_target);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->z_target);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->x_direction);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->y_direction);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->z_direction);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->x_center);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->y_center);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->x_snap_base);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->y_snap_base);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->x_snap_spacing);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%lf\n", &viewport->y_snap_spacing);
                        /* Now follows a string containing a group code. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", viewport->frozen_layer_list_begin);
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
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1003") == 0)
                        {
                                /* Start a loop reading all frozen layer
                                 * names and bail out when a group code
                                 * with a value of "1002" is encountered
                                 * or DXF_MAX_LAYERS is reached.*/
                                /*! \todo Do a proper implementation of reading frozen layers.*/
                                do
                                {
                                        (fp->line_number)++;
                                        fscanf (fp->fp, "%s\n", viewport->frozen_layers->value);
                                        /* Now follows a string containing a group code. */
                                        (fp->line_number)++;
                                        fscanf (fp->fp, "%s\n", temp_string);
                                }
                                while ((strcmp (temp_string, "1003") == 0));
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
                        fscanf (fp->fp, "%s\n", viewport->frozen_layer_list_end);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", viewport->window_descriptor_end);
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
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
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
        fprintf (fp->fp, " 10\n%f\n", viewport->x0);
        fprintf (fp->fp, " 20\n%f\n", viewport->y0);
        fprintf (fp->fp, " 30\n%f\n", viewport->z0);
        fprintf (fp->fp, " 40\n%f\n", viewport->width);
        fprintf (fp->fp, " 41\n%f\n", viewport->height);
        fprintf (fp->fp, " 68\n%d\n", viewport->status);
        fprintf (fp->fp, " 69\n%d\n", viewport->id);
        fprintf (fp->fp, "1001\n%s\n", DXF_VIEWPORT_APP_NAME);
        fprintf (fp->fp, "1000\n%s\n", DXF_VIEWPORT_DATA);
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_WINDOW_BEGIN);
        fprintf (fp->fp, "1070\n%d\n", viewport->extended_entity_data_version);
        fprintf (fp->fp, "1010\n%f\n", viewport->x_target);
        fprintf (fp->fp, "1020\n%f\n", viewport->y_target);
        fprintf (fp->fp, "1030\n%f\n", viewport->z_target);
        fprintf (fp->fp, "1010\n%f\n", viewport->x_direction);
        fprintf (fp->fp, "1020\n%f\n", viewport->y_direction);
        fprintf (fp->fp, "1030\n%f\n", viewport->z_direction);
        fprintf (fp->fp, "1040\n%f\n", viewport->view_twist_angle);
        fprintf (fp->fp, "1040\n%f\n", viewport->view_height);
        fprintf (fp->fp, "1040\n%f\n", viewport->x_center);
        fprintf (fp->fp, "1040\n%f\n", viewport->y_center);
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
        fprintf (fp->fp, "1040\n%f\n", viewport->x_snap_base);
        fprintf (fp->fp, "1040\n%f\n", viewport->y_snap_base);
        fprintf (fp->fp, "1040\n%f\n", viewport->x_snap_spacing);
        fprintf (fp->fp, "1040\n%f\n", viewport->y_snap_spacing);
        fprintf (fp->fp, "1040\n%f\n", viewport->x_grid_spacing);
        fprintf (fp->fp, "1040\n%f\n", viewport->y_grid_spacing);
        fprintf (fp->fp, "1070\n%d\n", viewport->plot_flag);
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_FROZEN_LAYER_LIST_BEGIN);
        /* Start a loop writing all frozen layer names. */
        /*! \todo Do a proper implementation of writing frozen layers. */
        while ((!viewport->frozen_layers->value) /* Do not allow NULL pointers. */
                || (strcmp (viewport->frozen_layers->value, "") == 1)) /* Do not allow empty strings. */
        {
                fprintf (fp->fp, "1003\n%s\n", viewport->frozen_layers->value);
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
        dxf_char_free_chain (viewport->frozen_layers);
        free (viewport->frozen_layer_list_end);
        free (viewport->window_descriptor_end);
        free (viewport);
        viewport = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c VIEWPORT
 * entities and all their data fields.
 */
void
dxf_viewport_free_chain
(
        DxfViewport *viewports
                /*!< a pointer to the chain of DXF \c VIEWPORT
                 * entities. */
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
                struct DxfViewport *iter = viewports->next;
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
 * \brief Get the center point \c p0 of a DXF \c VIEWPORT entity in
 * paperspace coordinates.
 *
 * \return the center point \c p0.
 */
DxfPoint *
dxf_viewport_get_p0
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
        if (viewport->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (viewport->p0);
}


/* EOF */
