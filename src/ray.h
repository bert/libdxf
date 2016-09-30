/*!
 * \file ray.h
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF ray entity (\c RAY).
 *
 * \warning The ray entity requires AutoCAD version R13 or higher.\n
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


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD ray entity (\c RAY).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_ray
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
                /*!< group code = 38\n
                 * Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default). */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
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
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        /* Specific members for a DXF ray. */
        double x0;
                /*!< group code = 10\n
                 * start point. */
        double y0;
                /*!< group code = 20\n
                 * start point. */
        double z0;
                /*!< group code = 30\n
                 * start point. */
        double x1;
                /*!< group code = 11\n
                 * end point. */
        double y1;
                /*!< group code = 21\n
                 * end point. */
        double z1;
                /*!< group code = 31\n
                 * end point. */
        struct DxfRay *next;
                /*!< pointer to the next DxfRay.\n
                 * \c NULL in the last DxfRay. */
} DxfRay;


DxfRay *
dxf_ray_new ();
DxfRay *
dxf_ray_init
(
        DxfRay *ray
);
DxfRay *
dxf_ray_read
(
        DxfFile *fp,
        DxfRay *ray
);
int
dxf_ray_write
(
        DxfFile *fp,
        DxfRay *ray
);
int
dxf_ray_free
(
        DxfRay *ray
);
void
dxf_ray_free_chain
(
        DxfRay *rays
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_RAY_H */


/* EOF */
