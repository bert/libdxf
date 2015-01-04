/*!
 * \file view.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF View symbol table entry (\c VIEW).
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


#include "view.h"


/*!
 * \brief Allocate memory for a DXF \c VIEW.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfView *
dxf_view_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfView *dxf_view = NULL;
        size_t size;

        size = sizeof (DxfView);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_view = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfView struct.\n")),
                  __FUNCTION__);
                dxf_view = NULL;
        }
        else
        {
                memset (dxf_view, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_view);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c VIEW
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfView *
dxf_view_init
(
        DxfView *dxf_view
                /*!< DXF View entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_view == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_view = dxf_view_new ();
        }
        if (dxf_view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfView struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_view->id_code = 0;
        dxf_view->view_name = strdup ("");
        dxf_view->x_view = 0.0;
        dxf_view->y_view = 0.0;
        dxf_view->x_direction = 0.0;
        dxf_view->y_direction = 0.0;
        dxf_view->z_direction = 0.0;
        dxf_view->x_target = 0.0;
        dxf_view->y_target = 0.0;
        dxf_view->z_target = 0.0;
        dxf_view->view_height = 0.0;
        dxf_view->view_width = 0.0;
        dxf_view->lens_length = 0.0;
        dxf_view->front_plane_offset = 0.0;
        dxf_view->back_plane_offset = 0.0;
        dxf_view->view_twist_angle = 0.0;
        dxf_view->flag = 0;
        dxf_view->view_mode = 0;
        dxf_view->dictionary_owner_soft = strdup ("");
        dxf_view->dictionary_owner_hard = strdup ("");
        dxf_view->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_view);
}


/*!
 * \brief Free the allocated memory for a DXF \c VIEW and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_view_free
(
        DxfView *dxf_view
                /*!< Pointer to the memory occupied by the DXF \c VIEW
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_view->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfView was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_view->view_name);
        free (dxf_view->dictionary_owner_soft);
        free (dxf_view->dictionary_owner_hard);
        free (dxf_view);
        dxf_view = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
