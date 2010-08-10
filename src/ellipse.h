/*!
 * \file ellipse.h
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Definition of a DXF ellipse entity (\c ELLIPSE).
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


/*!
 * \brief Write DXF output to a file for an ellipse entity (elliptic arc).
 *
 * This entity requires AutoCAD version R14 or higher.
 */
typedef struct
dxf_ellipse
{
        FILE *fp;
                /*!< file pointer to output file (or device). */
        int id_code;
                /*!< group code = 5. */
        char *linetype;
                /*!< group code = 6\n
                 * optional, defaults to BYLAYER. */
        char *layer;
                /*!< group code = 8.*/
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double x1;
                /*!< group code = 11\n
                 * base point. */
        double y1;
                /*!< group code = 21\n
                 * base point. */
        double z1;
                /*!< group code = 31\n
                 * base point. */
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
        double thickness;
                /*!< group code = 39\n
                 *  optional, defaults to 0.0. */
        double ratio;
                /*!< group code = 40\n
                 * ratio of minor axis to major axis. */
        double start_angle;
                /*!< group code = 41. */
        double end_angle;
                /*!< group code = 42. */
        int color;
                /*!< group code = 62\n
                 * optional, defaults to BYLAYER. */
        int paperspace;
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int acad_version_number;
                /*!< AutoCAD version number. */
} DxfEllipse, * DxfEllipsePtr;


int
dxf_write_ellipse
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
        double extr_x0,
        double extr_y0,
        double extr_z0,
        double thickness,
        double ratio,
        double start_angle,
        double end_angle,
        int color,
        int paperspace,
        int acad_version_number
);
int
dxf_write_ellipse_struct
(
        FILE *fp,
        DxfEllipse dxf_ellipse,
        int acad_version_number
);


/* EOF */
