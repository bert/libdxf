/*!
 * \file mleaderstyle.h
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF mleaderstyle entity (\c MLEADERSTYLE).
 *
 * \since The \c MLEADERSTYLE entity was introduced in DXF R2007.
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


#ifndef LIBDXF_SRC_MLEADERSTYLE_H
#define LIBDXF_SRC_MLEADERSTYLE_H


#include "global.h"
#include "binary_graphics_data.h"

#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD mleaderstyle entity (\c MLEADERSTYLE).
 */
typedef struct
dxf_mleaderstyle_struct
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
        /* Specific members for a DXF MLeaderStyle. */
        char *mleaderstyle_description;
                /*!< Mleader Style Description.\n
                 * Group code = 3. */
        double first_segment_angle_constraint;
                /*!< First Segment Angle Constraint.\n
                 * Group code = 40. */
        double second_segment_angle_constraint;
                /*!< Second Segment Angle Constraint.\n
                 * Group code = 41. */
        double landing_gap;
                /*!< Landing Gap.\n
                 * Group code = 42. */
        double dogleg_length;
                /*!< Dogleg Length.\n
                 * Group code = 43. */
        double arrowhead_size;
                /*!< Arrowhead Size.\n
                 * Group code = 44. */
        double text_height;
                /*!< Text Height.\n
                 * Group code = 45. */
        double align_space;
                /*!< Align Space.\n
                 * Group code = 46. */
        double block_content_scale_x;
                /*!< Block Content Scale on X-axis.\n
                 * Group code = 47. */
        double block_content_scale_y;
                /*!< Block Content Scale on Y-axis.\n
                 * Group code = 49. */
        int32_t leader_line_weight;
                /*!< Leader Line Weight.\n
                 * Group code = 90. */
        int32_t maxleader_segment_points;
                /*!< MaxLeader Segment Points.\n
                 * Group code = 92. */
        int32_t text_color;
                /*!< Text Color.\n
                 * Group code = 93. */
        int32_t block_content_color;
                /*!< Block Content Color.\n
                 * Group code = 94. */
        double block_content_scale_z;
                /*!< Block Content Scale on Z-axis.\n
                 * Group code = 140. */
        double block_content_rotation;
                /*!< Block Content Rotation.\n
                 * Group code = 141. */
        double scale;
                /*!< Scale.\n
                 * Group code = 142. */
        double break_gap_size;
                /*!< Break Gap Size.\n
                 * Group code = 143. */
        int16_t content_type;
                /*!< Content type.\n
                 * Group code = 170. */
        int16_t draw_mleader_order_type;
                /*!< Draw MLeader Order type.\n
                 * Group code = 171. */
        int16_t draw_leader_order_type;
                /*!< Draw Leader Order type.\n
                 * Group code = 172. */
        int16_t leader_line_color;
                /*!< LeaderLineColor.\n
                 * Group code = 173. */
        int16_t text_left_attachment_type;
                /*!< Text Left Attachment Type.\n
                 * Group code = 174. */
        int16_t text_angle_type;
                /*!< Text Angle Type.\n
                 * Group code = 175. */
        int16_t text_alignment_type;
                /*!< Text Alignment Type.\n
                 * Group code = 176. */
        int16_t block_content_connection_type;
                /*!< Block Content Connection Type.\n
                 * Group code = 177. */
        int16_t text_right_attachment_type;
                /*!< Text Right Attachment Type.\n
                 * Group code = 178. */
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
                /*!< Enable Frame Text (boolean).\n
                 * Group code = 292. */
        int enable_block_content_scale;
                /*!< Enable Block Content Scale (boolean).\n
                 * Group code = 293. */
        int enable_block_content_rotation;
                /*!< Enable Block Content Rotation (boolean).\n
                 * Group code = 294. */
        int overwrite_property_value;
                /*!< Overwrite Property Value (boolean).\n
                 * Group code = 295. */
        int is_annotative;
                /*!< Is Annotative (boolean).\n
                 * Group code = 296. */
        int text_align_always_left;
                /*!< Text Align Always Left (boolean).\n
                 * Group code = 297. */
        char *default_mtext_contents;
                /*!< Default MText Contents.\n
                 * Group code = 300. */
        char *leader_linetype_id;
                /*!< LeaderLineType ID (string representing hex object
                 * IDs).\n
                 * Group code = 340. */
        char *arrow_head_id;
                /*!< Arrowhead ID (string representing hex object
                 * IDs).\n
                 * Group code = 341. */
        char *mtext_style_id;
                /*!< mTextStyleId (string representing hex object
                 * IDs).\n
                 * Group code = 342. */
        char *block_content_id;
                /*!< Block Content Id (string representing hex object
                 * IDs).\n
                 * Group code = 343. */
        struct DxfMLeaderstyle *next;
                /*!< Pointer to the next DxfMLeaderstyle.\n
                 * \c NULL in the last DxfMLeaderstyle. */
} DxfMLeaderstyle;


DxfMLeaderstyle *dxf_mleaderstyle_new ();
DxfMLeaderstyle *dxf_mleaderstyle_init (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_read (DxfFile *fp, DxfMLeaderstyle *mleaderstyle);
int dxf_mleaderstyle_write (DxfFile *fp, DxfMLeaderstyle *mleaderstyle);
int dxf_mleaderstyle_free (DxfMLeaderstyle *mleaderstyle);
void dxf_mleaderstyle_free_list (DxfMLeaderstyle *mleaderstyles);
int dxf_mleaderstyle_get_id_code (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_id_code (DxfMLeaderstyle *mleaderstyle, int id_code);
char *dxf_mleaderstyle_get_linetype (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_linetype (DxfMLeaderstyle *mleaderstyle, char *linetype);
char *dxf_mleaderstyle_get_layer (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_layer (DxfMLeaderstyle *mleaderstyle, char *layer);
double dxf_mleaderstyle_get_elevation (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_elevation (DxfMLeaderstyle *mleaderstyle, double elevation);
double dxf_mleaderstyle_get_thickness (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_thickness (DxfMLeaderstyle *mleaderstyle, double thickness);
double dxf_mleaderstyle_get_linetype_scale (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_linetype_scale (DxfMLeaderstyle *mleaderstyle, double linetype_scale);
int16_t dxf_mleaderstyle_get_visibility (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_visibility (DxfMLeaderstyle *mleaderstyle, int16_t visibility);
int dxf_mleaderstyle_get_color (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_color (DxfMLeaderstyle *mleaderstyle, int color);
int dxf_mleaderstyle_get_paperspace (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_paperspace (DxfMLeaderstyle *mleaderstyle, int paperspace);
int dxf_mleaderstyle_get_graphics_data_size (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_graphics_data_size (DxfMLeaderstyle *mleaderstyle, int graphics_data_size);
int16_t dxf_mleaderstyle_get_shadow_mode (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_shadow_mode (DxfMLeaderstyle *mleaderstyle, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_mleaderstyle_get_binary_graphics_data (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_binary_graphics_data (DxfMLeaderstyle *mleaderstyle, DxfBinaryGraphicsData *data);
char *dxf_mleaderstyle_get_dictionary_owner_soft (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_dictionary_owner_soft (DxfMLeaderstyle *mleaderstyle, char *dictionary_owner_soft);
char *dxf_mleaderstyle_get_object_owner_soft (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_object_owner_soft (DxfMLeaderstyle *mleaderstyle, char *object_owner_soft);
char *dxf_mleaderstyle_get_material (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_material (DxfMLeaderstyle *mleaderstyle, char *material);
char *dxf_mleaderstyle_get_dictionary_owner_hard (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_dictionary_owner_hard (DxfMLeaderstyle *mleaderstyle, char *dictionary_owner_hard);
int16_t dxf_mleaderstyle_get_lineweight (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_lineweight (DxfMLeaderstyle *mleaderstyle, int16_t lineweight);
char *dxf_mleaderstyle_get_plot_style_name (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_plot_style_name (DxfMLeaderstyle *mleaderstyle, char *plot_style_name);
long dxf_mleaderstyle_get_color_value (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_color_value (DxfMLeaderstyle *mleaderstyle, long color_value);
char *dxf_mleaderstyle_get_color_name (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_color_name (DxfMLeaderstyle *mleaderstyle, char *color_name);
long dxf_mleaderstyle_get_transparency (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_transparency (DxfMLeaderstyle *mleaderstyle, long transparency);
char *dxf_mleaderstyle_get_mleaderstyle_description (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_mleaderstyle_description (DxfMLeaderstyle *mleaderstyle, char *mleaderstyle_description);
double dxf_mleaderstyle_get_first_segment_angle_constraint (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_first_segment_angle_constraint (DxfMLeaderstyle *mleaderstyle, double first_segment_angle_constraint);
double dxf_mleaderstyle_get_second_segment_angle_constraint (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_second_segment_angle_constraint (DxfMLeaderstyle *mleaderstyle, double second_segment_angle_constraint);
double dxf_mleaderstyle_get_landing_gap (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_landing_gap (DxfMLeaderstyle *mleaderstyle, double landing_gap);
double dxf_mleaderstyle_get_dogleg_length (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_dogleg_length (DxfMLeaderstyle *mleaderstyle, double dogleg_length);
double dxf_mleaderstyle_get_arrowhead_size (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_arrowhead_size (DxfMLeaderstyle *mleaderstyle, double arrowhead_size);
double dxf_mleaderstyle_get_text_height (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_text_height (DxfMLeaderstyle *mleaderstyle, double text_height);
double dxf_mleaderstyle_get_align_space (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_align_space (DxfMLeaderstyle *mleaderstyle, double align_space);
double dxf_mleaderstyle_get_block_content_scale_x (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_block_content_scale_x (DxfMLeaderstyle *mleaderstyle, double block_content_scale_x);
double dxf_mleaderstyle_get_block_content_scale_y (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_block_content_scale_y (DxfMLeaderstyle *mleaderstyle, double block_content_scale_y);
double dxf_mleaderstyle_get_block_content_scale_z (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_block_content_scale_z (DxfMLeaderstyle *mleaderstyle, double block_content_scale_z);
int32_t dxf_mleaderstyle_get_leader_line_weight (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_leader_line_weight (DxfMLeaderstyle *mleaderstyle, int32_t leader_line_weight);
int32_t dxf_mleaderstyle_get_maxleader_segment_points (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_maxleader_segment_points (DxfMLeaderstyle *mleaderstyle, int32_t maxleader_segment_points);
int32_t dxf_mleaderstyle_get_text_color (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_text_color (DxfMLeaderstyle *mleaderstyle, int32_t text_color);
int32_t dxf_mleaderstyle_get_block_content_color (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_block_content_color (DxfMLeaderstyle *mleaderstyle, int32_t block_content_color);
double dxf_mleaderstyle_get_block_content_rotation (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_block_content_rotation (DxfMLeaderstyle *mleaderstyle, double block_content_rotation);
double dxf_mleaderstyle_get_scale (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_scale (DxfMLeaderstyle *mleaderstyle, double scale);
double dxf_mleaderstyle_get_break_gap_size (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_break_gap_size (DxfMLeaderstyle *mleaderstyle, double break_gap_size);
int16_t dxf_mleaderstyle_get_content_type (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_content_type (DxfMLeaderstyle *mleaderstyle, int16_t content_type);
int16_t dxf_mleaderstyle_get_draw_mleader_order_type (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_draw_mleader_order_type (DxfMLeaderstyle *mleaderstyle, int16_t draw_mleader_order_type);
int16_t dxf_mleaderstyle_get_draw_leader_order_type (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_draw_leader_order_type (DxfMLeaderstyle *mleaderstyle, int16_t draw_leader_order_type);
int16_t dxf_mleaderstyle_get_leader_line_color (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_leader_line_color (DxfMLeaderstyle *mleaderstyle, int16_t leader_line_color);
int16_t dxf_mleaderstyle_get_text_left_attachment_type (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_text_left_attachment_type (DxfMLeaderstyle *mleaderstyle, int16_t text_left_attachment_type);
int16_t dxf_mleaderstyle_get_text_right_attachment_type (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_text_right_attachment_type (DxfMLeaderstyle *mleaderstyle, int16_t text_right_attachment_type);
int16_t dxf_mleaderstyle_get_text_angle_type (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_text_angle_type (DxfMLeaderstyle *mleaderstyle, int16_t text_angle_type);
int16_t dxf_mleaderstyle_get_text_alignment_type (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_text_alignment_type (DxfMLeaderstyle *mleaderstyle, int16_t text_alignment_type);
int16_t dxf_mleaderstyle_get_block_content_connection_type (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_block_content_connection_type (DxfMLeaderstyle *mleaderstyle, int16_t block_content_connection_type);
int16_t dxf_mleaderstyle_get_text_attachment_direction (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_text_attachment_direction (DxfMLeaderstyle *mleaderstyle, int16_t text_attachment_direction);
int16_t dxf_mleaderstyle_get_bottom_text_attachment_direction (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_bottom_text_attachment_direction (DxfMLeaderstyle *mleaderstyle, int16_t bottom_text_attachment_direction);
int16_t dxf_mleaderstyle_get_top_text_attachment_direction (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_top_text_attachment_direction (DxfMLeaderstyle *mleaderstyle, int16_t top_text_attachment_direction);
int dxf_mleaderstyle_get_enable_landing (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_enable_landing (DxfMLeaderstyle *mleaderstyle, int enable_landing);
int dxf_mleaderstyle_get_enable_dogleg (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_enable_dogleg (DxfMLeaderstyle *mleaderstyle, int enable_dogleg);
int dxf_mleaderstyle_get_enable_frame_text (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_enable_frame_text (DxfMLeaderstyle *mleaderstyle, int enable_frame_text);
int dxf_mleaderstyle_get_enable_block_content_scale (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_enable_block_content_scale (DxfMLeaderstyle *mleaderstyle, int enable_block_content_scale);
int dxf_mleaderstyle_get_enable_block_content_rotation (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_enable_block_content_rotation (DxfMLeaderstyle *mleaderstyle, int enable_block_content_rotation);
int dxf_mleaderstyle_get_overwrite_property_value (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_overwrite_property_value (DxfMLeaderstyle *mleaderstyle, int overwrite_property_value);
int dxf_mleaderstyle_get_is_annotative (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_is_annotative (DxfMLeaderstyle *mleaderstyle, int is_annotative);
int dxf_mleaderstyle_get_text_align_always_left (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_text_align_always_left (DxfMLeaderstyle *mleaderstyle, int text_align_always_left);
char *dxf_mleaderstyle_get_default_mtext_contents (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_default_mtext_contents (DxfMLeaderstyle *mleaderstyle, char *default_mtext_contents);
char *dxf_mleaderstyle_get_leader_linetype_id (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_leader_linetype_id (DxfMLeaderstyle *mleaderstyle, char *leader_linetype_id);
char *dxf_mleaderstyle_get_arrow_head_id (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_arrow_head_id (DxfMLeaderstyle *mleaderstyle, char *arrow_head_id);
char *dxf_mleaderstyle_get_mtext_style_id (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_mtext_style_id (DxfMLeaderstyle *mleaderstyle, char *mtext_style_id);
char *dxf_mleaderstyle_get_block_content_id (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_block_content_id (DxfMLeaderstyle *mleaderstyle, char *block_content_id);
DxfMLeaderstyle *dxf_mleaderstyle_get_next (DxfMLeaderstyle *mleaderstyle);
DxfMLeaderstyle *dxf_mleaderstyle_set_next (DxfMLeaderstyle *mleaderstyle, DxfMLeaderstyle *next);
DxfMLeaderstyle *dxf_mleaderstyle_get_last (DxfMLeaderstyle *mleaderstyle);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_MLEADERSTYLE_H */


/* EOF */
