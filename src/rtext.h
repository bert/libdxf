/*!
 * \file rtext.h
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF rtext entity (\c RTEXT).
 *
 * \version According to DXF R15.
 * \version According to DXF R2000.
 *
 * \since Introduced in version R15.
 *
 * \deprecated As of version R2002.
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


#ifndef LIBDXF_SRC_RTEXT_H
#define LIBDXF_SRC_RTEXT_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD rtext entity.
 */
typedef struct
dxf_rtext_struct
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
                /*!< Contents.\n
                 * If 1-bit off in type flags, contains external file
                 * name to import.\n
                 * Otherwise contains DIESEL expression.\n
                 * Group code = 1. */
        char *text_style;
                /*!< Optional, defaults to \c STANDARD.\n
                 * Group code = 7. */
        DxfPoint *p0;
                /*!< Insertion point.\n
                 * Group codes = 10, 20 and 30. */
        double height;
                /*!< Text height.\n
                 * Group code = 40. */
        double rot_angle;
                /*!< Text rotation (radians).\n
                 * Group code = 50. */
        int type_flags;
                /*!< Type flags:\n
                 * <ol>
                 * <li value = "1/0"> Expression/file name.</li>
                 * <li value = "2/0"> Inline mtext sequences enabled/disabled.</li>
                 * </ol>
                 * Group code = 70. */
        double extr_x0;
                /*!< X-value of the extrusion direction (optional).\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion direction (optional).\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion direction (optional).\n
                 * Defaults to 1.0 if ommitted in the DXF file.\n
                 * Group code = 230. */
        struct DxfRText *next;
                /*!< Pointer to the next DxfRText.\n
                 * \c NULL in the last DxfRText. */
} DxfRText;


#ifdef __cplusplus
}
#endif


DxfRText *dxf_rtext_new ();
DxfRText *dxf_rtext_init (DxfRText *rtext);
DxfRText *dxf_rtext_read (DxfFile *fp, DxfRText *rtext);
int dxf_rtext_write (DxfFile *fp, DxfRText *rtext);
int dxf_rtext_free (DxfRText *rtext);
void dxf_rtext_free_list (DxfRText *rtexts);
int dxf_rtext_get_id_code (DxfRText *rtext);
DxfRText *dxf_rtext_set_id_code (DxfRText *rtext, int id_code);
char *dxf_rtext_get_linetype (DxfRText *rtext);
DxfRText *dxf_rtext_set_linetype (DxfRText *rtext, char *linetype);
char *dxf_rtext_get_layer (DxfRText *rtext);
DxfRText *dxf_rtext_set_layer (DxfRText *rtext, char *layer);
double dxf_rtext_get_elevation (DxfRText *rtext);
DxfRText *dxf_rtext_set_elevation (DxfRText *rtext, double elevation);
double dxf_rtext_get_thickness (DxfRText *rtext);
DxfRText *dxf_rtext_set_thickness (DxfRText *rtext, double thickness);
double dxf_rtext_get_linetype_scale (DxfRText *rtext);
DxfRText *dxf_rtext_set_linetype_scale (DxfRText *rtext, double linetype_scale);
int16_t dxf_rtext_get_visibility (DxfRText *rtext);
DxfRText *dxf_rtext_set_visibility (DxfRText *rtext, int16_t visibility);
int dxf_rtext_get_color (DxfRText *rtext);
DxfRText *dxf_rtext_set_color (DxfRText *rtext, int color);
int dxf_rtext_get_paperspace (DxfRText *rtext);
DxfRText *dxf_rtext_set_paperspace (DxfRText *rtext, int paperspace);
int dxf_rtext_get_graphics_data_size (DxfRText *rtext);
DxfRText *dxf_rtext_set_graphics_data_size (DxfRText *rtext, int graphics_data_size);
int16_t dxf_rtext_get_shadow_mode (DxfRText *rtext);
DxfRText *dxf_rtext_set_shadow_mode (DxfRText *rtext, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_rtext_get_binary_graphics_data (DxfRText *rtext);
DxfRText *dxf_rtext_set_binary_graphics_data (DxfRText *rtext, DxfBinaryGraphicsData *data);
char *dxf_rtext_get_dictionary_owner_soft (DxfRText *rtext);
DxfRText *dxf_rtext_set_dictionary_owner_soft (DxfRText *rtext, char *dictionary_owner_soft);
char *dxf_rtext_get_material (DxfRText *rtext);
DxfRText *dxf_rtext_set_material (DxfRText *rtext, char *material);
char *dxf_rtext_get_dictionary_owner_hard (DxfRText *rtext);
DxfRText *dxf_rtext_set_dictionary_owner_hard (DxfRText *rtext, char *dictionary_owner_hard);
int16_t dxf_rtext_get_lineweight (DxfRText *rtext);
DxfRText *dxf_rtext_set_lineweight (DxfRText *rtext, int16_t lineweight);
char *dxf_rtext_get_plot_style_name (DxfRText *rtext);
DxfRText *dxf_rtext_set_plot_style_name (DxfRText *rtext, char *plot_style_name);
long dxf_rtext_get_color_value (DxfRText *rtext);
DxfRText *dxf_rtext_set_color_value (DxfRText *rtext, long color_value);
char *dxf_rtext_get_color_name (DxfRText *rtext);
DxfRText *dxf_rtext_set_color_name (DxfRText *rtext, char *color_name);
long dxf_rtext_get_transparency (DxfRText *rtext);
DxfRText *dxf_rtext_set_transparency (DxfRText *rtext, long transparency);
char *dxf_rtext_get_text_value (DxfRText *rtext);
DxfRText *dxf_rtext_set_text_value (DxfRText *rtext, char *text_value);
char *dxf_rtext_get_text_style (DxfRText *rtext);
DxfRText *dxf_rtext_set_text_style (DxfRText *rtext, char *text_style);
DxfPoint *dxf_rtext_get_p0 (DxfRText *rtext);
DxfRText *dxf_rtext_set_p0 (DxfRText *rtext, DxfPoint *p0);
double dxf_rtext_get_x0 (DxfRText *rtext);
DxfRText *dxf_rtext_set_x0 (DxfRText *rtext, double x0);
double dxf_rtext_get_y0 (DxfRText *rtext);
DxfRText *dxf_rtext_set_y0 (DxfRText *rtext, double y0);
double dxf_rtext_get_z0 (DxfRText *rtext);
DxfRText *dxf_rtext_set_z0 (DxfRText *rtext, double z0);
double dxf_rtext_get_height (DxfRText *rtext);
DxfRText *dxf_rtext_set_height (DxfRText *rtext, double height);
double dxf_rtext_get_rot_angle (DxfRText *rtext);
DxfRText *dxf_rtext_set_rot_angle (DxfRText *rtext, double rot_angle);
int dxf_rtext_get_type_flags (DxfRText *rtext);
DxfRText *dxf_rtext_set_type_flags (DxfRText *rtext, int type_flags);
double dxf_rtext_get_extr_x0 (DxfRText *rtext);
DxfRText *dxf_rtext_set_extr_x0 (DxfRText *rtext, double extr_x0);
double dxf_rtext_get_extr_y0 (DxfRText *rtext);
DxfRText *dxf_rtext_set_extr_y0 (DxfRText *rtext, double extr_y0);
double dxf_rtext_get_extr_z0 (DxfRText *rtext);
DxfRText *dxf_rtext_set_extr_z0 (DxfRText *rtext, double extr_z0);
DxfRText *dxf_rtext_set_extrusion_vector_from_point (DxfRText *rtext, DxfPoint *point);
DxfRText *dxf_rtext_set_extrusion_vector (DxfRText *rtext, double extr_x0, double extr_y0, double extr_z0);
DxfRText *dxf_rtext_get_next (DxfRText *rtext);
DxfRText *dxf_rtext_set_next (DxfRText *rtext, DxfRText *next);
DxfRText *dxf_rtext_get_last (DxfRText *rtext);


#endif /* LIBDXF_SRC_RTEXT_H */


/* EOF */
