/*!
 * \file ucs.h
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF User Coordinate System entity (\c UCS).
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


#ifndef _UCS_H
#define _UCS_H


#include "global.h"
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD User Coordinate System entity.
 */
typedef struct
dxf_ucs
{
        int id_code;
                /*!< group code = 5. */
        char *UCS_name;
                /*!< group code = 2. */
        double x_origin;
                /*!< group code = 10\n
                 * base point. */
        double y_origin;
                /*!< group code = 20\n
                 * base point. */
        double z_origin;
                /*!< group code = 30\n
                 * base point. */
        double x_X_dir;
                /*!< group code = 11\n
                 * X axis direction. */
        double y_X_dir;
                /*!< group code = 21\n
                 * X axis direction. */
        double z_X_dir;
                /*!< group code = 31\n
                 * X axis direction. */
        double x_Y_dir;
                /*!< group code = 12\n
                 * Y axis direction. */
        double y_Y_dir;
                /*!< group code = 22\n
                 * Y axis direction. */
        double z_Y_dir;
                /*!< group code = 32\n
                 * Y axis direction. */
        int flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 16 = if set, table entry is externally dependent on an
                 *         Xref\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *         dependent Xref has been successfully resolved\n
                 * 64 = if set, the table entry was referenced by at least
                 *         one entity in the drawing the last time the drawing
                 *         was edited.\n This flag is for the benefit of AutoCAD
                 *         commands; it can be ignored by most programs that
                 *         read DXF files, and need not be set by programs that
                 *         write DXF files.\n */
} DxfUcs, * DxfUcsPtr;


#endif /* _UCS_H */


/* EOF */
