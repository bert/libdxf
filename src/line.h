/*!
 * \file line.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017,
 * 2018, 2020 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF line entity (\c LINE).
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_LINE_H
#define LIBDXF_SRC_LINE_H


#include "global.h"
#include "binary_data.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD line entity.
 */
typedef struct
dxf_line_struct
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
                /*!< Start point for the line.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< End point for the line.\n
                 * Group codes = 11, 21 and 31.*/
        double extr_x0;
                /*!< X value of the extrusion direction.\n
                 * Optional, if ommited defaults to 0.0.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y value of the extrusion direction.\n
                 * Optional, if ommited defaults to 0.0.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z value of the extrusion direction.\n
                 * Optional, if ommited defaults to 1.0.\n
                 * Group code = 230. */
        struct DxfLine *next;
                /*!< pointer to the next DxfLine.\n
                 * \c NULL in the last DxfLine. */
} DxfLine;


DxfLine *dxf_line_new ();
DxfLine *dxf_line_init (DxfLine *line);
DxfLine *dxf_line_read (DxfFile *fp, DxfLine *line);
int dxf_line_write (DxfFile *fp, DxfLine *line);
int dxf_line_free (DxfLine *line);
void dxf_line_free_list (DxfLine *lines);
int dxf_line_get_id_code (DxfLine *line);
DxfLine *dxf_line_set_id_code (DxfLine *line, int id_code);
char *dxf_line_get_linetype (DxfLine *line);
DxfLine *dxf_line_set_linetype (DxfLine *line, char *linetype);
char *dxf_line_get_layer (DxfLine *line);
DxfLine *dxf_line_set_layer (DxfLine *line, char *layer);
double dxf_line_get_elevation (DxfLine *line);
DxfLine *dxf_line_set_elevation (DxfLine *line, double elevation);
double dxf_line_get_thickness (DxfLine *line);
DxfLine *dxf_line_set_thickness (DxfLine *line, double thickness);
double dxf_line_get_linetype_scale (DxfLine *line);
DxfLine *dxf_line_set_linetype_scale (DxfLine *line, double linetype_scale);
int16_t dxf_line_get_visibility (DxfLine *line);
DxfLine *dxf_line_set_visibility (DxfLine *line, int16_t visibility);
int16_t dxf_line_get_color (DxfLine *line);
DxfLine *dxf_line_set_color (DxfLine *line, int16_t color);
int16_t dxf_line_get_paperspace (DxfLine *line);
DxfLine *dxf_line_set_paperspace (DxfLine *line, int16_t paperspace);
int32_t dxf_line_get_graphics_data_size (DxfLine *line);
DxfLine *dxf_line_set_graphics_data_size (DxfLine *line, int32_t graphics_data_size);
int16_t dxf_line_get_shadow_mode (DxfLine *line);
DxfLine *dxf_line_set_shadow_mode (DxfLine *line, int16_t shadow_mode);
DxfBinaryData *dxf_line_get_binary_graphics_data (DxfLine *line);
DxfLine *dxf_line_set_binary_graphics_data (DxfLine *line, DxfBinaryData *data);
char *dxf_line_get_dictionary_owner_soft (DxfLine *line);
DxfLine *dxf_line_set_dictionary_owner_soft (DxfLine *line, char *dictionary_owner_soft);
char *dxf_line_get_material (DxfLine *line);
DxfLine *dxf_line_set_material (DxfLine *line, char *material);
char *dxf_line_get_dictionary_owner_hard (DxfLine *line);
DxfLine *dxf_line_set_dictionary_owner_hard (DxfLine *line, char *dictionary_owner_hard);
int16_t dxf_line_get_lineweight (DxfLine *line);
DxfLine *dxf_line_set_lineweight (DxfLine *line, int16_t lineweight);
char *dxf_line_get_plot_style_name (DxfLine *line);
DxfLine *dxf_line_set_plot_style_name (DxfLine *line, char *plot_style_name);
int32_t dxf_line_get_color_value (DxfLine *line);
DxfLine *dxf_line_set_color_value (DxfLine *line, int32_t color_value);
char *dxf_line_get_color_name (DxfLine *line);
DxfLine *dxf_line_set_color_name (DxfLine *line, char *color_name);
int32_t dxf_line_get_transparency (DxfLine *line);
DxfLine *dxf_line_set_transparency (DxfLine *line, int32_t transparency);
DxfPoint *dxf_line_get_p0 (DxfLine *line);
DxfLine *dxf_line_set_p0 (DxfLine *line, DxfPoint *p0);
double dxf_line_get_x0 (DxfLine *line);
DxfLine *dxf_line_set_x0 (DxfLine *line, double x0);
double dxf_line_get_y0 (DxfLine *line);
DxfLine *dxf_line_set_y0 (DxfLine *line, double y0);
double dxf_line_get_z0 (DxfLine *line);
DxfLine *dxf_line_set_z0 (DxfLine *line, double z0);
DxfPoint *dxf_line_get_p1 (DxfLine *line);
DxfLine *dxf_line_set_p1 (DxfLine *line, DxfPoint *p1);
double dxf_line_get_x1 (DxfLine *line);
DxfLine *dxf_line_set_x1 (DxfLine *line, double x1);
double dxf_line_get_y1 (DxfLine *line);
DxfLine *dxf_line_set_y1 (DxfLine *line, double y1);
double dxf_line_get_z1 (DxfLine *line);
DxfLine *dxf_line_set_z1 (DxfLine *line, double z1);
double dxf_line_get_extr_x0 (DxfLine *line);
DxfLine *dxf_line_set_extr_x0 (DxfLine *line, double extr_x0);
double dxf_line_get_extr_y0 (DxfLine *line);
DxfLine *dxf_line_set_extr_y0 (DxfLine *line, double extr_y0);
double dxf_line_get_extr_z0 (DxfLine *line);
DxfLine *dxf_line_set_extr_z0 (DxfLine *line, double extr_z0);
DxfPoint *dxf_line_get_extrusion_vector_as_point (DxfLine *line);
DxfLine *dxf_line_set_extrusion_vector (DxfLine *line, double extr_x0, double extr_y0, double extr_z0);
DxfLine *dxf_line_get_next (DxfLine *line);
DxfLine *dxf_line_set_next (DxfLine *line, DxfLine *next);
DxfLine *dxf_line_get_last (DxfLine *line);
DxfPoint *dxf_line_get_mid_point (DxfLine *line, int id_code, int inheritance);
double dxf_line_get_length (DxfLine *line);
DxfLine *dxf_line_create_from_points (DxfPoint *p1, DxfPoint *p2, int id_code, int inheritance);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LINE_H */


/* EOF */
