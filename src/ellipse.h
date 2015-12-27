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
        /* Specific members for a DXF ellipse. */
        double x0;
                /*!< X value of the center point.\n
                 * Group code = 10. */
        double y0;
                /*!< Y value of the center point.\n
                 * Group code = 20. */
        double z0;
                /*!< Z value of the center point.\n
                 * Group code = 30. */
        double x1;
                /*!< X value of the endpoint of major axis, relative to
                 * the center (in WCS).\n
                 * Group code = 11. */
        double y1;
                /*!< Y value of the endpoint of major axis, relative to
                 * the center (in WCS).\n
                 * Group code = 21. */
        double z1;
                /*!< Z value of the endpoint of major axis, relative to
                 * the center (in WCS).\n
                 * Group code = 31. */
        double ratio;
                /*!< Ratio of minor axis to major axis.\n
                 * Group code = 40. */
        double start_angle;
                /*!< Group code = 41. */
        double end_angle;
                /*!< Group code = 42. */
        double extr_x0;
                /*!< X value of the extrusion direction.\n
                 * Optional, if ommited defaults to 0.0.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y value of the extrusion direction.\n
                 * Optional, if ommited defaults to 0.0.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z value of the extrusion direction.\n
                 * Optional, if ommited defaults to 1.0.\n
                 * Group code = 230. */
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
dxf_ellipse_get_center_point
(
        DxfEllipse *ellipse,
        int id_code,
        int inheritance
);
DxfEllipse *
dxf_ellipse_set_center_point
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
DxfEllipse *
dxf_ellipse_set_extrusion_vector
(
        DxfEllipse *ellipse,
        double extr_x0,
        double extr_y0,
        double extr_z0
);
DxfEllipse *
dxf_ellipse_get_next
(
        DxfEllipse *ellipse
);
DxfEllipse *
dxf_ellipse_set_next
(
        DxfEllipse *ellipse,
        DxfEllipse *next
);


#endif /* LIBDXF_SRC_ELLIPSE_H */


/* EOF */
