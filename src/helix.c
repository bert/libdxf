/*!
 * \file helix.c
 *
 * \author Copyright (C) 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF helix entity (\c HELIX).
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


#include "helix.h"


/*!
 * \brief Allocate memory for a DXF \c HELIX.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHelix *
dxf_helix_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_helix_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfHelix *dxf_helix = NULL;
        size_t size;

        size = sizeof (DxfHelix);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_helix = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_helix_new () could not allocate memory for a DxfHelix struct.\n");
                dxf_helix = NULL;
        }
        else
        {
                memset (dxf_helix, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_helix_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_helix);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HELIX
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHelix *
dxf_helix_init
(
        DxfHelix *dxf_helix
                /*!< DXF helix entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_helix_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        dxf_helix = dxf_helix_new ();
        if (dxf_helix == NULL)
        {
              fprintf (stderr, "ERROR in dxf_helix_init () could not allocate memory for a DxfHelix struct.\n");
              return (NULL);
        }
        dxf_helix->id_code = 0;
        dxf_helix->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_helix->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_helix->x0 = 0.0;
        dxf_helix->y0 = 0.0;
        dxf_helix->z0 = 0.0;
        dxf_helix->x1 = 0.0;
        dxf_helix->y1 = 0.0;
        dxf_helix->z1 = 0.0;
        dxf_helix->x2 = 0.0;
        dxf_helix->y2 = 0.0;
        dxf_helix->z2 = 0.0;
        dxf_helix->thickness = 0.0;
        dxf_helix->radius = 0.0;
        dxf_helix->number_of_turns = 0.0;
        dxf_helix->turn_height = 0.0;
        dxf_helix->linetype_scale = 0.0;
        dxf_helix->visibility = 0;
        dxf_helix->color = DXF_COLOR_BYLAYER;
        dxf_helix->paperspace = DXF_MODELSPACE;
        dxf_helix->major_release_number = 0;
        dxf_helix->maintainance_release_number = 0;
        dxf_helix->graphics_data_size = 0;
        dxf_helix->constraint_type = 0;
        dxf_helix->shadow_mode = 0;
        dxf_helix->handedness = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_helix->binary_graphics_data[i] = strdup ("");
        }
        dxf_helix->dictionary_owner_hard = strdup ("");
        dxf_helix->material = strdup ("");
        dxf_helix->dictionary_owner_soft = strdup ("");
        dxf_helix->lineweight = 0;
        dxf_helix->plot_style_name = strdup ("");
        dxf_helix->color_value = 0;
        dxf_helix->color_name = strdup ("");
        dxf_helix->transparency = 0;
        dxf_helix->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_helix_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_helix);
}


/*!
 * \brief Free the allocated memory for a DXF \c HELIX and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_helix_free
(
        DxfHelix *dxf_helix
                /*!< Pointer to the memory occupied by the DXF \c HELIX
                 * entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_helix_free () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        if (dxf_helix->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_helix_free () pointer to next DxfHelix was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_helix->linetype);
        free (dxf_helix->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_helix->binary_graphics_data[i]);
        }
        free (dxf_helix->dictionary_owner_hard);
        free (dxf_helix->material);
        free (dxf_helix->dictionary_owner_soft);
        free (dxf_helix->plot_style_name);
        free (dxf_helix->color_name);
        free (dxf_helix);
        dxf_helix = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_helix_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
