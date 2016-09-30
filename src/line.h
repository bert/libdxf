/*!
 * \file line.h
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF line entity (\c LINE).
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


#ifndef LIBDXF_SRC_LINE_H
#define LIBDXF_SRC_LINE_H


#include "global.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD line entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_line
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
                 * to DXF version R12, or DXF_FLATLAND equals 0\n
                 * (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int16_t visibility;
                /*!< Object visibility (optional): 0 = Visible; 1 = Invisible.\n
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
        /* Specific members for a DXF line. */
        double x0;
                /*!< X value of the start point.\n
                 * Group code = 10. */
        double y0;
                /*!< Y value of the start point.\n
                 * Group code = 20. */
        double z0;
                /*!< Z value of the start point.\n
                 * Group code = 30. */
        double x1;
                /*!< X value of the end point.\n
                 * Group code = 11. */
        double y1;
                /*!< Y value of the end point.\n
                 * Group code = 21. */
        double z1;
                /*!< Z value of the end point.\n
                 * Group code = 31. */
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
        struct DxfLine *next;
                /*!< pointer to the next DxfLine.\n
                 * \c NULL in the last DxfLine. */
} DxfLine;


DxfLine *
dxf_line_new ();
DxfLine *
dxf_line_init
(
        DxfLine *line
);
DxfLine *
dxf_line_read
(
        DxfFile *fp,
        DxfLine *line
);
int
dxf_line_write
(
        DxfFile *fp,
        DxfLine *line
);
int
dxf_line_free
(
        DxfLine *line
);
void
dxf_line_free_chain
(
        DxfLine *lines
);
int
dxf_line_get_id_code
(
        DxfLine *line
);
DxfLine *
dxf_line_set_id_code
(
        DxfLine *line,
        int id_code
);
char *
dxf_line_get_linetype
(
        DxfLine *line
);
DxfLine *
dxf_line_set_linetype
(
        DxfLine *line,
        char *linetype
);
char *
dxf_line_get_layer
(
        DxfLine *line
);
DxfLine *
dxf_line_set_layer
(
        DxfLine *line,
        char *layer
);
double
dxf_line_get_elevation
(
        DxfLine *line
);
DxfLine *
dxf_line_set_elevation
(
        DxfLine *line,
        double elevation
);
double
dxf_line_get_thickness
(
        DxfLine *line
);
DxfLine *
dxf_line_set_thickness
(
        DxfLine *line,
        double thickness
);
double
dxf_line_get_linetype_scale
(
        DxfLine *line
);
DxfLine *
dxf_line_set_linetype_scale
(
        DxfLine *line,
        double linetype_scale
);
int16_t
dxf_line_get_visibility
(
        DxfLine *line
);
DxfLine *
dxf_line_set_visibility
(
        DxfLine *line,
        int16_t visibility
);
int
dxf_line_get_color
(
        DxfLine *line
);
DxfLine *
dxf_line_set_color
(
        DxfLine *line,
        int color
);
int
dxf_line_get_paperspace
(
        DxfLine *line
);
DxfLine *
dxf_line_set_paperspace
(
        DxfLine *line,
        int paperspace
);
char *
dxf_line_get_dictionary_owner_soft
(
        DxfLine *line
);
DxfLine *
dxf_line_set_dictionary_owner_soft
(
        DxfLine *line,
        char *dictionary_owner_soft
);
char *
dxf_line_get_dictionary_owner_hard
(
        DxfLine *line
);
DxfLine *
dxf_line_set_dictionary_owner_hard
(
        DxfLine *line,
        char *dictionary_owner_hard
);
DxfPoint *
dxf_line_get_start_point
(
        DxfLine *line,
        int id_code,
        int inheritance
);
DxfLine *
dxf_line_set_start_point
(
        DxfLine *line,
        DxfPoint *point
);
DxfPoint *
dxf_line_get_end_point
(
        DxfLine *line,
        int id_code,
        int inheritance
);
DxfLine *
dxf_line_set_end_point
(
        DxfLine *line,
        DxfPoint *point
);
DxfPoint *
dxf_line_get_extrusion_vector_as_point
(
        DxfLine *line
);
DxfLine *
dxf_line_set_extrusion_vector
(
        DxfLine *line,
        double extr_x0,
        double extr_y0,
        double extr_z0
);
DxfLine *
dxf_line_get_next
(
        DxfLine *line
);
DxfLine *
dxf_line_set_next
(
        DxfLine *line,
        DxfLine *next
);
DxfPoint *
dxf_line_calculate_mid_point
(
        DxfLine *line,
        int id_code,
        int inheritance
);
double
dxf_line_calculate_length
(
        DxfLine *line
);
DxfLine *
dxf_line_create_from_points
(
        DxfPoint *p1,
        DxfPoint *p2,
        int id_code,
        int inheritance
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LINE_H */


/* EOF */
