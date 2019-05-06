/*!
 * \file spline.h
 *
 * \author Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018, 2019
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF spline entity (\c SPLINE).
 *
 * \version According to DXF R10 (backward compatibility). 
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
#include "binary_graphics_data.h"
#include "point.h"
#include "util.h"


#ifdef __cplusplus
extern "C" {
#endif


#define DXF_SPLINE_KNOT_TOLERANCE_DEFAULT 0.0000001
#define DXF_SPLINE_CONTROL_POINT_TOLERANCE_DEFAULT 0.0000001
#define DXF_SPLINE_FIT_TOLERANCE_DEFAULT 0.0000000001


/*!
 * \brief Definition of an AutoCAD spline entity (\c SPLINE).
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
        int16_t color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int16_t paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67. */
        int32_t graphics_data_size;
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
        DxfBinaryGraphicsData *binary_graphics_data;
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
        int32_t color_value;
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
        int32_t transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440. */
        /* Specific members for a DXF spline. */
        DxfPoint *p0;
                /*!< Control point (multiple entries).\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Fit point (multiple entries).\n
                 * Group codes = 11, 21 and 31.*/
        DxfPoint *p2;
                /*!< Start tangent point.\n
                 * May be omitted (in WCS).\n
                 * Group codes = 12, 22 and 32.*/
        DxfPoint *p3;
                /*!< End tangent point.\n
                 * May be omitted (in WCS).\n
                 * Group codes = 13, 23 and 33. */
        DxfDouble *knot_value;
                /*!< Knot value (one entry per knot, multiple entries).\n
                 * Group code = 40. */
        DxfDouble *weight_value;
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
        int16_t flag;
                /*!< Spline flag (bit coded):\n
                 * <ol>
                 * <li value = "1"> Closed spline.</li>
                 * <li value = "2"> Periodic spline.</li>
                 * <li value = "4"> Rational spline.</li>
                 * <li value = "8"> Planar.</li>
                 * <li value = "16"> Linear (planar bit is also set).</li>
                 * </ol>\n
                 * Group code = 70. */
        int16_t degree;
                /*!< Degree of the spline curve.\n
                 * Group code = 71. */
        int16_t number_of_knots;
                /*!< Number of knots.\n
                 * Group code = 72. */
        int16_t number_of_control_points;
                /*!< Number of control points.\n
                 * Group code = 73. */
        int16_t number_of_fit_points;
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


DxfSpline *dxf_spline_new ();
DxfSpline *dxf_spline_init (DxfSpline *spline);
DxfSpline *dxf_spline_read (DxfFile *fp, DxfSpline *spline);
int dxf_spline_write (DxfFile *fp, DxfSpline *spline);
int dxf_spline_free (DxfSpline *spline);
void dxf_spline_free_list (DxfSpline *splines);
int dxf_spline_get_id_code (DxfSpline *spline);
DxfSpline *dxf_spline_set_id_code (DxfSpline *spline, int id_code);
char *dxf_spline_get_linetype (DxfSpline *spline);
DxfSpline *dxf_spline_set_linetype (DxfSpline *spline, char *linetype);
char *dxf_spline_get_layer (DxfSpline *spline);
DxfSpline *dxf_spline_set_layer (DxfSpline *spline, char *layer);
double dxf_spline_get_elevation (DxfSpline *spline);
DxfSpline *dxf_spline_set_elevation (DxfSpline *spline, double elevation);
double dxf_spline_get_thickness (DxfSpline *spline);
DxfSpline *dxf_spline_set_thickness (DxfSpline *spline, double thickness);
double dxf_spline_get_linetype_scale (DxfSpline *spline);
DxfSpline *dxf_spline_set_linetype_scale (DxfSpline *spline, double linetype_scale);
int16_t dxf_spline_get_visibility (DxfSpline *spline);
DxfSpline *dxf_spline_set_visibility (DxfSpline *spline, int16_t visibility);
int16_t dxf_spline_get_color (DxfSpline *spline);
DxfSpline *dxf_spline_set_color (DxfSpline *spline, int16_t color);
int16_t dxf_spline_get_paperspace (DxfSpline *spline);
DxfSpline *dxf_spline_set_paperspace (DxfSpline *spline, int16_t paperspace);
int32_t dxf_spline_get_graphics_data_size (DxfSpline *spline);
DxfSpline *dxf_spline_set_graphics_data_size (DxfSpline *spline, int32_t graphics_data_size);
int16_t dxf_spline_get_shadow_mode (DxfSpline *spline);
DxfSpline *dxf_spline_set_shadow_mode (DxfSpline *spline, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_spline_get_binary_graphics_data (DxfSpline *spline);
DxfSpline *dxf_spline_set_binary_graphics_data (DxfSpline *spline, DxfBinaryGraphicsData *data);
char *dxf_spline_get_dictionary_owner_soft (DxfSpline *spline);
DxfSpline *dxf_spline_set_dictionary_owner_soft (DxfSpline *spline, char *dictionary_owner_soft);
char *dxf_spline_get_material (DxfSpline *spline);
DxfSpline *dxf_spline_set_material (DxfSpline *spline, char *material);
char *dxf_spline_get_dictionary_owner_hard (DxfSpline *spline);
DxfSpline *dxf_spline_set_dictionary_owner_hard (DxfSpline *spline, char *dictionary_owner_hard);
int16_t dxf_spline_get_lineweight (DxfSpline *spline);
DxfSpline *dxf_spline_set_lineweight (DxfSpline *spline, int16_t lineweight);
char *dxf_spline_get_plot_style_name (DxfSpline *spline);
DxfSpline *dxf_spline_set_plot_style_name (DxfSpline *spline, char *plot_style_name);
int32_t dxf_spline_get_color_value (DxfSpline *spline);
DxfSpline *dxf_spline_set_color_value (DxfSpline *spline, int32_t color_value);
char *dxf_spline_get_color_name (DxfSpline *spline);
DxfSpline *dxf_spline_set_color_name (DxfSpline *spline, char *color_name);
int32_t dxf_spline_get_transparency (DxfSpline *spline);
DxfSpline *dxf_spline_set_transparency (DxfSpline *spline, int32_t transparency);
DxfPoint *dxf_spline_get_p0 (DxfSpline *spline);
DxfSpline *dxf_spline_set_p0 (DxfSpline *spline, DxfPoint *p0);
double dxf_spline_get_x0 (DxfSpline *spline);
DxfSpline *dxf_spline_set_x0 (DxfSpline *spline, double x0);
double dxf_spline_get_y0 (DxfSpline *spline);
DxfSpline *dxf_spline_set_y0 (DxfSpline *spline, double y0);
double dxf_spline_get_z0 (DxfSpline *spline);
DxfSpline *dxf_spline_set_z0 (DxfSpline *spline, double z0);
DxfPoint *dxf_spline_get_p1 (DxfSpline *spline);
DxfSpline *dxf_spline_set_p1 (DxfSpline *spline, DxfPoint *p1);
double dxf_spline_get_x1 (DxfSpline *spline);
DxfSpline *dxf_spline_set_x1 (DxfSpline *spline, double x1);
double dxf_spline_get_y1 (DxfSpline *spline);
DxfSpline *dxf_spline_set_y1 (DxfSpline *spline, double y1);
double dxf_spline_get_z1 (DxfSpline *spline);
DxfSpline *dxf_spline_set_z1 (DxfSpline *spline, double z1);
DxfPoint *dxf_spline_get_p2 (DxfSpline *spline);
DxfSpline *dxf_spline_set_p2 (DxfSpline *spline, DxfPoint *p2);
double dxf_spline_get_x2 (DxfSpline *spline);
DxfSpline *dxf_spline_set_x2 (DxfSpline *spline, double x2);
double dxf_spline_get_y2 (DxfSpline *spline);
DxfSpline *dxf_spline_set_y2 (DxfSpline *spline, double y2);
double dxf_spline_get_z2 (DxfSpline *spline);
DxfSpline *dxf_spline_set_z2 (DxfSpline *spline, double z2);
DxfPoint *dxf_spline_get_p3 (DxfSpline *spline);
DxfSpline *dxf_spline_set_p3 (DxfSpline *spline, DxfPoint *p3);
double dxf_spline_get_x3 (DxfSpline *spline);
DxfSpline *dxf_spline_set_x3 (DxfSpline *spline, double x3);
double dxf_spline_get_y3 (DxfSpline *spline);
DxfSpline *dxf_spline_set_y3 (DxfSpline *spline, double y3);
double dxf_spline_get_z3 (DxfSpline *spline);
DxfSpline *dxf_spline_set_z3 (DxfSpline *spline, double z3);
double dxf_spline_get_knot_tolerance (DxfSpline *spline);
DxfSpline *dxf_spline_set_knot_tolerance (DxfSpline *spline, double knot_tolerance);
double dxf_spline_get_control_point_tolerance (DxfSpline *spline);
DxfSpline *dxf_spline_set_control_point_tolerance (DxfSpline *spline, double control_point_tolerance);
double dxf_spline_get_fit_tolerance (DxfSpline *spline);
DxfSpline *dxf_spline_set_fit_tolerance (DxfSpline *spline, double fit_tolerance);
int16_t dxf_spline_get_flag (DxfSpline *spline);
DxfSpline *dxf_spline_set_flag (DxfSpline *spline, int16_t flag);
int16_t dxf_spline_get_degree (DxfSpline *spline);
DxfSpline *dxf_spline_set_degree (DxfSpline *spline, int16_t degree);
int16_t dxf_spline_get_number_of_knots (DxfSpline *spline);
DxfSpline *dxf_spline_set_number_of_knots (DxfSpline *spline, int16_t number_of_knots);
int16_t dxf_spline_get_number_of_control_points (DxfSpline *spline);
DxfSpline *dxf_spline_set_number_of_control_points (DxfSpline *spline, int16_t number_of_control_points);
int16_t dxf_spline_get_number_of_fit_points (DxfSpline *spline);
DxfSpline *dxf_spline_set_number_of_fit_points (DxfSpline *spline, int16_t number_of_fit_points);
DxfPoint *dxf_spline_get_extrusion_vector_as_point (DxfSpline *spline);
DxfSpline *dxf_spline_set_extrusion_vector_from_point (DxfSpline *spline, DxfPoint *point);
DxfSpline *dxf_spline_set_extrusion_vector (DxfSpline *spline, double extr_x0, double extr_y0, double extr_z0);
double dxf_spline_get_extr_x0 (DxfSpline *spline);
DxfSpline *dxf_spline_set_extr_x0 (DxfSpline *spline, double extr_x0);
double dxf_spline_get_extr_y0 (DxfSpline *spline);
DxfSpline *dxf_spline_set_extr_y0 (DxfSpline *spline, double extr_y0);
double dxf_spline_get_extr_z0 (DxfSpline *spline);
DxfSpline *dxf_spline_set_extr_z0 (DxfSpline *spline, double extr_z0);
DxfSpline *dxf_spline_get_next (DxfSpline *spline);
DxfSpline *dxf_spline_set_next (DxfSpline *spline, DxfSpline *next);
DxfSpline *dxf_spline_get_last (DxfSpline *spline);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_SPLINE_H */


/* EOF */

