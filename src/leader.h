/*!
 * \file leader.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018, 2020
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF leader entity (\c LEADER).
 *
 * \since The \c LEADER entity was introduced in DXF R13.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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


#ifndef LIBDXF_SRC_LEADER_H
#define LIBDXF_SRC_LEADER_H


#include "global.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD leader entity (\c LEADER).
 */
typedef struct
dxf_leader_struct
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
                /*!< Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60. */
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
                 * Group code = 67. */
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
        /* Specific members for a DXF 3D face. */
        char *dimension_style_name;
                /*!< Dimension style name.\n
                 * Group code = 3. */
        DxfPoint *p0;
                /*!< Vertex coordinates (single linked list, one entry
                 * for each vertex).\n
                 * Group codes = 10, 20 and 30.*/
        double text_annotation_height;
                /*!< Text annotation height.\n
                 * Group code = 40. */
        double text_annotation_width;
                /*!< Text annotation width.\n
                 * Group code = 41. */
        int arrow_head_flag;
                /*!< Arrow head flag.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "0"> Disabled.</li>
                 * <li value = "1"> Enabled.</li>
                 * </ol>
                 * Group code = 71. */
        int path_type;
                /*!< Leader path type.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "0"> Straight line segments.</li>
                 * <li value = "1"> Spline.</li>
                 * </ol>
                 * Group code = 72. */
        int creation_flag;
                /*!< Leader creation flag (default = 3).\n
                 * Not bit coded:\n
                 * <ol>
                 * <li value = "0"> Leader created with text annotation.</li>
                 * <li value = "1"> Created with tolerance annotation.</li>
                 * <li value = "2"> Created with block reference annotation.</li>
                 * <li value = "3"> Created without any annotation.</li>
                 * </ol>
                 * Group code = 73. */
        int hookline_direction_flag;
                /*!< Hookline direction flag.\n
                 * Not bit coded:\n
                 * <ol>
                 * <li value = "0"> Hookline (or end of tangent for a
                 * splined leader) is the opposite direction from the
                 * horizontal vector.</li>
                 * <li value = "1"> Hookline (or end of tangent for a
                 * splined leader) is the same direction as horizontal
                 * vector (see Group code 75).</li>
                 * </ol>
                 * Group code = 74. */
        int hookline_flag;
                /*!< Hookline flag.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "0"> No hookline.</li>
                 * <li value = "1"> Has a hookline.</li>
                 * </ol>
                 * Group code = 75. */
        int number_vertices;
                /*!< Number of vertices in leader (ignored for DXFIN).\n
                 * Group code = 76. */
        int leader_color;
                /*!< Color to use if leader's DIMCLRD=BYBLOCK.\n
                 * Group code = 77. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        DxfPoint *p1;
                /*!< The "Horizontal" direction for leader.\n
                 * Group codes = 211, 221 and 231. */
        DxfPoint *p2;
                /*!< The Block reference insertion point offset from the
                 * last leader vertex.\n
                 * Group code = 212, 222 and 232. */
        DxfPoint *p3;
                /*!< the Annotation placement point offset from last
                 * leader vertex.\n
                 * Group codes = 213, 223 and 233. */
        char *annotation_reference_hard;
                /*!< Hard reference to associated annotation (mtext,
                 * tolerance, or insert entity).\n
                 * Group code = 340. */
        struct DxfLeader *next;
                /*!< Pointer to the next DxfLeader.\n
                 * \c NULL in the last DxfLeader. */
} DxfLeader;


DxfLeader *dxf_leader_new ();
DxfLeader *dxf_leader_init (DxfLeader *leader);
DxfLeader *dxf_leader_read (DxfFile *fp, DxfLeader *leader);
int dxf_leader_write (DxfFile *fp, DxfLeader *leader);
int dxf_leader_free (DxfLeader *leader);
void dxf_leader_free_list (DxfLeader *leaders);
int dxf_leader_get_id_code (DxfLeader *leader);
DxfLeader *dxf_leader_set_id_code (DxfLeader *leader, int id_code);
char *dxf_leader_get_linetype (DxfLeader *leader);
DxfLeader *dxf_leader_set_linetype (DxfLeader *leader, char *linetype);
char *dxf_leader_get_layer (DxfLeader *leader);
DxfLeader *dxf_leader_set_layer (DxfLeader *leader, char *layer);
double dxf_leader_get_elevation (DxfLeader *leader);
DxfLeader *dxf_leader_set_elevation (DxfLeader *leader, double elevation);
double dxf_leader_get_thickness (DxfLeader *leader);
DxfLeader *dxf_leader_set_thickness (DxfLeader *leader, double thickness);
double dxf_leader_get_linetype_scale (DxfLeader *leader);
DxfLeader *dxf_leader_set_linetype_scale (DxfLeader *leader, double linetype_scale);
int16_t dxf_leader_get_visibility (DxfLeader *leader);
DxfLeader *dxf_leader_set_visibility (DxfLeader *leader, int16_t visibility);
int dxf_leader_get_color (DxfLeader *leader);
DxfLeader *dxf_leader_set_color (DxfLeader *leader, int color);
int dxf_leader_get_paperspace (DxfLeader *leader);
DxfLeader *dxf_leader_set_paperspace (DxfLeader *leader, int paperspace);
char *dxf_leader_get_dictionary_owner_soft (DxfLeader *leader);
DxfLeader *dxf_leader_set_dictionary_owner_soft (DxfLeader *leader, char *dictionary_owner_soft);
char *dxf_leader_get_dictionary_owner_hard (DxfLeader *leader);
DxfLeader *dxf_leader_set_dictionary_owner_hard (DxfLeader *leader, char *dictionary_owner_hard);
char *dxf_leader_get_dimension_style_name (DxfLeader *leader);
DxfLeader *dxf_leader_set_dimension_style_name (DxfLeader *leader, char *dimension_style_name);
DxfPoint *dxf_leader_get_p0 (DxfLeader *leader);
DxfLeader *dxf_leader_set_p0 (DxfLeader *leader, DxfPoint *p0);
double dxf_leader_get_x0 (DxfLeader *leader);
DxfLeader *dxf_leader_set_x0 (DxfLeader *leader, double x0);
double dxf_leader_get_y0 (DxfLeader *leader);
DxfLeader *dxf_leader_set_y0 (DxfLeader *leader, double y0);
double dxf_leader_get_z0 (DxfLeader *leader);
DxfLeader *dxf_leader_set_z0 (DxfLeader *leader, double z0);
double dxf_leader_get_text_annotation_height (DxfLeader *leader);
DxfLeader *dxf_leader_set_text_annotation_height (DxfLeader *leader, double text_annotation_height);
double dxf_leader_get_text_annotation_width (DxfLeader *leader);
DxfLeader *dxf_leader_set_text_annotation_width (DxfLeader *leader, double text_annotation_width);
int dxf_leader_get_arrow_head_flag (DxfLeader *leader);
DxfLeader *dxf_leader_set_arrow_head_flag (DxfLeader *leader, int arrow_head_flag);
int dxf_leader_get_path_type (DxfLeader *leader);
DxfLeader *dxf_leader_set_path_type (DxfLeader *leader, int path_type);
int dxf_leader_get_creation_flag (DxfLeader *leader);
DxfLeader *dxf_leader_set_creation_flag (DxfLeader *leader, int creation_flag);
int dxf_leader_get_hookline_direction_flag (DxfLeader *leader);
DxfLeader *dxf_leader_set_hookline_direction_flag (DxfLeader *leader, int hookline_direction_flag);
int dxf_leader_get_hookline_flag (DxfLeader *leader);
DxfLeader *dxf_leader_set_hookline_flag (DxfLeader *leader, int hookline_flag);
int dxf_leader_get_number_vertices (DxfLeader *leader);
DxfLeader *dxf_leader_set_number_vertices (DxfLeader *leader, int number_vertices);
int dxf_leader_get_leader_color (DxfLeader *leader);
DxfLeader *dxf_leader_set_leader_color (DxfLeader *leader, int leader_color);
double dxf_leader_get_extr_x0 (DxfLeader *leader);
DxfLeader *dxf_leader_set_extr_x0 (DxfLeader *leader, double extr_x0);
double dxf_leader_get_extr_y0 (DxfLeader *leader);
DxfLeader *dxf_leader_set_extr_y0 (DxfLeader *leader, double extr_y0);
double dxf_leader_get_extr_z0 (DxfLeader *leader);
DxfLeader *dxf_leader_set_extr_z0 (DxfLeader *leader, double extr_z0);
DxfPoint *dxf_leader_get_p1 (DxfLeader *leader);
DxfLeader *dxf_leader_set_p1 (DxfLeader *leader, DxfPoint *p1);
double dxf_leader_get_x1 (DxfLeader *leader);
DxfLeader *dxf_leader_set_x1 (DxfLeader *leader, double x1);
double dxf_leader_get_y1 (DxfLeader *leader);
DxfLeader *dxf_leader_set_y1 (DxfLeader *leader, double y1);
double dxf_leader_get_z1 (DxfLeader *leader);
DxfLeader *dxf_leader_set_z1 (DxfLeader *leader, double z1);
DxfPoint *dxf_leader_get_p2 (DxfLeader *leader);
DxfLeader *dxf_leader_set_p2 (DxfLeader *leader, DxfPoint *p2);
double dxf_leader_get_x2 (DxfLeader *leader);
DxfLeader *dxf_leader_set_x2 (DxfLeader *leader, double x2);
double dxf_leader_get_y2 (DxfLeader *leader);
DxfLeader *dxf_leader_set_y2 (DxfLeader *leader, double y2);
double dxf_leader_get_z2 (DxfLeader *leader);
DxfLeader *dxf_leader_set_z2 (DxfLeader *leader, double z2);
DxfPoint *dxf_leader_get_p3 (DxfLeader *leader);
DxfLeader *dxf_leader_set_p3 (DxfLeader *leader, DxfPoint *p3);
double dxf_leader_get_x3 (DxfLeader *leader);
DxfLeader *dxf_leader_set_x3 (DxfLeader *leader, double x3);
double dxf_leader_get_y3 (DxfLeader *leader);
DxfLeader *dxf_leader_set_y3 (DxfLeader *leader, double y3);
double dxf_leader_get_z3 (DxfLeader *leader);
DxfLeader *dxf_leader_set_z3 (DxfLeader *leader, double z3);
char *dxf_leader_get_annotation_reference_hard (DxfLeader *leader);
DxfLeader *dxf_leader_set_annotation_reference_hard (DxfLeader *leader, char *annotation_reference_hard);
DxfLeader *dxf_leader_get_next (DxfLeader *leader);
DxfLeader *dxf_leader_set_next (DxfLeader *leader, DxfLeader *next);
DxfLeader *dxf_leader_get_last (DxfLeader *leader);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LEADER_H */


/* EOF */
