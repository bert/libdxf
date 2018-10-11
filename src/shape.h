/*!
 * \file shape.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF shape entity (\c SHAPE).
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


#ifndef LIBDXF_SRC_SHAPE_H
#define LIBDXF_SRC_SHAPE_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD shape entity.
 */
typedef struct
dxf_shape_struct
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
        /* Specific members for a DXF shape. */
        char *shape_name;
                /*!< Shape name.\n
                 * Group code = 2. */
        DxfPoint *p0;
                /*!< Insertion point (in WCS).\n
                 * Group codes = 10, 20 and 30.*/
        double x0;
                /*!< X-value of the insertion point (in WCS).\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the insertion point (in WCS).\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the insertion point (in WCS).\n
                 * Group code = 30. */
        double size;
                /*!< Size.\n
                 * Group code = 40. */
        double rel_x_scale;
                /*!< Relative X scale factor (optional; default =1.0).\n
                 * Group code = 41. */
        double rot_angle;
                /*!< Rotation angle (optional; default = 0.0).\n
                 * Group code = 50. */
        double obl_angle;
                /*!< Oblique angle (optional; default =0.0).\n
                 * Group code = 51. */
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
        struct DxfShape *next;
                /*!< Pointer to the next DxfShape.\n
                 * \c NULL in the last DxfShape. */
} DxfShape;


DxfShape *dxf_shape_new ();
DxfShape *dxf_shape_init (DxfShape *shape);
DxfShape *dxf_shape_read (DxfFile *fp, DxfShape *shape);
int dxf_shape_write (DxfFile *fp, DxfShape *shape);
int dxf_shape_free (DxfShape *shape);
void dxf_shape_free_list (DxfShape *shapes);
int dxf_shape_get_id_code (DxfShape *shape);
DxfShape *dxf_shape_set_id_code (DxfShape *shape, int id_code);
char *dxf_shape_get_linetype (DxfShape *shape);
DxfShape *dxf_shape_set_linetype (DxfShape *shape, char *linetype);
char *dxf_shape_get_layer (DxfShape *shape);
DxfShape *dxf_shape_set_layer (DxfShape *shape, char *layer);
double dxf_shape_get_elevation (DxfShape *shape);
DxfShape *dxf_shape_set_elevation (DxfShape *shape, double elevation);
double dxf_shape_get_thickness (DxfShape *shape);
DxfShape *dxf_shape_set_thickness (DxfShape *shape, double thickness);
double dxf_shape_get_linetype_scale (DxfShape *shape);
DxfShape *dxf_shape_set_linetype_scale (DxfShape *shape, double linetype_scale);
int16_t dxf_shape_get_visibility (DxfShape *shape);
DxfShape *dxf_shape_set_visibility (DxfShape *shape, int16_t visibility);
int dxf_shape_get_color (DxfShape *shape);
DxfShape *dxf_shape_set_color (DxfShape *shape, int color);
int dxf_shape_get_paperspace (DxfShape *shape);
DxfShape *dxf_shape_set_paperspace (DxfShape *shape, int paperspace);
int dxf_shape_get_graphics_data_size (DxfShape *shape);
DxfShape *dxf_shape_set_graphics_data_size (DxfShape *shape, int graphics_data_size);
int16_t dxf_shape_get_shadow_mode (DxfShape *shape);
DxfShape *dxf_shape_set_shadow_mode (DxfShape *shape, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_shape_get_binary_graphics_data (DxfShape *shape);
DxfShape *dxf_shape_set_binary_graphics_data (DxfShape *shape, DxfBinaryGraphicsData *data);
char *dxf_shape_get_dictionary_owner_soft (DxfShape *shape);
DxfShape *dxf_shape_set_dictionary_owner_soft (DxfShape *shape, char *dictionary_owner_soft);
char *dxf_shape_get_material (DxfShape *shape);
DxfShape *dxf_shape_set_material (DxfShape *shape, char *material);
char *dxf_shape_get_dictionary_owner_hard (DxfShape *shape);
DxfShape *dxf_shape_set_dictionary_owner_hard (DxfShape *shape, char *dictionary_owner_hard);
int16_t dxf_shape_get_lineweight (DxfShape *shape);
DxfShape *dxf_shape_set_lineweight (DxfShape *shape, int16_t lineweight);
char *dxf_shape_get_plot_style_name (DxfShape *shape);
DxfShape *dxf_shape_set_plot_style_name (DxfShape *shape, char *plot_style_name);
long dxf_shape_get_color_value (DxfShape *shape);
DxfShape *dxf_shape_set_color_value (DxfShape *shape, long color_value);
char *dxf_shape_get_color_name (DxfShape *shape);
DxfShape *dxf_shape_set_color_name (DxfShape *shape, char *color_name);
long dxf_shape_get_transparency (DxfShape *shape);
DxfShape *dxf_shape_set_transparency (DxfShape *shape, long transparency);
DxfPoint *dxf_shape_get_p0 (DxfShape *shape);
DxfShape *dxf_shape_set_p0 (DxfShape *shape, DxfPoint *p0);
double dxf_shape_get_x0 (DxfShape *shape);
DxfShape *dxf_shape_set_x0 (DxfShape *shape, double x0);
double dxf_shape_get_y0 (DxfShape *shape);
DxfShape *dxf_shape_set_y0 (DxfShape *shape, double y0);
double dxf_shape_get_z0 (DxfShape *shape);
DxfShape *dxf_shape_set_z0 (DxfShape *shape, double z0);
double dxf_shape_get_size (DxfShape *shape);
DxfShape *dxf_shape_set_size (DxfShape *shape, double size);
double dxf_shape_get_rel_x_scale (DxfShape *shape);
DxfShape *dxf_shape_set_rel_x_scale (DxfShape *shape, double rel_x_scale);
double dxf_shape_get_rot_angle (DxfShape *shape);
DxfShape *dxf_shape_set_rot_angle (DxfShape *shape, double rot_angle);
double dxf_shape_get_obl_angle (DxfShape *shape);
DxfShape *dxf_shape_set_obl_angle (DxfShape *shape, double obl_angle);
double dxf_shape_get_extr_x0 (DxfShape *shape);
DxfShape *dxf_shape_set_extr_x0 (DxfShape *shape, double extr_x0);
double dxf_shape_get_extr_y0 (DxfShape *shape);
DxfShape *dxf_shape_set_extr_y0 (DxfShape *shape, double extr_y0);
double dxf_shape_get_extr_z0 (DxfShape *shape);
DxfShape *dxf_shape_set_extr_z0 (DxfShape *shape, double extr_z0);
DxfShape *dxf_shape_get_next (DxfShape *shape);
DxfShape *dxf_shape_set_next (DxfShape *shape, DxfShape *next);
DxfShape *dxf_shape_get_last (DxfShape *shape);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_SHAPE_H */


/* EOF */
