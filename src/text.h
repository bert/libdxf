/*!
 * \file text.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2012 by Paolo Caroni <kenren89@gmail.com>.
 *
 * \brief Definition of a DXF text entity (\c TEXT).
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


#ifndef LIBDXF_SRC_TEXT_H
#define LIBDXF_SRC_TEXT_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD text entity.
 *
 * DXFOUT handles ASCII control characters in text strings by expanding the
 * character into a ^ (caret) followed by the appropriate letter.\n
 * For example, an ASCII Control-G (BEL, decimal code 7) is output as ^G.\n
 * If the text itself contains a caret character, it is expanded to ^ (caret,
 * space).\n
 * DXFIN performs the complementary conversion.
 */
typedef struct
dxf_text_struct
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
        /* Specific members for a DXF text. */
        char *text_value;
                /*!< Default value (the string itself).\n
                 * Group code = 1. */
        char *text_style;
                /*!< Optional, defaults to \c STANDARD.\n
                 * Group code = 7. */
        DxfPoint *p0;
                /*!< Alignment point.\n
                 * Group codes = 10, 20 and 30. */
        DxfPoint *p1;
                /*!< Second alignment point.\n
                 * This value is meaningful only if the value of a 72 or
                 * 73 group is nonzero (if the justification is anything
                 * other than baseline/left).\n
                 * Group codes = 11, 21 and 31. */
        double height;
                /*!< Text height.\n
                 * Group code = 40. */
        double rel_x_scale;
                /*!< Relative X scale factor-width (optional;
                 * default = 1.0).\n
                 * This value is also adjusted when fit-type text is
                 * used.\n
                 * Group code = 41. */
        double rot_angle;
                /*!< Text rotation (optional; default = 0.0).\n
                 * Group code = 50. */
        double obl_angle;
                /*!< Oblique angle (optional; default = 0.0).\n
                 * Group code = 51. */
        int text_flags;
                /*!< Text generation flags (optional, default = 0).\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "2"> Text is backward (mirrored in X).</li>
                 * <li value = "4"> Text is upside down (mirrored in Y).</li>
                 * </ol>
                 * Group code = 71. */
        int hor_align;
                /*!< Horizontal text justification type (optional,
                 * default = 0) integer codes (not bit-coded)\n
                 * <ol>
                 * <li value = "0"> left.</li>
                 * <li value = "1"> center.</li>
                 * <li value = "2"> right.</li>
                 * <li value = "3"> aligned, only when vert_align = 0.</li>
                 * <li value = "4"> middle, only when vert_align = 0.</li>
                 * <li value = "5"> fit, only when vert_align = 0.</li>
                 * </ol>
                 * Group code = 72. */
        int vert_align;
                /*!< Vertical text justification type (optional,
                 * default = 0): integer codes (not bit-coded)\n
                 * <ol>
                 * <li value = "0"> baseline.</li>
                 * <li value = "1"> bottom.</li>
                 * <li value = "2"> middle.</li>
                 * <li value = "3"> top.</li>
                 * </ol>
                 * Group code = 73. */
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
        struct DxfText *next;
                /*!< Pointer to the next DxfText.\n
                 * \c NULL in the last DxfText. */
} DxfText;


DxfText *dxf_text_new ();
DxfText *dxf_text_init (DxfText *text);
DxfText *dxf_text_read (DxfFile *fp, DxfText *text);
int dxf_text_write (DxfFile *fp, DxfText *text);
int dxf_text_free (DxfText *text);
void dxf_text_free_list (DxfText *texts);
int dxf_text_get_id_code (DxfText *text);
DxfText *dxf_text_set_id_code (DxfText *text, int id_code);
char *dxf_text_get_linetype (DxfText *text);
DxfText *dxf_text_set_linetype (DxfText *text, char *linetype);
char *dxf_text_get_layer (DxfText *text);
DxfText *dxf_text_set_layer (DxfText *text, char *layer);
double dxf_text_get_elevation (DxfText *text);
DxfText *dxf_text_set_elevation (DxfText *text, double elevation);
double dxf_text_get_thickness (DxfText *text);
DxfText *dxf_text_set_thickness (DxfText *text, double thickness);
double dxf_text_get_linetype_scale (DxfText *text);
DxfText *dxf_text_set_linetype_scale (DxfText *text, double linetype_scale);
int16_t dxf_text_get_visibility (DxfText *text);
DxfText *dxf_text_set_visibility (DxfText *text, int16_t visibility);
int dxf_text_get_color (DxfText *text);
DxfText *dxf_text_set_color (DxfText *text, int color);
int dxf_text_get_paperspace (DxfText *text);
DxfText *dxf_text_set_paperspace (DxfText *text, int paperspace);
int dxf_text_get_graphics_data_size (DxfText *text);
DxfText *dxf_text_set_graphics_data_size (DxfText *text, int graphics_data_size);
int16_t dxf_text_get_shadow_mode (DxfText *text);
DxfText *dxf_text_set_shadow_mode (DxfText *text, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_text_get_binary_graphics_data (DxfText *text);
DxfText *dxf_text_set_binary_graphics_data (DxfText *text, DxfBinaryGraphicsData *data);
char *dxf_text_get_dictionary_owner_soft (DxfText *text);
DxfText *dxf_text_set_dictionary_owner_soft (DxfText *text, char *dictionary_owner_soft);
char *dxf_text_get_material (DxfText *text);
DxfText *dxf_text_set_material (DxfText *text, char *material);
char *dxf_text_get_dictionary_owner_hard (DxfText *text);
DxfText *dxf_text_set_dictionary_owner_hard (DxfText *text, char *dictionary_owner_hard);
int16_t dxf_text_get_lineweight (DxfText *text);
DxfText *dxf_text_set_lineweight (DxfText *text, int16_t lineweight);
char *dxf_text_get_plot_style_name (DxfText *text);
DxfText *dxf_text_set_plot_style_name (DxfText *text, char *plot_style_name);
long dxf_text_get_color_value (DxfText *text);
DxfText *dxf_text_set_color_value (DxfText *text, long color_value);
char *dxf_text_get_color_name (DxfText *text);
DxfText *dxf_text_set_color_name (DxfText *text, char *color_name);
long dxf_text_get_transparency (DxfText *text);
DxfText *dxf_text_set_transparency (DxfText *text, long transparency);
char *dxf_text_get_text_value (DxfText *text);
DxfText *dxf_text_set_text_value (DxfText *text, char *text_value);
char *dxf_text_get_text_style (DxfText *text);
DxfText *dxf_text_set_text_style (DxfText *text, char *text_style);
DxfPoint *dxf_text_get_p0 (DxfText *text);
DxfText *dxf_text_set_p0 (DxfText *text, DxfPoint *p0);
double dxf_text_get_x0 (DxfText *text);
DxfText *dxf_text_set_x0 (DxfText *text, double x0);
double dxf_text_get_y0 (DxfText *text);
DxfText *dxf_text_set_y0 (DxfText *text, double y0);
double dxf_text_get_z0 (DxfText *text);
DxfText *dxf_text_set_z0 (DxfText *text, double z0);
DxfPoint *dxf_text_get_p1 (DxfText *text);
DxfText *dxf_text_set_p1 (DxfText *text, DxfPoint *p1);
double dxf_text_get_x1 (DxfText *text);
DxfText *dxf_text_set_x1 (DxfText *text, double x1);
double dxf_text_get_y1 (DxfText *text);
DxfText *dxf_text_set_y1 (DxfText *text, double y1);
double dxf_text_get_z1 (DxfText *text);
DxfText *dxf_text_set_z1 (DxfText *text, double z1);
double dxf_text_get_height (DxfText *text);
DxfText *dxf_text_set_height (DxfText *text, double height);
double dxf_text_get_rel_x_scale (DxfText *text);
DxfText *dxf_text_set_rel_x_scale (DxfText *text, double rel_x_scale);
double dxf_text_get_rot_angle (DxfText *text);
DxfText *dxf_text_set_rot_angle (DxfText *text, double rot_angle);
double dxf_text_get_obl_angle (DxfText *text);
DxfText *dxf_text_set_obl_angle (DxfText *text, double obl_angle);
int dxf_text_get_text_flags (DxfText *text);
DxfText *dxf_text_set_text_flags (DxfText *text, int text_flags);
int dxf_text_get_hor_align (DxfText *text);
DxfText *dxf_text_set_hor_align (DxfText *text, int hor_align);
int dxf_text_get_vert_align (DxfText *text);
DxfText *dxf_text_set_vert_align (DxfText *text, int vert_align);
DxfPoint *dxf_text_get_extrusion_vector_as_point (DxfText *text);
double dxf_text_get_extr_x0 (DxfText *text);
DxfText *dxf_text_set_extr_x0 (DxfText *text, double extr_x0);
double dxf_text_get_extr_y0 (DxfText *text);
DxfText *dxf_text_set_extr_y0 (DxfText *text, double extr_y0);
double dxf_text_get_extr_z0 (DxfText *text);
DxfText *dxf_text_set_extr_z0 (DxfText *text, double extr_z0);
DxfText *dxf_text_set_extrusion_vector_from_point (DxfText *text, DxfPoint *point);
DxfText *dxf_text_set_extrusion_vector (DxfText *text, double extr_x0, double extr_y0, double extr_z0);
DxfText *dxf_text_get_next (DxfText *text);
DxfText *dxf_text_set_next (DxfText *text, DxfText *next);
DxfText *dxf_text_get_last (DxfText *text);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_TEXT_H */


/* EOF */
