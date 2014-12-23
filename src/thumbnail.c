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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_thumbnail_write () function.\n", __FILE__, __LINE__);
#endif
        /*!
         * \todo Add code here
         */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_thumbnail_write () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
