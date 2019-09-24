/*!
 * \file 3dline.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018, 2019
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF 3D line entity (\c 3DLINE).
 *
 * \warning This entity type is used in DXF versions R10 and R11 only,
 * it was obsoleted and removed in DXF version R12.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12 (forward compatibility).
 * \version According to DXF R13 (forward compatibility).
 * \version According to DXF R14 (forward compatibility).
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


#ifndef LIBDXF_SRC_3DLINE_H
#define LIBDXF_SRC_3DLINE_H


#include "global.h"
#include "point.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD line entity.
 */
typedef struct
dxf_3dline_struct
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
                 * to DXF version R12, or DXF_FLATLAND equals 0\n
                 * (default).\n
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
                /*!< Object visibility (optional):
                 * <ol>
                 * <li value = "0"> Visible.</li>
                 * <li value = "1"> Invisible.</li>
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
        /* Specific members for a DXF line. */
        DxfPoint *p0;
                /*!< Start point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< End point.\n
                 * Group codes = 11, 21 and 31. */
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
        struct Dxf3dline *next;
                /*!< pointer to the next Dxf3dline.\n
                 * \c NULL in the last Dxf3dline. */
} Dxf3dline;


Dxf3dline *dxf_3dline_new ();
Dxf3dline *dxf_3dline_init (Dxf3dline *line);
Dxf3dline *dxf_3dline_read (DxfFile *fp, Dxf3dline *line);
int dxf_3dline_write (DxfFile *fp, Dxf3dline *line);
int dxf_3dline_free (Dxf3dline *line);
void dxf_3dline_free_list (Dxf3dline *lines);
int dxf_3dline_get_id_code (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_id_code (Dxf3dline *line, int id_code);
char *dxf_3dline_get_linetype (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_linetype (Dxf3dline *line, char *linetype);
char *dxf_3dline_get_layer (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_layer (Dxf3dline *line, char *layer);
double dxf_3dline_get_elevation (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_elevation (Dxf3dline *line, double elevation);
double dxf_3dline_get_thickness (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_thickness (Dxf3dline *line, double thickness);
double dxf_3dline_get_linetype_scale (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_linetype_scale (Dxf3dline *line, double linetype_scale);
int16_t dxf_3dline_get_visibility (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_visibility (Dxf3dline *line, int16_t visibility);
int16_t dxf_3dline_get_color (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_color (Dxf3dline *line, int16_t color);
int16_t dxf_3dline_get_paperspace (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_paperspace (Dxf3dline *line, int16_t paperspace);
int32_t dxf_3dline_get_graphics_data_size (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_graphics_data_size (Dxf3dline *line, int32_t graphics_data_size);
int16_t dxf_3dline_get_shadow_mode (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_shadow_mode (Dxf3dline *line, int16_t shadow_mode);
DxfBinaryData *dxf_3dline_get_binary_graphics_data (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_binary_graphics_data (Dxf3dline *line, DxfBinaryData *data);
char *dxf_3dline_get_dictionary_owner_soft (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_dictionary_owner_soft (Dxf3dline *line, char *dictionary_owner_soft);
char *dxf_3dline_get_object_owner_soft (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_object_owner_soft (Dxf3dline *line, char *object_owner_soft);
char *dxf_3dline_get_material (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_material (Dxf3dline *line, char *material);
char *dxf_3dline_get_dictionary_owner_hard (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_dictionary_owner_hard (Dxf3dline *line, char *dictionary_owner_hard);
int16_t dxf_3dline_get_lineweight (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_lineweight (Dxf3dline *line, int16_t lineweight);
char *dxf_3dline_get_plot_style_name (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_plot_style_name (Dxf3dline *line, char *plot_style_name);
int32_t dxf_3dline_get_color_value (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_color_value (Dxf3dline *line, int32_t color_value);
char *dxf_3dline_get_color_name (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_color_name (Dxf3dline *line, char *color_name);
int32_t dxf_3dline_get_transparency (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_transparency (Dxf3dline *line, int32_t transparency);
DxfPoint *dxf_3dline_get_p0 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_p0 (Dxf3dline *line, DxfPoint *p0);
double dxf_3dline_get_x0 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_x0 (Dxf3dline *line, double x0);
double dxf_3dline_get_y0 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_y0 (Dxf3dline *line, double y0);
double dxf_3dline_get_z0 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_z0 (Dxf3dline *line, double z0);
DxfPoint *dxf_3dline_get_p1 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_p1 (Dxf3dline *line, DxfPoint *p1);
double dxf_3dline_get_x1 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_x1 (Dxf3dline *line, double x1);
double dxf_3dline_get_y1 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_y1 (Dxf3dline *line, double y1);
double dxf_3dline_get_z1 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_z1 (Dxf3dline *line, double z1);
double dxf_3dline_get_extr_x0 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_extr_x0 (Dxf3dline *line, double extr_x0);
double dxf_3dline_get_extr_y0 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_extr_y0 (Dxf3dline *line, double extr_y0);
double dxf_3dline_get_extr_z0 (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_extr_z0 (Dxf3dline *line, double extr_z0);
DxfPoint *dxf_3dline_get_extrusion_vector_as_point (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_extrusion_vector_from_point (Dxf3dline *line, DxfPoint *point);
Dxf3dline *dxf_3dline_set_extrusion_vector (Dxf3dline *line, double extr_x0, double extr_y0, double extr_z0);
DxfPoint *dxf_3dline_get_mid_point (Dxf3dline *line, int id_code, int inheritance);
double dxf_3dline_get_length (Dxf3dline *line);
Dxf3dline *dxf_3dline_create_from_points (DxfPoint *p0, DxfPoint *p1, int id_code, int inheritance);
Dxf3dline *dxf_3dline_get_next (Dxf3dline *line);
Dxf3dline *dxf_3dline_set_next (Dxf3dline *line, Dxf3dline *next);
Dxf3dline *dxf_3dline_get_last (Dxf3dline *line);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_3DLINE_H */


/* EOF */
