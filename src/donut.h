/*!
 * \file donut.h
 *
 * \author Copyright (C) 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018,
 * 2020 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a libDXF donut entity.
 *
 * \warning This is not an official AutoCAD entity.
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


#ifndef LIBDXF_SRC_DONUT_H
#define LIBDXF_SRC_DONUT_H


#include "global.h"
#include "point.h"
#include "binary_data.h"
#include "polyline.h"
#include "vertex.h"
#include "seqend.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of a libDXF donut entity.
 *
 * A libDXF donut is a typical convenience struct.
 *
 * \warning This is not an official AutoCAD entity.
 */
typedef struct
dxf_donut_struct
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
                /*!< Thickness of the arc in the local Z-direction.\n
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
        /* Specific members for a libDXF donut. */
        DxfPoint *p0;
                /*!< Insertion point for the center of the donut.\n
                 * Group codes = 10, 20 and 30.*/
        double outside_diameter;
                /*!< Outside diameter. */
        double inside_diameter;
                /*!< Inside diameter. */
        struct DxfDonut *next;
                /*!< Pointer to the next DxfDonut.\n
                 * \c NULL in the last DxfDonut. */
} DxfDonut;


DxfDonut *dxf_donut_new ();
DxfDonut *dxf_donut_init (DxfDonut *donut);
int dxf_donut_write (DxfFile *fp, DxfDonut *donut);
int dxf_donut_free (DxfDonut *donut);
void dxf_donut_free_list (DxfDonut *donuts);
int dxf_donut_get_id_code (DxfDonut *donut);
DxfDonut *dxf_donut_set_id_code (DxfDonut *donut, int id_code);
char *dxf_donut_get_linetype (DxfDonut *donut);
DxfDonut *dxf_donut_set_linetype (DxfDonut *donut, char *linetype);
char *dxf_donut_get_layer (DxfDonut *donut);
DxfDonut *dxf_donut_set_layer (DxfDonut *donut, char *layer);
double dxf_donut_get_elevation (DxfDonut *donut);
DxfDonut *dxf_donut_set_elevation (DxfDonut *donut, double elevation);
double dxf_donut_get_thickness (DxfDonut *donut);
DxfDonut *dxf_donut_set_thickness (DxfDonut *donut, double thickness);
double dxf_donut_get_linetype_scale (DxfDonut *donut);
DxfDonut *dxf_donut_set_linetype_scale (DxfDonut *donut, double linetype_scale);
int16_t dxf_donut_get_visibility (DxfDonut *donut);
DxfDonut *dxf_donut_set_visibility (DxfDonut *donut, int16_t visibility);
int16_t dxf_donut_get_color (DxfDonut *donut);
DxfDonut *dxf_donut_set_color (DxfDonut *donut, int16_t color);
int16_t dxf_donut_get_paperspace (DxfDonut *donut);
DxfDonut *dxf_donut_set_paperspace (DxfDonut *donut, int16_t paperspace);
int32_t dxf_donut_get_graphics_data_size (DxfDonut *donut);
DxfDonut *dxf_donut_set_graphics_data_size (DxfDonut *donut, int32_t graphics_data_size);
int16_t dxf_donut_get_shadow_mode (DxfDonut *donut);
DxfDonut *dxf_donut_set_shadow_mode (DxfDonut *donut, int16_t shadow_mode);
DxfBinaryData *dxf_donut_get_binary_graphics_data (DxfDonut *donut);
DxfDonut *dxf_donut_set_binary_graphics_data (DxfDonut *donut, DxfBinaryData *data);
char *dxf_donut_get_dictionary_owner_soft (DxfDonut *donut);
DxfDonut *dxf_donut_set_dictionary_owner_soft (DxfDonut *donut, char *dictionary_owner_soft);
char *dxf_donut_get_material (DxfDonut *donut);
DxfDonut *dxf_donut_set_material (DxfDonut *donut, char *material);
char *dxf_donut_get_dictionary_owner_hard (DxfDonut *donut);
DxfDonut *dxf_donut_set_dictionary_owner_hard (DxfDonut *donut, char *dictionary_owner_hard);
int16_t dxf_donut_get_lineweight (DxfDonut *donut);
DxfDonut *dxf_donut_set_lineweight (DxfDonut *donut, int16_t lineweight);
char *dxf_donut_get_plot_style_name (DxfDonut *donut);
DxfDonut *dxf_donut_set_plot_style_name (DxfDonut *donut, char *plot_style_name);
int32_t dxf_donut_get_color_value (DxfDonut *donut);
DxfDonut *dxf_donut_set_color_value (DxfDonut *donut, int32_t color_value);
char *dxf_donut_get_color_name (DxfDonut *donut);
DxfDonut *dxf_donut_set_color_name (DxfDonut *donut, char *color_name);
int32_t dxf_donut_get_transparency (DxfDonut *donut);
DxfDonut *dxf_donut_set_transparency (DxfDonut *donut, int32_t transparency);
DxfPoint *dxf_donut_get_p0 (DxfDonut *donut);
DxfDonut *dxf_donut_set_p0 (DxfDonut *donut, DxfPoint *p0);
double dxf_donut_get_x0 (DxfDonut *donut);
DxfDonut *dxf_donut_set_x0 (DxfDonut *donut, double x0);
double dxf_donut_get_y0 (DxfDonut *donut);
DxfDonut *dxf_donut_set_y0 (DxfDonut *donut, double y0);
double dxf_donut_get_z0 (DxfDonut *donut);
DxfDonut *dxf_donut_set_z0 (DxfDonut *donut, double z0);
double dxf_donut_get_outside_diameter (DxfDonut *donut);
DxfDonut *dxf_donut_set_outside_diameter (DxfDonut *donut, double outside_diameter);
double dxf_donut_get_inside_diameter (DxfDonut *donut);
DxfDonut *dxf_donut_set_inside_diameter (DxfDonut *donut, double inside_diameter);
DxfDonut *dxf_donut_get_next (DxfDonut *donut);
DxfDonut *dxf_donut_set_next (DxfDonut *donut, DxfDonut *next);
DxfDonut *dxf_donut_get_last (DxfDonut *donut);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_DONUT_H */


/* EOF */
