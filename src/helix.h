/*!
 * \file helix.h
 *
 * \author Copyright (C) 2013 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF helix entity (\c HELIX).
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


#ifndef LIBDXF_SRC_HELIX_H
#define LIBDXF_SRC_HELIX_H


#include "global.h"
#include "entity.h"
#include "spline.h"


/*!
 * \brief Definition of an AutoCAD helix entity (\c HELIX).
 */
typedef struct
dxf_helix
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
        int graphics_data_size;
                /*!< group code = 92\n
                 * Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).
                 *
                 * \warning On some 64 bit workstations output is
                 * generated with group code "160", thus omitting group
                 * code "92".
                 */
        int16_t shadow_mode;
                /*!< group code = 284\n
                 * Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol> */
        char *binary_graphics_data[DXF_MAX_PARAM];
                /*!< group code = 310\n
                 * Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional). */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *material;
                /*!< group code = 347\n
                 * Hard-pointer ID/handle to material object (present if
                 * not BYLAYER). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard-owner ID/handle to owner dictionary (optional). */
        int16_t lineweight;
                /*!< group code = 370\n
                 * Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer. */
        char *plot_style_name;
                /*!< group code = 390\n
                 * Hard pointer ID / handle of PlotStyleName object. */
        long color_value;
                /*!< group code = 420\n
                 * A 24-bit color value that should be dealt with in
                 * terms of bytes with values of 0 to 255.\n
                 * The lowest byte is the blue value, the middle byte is
                 * the green value, and the third byte is the red value.\n
                 * The top byte is always 0.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data. */
        char *color_name;
                /*!< group code = 430\n
                 * Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data. */
        long transparency;
                /*!< group code = 440\n
                 * Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data. */
        /* Specific members for a DXF helix. */
        double x0;
                /*!< group code = 10\n
                 * X-value of the axis base point coordinate. */
        double y0;
                /*!< group code = 20\n
                 * Y-value of the axis base point coordinate. */
        double z0;
                /*!< group code = 30\n
                 * Z-value of the axis base point coordinate. */
        double x1;
                /*!< group code = 11\n
                 * X-value of the start point coordinate. */
        double y1;
                /*!< group code = 21\n
                 * Y-value of the start point coordinate. */
        double z1;
                /*!< group code = 31\n
                 * Z-value of the start point coordinate. */
        double x2;
                /*!< group code = 12\n
                 * X-value of the axis vector point coordinate. */
        double y2;
                /*!< group code = 22\n
                 * Y-value of the axis vector point coordinate. */
        double z2;
                /*!< group code = 32\n
                 * Z-value of the axis vector point coordinate. */
        double radius;
                /*!< group code = 40\n
                 * Radius of the arc. */
        double number_of_turns;
                /*!< group code = 41\n
                 * Number of turns. */
        double turn_height;
                /*!< group code = 42\n
                 * Turn height. */
        long major_release_number;
                /*!< group code = 90\n
                 * Major release number. */
        long maintainance_release_number;
                /*!< group code = 91\n
                 * Maintainance release number. */
        int constraint_type;
                /*!< group code = 280\n
                 * Constrain type:\n
                 * <ol>
                 * <li value = "0"> Constrain turn height.</li>
                 * <li value = "1"> Constrain turns.</li>
                 * <li value = "2"> Constrain height.</li>
                 * </ol> */
        int handedness;
                /*!< group code = 290\n
                 * Handedness:
                 * <ol>
                 * <li value = "0"> Left.</li>
                 * <li value = "1"> Right</li>
                 * </ol> */
        DxfSpline spline;
                /*!< pointer to the first DxfSpline.\n
                 * \c NULL if the last DxfSpline. */
        struct DxfHelix *next;
                /*!< pointer to the next DxfHelix.\n
                 * \c NULL in the last DxfHelix. */
} DxfHelix, * DxfHelixPtr;


DxfHelix *
dxf_helix_new ();
DxfHelix *
dxf_helix_init
(
        DxfHelix *dxf_helix
);
int
dxf_helix_read
(
        DxfFile *fp,
        DxfHelix *dxf_helix
);
int
dxf_helix_write
(
        DxfFile *fp,
        DxfHelix *dxf_helix
);
int
dxf_helix_free
(
        DxfHelix *dxf_helix
);


#endif /* LIBDXF_SRC_HELIX_H */


/* EOF */
