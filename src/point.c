/*!
 * \file point.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF point entity (\c POINT).
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
#include "point.h"

/*!
 * \brief Write DXF output to a file for a point entity.
 */
int
dxf_write_point
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10. */
        double y0,
                /*!< group code = 20. */
        double z0,
                /*!< group code = 30. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to BYLAYER. */
        int paperspace
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
)
{
        char *dxf_entity_name = strdup ("POINT");

#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_point () function.\n", __FILE__, __LINE__);
#endif
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0", dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
}


/*!
 * \brief Write DXF output to fp for a point entity.
 */
int
dxf_write_point_struct
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfPoint dxf_point
                /*!< DXF point entity. */
)
{
        char *dxf_entity_name = strdup ("POINT");

#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_point_struct () function.\n", __FILE__, __LINE__);
#endif
        if (strcmp (dxf_point.layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, dxf_point.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0", dxf_entity_name);
                dxf_point.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_point.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_point.id_code);
        }
        fprintf (fp, "  8\n%s\n", dxf_point.layer);
        fprintf (fp, " 10\n%f\n", dxf_point.x0);
        fprintf (fp, " 20\n%f\n", dxf_point.y0);
        fprintf (fp, " 30\n%f\n", dxf_point.z0);
        if (dxf_point.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_point.thickness);
        }
        if (dxf_point.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_point.color);
        }
        if (dxf_point.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        return (EXIT_SUCCESS);
}

/* EOF */
