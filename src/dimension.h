/*!
 * \file dimension.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015, 2016, 2017, 2018, 2019
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF dimension entity (\c DIMENSION).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
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


#ifndef LIBDXF_SRC_DIMENSION_H
#define LIBDXF_SRC_DIMENSION_H


#include "global.h"
#include "point.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD dimension.
 */
typedef struct
dxf_dimension_struct
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
                /*!< Elevation of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38.\n
                 * \deprecated As of version R11. */
        double thickness;
                /*!< Thickness of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48.\n
                 * \since Introduced in version R13. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60.\n
                 * \since Introduced in version R13. */
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
                 * Group code = 67.\n
                 * \since Introduced in version R13. */
        int32_t graphics_data_size;
                /*!< Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).\n
                 * Group code = 92.\n
                 * \since Introduced in version R2000.\n
                 * \warning On some 64 bit workstations output is
                 * generated with group code "160", thus omitting group
                 * code "92". */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284.\n
                 * \since Introduced in version R2009. */
        DxfBinaryData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330.\n
                 * \since Introduced in version R14. */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle  to owner BLOCK_RECORD object.\n
                 * Group code = 330.\n
                 * \since Introduced in version R2000. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347.\n
                 * \since Introduced in version R2008. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360.\n
                 * \since Introduced in version R14. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370.\n
                 * \since Introduced in version R2002. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390.\n
                 * \since Introduced in version R2009. */
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
                 * Group code = 420.\n
                 * \since Introduced in version R2004. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430.\n
                 * \since Introduced in version R2004. */
        int32_t transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
        /* Specific members for a DXF dimension. */
        char *dim_text;
                /*!< Dimension text explicitly entered by the user.\n
                 * If null or "<>", the dimension measurement is drawn
                 * as the text, if " " [one blank space], the text is
                 * suppressed.\n
                 * Anything else is drawn as the text.\n
                 * Group code = 1. */
        char *dimblock_name;
                /*!< Name of pseudo-Block containing the current
                 * dimension entity geometry.\n
                 * Group code = 2. */
        char *dimstyle_name;
                /*!< Dimension style name.\n
                 * Group code = 3.  */
        DxfPoint *p0;
                /*!< Definition point for all dimension types.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Middle point of dimension text.\n
                 * Group codes = 11, 21 and 31. */
        DxfPoint *p2;
                /*!< Dimension block translation vector.\n
                 * Group codes = 12, 22 and 32. */
        DxfPoint *p3;
                /*!< Definition point for linear and angular dimensions.\n
                 * Group codes = 13, 23 and 33. */
        DxfPoint *p4;
                /*!< Definition point for linear and angular dimensions.\n
                 * Group codes = 14, 24 and 34. */
        DxfPoint *p5;
                /*!< Definition point for diameter, radius, and angular
                 * dimensions.\n
                 * Group codes = 15, 25 and 35. */
        DxfPoint *p6;
                /*!< Point defining dimension arc for angular dimensions.\n
                 * Group codes = 16, 26 and 36. */
        double leader_length;
                /*!< Leader length for radius and diameter dimensions.\n
                 * Group code = 40. */
        double text_line_spacing_factor;
                /*!< Dimension text line spacing factor (optional):\n
                 * Percentage of default (3-on-5) line spacing to be
                 * applied.\n
                 * Valid values range from 0.25 to 4.00.\n
                 * Group code = 41. */
        double actual_measurement;
                /*!< Actual measurement (optional; read-only value).\n
                 * Group code = 42. */
        double angle;
                /*!< Angle of rotated, horizontal, or vertical linear
                 * dimensions.\n
                 * Group code = 50. */
        double hor_dir;
                /*!< In addition, all dimension types have an optional
                 * group (group code 51) that indicates the horizontal
                 * direction for the Dimension entity.\n
                 * This determines the orientation of dimension text and
                 * dimension lines for horizontal, vertical, and rotated
                 * linear dimensions.\n
                 * The group value is the negative of the Entity
                 * Coordinate Systems (ECS) angle of the UCS X axis in
                 * effect when the Dimension was drawn.\n
                 * The X axis of the UCS in effect when the Dimension
                 * was drawn is always parallel to the XY plane for the
                 * Dimension's ECS, and the angle between the UCS X axis
                 * and the ECS X axis is a single 2D angle.\n
                 * The value in group code 51 is the angle from
                 * horizontal (the effective X axis) to the ECS X axis.\n
                 * Entity Coordinate Systems (ECS) are described
                 * elsewhere in this documentation.\n
                 * Group code = 51. */
        double obl_angle;
                /*!< Linear dimension types with an oblique angle have
                 * an optional group (group code 52).\n
                 * When added to the rotation angle of the linear
                 * dimension (group code 50) this gives the angle of the
                 * extension lines.\n
                 * Group code = 52. */
        double text_angle;
                /*!< The optional group code 53 is the rotation angle of
                 * the dimension text away from its default orientation
                 * (the direction of the dimension line).\n
                 * Group code = 53. */
        int16_t flag;
                /*!< Dimension type.\n
                 * Values 0–6 are integer values that represent the
                 * dimension type.\n
                 * Values 32, 64, and 128 are bit values, which are
                 * added to the integer values (value 32 is always set
                 * in R13 and later releases).\n
                 * 0 = Rotated, horizontal, or vertical.\n
                 * 1 = Aligned.\n
                 * 2 = Angular.\n
                 * 3 = Diameter.\n
                 * 4 = Radius.\n
                 * 5 = Angular 3-point.\n
                 * 6 = Ordinate.\n
                 * 32 = Indicates that the block reference (group code
                 *      2) is referenced by this dimension only.\n
                 * 64 = Ordinate type.\n
                 *      This is a bit value (bit 7) used only with
                 *      integer value 6.\n
                 *      If set, ordinate is X-type; if not set, ordinate
                 *      is Y-type.\n
                 * 128 = This is a bit value (bit 8) added to the other
                 *       group 70 values if the dimension text has been
                 *       positioned at a user-defined location rather
                 *       than at the default location.\n
                 * Group code = 70. */
        int16_t attachment_point;
                /*!< Attachment point:\n
                 * 1 = Top left;\n
                 * 2 = Top center;\n
                 * 3 = Top right;\n
                 * 4 = Middle left;\n
                 * 5 = Middle center;\n
                 * 6 = Middle right;\n
                 * 7 = Bottom left;\n
                 * 8 = Bottom center;\n
                 * 9 = Bottom right.\n
                 * Group code = 71. */
        int16_t text_line_spacing;
                /*!< Dimension text line spacing style (optional):\n
                 * 1 (or missing) = At least (taller characters will
                 *   override);\n
                 * 2 = Exact (taller characters will not override).\n
                 * Group code = 72. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file.\n
                 * Group code = 230. */
        int16_t version_number;
                /*!< Version number:\n
                 * 0 = 2010.\n
                 * Group code = 280.\n
                 * \since Introduced in version R2010. */
        struct DxfDimension *next;
                /*!< pointer to the next DxfDimension.\n
                 * \c NULL in the last DxfDimension. */
} DxfDimension;


DxfDimension *dxf_dimension_new ();
DxfDimension *dxf_dimension_init (DxfDimension *dimension);
DxfDimension *dxf_dimension_read (DxfFile *fp, DxfDimension *dimension);
int dxf_dimension_write (DxfFile *fp, DxfDimension *dimension);
int dxf_dimension_free (DxfDimension *dimension);
void dxf_dimension_free_list (DxfDimension *dimensions);
int dxf_dimension_get_id_code (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_id_code (DxfDimension *dimension, int id_code);
char *dxf_dimension_get_linetype (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_linetype (DxfDimension *dimension, char *linetype);
char *dxf_dimension_get_layer (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_layer (DxfDimension *dimension, char *layer);
double dxf_dimension_get_elevation (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_elevation (DxfDimension *dimension, double elevation);
double dxf_dimension_get_thickness (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_thickness (DxfDimension *dimension, double thickness);
double dxf_dimension_get_linetype_scale (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_linetype_scale (DxfDimension *dimension, double linetype_scale);
int16_t dxf_dimension_get_visibility (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_visibility (DxfDimension *dimension, int16_t visibility);
int16_t dxf_dimension_get_color (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_color (DxfDimension *dimension, int16_t color);
int16_t dxf_dimension_get_paperspace (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_paperspace (DxfDimension *dimension, int16_t paperspace);
int32_t dxf_dimension_get_graphics_data_size (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_graphics_data_size (DxfDimension *dimension, int32_t graphics_data_size);
int16_t dxf_dimension_get_shadow_mode (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_shadow_mode (DxfDimension *dimension, int16_t shadow_mode);
DxfBinaryData *dxf_dimension_get_binary_graphics_data (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_binary_graphics_data (DxfDimension *dimension, DxfBinaryData *data);
char *dxf_dimension_get_dictionary_owner_soft (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_dictionary_owner_soft (DxfDimension *dimension, char *dictionary_owner_soft);
char *dxf_dimension_get_object_owner_soft (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_object_owner_soft (DxfDimension *dimension, char *object_owner_soft);
char *dxf_dimension_get_material (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_material (DxfDimension *dimension, char *material);
char *dxf_dimension_get_dictionary_owner_hard (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_dictionary_owner_hard (DxfDimension *dimension, char *dictionary_owner_hard);
int16_t dxf_dimension_get_lineweight (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_lineweight (DxfDimension *dimension, int16_t lineweight);
char *dxf_dimension_get_plot_style_name (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_plot_style_name (DxfDimension *dimension, char *plot_style_name);
int32_t dxf_dimension_get_color_value (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_color_value (DxfDimension *dimension, int32_t color_value);
char *dxf_dimension_get_color_name (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_color_name (DxfDimension *dimension, char *color_name);
int32_t dxf_dimension_get_transparency (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_transparency (DxfDimension *dimension, int32_t transparency);
char *dxf_dimension_get_dim_text (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_dim_text (DxfDimension *dimension, char *dim_text);
char *dxf_dimension_get_dimblock_name (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_dimblock_name (DxfDimension *dimension, char *dimblock_name);
char *dxf_dimension_get_dimstyle_name (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_dimstyle_name (DxfDimension *dimension, char *dimstyle_name);
DxfPoint *dxf_dimension_get_p0 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_p0 (DxfDimension *dimension, DxfPoint *p0);
double dxf_dimension_get_x0 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_x0 (DxfDimension *dimension, double x0);
double dxf_dimension_get_y0 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_y0 (DxfDimension *dimension, double y0);
double dxf_dimension_get_z0 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_z0 (DxfDimension *dimension, double z0);
DxfPoint *dxf_dimension_get_p1 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_p1 (DxfDimension *dimension, DxfPoint *p1);
double dxf_dimension_get_x1 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_x1 (DxfDimension *dimension, double x1);
double dxf_dimension_get_y1 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_y1 (DxfDimension *dimension, double y1);
double dxf_dimension_get_z1 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_z1 (DxfDimension *dimension, double z1);
DxfPoint *dxf_dimension_get_p2 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_p2 (DxfDimension *dimension, DxfPoint *p2);
double dxf_dimension_get_x2 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_x2 (DxfDimension *dimension, double x2);
double dxf_dimension_get_y2 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_y2 (DxfDimension *dimension, double y2);
double dxf_dimension_get_z2 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_z2 (DxfDimension *dimension, double z2);
DxfPoint *dxf_dimension_get_p3 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_p3 (DxfDimension *dimension, DxfPoint *p3);
double dxf_dimension_get_x3 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_x3 (DxfDimension *dimension, double x3);
double dxf_dimension_get_y3 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_y3 (DxfDimension *dimension, double y3);
double dxf_dimension_get_z3 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_z3 (DxfDimension *dimension, double z3);
DxfPoint *dxf_dimension_get_p4 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_p4 (DxfDimension *dimension, DxfPoint *p4);
double dxf_dimension_get_x4 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_x4 (DxfDimension *dimension, double x4);
double dxf_dimension_get_y4 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_y4 (DxfDimension *dimension, double y4);
double dxf_dimension_get_z4 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_z4 (DxfDimension *dimension, double z4);
DxfPoint *dxf_dimension_get_p5 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_p5 (DxfDimension *dimension, DxfPoint *p5);
double dxf_dimension_get_x5 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_x5 (DxfDimension *dimension, double x5);
double dxf_dimension_get_y5 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_y5 (DxfDimension *dimension, double y5);
double dxf_dimension_get_z5 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_z5 (DxfDimension *dimension, double z5);
DxfPoint *dxf_dimension_get_p6 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_p6 (DxfDimension *dimension, DxfPoint *p6);
double dxf_dimension_get_x6 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_x6 (DxfDimension *dimension, double x6);
double dxf_dimension_get_y6 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_y6 (DxfDimension *dimension, double y6);
double dxf_dimension_get_z6 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_z6 (DxfDimension *dimension, double z6);
double dxf_dimension_get_leader_length (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_leader_length (DxfDimension *dimension, double leader_length);
double dxf_dimension_get_text_line_spacing_factor (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_text_line_spacing_factor (DxfDimension *dimension, double text_line_spacing_factor);
double dxf_dimension_get_actual_measurement (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_actual_measurement (DxfDimension *dimension, double actual_measurement);
double dxf_dimension_get_angle (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_angle (DxfDimension *dimension, double angle);
double dxf_dimension_get_hor_dir (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_hor_dir (DxfDimension *dimension, double hor_dir);
double dxf_dimension_get_obl_angle (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_obl_angle (DxfDimension *dimension, double obl_angle);
double dxf_dimension_get_text_angle (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_text_angle (DxfDimension *dimension, double text_angle);
int16_t dxf_dimension_get_flag (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_flag (DxfDimension *dimension, int16_t flag);
int16_t dxf_dimension_get_attachment_point (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_attachment_point (DxfDimension *dimension, int16_t attachment_point);
int16_t dxf_dimension_get_text_line_spacing (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_text_line_spacing (DxfDimension *dimension, int16_t text_line_spacing);
double dxf_dimension_get_extr_x0 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_extr_x0 (DxfDimension *dimension, double extr_x0);
double dxf_dimension_get_extr_y0 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_extr_y0 (DxfDimension *dimension, double extr_y0);
double dxf_dimension_get_extr_z0 (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_extr_z0 (DxfDimension *dimension, double extr_z0);
DxfPoint *dxf_dimension_get_extrusion_vector_as_point (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_extrusion_vector (DxfDimension *dimension, double extr_x0, double extr_y0, double extr_z0);
int16_t dxf_dimension_get_version_number (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_version_number (DxfDimension *dimension, int16_t version_number);
DxfDimension *dxf_dimension_get_next (DxfDimension *dimension);
DxfDimension *dxf_dimension_set_next (DxfDimension *dimension, DxfDimension *next);
DxfDimension *dxf_dimension_get_last (DxfDimension *dimension);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_DIMENSION_H */


/* EOF */
