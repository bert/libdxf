/*!
 * \file line.h
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Definition of a DXF line entity (\c LINE).
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


#include "global.h"
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD line entity.
 */
typedef struct
dxf_line
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
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
        double extr_x0;
                /*!< group code = 210\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_y0;
                /*!< group code = 220\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_z0;
                /*!< group code = 230\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 1.0. */
} DxfLine, * DxfLinePtr;


DxfLine *
dxf_line_new ();
DxfLine *
dxf_line_init
(
        DxfLine *dxf_line
);
int
dxf_line_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfLine *dxf_line,
        int acad_version_number
);
int
dxf_line_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *linetype,
        char *layer,
        double x0,
        double y0,
        double z0,
        double x1,
        double y1,
        double z1,
        double thickness,
        int color,
        int paperspace
);
int
dxf_line_write
(
        FILE *fp,
        DxfLine dxf_line
);


/* EOF */
