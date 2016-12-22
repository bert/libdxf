/*!
 * \file image.h
 *
 * \author Copyright (C) 2013 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF image entity (\c IMAGE).
 *
 * \warning The image entity requires AutoCAD version R14 or higher.\n
 *
 * \htmlinclude "image.html"
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
#include "binary_graphics_data.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of an AutoCAD image entity (\c IMAGE).
 *
 * \version According to DXF R14.
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
                 * Group code = 60. */
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
                 * Group code = 67. */
        int graphics_data_size;
                /*!< Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).\n
                 * Group code = 92. */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284. */
        DxfBinaryGraphicsData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390. */
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
                 * Group code = 420. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430. */
        long transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440. */
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
                 * Default is (-0.5,-0.5), (size.x-0.5, size.y-0.5).</li>
                 * <li>For polygonal clip boundary type, three or more
                 * vertices must be specified.\n
                 * Polygonal vertices must be listed sequentially.</li>
                 * </ul>\n
                 * Group codes = 14 and 24.*/
        double x0;
                /*!< X-value of the insertion point coordinate.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the insertion point coordinate.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the insertion point coordinate.\n
                 * Group code = 30. */
        double x1;
                /*!< X-value of the U-vector of a single pixel (points
                 * along the visual bottom of the image, starting at the
                 * insertion point) (in OCS).\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of the U-vector of a single pixel (points
                 * along the visual bottom of the image, starting at the
                 * insertion point) (in OCS).\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of the U-vector of a single pixel (points
                 * along the visual bottom of the image, starting at the
                 * insertion point) (in OCS).\n
                 * Group code = 31. */
        double x2;
                /*!< X-value of the V-vector of a single pixel (points
                 * along the visual left side of the image, starting at
                 * the insertion point) (in OCS).\n
                 * Group code = 12. */
        double y2;
                /*!< Y-value of the V-vector of a single pixel (points
                 * along the visual left side of the image, starting at
                 * the insertion point) (in OCS).\n
                 * Group code = 22. */
        double z2;
                /*!< Z-value of the V-vector of a single pixel (points
                 * along the visual left side of the image, starting at
                 * the insertion point) (in OCS).\n
                 * Group code = 32. */
        double x3;
                /*!< U-value of image size in pixels.\n
                 * Group code = 13. */
        double y3;
                /*!< V-value of image size in pixels.\n
                 * Group code = 23. */
        double x4[DXF_MAX_PARAM];
                /*!< X-value of clip boundary vertex (in OCS) (multiple
                 * entries).\n
                 * Notes:\n
                 * <ul>
                 * <li>For rectangular clip boundary type, two opposite
                 * corners must be specified.\n
                 * Default is (-0.5,-0.5), (size.x-0.5, size.y-0.5).</li>
                 * <li>For polygonal clip boundary type, three or more
                 * vertices must be specified.\n
                 * Polygonal vertices must be listed sequentially.</li>
                 * </ul>\n
                 * Group code = 14. */
        double y4[DXF_MAX_PARAM];
                /*!< Y-value of clip boundary vertex (in OCS) (multiple
                 * entries).\n
                 * Notes:\n
                 * <ul>
                 * <li>For rectangular clip boundary type, two opposite
                 * corners must be specified.\n
                 * Default is (-0.5,-0.5), (size.x-0.5, size.y-0.5).</li>
                 * <li>For polygonal clip boundary type, three or more
                 * vertices must be specified.\n
                 * Polygonal vertices must be listed sequentially.</li>
                 * </ul>\n
                 * Group code = 24. */
        int image_display_properties;
                /*!< Image display properties.\n
                 * bit coded:\n
                 * <ol>
                 * <li value = "1"> Show image.</li>
                 * <li value = "2"> Show image when not aligned with screen.</li>
                 * <li value = "4"> Use clipping boundary</li>
                 * <li value = "8"> Transparency is on.</li>
                 * </ol>\n
                 * Group code = 70. */
        int clipping_boundary_type;
                /*!< Clipping boundary type.\n
                 * <ol>
                 * <li value = "1"> Rectangular.</li>
                 * <li value = "2"> Polygonal.</li>
                 * </ol>\n
                 * Group code = 71. */
        long class_version;
                /*!< Class version.\n
                 * Group code = 90. */
        long number_of_clip_boundary_vertices;
                /*!< Number of clip boundary vertices that follow.\n
                 * Group code = 91. */
        int clipping_state;
                /*!< Clipping state: 0 = off, 1 = on.\n
                 * Group code = 280. */
        int brightness;
                /*!< Brightness value (0 ... 100; default = 50).\n
                 * Group code = 281. */
        int contrast;
                /*!< Contrast value (0 ... 100; default = 50).\n
                 * Group code = 282. */
        int fade;
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


DxfImage *
dxf_image_new ();
DxfImage *
dxf_image_init
(
        DxfImage *image
);
DxfImage *
dxf_image_read
(
        DxfFile *fp,
        DxfImage *image
);
int
dxf_image_write
(
        DxfFile *fp,
        DxfImage *image
);
int
dxf_image_free
(
        DxfImage *image
);
void
dxf_image_free_chain
(
        DxfImage *images
);
int
dxf_image_get_id_code
(
        DxfImage *image
);
DxfImage *
dxf_image_set_id_code
(
        DxfImage *image,
        int id_code
);
char *
dxf_image_get_linetype
(
        DxfImage *image
);
DxfImage *
dxf_image_set_linetype
(
        DxfImage *image,
        char *linetype
);
char *
dxf_image_get_layer
(
        DxfImage *image
);
DxfImage *
dxf_image_set_layer
(
        DxfImage *image,
        char *layer
);
double
dxf_image_get_elevation
(
        DxfImage *image
);
DxfImage *
dxf_image_set_elevation
(
        DxfImage *image,
        double elevation
);
double
dxf_image_get_thickness
(
        DxfImage *image
);
DxfImage *
dxf_image_set_thickness
(
        DxfImage *image,
        double thickness
);
double
dxf_image_get_linetype_scale
(
        DxfImage *image
);
DxfImage *
dxf_image_set_linetype_scale
(
        DxfImage *image,
        double linetype_scale
);
int16_t
dxf_image_get_visibility
(
        DxfImage *image
);
DxfImage *
dxf_image_set_visibility
(
        DxfImage *image,
        int16_t visibility
);
int
dxf_image_get_color
(
        DxfImage *image
);
DxfImage *
dxf_image_set_color
(
        DxfImage *image,
        int color
);
int
dxf_image_get_paperspace
(
        DxfImage *image
);
DxfImage *
dxf_image_set_paperspace
(
        DxfImage *image,
        int paperspace
);
int
dxf_image_get_graphics_data_size
(
        DxfImage *image
);
DxfImage *
dxf_image_set_graphics_data_size
(
        DxfImage *spline,
        int graphics_data_size
);
int16_t
dxf_image_get_shadow_mode
(
        DxfImage *image
);
DxfImage *
dxf_image_set_shadow_mode
(
        DxfImage *image,
        int16_t shadow_mode
);
DxfBinaryGraphicsData *
dxf_image_get_binary_graphics_data
(
        DxfImage *image
);
DxfImage *
dxf_image_set_binary_graphics_data
(
        DxfImage *image,
        DxfBinaryGraphicsData *data
);
char *
dxf_image_get_dictionary_owner_soft
(
        DxfImage *image
);
DxfImage *
dxf_image_set_dictionary_owner_soft
(
        DxfImage *image,
        char *dictionary_owner_soft
);
char *
dxf_image_get_material
(
        DxfImage *image
);
DxfImage *
dxf_image_set_material
(
        DxfImage *image,
        char *material
);
char *
dxf_image_get_dictionary_owner_hard
(
        DxfImage *image
);
DxfImage *
dxf_image_set_dictionary_owner_hard
(
        DxfImage *image,
        char *dictionary_owner_hard
);
int16_t
dxf_image_get_lineweight
(
        DxfImage *image
);
DxfImage *
dxf_image_set_lineweight
(
        DxfImage *image,
        int16_t lineweight
);
char *
dxf_image_get_plot_style_name
(
        DxfImage *image
);
DxfImage *
dxf_image_set_plot_style_name
(
        DxfImage *image,
        char *plot_style_name
);
long
dxf_image_get_color_value
(
        DxfImage *image
);
DxfImage *
dxf_image_set_color_value
(
        DxfImage *image,
        long color_value
);
char *
dxf_image_get_color_name
(
        DxfImage *image
);
DxfImage *
dxf_image_set_color_name
(
        DxfImage *image,
        char *color_name
);
long
dxf_image_get_transparency
(
        DxfImage *image
);
DxfImage *
dxf_image_set_transparency
(
        DxfImage *image,
        long transparency
);
DxfPoint *
dxf_image_get_p0
(
        DxfImage *image
);
DxfImage *
dxf_image_set_p0
(
        DxfImage *image,
        DxfPoint *p0
);
double
dxf_image_get_x0
(
        DxfImage *image
);
DxfImage *
dxf_image_set_x0
(
        DxfImage *image,
        double x0
);
double
dxf_image_get_y0
(
        DxfImage *image
);
DxfImage *
dxf_image_set_y0
(
        DxfImage *image,
        double y0
);
double
dxf_image_get_z0
(
        DxfImage *image
);
DxfImage *
dxf_image_set_z0
(
        DxfImage *image,
        double z0
);
DxfPoint *
dxf_image_get_p1
(
        DxfImage *image
);
DxfImage *
dxf_image_set_p1
(
        DxfImage *image,
        DxfPoint *p1
);
double
dxf_image_get_x1
(
        DxfImage *image
);
DxfImage *
dxf_image_set_x1
(
        DxfImage *image,
        double x1
);
double
dxf_image_get_y1
(
        DxfImage *image
);
int
dxf_image_get_image_display_properties
(
        DxfImage *image
);
DxfImage *
dxf_image_set_image_display_properties
(
        DxfImage *image,
        int image_display_properties
);
int
dxf_image_get_clipping_boundary_type
(
        DxfImage *image
);
DxfImage *
dxf_image_set_clipping_boundary_type
(
        DxfImage *image,
        int clipping_boundary_type
);
long
dxf_image_get_class_version
(
        DxfImage *image
);
DxfImage *
dxf_image_set_class_version
(
        DxfImage *image,
        long class_version
);
long
dxf_image_get_number_of_clip_boundary_vertices
(
        DxfImage *image
);
DxfImage *
dxf_image_set_number_of_clip_boundary_vertices
(
        DxfImage *image,
        long number_of_clip_boundary_vertices
);
int
dxf_image_get_clipping_state
(
        DxfImage *image
);
DxfImage *
dxf_image_set_clipping_state
(
        DxfImage *image,
        int clipping_state
);
int
dxf_image_get_brightness
(
        DxfImage *image
);
DxfImage *
dxf_image_set_brightness
(
        DxfImage *image,
        int brightness
);
int
dxf_image_get_contrast
(
        DxfImage *image
);
DxfImage *
dxf_image_set_contrast
(
        DxfImage *image,
        int contrast
);
int
dxf_image_get_fade
(
        DxfImage *image
);
DxfImage *
dxf_image_set_fade
(
        DxfImage *image,
        int fade
);
char *
dxf_image_get_imagedef_object
(
        DxfImage *image
);
DxfImage *
dxf_image_set_imagedef_object
(
        DxfImage *image,
        char *imagedef_object
);
char *
dxf_image_get_imagedef_reactor_object
(
        DxfImage *image
);
DxfImage *
dxf_image_set_imagedef_reactor_object
(
        DxfImage *image,
        char *imagedef_reactor_object
);
DxfImage *
dxf_image_get_next
(
        DxfImage *image
);
DxfImage *
dxf_image_set_next
(
        DxfImage *image,
        DxfImage *next
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_IMAGE_H */


/* EOF */
