/*!
 * \file circle.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF circle entity (\c CIRCLE).
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
#include "circle.h"

/*!
 * \brief Write DXF output to a file for a circle entity.
 */
int
dxf_write_circle
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * base point. */
        double y0,
                /*!< group code = 20\n
                 * base point. */
        double z0,
                /*!< group code = 30\n
                 * base point. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double radius,
                /*!< group code = 40. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to BYLAYER. */
        int paperspace
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_circle () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("CIRCLE");
        if (radius == 0.0)
        {
                fprintf (stderr, "Error: radius value equals 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
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
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        fprintf (fp, " 40\n%f\n", radius);
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_circle () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/*!
 * \brief Write DXF output to fp for a circle entity.
 */
int
dxf_write_circle_struct
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfCircle dxf_circle
                /*!< DXF circle entity. */
)
{
        char *dxf_entity_name = strdup ("CIRCLE");

#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_circle2 () function.\n", __FILE__, __LINE__);
#endif
        if (dxf_circle.radius == 0.0)
        {
                fprintf (stderr, "Error: radius value equals 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, dxf_circle.id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_circle.layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, dxf_circle.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0", dxf_entity_name );
                dxf_circle.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_circle.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_circle.id_code);
        }
        if (strcmp (dxf_circle.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_circle.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_circle.layer);
        fprintf (fp, " 10\n%f\n", dxf_circle.x0);
        fprintf (fp, " 20\n%f\n", dxf_circle.y0);
        fprintf (fp, " 30\n%f\n", dxf_circle.z0);
        if (dxf_circle.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_circle.thickness);
        }
        fprintf (fp, " 40\n%f\n", dxf_circle.radius);
        if (dxf_circle.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_circle.color);
        }
        if (dxf_circle.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_circle2 () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF */
