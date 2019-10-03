/*!
 * \file attdef.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017,
 * 2018, 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF attribute definition entity (\c ATTDEF).
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


#include "global.h"
#include "point.h"
#include "binary_data.h"


#ifndef LIBDXF_SRC_ATTDEF_H
#define LIBDXF_SRC_ATTDEF_H


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD attribute definition entity
 * (\c ATTDEF).
 */
typedef struct
dxf_attdef_struct
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
        /* Specific members for a DXF attdef. */
        char *default_value;
                /*!< Default value for the attribute.\n
                 * Group code = 1. */
        char *tag_value;
                /*!< Tagname for the attribute.\n
                 * Group code = 2. */
        char *prompt_value;
                /*!< Prompt text for the value to be stored in the
                 * attribute.\n
                 * Group code = 3. */
        char *text_style;
                /*!< The style used for the presentation of the value of
                 * the attribute.\n
                 * Defaults to \c STANDARD if  omitted in the DXF file.\n
                 * Group code = 7. */
        DxfPoint *p0;
                /*!< First alignment point (in OCS).\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Second alignment point (in OCS)(optional).\n
                 * Meaningful only if 72 or 74 group values are nonzero.\n
                 * Group codes = 11, 21 and 31. */
        double height;
                /*!< Character height of the attribute value.\n
                 * Group code = 40. */
        double rel_x_scale;
                /*!< Relative scale in the X-direction.\n
                 * Defaults to 1.0 if omitted from DXF file.\n
                 * Group code = 41. */
        double rot_angle;
                /*!< Rotation angle of the attribute value.\n
                 * Defaults to 0.0 if omitted from DXF file.\n
                 * Group code = 50. */
        double obl_angle;
                /*!< Oblique angle of the attribute value.\n
                 * Defaults to 0.0 if omitted from DXF file.\n
                 * Group code = 51. */
        int16_t attr_flags;
                /*!< Attribute flags.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> attribute is invisible (does not display).</li>
                 * <li value = "2"> this is a constant attribute.</li>
                 * <li value = "4"> verification is required on input of this attribute.</li>
                 * <li value = "8"> attribute is preset (no prompt during insertion).</li>
                 * </ol>
                 * Group code = 70.
                 */
        int16_t text_flags;
                /*!< Text flags.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "2"> text is backward (mirrored in X).</li>
                 * <li value = "4"> text is upside down (mirrored in Y).</li>
                 * </ol>
                 * Defaults to 0 if ommited from DXF file.\n
                 * Group code = 71. */
        int16_t hor_align;
                /*!< Horizontal text justification type (optional,
                 * default = 0).\n
                 * See \c TEXT.\n
                 * Not bit coded:
                 * <ol>
                 * <li value = "0"> Left.</li>
                 * <li value = "1"> Center.</li>
                 * <li value = "2"> Right.</li>
                 * <li value = "3"> Aligned, only when vert_align = 0.</li>
                 * <li value = "4"> Middle, only when vert_align = 0.</li>
                 * <li value = "5"> Fit, only when vert_align = 0.</li>
                 * </ol>
                 * Group code = 72. */
        int16_t field_length;
                /*!< Field length (optional; default = 0) (not currently
                 * used in DXF R14).\n
                 * Group code = 73. */
        int16_t vert_align;
                /*!< Vertical text justification type (optional,
                 * default = 0).\n
                 * See group code 73 in \c TEXT.\n
                 * Not bit coded:\n
                 * <ol>
                 * <li value = "0"> Baseline.</li>
                 * <li value = "1"> Bottom.</li>
                 * <li value = "2"> Middle.</li>
                 * <li value = "3"> Top.</li>
                 * </ol>
                 * Group code = 74.\n
                 * \version Added in DXF R12. */
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
        struct DxfAttdef *next;
                /*!< Pointer to the next DxfAttdef.\n
                 * \c NULL in the last DxfAttdef. */
} DxfAttdef;


DxfAttdef *dxf_attdef_new ();
DxfAttdef *dxf_attdef_init (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_read (DxfFile *fp, DxfAttdef *attdef);
int dxf_attdef_write (DxfFile *fp, DxfAttdef *attdef);
int dxf_attdef_free (DxfAttdef *attdef);
void dxf_attdef_free_list (DxfAttdef *attdefs);
int dxf_attdef_get_id_code (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_id_code (DxfAttdef *attdef, int id_code);
char *dxf_attdef_get_linetype (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_linetype (DxfAttdef *attdef, char *linetype);
char *dxf_attdef_get_layer (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_layer (DxfAttdef *attdef, char *layer);
double dxf_attdef_get_elevation (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_elevation (DxfAttdef *attdef, double elevation);
double dxf_attdef_get_thickness (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_thickness (DxfAttdef *attdef, double thickness);
double dxf_attdef_get_linetype_scale (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_linetype_scale (DxfAttdef *attdef, double linetype_scale);
int16_t dxf_attdef_get_visibility (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_visibility (DxfAttdef *attdef, int16_t visibility);
int16_t dxf_attdef_get_color (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_color (DxfAttdef *attdef, int16_t color);
int16_t dxf_attdef_get_paperspace (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_paperspace (DxfAttdef *attdef, int16_t paperspace);
int32_t dxf_attdef_get_graphics_data_size (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_graphics_data_size (DxfAttdef *attdef, int32_t graphics_data_size);
int16_t dxf_attdef_get_shadow_mode (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_shadow_mode (DxfAttdef *attdef, int16_t shadow_mode);
DxfBinaryData *dxf_attdef_get_binary_graphics_data (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_binary_graphics_data (DxfAttdef *attdef, DxfBinaryData *data);
char *dxf_attdef_get_dictionary_owner_soft (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_dictionary_owner_soft (DxfAttdef *attdef, char *dictionary_owner_soft);
char *dxf_attdef_get_object_owner_soft (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_object_owner_soft (DxfAttdef *attdef, char *object_owner_soft);
char *dxf_attdef_get_material (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_material (DxfAttdef *attdef, char *material);
char *dxf_attdef_get_dictionary_owner_hard (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_dictionary_owner_hard (DxfAttdef *attdef, char *dictionary_owner_hard);
int16_t dxf_attdef_get_lineweight (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_lineweight (DxfAttdef *attdef, int16_t lineweight);
char *dxf_attdef_get_plot_style_name (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_plot_style_name (DxfAttdef *attdef, char *plot_style_name);
int32_t dxf_attdef_get_color_value (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_color_value (DxfAttdef *attdef, int32_t color_value);
char *dxf_attdef_get_color_name (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_color_name (DxfAttdef *attdef, char *color_name);
int32_t dxf_attdef_get_transparency (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_transparency (DxfAttdef *attdef, int32_t transparency);
char *dxf_attdef_get_default_value (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_default_value (DxfAttdef *attdef, char *default_value);
char *dxf_attdef_get_tag_value (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_tag_value (DxfAttdef *attdef, char *tag_value);
char *dxf_attdef_get_prompt_value (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_prompt_value (DxfAttdef *attdef, char *prompt_value);
char *dxf_attdef_get_text_style (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_text_style (DxfAttdef *attdef, char *text_style);
DxfPoint *dxf_attdef_get_p0 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_p0 (DxfAttdef *attdef, DxfPoint *p0);
double dxf_attdef_get_x0 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_x0 (DxfAttdef *attdef, double x0);
double dxf_attdef_get_y0 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_y0 (DxfAttdef *attdef, double y0);
double dxf_attdef_get_z0 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_z0 (DxfAttdef *attdef, double z0);
DxfPoint *dxf_attdef_get_p1 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_p1 (DxfAttdef *attdef, DxfPoint *p1);
double dxf_attdef_get_x1 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_x1 (DxfAttdef *attdef, double x1);
double dxf_attdef_get_y1 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_y1 (DxfAttdef *attdef, double y1);
double dxf_attdef_get_z1 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_z1 (DxfAttdef *attdef, double z1);
double dxf_attdef_get_height (DxfAttdef *attdef);
DxfAttdef * dxf_attdef_set_height (DxfAttdef *attdef, double height);
double dxf_attdef_get_rel_x_scale (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_rel_x_scale (DxfAttdef *attdef, double rel_x_scale);
double dxf_attdef_get_rot_angle (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_rot_angle (DxfAttdef *attdef, double rot_angle);
double dxf_attdef_get_obl_angle (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_obl_angle (DxfAttdef *attdef, double obl_angle);
int16_t dxf_attdef_get_attr_flags (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_attr_flags (DxfAttdef *attdef, int16_t attr_flags);
int dxf_attdef_is_invisible (DxfAttdef *attdef);
int dxf_attdef_is_constant (DxfAttdef *attdef);
int dxf_attdef_is_verification_required (DxfAttdef *attdef);
int dxf_attdef_is_preset (DxfAttdef *attdef);
int16_t dxf_attdef_get_text_flags (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_text_flags (DxfAttdef *attdef, int16_t text_flags);
int16_t dxf_attdef_get_hor_align (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_hor_align (DxfAttdef *attdef, int16_t hor_align);
int16_t dxf_attdef_get_field_length (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_field_length (DxfAttdef *attdef, int16_t field_length);
int16_t dxf_attdef_get_vert_align (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_vert_align (DxfAttdef *attdef, int16_t vert_align);
double dxf_attdef_get_extr_x0 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_extr_x0 (DxfAttdef *attdef, double extr_x0);
double dxf_attdef_get_extr_y0 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_extr_y0 (DxfAttdef *attdef, double extr_y0);
double dxf_attdef_get_extr_z0 (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_extr_z0 (DxfAttdef *attdef, double extr_z0);
DxfPoint *dxf_attdef_get_extrusion_vector_as_point (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_extrusion_vector_from_point (DxfAttdef *attdef, DxfPoint *point);
DxfAttdef *dxf_attdef_set_extrusion_vector (DxfAttdef *attdef, double extr_x0, double extr_y0, double extr_z0);
DxfAttdef *dxf_attdef_get_next (DxfAttdef *attdef);
DxfAttdef *dxf_attdef_set_next (DxfAttdef *attdef, DxfAttdef *next);
DxfAttdef *dxf_attdef_get_last (DxfAttdef *attdef);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_ATTDEF_H */


/* EOF */
