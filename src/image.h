/*!
 * \file image.h
 *
 * \author Copyright (C) 2013 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
#include "entity.h"


/*!
 * \brief Definition of an AutoCAD image entity (\c IMAGE).
 */
typedef struct
dxf_image
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< group code = 5\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        char *linetype;
                /*!< group code = 6\n
                 * The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file. */
        char *layer;
                /*!< group code = 8\n
                 * Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given. */
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        /* Specific members for a DXF image. */
        double x0;
                /*!< group code = 10\n
                 * X-value of the insertion point coordinate. */
        double y0;
                /*!< group code = 20\n
                 * Y-value of the insertion point coordinate. */
        double z0;
                /*!< group code = 30\n
                 * Z-value of the insertion point coordinate. */
        double x1;
                /*!< group code = 11\n
                 * X-value of the U-vector of a single pixel (points
                 * along the visual bottom of the image, starting at the
                 * insertion point) (in OCS). */
        double y1;
                /*!< group code = 21\n
                 * Y-value of the U-vector of a single pixel (points
                 * along the visual bottom of the image, starting at the
                 * insertion point) (in OCS). */
        double z1;
                /*!< group code = 31\n
                 * Z-value of the U-vector of a single pixel (points
                 * along the visual bottom of the image, starting at the
                 * insertion point) (in OCS). */
        double x2;
                /*!< group code = 12\n
                 * X-value of the V-vector of a single pixel (points
                 * along the visual left side of the image, starting at
                 * the insertion point) (in OCS). */
        double y2;
                /*!< group code = 22\n
                 * Y-value of the V-vector of a single pixel (points
                 * along the visual left side of the image, starting at
                 * the insertion point) (in OCS). */
        double z2;
                /*!< group code = 32\n
                 * Z-value of the V-vector of a single pixel (points
                 * along the visual left side of the image, starting at
                 * the insertion point) (in OCS). */
        double x3;
                /*!< group code = 13\n
                 * U-value of image size in pixels. */
        double y3;
                /*!< group code = 23\n
                 * V-value of image size in pixels. */
        double x4[DXF_MAX_PARAM];
                /*!< group code = 14\n
                 * X-value of clip boundary vertex (in OCS) (multiple
                 * entries).\n
                 * Notes:\n
                 * <ol>
                 * <li>For rectangular clip boundary type, two opposite
                 * corners must be specified.\n
                 * Default is (-0.5,-0.5), (size.x-0.5, size.y-0.5).</li>
                 * <li>For polygonal clip boundary type, three or more
                 * vertices must be specified.\n
                 * Polygonal vertices must be listed sequentially.</li>
                 * </ul> */
        double y4[DXF_MAX_PARAM];
                /*!< group code = 24\n
                 * Y-value of clip boundary vertex (in OCS) (multiple
                 * entries).\n
                 * Notes:\n
                 * <ol>
                 * <li>For rectangular clip boundary type, two opposite
                 * corners must be specified.\n
                 * Default is (-0.5,-0.5), (size.x-0.5, size.y-0.5).</li>
                 * <li>For polygonal clip boundary type, three or more
                 * vertices must be specified.\n
                 * Polygonal vertices must be listed sequentially.</li>
                 * </ul> */
        int image_display_properties;
                /*!< group code = 70\n
                 * Image display properties.\n
                 * bit coded:\n
                 * <ol>
                 * <li value = "1"> Show image.</li>
                 * <li value = "2"> Show image when not aligned with screen.</li>
                 * <li value = "4"> Use clipping boundary</li>
                 * <li value = "8"> Transparency is on.</li>
                 * </ol> */
        int clipping_boundary_type;
                /*!< group code = 71\n
                 * Clipping boundary type.\n
                 * <ol>
                 * <li value = "1"> Rectangular.</li>
                 * <li value = "2"> Polygonal.</li>
                 * </ol> */
        long class_version;
                /*!< group code = 90\n
                 * Class version.\n */
        long number_of_clip_boundary_vertices;
                /*!< group code = 91\n
                 * Number of clip boundary vertices that follow.\n */
        int clipping_state;
                /*!< group code = 280\n
                 * Clipping state: 0 = off, 1 = on. */
        int brightness;
                /*!< group code = 281\n
                 * Brightness value (0 - 100; default = 50). */
        int contrast;
                /*!< group code = 282\n
                 * Contrast value (0 - 100; default = 50). */
        int fade;
                /*!< group code = 283\n
                 * Fade value (0 - 100; default = 50). */
        char *imagedef_object;
                /*!< group code = 340\n
                 * Hard reference to imagedef object. */
        char *imagedef_reactor_object;
                /*!< group code = 360\n
                 * Hard reference to imagedef_reactor object. */
        struct DxfImage *next;
                /*!< pointer to the next DxfImage.\n
                 * \c NULL in the last DxfImage. */
} DxfImage;


DxfImage *
dxf_image_new ();
DxfImage *
dxf_image_init
(
        DxfImage *dxf_image
);
DxfImage *
dxf_image_read
(
        DxfFile *fp,
        DxfImage *dxf_image
);
int
dxf_image_write
(
        DxfFile *fp,
        DxfImage *dxf_image
);
int
dxf_image_free
(
        DxfImage *dxf_image
);


#endif /* LIBDXF_SRC_IMAGE_H */


/* EOF */
