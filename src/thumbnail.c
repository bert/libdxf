/*!
 * \file thumbnail.c
 *
 * \author Copyright (C) 2009 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF thumbnail.
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


#include "thumbnail.h"


/*!
 * \brief Allocate memory for a DXF \c THUMBNAILIMAGE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfThumbnail *
dxf_thumbnail_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfThumbnail *dxf_thumbnail = NULL;
        size_t size;

        size = sizeof (DxfThumbnail);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_thumbnail = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfThumbnail struct.\n")),
                  __FUNCTION__);
                dxf_thumbnail = NULL;
        }
        else
        {
                memset (dxf_thumbnail, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_thumbnail);
}


/*!
 * \brief Write a thumbnail to a DXF file.
 */
int
dxf_thumbnail_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfThumbnail *dxf_thumbnail
                /*!< the thumbnail to write to the output file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /*!
         * \todo Add code here
         */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
