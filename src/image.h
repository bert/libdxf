/*!
 * \file image.h
 *
 * \author Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF image entity (\c IMAGE).
 *
 * \since The \c IMAGE entity was introduced in DXF R14.
 *
 * \warning The image entity requires AutoCAD version R14 or higher.\n
 *
 * \htmlinclude "image.html"
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
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


#ifndef LIBDXF_SRC_IMAGE_H
#define LIBDXF_SRC_IMAGE_H


#include "global.h"
#include "binary_data.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of an AutoCAD image entity (\c IMAGE).
 */
typedef struct
dxf_image_struct
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
        /* Specific members for a DXF image. */
        DxfPoint *p0;
                /*!< Insertion point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< U-vector of a single pixel (points
                 * along the visual bottom of the image, starting at the
                 * insertion point) (in OCS).\n
                 * Group codes = 11, 21 and 31.*/
        DxfPoint *p2;
                /*!< V-vector of a single pixel (points
                 * along the visual left side of the image, starting at
                 * the insertion point) (in OCS).\n
                 * Group codes = 12, 22 and 32.*/
        DxfPoint *p3;
                /*!< U- and V-value of image size in pixels.\n
                 * Group codes = 13 and 23.*/
        DxfPoint *p4;
                /*!< Rectangular clip boundary type, two opposite
                 * corners must be specified.\n
                 * Default is (-0.5,-0.5), (size.x-0.5, size.y-0.5).\n
                 * For polygonal clip boundary type, three or more
                 * vertices must be specified.\n
                 * Group codes = 14 and 24.\n
                 * \note Polygonal vertices must be listed sequentially.*/
        int16_t image_display_properties;
                /*!< Image display properties.\n
                 * bit coded:\n
                 * <ol>
                 * <li value = "1"> Show image.</li>
                 * <li value = "2"> Show image when not aligned with screen.</li>
                 * <li value = "4"> Use clipping boundary</li>
                 * <li value = "8"> Transparency is on.</li>
                 * </ol>\n
                 * Group code = 70. */
        int16_t clipping_boundary_type;
                /*!< Clipping boundary type.\n
                 * <ol>
                 * <li value = "1"> Rectangular.</li>
                 * <li value = "2"> Polygonal.</li>
                 * </ol>\n
                 * Group code = 71. */
        int32_t class_version;
                /*!< Class version.\n
                 * Group code = 90. */
        int32_t number_of_clip_boundary_vertices;
                /*!< Number of clip boundary vertices that follow.\n
                 * Group code = 91. */
        int16_t clipping_state;
                /*!< Clipping state: 0 = off, 1 = on.\n
                 * Group code = 280. */
        int16_t brightness;
                /*!< Brightness value (0 ... 100; default = 50).\n
                 * Group code = 281. */
        int16_t contrast;
                /*!< Contrast value (0 ... 100; default = 50).\n
                 * Group code = 282. */
        int16_t fade;
                /*!< Fade value (0 ... 100; default = 50).\n
                 * Group code = 283. */
        char *imagedef_object;
                /*!< Hard reference to imagedef object.\n
                 * Group code = 340. */
        char *imagedef_reactor_object;
                /*!< Hard reference to imagedef_reactor object.\n
                 * Group code = 360. */
        struct DxfImage *next;
                /*!< Pointer to the next DxfImage.\n
                 * \c NULL in the last DxfImage. */
} DxfImage;


DxfImage *dxf_image_new ();
DxfImage *dxf_image_init (DxfImage *image);
DxfImage *dxf_image_read (DxfFile *fp, DxfImage *image);
int dxf_image_write (DxfFile *fp, DxfImage *image);
int dxf_image_free (DxfImage *image);
void dxf_image_free_list (DxfImage *images);
int dxf_image_get_id_code (DxfImage *image);
DxfImage *dxf_image_set_id_code (DxfImage *image, int id_code);
char *dxf_image_get_linetype (DxfImage *image);
DxfImage *dxf_image_set_linetype (DxfImage *image, char *linetype);
char *dxf_image_get_layer (DxfImage *image);
DxfImage *dxf_image_set_layer (DxfImage *image, char *layer);
double dxf_image_get_elevation (DxfImage *image);
DxfImage *dxf_image_set_elevation (DxfImage *image, double elevation);
double dxf_image_get_thickness (DxfImage *image);
DxfImage *dxf_image_set_thickness (DxfImage *image, double thickness);
double dxf_image_get_linetype_scale (DxfImage *image);
DxfImage *dxf_image_set_linetype_scale (DxfImage *image, double linetype_scale);
int16_t dxf_image_get_visibility (DxfImage *image);
DxfImage *dxf_image_set_visibility (DxfImage *image, int16_t visibility);
int16_t dxf_image_get_color (DxfImage *image);
DxfImage *dxf_image_set_color (DxfImage *image, int16_t color);
int16_t dxf_image_get_paperspace (DxfImage *image);
DxfImage *dxf_image_set_paperspace (DxfImage *image, int16_t paperspace);
int32_t dxf_image_get_graphics_data_size (DxfImage *image);
DxfImage *dxf_image_set_graphics_data_size (DxfImage *spline, int32_t graphics_data_size);
int16_t dxf_image_get_shadow_mode (DxfImage *image);
DxfImage *dxf_image_set_shadow_mode (DxfImage *image, int16_t shadow_mode);
DxfBinaryData *dxf_image_get_binary_graphics_data (DxfImage *image);
DxfImage *dxf_image_set_binary_graphics_data (DxfImage *image, DxfBinaryData *data);
char *dxf_image_get_dictionary_owner_soft (DxfImage *image);
DxfImage *dxf_image_set_dictionary_owner_soft (DxfImage *image, char *dictionary_owner_soft);
char *dxf_image_get_object_owner_soft (DxfImage *image);
DxfImage *dxf_image_set_object_owner_soft (DxfImage *image, char *object_owner_soft);
char *dxf_image_get_material (DxfImage *image);
DxfImage *dxf_image_set_material (DxfImage *image, char *material);
char *dxf_image_get_dictionary_owner_hard (DxfImage *image);
DxfImage *dxf_image_set_dictionary_owner_hard (DxfImage *image, char *dictionary_owner_hard);
int16_t dxf_image_get_lineweight (DxfImage *image);
DxfImage *dxf_image_set_lineweight (DxfImage *image, int16_t lineweight);
char *dxf_image_get_plot_style_name (DxfImage *image);
DxfImage *dxf_image_set_plot_style_name (DxfImage *image, char *plot_style_name);
int32_t dxf_image_get_color_value (DxfImage *image);
DxfImage *dxf_image_set_color_value (DxfImage *image, int32_t color_value);
char *dxf_image_get_color_name (DxfImage *image);
DxfImage *dxf_image_set_color_name (DxfImage *image, char *color_name);
int32_t dxf_image_get_transparency (DxfImage *image);
DxfImage *dxf_image_set_transparency (DxfImage *image, int32_t transparency);
DxfPoint *dxf_image_get_p0 (DxfImage *image);
DxfImage *dxf_image_set_p0 (DxfImage *image, DxfPoint *p0);
double dxf_image_get_x0 (DxfImage *image);
DxfImage *dxf_image_set_x0 (DxfImage *image, double x0);
double dxf_image_get_y0 (DxfImage *image);
DxfImage *dxf_image_set_y0 (DxfImage *image, double y0);
double dxf_image_get_z0 (DxfImage *image);
DxfImage *dxf_image_set_z0 (DxfImage *image, double z0);
DxfPoint *dxf_image_get_p1 (DxfImage *image);
DxfImage *dxf_image_set_p1 (DxfImage *image, DxfPoint *p1);
double dxf_image_get_x1 (DxfImage *image);
DxfImage *dxf_image_set_x1 (DxfImage *image, double x1);
double dxf_image_get_y1 (DxfImage *image);
DxfImage *dxf_image_set_y1 (DxfImage *image, double y1);
double dxf_image_get_z1 (DxfImage *image);
DxfImage *dxf_image_set_z1 (DxfImage *image, double z1);
DxfPoint *dxf_image_get_p2 (DxfImage *image);
DxfImage *dxf_image_set_p2 (DxfImage *image, DxfPoint *p2);
double dxf_image_get_x2 (DxfImage *image);
DxfImage *dxf_image_set_x2 (DxfImage *image, double x2);
double dxf_image_get_y2 (DxfImage *image);
DxfImage *dxf_image_set_y2 (DxfImage *image, double y2);
double dxf_image_get_z2 (DxfImage *image);
DxfImage *dxf_image_set_z2 (DxfImage *image, double z2);
DxfPoint *dxf_image_get_p3 (DxfImage *image);
DxfImage *dxf_image_set_p3 (DxfImage *image, DxfPoint *p3);
double dxf_image_get_x3 (DxfImage *image);
DxfImage *dxf_image_set_x3 (DxfImage *image, double x3);
double dxf_image_get_y3 (DxfImage *image);
DxfImage *dxf_image_set_y3 (DxfImage *image, double y3);
DxfPoint *dxf_image_get_p4 (DxfImage *image);
DxfImage *dxf_image_set_p4 (DxfImage *image, DxfPoint *p4);
double dxf_image_get_x4 (DxfImage *image);
DxfImage *dxf_image_set_x4 (DxfImage *image, double x4);
double dxf_image_get_y4 (DxfImage *image);
DxfImage *dxf_image_set_y4 (DxfImage *image, double y4);
int16_t dxf_image_get_image_display_properties (DxfImage *image);
DxfImage *dxf_image_set_image_display_properties (DxfImage *image, int16_t image_display_properties);
int16_t dxf_image_get_clipping_boundary_type (DxfImage *image);
DxfImage *dxf_image_set_clipping_boundary_type (DxfImage *image, int16_t clipping_boundary_type);
int32_t dxf_image_get_class_version (DxfImage *image);
DxfImage *dxf_image_set_class_version (DxfImage *image, int32_t class_version);
int32_t dxf_image_get_number_of_clip_boundary_vertices (DxfImage *image);
DxfImage *dxf_image_set_number_of_clip_boundary_vertices (DxfImage *image, int32_t number_of_clip_boundary_vertices);
int16_t dxf_image_get_clipping_state (DxfImage *image);
DxfImage *dxf_image_set_clipping_state (DxfImage *image, int16_t clipping_state);
int16_t dxf_image_get_brightness (DxfImage *image);
DxfImage *dxf_image_set_brightness (DxfImage *image, int16_t brightness);
int16_t dxf_image_get_contrast (DxfImage *image);
DxfImage *dxf_image_set_contrast (DxfImage *image, int16_t contrast);
int16_t dxf_image_get_fade (DxfImage *image);
DxfImage *dxf_image_set_fade (DxfImage *image, int16_t fade);
char *dxf_image_get_imagedef_object (DxfImage *image);
DxfImage *dxf_image_set_imagedef_object (DxfImage *image, char *imagedef_object);
char *dxf_image_get_imagedef_reactor_object (DxfImage *image);
DxfImage *dxf_image_set_imagedef_reactor_object (DxfImage *image, char *imagedef_reactor_object);
DxfImage *dxf_image_get_next (DxfImage *image);
DxfImage *dxf_image_set_next (DxfImage *image, DxfImage *next);
DxfImage *dxf_image_get_last (DxfImage *image);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_IMAGE_H */


/* EOF */
