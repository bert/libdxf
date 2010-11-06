/*!
 * \file viewport.c
 * \author Copyright (C) 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_viewport_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfViewport *dxf_viewport = NULL;
        size_t size;

        size = sizeof (DxfViewport);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_viewport = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_viewport_new () could not allocate memory for a DxfViewport struct.\n");
                dxf_viewport = NULL;
        }
        else
        {
                memset (dxf_viewport, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_viewport_new () function.\n",
                __FILE__, __LINE__);
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_viewport_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;
        dxf_viewport = dxf_viewport_new ();
        if (dxf_viewport == NULL)
        {
              fprintf (stderr, "ERROR in dxf_viewport_init () could not allocate memory for a DxfViewport struct.\n");
              return (NULL);
        }
        dxf_viewport->common.id_code = 0;
        dxf_viewport->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_viewport->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_viewport->x0 = 0.0;
        dxf_viewport->y0 = 0.0;
        dxf_viewport->z0 = 0.0;
        dxf_viewport->common.thickness = 0.0;
        dxf_viewport->width = 0.0;
        dxf_viewport->height = 0.0;
        dxf_viewport->status = 0;
        dxf_viewport->id = 1; /* Always 1. */
        dxf_viewport->common.color = DXF_COLOR_BYLAYER;
        dxf_viewport->common.paperspace = DXF_PAPERSPACE; /* Always on PAPERSPACE. */
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
        dxf_viewport->common.acad_version_number = AutoCAD_12; /* Minimum required version is AutoCAD R12*/
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_viewport_init () function.\n",
                __FILE__, __LINE__);
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
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfViewport *dxf_viewport,
                /*!< DXF viewport entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_viewport_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_viewport)
        {
                dxf_viewport = dxf_viewport_new ();
        }
        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_viewport->common.id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_viewport->common.linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_viewport->common.layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->z0);
                }
                else if ((acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_viewport->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->common.thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * width. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->height);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->common.color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->common.paperspace);
                }
                else if (strcmp (temp_string, "68") == 0)
                {
                        /* Now follows a string containing the
                         * status value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->status);
                }
                else if (strcmp (temp_string, "69") == 0)
                {
                        /* Now follows a string containing the
                         * id. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->id);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else if (strcmp (temp_string, "1001") == 0)
                {
                        /* Now follows a sequence of ordered data fields. */
                        /* Now follows a string containing the appname,
                         * always "ACAD". */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_viewport->app_name);
                        if (strcmp (dxf_viewport->app_name, "ACAD") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string followed after group code 1001.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1000") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the viewport
                         * data, always "MVIEW". */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_viewport->viewport_data);
                        if (strcmp (dxf_viewport->viewport_data, "MVIEW") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string.\n");
                        }
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1002") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the window
                         * begin descriptor, always "{". */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_viewport->window_descriptor_begin);
                        if (strcmp (dxf_viewport->window_descriptor_begin, "{") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string.\n");
                        }
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the extended
                         * entity data version number. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->extended_entity_data_version);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1010") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the X-target. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->x_target);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1020") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Y-target. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->y_target);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1030") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Z-target. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->z_target);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1010") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the X-direction. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->x_direction);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1020") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Y-direction. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->y_direction);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1030") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Z-direction. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->z_direction);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the view
                         * twist angle. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->view_twist_angle);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the view
                         * height. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->view_height);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the
                         * X-coordinate of the view center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->x_center);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the
                         * Y-coordinate of the view center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->y_center);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the
                         * perspective lens length. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->perspective_lens_length);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the front
                         * clipping plane offset. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->front_plane_offset);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the back
                         * clipping plane offset. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->back_plane_offset);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the view mode. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->view_mode);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the circle
                         * zoom percent. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->circle_zoom_percent);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the fast zoom
                         * setting. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->fast_zoom_setting);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the ICS ICON
                         * setting. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->UCSICON_setting);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the snap on
                         * setting. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->snap_on);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the grid on
                         * setting. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->grid_on);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the snap
                         * style setting. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->snap_style);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the snap
                         * isopair setting. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->snap_isopair);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the snap
                         * rotation angle. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->snap_rotation_angle);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the X snap
                         * base. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->x_snap_base);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Y snap
                         * base. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->y_snap_base);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the X snap
                         * spacing. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->x_snap_spacing);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1040") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the Y snap
                         * spacing. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_viewport->y_snap_spacing);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1070") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the plot flag. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_viewport->plot_flag);
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1002") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the frozen
                         * layer list begin descriptor, always "{". */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_viewport->frozen_layer_list_begin);
                        if (strcmp (dxf_viewport->frozen_layer_list_begin, "{") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string.\n");
                        }
                        /*! \todo Implement the list of frozen layers
                         * here (in a proper way). */
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1002") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the frozen
                         * layer list end descriptor, always "}". */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_viewport->frozen_layer_list_end);
                        if (strcmp (dxf_viewport->frozen_layer_list_end, "}") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string.\n");
                        }
                        /* Now follows a string containing a group code. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "1002") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string sequence found.\n");
                                return (EXIT_FAILURE);
                        }
                        /* Now follows a string containing the window
                         * end descriptor, always "}". */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_viewport->window_descriptor_end);
                        if (strcmp (dxf_viewport->window_descriptor_end, "}") == 1)
                        {
                                fprintf (stderr, "Error in dxf_viewport_read () while reading from: %s in line: %d.\n",
                                        filename, *line_number);
                                fprintf (stderr, "    unexpected content in string.\n");
                        }
                }
                /* End of sequential ordered data fields. */
                else 
                {
                        fprintf (stderr, "Warning: in dxf_arc_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_arc_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
