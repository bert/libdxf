/*!
 * \file viewport.h
 *
 * \author Copyright (C) 2010 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF viewport entity (\c VIEWPORT).
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
dxf_viewport
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
        int acad_version_number;
                /*!< AutoCAD version number. */
        /* Specific members for a DXF viewport. */
        double x0;
                /*!< X-value of the center point of entity in paper
                 * space coordinates.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the center point of entity in paper
                 * space coordinates.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the center point of entity in paper
                 * space coordinates.\n
                 * Group code = 30. */
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
                 * For Releases 11 and 12, this field will always be
                 * the integer 16.\n
                 * Group code = 1070. */
        double x_target;
                /*!< View target point X-value.\n
                 * Group code = 1010. */
        double y_target;
                /*!< View target point Y-value.\n
                 * Group code = 1020. */
        double z_target;
                /*!< View target point Z-value.\n
                 * Group code = 1030. */
        double x_direction;
                /*!< View direction from target point X-value.\n
                 * Group code = 1010. */
        double y_direction;
                /*!< View direction from target point Y-value.\n
                 * Group code = 1020. */
        double z_direction;
                /*!< View direction from target point Z-value.\n
                 * Group code = 1030. */
        double view_twist_angle;
                /*!< group code = 1040. */
        double view_height;
                /*!< group code = 1040. */
        double x_center;
                /*!< group code = 1040\n
                 * view center point X-value. */
        double y_center;
                /*!< group code = 1040\n
                 * view center point Y-value. */
        double perspective_lens_length;
                /*!< group code = 1040. */
        double front_plane_offset;
                /*!< group code = 1040\n
                 * front clipping plane - offset from target point. */
        double back_plane_offset;
                /*!< group code = 1040\n
                 * back clipping plane - offset from target point. */
        int view_mode;
                /*!< group code = 1070\n
                 * View mode. */
        int circle_zoom_percent;
                /*!< group code = 1070. */
        int fast_zoom_setting;
                /*!< group code = 1070. */
        int UCSICON_setting;
                /*!< group code = 1070. */
        int snap_on;
                /*!< group code = 1070. */
        int grid_on;
                /*!< group code = 1070. */
        int snap_style;
                /*!< group code = 1070. */
        int snap_isopair;
                /*!< group code = 1070. */
        double snap_rotation_angle;
                /*!< group code = 1040. */
        double x_snap_base;
                /*!< group code = 1040.\n
                 * snap base point UCS X-coordinate. */
        double y_snap_base;
                /*!< group code = 1040.\n
                 * snap base point UCS Y-coordinate. */
        double x_snap_spacing;
                /*!< group code = 1040. */
        double y_snap_spacing;
                /*!< group code = 1040. */
        double x_grid_spacing;
                /*!< group code = 1040. */
        double y_grid_spacing;
                /*!< group code = 1040. */
        int plot_flag;
                /*!< Hidden in plot flag.\n
                 * Group code = 1070. */
        char *frozen_layer_list_begin;
                /*!< Begin frozen layer list (possibly empty).\n
                 * This field will always be the string "{".\n
                 * Group code = 1002. */
        char *frozen_layers[DXF_MAX_LAYERS];
                /*!< The names of layers frozen in this viewport.\n
                 * This list may include Xref-dependent layers.\n
                 * Any number of 1003 groups may appear here.\n
                 * Group code = 1003.\n
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
                /*!< pointer to the next DxfViewport.\n
                 * \c NULL in the last DxfViewport. */
} DxfViewport;


DxfViewport *
dxf_viewport_new ();
DxfViewport *
dxf_viewport_init
(
        DxfViewport *dxf_viewport
);
int
dxf_viewport_read
(
        DxfFile *fp,
        DxfViewport *dxf_viewport
);
int
dxf_viewport_write
(
        DxfFile *fp,
        DxfViewport *dxf_viewport
);
int
dxf_viewport_free
(
        DxfViewport *dxf_viewport
);


#endif /* LIBDXF_SRC_VIEWPORT_H */


/* EOF */
