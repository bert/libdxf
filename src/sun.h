/*!
 * \file sun.h
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF sun entity (\c SUN).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * \since The \c SUN entity was introduced in DXF R2007.
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


#ifndef LIBDXF_SRC_SUN_H
#define LIBDXF_SRC_SUN_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD sun entity.
 */
typedef struct
dxf_sun_struct
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
        /* Specific members for a DXF sun. */
        double intensity;
                /*!< Intensity.\n
                 * Group code = 40. */
        int sun_color;
                /*!< Color.\n
                 * Group code = 63. */
        int shadow_type;
                /*!< Shadow type:\n
                 * <ol>
                 * <li value = "0"> Ray traced shadows.</li>
                 * <li value = "1"> Shadow maps.</li>
                 * </ol>
                 * Group code = 70. */
        int shadow_map_size;
                /*!< Shadow map size.\n
                 * Group code = 71. */
        int32_t version;
                /*!< Version number.\n
                 * Group code = 90. */
        int32_t julian_day;
                /*!< Julian day.\n
                 * Group code = 91. */
        int32_t time;
                /*!< Time (in seconds past midnight).\n
                 * Group code = 92. */
        int16_t shadow_softness;
                /*!< Shadow softness.\n
                 * Group code = 280.*/
        int status;
                /*!< Status (boolean).\n
                 * Group code = 290. */
        int shadows;
                /*!< Shadows (boolean).\n
                 * Group code = 291. */
        int daylight_savings_time;
                /*!< Daylight savings time (boolean).\n
                 * Group code = 292. */
        struct DxfSun *next;
                /*!< pointer to the next DxfSun.\n
                 * \c NULL in the last DxfSun. */

} DxfSun;


#ifdef __cplusplus
}
#endif


DxfSun *dxf_sun_new ();
DxfSun *dxf_sun_init (DxfSun *sun);
DxfSun *dxf_sun_read (DxfFile *fp, DxfSun *sun);
int dxf_sun_write (DxfFile *fp, DxfSun *sun);
int dxf_sun_free (DxfSun *sun);
void dxf_sun_free_list (DxfSun *suns);
int dxf_sun_get_id_code (DxfSun *sun);
DxfSun *dxf_sun_set_id_code (DxfSun *sun, int id_code);
char *dxf_sun_get_linetype (DxfSun *sun);
DxfSun *dxf_sun_set_linetype (DxfSun *sun, char *linetype);
char *dxf_sun_get_layer (DxfSun *sun);
DxfSun *dxf_sun_set_layer (DxfSun *sun, char *layer);
double dxf_sun_get_elevation (DxfSun *sun);
DxfSun *dxf_sun_set_elevation (DxfSun *sun, double elevation);
double dxf_sun_get_thickness (DxfSun *sun);
DxfSun *dxf_sun_set_thickness (DxfSun *sun, double thickness);
double dxf_sun_get_linetype_scale (DxfSun *sun);
DxfSun *dxf_sun_set_linetype_scale (DxfSun *sun, double linetype_scale);
int16_t dxf_sun_get_visibility (DxfSun *sun);
DxfSun *dxf_sun_set_visibility (DxfSun *sun, int16_t visibility);
int dxf_sun_get_color (DxfSun *sun);
DxfSun *dxf_sun_set_color (DxfSun *sun, int color);
int dxf_sun_get_paperspace (DxfSun *sun);
DxfSun *dxf_sun_set_paperspace (DxfSun *sun, int paperspace);
int dxf_sun_get_graphics_data_size (DxfSun *sun);
DxfSun *dxf_sun_set_graphics_data_size (DxfSun *sun, int graphics_data_size);
int16_t dxf_sun_get_shadow_mode (DxfSun *sun);
DxfSun *dxf_sun_set_shadow_mode (DxfSun *sun, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_sun_get_binary_graphics_data (DxfSun *sun);
DxfSun *dxf_sun_set_binary_graphics_data (DxfSun *sun, DxfBinaryGraphicsData *data);
char *dxf_sun_get_dictionary_owner_soft (DxfSun *sun);
DxfSun *dxf_sun_set_dictionary_owner_soft (DxfSun *sun, char *dictionary_owner_soft);
char *dxf_sun_get_object_owner_soft (DxfSun *sun);
DxfSun *dxf_sun_set_object_owner_soft (DxfSun *sun, char *object_owner_soft);
char *dxf_sun_get_material (DxfSun *sun);
DxfSun *dxf_sun_set_material (DxfSun *sun, char *material);
char *dxf_sun_get_dictionary_owner_hard (DxfSun *sun);
DxfSun *dxf_sun_set_dictionary_owner_hard (DxfSun *sun, char *dictionary_owner_hard);
int16_t dxf_sun_get_lineweight (DxfSun *sun);
DxfSun *dxf_sun_set_lineweight (DxfSun *sun, int16_t lineweight);
char *dxf_sun_get_plot_style_name (DxfSun *sun);
DxfSun *dxf_sun_set_plot_style_name (DxfSun *sun, char *plot_style_name);
long dxf_sun_get_color_value (DxfSun *sun);
DxfSun *dxf_sun_set_color_value (DxfSun *sun, long color_value);
char *dxf_sun_get_color_name (DxfSun *sun);
DxfSun *dxf_sun_set_color_name (DxfSun *sun, char *color_name);
long dxf_sun_get_transparency (DxfSun *sun);
DxfSun *dxf_sun_set_transparency (DxfSun *sun, long transparency);
double dxf_sun_get_intensity (DxfSun *sun);
DxfSun *dxf_sun_set_intensity (DxfSun *sun, double intensity);
int dxf_sun_get_sun_color (DxfSun *sun);
DxfSun *dxf_sun_set_sun_color (DxfSun *sun, int sun_color);
int dxf_sun_get_shadow_type (DxfSun *sun);
DxfSun *dxf_sun_set_shadow_type (DxfSun *sun, int shadow_type);
int dxf_sun_get_shadow_map_size (DxfSun *sun);
DxfSun *dxf_sun_set_shadow_map_size (DxfSun *sun, int shadow_map_size);
int32_t dxf_sun_get_version (DxfSun *sun);
DxfSun *dxf_sun_set_version (DxfSun *sun, int32_t version);
int32_t dxf_sun_get_julian_day (DxfSun *sun);
DxfSun *dxf_sun_set_julian_day (DxfSun *sun, int32_t julian_day);
int32_t dxf_sun_get_time (DxfSun *sun);
DxfSun *dxf_sun_set_time (DxfSun *sun, int32_t time);
int16_t dxf_sun_get_shadow_softness (DxfSun *sun);
DxfSun *dxf_sun_set_shadow_softness (DxfSun *sun, int16_t shadow_softness);
int dxf_sun_get_status (DxfSun *sun);
DxfSun *dxf_sun_set_status (DxfSun *sun, int status);
int dxf_sun_get_shadows (DxfSun *sun);
DxfSun *dxf_sun_set_shadows (DxfSun *sun, int shadows);
int dxf_sun_get_daylight_savings_time (DxfSun *sun);
DxfSun *dxf_sun_set_daylight_savings_time (DxfSun *sun, int daylight_savings_time);
DxfSun *dxf_sun_get_next (DxfSun *sun);
DxfSun *dxf_sun_set_next (DxfSun *sun, DxfSun *next);
DxfSun *dxf_sun_get_last (DxfSun *sun);


#endif /* LIBDXF_SRC_SUN_H */


/* EOF */
