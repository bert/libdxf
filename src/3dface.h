/*!
 * \file 3dface.h
 *
 * \author Copyright (C) 2010, 2012, 2013, 2014, 2015 2016, 2017, 2018,
 * 2019, 2020 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF 3D face entity (\c 3DFACE).
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


#ifndef LIBDXF_SRC_3DFACE_H
#define LIBDXF_SRC_3DFACE_H


#include "global.h"
#include "point.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD 3D face entity (\c 3DFACE).
 */
typedef struct
dxf_3dface_struct
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
        /* Specific members for a DXF 3D face. */
        DxfPoint *p0;
                /*!< Base point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< First alignment point.\n
                 * Group codes = 11, 21 and 31. */
        DxfPoint *p2;
                /*!< Second alignment point.\n
                 * Group codes = 12, 22 and 32. */
        DxfPoint *p3;
                /*!< Third alignment point.\n
                 * Group codes = 13, 23 and 33. */
        int16_t flag;
                /*!< Optional, defaults to 0.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> First edge is invisible.</li>
                 * <li value = "2"> Second edge is invisible.</li>
                 * <li value = "4"> Third edge is invisible.</li>
                 * <li value = "8"> Fourth edge is invisible.</li>
                 * </ol>
                 * Group code = 70. */
        struct Dxf3dface *next;
                /*!< Pointer to the next Dxf3dface.\n
                 * \c NULL in the last Dxf3dface. */
} Dxf3dface;


Dxf3dface *dxf_3dface_new ();
Dxf3dface *dxf_3dface_init (Dxf3dface *face);
Dxf3dface *dxf_3dface_read (DxfFile *fp, Dxf3dface *face);
int dxf_3dface_write (DxfFile *fp, Dxf3dface *face);
Dxf3dface *dxf_3dface_free (Dxf3dface *face);
void dxf_3dface_free_list (Dxf3dface *faces);
int dxf_3dface_get_id_code (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_id_code (Dxf3dface *face, int id_code);
char *dxf_3dface_get_linetype (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_linetype (Dxf3dface *face, char *linetype);
char *dxf_3dface_get_layer (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_layer (Dxf3dface *face, char *layer);
double dxf_3dface_get_elevation (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_elevation (Dxf3dface *face, double elevation);
double dxf_3dface_get_thickness (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_thickness (Dxf3dface *face, double thickness);
double dxf_3dface_get_linetype_scale (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_linetype_scale (Dxf3dface *face, double linetype_scale);
int16_t dxf_3dface_get_visibility (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_visibility (Dxf3dface *face, int16_t visibility);
int16_t dxf_3dface_get_color (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_color (Dxf3dface *face, int16_t color);
int16_t dxf_3dface_get_paperspace (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_paperspace (Dxf3dface *face, int16_t paperspace);
int32_t dxf_3dface_get_graphics_data_size (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_graphics_data_size (Dxf3dface *face, int32_t graphics_data_size);
int16_t dxf_3dface_get_shadow_mode (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_shadow_mode (Dxf3dface *face, int16_t shadow_mode);
DxfBinaryData *dxf_3dface_get_binary_graphics_data (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_binary_graphics_data (Dxf3dface *face, DxfBinaryData *data);
char *dxf_3dface_get_dictionary_owner_soft (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_dictionary_owner_soft (Dxf3dface *face, char *dictionary_owner_soft);
char *dxf_3dface_get_object_owner_soft (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_object_owner_soft (Dxf3dface *face, char *object_owner_soft);
char *dxf_3dface_get_material (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_material (Dxf3dface *face, char *material);
char *dxf_3dface_get_dictionary_owner_hard (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_dictionary_owner_hard (Dxf3dface *face, char *dictionary_owner_hard);
int16_t dxf_3dface_get_lineweight (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_lineweight (Dxf3dface *face, int16_t lineweight);
char *dxf_3dface_get_plot_style_name (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_plot_style_name (Dxf3dface *face, char *plot_style_name);
int32_t dxf_3dface_get_color_value (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_color_value (Dxf3dface *face, int32_t color_value);
char *dxf_3dface_get_color_name (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_color_name (Dxf3dface *face, char *color_name);
int32_t dxf_3dface_get_transparency (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_transparency (Dxf3dface *face, int32_t transparency);
DxfPoint *dxf_3dface_get_p0 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_p0 (Dxf3dface *face, DxfPoint *point);
double dxf_3dface_get_x0 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_x0 (Dxf3dface *face, double x0);
double dxf_3dface_get_y0 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_y0 (Dxf3dface *face, double y0);
double dxf_3dface_get_z0 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_z0 (Dxf3dface *face, double z0);
DxfPoint *dxf_3dface_get_p1 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_p1 (Dxf3dface *face, DxfPoint *point);
double dxf_3dface_get_x1 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_x1 (Dxf3dface *face, double x1);
double dxf_3dface_get_y1 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_y1 (Dxf3dface *face, double y1);
double dxf_3dface_get_z1 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_z1 (Dxf3dface *face, double z1);
DxfPoint *dxf_3dface_get_p2 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_p2 (Dxf3dface *face, DxfPoint *point);
double dxf_3dface_get_x2 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_x2 (Dxf3dface *face, double x2);
double dxf_3dface_get_y2 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_y2 (Dxf3dface *face, double y2);
double dxf_3dface_get_z2 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_z2 (Dxf3dface *face, double z2);
DxfPoint *dxf_3dface_get_p3 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_p3 (Dxf3dface *face, DxfPoint *point);
double dxf_3dface_get_x3 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_x3 (Dxf3dface *face, double x3);
double dxf_3dface_get_y3 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_y3 (Dxf3dface *face, double y3);
double dxf_3dface_get_z3 (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_z3 (Dxf3dface *face, double z3);
int16_t dxf_3dface_get_flag (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_flag (Dxf3dface *face, int16_t flag);
int dxf_3dface_is_first_edge_invisible (Dxf3dface *face);
int dxf_3dface_is_second_edge_invisible (Dxf3dface *face);
int dxf_3dface_is_third_edge_invisible (Dxf3dface *face);
int dxf_3dface_is_fourth_edge_invisible (Dxf3dface *face);
Dxf3dface *dxf_3dface_create_from_points (DxfPoint *p0, DxfPoint *p1, DxfPoint *p2, DxfPoint *p3, int id_code, int inheritance);
Dxf3dface *dxf_3dface_get_next (Dxf3dface *face);
Dxf3dface *dxf_3dface_set_next (Dxf3dface *face, Dxf3dface *next);
Dxf3dface *dxf_3dface_get_last (Dxf3dface *face);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_3DFACE_H */


/* EOF */
