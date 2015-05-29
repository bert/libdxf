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


/* EOF*/
