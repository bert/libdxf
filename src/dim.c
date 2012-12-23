/*!
 * \file dim.c
 *
 * \author Copyright (C) 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dimension entity (\c DIM).
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


#include "dim.h"


/*!
 * \brief Allocate memory for a DXF \c DIMENSION.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDimension *
dxf_dimension_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimension_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfDimension *dxf_dimension = NULL;
        size_t size;

        size = sizeof (DxfDimension);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_dimension = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_dimension_new () could not allocate memory for a DxfArc struct.\n");
                dxf_dimension = NULL;
        }
        else
        {
                memset (dxf_dimension, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimension_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_dimension);
}


/* EOF */
