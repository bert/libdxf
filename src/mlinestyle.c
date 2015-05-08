/*!
 * \file mlinestyle.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mlinestyle object (\c MLINESTYLE).
 *
 * \version The \c MLINESTYLE object was introduced in DXF R13.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#include "mlinestyle.h"


/*!
 * \brief Allocate memory for a \c DxfMlinestyle.
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
DxfMlinestyle *
dxf_mlinestyle_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMlinestyle *mlinestyle = NULL;
        size_t size;

        size = sizeof (DxfMlinestyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mlinestyle = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfMlinestyle struct.\n")),
                  __FUNCTION__);
                mlinestyle = NULL;
        }
        else
        {
                memset (mlinestyle, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/* EOF */
