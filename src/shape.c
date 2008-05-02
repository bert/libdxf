/*!
 * \file shape.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF shape entity (\c SHAPE).
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
#include "shape.h"

/*!
 * \brief Write DXF output to a file for a shape entity.
 */
int
dxf_write_shape
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *shape_name,
                /*!< group code = 2. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to \c BYLAYER. */
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
        double size,
                /*!< group code = 40. */
        double rel_x_scale,
                /*!< group code = 41\n
                 * optional, defaults to 1.0. */
        double rot_angle,
                /*!< group code = 50\n
                 * optional, defaults to 0.0. */
        double obl_angle,
                /*!< group code = 51\n
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_shape () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("SHAPE");

        if (strcmp (shape_name, "") == 0)
        {
                fprintf (stderr, "Error: %s name string is empty for the %s entity with id-code: %x\n", dxf_entity_name, dxf_entity_name, id_code);
                dxf_skip_entity (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0", dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (size == 0.0)
        {
                fprintf (stderr, "Warning: size has a value of 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
        }
        if (rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning: relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  2\n%s\n", shape_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (linetype != DXF_DEFAULT_LINETYPE)
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
        fprintf (fp, " 40\n%f\n", size);
        if (rel_x_scale != 1.0)
        {
                fprintf (fp, " 41\n%f\n", rel_x_scale);
        }
        if (rot_angle != 0.0)
        {
                fprintf (fp, " 50\n%f\n", rot_angle);
        }
        if (obl_angle != 0.0)
        {
                fprintf (fp, " 51\n%f\n", obl_angle);
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
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_shape () function.\n", __FILE__, __LINE__);
#endif


/*!
 * \brief Write DXF output to fp for a shape entity.
 */
int
dxf_write_shape_struct
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfShape dxf_shape
                /*!< DXF shape entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_shape_struct () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("SHAPE");

        if (strcmp (dxf_shape.shape_name, "") == 0)
        {
                fprintf (stderr, "Error: %s name string is empty for the %s entity with id-code: %x\n", dxf_entity_name, dxf_entity_name, dxf_shape.id_code);
                dxf_skip_entity (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_shape.layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, dxf_shape.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0", dxf_entity_name);
                dxf_shape.layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_shape.size == 0.0)
        {
                fprintf (stderr, "Warning: size has a value of 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, dxf_shape.id_code);
        }
        if (dxf_shape.rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning: relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, dxf_shape.id_code);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  2\n%s\n", dxf_shape.shape_name);
        if (dxf_shape.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_shape.id_code);
        }
        if (dxf_shape.linetype != DXF_DEFAULT_LINETYPE)
        {
                fprintf (fp, "  6\n%s\n", dxf_shape.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_shape.layer);
        fprintf (fp, " 10\n%f\n", dxf_shape.x0);
        fprintf (fp, " 20\n%f\n", dxf_shape.y0);
        fprintf (fp, " 30\n%f\n", dxf_shape.z0);
        if (dxf_shape.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_shape.thickness);
        }
        fprintf (fp, " 40\n%f\n", dxf_shape.size);
        if (dxf_shape.rel_x_scale != 1.0)
        {
                fprintf (fp, " 41\n%f\n", dxf_shape.rel_x_scale);
        }
        if (dxf_shape.rot_angle != 0.0)
        {
                fprintf (fp, " 50\n%f\n", dxf_shape.rot_angle);
        }
        if (dxf_shape.obl_angle != 0.0)
        {
                fprintf (fp, " 51\n%f\n", dxf_shape.obl_angle);
        }
        if (dxf_shape.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_shape.color);
        }
        if (dxf_shape.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_shape_struct () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF */
