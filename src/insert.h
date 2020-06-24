/*!
 * \file insert.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2016, 2017, 2018,
 * 2020 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF insert entity (\c INSERT).
 *
 * A DXF \c INSERT entity is an insertion for a (external) \c BLOCK entity.\n
 * Whilst a \c BLOCK only resides in the block table only once as a
 * definition, an \c INSERT entity can insert blocks as singlular entities
 * and also as [rectanglar, polar] arrays in the drawing.
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


#ifndef LIBDXF_SRC_INSERT_H
#define LIBDXF_SRC_INSERT_H


#include "global.h"
#include "point.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD block or external reference insert
 * entity.
 */
typedef struct
dxf_insert_struct
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
        /* Specific members for a DXF insert. */
        char *block_name;
                /*!< group code = 2. */
        DxfPoint *p0;
                /*!< Base point.\n
                 * Group codes = 10, 20 and 30.*/
        double rel_x_scale;
                /*!< Relative scale along the X-axis.\n
                 * Optional, defaults to 1.0.\n
                 * Group code = 41. */
        double rel_y_scale;
                /*!< Relative scale along the Y-axis.\n
                 * Optional, defaults to 1.0.\n
                 * Group code = 42. */
        double rel_z_scale;
                /*!< Relative scale along the Z-axis.\n
                 * Optional, defaults to 1.0.\n
                 * Group code = 43. */
        double column_spacing;
                /*!< Column spacing.\n
                 * Optional, defaults to 0.0.\n
                 * Group code = 44. */
        double row_spacing;
                /*!< Row spacing.\n
                 * Optional, defaults to 0.0.\n
                 * Group code = 45. */
        double rot_angle;
                /*!< Rotation angle.\n
                 * Optional, defaults to 0.0.\n
                 * Group code = 50. */
        int attributes_follow;
                /*!< Attributes follow flag.\n
                 * Optional, defaults to 0\n
                 * If the value of the "Attributes follow" flag is 1,
                 * a series of Attribute (Attrib) entities is expected to
                 * follow the Insert, terminated by a sequence end (Seqend)
                 * entity.\n
                 * Group code = 66. */
        int columns;
                /*!< Number of columns.\n
                 * Optional, defaults to 1.\n
                 * Group code = 70. */
        int rows;
                /*!< Number of rows.\n
                 * Optional, defaults to 1.\n
                 * Group code = 71. */
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
        struct DxfInsert *next;
                /*!< pointer to the next DxfInsert.\n
                 * \c NULL in the last DxfInsert. */
} DxfInsert;


DxfInsert *dxf_insert_new ();
DxfInsert *dxf_insert_init (DxfInsert *insert);
DxfInsert *dxf_insert_read (DxfFile *fp, DxfInsert *insert);
int dxf_insert_write (DxfFile *fp, DxfInsert *insert);
int dxf_insert_free (DxfInsert *insert);
void dxf_insert_free_list (DxfInsert *inserts);
int dxf_insert_get_id_code (DxfInsert *insert);
DxfInsert *dxf_insert_set_id_code (DxfInsert *insert, int id_code);
char *dxf_insert_get_linetype (DxfInsert *insert);
DxfInsert *dxf_insert_set_linetype (DxfInsert *insert, char *linetype);
char *dxf_insert_get_layer (DxfInsert *insert);
DxfInsert *dxf_insert_set_layer (DxfInsert *insert, char *layer);
double dxf_insert_get_elevation (DxfInsert *insert);
DxfInsert *dxf_insert_set_elevation (DxfInsert *insert, double elevation);
double dxf_insert_get_thickness (DxfInsert *insert);
DxfInsert *dxf_insert_set_thickness (DxfInsert *insert, double thickness);
double dxf_insert_get_linetype_scale (DxfInsert *insert);
DxfInsert *dxf_insert_set_linetype_scale (DxfInsert *insert, double linetype_scale);
int16_t dxf_insert_get_visibility (DxfInsert *insert);
DxfInsert *dxf_insert_set_visibility (DxfInsert *insert, int16_t visibility);
int dxf_insert_get_color (DxfInsert *insert);
DxfInsert *dxf_insert_set_color (DxfInsert *insert, int color);
int dxf_insert_get_paperspace (DxfInsert *insert);
DxfInsert *dxf_insert_set_paperspace (DxfInsert *insert, int paperspace);
int dxf_insert_get_graphics_data_size (DxfInsert *insert);
DxfInsert *dxf_insert_set_graphics_data_size (DxfInsert *insert, int graphics_data_size);
int16_t dxf_insert_get_shadow_mode (DxfInsert *insert);
DxfInsert *dxf_insert_set_shadow_mode (DxfInsert *insert, int16_t shadow_mode);
DxfBinaryData *dxf_insert_get_binary_graphics_data (DxfInsert *insert);
DxfInsert *dxf_insert_set_binary_graphics_data (DxfInsert *insert, DxfBinaryData *data);
char *dxf_insert_get_dictionary_owner_soft (DxfInsert *insert);
DxfInsert *dxf_insert_set_dictionary_owner_soft (DxfInsert *insert, char *dictionary_owner_soft);
char *dxf_insert_get_material (DxfInsert *insert);
DxfInsert *dxf_insert_set_material (DxfInsert *insert, char *material);
char *dxf_insert_get_dictionary_owner_hard (DxfInsert *insert);
DxfInsert *dxf_insert_set_dictionary_owner_hard (DxfInsert *insert, char *dictionary_owner_hard);
int16_t dxf_insert_get_lineweight (DxfInsert *insert);
DxfInsert *dxf_insert_set_lineweight (DxfInsert *insert, int16_t lineweight);
char *dxf_insert_get_plot_style_name (DxfInsert *insert);
DxfInsert *dxf_insert_set_plot_style_name (DxfInsert *insert, char *plot_style_name);
long dxf_insert_get_color_value (DxfInsert *insert);
DxfInsert *dxf_insert_set_color_value (DxfInsert *insert, long color_value);
char *dxf_insert_get_color_name (DxfInsert *insert);
DxfInsert *dxf_insert_set_color_name (DxfInsert *insert, char *color_name);
long dxf_insert_get_transparency (DxfInsert *insert);
DxfInsert *dxf_insert_set_transparency (DxfInsert *insert, long transparency);
char *dxf_insert_get_block_name (DxfInsert *insert);
DxfInsert *dxf_insert_set_block_name (DxfInsert *insert, char *block_name);
DxfPoint *dxf_insert_get_p0 (DxfInsert *insert);
DxfInsert *dxf_insert_set_p0 (DxfInsert *insert, DxfPoint *p0);
double dxf_insert_get_x0 (DxfInsert *insert);
DxfInsert *dxf_insert_set_x0 (DxfInsert *insert, double x0);
double dxf_insert_get_y0 (DxfInsert *insert);
DxfInsert *dxf_insert_set_y0 (DxfInsert *insert, double y0);
double dxf_insert_get_z0 (DxfInsert *insert);
DxfInsert *dxf_insert_set_z0 (DxfInsert *insert, double z0);
double dxf_insert_get_rel_x_scale (DxfInsert *insert);
DxfInsert *dxf_insert_set_rel_x_scale (DxfInsert *insert, double rel_x_scale);
double dxf_insert_get_rel_y_scale (DxfInsert *insert);
DxfInsert *dxf_insert_set_rel_y_scale (DxfInsert *insert, double rel_y_scale);
double dxf_insert_get_rel_z_scale (DxfInsert *insert);
DxfInsert *dxf_insert_set_rel_z_scale (DxfInsert *insert, double rel_z_scale);
double dxf_insert_get_column_spacing (DxfInsert *insert);
DxfInsert *dxf_insert_set_column_spacing (DxfInsert *insert, double column_spacing);
double dxf_insert_get_row_spacing (DxfInsert *insert);
DxfInsert *dxf_insert_set_row_spacing (DxfInsert *insert, double row_spacing);
double dxf_insert_get_rot_angle (DxfInsert *insert);
DxfInsert *dxf_insert_set_rot_angle (DxfInsert *insert, double rot_angle);
int dxf_insert_get_attributes_follow (DxfInsert *insert);
DxfInsert *dxf_insert_set_attributes_follow (DxfInsert *insert, int attributes_follow);
int dxf_insert_get_columns (DxfInsert *insert);
DxfInsert *dxf_insert_set_columns (DxfInsert *insert, int columns);
int dxf_insert_get_rows (DxfInsert *insert);
DxfInsert *dxf_insert_set_rows (DxfInsert *insert, int rows);
double dxf_insert_get_extr_x0 (DxfInsert *insert);
DxfInsert *dxf_insert_set_extr_x0 (DxfInsert *insert, double extr_x0);
double dxf_insert_get_extr_y0 (DxfInsert *insert);
DxfInsert *dxf_insert_set_extr_y0 (DxfInsert *insert, double extr_y0);
double dxf_insert_get_extr_z0 (DxfInsert *insert);
DxfInsert *dxf_insert_set_extr_z0 (DxfInsert *insert, double extr_z0);
DxfInsert *dxf_insert_set_extrusion_vector_from_point (DxfInsert *insert, DxfPoint *point);
DxfInsert *dxf_insert_set_extrusion_vector (DxfInsert *insert, double extr_x0, double extr_y0, double extr_z0);
DxfInsert *dxf_insert_get_next (DxfInsert *insert);
DxfInsert *dxf_insert_set_next (DxfInsert *insert, DxfInsert *next);
DxfInsert *dxf_insert_get_last (DxfInsert *insert);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_INSERT_H */


/* EOF */
