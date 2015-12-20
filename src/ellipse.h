/*!
 * \file ellipse.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF ellipse entity (\c ELLIPSE).
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


#ifndef LIBDXF_SRC_ELLIPSE_H
#define LIBDXF_SRC_ELLIPSE_H


#include "global.h"
#include "point.h"


/*!
 * \brief Definition of an AutoCAD ellipse entity (\c ELLIPSE).
 *
 * This entity requires AutoCAD version R14 or higher.
 */
typedef struct
dxf_ellipse
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
                 * Elevation of the arc in the local Z-direction.\n
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
        /* Specific members for a DXF ellipse. */
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
                 * X value of the endpoint of major axis, relative to
                 * the center (in WCS). */
        double y1;
                /*!< group code = 21\n
                 * Y value of the endpoint of major axis, relative to
                 * the center (in WCS). */
        double z1;
                /*!< group code = 31\n
                 * Z value of the endpoint of major axis, relative to
                 * the center (in WCS). */
        double ratio;
                /*!< group code = 40\n
                 * ratio of minor axis to major axis. */
        double start_angle;
                /*!< group code = 41. */
        double end_angle;
                /*!< group code = 42. */
        double extr_x0;
                /*!< group code = 210\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_y0;
                /*!< group code = 220\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_z0;
                /*!< group code = 230\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 1.0. */
        struct DxfEllipse *next;
                /*!< pointer to the next DxfEllipse.\n
                 * \c NULL in the last DxfEllipse. */
} DxfEllipse;


DxfEllipse *
dxf_ellipse_new ();
DxfEllipse *
dxf_ellipse_init
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_read
(
        DxfFile *fp,
        DxfEllipse *ellipse
);
int
dxf_ellipse_write
(
        DxfFile *fp,
        DxfEllipse *ellipse
);
int
dxf_ellipse_free
(
        DxfEllipse *ellipse
);
void
dxf_ellipse_free_chain
(
        DxfEllipse *ellipses
);
int
dxf_ellipse_get_id_code
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_id_code
(
        DxfEllipse *ellipse,
        int id_code
);
char *
dxf_ellipse_get_linetype
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_linetype
(
        DxfEllipse *ellipse,
        char *linetype
);
char *
dxf_ellipse_get_layer
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_layer
(
        DxfEllipse *ellipse,
        char *layer
);
double
dxf_ellipse_get_elevation
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_elevation
(
        DxfEllipse *ellipse,
        double elevation
);
double
dxf_ellipse_get_thickness
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_thickness
(
        DxfEllipse *ellipse,
        double thickness
);
double
dxf_ellipse_get_linetype_scale
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_linetype_scale
(
        DxfEllipse *ellipse,
        double linetype_scale
);
int16_t
dxf_ellipse_get_visibility
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_visibility
(
        DxfEllipse *ellipse,
        int16_t visibility
);
int
dxf_ellipse_get_color
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_color
(
        DxfEllipse *ellipse,
        int color
);
int
dxf_ellipse_get_paperspace
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_paperspace
(
        DxfEllipse *ellipse,
        int paperspace
);
char *
dxf_ellipse_get_dictionary_owner_soft
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_dictionary_owner_soft
(
        DxfEllipse *ellipse,
        char *dictionary_owner_soft
);
char *
dxf_ellipse_get_dictionary_owner_hard
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_dictionary_owner_hard
(
        DxfEllipse *ellipse,
        char *dictionary_owner_hard
);
DxfPoint *
dxf_ellipse_get_base_point
(
        DxfEllipse *ellipse,
        int id_code,
        int inheritance
);
DxfEllipse *
dxf_ellipse_set_base_point
(
        DxfEllipse *ellipse,
        DxfPoint *point
);
DxfPoint *
dxf_ellipse_get_end_point
(
        DxfEllipse *ellipse,
        int id_code,
        int inheritance
);
DxfEllipse *
dxf_ellipse_set_end_point
(
        DxfEllipse *ellipse,
        DxfPoint *point
);
double
dxf_ellipse_get_ratio
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_radius
(
        DxfEllipse *ellipse,
        double ratio
);
double
dxf_ellipse_get_start_angle
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_start_angle
(
        DxfEllipse *ellipse,
        double start_angle
);
double
dxf_ellipse_get_end_angle
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_end_angle
(
        DxfEllipse *ellipse,
        double end_angle
);
DxfPoint *
dxf_ellipse_get_extrusion_vector_as_point
(
        DxfEllipse *ellipse
);


#endif /* LIBDXF_SRC_ELLIPSE_H */


/* EOF */
