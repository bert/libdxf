/*!
 * \file viewport.h
 *
 * \author Copyright (C) 2010, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF viewport entity (\c VIEWPORT).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12.
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#ifndef LIBDXF_SRC_VIEWPORT_H
#define LIBDXF_SRC_VIEWPORT_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"
#include "util.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD viewport entity (\c VIEWPORT).
 *
 * In addition, the extended entity data groups in the following struct
 * apply to viewports.\n
 *
 * \warning In contrast to normal entity data, the same extended entity
 * group code can appear multiple times, and so order is important.
 */
typedef struct
dxf_viewport_struct
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
                 * Group code = 67.\n
                 * \since Introduced in version R13. */
        int graphics_data_size;
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
        long transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
        /* Specific members for a DXF viewport. */
        DxfPoint *center;
                /*!< Center point of entity in paperspace coordinates.\n
                 * Group codes = 10, 20 and 30.*/
        double width;
                /*!< Width of the viewport in paper space units.\n
                 * Group code = 40. */
        double height;
                /*!< Height of the viewport in paper space units.\n
                 * Group code = 41. */
        int status;
                /*!< Viewport status field.\n
                 * The value of the viewport status field is interpreted
                 * as follows:\n
                 * -1 = On, but is fully off-screen or is one of the
                 * viewports not active because the $MAXACTVP count is
                 * currently being exceeded.\n
                 * 0 = Off.\n
                 * any positive value = On, active and the value indicates
                 * the order of "stacking" for the viewports, with 1
                 * applying to the active viewport, which is also the
                 * highest, 2 applying to the next viewport in the
                 * stack, and so on.\n
                 * Group code = 68. */
        int id;
                /*!< Viewport ID, permanent during editing sessions,
                 * but mutable between sessions; the paper space
                 * viewport entity always has an ID of 1.\n
                 * Group code = 69. */
        char *app_name;
                /*!< Application name.\n
                 * This field will always be the string "ACAD".\n
                 * Group code = 1001. */
        char *viewport_data;
                /*!< Begin viewport data.\n
                 * This field will always be the string "MVIEW".\n
                 * Other data groups may appear in the future.\n
                 * Group code = 1000. */
        char *window_descriptor_begin;
                /*!< Begin window descriptor data.\n
                 * This field will always be the string "{".\n
                 * Group code 1002. */
        int extended_entity_data_version;
                /*!< Extended entity data version number.\n
                 * For Releases 11, 12, 13 and 14, this field will
                 * always be the integer 16.\n
                 * Group code = 1070. */
        DxfPoint *target;
                /*!< View target point.\n
                 * Group codes = 1010, 1020 and 1030. */
        DxfPoint *direction;
                /*!< View direction from target point.\n
                 * Group codes = 1010, 1020 and 1030. */
        double view_twist_angle;
                /*!< View twist angle.\n
                 * Group code = 1040. */
        double view_height;
                /*!< View height.\n
                 * Group code = 1040. */
        DxfPoint *view_center;
                /*!< View center point.\n
                 * Group code = 1040. */
        double perspective_lens_length;
                /*!< group code = 1040. */
        double front_plane_offset;
                /*!< Front clip plane Z value.\n
                 * Group code = 1040. */
        double back_plane_offset;
                /*!< Back clip plane Z value.\n
                 * Group code = 1040. */
        int view_mode;
                /*!< View mode.\n
                 * Group code = 1070. */
        int circle_zoom_percent;
                /*!< Circle zoom.\n
                 * Group code = 1070. */
        int fast_zoom_setting;
                /*!< Fast zoom setting.\n
                 * Group code = 1070. */
        int UCSICON_setting;
                /*!< UCSICON setting.\n
                 * Group code = 1070. */
        int snap_on;
                /*!< Snap ON/OFF.\n
                 * Group code = 1070. */
        int grid_on;
                /*!< Grid ON/OFF.\n
                 * Group code = 1070. */
        int snap_style;
                /*!< Snap style.\n
                 * Group code = 1070. */
        int snap_isopair;
                /*!< Snap ISOPAIR.\n
                 * Group code = 1070. */
        double snap_rotation_angle;
                /*!< Snap angle.\n
                 * Group code = 1040. */
        DxfPoint *snap_base;
                /*!< Snap base point UCS.\n
                 * Group code = 1040. */
        DxfPoint *snap_spacing;
                /*!< Snap spacing.\n
                 * Group code = 1040. */
        DxfPoint *grid_spacing;
                /*!< Grid spacing.\n
                 * Group code = 1040. */
        int plot_flag;
                /*!< Hidden in plot flag.\n
                 * Group code = 1070. */
        char *frozen_layer_list_begin;
                /*!< Begin frozen layer list (possibly empty).\n
                 * This field will always be the string "{".\n
                 * Group code = 1002. */
        DxfChar *frozen_layers;
                /*!< The names of layers frozen in this viewport.\n
                 * This list may include Xref-dependent layers.\n
                 * Any number of 1003 groups may appear here.\n
                 * Group code = 1003.\n
                 *
                 * \todo Implement the number of layers in a more
                 * efficient way.\n
                 * A lot of memory is consumed by reserving for
                 * DXF_MAX_LAYERS instead of the actual existing number
                 * of layers.\n
                 * Maybe this can be solved by dynamically allocating a
                 * reasonable number of layers during compile time, and
                 * (re-allocating) shrinking when the actual number of
                 * layers is known during run time. */
        char *frozen_layer_list_end;
                /*!< End frozen layer list.\n
                 * This field will always be the string "}".\n
                 * Group code = 1002. */
        char *window_descriptor_end;
                /*!< End viewport data.\n
                 * This field will always be the string "}".\n
                 * Group code = 1002. */
        struct DxfViewport *next;
                /*!< Pointer to the next DxfViewport.\n
                 * \c NULL in the last DxfViewport. */
} DxfViewport;


DxfViewport *dxf_viewport_new ();
DxfViewport *dxf_viewport_init (DxfViewport *viewport);
DxfViewport *dxf_viewport_read (DxfFile *fp, DxfViewport *viewport);
int dxf_viewport_write (DxfFile *fp, DxfViewport *viewport);
int dxf_viewport_free (DxfViewport *viewport);
void dxf_viewport_free_list (DxfViewport *viewports);
int dxf_viewport_get_id_code (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_id_code (DxfViewport *viewport, int id_code);
char *dxf_viewport_get_linetype (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_linetype (DxfViewport *viewport, char *linetype);
char *dxf_viewport_get_layer (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_layer (DxfViewport *viewport, char *layer);
double dxf_viewport_get_elevation (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_elevation (DxfViewport *viewport, double elevation);
double dxf_viewport_get_thickness (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_thickness (DxfViewport *viewport, double thickness);
double dxf_viewport_get_linetype_scale (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_linetype_scale (DxfViewport *viewport, double linetype_scale);
int16_t dxf_viewport_get_visibility (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_visibility (DxfViewport *viewport, int16_t visibility);
int dxf_viewport_get_color (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_color (DxfViewport *viewport, int color);
int dxf_viewport_get_paperspace (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_paperspace (DxfViewport *viewport, int paperspace);
int dxf_viewport_get_graphics_data_size (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_graphics_data_size (DxfViewport *viewport, int graphics_data_size);
int16_t dxf_viewport_get_shadow_mode (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_shadow_mode (DxfViewport *viewport, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_viewport_get_binary_graphics_data (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_binary_graphics_data (DxfViewport *viewport, DxfBinaryGraphicsData *data);
char *dxf_viewport_get_dictionary_owner_soft (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_dictionary_owner_soft (DxfViewport *viewport, char *dictionary_owner_soft);
char *dxf_viewport_get_material (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_material (DxfViewport *viewport, char *material);
char *dxf_viewport_get_dictionary_owner_hard (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_dictionary_owner_hard (DxfViewport *viewport, char *dictionary_owner_hard);
int16_t dxf_viewport_get_lineweight (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_lineweight (DxfViewport *viewport, int16_t lineweight);
char *dxf_viewport_get_plot_style_name (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_plot_style_name (DxfViewport *viewport, char *plot_style_name);
long dxf_viewport_get_color_value (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_color_value (DxfViewport *viewport, long color_value);
char *dxf_viewport_get_color_name (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_color_name (DxfViewport *viewport, char *color_name);
long dxf_viewport_get_transparency (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_transparency (DxfViewport *viewport, long transparency);
DxfPoint *dxf_viewport_get_center (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_center (DxfViewport *viewport, DxfPoint *center);
double dxf_viewport_get_center_x (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_center_x (DxfViewport *viewport, double center_x);
double dxf_viewport_get_center_y (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_center_y (DxfViewport *viewport, double center_y);
double dxf_viewport_get_center_z (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_center_z (DxfViewport *viewport, double center_z);
double dxf_viewport_get_width (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_width (DxfViewport *viewport, double width);
double dxf_viewport_get_height (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_height (DxfViewport *viewport, double height);
int dxf_viewport_get_status (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_status (DxfViewport *viewport, int status);
int dxf_viewport_get_id (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_id (DxfViewport *viewport, int id);
char *dxf_viewport_get_app_name (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_app_name (DxfViewport *viewport, char *app_name);
char *dxf_viewport_get_viewport_data (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_viewport_data (DxfViewport *viewport, char *viewport_data);
char *dxf_viewport_get_window_descriptor_begin (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_window_descriptor_begin (DxfViewport *viewport, char *window_descriptor_begin);
int dxf_viewport_get_extended_entity_data_version (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_extended_entity_data_version (DxfViewport *viewport, int extended_entity_data_version);
DxfPoint *dxf_viewport_get_target (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_target (DxfViewport *viewport, DxfPoint *target);
double dxf_viewport_get_target_x (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_target_x (DxfViewport *viewport, double target_x);
double dxf_viewport_get_target_y (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_target_y (DxfViewport *viewport, double target_y);
double dxf_viewport_get_target_z (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_target_z (DxfViewport *viewport, double target_z);
DxfPoint *dxf_viewport_get_direction (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_direction (DxfViewport *viewport, DxfPoint *direction);
double dxf_viewport_get_direction_x (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_direction_x (DxfViewport *viewport, double direction_x);
double dxf_viewport_get_direction_y (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_direction_y (DxfViewport *viewport, double direction_y);
double dxf_viewport_get_direction_z (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_direction_z (DxfViewport *viewport, double direction_z);
double dxf_viewport_get_view_twist_angle (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_view_twist_angle (DxfViewport *viewport, double view_twist_angle);
double dxf_viewport_get_view_height (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_view_height (DxfViewport *viewport, double view_height);
DxfPoint *dxf_viewport_get_view_center (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_view_center (DxfViewport *viewport, DxfPoint *view_center);
double dxf_viewport_get_view_center_x (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_view_center_x (DxfViewport *viewport, double view_center_x);
double dxf_viewport_get_view_center_y (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_view_center_y (DxfViewport *viewport, double view_center_y);
double dxf_viewport_get_perspective_lens_length (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_perspective_lens_length (DxfViewport *viewport, double perspective_lens_length);
double dxf_viewport_get_front_plane_offset (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_front_plane_offset (DxfViewport *viewport, double front_plane_offset);
double dxf_viewport_get_back_plane_offset (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_back_plane_offset (DxfViewport *viewport, double back_plane_offset);
int dxf_viewport_get_view_mode (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_view_mode (DxfViewport *viewport, int view_mode);
int dxf_viewport_get_circle_zoom_percent (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_circle_zoom_percent (DxfViewport *viewport, int circle_zoom_percent);
int dxf_viewport_get_fast_zoom_setting (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_fast_zoom_setting (DxfViewport *viewport, int fast_zoom_setting);
int dxf_viewport_get_UCSICON_setting (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_UCSICON_setting (DxfViewport *viewport, int UCSICON_setting);
int dxf_viewport_get_snap_on (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_on (DxfViewport *viewport, int snap_on);
int dxf_viewport_get_grid_on (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_grid_on (DxfViewport *viewport, int grid_on);
int dxf_viewport_get_snap_style (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_style (DxfViewport *viewport, int snap_style);
int dxf_viewport_get_snap_isopair (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_isopair (DxfViewport *viewport, int snap_isopair);
double dxf_viewport_get_snap_rotation_angle (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_rotation_angle (DxfViewport *viewport, double snap_rotation_angle);
DxfPoint *dxf_viewport_get_snap_base (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_base (DxfViewport *viewport, DxfPoint *snap_base);
double dxf_viewport_get_snap_base_x (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_base_x (DxfViewport *viewport, double snap_base_x);
double dxf_viewport_get_snap_base_y (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_base_y (DxfViewport *viewport, double snap_base_y);
DxfPoint *dxf_viewport_get_snap_spacing (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_spacing (DxfViewport *viewport, DxfPoint *snap_spacing);
double dxf_viewport_get_snap_spacing_x (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_spacing_x (DxfViewport *viewport, double snap_spacing_x);
double dxf_viewport_get_snap_spacing_y (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_snap_spacing_y (DxfViewport *viewport, double snap_spacing_y);
DxfPoint *dxf_viewport_get_grid_spacing (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_grid_spacing (DxfViewport *viewport, DxfPoint *grid_spacing);
double dxf_viewport_get_grid_spacing_x (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_grid_spacing_x (DxfViewport *viewport, double grid_spacing_x);
double dxf_viewport_get_grid_spacing_y (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_grid_spacing_y (DxfViewport *viewport, double grid_spacing_y);
int dxf_viewport_get_plot_flag (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_plot_flag (DxfViewport *viewport, int plot_flag);
char *dxf_viewport_get_frozen_layer_list_begin (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_frozen_layer_list_begin (DxfViewport *viewport, char *frozen_layer_list_begin);
DxfChar *dxf_viewport_get_frozen_layers (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_frozen_layers (DxfViewport *viewport, DxfChar *frozen_layers);
char *dxf_viewport_get_frozen_layer_list_end (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_frozen_layer_list_end (DxfViewport *viewport, char *frozen_layer_list_end);
char *dxf_viewport_get_window_descriptor_end (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_window_descriptor_end (DxfViewport *viewport, char *window_descriptor_end);
DxfViewport *dxf_viewport_get_next (DxfViewport *viewport);
DxfViewport *dxf_viewport_set_next (DxfViewport *viewport, DxfViewport *next);
DxfViewport *dxf_viewport_get_last (DxfViewport *viewport);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_VIEWPORT_H */


/* EOF */
