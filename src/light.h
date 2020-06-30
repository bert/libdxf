/*!
 * \file light.h
 *
 * \author Copyright (C) 2018, 2020
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF light entity (\c LIGHT).
 *
 * \since The \c LIGHT entity was introduced in DXF R2007.
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


#ifndef LIBDXF_SRC_LIGHT_H
#define LIBDXF_SRC_LIGHT_H


#include "global.h"
#include "binary_data.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD light entity (\c LIGHT).
 */
typedef struct
dxf_light_struct
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
        /* Specific members for a DXF light. */
        char *light_name;
                /*!< Light name.\n
                 * Group code = 1.*/
        DxfPoint *p0;
                /*!< Light position.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Target location.\n
                 * Group codes = 11, 21 and 31.*/
        double intensity;
                /*!< Intensity.\n
                 * Group code = 40.*/
        double attenuation_start_limit;
                /*!< Attenuation start limit.\n
                 * Group code = 41.*/
        double attenuation_end_limit;
                /*!< Attenuation end limit.\n
                 * Group code = 42.*/
        double hotspot_angle;
                /*!< Hotspot angle.\n
                 * Group code = 50.*/
        double falloff_angle;
                /*!< Falloff angle.\n
                 * Group code = 51.*/
        int16_t light_type;
                /*!< Light type.\n
                 * <ol>
                 *   <li value = 1>Distant.</li>
                 *   <li value = 2>Point.</li>
                 *   <li value = 3>Spot.</li>
                 * </ol>
                 * Group code = 70.*/
        int16_t attenuation_type;
                /*!< Attenuation type.\n
                 * <ol>
                 *   <li value = 0>None.</li>
                 *   <li value = 1>Inverse Linear.</li>
                 *   <li value = 2>Inverse Square.</li>
                 * </ol>
                 * Group code = 72.*/
        int16_t shadow_type;
                /*!< Shadow type.\n
                 * <ol>
                 *   <li value = 0>Ray traced shadows.</li>
                 *   <li value = 1>Shadow maps.</li>
                 * </ol>
                 * Group code = 73.*/
        int32_t version_number;
                /*!< Version number.\n
                 * Group code = 90.*/
        int32_t shadow_map_size;
                /*!< Shadow map size.\n
                 * Group code = 91.*/
        int16_t shadow_map_softness;
                /*!< Shadow map softness.\n
                 * Group code = 280.*/
        int status;
                /*!< Status.\n
                 * Group code = 290.*/
        int plot_glyph;
                /*!< Plot glyph.\n
                 * Group code = 291.*/
        int use_attenuation_limits;
                /*!< Use attenuation limits.\n
                 * Group code = 292.*/
        int cast_shadows;
                /*!< Cast shadows.\n
                 * Group code = 293.*/
        struct DxfLight *next;
                /*!< Pointer to the next DxfLight.\n
                 * \c NULL in the last DxfLight. */
} DxfLight;


DxfLight *dxf_light_new ();
DxfLight *dxf_light_init (DxfLight *light);
DxfLight *dxf_light_read (DxfFile *fp, DxfLight *light);
int dxf_light_write (DxfFile *fp, DxfLight *light);
int dxf_light_free (DxfLight *light);
void dxf_light_free_list (DxfLight *light_list);
int dxf_light_get_id_code (DxfLight *light);
DxfLight *dxf_light_set_id_code (DxfLight *light, int id_code);
char *dxf_light_get_linetype (DxfLight *light);
DxfLight *dxf_light_set_linetype (DxfLight *light, char *linetype);
char *dxf_light_get_layer (DxfLight *light);
DxfLight *dxf_light_set_layer (DxfLight *light, char *layer);
double dxf_light_get_thickness (DxfLight *light);
DxfLight *dxf_light_set_thickness (DxfLight *light, double thickness);
double dxf_light_get_linetype_scale (DxfLight *light);
DxfLight *dxf_light_set_linetype_scale (DxfLight *light, double linetype_scale);
int16_t dxf_light_get_visibility (DxfLight *light);
DxfLight *dxf_light_set_visibility (DxfLight *light, int16_t visibility);
int dxf_light_get_color (DxfLight *light);
DxfLight *dxf_light_set_color (DxfLight *light, int color);
int dxf_light_get_paperspace (DxfLight *light);
DxfLight *dxf_light_set_paperspace (DxfLight *light, int paperspace);
int dxf_light_get_graphics_data_size (DxfLight *light);
DxfLight *dxf_light_set_graphics_data_size (DxfLight *light, int graphics_data_size);
int16_t dxf_light_get_shadow_mode (DxfLight *light);
DxfLight *dxf_light_set_shadow_mode (DxfLight *light, int16_t shadow_mode);
DxfBinaryData *dxf_light_get_binary_graphics_data (DxfLight *light);
DxfLight *dxf_light_set_binary_graphics_data (DxfLight *light, DxfBinaryData *data);
char *dxf_light_get_dictionary_owner_soft (DxfLight *light);
DxfLight *dxf_light_set_dictionary_owner_soft (DxfLight *light, char *dictionary_owner_soft);
char *dxf_light_get_object_owner_soft (DxfLight *light);
DxfLight *dxf_light_set_object_owner_soft (DxfLight *light, char *object_owner_soft);
char *dxf_light_get_material (DxfLight *light);
DxfLight *dxf_light_set_material (DxfLight *light, char *material);
char *dxf_light_get_dictionary_owner_hard (DxfLight *light);
DxfLight *dxf_light_set_dictionary_owner_hard (DxfLight *light, char *dictionary_owner_hard);
int16_t dxf_light_get_lineweight (DxfLight *light);
DxfLight *dxf_light_set_lineweight (DxfLight *light, int16_t lineweight);
char *dxf_light_get_plot_style_name (DxfLight *light);
DxfLight *dxf_light_set_plot_style_name (DxfLight *light, char *plot_style_name);
long dxf_light_get_color_value (DxfLight *light);
DxfLight *dxf_light_set_color_value (DxfLight *light, long color_value);
char *dxf_light_get_color_name (DxfLight *light);
DxfLight *dxf_light_set_color_name (DxfLight *light, char *color_name);
long dxf_light_get_transparency (DxfLight *light);
DxfLight *dxf_light_set_transparency (DxfLight *light, long transparency);
DxfPoint *dxf_light_get_p0 (DxfLight *light);
DxfLight *dxf_light_set_p0 (DxfLight *light, DxfPoint *p0);
double dxf_light_get_x0 (DxfLight *light);
DxfLight *dxf_light_set_x0 (DxfLight *light, double x0);
double dxf_light_get_y0 (DxfLight *light);
DxfLight *dxf_light_set_y0 (DxfLight *light, double y0);
double dxf_light_get_z0 (DxfLight *light);
DxfLight *dxf_light_set_z0 (DxfLight *light, double z0);
DxfPoint *dxf_light_get_p1 (DxfLight *light);
DxfLight *dxf_light_set_p1 (DxfLight *light, DxfPoint *p1);
double dxf_light_get_x1 (DxfLight *light);
DxfLight *dxf_light_set_x1 (DxfLight *light, double x1);
double dxf_light_get_y1 (DxfLight *light);
DxfLight *dxf_light_set_y1 (DxfLight *light, double y1);
double dxf_light_get_z1 (DxfLight *light);
DxfLight *dxf_light_set_z1 (DxfLight *light, double z1);
double dxf_light_get_intensity (DxfLight *light);
DxfLight *dxf_light_set_intensity (DxfLight *light, double intensity);
double dxf_light_get_attenuation_start_limit (DxfLight *light);
DxfLight *dxf_light_set_attenuation_start_limit (DxfLight *light, double attenuation_start_limit);
double dxf_light_get_attenuation_end_limit (DxfLight *light);
DxfLight *dxf_light_set_attenuation_end_limit (DxfLight *light, double attenuation_end_limit);
double dxf_light_get_hotspot_angle (DxfLight *light);
DxfLight *dxf_light_set_hotspot_angle (DxfLight *light, double hotspot_angle);
double dxf_light_get_falloff_angle (DxfLight *light);
DxfLight *dxf_light_set_falloff_angle (DxfLight *light, double falloff_angle);
int16_t dxf_light_get_light_type (DxfLight *light);
DxfLight *dxf_light_set_light_type (DxfLight *light, int16_t light_type);
int16_t dxf_light_get_attenuation_type (DxfLight *light);
DxfLight *dxf_light_set_attenuation_type (DxfLight *light, int16_t attenuation_type);
int16_t dxf_light_get_shadow_type (DxfLight *light);
DxfLight *dxf_light_set_shadow_type (DxfLight *light, int16_t shadow_type);
int16_t dxf_light_get_version_number (DxfLight *light);
DxfLight *dxf_light_set_version_number (DxfLight *light, int16_t version_number);
int16_t dxf_light_get_shadow_map_size (DxfLight *light);
DxfLight *dxf_light_set_shadow_map_size (DxfLight *light, int16_t shadow_map_size);
int16_t dxf_light_get_shadow_map_softness (DxfLight *light);
DxfLight *dxf_light_set_shadow_map_softness (DxfLight *light, int16_t shadow_map_softness);
int dxf_light_get_status (DxfLight *light);
DxfLight *dxf_light_set_status (DxfLight *light, int status);
int dxf_light_get_plot_glyph (DxfLight *light);
DxfLight *dxf_light_set_plot_glyph (DxfLight *light, int plot_glyph);
int dxf_light_get_use_attenuation_limits (DxfLight *light);
DxfLight *dxf_light_set_use_attenuation_limits (DxfLight *light, int use_attenuation_limits);
int dxf_light_get_cast_shadows (DxfLight *light);
DxfLight *dxf_light_set_cast_shadows (DxfLight *light, int cast_shadows);
DxfLight *dxf_light_get_next (DxfLight *light);
DxfLight *dxf_light_set_next (DxfLight *light, DxfLight *next);
DxfLight *dxf_light_get_last (DxfLight *light);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LIGHT_H */


/* EOF */
