/*!
 * \file donut.c
 * 
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * 
 * \brief Functions for a DXF donut entity (\c DONUT).
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


#include "donut.h"


/*!
 * \brief Draw a donut.
 *
 * A typical convenience function.\n
 * Draw a donut by means of two bulged vertices into a single polyline.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_donut_write_lowlevel
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, if omitted defaults to \c BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * if omitted defaults to 0.0. */
        double y0,
                /*!< group code = 20\n
                 * if omitted defaults to 0.0. */
        double z0,
                /*!< group code = 30\n
                 * default elevation for vertices. */
        double thickness,
                /*!< group code = 39\n
                 * optional, if omitted defaults to 0.0. */
        double outside_diameter,
                /*!< outside diameter. */
        double inside_diameter,
                /*!< inside diameter. */
        int color,
                /*!< group code = 62\n
                 * optional, if omitted defaults to \c BYLAYER. */
        int paperspace
                /*!< group code = 67\n
                 * optional, if omitted defaults to 0 (modelspace). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPolyline *dxf_polyline = NULL;
        DxfVertex *dxf_vertex = NULL;
        char *dxf_entity_name = strdup ("POLYLINE");
        double start_width;
        double end_width;

        if (outside_diameter > inside_diameter)
        {
                fprintf (stderr,
                  (_("Error in %s () outside diameter is smaller than the inside diameter for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        start_width = 0.5 * (outside_diameter - inside_diameter);
        end_width = 0.5 * (outside_diameter - inside_diameter);
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Draw a polyline primitive. */
        dxf_polyline_new (dxf_polyline);
        dxf_polyline = dxf_polyline_init (dxf_polyline);
        dxf_polyline->id_code = id_code;
        dxf_polyline->linetype = linetype;
        dxf_polyline->layer = layer;
        dxf_polyline->x0 = x0;
        dxf_polyline->y0 = y0;
        dxf_polyline->z0 = z0;
        dxf_polyline->thickness = thickness;
        dxf_polyline->start_width = 0.5 * start_width;
        dxf_polyline->end_width = 0.5 * end_width;
        dxf_polyline->color = color;
        dxf_polyline->vertices_follow = 1;
        dxf_polyline->paperspace = paperspace;
        dxf_polyline->flag = 1;
        dxf_polyline->polygon_mesh_M_vertex_count = 0;
        dxf_polyline->polygon_mesh_N_vertex_count = 0;
        dxf_polyline->smooth_M_surface_density = 0;
        dxf_polyline->smooth_N_surface_density = 0;
        dxf_polyline->surface_type = 0;
        dxf_polyline_write (fp, dxf_polyline);
        /*! \todo Hook up this polyline to the list of polylines. */
        id_code++;
        /* Write first XY-coordinate. */
        dxf_vertex = dxf_vertex_new ();
        dxf_vertex = dxf_vertex_init (dxf_vertex);
        dxf_vertex->id_code = id_code;
        dxf_vertex->layer = layer;
        dxf_vertex->linetype = linetype;
        dxf_vertex->x0 = x0 - (0.25 * (outside_diameter + inside_diameter));
        dxf_vertex->y0 = y0;
        dxf_vertex->z0 = z0;
        dxf_vertex->thickness = thickness;
        dxf_vertex->start_width = 0.5 * start_width;
        dxf_vertex->end_width = 0.5 * end_width;
        dxf_vertex->bulge = 1;
        dxf_vertex->curve_fit_tangent_direction = 0.0;
        dxf_vertex->color = color;
        dxf_vertex->paperspace = paperspace;
        dxf_vertex->flag = 0;
        dxf_vertex_write (fp, dxf_vertex);
        /*! \todo Hook up this vertex to the list of vertices. */
        id_code++;
        /* Write second XY-coordinate. */
        dxf_vertex->x0 = x0 + (0.25 * (outside_diameter + inside_diameter));
        dxf_vertex_write (fp, dxf_vertex);
        /*! \todo Hook up this vertex to the list of vertices. */
        id_code++;
        /* Write the end of polyline sequence marker. */
        /*! \todo FIX ME:
        dxf_seqend_write (fp, dxf_seqend);
        */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
