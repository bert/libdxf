/*!
 * \file insert.h
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Definition of a DXF insert entity (\c INSERT).
 *
 * A DXF \c INSERT entity is an insertion for a (external) \c BLOCK entity.\n
 * Whilst a \c BLOCK only resides in the block table only once as a
 * definition, an \c INSERT entity can insert blocks as singlular entities
 * and also as [rectanglar, polar] arrays in the drawing.
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

#include "global.h"

/*!
 * \brief DXF definition of an AutoCAD block or external reference insert
 * entity.
 */
typedef struct
dxf_insert
{
        int id_code;
                /*!< group code = 5. */
        char *block_name;
                /*!< group code = 2. */
        char *linetype;
                /*!< group code = 6\n
                 * optional, defaults to BYLAYER. */
        char *layer;
                /*!< group code = 8. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double thickness;
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double rel_x_scale;
                /*!< group code = 41\n
                 * optional, defaults to 1.0. */
        double rel_y_scale;
                /*!< group code = 42\n
                 * optional, defaults to 1.0. */
        double rel_z_scale;
                /*!< group code = 43\n
                 * optional, defaults to 1.0. */
        double column_spacing;
                /*!< group code = 44\n
                 * optional, defaults to 0.0. */
        double row_spacing;
                /*!< group code = 45\n
                 * optional, defaults to 0.0. */
        double rot_angle;
                /*!< group code = 50\n
                 * optional, defaults to 0.0. */
        int color;
                /*!< group code = 62\n
                 * optional, defaults to BYLAYER. */
        int attribute_follows;
                /*!< group code = 66\n
                 * optional, defaults to 0\n
                 * If the value of the "Attributes follow" flag is 1,
                 * a series of Attribute (Attrib) entities is expected to
                 * follow the Insert, terminated by a sequence end (Seqend)
                 * entity. */
        int paperspace;
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int columns;
                /*!< group code = 70\n
                 * optional, defaults to 1. */
        int rows;
                /*!< group code = 71\n
                 * optional, defaults to 1. */
} DxfInsert, * DxfInsertPtr;

/* EOF */
