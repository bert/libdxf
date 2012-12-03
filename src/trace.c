/*!
 * \file trace.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF trace entity (\c TRACE).
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


#include "trace.h"


/*!
 * \brief Write DXF output to fp for a trace entity.
 */
int
dxf_trace_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfTrace *dxf_trace
                /*!< DXF trace entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_trace_write () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("TRACE");

        if (strcmp (dxf_trace->layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, dxf_trace->id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0", dxf_entity_name);
                dxf_trace->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_trace->id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_trace->id_code);
        }
        if (strcmp (dxf_trace->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_trace->linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_trace->layer);
        fprintf (fp, " 10\n%f\n", dxf_trace->x0);
        fprintf (fp, " 20\n%f\n", dxf_trace->y0);
        fprintf (fp, " 30\n%f\n", dxf_trace->z0);
        fprintf (fp, " 11\n%f\n", dxf_trace->x1);
        fprintf (fp, " 21\n%f\n", dxf_trace->y1);
        fprintf (fp, " 31\n%f\n", dxf_trace->z1);
        fprintf (fp, " 12\n%f\n", dxf_trace->x2);
        fprintf (fp, " 22\n%f\n", dxf_trace->y2);
        fprintf (fp, " 32\n%f\n", dxf_trace->z2);
        fprintf (fp, " 13\n%f\n", dxf_trace->x3);
        fprintf (fp, " 23\n%f\n", dxf_trace->y3);
        fprintf (fp, " 33\n%f\n", dxf_trace->z3);
        if (dxf_trace->thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_trace->thickness);
        }
        if (dxf_trace->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_trace->color);
        }
        if (dxf_trace->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_trace_write () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a trace entity.
 */
int
dxf_trace_write_lowlevel
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
                 * base point. */
        double y0,
                /*!< group code = 20\n
                 * base point. */
        double z0,
                /*!< group code = 30\n
                 * base point. */
        double x1,
                /*!< group code = 11\n
                 * alignment point. */
        double y1,
                /*!< group code = 21\n
                 * alignment point. */
        double z1,
                /*!< group code = 31\n
                 * alignment point. */
        double x2,
                /*!< group code = 12\n
                 * alignment point. */
        double y2,
                /*!< group code = 22\n
                 * alignment point. */
        double z2,
                /*!< group code = 32\n
                 * alignment point. */
        double x3,
                /*!< group code = 13\n
                 * alignment point. */
        double y3,
                /*!< group code = 23\n
                 * alignment point. */
        double z3,
                /*!< group code = 33\n
                 * alignment point. */
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_trace_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("TRACE");

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
        fprintf (fp, " 12\n%f\n", x2);
        fprintf (fp, " 22\n%f\n", y2);
        fprintf (fp, " 32\n%f\n", z2);
        fprintf (fp, " 13\n%f\n", x3);
        fprintf (fp, " 23\n%f\n", y3);
        fprintf (fp, " 33\n%f\n", z3);
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
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_trace_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
