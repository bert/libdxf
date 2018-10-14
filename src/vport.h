/*!
 * \file vport.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF Viewport symbol table entry (\c VPORT).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
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


#ifndef LIBDXF_SRC_VPORT_H
#define LIBDXF_SRC_VPORT_H


#include "global.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD vport symbol table entry.
 *
 * The VPORT table is unique in that it may contain several entries with the
 * same name (indicating a multiple-viewport configuration).\n
 * The entries corresponding to the active viewport configuration all have
 * the name *ACTIVE.\n
 * The first such entry describes the current viewport.
 */
typedef struct
dxf_vport_struct
{
        int id_code;
                /*!< Identification number for the symbol table entry.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *viewport_name;
                /*!< Group code = 2. */
        DxfPoint *min;
                /*!< The lower-left corner of viewport.\n
                 * Group codes = 10 and 20.*/
        DxfPoint *max;
                /*!< The upper-right corner of viewport.\n
                 * Group codes = 11 and 21.*/
        DxfPoint *center;
                /*!< The view center point, in World Coordinate System.\n
                 * Group codes = 12 and 22. */
        DxfPoint *snap_base;
                /*!< The snap base point.\n
                 * Group codes = 13 and 23. */
        DxfPoint *snap_spacing;
                /*!< The snap spacing.\n
                 * Group codes = 14 and 24. */
        DxfPoint *grid_spacing;
                /*!< The grid spacing.\n
                 * Group codes = 15 and 25. */
        DxfPoint *direction;
                /*!< The view direction from target point.\n
                 * Group codes = 16, 26 and 36. */
        DxfPoint *target;
                /*!< The view target point.\n
                 * Group codes = 17, 27 and 37. */
        double view_height;
                /*!< View height.\n
                 * Group code = 40. */
        double viewport_aspect_ratio;
                /*!< Viewport aspect ratio.\n
                 * Group code = 41. */
        double lens_length;
                /*!< Lens length.\n
                 * Group code = 42. */
        double front_plane_offset;
                /*!< Front clipping plane - offset from target point.\n
                 * Group code = 43. */
        double back_plane_offset;
                /*!< Back clipping plane - offset from target point.\n
                 * Group code = 44. */
        double snap_rotation_angle;
                /*!< Snap rotation angle.\n
                 * Group code = 50. */
        double view_twist_angle;
                /*!< View twist angle.\n
                 * Group code = 51. */
        int status_field;
                /*!< Status field (never saved in DXF).\n
                 * Group code = 68. */
        int id;
                /*!< ID (never saved in DXF).\n
                 * Group code = 69. */
        int standard_flag;
                /*!< Standard flag values (See "Common Group Codes for
                 * Symbol Table Entries.").\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "16"> If set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> If this bit and bit 16 are both
                 * set, the externally dependent Xref has been
                 * successfully resolved.</li>
                 * <li value = "64"> If set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * This flag is for the benefit of AutoCAD commands; it can
                 * be ignored by most programs that read DXF files, and need
                 * not be set by programs that write DXF files.\n
                 * Group code = 70. */
        int view_mode;
                /*!< See VIEWMODE system variable in appendix A.\n
                 * Group code = 71. */
        int circle_zoom_percent;
                /*!< Circle zoom percent.\n
                 * Group code = 72. */
        int fast_zoom_setting;
                /*!< Fast zoom setting.\n
                 * Group code = 73. */
        int UCSICON_setting;
                /*!< UCSICON setting.\n
                 * Group code = 74. */
        int snap_on;
                /*!< Snap on/off.\n
                 * Group code = 75. */
        int grid_on;
                /*!< Grid on/off.\n
                 * Group code = 76. */
        int snap_style;
                /*!< Snap style.\n
                 * Group code = 77. */
        int snap_isopair;
                /*!< Snap isopair.\n
                 * Group code = 78. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
        struct DxfVPort *next;
                /*!< Pointer to the next DxfVPort.\n
                 * \c NULL in the last DxfVPort. */
} DxfVPort;


DxfVPort *dxf_vport_new ();
DxfVPort *dxf_vport_init (DxfVPort *vport);
DxfVPort *dxf_vport_read (DxfFile *fp, DxfVPort *vport);
int dxf_vport_write (DxfFile *fp, DxfVPort *vport);
int dxf_vport_free (DxfVPort *vport);
void dxf_vport_free_list (DxfVPort *vports);
int dxf_vport_get_id_code (DxfVPort *vport);
DxfVPort *dxf_vport_set_id_code (DxfVPort *vport, int id_code);
char *dxf_vport_get_viewport_name (DxfVPort *vport);
DxfVPort *dxf_vport_set_viewport_name (DxfVPort *vport, char *viewport_name);
DxfPoint *dxf_vport_get_min (DxfVPort *vport);
DxfVPort *dxf_vport_set_min (DxfVPort *vport, DxfPoint *min);
double dxf_vport_get_min_x (DxfVPort *vport);
DxfVPort *dxf_vport_set_min_x (DxfVPort *vport, double min_x);
double dxf_vport_get_min_y (DxfVPort *vport);
DxfVPort *dxf_vport_set_min_y (DxfVPort *vport, double min_y);
DxfPoint *dxf_vport_get_max (DxfVPort *vport);
DxfVPort *dxf_vport_set_max (DxfVPort *vport, DxfPoint *max);
double dxf_vport_get_max_x (DxfVPort *vport);
DxfVPort *dxf_vport_set_max_x (DxfVPort *vport, double max_x);
double dxf_vport_get_max_y (DxfVPort *vport);
DxfVPort *dxf_vport_set_max_y (DxfVPort *vport, double max_y);
DxfPoint *dxf_vport_get_center (DxfVPort *vport);
DxfVPort *dxf_vport_set_center (DxfVPort *vport, DxfPoint *center);
double dxf_vport_get_center_x (DxfVPort *vport);
DxfVPort *dxf_vport_set_center_x (DxfVPort *vport, double center_x);
double dxf_vport_get_center_y (DxfVPort *vport);
DxfVPort *dxf_vport_set_center_y (DxfVPort *vport, double center_y);
DxfPoint *dxf_vport_get_snap_base (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_base (DxfVPort *vport, DxfPoint *snap_base);
double dxf_vport_get_snap_base_x (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_base_x (DxfVPort *vport, double snap_base_x);
double dxf_vport_get_snap_base_y (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_base_y (DxfVPort *vport, double snap_base_y);
DxfPoint *dxf_vport_get_snap_spacing (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_spacing (DxfVPort *vport, DxfPoint *snap_spacing);
double dxf_vport_get_snap_spacing_x (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_spacing_x (DxfVPort *vport, double snap_spacing_x);
double dxf_vport_get_snap_spacing_y (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_spacing_y (DxfVPort *vport, double snap_spacing_y);
DxfPoint *dxf_vport_get_grid_spacing (DxfVPort *vport);
DxfVPort *dxf_vport_set_grid_spacing (DxfVPort *vport, DxfPoint *grid_spacing);
double dxf_vport_get_grid_spacing_x (DxfVPort *vport);
DxfVPort *dxf_vport_set_grid_spacing_x (DxfVPort *vport, double grid_spacing_x);
double dxf_vport_get_grid_spacing_y (DxfVPort *vport);
DxfVPort *dxf_vport_set_grid_spacing_y (DxfVPort *vport, double grid_spacing_y);
DxfPoint *dxf_vport_get_direction (DxfVPort *vport);
DxfVPort *dxf_vport_set_direction (DxfVPort *vport, DxfPoint *direction);
double dxf_vport_get_direction_x (DxfVPort *vport);
DxfVPort *dxf_vport_set_direction_x (DxfVPort *vport, double direction_x);
double dxf_vport_get_direction_y (DxfVPort *vport);
DxfVPort *dxf_vport_set_direction_y (DxfVPort *vport, double direction_y);
double dxf_vport_get_direction_z (DxfVPort *vport);
DxfVPort *dxf_vport_set_direction_z (DxfVPort *vport, double direction_z);
DxfPoint *dxf_vport_get_target (DxfVPort *vport);
DxfVPort *dxf_vport_set_target (DxfVPort *vport, DxfPoint *target);
double dxf_vport_get_target_x (DxfVPort *vport);
DxfVPort *dxf_vport_set_target_x (DxfVPort *vport, double target_x);
double dxf_vport_get_target_y (DxfVPort *vport);
DxfVPort *dxf_vport_set_target_y (DxfVPort *vport, double target_y);
double dxf_vport_get_target_z (DxfVPort *vport);
DxfVPort *dxf_vport_set_target_z (DxfVPort *vport, double target_z);
double dxf_vport_get_view_height (DxfVPort *vport);
DxfVPort *dxf_vport_set_view_height (DxfVPort *vport, double view_height);
double dxf_vport_get_viewport_aspect_ratio (DxfVPort *vport);
DxfVPort *dxf_vport_set_viewport_aspect_ratio (DxfVPort *vport, double viewport_aspect_ratio);
double dxf_vport_get_lens_length (DxfVPort *vport);
DxfVPort *dxf_vport_set_lens_length (DxfVPort *vport, double lens_length);
double dxf_vport_get_front_plane_offset (DxfVPort *vport);
DxfVPort *dxf_vport_set_front_plane_offset (DxfVPort *vport, double front_plane_offset);
double dxf_vport_get_back_plane_offset (DxfVPort *vport);
DxfVPort *dxf_vport_set_back_plane_offset (DxfVPort *vport, double back_plane_offset);
double dxf_vport_get_snap_rotation_angle (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_rotation_angle (DxfVPort *vport, double snap_rotation_angle);
double dxf_vport_get_view_twist_angle (DxfVPort *vport);
DxfVPort *dxf_vport_set_view_twist_angle (DxfVPort *vport, double view_twist_angle);
int dxf_vport_get_status_field (DxfVPort *vport);
DxfVPort *dxf_vport_set_status_field (DxfVPort *vport, int status_field);
int dxf_vport_get_id (DxfVPort *vport);
DxfVPort *dxf_vport_set_id (DxfVPort *vport, int id);
int dxf_vport_get_standard_flag (DxfVPort *vport);
DxfVPort *dxf_vport_set_standard_flag (DxfVPort *vport, int standard_flag);
int dxf_vport_get_view_mode (DxfVPort *vport);
DxfVPort *dxf_vport_set_view_mode (DxfVPort *vport, int view_mode);
int dxf_vport_get_circle_zoom_percent (DxfVPort *vport);
DxfVPort *dxf_vport_set_circle_zoom_percent (DxfVPort *vport, int circle_zoom_percent);
int dxf_vport_get_fast_zoom_setting (DxfVPort *vport);
DxfVPort *dxf_vport_set_fast_zoom_setting (DxfVPort *vport, int fast_zoom_setting);
int dxf_vport_get_UCSICON_setting (DxfVPort *vport);
DxfVPort *dxf_vport_set_UCSICON_setting (DxfVPort *vport, int UCSICON_setting);
int dxf_vport_get_snap_on (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_on (DxfVPort *vport, int snap_on);
int dxf_vport_get_grid_on (DxfVPort *vport);
DxfVPort *dxf_vport_set_grid_on (DxfVPort *vport, int grid_on);
int dxf_vport_get_snap_style (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_style (DxfVPort *vport, int snap_style);
int dxf_vport_get_snap_isopair (DxfVPort *vport);
DxfVPort *dxf_vport_set_snap_isopair (DxfVPort *vport, int snap_isopair);
char *dxf_vport_get_dictionary_owner_soft (DxfVPort *vport);
DxfVPort *dxf_vport_set_dictionary_owner_soft (DxfVPort *vport, char *dictionary_owner_soft);
char *dxf_vport_get_dictionary_owner_hard (DxfVPort *vport);
DxfVPort *dxf_vport_set_dictionary_owner_hard (DxfVPort *vport, char *dictionary_owner_hard);
DxfVPort *dxf_vport_get_next (DxfVPort *vport);
DxfVPort *dxf_vport_set_next (DxfVPort *vport, DxfVPort *next);
DxfVPort *dxf_vport_get_last (DxfVPort *vport);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_VPORT_H */


/* EOF */
