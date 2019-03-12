/*!
 * \file rtext.c
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF rtext entity (\c RTEXT).
 *
 * \version According to DXF R15.
 * \version According to DXF R2000.
 *
 * \since Introduced in version R15.
 *
 * \deprecated As of version R2002.
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


#include "rtext.h"


/*!
 * \brief Allocate memory for a \c DxfRText.
 *
 * Fill the memory contents with zeros.
 */
DxfRText *
dxf_rtext_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfRText *rtext = NULL;
        size_t size;

        size = sizeof (DxfRText);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((rtext = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRText struct.\n")),
                  __FUNCTION__);
                rtext = NULL;
        }
        else
        {
                memset (rtext, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/* EOF */
