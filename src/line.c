/*!
 * \file line.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF line entity (\c LINE).
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

/*!
 * \brief Write DXF output to fp for a line entity.
 */
int
dxf_write_line
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to \c BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * start point. */
        double y0,
                /*!< group code = 20\n
                 * start point. */
        double z0,
                /*!< group code = 30\n
                 * start point. */
        double x1,
                /*!< group code = 11\n
                 * end point. */
        double y1,
                /*!< group code = 21\n
                 * end point. */
        double z1,
                /*!< group code = 31\n
                 * end point. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER. */
        int paperspace
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_line () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LINE");

        if ((x0 == x1) && (y0 == y1) && (z0 == z1))
        {
                fprintf (stderr, "Error: start point and end point are identical for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                dxf_skip_entity (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n", dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        fprintf (fp, " 11\n%f\n", x1);
        fprintf (fp, " 21\n%f\n", y1);
        fprintf (fp, " 31\n%f\n", z1);
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
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_line () function.\n", __FILE__, __LINE__);
#endif
        return;
}


/*!
 * \brief Write DXF output to fp for a line entity.
 */
int
dxf_write_line2
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfLine dxf_line
                /*!< DXF line entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_line2 () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LINE");

        if ((dxf_line.x0 == dxf_line.x1) && (dxf_line.y0 == dxf_line.y1) && (dxf_line.z0 == dxf_line.z1))
        {
                fprintf (stderr, "Error: start point and end point are identical for the %s entity with id-code: %x\n", dxf_entity_name, dxf_line.id_code);
                dxf_skip_entity (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_line.layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, dxf_line.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n", dxf_entity_name);
                dxf_line.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_line.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_line.id_code);
        }
        if (strcmp (dxf_line.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_line.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_line.layer);
        fprintf (fp, " 10\n%f\n", dxf_line.x0);
        fprintf (fp, " 20\n%f\n", dxf_line.y0);
        fprintf (fp, " 30\n%f\n", dxf_line.z0);
        fprintf (fp, " 11\n%f\n", dxf_line.x1);
        fprintf (fp, " 21\n%f\n", dxf_line.y1);
        fprintf (fp, " 31\n%f\n", dxf_line.z1);
        if (dxf_line.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_line.thickness);
        }
        if (dxf_line.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_line.color);
        }
        if (dxf_line.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_line2 () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF */

