/*!
 * \file helix.h
 *
 * \author Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018, 2019
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF helix entity (\c HELIX).
 *
 * \since The \c HELIX entity was introduced in DXF R2007.
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
#include "spline.h"
#include "binary_graphics_data.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of an AutoCAD helix entity (\c HELIX).
 */
typedef struct
dxf_helix_struct
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
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
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
        DxfBinaryGraphicsData *binary_graphics_data;
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
        /* Specific members for a DXF helix. */
        DxfPoint *p0;
                /*!< Axis base point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Start point.\n
                 * Group codes = 11, 21 and 31. */
        DxfPoint *p2;
                /*!< Axis vector point.\n
                 * Group codes = 12, 22 and 32. */
        double radius;
                /*!< Radius of the arc.\n
                 * Group code = 40. */
        double number_of_turns;
                /*!< Number of turns.\n
                 * Group code = 41. */
        double turn_height;
                /*!< Turn height.\n
                 * Group code = 42. */
        int32_t major_release_number;
                /*!< Major release number.\n
                 * Group code = 90. */
        int32_t maintainance_release_number;
                /*!< Maintainance release number.\n
                 * Group code = 91. */
        int16_t constraint_type;
                /*!< Constrain type:\n
                 * <ol>
                 * <li value = "0"> Constrain turn height.</li>
                 * <li value = "1"> Constrain turns.</li>
                 * <li value = "2"> Constrain height.</li>
                 * </ol>
                 * Group code = 280. */
        int handedness;
                /*!< Handedness:
                 * <ol>
                 * <li value = "0"> Left.</li>
                 * <li value = "1"> Right</li>
                 * </ol>
                 * Group code = 290. */
        DxfSpline *spline;
                /*!< Pointer to the DxfSpline. */
        struct DxfHelix *next;
                /*!< Pointer to the next DxfHelix.\n
                 * \c NULL in the last DxfHelix. */
} DxfHelix;


DxfHelix *dxf_helix_new ();
DxfHelix *dxf_helix_init (DxfHelix *helix);
DxfHelix *dxf_helix_read (DxfFile *fp, DxfHelix *helix);
int dxf_helix_write (DxfFile *fp, DxfHelix *helix);
int dxf_helix_free (DxfHelix *helix);
void dxf_helix_free_list (DxfHelix *helices);
int dxf_helix_get_id_code (DxfHelix *helix);
DxfHelix *dxf_helix_set_id_code (DxfHelix *helix, int id_code);
char *dxf_helix_get_linetype (DxfHelix *helix);
DxfHelix *dxf_helix_set_linetype (DxfHelix *helix, char *linetype);
char *dxf_helix_get_layer (DxfHelix *helix);
DxfHelix *dxf_helix_set_layer (DxfHelix *helix, char *layer);
double dxf_helix_get_thickness (DxfHelix *helix);
DxfHelix *dxf_helix_set_thickness (DxfHelix *helix, double thickness);
double dxf_helix_get_linetype_scale (DxfHelix *helix);
DxfHelix *dxf_helix_set_linetype_scale (DxfHelix *helix, double linetype_scale);
int16_t dxf_helix_get_visibility (DxfHelix *helix);
DxfHelix *dxf_helix_set_visibility (DxfHelix *helix, int16_t visibility);
int16_t dxf_helix_get_color (DxfHelix *helix);
DxfHelix *dxf_helix_set_color (DxfHelix *helix, int16_t color);
int16_t dxf_helix_get_paperspace (DxfHelix *helix);
DxfHelix *dxf_helix_set_paperspace (DxfHelix *helix, int16_t paperspace);
int32_t dxf_helix_get_graphics_data_size (DxfHelix *helix);
DxfHelix *dxf_helix_set_graphics_data_size (DxfHelix *helix, int32_t graphics_data_size);
int16_t dxf_helix_get_shadow_mode (DxfHelix *helix);
DxfHelix *dxf_helix_set_shadow_mode (DxfHelix *helix, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_helix_get_binary_graphics_data (DxfHelix *helix);
DxfHelix *dxf_helix_set_binary_graphics_data (DxfHelix *helix, DxfBinaryGraphicsData *data);
char *dxf_helix_get_dictionary_owner_soft (DxfHelix *helix);
DxfHelix *dxf_helix_set_dictionary_owner_soft (DxfHelix *helix, char *dictionary_owner_soft);
char *dxf_helix_get_object_owner_soft (DxfHelix *helix);
DxfHelix *dxf_helix_set_object_owner_soft (DxfHelix *helix, char *object_owner_soft);
char *dxf_helix_get_material (DxfHelix *helix);
DxfHelix *dxf_helix_set_material (DxfHelix *helix, char *material);
char *dxf_helix_get_dictionary_owner_hard (DxfHelix *helix);
DxfHelix *dxf_helix_set_dictionary_owner_hard (DxfHelix *helix, char *dictionary_owner_hard);
int16_t dxf_helix_get_lineweight (DxfHelix *helix);
DxfHelix *dxf_helix_set_lineweight (DxfHelix *helix, int16_t lineweight);
char *dxf_helix_get_plot_style_name (DxfHelix *helix);
DxfHelix *dxf_helix_set_plot_style_name (DxfHelix *helix, char *plot_style_name);
int32_t dxf_helix_get_color_value (DxfHelix *helix);
DxfHelix *dxf_helix_set_color_value (DxfHelix *helix, int32_t color_value);
char *dxf_helix_get_color_name (DxfHelix *helix);
DxfHelix *dxf_helix_set_color_name (DxfHelix *helix, char *color_name);
int32_t dxf_helix_get_transparency (DxfHelix *helix);
DxfHelix *dxf_helix_set_transparency (DxfHelix *helix, int32_t transparency);
DxfPoint *dxf_helix_get_p0 (DxfHelix *helix);
DxfHelix *dxf_helix_set_p0 (DxfHelix *helix, DxfPoint *p0);
double dxf_helix_get_x0 (DxfHelix *helix);
DxfHelix *dxf_helix_set_x0 (DxfHelix *helix, double x0);
double dxf_helix_get_y0 (DxfHelix *helix);
DxfHelix *dxf_helix_set_y0 (DxfHelix *helix, double y0);
double dxf_helix_get_z0 (DxfHelix *helix);
DxfHelix *dxf_helix_set_z0 (DxfHelix *helix, double z0);
DxfPoint *dxf_helix_get_p1 (DxfHelix *helix);
DxfHelix *dxf_helix_set_p1 (DxfHelix *helix, DxfPoint *p1);
double dxf_helix_get_x1 (DxfHelix *helix);
DxfHelix *dxf_helix_set_x1 (DxfHelix *helix, double x1);
double dxf_helix_get_y1 (DxfHelix *helix);
DxfHelix *dxf_helix_set_y1 (DxfHelix *helix, double y1);
double dxf_helix_get_z1 (DxfHelix *helix);
DxfHelix *dxf_helix_set_z1 (DxfHelix *helix, double z1);
DxfPoint *dxf_helix_get_p2 (DxfHelix *helix);
DxfHelix *dxf_helix_set_p2 (DxfHelix *helix, DxfPoint *p2);
double dxf_helix_get_x2 (DxfHelix *helix);
DxfHelix *dxf_helix_set_x2 (DxfHelix *helix, double x2);
double dxf_helix_get_y2 (DxfHelix *helix);
DxfHelix *dxf_helix_set_y2 (DxfHelix *helix, double y2);
double dxf_helix_get_z2 (DxfHelix *helix);
DxfHelix *dxf_helix_set_z2 (DxfHelix *helix, double z2);
double dxf_helix_get_radius (DxfHelix *helix);
DxfHelix *dxf_helix_set_radius (DxfHelix *helix, double radius);
double dxf_helix_get_number_of_turns (DxfHelix *helix);
DxfHelix *dxf_helix_set_number_of_turns (DxfHelix *helix, double number_of_turns);
double dxf_helix_get_turn_height (DxfHelix *helix);
DxfHelix *dxf_helix_set_turn_height (DxfHelix *helix, double turn_height);
int32_t dxf_helix_get_major_release_number (DxfHelix *helix);
DxfHelix *dxf_helix_set_major_release_number (DxfHelix *helix, int32_t major_release_number);
int32_t dxf_helix_get_maintainance_release_number (DxfHelix *helix);
DxfHelix *dxf_helix_set_maintainance_release_number (DxfHelix *helix, int32_t maintainance_release_number);
int16_t dxf_helix_get_constraint_type (DxfHelix *helix);
DxfHelix *dxf_helix_set_constraint_type (DxfHelix *helix, int16_t constraint_type);
int dxf_helix_get_handedness (DxfHelix *helix);
DxfHelix *dxf_helix_set_handedness (DxfHelix *helix, int handedness);
DxfSpline *dxf_helix_get_spline (DxfHelix *helix);
DxfHelix *dxf_helix_set_spline (DxfHelix *helix, DxfSpline *spline);
DxfHelix *dxf_helix_get_next (DxfHelix *helix);
DxfHelix *dxf_helix_set_next (DxfHelix *helix, DxfHelix *next);
DxfHelix *dxf_helix_get_last (DxfHelix *helix);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_HELIX_H */


/* EOF */
