/*!
 * \file trace.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * \brief Allocate memory for a DXF \c TRACE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfTrace *
dxf_trace_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTrace *dxf_trace = NULL;
        size_t size;

        size = sizeof (DxfTrace);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_trace = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTrace struct.\n")),
                  __FUNCTION__);
                dxf_trace = NULL;
        }
        else
        {
                memset (dxf_trace, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_trace);
}


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
        DXF_DEBUG_BEGIN
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
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
