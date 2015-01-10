/*!
 * \file viewport.c
 *
 * \author Copyright (C) 2010 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF viewport entity (\c VIEWPORT).
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
        DxfViewport *dxf_viewport = NULL;
        size_t size;

        size = sizeof (DxfViewport);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_viewport = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfViewport struct.\n")),
                  __FUNCTION__);
                dxf_viewport = NULL;
        }
        else
        {
                memset (dxf_viewport, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_viewport);
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
        DxfViewport *dxf_viewport
                /*!< DXF viewport entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;
        dxf_viewport = dxf_viewport_new ();
        if (dxf_viewport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfViewport struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_viewport->id_code = 0;
        dxf_viewport->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_viewport->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_viewport->x0 = 0.0;
        dxf_viewport->y0 = 0.0;
        dxf_viewport->z0 = 0.0;
        dxf_viewport->thickness = 0.0;
        dxf_viewport->width = 0.0;
        dxf_viewport->height = 0.0;
        dxf_viewport->status = 0;
        dxf_viewport->id = 1; /* Always 1. */
        dxf_viewport->color = DXF_COLOR_BYLAYER;
        dxf_viewport->paperspace = DXF_PAPERSPACE; /* Always on PAPERSPACE. */
        dxf_viewport->app_name = strdup ("ACAD"); /* Always "ACAD". */
        dxf_viewport->viewport_data = strdup ("MVIEW"); /* Always "MVIEW". */
        dxf_viewport->window_descriptor_begin = strdup ("{"); /* Always "{". */
        dxf_viewport->extended_entity_data_version = 16;
        dxf_viewport->x_target = 0.0;
        dxf_viewport->y_target = 0.0;
        dxf_viewport->z_target = 0.0;
        dxf_viewport->x_direction = 0.0;
        dxf_viewport->y_direction = 0.0;
        dxf_viewport->z_direction = 0.0;
        dxf_viewport->view_twist_angle = 0.0;
        dxf_viewport->view_height = 0.0;
        dxf_viewport->x_center = 0.0;
        dxf_viewport->y_center = 0.0;
        dxf_viewport->perspective_lens_length = 0.0;
        dxf_viewport->front_plane_offset = 0.0;
        dxf_viewport->back_plane_offset = 0.0;
        dxf_viewport->view_mode = 0;
        dxf_viewport->circle_zoom_percent = 0;
        dxf_viewport->fast_zoom_setting = 0;
        dxf_viewport->UCSICON_setting = 0;
        dxf_viewport->snap_on = 0;
        dxf_viewport->grid_on = 0;
        dxf_viewport->snap_style = 0;
        dxf_viewport->snap_isopair = 0;
        dxf_viewport->snap_rotation_angle = 0.0;
        dxf_viewport->x_snap_base = 0.0;
        dxf_viewport->y_snap_base = 0.0;
        dxf_viewport->x_snap_spacing = 0.0;
        dxf_viewport->y_snap_spacing = 0.0;
        dxf_viewport->x_grid_spacing = 0.0;
        dxf_viewport->y_grid_spacing = 0.0;
        dxf_viewport->plot_flag = 0;
        dxf_viewport->frozen_layer_list_begin = strdup ("{"); /* Always "{". */
        /*! \todo Implement the number of layers in a more efficient way.
         * A lot of memory is consumed by reserving for DXF_MAX_LAYERS
         * instead of the actual existing number of layers.
         * Maybe this can be solved by dynamically allocating a
         * reasonable number of layers during compile time, and
         * (re-allocating) shrinking when the actual number of layers is
         * known during run time. */
        for (i = 0; i == DXF_MAX_LAYERS; i++)
        {
                dxf_viewport->frozen_layers[i] = strdup ("");
        }
        dxf_viewport->frozen_layer_list_end = strdup ("}"); /* Always "}". */
        dxf_viewport->window_descriptor_end = strdup ("}"); /* Always "}". */
        dxf_viewport->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_viewport);
}


/*!
 * \brief Read data from a DXF file into an \c VIEWPORT entity.
 *
 * The last line read from file contained the string "VIEWPORT". \n
 * Now follows some data for the \c VIEWPORT, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_viewport. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_viewport_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfViewport *dxf_viewport
                /*!< DXF viewport entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        if (!dxf_viewport)
        {
                dxf_viewport = dxf_viewport_new ();
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
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_viewport->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_viewport->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_viewport->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_viewport->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->height);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->paperspace);
                }
                else if (strcmp (temp_string, "68") == 0)
                {
                        /* Now follows a string containing the
                         * status value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->status);
                }
                else if (strcmp (temp_string, "69") == 0)
                {
                        /* Now follows a string containing the
                         * id. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->id);
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
                        fscanf (fp->fp, "%s\n", dxf_viewport->app_name);
                        if (strcmp (dxf_viewport->app_name, "ACAD") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                                fprintf (stderr, "    unexpected content in string followed after group code 1001.\n");
                                return (EXIT_FAILURE);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the viewport
                         * data, always "MVIEW". */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_viewport->viewport_data);
                        if (strcmp (dxf_viewport->viewport_data, "MVIEW") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string.\n")));
                                return (EXIT_FAILURE);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the window
                         * begin descriptor, always "{". */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_viewport->window_descriptor_begin);
                        if (strcmp (dxf_viewport->window_descriptor_begin, "{") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr, "    unexpected content in string.\n");
                                return (EXIT_FAILURE);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the extended
                         * entity data version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->extended_entity_data_version);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the X-target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->x_target);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Y-target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->y_target);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Z-target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->z_target);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the X-direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->x_direction);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Y-direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->y_direction);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Z-direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->z_direction);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the view
                         * twist angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->view_twist_angle);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the view
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->view_height);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the
                         * X-coordinate of the view center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->x_center);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the
                         * Y-coordinate of the view center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->y_center);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the
                         * perspective lens length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->perspective_lens_length);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the front
                         * clipping plane offset. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->front_plane_offset);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the back
                         * clipping plane offset. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->back_plane_offset);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the view mode. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->view_mode);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the circle
                         * zoom percent. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->circle_zoom_percent);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the fast zoom
                         * setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->fast_zoom_setting);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the ICS ICON
                         * setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->UCSICON_setting);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the snap on
                         * setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->snap_on);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the grid on
                         * setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->grid_on);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the snap
                         * style setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->snap_style);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the snap
                         * isopair setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->snap_isopair);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the snap
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->snap_rotation_angle);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the X snap
                         * base. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->x_snap_base);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Y snap
                         * base. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->y_snap_base);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the X snap
                         * spacing. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->x_snap_spacing);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Y snap
                         * spacing. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_viewport->y_snap_spacing);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the plot flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_viewport->plot_flag);
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the frozen
                         * layer list begin descriptor, always "{". */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_viewport->frozen_layer_list_begin);
                        if (strcmp (dxf_viewport->frozen_layer_list_begin, "{") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string.\n")));
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
                                int j = 0;
                                do
                                {
                                        (fp->line_number)++;
                                        fscanf (fp->fp, "%s\n", dxf_viewport->frozen_layers[j]);
                                        j++;
                                        /* Now follows a string containing a group code. */
                                        (fp->line_number)++;
                                        fscanf (fp->fp, "%s\n", temp_string);
                                }
                                while ((strcmp (temp_string, "1003") == 0)
                                        || (j < DXF_MAX_LAYERS));
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the frozen
                         * layer list end descriptor, always "}". */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_viewport->frozen_layer_list_end);
                        if (strcmp (dxf_viewport->frozen_layer_list_end, "}") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string.\n")));
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
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the window
                         * end descriptor, always "}". */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_viewport->window_descriptor_end);
                        if (strcmp (dxf_viewport->window_descriptor_end, "}") == 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                fprintf (stderr,
                                  (_("\tunexpected content in string.\n")));
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
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
        DxfViewport *dxf_viewport
                /*!< DXF viewport entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("VIEWPORT");

        if (strcmp (dxf_viewport->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_viewport->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to default layer.\n")),
                  dxf_entity_name);
                dxf_viewport->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_viewport->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_viewport->id_code);
        }
        if (strcmp (dxf_viewport->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_viewport->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_viewport->layer);
        fprintf (fp->fp, " 10\n%f\n", dxf_viewport->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_viewport->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_viewport->z0);
        if (dxf_viewport->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_viewport->thickness);
        }
        fprintf (fp->fp, " 40\n%f\n", dxf_viewport->width);
        fprintf (fp->fp, " 41\n%f\n", dxf_viewport->height);
        if (dxf_viewport->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_viewport->color);
        }
        fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        fprintf (fp->fp, " 68\n%d\n", dxf_viewport->status);
        fprintf (fp->fp, " 69\n%d\n", dxf_viewport->id);
        fprintf (fp->fp, "1001\n%s\n", DXF_VIEWPORT_APP_NAME);
        fprintf (fp->fp, "1000\n%s\n", DXF_VIEWPORT_DATA);
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_WINDOW_BEGIN);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->extended_entity_data_version);
        fprintf (fp->fp, "1010\n%f\n", dxf_viewport->x_target);
        fprintf (fp->fp, "1020\n%f\n", dxf_viewport->y_target);
        fprintf (fp->fp, "1030\n%f\n", dxf_viewport->z_target);
        fprintf (fp->fp, "1010\n%f\n", dxf_viewport->x_direction);
        fprintf (fp->fp, "1020\n%f\n", dxf_viewport->y_direction);
        fprintf (fp->fp, "1030\n%f\n", dxf_viewport->z_direction);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->view_twist_angle);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->view_height);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->x_center);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->y_center);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->perspective_lens_length);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->front_plane_offset);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->back_plane_offset);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->view_mode);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->circle_zoom_percent);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->fast_zoom_setting);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->UCSICON_setting);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->snap_on);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->grid_on);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->snap_style);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->snap_isopair);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->snap_rotation_angle);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->x_snap_base);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->y_snap_base);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->x_snap_spacing);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->y_snap_spacing);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->x_grid_spacing);
        fprintf (fp->fp, "1040\n%f\n", dxf_viewport->y_grid_spacing);
        fprintf (fp->fp, "1070\n%d\n", dxf_viewport->plot_flag);
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_FROZEN_LAYER_LIST_BEGIN);
        /* Start a loop writing all frozen layer names*/
        int j = 0;
        while ((!dxf_viewport->frozen_layers[j]) /* Do not allow NULL pointers. */
                || (strcmp (dxf_viewport->frozen_layers[j], "") == 1) /* Do not allow empty strings. */
                || (j < DXF_MAX_LAYERS)) /* Do not overrun the array size. */
        {
                fprintf (fp->fp, "1003\n%s\n", dxf_viewport->frozen_layers[j]);
                j++;
        }
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_FROZEN_LAYER_LIST_END);
        fprintf (fp->fp, "1002\n%s\n", DXF_VIEWPORT_WINDOW_END);
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
        DxfViewport *dxf_viewport
                /*!< Pointer to the memory occupied by the DXF \c VIEWPORT
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_viewport->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfViewport was not NULL.\n")));
              return (EXIT_FAILURE);
        }
        free (dxf_viewport->linetype);
        free (dxf_viewport->layer);
        free (dxf_viewport->app_name);
        free (dxf_viewport->viewport_data);
        free (dxf_viewport->window_descriptor_begin);
        free (dxf_viewport->frozen_layer_list_begin);
        for (i = 0; i == DXF_MAX_LAYERS; i++)
        {
                if (strcmp (dxf_viewport->frozen_layers[i], "") != 0)
                {
                        free (dxf_viewport->frozen_layers[i]);
                }
        }
        free (dxf_viewport->frozen_layer_list_end);
        free (dxf_viewport->window_descriptor_end);
        free (dxf_viewport);
        dxf_viewport = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
