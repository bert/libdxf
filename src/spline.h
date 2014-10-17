/*!
 * \file spline.h
 *
 * \author Copyright (C) 2013 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF spline entity (\c SPLINE).
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


#ifndef LIBDXF_SRC_SPLINE_H
#define LIBDXF_SRC_SPLINE_H


#include "global.h"


/*!
 * \brief Definition of an AutoCAD spline entity (\c SPLINE).
 */
typedef struct
dxf_spline
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
                 * binary chunk records (optional). */
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
        /* Specific members for a DXF spline. */
        double x0[DXF_MAX_PARAM];
                /*!< group code = 10\n
                 * X-value of the control point coordinate
                 * (multiple entries). */
        double y0[DXF_MAX_PARAM];
                /*!< group code = 20\n
                 * Y-value of the control point coordinate
                 * (multiple entries). */
        double z0[DXF_MAX_PARAM];
                /*!< group code = 30\n
                 * Z-value of the control point coordinate
                 * (multiple entries). */
        double x1[DXF_MAX_PARAM];
                /*!< group code = 11\n
                 * X-value of the fit point coordinate
                 * (multiple entries). */
        double y1[DXF_MAX_PARAM];
                /*!< group code = 21\n
                 * Y-value of the fit point coordinate
                 * (multiple entries). */
        double z1[DXF_MAX_PARAM];
                /*!< group code = 31\n
                 * Z-value of the fit point coordinate
                 * (multiple entries). */
        double x2;
                /*!< group code = 12\n
                 * X-value of the start tangent, may be omitted (in WCS). */
        double y2;
                /*!< group code = 22\n
                 * Y-value of the start tangent, may be omitted (in WCS). */
        double z2;
                /*!< group code = 32\n
                 * Z-value of the start tangent, may be omitted (in WCS). */
        double x3;
                /*!< group code = 13\n
                 * X-value of the end tangent, may be omitted (in WCS). */
        double y3;
                /*!< group code = 23\n
                 * Y-value of the end tangent, may be omitted (in WCS). */
        double z3;
                /*!< group code = 33\n
                 * Z-value of the end tangent, may be omitted (in WCS). */
        double knot_value[DXF_MAX_PARAM];
                /*!< group code = 40\n
                 * Knot value (one entry per knot, multiple entries). */
        double weight_value[DXF_MAX_PARAM];
                /*!< group code = 41\n
                 * Weight (if not 1); with multiple group pairs, they
                 * are present if all are not 1. */
        double knot_tolerance;
                /*!< group code = 42\n
                 * Knot tolerance (default = 0.0000001).*/
        double control_point_tolerance;
                /*!< group code = 43\n
                 * Control-point tolerance (default = 0.0000001).*/
        double fit_tolerance;
                /*!< group code = 44\n
                 * Fit tolerance (default = 0.0000000001).*/
        int flag;
                /*!< group code = 70\n
                 * Spline flag (bit coded):\n
                 * <ol>
                 * <li value = "1"> Closed spline.</li>
                 * <li value = "2"> Periodic spline.</li>
                 * <li value = "4"> Rational spline.</li>
                 * <li value = "8"> Planar.</li>
                 * <li value = "16"> Linear (planar bit is also set).</li>
                 * </ol> */
        int degree;
                /*!< group code = 71\n
                 * Degree of the spline curve.*/
        int number_of_knots;
                /*!< group code = 72\n
                 * Number of knots.*/
        int number_of_control_points;
                /*!< group code = 73\n
                 * Number of control points.*/
        int number_of_fit_points;
                /*!< group code = 74\n
                 * Number of fit points (if any).*/
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
        struct DxfSpline *next;
                /*!< pointer to the next DxfSpline.\n
                 * \c NULL in the last DxfSpline. */
} DxfSpline;


DxfSpline *
dxf_spline_new ();
DxfSpline *
dxf_spline_init
(
        DxfSpline *dxf_spline
);
int
dxf_spline_read
(
        DxfFile *fp,
        DxfSpline *dxf_spline
);
int
dxf_spline_write
(
        DxfFile *fp,
        DxfSpline *dxf_spline
);
int
dxf_spline_free
(
        DxfSpline *dxf_spline
);


#endif /* LIBDXF_SRC_SPLINE_H */


/* EOF */

