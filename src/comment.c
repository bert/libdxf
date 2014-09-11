/*!
 * \file comment.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF comment entity (\c COMMENT).
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
 * For more details see http://www.autodesk.com.\n\n
 * <hr>
 */

#include "comment.h"

/*!
 * \brief Write DXF output to fp for a comment.
 *
 * The 999 group code indicates that the following line is a comment string.\n
 * DXFOUT does not currently include such groups in a DXF output file, but
 * DXFIN honors them and ignores the comments.\n
 * Thus, you can use the 999 group to include comments in a DXF file you've
 * edited.
 */
int
dxf_comment_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        char *comment_string
                /*!< comment string to be writen to fp. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        fprintf (fp, "999\n%s\n", comment_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
