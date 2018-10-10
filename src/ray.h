/*!
 * \file ray.h
 *
 * \author Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF ray entity (\c RAY).
 *
 * \since The ray entity was introduced in DXF version R13.\n
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_RAY_H
#define LIBDXF_SRC_RAY_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD ray entity (\c RAY).
 */
typedef struct
dxf_ray_struct
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
        /* Specific members for a DXF ray. */
        DxfPoint *p0;
                /*!< Start point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< End point.\n
                 * Group codes = 11, 21 and 31.*/
        struct DxfRay *next;
                /*!< pointer to the next DxfRay.\n
                 * \c NULL in the last DxfRay. */
} DxfRay;


DxfRay *dxf_ray_new ();
DxfRay *dxf_ray_init (DxfRay *ray);
DxfRay *dxf_ray_read (DxfFile *fp, DxfRay *ray);
int dxf_ray_write (DxfFile *fp, DxfRay *ray);
int dxf_ray_free (DxfRay *ray);
void dxf_ray_free_list (DxfRay *rays);
int dxf_ray_get_id_code (DxfRay *ray);
DxfRay *dxf_ray_set_id_code (DxfRay *ray, int id_code);
char *dxf_ray_get_linetype (DxfRay *ray);
DxfRay *dxf_ray_set_linetype (DxfRay *ray, char *linetype);
char *dxf_ray_get_layer (DxfRay *ray);
DxfRay *dxf_ray_set_layer (DxfRay *ray, char *layer);
double dxf_ray_get_elevation (DxfRay *ray);
DxfRay *dxf_ray_set_elevation (DxfRay *ray, double elevation);
double dxf_ray_get_thickness (DxfRay *ray);
DxfRay *dxf_ray_set_thickness (DxfRay *ray, double thickness);
double dxf_ray_get_linetype_scale (DxfRay *ray);
DxfRay *dxf_ray_set_linetype_scale (DxfRay *ray, double linetype_scale);
int16_t dxf_ray_get_visibility (DxfRay *ray);
DxfRay *dxf_ray_set_visibility (DxfRay *ray, int16_t visibility);
int dxf_ray_get_color (DxfRay *ray);
DxfRay *dxf_ray_set_color (DxfRay *ray, int color);
int dxf_ray_get_paperspace (DxfRay *ray);
DxfRay *dxf_ray_set_paperspace (DxfRay *ray, int paperspace);
int dxf_ray_get_graphics_data_size (DxfRay *ray);
DxfRay *dxf_ray_set_graphics_data_size (DxfRay *ray, int graphics_data_size);
int16_t dxf_ray_get_shadow_mode (DxfRay *ray);
DxfRay *dxf_ray_set_shadow_mode (DxfRay *ray, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_ray_get_binary_graphics_data (DxfRay *ray);
DxfRay *dxf_ray_set_binary_graphics_data (DxfRay *ray, DxfBinaryGraphicsData *data);
char *dxf_ray_get_dictionary_owner_soft (DxfRay *ray);
DxfRay *dxf_ray_set_dictionary_owner_soft (DxfRay *ray, char *dictionary_owner_soft);
char *dxf_ray_get_material (DxfRay *ray);
DxfRay *dxf_ray_set_material (DxfRay *ray, char *material);
char *dxf_ray_get_dictionary_owner_hard (DxfRay *ray);
DxfRay *dxf_ray_set_dictionary_owner_hard (DxfRay *ray, char *dictionary_owner_hard);
int16_t dxf_ray_get_lineweight (DxfRay *ray);
DxfRay *dxf_ray_set_lineweight (DxfRay *ray, int16_t lineweight);
char *dxf_ray_get_plot_style_name (DxfRay *ray);
DxfRay *dxf_ray_set_plot_style_name (DxfRay *ray, char *plot_style_name);
long dxf_ray_get_color_value (DxfRay *ray);
DxfRay *dxf_ray_set_color_value (DxfRay *ray, long color_value);
char *dxf_ray_get_color_name (DxfRay *ray);
DxfRay *dxf_ray_set_color_name (DxfRay *ray, char *color_name);
long dxf_ray_get_transparency (DxfRay *ray);
DxfRay *dxf_ray_set_transparency (DxfRay *ray, long transparency);
DxfPoint *dxf_ray_get_p0 (DxfRay *ray);
DxfRay *dxf_ray_set_p0 (DxfRay *ray, DxfPoint *p0);
double dxf_ray_get_x0 (DxfRay *ray);
DxfRay *dxf_ray_set_x0 (DxfRay *ray, double x0);
double dxf_ray_get_y0 (DxfRay *ray);
DxfRay *dxf_ray_set_y0 (DxfRay *ray, double y0);
double dxf_ray_get_z0 (DxfRay *ray);
DxfRay *dxf_ray_set_z0 (DxfRay *ray, double z0);
DxfPoint *dxf_ray_get_p1 (DxfRay *ray);
DxfRay *dxf_ray_set_p1 (DxfRay *ray, DxfPoint *p1);
double dxf_ray_get_x1 (DxfRay *ray);
DxfRay *dxf_ray_set_x1 (DxfRay *ray, double x1);
double dxf_ray_get_y1 (DxfRay *ray);
DxfRay *dxf_ray_set_y1 (DxfRay *ray, double y1);
double dxf_ray_get_z1 (DxfRay *ray);
DxfRay *dxf_ray_set_z1 (DxfRay *ray, double z1);
DxfRay *dxf_ray_get_next (DxfRay *ray);
DxfRay *dxf_ray_set_next (DxfRay *ray, DxfRay *next);
DxfRay *dxf_ray_get_last (DxfRay *ray);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_RAY_H */


/* EOF */
