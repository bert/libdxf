/*!
 * \file region.h
 *
 * \author Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF region entity (\c REGION).
 *
 * \since The region entity was introduced in DXF version R13.\n
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


#ifndef LIBDXF_SRC_REGION_H
#define LIBDXF_SRC_REGION_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"
#include "util.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD region entity (\c REGION).
 */
typedef struct
dxf_region_struct
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
        /* Specific members for a DXF region. */
        DxfChar *proprietary_data;
                /*!< Proprietary data (multiple lines < 255 characters
                 * each).\n
                 * Group code = 1. */
        DxfChar *additional_proprietary_data;
                /*!< Additional lines of proprietary data if previous
                 * group 1 string is greater than 255 characters
                 * (optional).\n
                 * Group code = 3. */
        int modeler_format_version_number;
                /*!< Modeler format version number (currently = 1).\n
                 * Group code = 70. */
        struct DxfRegion *next;
                /*!< pointer to the next DxfRegion.\n
                 * \c NULL in the last DxfRegion. */
} DxfRegion;


DxfRegion *dxf_region_new ();
DxfRegion *dxf_region_init (DxfRegion *region);
DxfRegion *dxf_region_read (DxfFile *fp, DxfRegion *region);
int dxf_region_write (DxfFile *fp, DxfRegion *region);
int dxf_region_free (DxfRegion *region);
void dxf_region_free_list (DxfRegion *regions);
int dxf_region_get_id_code (DxfRegion *region);
DxfRegion *dxf_region_set_id_code (DxfRegion *region, int id_code);
char *dxf_region_get_linetype (DxfRegion *region);
DxfRegion *dxf_region_set_linetype (DxfRegion *region, char *linetype);
char *dxf_region_get_layer (DxfRegion *region);
DxfRegion *dxf_region_set_layer (DxfRegion *region, char *layer);
double dxf_region_get_elevation (DxfRegion *region);
DxfRegion *dxf_region_set_elevation (DxfRegion *region, double elevation);
double dxf_region_get_thickness (DxfRegion *region);
DxfRegion *dxf_region_set_thickness (DxfRegion *region, double thickness);
double dxf_region_get_linetype_scale (DxfRegion *region);
DxfRegion *dxf_region_set_linetype_scale (DxfRegion *region, double linetype_scale);
int16_t dxf_region_get_visibility (DxfRegion *region);
DxfRegion *dxf_region_set_visibility (DxfRegion *region, int16_t visibility);
int dxf_region_get_color (DxfRegion *region);
DxfRegion *dxf_region_set_color (DxfRegion *region, int color);
int dxf_region_get_paperspace (DxfRegion *region);
DxfRegion *dxf_region_set_paperspace (DxfRegion *region, int paperspace);
int dxf_region_get_graphics_data_size (DxfRegion *region);
DxfRegion *dxf_region_set_graphics_data_size (DxfRegion *region, int graphics_data_size);
int16_t dxf_region_get_shadow_mode (DxfRegion *region);
DxfRegion *dxf_region_set_shadow_mode (DxfRegion *region, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_region_get_binary_graphics_data (DxfRegion *region);
DxfRegion *dxf_region_set_binary_graphics_data (DxfRegion *region, DxfBinaryGraphicsData *data);
char *dxf_region_get_dictionary_owner_soft (DxfRegion *region);
DxfRegion *dxf_region_set_dictionary_owner_soft (DxfRegion *region, char *dictionary_owner_soft);
char *dxf_region_get_material (DxfRegion *region);
DxfRegion *dxf_region_set_material (DxfRegion *region, char *material);
char *dxf_region_get_dictionary_owner_hard (DxfRegion *region);
DxfRegion *dxf_region_set_dictionary_owner_hard (DxfRegion *region, char *dictionary_owner_hard);
int16_t dxf_region_get_lineweight (DxfRegion *region);
DxfRegion *dxf_region_set_lineweight (DxfRegion *region, int16_t lineweight);
char *dxf_region_get_plot_style_name (DxfRegion *region);
DxfRegion *dxf_region_set_plot_style_name (DxfRegion *region, char *plot_style_name);
long dxf_region_get_color_value (DxfRegion *region);
DxfRegion *dxf_region_set_color_value (DxfRegion *region, long color_value);
char *dxf_region_get_color_name (DxfRegion *region);
DxfRegion *dxf_region_set_color_name (DxfRegion *region, char *color_name);
long dxf_region_get_transparency (DxfRegion *region);
DxfRegion *dxf_region_set_transparency (DxfRegion *region, long transparency);
DxfChar *dxf_region_get_proprietary_data (DxfRegion *region);
DxfRegion *dxf_region_set_proprietary_data (DxfRegion *region, DxfChar *proprietary_data);
DxfChar *dxf_region_get_additional_proprietary_data (DxfRegion *region);
DxfRegion *dxf_region_set_additional_proprietary_data (DxfRegion *region, DxfChar *additional_proprietary_data);
int dxf_region_get_modeler_format_version_number (DxfRegion *region);
DxfRegion *dxf_region_set_modeler_format_version_number (DxfRegion *region, int modeler_format_version_number);
DxfRegion *dxf_region_get_next (DxfRegion *region);
DxfRegion *dxf_region_set_next (DxfRegion *region, DxfRegion *next);
DxfRegion *dxf_region_get_last (DxfRegion *region);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_REGION_H */


/* EOF */
