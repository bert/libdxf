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


/* EOF */
