/*!
 * \file region.h
 *
 * \author Copyright (C) 2013 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF region entity (\c REGION).
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
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD region entity (\c REGION).
 */
typedef struct
dxf_region
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
        /* Specific members for a DXF region. */
        char *proprietary_data[DXF_MAX_PARAM];
                /*!< group code = 1\n
                 * Proprietary data (multiple lines < 255 characters
                 * each).*/
        char *additional_proprietary_data[DXF_MAX_PARAM];
                /*!< group code = 3\n
                 * Additional lines of proprietary data if previous
                 * group 1 string is greater than 255 characters
                 * (optional).*/
        int modeler_format_version_number;
                /*!< group code = 70\n
                 * Modeler format version number (currently = 1).\n */
        struct DxfRegion *next;
                /*!< pointer to the next DxfRegion.\n
                 * \c NULL in the last DxfRegion. */
} DxfRegion;


DxfRegion *
dxf_region_new ();
DxfRegion *
dxf_region_init
(
        DxfRegion *dxf_region
);
int
dxf_region_read
(
        DxfFile *fp,
        DxfRegion *dxf_region
);
int
dxf_region_write
(
        DxfFile *fp,
        DxfRegion *dxf_region
);
int
dxf_region_free
(
        DxfRegion *dxf_region
);


#endif /* LIBDXF_SRC_REGION_H */


/* EOF */
