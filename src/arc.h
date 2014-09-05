/*!
 * \file arc.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF arc entity (\c ARC).
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


#ifndef _ARC_H
#define _ARC_H


#include "global.h"
#include "entity.h"


/*!
 * \brief Definition of an AutoCAD arc entity (\c ARC).
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_arc
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
                 * Defaults to \c BYLAYER if ommitted in the DXF file. */
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
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        /* Specific members for a DXF arc. */
        double x0;
                /*!< group code = 10\n
                 * X-value of the starting point coordinate. */
        double y0;
                /*!< group code = 20\n
                 * Y-value of the starting point coordinate. */
        double z0;
                /*!< group code = 30\n
                 * Z-value of the starting point coordinate. */
        double extr_x0;
                /*!< group code = 210\n
                 * X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double extr_y0;
                /*!< group code = 220\n
                 * Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double extr_z0;
                /*!< group code = 230\n
                 * Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file. */
        double radius;
                /*!< group code = 40\n
                 * Radius of the arc. */
        double start_angle;
                /*!< group code = 50\n
                 * Start angle of the arc. */
        double end_angle;
                /*!< group code = 51\n
                 * End angle of the arc. */
        struct DxfArc *next;
                /*!< pointer to the next DxfArc.\n
                 * \c NULL in the last DxfArc. */
} DxfArc, * DxfArcPtr;


DxfArc *
dxf_arc_new ();
DxfArc *
dxf_arc_init
(
        DxfArc *dxf_arc
);
int
dxf_arc_read
(
        DxfFile *fp,
        DxfArc *dxf_arc
);
int dxf_arc_write
(
        DxfFile *fp,
        DxfArc *dxf_arc
);
int dxf_arc_free (DxfArc *dxf_arc);


#endif /* _ARC_H */


/* EOF */
