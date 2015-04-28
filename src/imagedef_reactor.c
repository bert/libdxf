/*!
 * \file imagedef_reactor.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF imagedef_reactor object (\c IMAGEDEF_REACTOR).
 *
 * \version The \c IMAGEDEF_REACTOR object was introduced in DXF R14.
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


#include "imagedef_reactor.h"


/*!
 * \brief Allocate memory for a \c DxfImagedefReactor.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfImagedefReactor *
dxf_imagedef_reactor_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfImagedefReactor *imagedef_reactor = NULL;
        size_t size;

        size = sizeof (DxfImagedefReactor);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((imagedef_reactor = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfImagedefReactor struct.\n")),
                  __FUNCTION__);
                imagedef_reactor = NULL;
        }
        else
        {
                memset (imagedef_reactor, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (imagedef_reactor);
}


/* EOF*/
