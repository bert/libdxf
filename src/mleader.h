/*!
 * \file mleader.h
 *
 * \author Copyright (C) 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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


DxfMLeader *dxf_mleader_new();


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_MLEADER_H */


/* EOF */
