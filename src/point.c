/*!
 * \file point.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF point entity (\c POINT).
 *
 * Point entities have an optional 50 group that determines the
 * orientation of PDMODE images.\n
 * The group value is the negative of the Entity Coordinate Systems
 * (ECS) angle of the UCS X axis in effect when the point was drawn.\n
 * The X-axis of the UCS in effect when the point was drawn is always
 * parallel to the XY plane for the point's ECS, and the angle between
 * the UCS X axis and the ECS X axis is a single 2D angle.\n
 * The value in group 50 is the angle from horizontal (the effective
 * X-axis) to the ECS X axis.\n
 *
 * Entity Coordinate Systems (ECS) are described ... somewhere else.
 *
 * \todo Add a link to somewhere else.
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
 * \brief Allocate memory for a \c DxfPoint.
 *
 * and fill the memory contents with zeros.
 */
DxfPoint *
dxf_malloc_point ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_malloc_point () function.\n",
                __FILE__, __LINE__);
#endif
        DxfPoint *dxf_point = NULL;
        size_t size;

        size = sizeof (DxfPoint);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_point = malloc (size)) == NULL)
        {
                fprintf (stderr, "[File: %s: line: %d] Out of memory in dxf_malloc_point()\n",
                        __FILE__, __LINE__);
        }
        memset (dxf_point, 0, size);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_malloc_point () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_point);
}


/*!
 * \brief Allocate memory and initialize data fields in an \c POINT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfPoint *
dxf_init_point_struct
(
        DxfPoint *dxf_point
                /*!< DXF point entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_init_point_struct () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_point = dxf_malloc_point ();
        if (dxf_point == NULL)
        {
              fprintf(stderr, "ERROR: could not allocate memory for a DxfPoint struct.\n");
              return (NULL);
        }
        dxf_point->common.id_code = 0;
        dxf_point->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_point->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_point->x0 = 0.0;
        dxf_point->y0 = 0.0;
        dxf_point->z0 = 0.0;
        dxf_point->extr_x0 = 0.0;
        dxf_point->extr_y0 = 0.0;
        dxf_point->extr_z0 = 0.0;
        dxf_point->common.thickness = 0.0;
        dxf_point->common.color = DXF_COLOR_BYLAYER;
        dxf_point->common.paperspace = DXF_MODELSPACE;
        dxf_point->common.acad_version_number = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_init_point_struct () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_point);
}


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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_point () function.\n",
                __FILE__, __LINE__);
#endif
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n",
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
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_point () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_point_struct () function.\n",
                __FILE__, __LINE__);
#endif
        if (strcmp (dxf_point.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name,
                        dxf_point.common.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_point.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_point.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_point.common.id_code);
        }
        fprintf (fp, "  8\n%s\n", dxf_point.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_point.x0);
        fprintf (fp, " 20\n%f\n", dxf_point.y0);
        fprintf (fp, " 30\n%f\n", dxf_point.z0);
        if (dxf_point.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_point.common.thickness);
        }
        if (dxf_point.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_point.common.color);
        }
        if (dxf_point.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        return (EXIT_SUCCESS);
}


/* EOF */
