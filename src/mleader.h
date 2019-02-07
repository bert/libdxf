/*!
 * \file mleader.h
 *
 * \author Copyright (C) 2018, 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF mleader entity (\c MLEADER).
 *
 * \since The \c MLEADER entity was introduced in DXF R2007.
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


#ifndef LIBDXF_SRC_MLEADER_H
#define LIBDXF_SRC_MLEADER_H


#include "global.h"
#include "binary_graphics_data.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD mleader entity (\c MLEADER).
 */
typedef struct
dxf_mleader_struct
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
        /* Specific members for a DXF MLeader. */
        double block_content_scale;
                /*!< Block content scale.\n
                 * Group code = 10. */
        double dogleg_length;
                /*!< Dogleg length.\n
                 * Group code = 41. */
        double arrowhead_size;
                /*!< Arrowhead size.\n
                 * Group code = 42. */
        double block_content_rotation;
                /*!< Block content rotation.\n
                 * Group code = 43. */
        double block_attribute_width;
                /*!< Block attribute width.\n
                 * Group code = 44. */
        int32_t property_override_flag;
                /*!< Property override flag.\n
                 * Group code = 90. */
        int32_t leader_line_color;
                /*!< Leader line color.\n
                 * Group code = 91. */
        int32_t text_color;
                /*!< Text color.\n
                 * Group code = 92. */
        int32_t block_content_color;
                /*!< Block conten color.\n
                 * Group code = 93. */
        int32_t arrowhead_index;
                /*!< Arrowhead index.\n
                 * Group code = 94. */
        int32_t text_right_attachment_type;
                /*!< Text right attachment type.\n
                 * Group code = 95. */
        int16_t leader_linetype_style;
                /*!< Leader linetype style.\n
                 * Group code = 170. */
        int16_t leader_line_weight;
                /*!< Leader line weight.\n
                 * Group code = 171. */
        int16_t content_type;
                /*!< Content type.\n
                 * Group code = 172. */
        int16_t text_left_attachment_type;
                /*!< Text left attachment type.\n
                 * Group code = 173. */
        int16_t text_angle_type;
                /*!< Text angle type.\n
                 * Group code = 174. */
        int16_t text_alignment_type;
                /*!< Text alignment type.\n
                 * Group code = 175. */
        int16_t block_content_connection_type;
                /*!< Block content connection type.\n
                 * Group code = 176. */
        int16_t block_attribute_index;
                /*!< Block attribute index.\n
                 * Group code = 177. */
        int16_t text_align_in_IPE;
                /*!< Text align in IPE.\n
                 * Group code = 178. */
        int16_t text_attachment_point;
                /*!< Text attachment point.\n
                 * Group code = 179. */
        int16_t text_attachment_direction;
                /*!< Text attachment direction for MText contents:
                 * <ol>
                 *   <li value = 0>Horizontal.</li>
                 *   <li value = 1>Vertical.</li>
                 * </ol>
                 * Group code = 271. */
        int16_t bottom_text_attachment_direction;
                /*!< Bottom text attachment direction:
                 * <ol>
                 *   <li value = 9>Center.</li>
                 *   <li value = 10>Underline and Center.</li>
                 * </ol>
                 * Group code = 272. */
        int16_t top_text_attachment_direction;
                /*!< Top text attachment direction:
                 * <ol>
                 *   <li value = 9>Center.</li>
                 *   <li value = 10>Overline and Center.</li>
                 * </ol>
                 * Group code = 273. */
        int enable_landing;
                /*!< Enable landing (boolean).\n
                 * Group code = 290. */
        int enable_dogleg;
                /*!< Enable dogleg (boolean).\n
                 * Group code = 291. */
        int enable_frame_text;
                /*!< Enable frame text (boolean).\n
                 * Group code = 292. */
        int enable_annotation_scale;
                /*!< Enable annotation scale (boolean).\n
                 * Group code = 293. */
        int text_direction_negative;
                /*!< Text direction negative (boolean).\n
                 * Group code = 294. */
        char *block_attribute_text_string;
                /*!< Block attribute text string.\n
                 * Group code = 302. */
        char *block_attribute_id;
                /*!< Block attribute ID (string representing hex object
                 * IDs).\n
                 * Group code = 330. */
        char *leader_style_id;
                /*!< Leader style ID (string representing hex object
                 * IDs).\n
                 * Group code = 340. */
        char *leader_linetype_id;
                /*!< Leader linetype ID (string representing hex object
                 * IDs).\n
                 * Group code = 341. */
        char *arrowhead_id;
                /*!< Arrowhead ID (string representing hex object IDs).\n
                 * Group code = 342. */
        char *text_style_id;
                /*!< Text style ID (string representing hex object IDs).\n
                 * Group code = 343. */
        char *block_content_id;
                /*!< Block content ID (string representing hex object
                 * IDs).\n
                 * Group code = 344. */
        char *arrow_head_id;
                /*!< Arrowhead ID (string representing hex object
                 * IDs).\n
                 * Another Arrowhead ID ?.\n
                 * Group code = 345. */
        struct DxfMLeader *next;
                /*!< Pointer to the next DxfMLeader.\n
                 * \c NULL in the last DxfMLeader. */
} DxfMLeader;


/*!
 * \brief DXF definition of an AutoCAD mleader context data object.
 */
typedef struct
dxf_mleader_context_data_struct
{
        DxfPoint *p0;
                /*!< Content base position.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *vertex;
                /*!< Vertex.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Text normal direction.\n
                 * Group codes = 11, 21 and 31.*/
        DxfPoint *p2;
                /*!< Text location.\n
                 * Group codes = 12, 22 and 32.*/
        DxfPoint *p3;
                /*!< Text direction.\n
                 * Group codes = 13, 23 and 33.*/
        DxfPoint *p4;
                /*!< Block content normal direction.\n
                 * Group codes = 14, 24 and 34.*/
        DxfPoint *p5;
                /*!< Block content position.\n
                 * Group codes = 15, 25 and 35.*/
        double block_content_scale;
                /*!< Block content scale.\n
                 * Group code = 16. */
        double content_scale;
                /*!< Content scale.\n
                 * Group code = 40. */
        double text_height;
                /*!< Text height.\n
                 * Group code = 41. */
        double text_rotation;
                /*!< Text rotation.\n
                 * Group code = 42. */
        double text_width;
                /*!< Text width.\n
                 * Group code = 43. */
        double text_height2;
                /*!< Text height.\n
                 * Group code = 44. */
        double text_line_spacing_factor;
                /*!< Text line spacing factor.\n
                 * Group code = 45. */
        double block_content_rotation;
                /*!< Block content rotation.\n
                 * Group code = 46. */
        double block_transformation_matrix;
                /*!< Block transformation matrix.\n
                 * Group code = 47. */
        int32_t text_color;
                /*!< Text color.\n
                 * Group code = 90. */
        int32_t break_point_index;
                /*!< Break point index.\n
                 * Group code = 90. */
        int32_t text_background_color;
                /*!< Text background color.\n
                 * Group code = 91. */
        int32_t text_background_transparency;
                /*!< Text background transparency.\n
                 * Group code = 92. */
        int32_t block_content_color;
                /*!< Block content color.\n
                 * Group code = 93. */
        double MLeader_plane_origin_point;
                /*!< MLeader plane origin point.\n
                 * Group code = 110. */
        double MLeader_plane_X_axis_direction;
                /*!< MLeader plane X-axis direction.\n
                 * Group code = 111. */
        double MLeader_plane_Y_axis_direction;
                /*!< MLeader plane Y-axis direction.\n
                 * Group code = 112. */
        double arrowhead_size;
                /*!< Arrowhead size.\n
                 * Group code = 140. */
        double text_background_scale_factor;
                /*!< Text background scale factor.\n
                 * Group code = 141. */
        double text_column_width;
                /*!< Text column width.\n
                 * Group code = 142. */
        double text_column_gutter_width;
                /*!< Text column gutter width.\n
                 * Group code = 143. */
        double text_column_height;
                /*!< Text column height.\n
                 * Group code = 144. */
        double landing_gap;
                /*!< Landing gap.\n
                 * Group code = 145. */
        int16_t text_line_spacing_style;
                /*!< Text line spacing style.\n
                 * Group code = 170. */
        int16_t text_attachment;
                /*!< Text attachment.\n
                 * Group code = 171. */
        int16_t text_flow_direction;
                /*!< Text flow direction.\n
                 * Group code = 172. */
        int16_t text_column_type;
                /*!< Text column type.\n
                 * Group code = 173. */
        int has_Mtext;
                /*!< Has M text (boolean).\n
                 * Group code = 290. */
        int is_text_background_color_on;
                /*!< Is text background color on (boolean).\n
                 * Group code = 291. */
        int is_text_background_fill_on;
                /*!< Is text background fill on (boolean).\n
                 * Group code = 292. */
        int use_text_auto_height;
                /*!< Use text auto height (boolean).\n
                 * Group code = 293. */
        int text_column_flow_reversed;
                /*!< Text column flow reversed (boolean).\n
                 * Group code = 294. */
        int text_use_word_break;
                /*!< Text use word break (boolean).\n
                 * Group code = 295. */
        int has_block;
                /*!< Has block (boolean).\n
                 * Group code = 296. */
        int MLeader_plane_normal_reversed;
                /*!< MLeader plane normal reversed (boolean).\n
                 * Group code = 297. */
        char *default_text_contents;
                /*!< Default text contents.\n
                 * Group code = 304. */
        char *type_style_id;
                /*!< Type style ID (string representing hex object
                 * IDs).\n
                 * Group code = 340. */
        char *block_content_id;
                /*!< Block content ID (string representing hex object
                 * IDs).\n
                 * Group code = 341. */
        struct DxfMLeaderContextData *next;
                /*!< Pointer to the next DxfMLeaderContextData.\n
                 * \c NULL in the last DxfMLeaderContextData. */
} DxfMLeaderContextData;


/*!
 * \brief DXF definition of an AutoCAD mleader leader node object.
 */
typedef struct
dxf_mleader_leader_node_struct
{
        DxfPoint *p0;
                /*!< Last leader line point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Dogleg vector.\n
                 * Group codes = 11, 21 and 31.*/
        DxfPoint *p2;
                /*!< Break start point.\n
                 * Group codes = 12, 22 and 32.*/
        DxfPoint *p3;
                /*!< Break end point.\n
                 * Group codes = 13, 23 and 33.*/
        double dogleg_length;
                /*!< Dogleg length.\n
                 * Group code = 40. */
        int32_t leader_branch_index;
                /*!< Leader branch index.\n
                 * Group code = 90. */
        int has_set_last_leader_line_point;
                /*!< Has set last leader line point (boolean).\n
                 * Group code = 290. */
        int has_set_dogleg_vector;
                /*!< Has set dogleg vector (boolean).\n
                 * Group code = 291. */
        struct DxfMLeaderLeaderNode *next;
                /*!< Pointer to the next DxfMLeaderLeaderNode.\n
                 * \c NULL in the last DxfMLeaderLeaderNode. */
} DxfMLeaderLeaderNode;


/*!
 * \brief DXF definition of an AutoCAD mleader leader line object.
 */
typedef struct
dxf_mleader_leader_line_struct
{
        DxfPoint *p0;
                /*!< Vertex.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Break start point.\n
                 * Group codes = 11, 21 and 31.*/
        DxfPoint *p2;
                /*!< Break end point.\n
                 * Group codes = 12, 22 and 32.*/
        int32_t break_point_index;
                /*!< Break point index.\n
                 * Group code = 90. */
        int32_t leader_line_index;
                /*!< Leader line index.\n
                 * Group code = 91. */
        struct DxfMLeaderLeaderLine *next;
                /*!< Pointer to the next DxfMLeaderLeaderLine.\n
                 * \c NULL in the last DxfMLeaderLeaderLine. */
} DxfMLeaderLeaderLine;


DxfMLeader *dxf_mleader_new ();
DxfMLeader *dxf_mleader_init (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_read (DxfFile *fp, DxfMLeader *mleader);
int dxf_mleader_write (DxfFile *fp, DxfMLeader *mleader);
int dxf_mleader_free (DxfMLeader *mleader);
void dxf_mleader_free_list (DxfMLeader *mleaders);
int dxf_mleader_get_id_code (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_id_code (DxfMLeader *mleader, int id_code);
char *dxf_mleader_get_linetype (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_linetype (DxfMLeader *mleader, char *linetype);
char *dxf_mleader_get_layer (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_layer (DxfMLeader *mleader, char *layer);
double dxf_mleader_get_elevation (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_elevation (DxfMLeader *mleader, double elevation);
double dxf_mleader_get_thickness (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_thickness (DxfMLeader *mleader, double thickness);
double dxf_mleader_get_linetype_scale (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_linetype_scale (DxfMLeader *mleader, double linetype_scale);
int16_t dxf_mleader_get_visibility (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_visibility (DxfMLeader *mleader, int16_t visibility);
int dxf_mleader_get_color (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_color (DxfMLeader *mleader, int color);
int dxf_mleader_get_paperspace (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_paperspace (DxfMLeader *mleader, int paperspace);
int dxf_mleader_get_graphics_data_size (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_graphics_data_size (DxfMLeader *mleader, int graphics_data_size);
int16_t dxf_mleader_get_shadow_mode (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_shadow_mode (DxfMLeader *mleader, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_mleader_get_binary_graphics_data (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_binary_graphics_data (DxfMLeader *mleader, DxfBinaryGraphicsData *data);
char *dxf_mleader_get_dictionary_owner_soft (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_dictionary_owner_soft (DxfMLeader *mleader, char *dictionary_owner_soft);
char *dxf_mleader_get_object_owner_soft (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_object_owner_soft (DxfMLeader *mleader, char *object_owner_soft);
char *dxf_mleader_get_material (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_material (DxfMLeader *mleader, char *material);
char *dxf_mleader_get_dictionary_owner_hard (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_dictionary_owner_hard (DxfMLeader *mleader, char *dictionary_owner_hard);
int16_t dxf_mleader_get_lineweight (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_lineweight (DxfMLeader *mleader, int16_t lineweight);
char *dxf_mleader_get_plot_style_name (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_plot_style_name (DxfMLeader *mleader, char *plot_style_name);
long dxf_mleader_get_color_value (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_color_value (DxfMLeader *mleader, long color_value);
char *dxf_mleader_get_color_name (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_color_name (DxfMLeader *mleader, char *color_name);
long dxf_mleader_get_transparency (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_transparency (DxfMLeader *mleader, long transparency);
double dxf_mleader_get_block_content_scale (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_content_scale (DxfMLeader *mleader, double block_content_scale);
double dxf_mleader_get_dogleg_length (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_dogleg_length (DxfMLeader *mleader, double dogleg_length);
double dxf_mleader_get_arrowhead_size (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_arrowhead_size (DxfMLeader *mleader, double arrowhead_size);
double dxf_mleader_get_block_content_rotation (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_content_rotation (DxfMLeader *mleader, double block_content_rotation);
double dxf_mleader_get_block_attribute_width (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_attribute_width (DxfMLeader *mleader, double block_attribute_width);
int32_t dxf_mleader_get_property_override_flag (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_property_override_flag (DxfMLeader *mleader, int32_t property_override_flag);
int32_t dxf_mleader_get_leader_line_color (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_leader_line_color (DxfMLeader *mleader, int32_t leader_line_color);
int32_t dxf_mleader_get_text_color (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_color (DxfMLeader *mleader, int32_t text_color);
int32_t dxf_mleader_get_block_content_color (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_content_color (DxfMLeader *mleader, int32_t block_content_color);
int32_t dxf_mleader_get_arrowhead_index (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_arrowhead_index (DxfMLeader *mleader, int32_t arrowhead_index);
int32_t dxf_mleader_get_text_right_attachment_type (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_right_attachment_type (DxfMLeader *mleader, int32_t text_right_attachment_type);
int16_t dxf_mleader_get_leader_linetype_style (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_leader_linetype_style (DxfMLeader *mleader, int16_t leader_linetype_style);
int16_t dxf_mleader_get_leader_line_weight (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_leader_line_weight (DxfMLeader *mleader, int16_t leader_line_weight);
int16_t dxf_mleader_get_content_type (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_content_type (DxfMLeader *mleader, int16_t content_type);
int16_t dxf_mleader_get_text_left_attachment_type (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_left_attachment_type (DxfMLeader *mleader, int16_t text_left_attachment_type);
int16_t dxf_mleader_get_text_angle_type (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_angle_type (DxfMLeader *mleader, int16_t text_angle_type);
int16_t dxf_mleader_get_text_alignment_type (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_alignment_type (DxfMLeader *mleader, int16_t text_alignment_type);
int16_t dxf_mleader_get_block_content_connection_type (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_content_connection_type (DxfMLeader *mleader, int16_t block_content_connection_type);
int16_t dxf_mleader_get_block_attribute_index (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_attribute_index (DxfMLeader *mleader, int16_t block_attribute_index);
int16_t dxf_mleader_get_text_align_in_IPE (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_align_in_IPE (DxfMLeader *mleader, int16_t text_align_in_IPE);
int16_t dxf_mleader_get_text_attachment_point (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_attachment_point (DxfMLeader *mleader, int16_t text_attachment_point);
int16_t dxf_mleader_get_text_attachment_direction (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_attachment_direction (DxfMLeader *mleader, int16_t text_attachment_direction);
int16_t dxf_mleader_get_bottom_text_attachment_direction (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_bottom_text_attachment_direction (DxfMLeader *mleader, int16_t bottom_text_attachment_direction);
int16_t dxf_mleader_get_top_text_attachment_direction (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_top_text_attachment_direction (DxfMLeader *mleader, int16_t top_text_attachment_direction);
int dxf_mleader_get_enable_landing (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_enable_landing (DxfMLeader *mleader, int enable_landing);
int dxf_mleader_get_enable_dogleg (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_enable_dogleg (DxfMLeader *mleader, int enable_dogleg);
int dxf_mleader_get_enable_frame_text (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_enable_frame_text (DxfMLeader *mleader, int enable_frame_text);
int dxf_mleader_get_enable_annotation_scale (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_enable_annotation_scale (DxfMLeader *mleader, int enable_annotation_scale);
int dxf_mleader_get_text_direction_negative (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_direction_negative (DxfMLeader *mleader, int text_direction_negative);
char *dxf_mleader_get_block_attribute_text_string (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_attribute_text_string (DxfMLeader *mleader, char *block_attribute_text_string);
char *dxf_mleader_get_block_attribute_id (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_attribute_id (DxfMLeader *mleader, char *block_attribute_id);
char *dxf_mleader_get_leader_style_id (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_leader_style_id (DxfMLeader *mleader, char *leader_style_id);
char *dxf_mleader_get_leader_linetype_id (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_leader_linetype_id (DxfMLeader *mleader, char *leader_linetype_id);
char *dxf_mleader_get_arrowhead_id (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_arrowhead_id (DxfMLeader *mleader, char *arrowhead_id);
char *dxf_mleader_get_text_style_id (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_text_style_id (DxfMLeader *mleader, char *text_style_id);
char *dxf_mleader_get_block_content_id (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_block_content_id (DxfMLeader *mleader, char *block_content_id);
char *dxf_mleader_get_arrow_head_id (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_arrow_head_id (DxfMLeader *mleader, char *arrow_head_id);
DxfMLeader *dxf_mleader_get_next (DxfMLeader *mleader);
DxfMLeader *dxf_mleader_set_next (DxfMLeader *mleader, DxfMLeader *next);
DxfMLeader *dxf_mleader_get_last (DxfMLeader *mleader);
DxfMLeaderContextData *dxf_mleader_context_data_new ();
DxfMLeaderContextData *dxf_mleader_context_data_init (DxfMLeaderContextData *data);
int dxf_mleader_context_data_free (DxfMLeaderContextData *data);
void dxf_mleader_context_data_free_list (DxfMLeaderContextData *datas);
DxfPoint *dxf_mleader_context_data_get_p0 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_p0 (DxfMLeaderContextData *data, DxfPoint *p0);
double dxf_mleader_context_data_get_x0 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_x0 (DxfMLeaderContextData *data, double x0);
double dxf_mleader_context_data_get_y0 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_y0 (DxfMLeaderContextData *data, double y0);
double dxf_mleader_context_data_get_z0 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_z0 (DxfMLeaderContextData *data, double z0);
DxfPoint *dxf_mleader_context_data_get_vertex (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_vertex (DxfMLeaderContextData *data, DxfPoint *vertex);
double dxf_mleader_context_data_get_vertex_x0 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_vertex_x0 (DxfMLeaderContextData *data, double vertex_x0);
double dxf_mleader_context_data_get_vertex_y0 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_vertex_y0 (DxfMLeaderContextData *data, double vertex_y0);
double dxf_mleader_context_data_get_vertex_z0 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_vertex_z0 (DxfMLeaderContextData *data, double vertex_z0);
DxfPoint *dxf_mleader_context_data_get_p1 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_p1 (DxfMLeaderContextData *data, DxfPoint *p1);
double dxf_mleader_context_data_get_x1 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_x1 (DxfMLeaderContextData *data, double x1);
double dxf_mleader_context_data_get_y1 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_y1 (DxfMLeaderContextData *data, double y1);
double dxf_mleader_context_data_get_z1 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_z1 (DxfMLeaderContextData *data, double z1);
DxfPoint *dxf_mleader_context_data_get_p2 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_p2 (DxfMLeaderContextData *data, DxfPoint *p2);
double dxf_mleader_context_data_get_x2 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_x2 (DxfMLeaderContextData *data, double x2);
double dxf_mleader_context_data_get_y2 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_y2 (DxfMLeaderContextData *data, double y2);
double dxf_mleader_context_data_get_z2 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_z2 (DxfMLeaderContextData *data, double z2);
DxfPoint *dxf_mleader_context_data_get_p3 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_p3 (DxfMLeaderContextData *data, DxfPoint *p3);
double dxf_mleader_context_data_get_x3 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_x3 (DxfMLeaderContextData *data, double x3);
double dxf_mleader_context_data_get_y3 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_y3 (DxfMLeaderContextData *data, double y3);
double dxf_mleader_context_data_get_z3 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_z3 (DxfMLeaderContextData *data, double z3);
DxfPoint *dxf_mleader_context_data_get_p4 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_p4 (DxfMLeaderContextData *data, DxfPoint *p4);
double dxf_mleader_context_data_get_x4 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_x4 (DxfMLeaderContextData *data, double x4);
double dxf_mleader_context_data_get_y4 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_y4 (DxfMLeaderContextData *data, double y4);
double dxf_mleader_context_data_get_z4 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_z4 (DxfMLeaderContextData *data, double z4);
DxfPoint *dxf_mleader_context_data_get_p5 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_p5 (DxfMLeaderContextData *data, DxfPoint *p5);
double dxf_mleader_context_data_get_x5 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_x5 (DxfMLeaderContextData *data, double x5);
double dxf_mleader_context_data_get_y5 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_y5 (DxfMLeaderContextData *data, double y5);
double dxf_mleader_context_data_get_z5 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_z5 (DxfMLeaderContextData *data, double z5);
double dxf_mleader_context_data_get_block_content_scale (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_block_content_scale (DxfMLeaderContextData *data, double block_content_scale);
double dxf_mleader_context_data_get_content_scale (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_content_scale (DxfMLeaderContextData *data, double content_scale);
double dxf_mleader_context_data_get_text_height (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_height (DxfMLeaderContextData *data, double text_height);
double dxf_mleader_context_data_get_text_rotation (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_rotation (DxfMLeaderContextData *data, double text_rotation);
double dxf_mleader_context_data_get_text_width (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_width (DxfMLeaderContextData *data, double text_width);
double dxf_mleader_context_data_get_text_height2 (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_height2 (DxfMLeaderContextData *data, double text_height2);
double dxf_mleader_context_data_get_text_line_spacing_factor (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_line_spacing_factor (DxfMLeaderContextData *data, double text_line_spacing_factor);
double dxf_mleader_context_data_get_block_content_rotation (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_block_content_rotation (DxfMLeaderContextData *data, double block_content_rotation);
double dxf_mleader_context_data_get_block_transformation_matrix (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_block_transformation_matrix (DxfMLeaderContextData *data, double block_transformation_matrix);
int32_t dxf_mleader_context_data_get_text_color (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_color (DxfMLeaderContextData *data, int32_t text_color);
int32_t dxf_mleader_context_data_get_break_point_index (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_break_point_index (DxfMLeaderContextData *data, int32_t break_point_index);
int32_t dxf_mleader_context_data_get_text_background_color (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_background_color (DxfMLeaderContextData *data, int32_t text_background_color);
int32_t dxf_mleader_context_data_get_text_background_transparency (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_background_transparency (DxfMLeaderContextData *data, int32_t text_background_transparency);
int32_t dxf_mleader_context_data_get_block_content_color (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_block_content_color (DxfMLeaderContextData *data, int32_t block_content_color);
double dxf_mleader_context_data_get_MLeader_plane_origin_point (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_MLeader_plane_origin_point (DxfMLeaderContextData *data, double MLeader_plane_origin_point);
double dxf_mleader_context_data_get_MLeader_plane_X_axis_direction (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_MLeader_plane_X_axis_direction (DxfMLeaderContextData *data, double MLeader_plane_X_axis_direction);
double dxf_mleader_context_data_get_MLeader_plane_Y_axis_direction (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_MLeader_plane_Y_axis_direction (DxfMLeaderContextData *data, double MLeader_plane_Y_axis_direction);
double dxf_mleader_context_data_get_arrowhead_size (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_arrowhead_size (DxfMLeaderContextData *data, double arrowhead_size);
double dxf_mleader_context_data_get_text_background_scale_factor (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_background_scale_factor (DxfMLeaderContextData *data, double text_background_scale_factor);
double dxf_mleader_context_data_get_text_column_width (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_column_width (DxfMLeaderContextData *data, double text_column_width);
double dxf_mleader_context_data_get_text_column_gutter_width (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_column_gutter_width (DxfMLeaderContextData *data, double text_column_gutter_width);
double dxf_mleader_context_data_get_text_column_height (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_column_height (DxfMLeaderContextData *data, double text_column_height);
double dxf_mleader_context_data_get_landing_gap (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_landing_gap (DxfMLeaderContextData *data, double landing_gap);
int16_t dxf_mleader_context_data_get_text_line_spacing_style (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_line_spacing_style (DxfMLeaderContextData *data, int16_t text_line_spacing_style);
int16_t dxf_mleader_context_data_get_text_attachment (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_attachment (DxfMLeaderContextData *data, int16_t text_attachment);
int16_t dxf_mleader_context_data_get_text_flow_direction (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_flow_direction (DxfMLeaderContextData *data, int16_t text_flow_direction);
int16_t dxf_mleader_context_data_get_text_column_type (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_column_type (DxfMLeaderContextData *data, int16_t text_column_type);
int dxf_mleader_context_data_get_hasMtext (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_hasMtext (DxfMLeaderContextData *data, int hasMtext);
int dxf_mleader_context_data_get_is_text_background_color_on (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_is_text_background_color_on (DxfMLeaderContextData *data, int is_text_background_color_on);
int dxf_mleader_context_data_get_is_text_background_fill_on (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_is_text_background_fill_on (DxfMLeaderContextData *data, int is_text_background_fill_on);
int dxf_mleader_context_data_get_use_text_auto_height (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_use_text_auto_height (DxfMLeaderContextData *data, int use_text_auto_height);
int dxf_mleader_context_data_get_text_column_flow_reversed (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_column_flow_reversed (DxfMLeaderContextData *data, int text_column_flow_reversed);
int dxf_mleader_context_data_get_text_use_word_break (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_text_use_word_break (DxfMLeaderContextData *data, int text_use_word_break);
int dxf_mleader_context_data_get_has_block (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_has_block (DxfMLeaderContextData *data, int has_block);
int dxf_mleader_context_data_get_MLeader_plane_normal_reversed (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_MLeader_plane_normal_reversed (DxfMLeaderContextData *data, int MLeader_plane_normal_reversed);
char *dxf_mleader_context_data_get_default_text_contents (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_default_text_contents (DxfMLeaderContextData *data, char *default_text_contents);
char *dxf_mleader_context_data_get_type_style_id (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_type_style_id (DxfMLeaderContextData *data, char *type_style_id);
char *dxf_mleader_context_data_get_block_content_id (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_block_content_id (DxfMLeaderContextData *data, char *block_content_id);
DxfMLeaderContextData *dxf_mleader_context_data_get_next (DxfMLeaderContextData *data);
DxfMLeaderContextData *dxf_mleader_context_data_set_next (DxfMLeaderContextData *data, DxfMLeaderContextData *next);
DxfMLeaderContextData *dxf_mleader_context_data_get_last (DxfMLeaderContextData *data);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_new ();
DxfMLeaderLeaderNode *dxf_mleader_leader_node_init (DxfMLeaderLeaderNode *node);
int dxf_mleader_leader_node_free (DxfMLeaderLeaderNode *node);
void dxf_mleader_leader_node_free_list (DxfMLeaderLeaderNode *nodes);
DxfPoint *dxf_mleader_leader_node_get_p0 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_p0 (DxfMLeaderLeaderNode *node, DxfPoint *p0);
double dxf_mleader_leader_node_get_x0 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_x0 (DxfMLeaderLeaderNode *node, double x0);
double dxf_mleader_leader_node_get_y0 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_y0 (DxfMLeaderLeaderNode *node, double y0);
double dxf_mleader_leader_node_get_z0 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_z0 (DxfMLeaderLeaderNode *node, double z0);
DxfPoint *dxf_mleader_leader_node_get_p1 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_p1 (DxfMLeaderLeaderNode *node, DxfPoint *p1);
double dxf_mleader_leader_node_get_x1 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_x1 (DxfMLeaderLeaderNode *node, double x1);
double dxf_mleader_leader_node_get_y1 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_y1 (DxfMLeaderLeaderNode *node, double y1);
double dxf_mleader_leader_node_get_z1 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_z1 (DxfMLeaderLeaderNode *node, double z1);
DxfPoint *dxf_mleader_leader_node_get_p2 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_p2 (DxfMLeaderLeaderNode *node, DxfPoint *p2);
double dxf_mleader_leader_node_get_x2 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_x2 (DxfMLeaderLeaderNode *node, double x2);
double dxf_mleader_leader_node_get_y2 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_y2 (DxfMLeaderLeaderNode *node, double y2);
double dxf_mleader_leader_node_get_z2 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_z2 (DxfMLeaderLeaderNode *node, double z2);
DxfPoint *dxf_mleader_leader_node_get_p3 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_p3 (DxfMLeaderLeaderNode *node, DxfPoint *p3);
double dxf_mleader_leader_node_get_x3 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_x3 (DxfMLeaderLeaderNode *node, double x3);
double dxf_mleader_leader_node_get_y3 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_y3 (DxfMLeaderLeaderNode *node, double y3);
double dxf_mleader_leader_node_get_z3 (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_z3 (DxfMLeaderLeaderNode *node, double z3);
double dxf_mleader_leader_node_get_dogleg_length (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_dogleg_length (DxfMLeaderLeaderNode *node, double dogleg_length);
int32_t dxf_mleader_leader_node_get_leader_branch_index (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_context_data_set_leader_branch_index (DxfMLeaderLeaderNode *node, int32_t leader_branch_index);
int dxf_mleader_leader_node_get_has_set_last_leader_line_point (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_context_data_set_has_set_last_leader_line_point (DxfMLeaderLeaderNode *node, int has_set_last_leader_line_point);
int dxf_mleader_leader_node_get_has_set_dogleg_vector (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_context_data_set_has_set_dogleg_vector (DxfMLeaderLeaderNode *node, int has_set_dogleg_vector);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_get_next (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_set_next (DxfMLeaderLeaderNode *node, DxfMLeaderLeaderNode *next);
DxfMLeaderLeaderNode *dxf_mleader_leader_node_get_last (DxfMLeaderLeaderNode *node);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_new ();
DxfMLeaderLeaderLine *dxf_mleader_leader_line_init (DxfMLeaderLeaderLine *line);
int dxf_mleader_leader_line_free (DxfMLeaderLeaderLine *line);
void dxf_mleader_leader_line_free_list (DxfMLeaderLeaderLine *lines);
DxfPoint *dxf_mleader_leader_line_get_p0 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_p0 (DxfMLeaderLeaderLine *line, DxfPoint *p0);
double dxf_mleader_leader_line_get_x0 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_x0 (DxfMLeaderLeaderLine *line, double x0);
double dxf_mleader_leader_line_get_y0 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_y0 (DxfMLeaderLeaderLine *line, double y0);
double dxf_mleader_leader_line_get_z0 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_z0 (DxfMLeaderLeaderLine *line, double z0);
DxfPoint *dxf_mleader_leader_line_get_p1 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_p1 (DxfMLeaderLeaderLine *line, DxfPoint *p1);
double dxf_mleader_leader_line_get_x1 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_x1 (DxfMLeaderLeaderLine *line, double x1);
double dxf_mleader_leader_line_get_y1 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_y1 (DxfMLeaderLeaderLine *line, double y1);
double dxf_mleader_leader_line_get_z1 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_z1 (DxfMLeaderLeaderLine *line, double z1);
DxfPoint *dxf_mleader_leader_line_get_p2 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_p2 (DxfMLeaderLeaderLine *line, DxfPoint *p2);
double dxf_mleader_leader_line_get_x2 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_x2 (DxfMLeaderLeaderLine *line, double x2);
double dxf_mleader_leader_line_get_y2 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_y2 (DxfMLeaderLeaderLine *line, double y2);
double dxf_mleader_leader_line_get_z2 (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_z2 (DxfMLeaderLeaderLine *line, double z2);
int32_t dxf_mleader_leader_line_get_break_point_index (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_break_point_index (DxfMLeaderLeaderLine *line, int32_t break_point_index);
int32_t dxf_mleader_leader_line_get_leader_line_index (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_leader_line_index (DxfMLeaderLeaderLine *line, int32_t leader_line_index);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_get_next (DxfMLeaderLeaderLine *line);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_set_next (DxfMLeaderLeaderLine *line, DxfMLeaderLeaderLine *next);
DxfMLeaderLeaderLine *dxf_mleader_leader_line_get_last (DxfMLeaderLeaderLine *line);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_MLEADER_H */


/* EOF */
