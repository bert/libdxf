/*!
 * \file spatial_filter.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF spatial_filter object (\c SPATIAL_FILTER).
 *
 * \version The \c SPATIAL_FILTER object was introduced in DXF R14.
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


#include "spatial_filter.h"


/*!
 * \brief Allocate memory for a \c DxfSpatialFilter.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfSpatialFilter *
dxf_spatial_filter_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSpatialFilter *spatial_filter = NULL;
        size_t size;

        size = sizeof (DxfSpatialFilter);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((spatial_filter = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpatialFilter struct.\n")),
                  __FUNCTION__);
                spatial_filter = NULL;
        }
        else
        {
                memset (spatial_filter, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SPATIAL_FILTER
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfSpatialFilter *
dxf_spatial_filter_init
(
        DxfSpatialFilter *spatial_filter
                /*!< DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spatial_filter = dxf_spatial_filter_new ();
        }
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpatialFilter struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->id_code = 0;
        spatial_filter->dictionary_owner_soft = strdup ("");
        spatial_filter->dictionary_owner_hard = strdup ("");
        spatial_filter->x1 = 0.0;
        spatial_filter->y1 = 0.0;
        spatial_filter->z1 = 0.0;
        spatial_filter->front_clipping_plane_distance = 0.0;
        spatial_filter->back_clipping_plane_distance = 0.0;
        spatial_filter->number_of_points = 0;
        spatial_filter->clip_boundary_display_flag = 0;
        spatial_filter->front_clipping_plane_flag = 0;
        spatial_filter->back_clipping_plane_flag = 0;
        spatial_filter->extr_x0 = 0.0;
        spatial_filter->extr_y0 = 0.0;
        spatial_filter->extr_z0 = 0.0;
        for (i = 0; i < 12; i++)
        {
                spatial_filter->inverse_block_transformation[i] = 0.0;
                spatial_filter->block_transformation[i] = 0.0;
        }
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                spatial_filter->x0[i] = 0.0;
                spatial_filter->y0[i] = 0.0;
        }
        spatial_filter->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Free the allocated memory for a DXF \c SPATIAL_FILTER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
int
dxf_spatial_filter_free
(
        DxfSpatialFilter *spatial_filter
                /*!< Pointer to the memory occupied by the DXF
                 * \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfSpatialFilter was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (spatial_filter->dictionary_owner_soft);
        free (spatial_filter->dictionary_owner_hard);
        free (spatial_filter);
        spatial_filter = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
