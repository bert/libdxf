/*!
 * \file spatial_index.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF spatial_index object (\c SPATIAL_INDEX).
 *
 * \version The \c SPATIAL_INDEX object was introduced in DXF R14.
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


#include "spatial_index.h"


/*!
 * \brief Allocate memory for a \c DxfSpatialIndex.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfSpatialIndex *
dxf_spatial_index_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSpatialIndex *spatial_index = NULL;
        size_t size;

        size = sizeof (DxfSpatialIndex);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((spatial_index = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpatialIndex struct.\n")),
                  __FUNCTION__);
                spatial_index = NULL;
        }
        else
        {
                memset (spatial_index, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SPATIAL_INDEX
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
DxfSpatialIndex *
dxf_spatial_index_init
(
        DxfSpatialIndex *spatial_index
                /*!< DXF \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int JD;
        float fraction_day;
        time_t now;

        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spatial_index = dxf_spatial_index_new ();
        }
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpatialIndex struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_index->id_code = 0;
        spatial_index->dictionary_owner_soft = strdup ("");
        spatial_index->dictionary_owner_hard = strdup ("");
        if (time (&now) != (time_t)(-1))
        {
                struct tm *current_time = localtime (&now);

                /* Transform the current local gregorian date in a julian date.*/
                JD = current_time->tm_mday - 32075 + 1461 * (current_time->tm_year + 6700 + (current_time->tm_mon - 13) / 12) / 4 + 367 * (current_time->tm_mon - 1 - (current_time->tm_mon - 13) / 12 * 12) / 12 - 3 * ((current_time->tm_year + 6800 + (current_time->tm_mon - 13) / 12) / 100) / 4;
                /* Transform the current local clock time in fraction of day.*/
                fraction_day = (current_time->tm_hour + (current_time->tm_min / 60.0) + (current_time->tm_sec / 3600.0)) / 24.0;
                spatial_index->time_stamp = (double) (JD + fraction_day);
        }
        else spatial_index->time_stamp = 0.0;
        spatial_index->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Free the allocated memory for a DXF \c SPATIAL_INDEX and all it's
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
dxf_spatial_index_free
(
        DxfSpatialIndex *spatial_index
                /*!< Pointer to the memory occupied by the DXF
                 * \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfSpatialIndex was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (spatial_index->dictionary_owner_soft);
        free (spatial_index->dictionary_owner_hard);
        free (spatial_index);
        spatial_index = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
