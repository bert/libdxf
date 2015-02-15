/*!
 * \file leader.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF leader entity (\c LEADER).
 *
 * \version The \c LEADER entity was introduced in DXF R13.
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


#include "leader.h"


/*!
 * \brief Allocate memory for a DXF \c LEADER.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfLeader *
dxf_leader_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLeader *leader = NULL;
        size_t size;

        size = sizeof (DxfLeader);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((leader = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfArc struct.\n")),
                  __FUNCTION__);
                leader = NULL;
        }
        else
        {
                memset (leader, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LEADER
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfLeader *
dxf_leader_init
(
        DxfLeader *leader
                /*!< pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                leader = dxf_leader_new ();
        }
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLeader struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->id_code = 0;
        leader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        leader->layer = strdup (DXF_DEFAULT_LAYER);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                leader->x0[i] = 0.0;
                leader->y0[i] = 0.0;
                leader->z0[i] = 0.0;
        }
        leader->x_extr = 0.0;
        leader->y_extr = 0.0;
        leader->z_extr = 0.0;
        leader->elevation = 0.0;
        leader->thickness = 0.0;
        leader->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        leader->visibility = DXF_DEFAULT_VISIBILITY;
        leader->color = DXF_COLOR_BYLAYER;
        leader->paperspace = DXF_MODELSPACE;
        leader->dictionary_owner_soft = strdup ("");
        leader->dictionary_owner_hard = strdup ("");
        leader->dimension_style_name = strdup ("");
        leader->text_annotation_height = 0.0;
        leader->text_annotation_width = 0.0;
        leader->arrow_head_flag = 0;
        leader->path_type = 0;
        leader->creation_flag = 0;
        leader->hookline_direction_flag = 0;
        leader->hookline_flag = 0;
        leader->number_vertices = 0;
        leader->leader_color = 0;
        leader->x1 = 0.0;
        leader->y1 = 0.0;
        leader->z1 = 0.0;
        leader->x2 = 0.0;
        leader->y2 = 0.0;
        leader->z2 = 0.0;
        leader->x3 = 0.0;
        leader->y3 = 0.0;
        leader->z3 = 0.0;
        leader->annotation_reference_hard = strdup ("");
        leader->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Free the allocated memory for a DXF \c LEADER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_leader_free
(
        DxfLeader *leader
                /*!< Pointer to the memory occupied by the DXF
                 * \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfLeader was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (leader->linetype);
        free (leader->layer);
        free (leader->dictionary_owner_soft);
        free (leader->dictionary_owner_hard);
        free (leader->dimension_style_name);
        free (leader->annotation_reference_hard);
        free (leader);
        leader = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
