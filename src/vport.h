/*!
 * \file vport.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF viewport entity (\c VPORT).
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
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD viewport entity.
 *
 * The VPORT table is unique in that it may contain several entries with the
 * same name (indicating a multiple-viewport configuration).\n
 * The entries corresponding to the active viewport configuration all have
 * the name *ACTIVE.\n
 * The first such entry describes the current viewport.
 */
typedef struct
dxf_vport
{
        int id_code;
                /*!< group code = 5. */
        char *viewport_name;
                /*!< group code = 2. */
        double x_min;
                /*!< group code = 10\n
                 * lower-left corner of viewport; 0.0 to 1.0. */
        double y_min;
                /*!< group code = 20\n
                 * lower-left corner of viewport; 0.0 to 1.0. */
        double x_max;
                /*!< group code = 11\n
                 * upper-right corner. */
        double y_max;
                /*!< group code = 21\n
                 * upper-right corner. */
        double x_center;
                /*!< group code = 12\n
                 * view center point, in World Coordinate System. */
        double y_center;
                /*!< group code = 22\n
                 * view center point, in World Coordinate System. */
        double x_snap_base;
                /*!< group code = 13\n
                 * snap base point. */
        double y_snap_base;
                /*!< group code = 23\n
                 * snap base point. */
        double x_snap_spacing;
                /*!< group code = 14. */
        double y_snap_spacing;
                /*!< group code = 24. */
        double x_grid_spacing;
                /*!< group code = 15. */
        double y_grid_spacing;
                /*!< group code = 25. */
        double x_direction;
                /*!< group code = 16\n
                 * view direction from target point. */
        double y_direction;
                /*!< group code = 26\n
                 * view direction from target point. */
        double z_direction;
                /*!< group code = 36\n
                 * view direction from target point. */
        double x_target;
                /*!< group code = 17\n
                 * view target point. */
        double y_target;
                /*!< group code = 27\n
                 * view target point. */
        double z_target;
                /*!< group code = 37\n
                 * view target point. */
        double view_height;
                /*!< group code = 40. */
        double viewport_aspect_ratio;
                /*!< group code = 41. */
        double lens_length;
                /*!< group code = 42. */
        double front_plane_offset;
                /*!< group code = 43\n
                 * front clipping plane - offset from target point. */
        double back_plane_offset;
                /*!< group code = 44\n
                 * back clipping plane - offset from target point. */
        double snap_rotation_angle;
                /*!< group code = 50. */
        double view_twist_angle;
                /*!< group code = 51. */
        int status_field;
                /*!< group code = 68. */
        int id;
                /*!< group code = 69. */
        int standard_flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 16 = if set, table entry is externally dependent on an
                 *         Xref\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *         dependent Xref has been successfully resolved\n
                 * 64 = if set, the table entry was referenced by at least
                 *         one entity in the drawing the last time the drawing
                 *         was edited.\n
                 * This flag is for the benefit of AutoCAD commands; it can
                 * be ignored by most programs that read DXF files, and need
                 * not be set by programs that write DXF files.\n */
        int view_mode;
                /*!< group code = 71\n
                 * see VIEWMODE system variable in appendix A. */
        int circle_zoom_percent;
                /*!< group code = 72. */
        int fast_zoom_setting;
                /*!< group code = 73. */
        int UCSICON_setting;
                /*!< group code = 74. */
        int snap_on;
                /*!< group code = 75. */
        int grid_on;
                /*!< group code = 76. */
        int snap_style;
                /*!< group code = 77. */
        int snap_isopair;
                /*!< group code = 78. */
        int acad_version_number;
                /*!< AutoCAD version number. */

} DxfVPort, * DxfVPortPtr;


#endif /* LIBDXF_SRC_VPORT_H */


/* EOF */
