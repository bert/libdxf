/*!
 * \file point.h
 *
 * \author Copyright (C) 2008, 2009, 2010, 2012, 2014, 2015, 2016, 2017,
 * 2018, 2019, 2020 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Header file for a DXF point entity (\c POINT).
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

#ifndef LIBDXF_SRC_POINT_H
#define LIBDXF_SRC_POINT_H


#include "global.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD point entity.
 *
 * \c POINT entities have an optional 50 group that determines the
 * orientation of PDMODE images.\n
 * The group value is the negative of the Entity Coordinate Systems (ECS)
 * angle of the UCS X axis in effect when the point was drawn.\n
 * The X axis of the UCS in effect when the point was drawn is always
 * parallel to the XY plane for the point's ECS, and the angle between the
 * UCS X axis and the ECS X axis is a single 2D angle.\n
 * The value in group 50 is the angle from horizontal (the effective X axis)
 * to the ECS X axis.\n
 * Entity Coordinate Systems (ECS) are described in the UCS section.\n
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2014.
 */
typedef struct
dxf_point_struct
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
        double elevation;
                /*!< group code = 38\n
                 * Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default). */
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
        int16_t color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int16_t paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
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
        DxfBinaryData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle  to owner BLOCK_RECORD object.\n
                 * Group code = 330.\n
                 * \since Introduced in version R2000. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347. */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
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
        /* Specific members for a DXF point. */
        double x0;
                /*!< group code = 10. */
        double y0;
                /*!< group code = 20. */
        double z0;
                /*!< group code = 30. */
        double angle_to_X;
                /*!< group code 50.\n
                 * Angle of the X axis for the UCS in effect when the
                 * point was drawn (optional, default = 0.0); used when
                 * \c PDMODE is nonzero. */
        double extr_x0;
                /*!< group code = 210\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_y0;
                /*!< group code = 220\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_z0;
                /*!< group code = 230\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 1.0. */
        struct DxfPoint *next;
                /*!< pointer to the next DxfPoint.\n
                 * \c NULL in the last DxfPoint. */
} DxfPoint;


DxfPoint *dxf_point_new ();
DxfPoint *dxf_point_init (DxfPoint *point);
DxfPoint *dxf_point_read (DxfFile *fp, DxfPoint *point);
int dxf_point_write (DxfFile *fp, DxfPoint *point);
int dxf_point_free (DxfPoint *point);
void dxf_point_free_list (DxfPoint *points);
int dxf_point_get_id_code (DxfPoint *point);
DxfPoint *dxf_point_set_id_code (DxfPoint *point, int id_code);
char *dxf_point_get_linetype (DxfPoint *point);
DxfPoint *dxf_point_set_linetype (DxfPoint *point, char *linetype);
char *dxf_point_get_layer (DxfPoint *point);
DxfPoint *dxf_point_set_layer (DxfPoint *point, char *layer);
double dxf_point_get_elevation (DxfPoint *point);
DxfPoint *dxf_point_set_elevation (DxfPoint *point, double elevation);
double dxf_point_get_thickness (DxfPoint *point);
DxfPoint *dxf_point_set_thickness (DxfPoint *point, double thickness);
double dxf_point_get_linetype_scale (DxfPoint *point);
DxfPoint *dxf_point_set_linetype_scale (DxfPoint *point, double linetype_scale);
int16_t dxf_point_get_visibility (DxfPoint *point);
DxfPoint *dxf_point_set_visibility (DxfPoint *point, int16_t visibility);
int16_t dxf_point_get_color (DxfPoint *point);
DxfPoint *dxf_point_set_color (DxfPoint *point, int16_t color);
int16_t dxf_point_get_paperspace (DxfPoint *point);
DxfPoint *dxf_point_set_paperspace (DxfPoint *point, int16_t paperspace);
int32_t dxf_point_get_graphics_data_size (DxfPoint *point);
DxfPoint *dxf_point_set_graphics_data_size (DxfPoint *point, int32_t graphics_data_size);
int16_t dxf_point_get_shadow_mode (DxfPoint *point);
DxfPoint *dxf_point_set_shadow_mode (DxfPoint *point, int16_t shadow_mode);
DxfBinaryData *dxf_point_get_binary_graphics_data (DxfPoint *point);
DxfPoint *dxf_point_set_binary_graphics_data (DxfPoint *point, DxfBinaryData *data);
char *dxf_point_get_dictionary_owner_soft (DxfPoint *point);
DxfPoint *dxf_point_set_dictionary_owner_soft (DxfPoint *point, char *dictionary_owner_soft);
char *dxf_point_get_material (DxfPoint *point);
DxfPoint *dxf_point_set_material (DxfPoint *point, char *material);
char *dxf_point_get_dictionary_owner_hard (DxfPoint *point);
DxfPoint *dxf_point_set_dictionary_owner_hard (DxfPoint *point, char *dictionary_owner_hard);
int16_t dxf_point_get_lineweight (DxfPoint *point);
DxfPoint *dxf_point_set_lineweight (DxfPoint *point, int16_t lineweight);
char *dxf_point_get_plot_style_name (DxfPoint *point);
DxfPoint *dxf_point_set_plot_style_name (DxfPoint *point, char *plot_style_name);
int32_t dxf_point_get_color_value (DxfPoint *point);
DxfPoint *dxf_point_set_color_value (DxfPoint *point, int32_t color_value);
char *dxf_point_get_color_name (DxfPoint *point);
DxfPoint *dxf_point_set_color_name (DxfPoint *point, char *color_name);
int32_t dxf_point_get_transparency (DxfPoint *point);
DxfPoint *dxf_point_set_transparency (DxfPoint *point, int32_t transparency);
double dxf_point_get_x0 (DxfPoint *point);
DxfPoint *dxf_point_set_x0 (DxfPoint *point, double x0);
double dxf_point_get_y0 (DxfPoint *point);
DxfPoint *dxf_point_set_y0 (DxfPoint *point, double y0);
double dxf_point_get_z0 (DxfPoint *point);
DxfPoint *dxf_point_set_z0 (DxfPoint *point, double z0);
double dxf_point_get_angle_to_X (DxfPoint *point);
DxfPoint *dxf_point_set_angle_to_X (DxfPoint *point, double angle_to_X);
DxfPoint *dxf_point_get_extrusion_vector_as_point (DxfPoint *point);
DxfPoint *dxf_point_set_extrusion_vector (DxfPoint *point, double extr_x0, double extr_y0, double extr_z0);
DxfPoint *dxf_point_get_next (DxfPoint *point);
DxfPoint *dxf_point_set_next (DxfPoint *point, DxfPoint *next);
DxfPoint *dxf_point_get_last (DxfPoint *point);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_POINT_H */


/* EOF */
