/*!
 * \file lwpolyline.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF light weight polyline entity (\c LWPOLYLINE).
 *
 * \warning This entity requires AutoCAD version 2004 or higher.
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


#include "lwpolyline.h"


/*!
 * \brief Write DXF output to a file for a light weight polyline entity.
 *
 * \warning This entity requires AutoCAD version 2004 or higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_write_lowlevel
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
                 * defaults to 0.0. */
        double y0,
                /*!< group code = 20\n
                 * defaults to 0.0. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double start_width,
                /*!< group code = 40\n
                 * optional, defaults to 0.0. */
        double end_width,
                /*!< group code = 41\n
                 * optional, defaults to 0.0. */
        double constant_width,
                /*!< group code = 43\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER. */
        int paperspace,
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int flag,
                /*!< group code = 70\n
                 * optional, defaults to 0. */
        int number_vertices,
                /*!< group code = 90. */
        double extr_x0,
                /*!< group code = 210\n
                 * Extrusion direction (optional; default = 0, 0, 1)\n
                 * DXF: X value;\n
                 * APP: 3D vector\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double extr_y0,
                /*!< group code = 220
                 * DXF: Y value of extrusion direction (optional). */
        double extr_z0
                /*!< group code = 230
                 * DXF: Z value of extrusion direction (optional). */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_lwpolyline_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LWPOLYLINE");

        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_lwpolyline_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n",
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
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_lwpolyline_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a light weight polyline entity.
 *
 * \warning This entity requires AutoCAD version 2004 or higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfLWPolyline dxf_lwpolyline
                /*!< DXF polyline entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_lwpolyline_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LWPOLYLINE");

        if (strcmp (dxf_lwpolyline.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_lwpolyline_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_lwpolyline.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n",
                        dxf_entity_name);
                dxf_lwpolyline.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_lwpolyline.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_lwpolyline.id_code);
        }
        if (strcmp (dxf_lwpolyline.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_lwpolyline.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_lwpolyline.layer);
        fprintf (fp, " 10\n%f\n", dxf_lwpolyline.x0);
        fprintf (fp, " 20\n%f\n", dxf_lwpolyline.y0);
        if (dxf_lwpolyline.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_lwpolyline.thickness);
        }
        if (dxf_lwpolyline.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_lwpolyline.color);
        }
        if (dxf_lwpolyline.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_lwpolyline_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
