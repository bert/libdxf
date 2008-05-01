/*!
 * \file layer.
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Definition of a DXF layer entity.
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

#include "global.h"

/*!
 * \brief DXF definition of an AutoCAD layer entity.
 *
 * Xref-dependent layers are to be written to an output file during DXFOUT.
 */
typedef struct
dxf_layer
{
        int id_code;
                /*!< group code = 5. */
        char *layer_name;
                /*!< group code = 2. */
        char *linetype;
                /*!< group code = 6\n
                 * For these layers, the associated linetype name in the DXF
                 * file is always CONTINUOUS. */
        int color;
                /*!< group code = 62\n
                 * if negative, layer is off. */
        int flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 0 = on and thawed\n
                 * 1 = if set, layer is frozen\n
                 * 2 = if set, layer is frozen by default in new viewports\n
                 * 4 = if set, layer is locked\n
                 * 8 = unused\n
                 * 128 = unused. */
} DxfLayer, * DxfLayerPtr;

/* EOF */
