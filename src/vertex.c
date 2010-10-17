/*!
 * \file vertex.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF vertex entity (\c VERTEX).
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


#include "vertex.h"


/*!
 * \brief Write DXF output to a file for a vertex entity.
 */
int
dxf_vertex_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, if omitted defaults to \c BYLAYER. */
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
                 * optional, if omitted defaults to 0.0. */
        double start_width,
                /*!< group code = 40\n
                 * optional, if omitted defaults to 0.0. */
        double end_width,
                /*!< group code = 41\n
                 * optional, if omitted defaults to 0.0. */
        double bulge,
                /*!< group code = 42\n
                 * optional, if omitted defaults to 0.0\n
                 * The bulge is the tangent of 1/4 of the included angle for
                 * an arc segment.\n
                 * Made negative if the arc goes clockwise from the start
                 * point to the endpoint.\n
                 * A bulge of 0 indicates a straight segment, and a bulge of
                 * 1 is a semicircle. */
        double curve_fit_tangent_direction,
                /*!< group code = 50\n
                 * optional, a curve-fit tangent direction of 0 may be
                 * omitted from the DXF output, but is significant if the
                 * flag bit is set. */
        int color,
                /*!< group code = 62\n
                 * optional, if omitted defaults to \c BYLAYER. */
        int paperspace,
                /*!< group code = 67\n
                 * optional, if omitted defaults to 0 (modelspace). */
        int flag
                /*!< group code = 70\n
                 * optional, if omitted defaults to 0\n
                 * bit coded:\n
                 * 1 = extra vertex created by curve-fitting\n
                 * 2 = curve-fit tangent defined for this vertex\n
                 * 4 = unused (never set in DXF files)\n
                 * 8 = spline vertex created by spline-fitting\n
                 * 16 = spline frame control point\n
                 * 32 = 3D Polyline vertex\n
                 * 64 = 3D polygon mesh vertex\n
                 * 128 = polyface mesh vertex. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_vertex_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("VERTEX");

        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_vertex_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
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
        if (start_width != 0.0)
        {
                fprintf (fp, " 40\n%f\n", start_width);
        }
        if (end_width != 0.0)
        {
                fprintf (fp, " 41\n%f\n", end_width);
        }
        if (bulge != 0.0)
        {
                fprintf (fp, " 42\n%f\n", bulge);
        }
        if (curve_fit_tangent_direction != 0.0)
        {
                fprintf (fp, " 50\n%f\n", curve_fit_tangent_direction);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_vertex_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a vertex entity.
 */
int
dxf_vertex_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfVertex dxf_vertex
                /*!< DXF vertex entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_vertex_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("VERTEX");

        if (strcmp (dxf_vertex.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_vertex_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_vertex.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_vertex.layer = strdup (DXF_DEFAULT_LAYER);
        }

        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_vertex.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_vertex.id_code);
        }
        if (strcmp (dxf_vertex.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_vertex.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_vertex.layer);
        fprintf (fp, " 10\n%f\n", dxf_vertex.x0);
        fprintf (fp, " 20\n%f\n", dxf_vertex.y0);
        fprintf (fp, " 30\n%f\n", dxf_vertex.z0);
        if (dxf_vertex.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_vertex.thickness);
        }
        if (dxf_vertex.start_width != 0.0)
        {
                fprintf (fp, " 40\n%f\n", dxf_vertex.start_width);
        }
        if (dxf_vertex.end_width != 0.0)
        {
                fprintf (fp, " 41\n%f\n", dxf_vertex.end_width);
        }
        if (dxf_vertex.bulge != 0.0)
        {
                fprintf (fp, " 42\n%f\n", dxf_vertex.bulge);
        }
        if (dxf_vertex.curve_fit_tangent_direction != 0.0)
        {
                fprintf (fp, " 50\n%f\n", dxf_vertex.curve_fit_tangent_direction);
        }
        if (dxf_vertex.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_vertex.color);
        }
        if (dxf_vertex.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", dxf_vertex.flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_vertex_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
