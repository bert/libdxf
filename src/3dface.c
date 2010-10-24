/*!
 * \file 3dface.c
 * \author Copyright (C) 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF 3D face entity (\c 3DFACE).
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


#include "3dface.h"


/*!
 * \brief Allocate memory for a \c Dxf3dface.
 *
 * Fill the memory contents with zeros.
 */
Dxf3dface *
dxf_3dface_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_new () function.\n",
                __FILE__, __LINE__);
#endif
        Dxf3dface *dxf_3dface = NULL;
        size_t size;

        size = sizeof (Dxf3dface);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_3dface = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_3dface_new () could not allocate memory for a Dxf3dface struct.\n");
                dxf_3dface = NULL;
        }
        else
        {
                memset (dxf_3dface, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dface_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_3dface);
}


/*!
 * \brief Write DXF output to a file for a 3D face entity (\c 3DFACE).
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_3dface_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        Dxf3dface dxf_3dface
                /*!< DXF 3D face entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("3DFACE");

        if (strcmp (dxf_3dface.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_3dface_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_3dface.common.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_3dface.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_3dface.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_3dface.common.id_code);
        }
        if (strcmp (dxf_3dface.common.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_3dface.common.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_3dface.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_3dface.x0);
        fprintf (fp, " 20\n%f\n", dxf_3dface.y0);
        fprintf (fp, " 30\n%f\n", dxf_3dface.z0);
        fprintf (fp, " 11\n%f\n", dxf_3dface.x1);
        fprintf (fp, " 21\n%f\n", dxf_3dface.y1);
        fprintf (fp, " 31\n%f\n", dxf_3dface.z1);
        fprintf (fp, " 12\n%f\n", dxf_3dface.x2);
        fprintf (fp, " 22\n%f\n", dxf_3dface.y2);
        fprintf (fp, " 32\n%f\n", dxf_3dface.z2);
        fprintf (fp, " 13\n%f\n", dxf_3dface.x3);
        fprintf (fp, " 23\n%f\n", dxf_3dface.y3);
        fprintf (fp, " 33\n%f\n", dxf_3dface.z3);
        if (dxf_3dface.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_3dface.common.thickness);
        }
        if (dxf_3dface.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_3dface.common.color);
        }
        if (dxf_3dface.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dface_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
