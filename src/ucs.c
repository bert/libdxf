/*!
 * \file ucs.c
 *
 * \author Copyright (C) 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF User Coordinate System entity (\c UCS).
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


#include "ucs.h"


/*!
 * \brief Allocate memory for a DXF \c UCS.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfUcs *
dxf_ucs_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfUcs *dxf_ucs = NULL;
        size_t size;

        size = sizeof (DxfUcs);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_ucs = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfUcs struct.\n")),
                  __FUNCTION__);
                dxf_ucs = NULL;
        }
        else
        {
                memset (dxf_ucs, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ucs);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c UCS
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfUcs *
dxf_ucs_init
(
        DxfUcs *dxf_ucs
                /*!< DXF ucs entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_ucs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ucs = dxf_ucs_new ();
        }
        if (dxf_ucs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfUcs struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_ucs->id_code = 0;
        dxf_ucs->UCS_name = strdup ("");
        dxf_ucs->x_origin = 0.0;
        dxf_ucs->y_origin = 0.0;
        dxf_ucs->z_origin = 0.0;
        dxf_ucs->x_X_dir = 0.0;
        dxf_ucs->y_X_dir = 0.0;
        dxf_ucs->z_X_dir = 0.0;
        dxf_ucs->x_Y_dir = 0.0;
        dxf_ucs->y_Y_dir = 0.0;
        dxf_ucs->z_Y_dir = 0.0;
        dxf_ucs->flag = 0;
        dxf_ucs->dictionary_owner_soft = strdup ("");
        dxf_ucs->dictionary_owner_hard = strdup ("");
        dxf_ucs->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ucs);
}


/*!
 * \brief Free the allocated memory for a DXF \c UCS and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ucs_free
(
        DxfUcs *dxf_ucs
                /*!< Pointer to the memory occupied by the DXF \c UCS
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_ucs->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfUcs was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_ucs->UCS_name);
        free (dxf_ucs->dictionary_owner_soft);
        free (dxf_ucs->dictionary_owner_hard);
        free (dxf_ucs);
        dxf_ucs = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
