/*!
 * \file seqend.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF end of sequence marker (\c SEQEND).
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


#include "seqend.h"


/*!
 * \brief Write DXF output to a file for an end of sequence marker
 * (\c SEQEND).
 *
 * No fields.\n
 * This entity marks the end of vertices (Vertex type name) for a 
 * Polyline (\c POLYLINE), a Light Wight Polyline (\c LWPOLYLINE)
 * or the end of Attribute entities (Attrib type name) for an Insert
 * entity (\c INSERT) that has Attributes (indicated by 66 group present
 * and nonzero).
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_seqend_write
(
        FILE *fp
                /*!< file pointer to output file (or device). */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_seqend_write () function.\n", __FILE__, __LINE__);
#endif
        fprintf (fp, "  0\nSEQEND\n");
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_seqend_write () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
