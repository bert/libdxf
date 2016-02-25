/*!
 * \file spline.h
 *
 * \author Copyright (C) 2013 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 *
 * \version According to DXF R10 (backward compatibility). 
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_spline_struct
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
                /*!< Elevation of the spline in the local Z-direction.\n
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
        int graphics_data_size;
                /*!< Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).\n
                 * Group code = 92. */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284. */
        char *binary_graphics_data[DXF_MAX_PARAM];
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390. */
        long color_value;
                /*!< A 24-bit color value that should be dealt with in
                 * terms of bytes with values of 0 to 255.\n
                 * The lowest byte is the blue value, the middle byte is
                 * the green value, and the third byte is the red value.\n
                 * The top byte is always 0.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 420. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430. */
        long transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440. */
        /* Specific members for a DXF spline. */
        double x0[DXF_MAX_PARAM];
                /*!< X-value of the control point coordinate
                 * (multiple entries).\n
                 * Group code = 10. */
        double y0[DXF_MAX_PARAM];
                /*!< Y-value of the control point coordinate
                 * (multiple entries).\n
                 * Group code = 20. */
        double z0[DXF_MAX_PARAM];
                /*!< Z-value of the control point coordinate
                 * (multiple entries).\n
                 * Group code = 30. */
        double x1[DXF_MAX_PARAM];
                /*!< X-value of the fit point coordinate
                 * (multiple entries).\n
                 * Group code = 11. */
        double y1[DXF_MAX_PARAM];
                /*!< Y-value of the fit point coordinate
                 * (multiple entries).\n
                 * Group code = 21. */
        double z1[DXF_MAX_PARAM];
                /*!< Z-value of the fit point coordinate
                 * (multiple entries).\n
                 * Group code = 31. */
        double x2;
                /*!< X-value of the start tangent,
                 * may be omitted (in WCS).\n
                 * Group code = 12. */
        double y2;
                /*!< Y-value of the start tangent,
                 * may be omitted (in WCS).\n
                 * Group code = 22. */
        double z2;
                /*!< Z-value of the start tangent,
                 * may be omitted (in WCS).\n
                 * Group code = 32. */
        double x3;
                /*!< X-value of the end tangent,
                 * may be omitted (in WCS).\n
                 * Group code = 13. */
        double y3;
                /*!< Y-value of the end tangent,
                 * may be omitted (in WCS).\n
                 * Group code = 23. */
        double z3;
                /*!< Z-value of the end tangent,
                 * may be omitted (in WCS).\n
                 * Group code = 33. */
        double knot_value[DXF_MAX_PARAM];
                /*!< Knot value (one entry per knot, multiple entries).\n
                 * Group code = 40. */
        double weight_value[DXF_MAX_PARAM];
                /*!< Weight (if not 1); with multiple group pairs, they
                 * are present if all are not 1.\n
                 * Group code = 41. */
        double knot_tolerance;
                /*!< Knot tolerance (default = 0.0000001).\n
                 * Group code = 42. */
        double control_point_tolerance;
                /*!< Control-point tolerance (default = 0.0000001).\n
                 * Group code = 43. */
        double fit_tolerance;
                /*!< Fit tolerance (default = 0.0000000001).\n
                 * Group code = 44. */
        int flag;
                /*!< Spline flag (bit coded):\n
                 * <ol>
                 * <li value = "1"> Closed spline.</li>
                 * <li value = "2"> Periodic spline.</li>
                 * <li value = "4"> Rational spline.</li>
                 * <li value = "8"> Planar.</li>
                 * <li value = "16"> Linear (planar bit is also set).</li>
                 * </ol>\n
                 * Group code = 70. */
        int degree;
                /*!< Degree of the spline curve.\n
                 * Group code = 71. */
        int number_of_knots;
                /*!< Number of knots.\n
                 * Group code = 72. */
        int number_of_control_points;
                /*!< Number of control points.\n
                 * Group code = 73. */
        int number_of_fit_points;
                /*!< group code = 74\n
                 * Number of fit points (if any).*/
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        struct DxfSpline *next;
                /*!< Pointer to the next DxfSpline.\n
                 * \c NULL in the last DxfSpline. */
} DxfSpline;


DxfSpline *
dxf_spline_new ();
DxfSpline *
dxf_spline_init
(
        DxfSpline *spline
);
DxfSpline *
dxf_spline_read
(
        DxfFile *fp,
        DxfSpline *spline
);
int
dxf_spline_write
(
        DxfFile *fp,
        DxfSpline *spline
);
int
dxf_spline_free
(
        DxfSpline *spline
);
void
dxf_spline_free_chain
(
        DxfSpline *splines
);
int
dxf_spline_get_id_code
(
        DxfSpline *spline
);
DxfSpline *
dxf_spline_set_id_code
(
        DxfSpline *spline,
        int id_code
);
char *
dxf_spline_get_linetype
(
        DxfSpline *spline
);
DxfSpline *
dxf_spline_set_linetype
(
        DxfSpline *spline,
        char *linetype
);
char *
dxf_spline_get_layer
(
        DxfSpline *spline
);
DxfSpline *
dxf_spline_set_layer
(
        DxfSpline *spline,
        char *layer
);
double
dxf_spline_get_elevation
(
        DxfSpline *spline
);


#endif /* LIBDXF_SRC_SPLINE_H */


/* EOF */

