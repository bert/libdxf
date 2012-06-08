/*!
 * \file ltype.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF ltype entity.
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


#ifndef _LTYPE_H
#define _LTYPE_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD linetype.
 */
typedef struct
dxf_ltype
{
        int id_code;
                /*!< group code = 5. */
        char *linetype_name;
                /*!< group code = 2. */
        char *description;
                /*!< group code = 3. */
        double total_pattern_length;
                /*!< group code = 40. */
        double dash_length[DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS];
                /*!< group code = 49. */
        int flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 16 = if set, table entry is externally dependent on an
                 *      Xref\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved\n
                 * 64 = if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.\n
                 * This flag is for the benefit of AutoCAD commands; it can
                 * be ignored by most programs that read DXF files, and need
                 * not be set by programs that write DXF files. */
        int alignment;
                /*!< group code = 72\n
                 * always 65; ASCII code for 'A'. */
        int number_of_dash_length_items;
                /*!< group code = 73. */
} DxfLType, * DxfLTypePtr;


DxfLType *
dxf_ltype_new ();


#endif /* _LTYPE_H */


/* EOF */
