/*!
 * \file 3dface.h
 *
 * \author Copyright (C) 2010 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF 3D face entity (\c 3DFACE).
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


#ifndef _3DFACE_H
#define _3DFACE_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD 3D face entity (\c 3DFACE).
 *
 * \version According to DXF R13.
 */
typedef struct
dxf_3dface
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< group code = 5\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        char *linetype;
                /*!< group code = 6\n
                 * The linetype of the entity.\n
                 * Defaults to \c BYLAYER if omitted in the DXF file. */
        char *layer;
                /*!< group code = 8\n
                 * Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given. */
        double elevation;
                /*!< group code = 38\n
                 * Elevation of the 3dface in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default). */
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the 3dface in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if omitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        /* Specific members for a DXF 3D face. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double x1;
                /*!< group code = 11\n
                 * alignment point. */
        double y1;
                /*!< group code = 21\n
                 * alignment point. */
        double z1;
                /*!< group code = 31\n
                 * alignment point. */
        double x2;
                /*!< group code = 12\n
                 * alignment point. */
        double y2;
                /*!< group code = 22\n
                 * alignment point. */
        double z2;
                /*!< group code = 32\n
                 * alignment point. */
        double x3;
                /*!< group code = 13\n
                 * alignment point. */
        double y3;
                /*!< group code = 23\n
                 * alignment point. */
        double z3;
                /*!< group code = 33\n
                 * alignment point. */
        int flag;
                /*!< group code = 70\n
                 * optional, defaults to 0\n
                 * bit coded:\n
                 * <ol>
                 * <li value = "1"> First edge is invisible.</li>
                 * <li value = "2"> Second edge is invisible.</li>
                 * <li value = "4"> Third edge is invisible.</li>
                 * <li value = "8"> Fourth edge is invisible.</li>
                 * </ol> */
        struct Dxf3dface *next;
                /*!< pointer to the next Dxf3dface.\n
                 * \c NULL in the last Dxf3dface. */
} Dxf3dface, * Dxf3dfacePtr;


Dxf3dface *
dxf_3dface_new ();
Dxf3dface *
dxf_3dface_init
(
        Dxf3dface *dxf_3dface
);
int
dxf_3dface_read
(
        DxfFile *fp,
        Dxf3dface *dxf_3dface
);
int
dxf_3dface_write
(
        DxfFile *fp,
        Dxf3dface *dxf_3dface
);
int
dxf_3dface_free
(
        Dxf3dface *dxf_3dface
);


#endif /* _3DFACE_H */


/* EOF */
