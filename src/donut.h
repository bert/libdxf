/*!
 * \file donut.h
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a libDXF donut entity.
 *
 * \warning This is not an official AutoCAD entity.
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


#ifndef LIBDXF_SRC_DONUT_H
#define LIBDXF_SRC_DONUT_H


#include "global.h"
#include "point.h"
#include "polyline.h"
#include "vertex.h"
#include "seqend.h"


/*!
 * \brief Definition of a libDXF donut entity.
 *
 * A libDXF donut is a typical convenience struct.
 *
 * \warning This is not an official AutoCAD entity.
 */
typedef struct
dxf_donut_struct
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double elevation;
                /*!< Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a libDXF donut. */
        DxfPoint *p0;
                /*!< Insertion point for the center of the donut.\n
                 * Group codes = 10, 20 and 30.*/
        double outside_diameter;
                /*!< Outside diameter. */
        double inside_diameter;
                /*!< Inside diameter. */
        struct DxfDonut *next;
                /*!< Pointer to the next DxfDonut.\n
                 * \c NULL in the last DxfDonut. */
} DxfDonut;


DxfDonut *
dxf_donut_new ();
DxfDonut *
dxf_donut_init
(
        DxfDonut *donut
);
int
dxf_donut_write
(
        DxfFile *fp,
        DxfDonut *donut
);
int
dxf_donut_free
(
        DxfDonut *donut
);
void
dxf_donut_free_chain
(
        DxfDonut *donuts
);
int
dxf_donut_get_id_code
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_id_code
(
        DxfDonut *donut,
        int id_code
);
char *
dxf_donut_get_linetype
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_linetype
(
        DxfDonut *donut,
        char *linetype
);
char *
dxf_donut_get_layer
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_layer
(
        DxfDonut *donut,
        char *layer
);
double
dxf_donut_get_elevation
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_elevation
(
        DxfDonut *donut,
        double elevation
);
double
dxf_donut_get_thickness
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_thickness
(
        DxfDonut *donut,
        double thickness
);
double
dxf_donut_get_linetype_scale
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_linetype_scale
(
        DxfDonut *donut,
        double linetype_scale
);
int16_t
dxf_donut_get_visibility
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_visibility
(
        DxfDonut *donut,
        int16_t visibility
);
int
dxf_donut_get_color
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_color
(
        DxfDonut *donut,
        int color
);
int
dxf_donut_get_paperspace
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_paperspace
(
        DxfDonut *donut,
        int paperspace
);
char *
dxf_donut_get_dictionary_owner_soft
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_dictionary_owner_soft
(
        DxfDonut *donut,
        char *dictionary_owner_soft
);
char *
dxf_donut_get_dictionary_owner_hard
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_dictionary_owner_hard
(
        DxfDonut *donut,
        char *dictionary_owner_hard
);
DxfPoint *
dxf_donut_get_p0
(
        DxfDonut *donut
);
DxfDonut *
dxf_donut_set_p0
(
        DxfDonut *donut,
        DxfPoint *p0
);
double
dxf_donut_get_x0
(
        DxfDonut *donut
);


#endif /* LIBDXF_SRC_DONUT_H */


/* EOF */

