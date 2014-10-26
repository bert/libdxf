/*!
 * \file style.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF (text) style entity \c STYLE.
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


#ifndef LIBDXF_SRC_STYLE_H
#define LIBDXF_SRC_STYLE_H


#include "global.h"
#include "file.h"


/*!
 * \brief DXF definition of an AutoCAD (text) style.
 *
 * A \c STYLE table item can also be used to record shape file \c LOAD
 * requests.\n
 * In this case the first bit (1) is set in the 70 group flags and only the
 * 3 group (shape filename) is meaningful (all the other groups are output).
 */
typedef struct
dxf_style
{
        int id_code;
                /*!< group code = 5. */
        char *style_name;
                /*!< group code = 2. */
        char *primary_font_filename;
                /*!< group code = 3. */
        char *big_font_filename;
                /*!< group code = 4\n
                 * blank if none. */
        double height;
                /*!< group code = 40\n
                 * 0 if not fixed. */
        double width;
                /*!< group code = 41. */
        double last_height;
                /*!< group code = 42. */
        double oblique_angle;
                /*!< group code = 50. */
        int flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 1 = loads a shape file, only the primary_font_filename
                 *     (group code = 3) is relevant\n
                 * 4 = text is vertical oriented\n
                 * 16 = if set, table entry is externally dependent on an
                 *      Xref\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved\n
                 * 64 = if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.\n
                 * This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n */
        int text_generation_flag;
                /*!< group code = 71\n
                 * bit coded:\n
                 * 2 = text is backward (mirrored in X)\n
                 * 4 = text is upside down (mirrored in Y). */
} DxfStyle;


#endif /* LIBDXF_SRC_STYLE_H */


/* EOF */
