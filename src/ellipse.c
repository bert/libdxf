/*!
 * \file ellipse.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF ellipse entity (\c ELLIPSE).
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


#include "ellipse.h"


/*!
 * \brief Write DXF output to a file for an ellipse entity (elliptic arc).
 *
 * This entity requires AutoCAD version R14 or higher.
 */
int
dxf_write_ellipse
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to BYLAYER. */
        char *layer,
                /*!< group code = 8.*/
        double x0,
                /*!< group code = 10\n
                 * base point. */
        double y0,
                /*!< group code = 20\n
                 * base point. */
        double z0,
                /*!< group code = 30\n
                 * base point. */
        double x1,
                /*!< group code = 11\n
                 * base point. */
        double y1,
                /*!< group code = 21\n
                 * base point. */
        double z1,
                /*!< group code = 31\n
                 * base point. */
        double extr_x0,
                /*!< group code = 210\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_y0,
                /*!< group code = 220\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_z0,
                /*!< group code = 230\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 1.0. */
        double thickness,
                /*!< group code = 39\n
                 *  optional, defaults to 0.0. */
        double ratio,
                /*!< group code = 40\n
                 * ratio of minor axis to major axis. */
        double start_angle,
                /*!< group code = 41. */
        double end_angle,
                /*!< group code = 42. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to BYLAYER. */
        int paperspace,
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_ellipse () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("ELLIPSE");
        if (ratio == 0.0)
        {
                fprintf (stderr, "Error: ratio value equals 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
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
        fprintf (fp, " 11\n%f\n", x1);
        fprintf (fp, " 21\n%f\n", y1);
        fprintf (fp, " 31\n%f\n", z1);
        fprintf (fp, " 210\n%f\n", extr_x0);
        fprintf (fp, " 220\n%f\n", extr_y0);
        fprintf (fp, " 230\n%f\n", extr_z0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        fprintf (fp, " 40\n%f\n", ratio);
        fprintf (fp, " 41\n%f\n", start_angle);
        fprintf (fp, " 42\n%f\n", end_angle);
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_ellipse () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an ellipse entity (elliptic arc).
 *
 * This entity requires AutoCAD version R14 or higher.
 */
int
dxf_write_ellipse_struct
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfEllipse dxf_ellipse,
                /*!< DXF ellipse entity */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_ellipse () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("ELLIPSE");
        if (dxf_ellipse.ratio == 0.0)
        {
                fprintf (stderr, "Error: ratio value equals 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, dxf_ellipse.id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_ellipse.layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, dxf_ellipse.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0", dxf_entity_name);
                dxf_ellipse.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ellipse.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_ellipse.id_code);
        }
        if (strcmp (dxf_ellipse.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_ellipse.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_ellipse.layer);
        fprintf (fp, " 10\n%f\n", dxf_ellipse.x0);
        fprintf (fp, " 20\n%f\n", dxf_ellipse.y0);
        fprintf (fp, " 30\n%f\n", dxf_ellipse.z0);
        fprintf (fp, " 11\n%f\n", dxf_ellipse.x1);
        fprintf (fp, " 21\n%f\n", dxf_ellipse.y1);
        fprintf (fp, " 31\n%f\n", dxf_ellipse.z1);
        fprintf (fp, " 210\n%f\n", dxf_ellipse.extr_x0);
        fprintf (fp, " 220\n%f\n", dxf_ellipse.extr_y0);
        fprintf (fp, " 230\n%f\n", dxf_ellipse.extr_z0);
        if (dxf_ellipse.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_ellipse.thickness);
        }
        fprintf (fp, " 40\n%f\n", dxf_ellipse.ratio);
        fprintf (fp, " 41\n%f\n", dxf_ellipse.start_angle);
        fprintf (fp, " 42\n%f\n", dxf_ellipse.end_angle);
        if (dxf_ellipse.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_ellipse.color);
        }
        if (dxf_ellipse.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_ellipse () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
