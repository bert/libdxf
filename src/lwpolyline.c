/*!
 * \file lwpolyline.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF light weight polyline entity (\c LWPOLYLINE).
 *
 * A DXF \c APPID (table entry) entity contains data concerning the
 * application registered with the drawing involved.\n
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
#include "polyline.h"

/*!
 * \brief Write DXF output to fp for a light weight polyline entity.
 *
 * This entity requires AutoCAD release 2004 or higher.
 */
int
dxf_write_lwpolyline_struct
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfPolyline dxf_polyline
                /*!< DXF polyline entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_lwpolyline2 () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LWPOLYLINE");

        if (strcmp (dxf_polyline.layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, dxf_polyline.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n", dxf_entity_name);
                dxf_polyline.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_polyline.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_polyline.id_code);
        }
        if (strcmp (dxf_polyline.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_polyline.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_polyline.layer);
        fprintf (fp, " 10\n%f\n", dxf_polyline.x0);
        fprintf (fp, " 20\n%f\n", dxf_polyline.y0);
        fprintf (fp, " 30\n%f\n", dxf_polyline.z0);
        if (dxf_polyline.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_polyline.thickness);
        }
        if (dxf_polyline.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_polyline.color);
        }
        if (dxf_polyline.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_lwpolyline2 () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF */
