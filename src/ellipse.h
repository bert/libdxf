/*!
 * \file ellipse.h
 *
 * \author Copyright (C) 2008, 2010, 2011, 2012, 2014, 2015, 2016, 2017,
 * 2018, 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF ellipse entity (\c ELLIPSE).
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


#ifndef LIBDXF_SRC_ELLIPSE_H
#define LIBDXF_SRC_ELLIPSE_H


#include "global.h"
#include "point.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of an AutoCAD ellipse entity (\c ELLIPSE).
 *
 * This entity requires AutoCAD version R14 or higher.
 */
typedef struct
dxf_ellipse_struct
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
        /* Specific members for a DXF ellipse. */
        DxfPoint *p0;
                /*!< Center point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Endpoint of major axis, relative to the center (in
                 * WCS).\n
                 * Group codes = 11, 21 and 31. */
        double x0;
                /*!< X value of the center point.\n
                 * Group code = 10. */
        double y0;
                /*!< Y value of the center point.\n
                 * Group code = 20. */
        double z0;
                /*!< Z value of the center point.\n
                 * Group code = 30. */
        double x1;
                /*!< X value of the endpoint of major axis, relative to
                 * the center (in WCS).\n
                 * Group code = 11. */
        double y1;
                /*!< Y value of the endpoint of major axis, relative to
                 * the center (in WCS).\n
                 * Group code = 21. */
        double z1;
                /*!< Z value of the endpoint of major axis, relative to
                 * the center (in WCS).\n
                 * Group code = 31. */
        double ratio;
                /*!< Ratio of minor axis to major axis.\n
                 * Group code = 40. */
        double start_angle;
                /*!< Group code = 41. */
        double end_angle;
                /*!< Group code = 42. */
        double extr_x0;
                /*!< X value of the extrusion direction.\n
                 * Optional, if ommited defaults to 0.0.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y value of the extrusion direction.\n
                 * Optional, if ommited defaults to 0.0.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z value of the extrusion direction.\n
                 * Optional, if ommited defaults to 1.0.\n
                 * Group code = 230. */
        struct DxfEllipse *next;
                /*!< pointer to the next DxfEllipse.\n
                 * \c NULL in the last DxfEllipse. */
} DxfEllipse;


DxfEllipse *dxf_ellipse_new ();
DxfEllipse *dxf_ellipse_init (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_read (DxfFile *fp, DxfEllipse *ellipse);
int dxf_ellipse_write (DxfFile *fp, DxfEllipse *ellipse);
int dxf_ellipse_free (DxfEllipse *ellipse);
void dxf_ellipse_free_list (DxfEllipse *ellipses);
int dxf_ellipse_get_id_code (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_id_code (DxfEllipse *ellipse, int id_code);
char *dxf_ellipse_get_linetype (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_linetype (DxfEllipse *ellipse, char *linetype);
char *dxf_ellipse_get_layer (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_layer (DxfEllipse *ellipse, char *layer);
double dxf_ellipse_get_elevation (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_elevation (DxfEllipse *ellipse, double elevation);
double dxf_ellipse_get_thickness (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_thickness (DxfEllipse *ellipse, double thickness);
double dxf_ellipse_get_linetype_scale (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_linetype_scale (DxfEllipse *ellipse, double linetype_scale);
int16_t dxf_ellipse_get_visibility (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_visibility (DxfEllipse *ellipse, int16_t visibility);
int16_t dxf_ellipse_get_color (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_color (DxfEllipse *ellipse, int16_t color);
int16_t dxf_ellipse_get_paperspace (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_paperspace (DxfEllipse *ellipse, int16_t paperspace);
int32_t dxf_ellipse_get_graphics_data_size (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_graphics_data_size (DxfEllipse *ellipse, int32_t graphics_data_size);
int16_t dxf_ellipse_get_shadow_mode (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_shadow_mode (DxfEllipse *ellipse, int16_t shadow_mode);
DxfBinaryData *dxf_ellipse_get_binary_graphics_data (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_binary_graphics_data (DxfEllipse *ellipse, DxfBinaryData *data);
char *dxf_ellipse_get_dictionary_owner_soft (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_dictionary_owner_soft (DxfEllipse *ellipse, char *dictionary_owner_soft);
char *dxf_ellipse_get_object_owner_soft (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_object_owner_soft (DxfEllipse *ellipse, char *object_owner_soft);
char *dxf_ellipse_get_material (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_material (DxfEllipse *ellipse, char *material);
char *dxf_ellipse_get_dictionary_owner_hard (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_dictionary_owner_hard (DxfEllipse *ellipse, char *dictionary_owner_hard);
int16_t dxf_ellipse_get_lineweight (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_lineweight (DxfEllipse *ellipse, int16_t lineweight);
char *dxf_ellipse_get_plot_style_name (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_plot_style_name (DxfEllipse *ellipse, char *plot_style_name);
int32_t dxf_ellipse_get_color_value (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_color_value (DxfEllipse *ellipse, int32_t color_value);
char *dxf_ellipse_get_color_name (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_color_name (DxfEllipse *ellipse, char *color_name);
int32_t dxf_ellipse_get_transparency (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_transparency (DxfEllipse *ellipse, int32_t transparency);
DxfPoint *dxf_ellipse_get_p0 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_p0 (DxfEllipse *ellipse, DxfPoint *p0);
double dxf_ellipse_get_x0 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_x0 (DxfEllipse *ellipse, double x0);
double dxf_ellipse_get_y0 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_y0 (DxfEllipse *ellipse, double y0);
double dxf_ellipse_get_z0 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_z0 (DxfEllipse *ellipse, double z0);
DxfPoint *dxf_ellipse_get_p1 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_p1 (DxfEllipse *ellipse, DxfPoint *p1);
double dxf_ellipse_get_x1 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_x1 (DxfEllipse *ellipse, double x1);
double dxf_ellipse_get_y1 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_y1 (DxfEllipse *ellipse, double y1);
double dxf_ellipse_get_z1 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_z1 (DxfEllipse *ellipse, double z1);
double dxf_ellipse_get_ratio (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_ratio (DxfEllipse *ellipse, double ratio);
double dxf_ellipse_get_start_angle (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_start_angle (DxfEllipse *ellipse, double start_angle);
double dxf_ellipse_get_end_angle (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_end_angle (DxfEllipse *ellipse, double end_angle);
double dxf_ellipse_get_extr_x0 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_extr_x0 (DxfEllipse *ellipse, double extr_x0);
double dxf_ellipse_get_extr_y0 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_extr_y0 (DxfEllipse *ellipse, double extr_y0);
double dxf_ellipse_get_extr_z0 (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_extr_z0 (DxfEllipse *ellipse, double extr_z0);
DxfPoint *dxf_ellipse_get_extrusion_vector_as_point (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_extrusion_vector_from_point (DxfEllipse *ellipse, DxfPoint *point);
DxfEllipse *dxf_ellipse_set_extrusion_vector (DxfEllipse *ellipse, double extr_x0, double extr_y0, double extr_z0);
DxfEllipse *dxf_ellipse_get_next (DxfEllipse *ellipse);
DxfEllipse *dxf_ellipse_set_next (DxfEllipse *ellipse, DxfEllipse *next);
DxfEllipse *dxf_ellipse_get_last (DxfEllipse *ellipse);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_ELLIPSE_H */


/* EOF */
