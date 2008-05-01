/*!
 * \file circle.h
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Defintion of a DXF circle entity (\c CIRCLE).
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
 * \brief DXF definition of a circle entity.
 */
typedef struct
dxf_circle
{
        int id_code;
                /*!< group code = 5. */
        char *linetype;
                /*!< group code = 6\n
                 * optional, defaults to \c BYLAYER. */
        char *layer;
                /*!< group code = 8. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double thickness;
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double radius;
                /*!< group code = 40. */
        int color;
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER. */
        int paperspace;
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
} DxfCircle, * DxfCirclePtr;

/* EOF */
