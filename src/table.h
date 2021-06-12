/*!
 * \file table.h
 *
 * \author Copyright (C) 2009, 2012, 2014, 2015, 2016, 2017, 2018, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Header file for of a DXF table entry (\c TABLE).
 *
 * \since The \c TABLE entity was introduced in DXF R2005.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2005.
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

#ifndef LIBDXF_SRC_TABLE_H
#define LIBDXF_SRC_TABLE_H


#include "global.h"
#include "point.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of a table entity cell.
 */
typedef struct
dxf_table_cell_struct
{
        char *text_string;
                /*!< Text string in a cell.\n
                 * If the string is shorter than 250 characters, all
                 * characters appear in code 1.\n
                 * If the string is longer than 250 characters, it is
                 * divided into chunks of 250 characters.\n
                 * The chunks are contained in one or more code 3 codes.\n
                 * If code 3 codes are used, the last group is a code 1
                 * and is shorter than 250 characters.\n
                 * This value applies only to text-type cells and is
                 * repeated, 1 value per cell.\n
                 * Group code = 1. */
        char *optional_text_string[DXF_MAX_PARAM];
                /*!< Text string in a cell, in 250-character chunks;
                 * optional.\n
                 * This value applies only to text-type cells and is
                 * repeated, 1 value per cell.\n
                 * Group code = 3. */
        char *text_style_name;
                /*!< Text style name (string); override applied at the
                 * cell level.\n
                 * Group code = 7. */
        int color_bg;
                /*!< Value for the background (fill) color of cell
                 * content; override applied at the cell level.\n
                 * Group code = 63. */
        int color_fg;
                /*!< Value for the color of cell content; override
                 * applied at the cell level.\n
                 * Group code = 64. */
        int border_color_right;
                /*!< True color value for the right border of the cell;
                 * override applied at the cell level.\n
                 * Group code = 65. */
        int border_color_bottom;
                /*!< True color value for the bottom border of the cell;
                 * override applied at the cell level.\n
                 * Group code = 66. */
        int border_color_left;
                /*!< True color value for the left border of the cell;
                 * override applied at the cell level.\n
                 * Group code = 68. */
        int border_color_top;
                /*!< True color value for the top border of the cell;
                 * override applied at the cell level.\n
                 * Group code = 69. */
        int override_flag;
                /*!< Cell override flag; this value is repeated, 1 value
                 * per cell (from AutoCAD 2007).\n
                 * Group code = 91.
                 *
                 * \warning Multiple entries with Group code 91. */
        double text_height;
                /*!< Text height value; override applied at the cell
                 * level.\n
                 * Group code = 140. */
        double block_scale;
                /*!< Block scale (real).\n
                 * This value applies only to block-type cells and is
                 * repeated, 1 value per cell.\n
                 * Group code = 144. */
        double block_rotation;
                /*!< Rotation value (real; applicable for a block-type
                 * cell and a text-type cell).\n
                 * Group code = 145. */
        int alignment;
                /*!< Cell alignment value; override applied at the cell
                 * level.\n
                 * Group code = 170. */
        int type;
                /*!< Cell type; this value is repeated, 1 value per cell:
                 * <ol>
                 * <li value = "1"> Text type.</li>
                 * <li value = "2"> Block type.</li>
                 * </ol>
                 * Group code = 171. */
        int flag;
                /*!< Cell flag value; this value is repeated, 1 value
                 * per cell.\n
                 * Group code = 172. */
        int merged;
                /*!< Cell merged value; this value is repeated, 1 value
                 * per cell.\n
                 * Group code = 173. */
        int autofit;
                /*!< Boolean flag indicating if the autofit option is
                 * set for the cell; this value is repeated, 1 value per
                 * cell.\n
                 * Group code = 174. */
        double border_width;
                /*!< Cell border width (applicable only for merged
                 * cells); this value is repeated, 1 value per cell.\n
                 * Group code = 175. */
        double border_height;
                /*!< Cell border height (applicable only for merged
                 * cells); this value is repeated, 1 value per cell.\n
                 * Group code = 176. */
        int override;
                /*!< Cell override flag; this value is repeated, 1 value
                 * per cell.\n
                 * Group code = 177. */
        int virtual_edge;
                /*!< Flag value for a virtual edge.\n
                 *
                 * \note Group code 178 is a flag value for a virtual
                 * edge.\n
                 * A virtual edge is used when a grid line is shared by
                 * two cells.\n
                 * For example, if a table contains one row and two
                 * columns and it contains cell A and cell B, the
                 * central grid line contains the right edge of cell A
                 * and the left edge of cell B.\n
                 * One edge is real, and the other edge is virtual.\n
                 * The virtual edge points to the real edge; both edges
                 * have the same set of properties, including color,
                 * lineweight, and visibility.\n
                 *
                 * Group code = 178. */
        int number_of_block_attdefs;
                /*!< Number of attribute definitions in the block table
                 * record (applicable only to a block-type cell).\n
                 * Group code = 179. */
        double border_lineweight_right;
                /*!< Lineweight for the right border of the cell;
                 * override applied at the cell level.\n
                 * Group code = 275. */
        double border_lineweight_bottom;
                /*!< Lineweight for the bottom border of the cell;
                 * override applied at the cell level.\n
                 * Group code = 276. */
        double border_lineweight_left;
                /*!< Lineweight for the left border of the cell;
                 * override applied at the cell level.\n
                 * Group code = 278. */
        double border_lineweight_top;
                /*!< Lineweight for the top border of the cell; override
                 * applied at the cell level.\n
                 * Group code = 279. */
        int color_fill_override;
                /*!< Boolean flag for whether the fill color is on;
                 * override applied at the cell level.\n
                 * Group code = 283. */
        int border_visibility_override_right;
                /*!< Boolean flag for the visibility of the right border
                 * of the cell; override applied at the cell level.\n
                 * Group code = 285. */
        int border_visibility_override_bottom;
                /*!< Boolean flag for the visibility of the bottom
                 * border of the cell; override applied at the cell
                 * level.\n
                 * Group code = 286. */
        int border_visibility_override_left;
                /*!< Boolean flag for the visibility of the left border
                 * of the cell; override applied at the cell level.\n
                 * Group code = 288. */
        int border_visibility_override_top;
                /*!< Boolean flag for the visibility of the top border
                 * of the cell; override applied at the cell level.\n
                 * Group code = 289. */
        char *attdef_text_string;
                /*!< Text string value for an attribute definition,
                 * repeated once per attribute definition and applicable
                 * only for a block-type cell.\n
                 * Group code = 300. */
        char *attdef_soft_pointer[DXF_MAX_PARAM];
                /*!< Soft pointer ID of the attribute definition in the
                 * block table record, referenced by group code 179
                 * (applicable only for a block-type cell).\n
                 * This value is repeated once per attribute definition.\n
                 * Group code = 331. */
        char *block_table_record_hard_pointer;
                /*!< Hard-pointer ID of the block table record.\n
                 * This value applies only to block-type cells and is
                 * repeated, 1 value per cell.\n
                 * Group code = 340. */
        char *field_object_pointer;
                /*!< Hard pointer ID of the \c FIELD object.\n
                 * This applies only to a text-type cell.\n
                 * If the text in the cell contains one or more fields,
                 * only the ID of the \c FIELD object is saved.\n
                 * The text string (group codes 1 and 3) is ignored.\n
                 * Group code = 344. */
        struct DxfTableCell *next;
                /*!< Pointer to the next DxfTableCell.\n
                 * \c NULL in the last DxfTableCell. */
} DxfTableCell;


/*!
 * \brief DXF definition of a table entity.
 */
typedef struct
dxf_table_struct
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
        /* Specific members for a DXF table. */
        char *block_name;
                /*!< Block name; an anonymous block begins with a *T
                 * value.\n
                 * Group code = 2. */
        char *table_text_style_name;
                /*!< Text style name (string); override applied at the
                 * table entity level.\n
                 * There may be one entry for each cell type.\n
                 * Group code = 7. */
        DxfPoint *p0;
                /*!< Insertion point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Horizontal direction vector.\n
                 * Group codes = 11, 21 and 31. */
        double horizontal_cell_margin;
                /*!< Horizontal cell margin; override applied at the
                 * table entity level.\n
                 * Group code = 40. */
        double vertical_cell_margin;
                /*!< Vertical cell margin; override applied at the
                 * table entity level.\n
                 * Group code = 41. */
        int16_t table_cell_color_bg;
                /*!< Color value for cell background or for the vertical,
                 * left border of the table; override applied at the
                 * table entity level.\n
                 * There may be one entry for each cell type.\n
                 * Group code = 63. */
        int16_t table_cell_color_fg;
                /*!< Color value for cell content or for the horizontal,
                 * top border of the table; override applied at the
                 * table entity level.\n
                 * There may be one entry for each cell type.\n
                 * Group code = 64. */
        int16_t table_cell_border_color_horizontal;
                /*!< Color value for the horizontal, inside border lines;
                 * override applied at the table entity level.\n
                 * Group code = 65. */
        int16_t table_cell_border_color_bottom;
                /*!< Color value for the horizontal, bottom border lines;
                 * override applied at the table entity level.\n
                 * Group code = 66. */
        int16_t table_cell_border_color_vertical;
                /*!< Color value for the vertical, inside border lines;
                 * override applied at the table entity level.\n
                 * Group code = 68. */
        int16_t table_cell_border_color_right;
                /*!< Color value for the vertical, right border lines;
                 * override applied at the table entity level.\n
                 * Group code = 69. */
        int16_t flow_direction;
                /*!< Flow direction; override applied at the table
                 * entity level.\n
                 * Group code = 70. */
        int32_t table_value_flag;
                /*!< Flag for table value (unsigned integer).\n
                 * Group code = 90. */
        int32_t number_of_rows;
                /*!< Number of rows.\n
                 * Group code = 91.\n
                 * \warning Multiple entries with Group code 91. */
        int32_t number_of_columns;
                /*!< Number of columns.\n
                 * Group code = 92.\n
                 * \warning Multiple entries with Group code 92. */
        int32_t override_flag;
                /*!< Flag for an override.\n
                 * Group code = 93. */
        int32_t border_color_override_flag;
                /*!< Flag for an override of border color.\n
                 * Group code = 94. */
        int32_t border_lineweight_override_flag;
                /*!< Flag for an override of border lineweight.\n
                 * Group code = 95. */
        int32_t border_visibility_override_flag;
                /*!< Flag for an override of border visibility.\n
                 * Group code = 96. */
        double table_text_height;
                /*!< Text height (real); override applied at the table
                 * entity level.\n
                 * There may be one entry for each cell type.\n
                 * Group code = 140. */
        double row_height;
                /*!< Row height; this value is repeated, 1 value per
                 * row.\n
                 * Group code = 141. */
        double column_height;
                /*!< Column height; this value is repeated, 1 value per
                 * column.\n
                 * Group code = 142. */
        int table_cell_alignment;
                /*!< Cell alignment (integer); override applied at the
                 * table entity level.\n
                 * There may be one entry for each cell type.\n
                 * Group code = 170. */
        double table_cell_border_lineweight_right;
                /*!< Group code = 274. */
        int16_t table_data_version;
                /*!< Table data version number:\n
                 * 0 = 2010.\n
                 * Group code = 280.
                 *
                 * \warning Multiple entries with Group code 280. */
        int16_t suppress_table_title;
                /*!< Flag for whether the title is suppressed; override
                 * applied at the table entity level.\n
                 * Group code = 280.
                 *
                 * \warning Multiple entries with Group code 280. */
        int16_t suppress_header_row;
                /*!< Flag for whether the header row is suppressed;
                 * override applied at the table entity level.\n
                 * Group code = 281. */
        int16_t table_cell_color_fill_override;
                /*!< Flag for whether background color is enabled
                 * (default = 0); override applied at the table entity
                 * level.\n
                 * There may be one entry for each cell type:
                 * <ol>
                 * <li value = "0"> Disabled.</li>
                 * <li value = "1"> Enabled.</li>
                 * </ol>
                 * Group code = 283. */
        char *tablestyle_object_pointer;
                /*!< Hard pointer ID of the \c TABLESTYLE object.\n
                 * Group code = 342. */
        char *owning_block_pointer;
                /*!< Hard pointer ID of the owning \c BLOCK record.\n
                 * Group code = 343. */
        struct DxfTableCell *cells;
                /*!< Pointer to the first DxfTableCell of a linked list
                 * of table cells. */
        struct DxfTable *next;
                /*!< Pointer to the next DxfTable.\n
                 * \c NULL in the last DxfTable. */
} DxfTable;


DxfTableCell *dxf_table_cell_new ();
DxfTableCell *dxf_table_cell_init (DxfTableCell *cell);
int dxf_table_cell_write (DxfFile *fp, DxfTableCell *cell);
int dxf_table_cell_free (DxfTableCell *cell);
void dxf_table_cell_free_list (DxfTableCell *cells);
DxfTableCell *dxf_table_cell_get_next (DxfTableCell *cell);
DxfTableCell *dxf_table_cell_set_next (DxfTableCell *cell,  DxfTableCell *next);
DxfTableCell *dxf_table_cell_get_last (DxfTableCell *cells);

DxfTable *dxf_table_new ();
DxfTable *dxf_table_init (DxfTable *table);
DxfTable *dxf_table_read (DxfFile *fp, DxfTable *table);
int dxf_table_write (DxfFile *fp, DxfTable *table);
int dxf_table_free (DxfTable *table);
void dxf_table_free_list (DxfTable *tables);
int dxf_table_get_id_code (DxfTable *table);
DxfTable *dxf_table_set_id_code (DxfTable *table, int id_code);
char *dxf_table_get_linetype (DxfTable *table);
DxfTable *dxf_table_set_linetype (DxfTable *table, char *linetype);
char *dxf_table_get_layer (DxfTable *table);
DxfTable *dxf_table_set_layer (DxfTable *table, char *layer);
double dxf_table_get_elevation (DxfTable *table);
DxfTable *dxf_table_set_elevation (DxfTable *table, double elevation);
double dxf_table_get_thickness (DxfTable *table);
DxfTable *dxf_table_set_thickness (DxfTable *table, double thickness);
double dxf_table_get_linetype_scale (DxfTable *table);
DxfTable *dxf_table_set_linetype_scale (DxfTable *table, double linetype_scale);
int16_t dxf_table_get_visibility (DxfTable *table);
DxfTable *dxf_table_set_visibility (DxfTable *table, int16_t visibility);
int16_t dxf_table_get_color (DxfTable *table);
DxfTable *dxf_table_set_color (DxfTable *table, int16_t color);
int16_t dxf_table_get_paperspace (DxfTable *table);
DxfTable *dxf_table_set_paperspace (DxfTable *table, int16_t paperspace);
int32_t dxf_table_get_graphics_data_size (DxfTable *table);
DxfTable *dxf_table_set_graphics_data_size (DxfTable *table, int32_t graphics_data_size);
int16_t dxf_table_get_shadow_mode (DxfTable *table);
DxfTable *dxf_table_set_shadow_mode (DxfTable *table, int16_t shadow_mode);
DxfBinaryData *dxf_table_get_binary_graphics_data (DxfTable *table);
DxfTable *dxf_table_set_binary_graphics_data (DxfTable *table, DxfBinaryData *data);
char *dxf_table_get_dictionary_owner_soft (DxfTable *table);
DxfTable *dxf_table_set_dictionary_owner_soft (DxfTable *table, char *dictionary_owner_soft);
char *dxf_table_get_object_owner_soft (DxfTable *table);
DxfTable *dxf_table_set_object_owner_soft (DxfTable *table, char *object_owner_soft);
char *dxf_table_get_material (DxfTable *table);
DxfTable *dxf_table_set_material (DxfTable *table, char *material);
char *dxf_table_get_dictionary_owner_hard (DxfTable *table);
DxfTable *dxf_table_set_dictionary_owner_hard (DxfTable *table, char *dictionary_owner_hard);
int16_t dxf_table_get_lineweight (DxfTable *table);
DxfTable *dxf_table_set_lineweight (DxfTable *table, int16_t lineweight);
char *dxf_table_get_plot_style_name (DxfTable *table);
DxfTable *dxf_table_set_plot_style_name (DxfTable *table, char *plot_style_name);
int32_t dxf_table_get_color_value (DxfTable *table);
DxfTable *dxf_table_set_color_value (DxfTable *table, int32_t color_value);
char *dxf_table_get_color_name (DxfTable *table);
DxfTable *dxf_table_set_color_name (DxfTable *table, char *color_name);
int32_t dxf_table_get_transparency (DxfTable *table);
DxfTable *dxf_table_set_transparency (DxfTable *table, int32_t transparency);
char *dxf_table_get_block_name (DxfTable *table);
DxfTable *dxf_table_set_block_name (DxfTable *table, char *block_name);
char *dxf_table_get_table_text_style_name (DxfTable *table);
DxfTable *dxf_table_set_table_text_style_name (DxfTable *table, char *table_text_style_name);
DxfPoint *dxf_table_get_p0 (DxfTable *table);
DxfTable *dxf_table_set_p0 (DxfTable *table, DxfPoint *point);
double dxf_table_get_x0 (DxfTable *table);
DxfTable *dxf_table_set_x0 (DxfTable *table, double x0);
double dxf_table_get_y0 (DxfTable *table);
DxfTable *dxf_table_set_y0 (DxfTable *table, double y0);
double dxf_table_get_z0 (DxfTable *table);
DxfTable *dxf_table_set_z0 (DxfTable *table, double z0);
DxfPoint *dxf_table_get_p1 (DxfTable *table);
DxfTable *dxf_table_set_p1 (DxfTable *table, DxfPoint *point);
double dxf_table_get_x1 (DxfTable *table);
DxfTable *dxf_table_set_x1 (DxfTable *table, double x1);
double dxf_table_get_y1 (DxfTable *table);
DxfTable *dxf_table_set_y1 (DxfTable *table, double y1);
double dxf_table_get_z1 (DxfTable *table);
DxfTable *dxf_table_set_z1 (DxfTable *table, double z1);
double dxf_table_get_horizontal_cell_margin (DxfTable *table);
DxfTable *dxf_table_set_horizontal_cell_margin (DxfTable *table, double horizontal_cell_margin);
double dxf_table_get_vertical_cell_margin (DxfTable *table);
DxfTable *dxf_table_set_vertical_cell_margin (DxfTable *table, double vertical_cell_margin);
int16_t dxf_table_get_table_cell_color_bg (DxfTable *table);
DxfTable *dxf_table_set_table_cell_color_bg (DxfTable *table, int16_t table_cell_color_bg);
int16_t dxf_table_get_table_cell_color_fg (DxfTable *table);
DxfTable *dxf_table_set_table_cell_color_fg (DxfTable *table, int16_t table_cell_color_fg);
int16_t dxf_table_get_table_cell_border_color_horizontal (DxfTable *table);
DxfTable *dxf_table_set_table_cell_border_color_horizontal (DxfTable *table, int16_t table_cell_border_color_horizontal);
int16_t dxf_table_get_table_cell_border_color_bottom (DxfTable *table);
DxfTable *dxf_table_set_table_cell_border_color_bottom (DxfTable *table, int16_t table_cell_border_color_bottom);
int16_t dxf_table_get_table_cell_border_color_vertical (DxfTable *table);
DxfTable *dxf_table_set_table_cell_border_color_vertical (DxfTable *table, int16_t table_cell_border_color_vertical);
int16_t dxf_table_get_table_cell_border_color_right (DxfTable *table);
DxfTable *dxf_table_set_table_cell_border_color_right (DxfTable *table, int16_t table_cell_border_color_right);
int16_t dxf_table_get_flow_direction (DxfTable *table);
DxfTable *dxf_table_set_flow_direction (DxfTable *table, int16_t flow_direction);
int32_t dxf_table_get_table_value_flag (DxfTable *table);
DxfTable *dxf_table_set_table_value_flag (DxfTable *table, int32_t table_value_flag);
int32_t dxf_table_get_number_of_rows (DxfTable *table);
DxfTable *dxf_table_set_number_of_rows (DxfTable *table, int32_t number_of_rows);
int32_t dxf_table_get_number_of_columns (DxfTable *table);
DxfTable *dxf_table_set_number_of_columns (DxfTable *table, int32_t number_of_columns);
int32_t dxf_table_get_override_flag (DxfTable *table);
DxfTable * dxf_table_set_override_flag (DxfTable *table, int32_t override_flag);
int32_t dxf_table_get_border_color_override_flag (DxfTable *table);
DxfTable *dxf_table_set_border_color_override_flag (DxfTable *table, int32_t border_color_override_flag);
int32_t dxf_table_get_border_lineweight_override_flag (DxfTable *table);
DxfTable *dxf_table_set_border_lineweight_override_flag (DxfTable *table, int32_t border_lineweight_override_flag);
int32_t dxf_table_get_border_visibility_override_flag (DxfTable *table);
DxfTable *dxf_table_set_border_visibility_override_flag (DxfTable *table, int32_t border_visibility_override_flag);
double dxf_table_get_table_text_height (DxfTable *table);
DxfTable *dxf_table_set_table_text_height (DxfTable *table, double table_text_height);
double dxf_table_get_row_height (DxfTable *table);
DxfTable *dxf_table_set_row_height (DxfTable *table, double row_height);
double dxf_table_get_column_height (DxfTable *table);
DxfTable *dxf_table_set_column_height (DxfTable *table, double column_height);
int dxf_table_get_table_cell_alignment (DxfTable *table);
DxfTable *dxf_table_set_table_cell_alignment (DxfTable *table, int table_cell_alignment);
double dxf_table_get_table_cell_border_lineweight_right (DxfTable *table);
DxfTable *dxf_table_set_table_cell_border_lineweight_right (DxfTable *table, double table_cell_border_lineweight_right);
int16_t dxf_table_get_table_data_version (DxfTable *table);
DxfTable *dxf_table_set_table_data_version (DxfTable *table, int16_t table_data_version);
int16_t dxf_table_get_suppress_table_title (DxfTable *table);
DxfTable *dxf_table_set_suppress_table_title (DxfTable *table, int16_t suppress_table_title);
int16_t dxf_table_get_suppress_header_row (DxfTable *table);
DxfTable *dxf_table_set_suppress_header_row (DxfTable *table, int16_t suppress_header_row);
int16_t dxf_table_get_table_cell_color_fill_override (DxfTable *table);
DxfTable *dxf_table_set_table_cell_color_fill_override (DxfTable *table, int16_t table_cell_color_fill_override);
char *dxf_table_get_tablestyle_object_pointer (DxfTable *table);
DxfTable *dxf_table_set_tablestyle_object_pointer (DxfTable *table, char *tablestyle_object_pointer);
char *dxf_table_get_owning_block_pointer (DxfTable *table);
DxfTable *dxf_table_set_owning_block_pointer (DxfTable *table, char *owning_block_pointer);
struct DxfTableCell *dxf_table_get_cells (DxfTable *table);
DxfTable *dxf_table_set_cells (DxfTable *table, struct DxfTableCell *cells);
DxfTable *dxf_table_get_next (DxfTable *table);
DxfTable *dxf_table_set_next (DxfTable *table, DxfTable *next);
DxfTable *dxf_table_get_last (DxfTable *table);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_TABLE_H */


/* EOF */
