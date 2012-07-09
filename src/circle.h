/*!
 * \file circle.h
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Header file for a DXF circle entity (\c CIRCLE).
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


#include "global.h"
#include "entity.h"


/*!
 * \brief DXF definition of a circle entity.
 */
typedef struct
dxf_circle
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file.\n
                 * Group code = 230. */
        double radius;
                /*!< group code = 40. */
        struct DxfCircle *next;
                /*!< pointer to the next DxfCircle.\n
                 * \c NULL in the last DxfCircle. */
} DxfCircle, * DxfCirclePtr;


DxfCircle *
dxf_circle_new ();
DxfCircle *
dxf_circle_init
(
        DxfCircle *dxf_circle
);
int
dxf_circle_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfCircle *dxf_circle,
        int acad_version_number
);
int
dxf_circle_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *linetype,
        char *layer,
        double x0,
        double y0,
        double z0,
        double thickness,
        double radius,
        int color,
        int paperspace,
        int acad_version_number
);
int
dxf_circle_write
(
        FILE *fp,
        DxfCircle dxf_circle,
        int acad_version_number
);


/* EOF */
