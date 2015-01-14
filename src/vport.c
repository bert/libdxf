/*!
 * \file vport.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF Viewport symbol table entry (\c VPORT).
 *
 * The VPORT table is unique: it may contain several entries with the
 * same name (indicating a multiple-viewport configuration).\n
 * The entries corresponding to the active viewport configuration all
 * have the name *ACTIVE.\n
 * The first such entry describes the current viewport.
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


#include "vport.h"


/*!
 * \brief Allocate memory for a DXF \c VPORT entity.
 *
 * Fill the memory contents with zeros.
 */
DxfVPort *
dxf_vport_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfVPort *dxf_vport = NULL;
        size_t size;

        size = sizeof (DxfVPort);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_vport = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfVPort struct.\n")),
                  __FUNCTION__);
                dxf_vport = NULL;
        }
        else
        {
                memset (dxf_vport, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_vport);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c VPORT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfVPort *
dxf_vport_init
(
        DxfVPort *dxf_vport
                /*!< DXF Viewport symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_vport == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_vport = dxf_vport_new ();
        }
        if (dxf_vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfVPort struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_vport->id_code = 0;
        dxf_vport->viewport_name = strdup ("");
        dxf_vport->x_min = 0.0;
        dxf_vport->y_min = 0.0;
        dxf_vport->x_max = 0.0;
        dxf_vport->y_max = 0.0;
        dxf_vport->x_center = 0.0;
        dxf_vport->y_center = 0.0;
        dxf_vport->x_snap_base = 0.0;
        dxf_vport->y_snap_base = 0.0;
        dxf_vport->x_snap_spacing = 0.0;
        dxf_vport->y_snap_spacing = 0.0;
        dxf_vport->x_grid_spacing = 0.0;
        dxf_vport->y_grid_spacing = 0.0;
        dxf_vport->x_direction = 0.0;
        dxf_vport->y_direction = 0.0;
        dxf_vport->z_direction = 0.0;
        dxf_vport->x_target = 0.0;
        dxf_vport->y_target = 0.0;
        dxf_vport->z_target = 0.0;
        dxf_vport->view_height = 0.0;
        dxf_vport->viewport_aspect_ratio = 0.0;
        dxf_vport->lens_length = 0.0;
        dxf_vport->front_plane_offset = 0.0;
        dxf_vport->back_plane_offset = 0.0;
        dxf_vport->snap_rotation_angle = 0.0;
        dxf_vport->view_twist_angle = 0.0;
        dxf_vport->status_field = 0;
        dxf_vport->id = 0;
        dxf_vport->standard_flag = 0;
        dxf_vport->view_mode = 0;
        dxf_vport->circle_zoom_percent = 0;
        dxf_vport->fast_zoom_setting = 0;
        dxf_vport->UCSICON_setting = 0;
        dxf_vport->snap_on = 0;
        dxf_vport->grid_on = 0;
        dxf_vport->snap_style = 0;
        dxf_vport->snap_isopair = 0;
        dxf_vport->dictionary_owner_soft = strdup ("");
        dxf_vport->dictionary_owner_hard = strdup ("");
        dxf_vport->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_vport);
}


/*!
 * \brief Free the allocated memory for a DXF \c VPORT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_vport_free
(
        DxfVPort *dxf_vport
                /*!< Pointer to the memory occupied by the DXF \c VPORT
                 * symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_vport->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfVPort was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_vport->viewport_name);
        free (dxf_vport->dictionary_owner_soft);
        free (dxf_vport->dictionary_owner_hard);
        free (dxf_vport);
        dxf_vport = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
