/*!
 * \file donut.c
 * 
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * 
 * \brief Functions for a libDXF donut entity.
 *
 * \warning This is not an official AutoCAD entity.
 *
 * \c donut is an AutoCAD command that generates a polyline (\c POLYLINE)
 * consisting of two vertices (\c VERTEX) and an end of sequence marker
 * (\c SEQEND).
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
 * \brief Allocate memory for a libDXF donut.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDonut *
dxf_donut_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDonut *donut = NULL;
        size_t size;

        size = sizeof (DxfDonut);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((donut = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDonut struct.\n")),
                  __FUNCTION__);
                donut = NULL;
        }
        else
        {
                memset (donut, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Allocate memory and initialize data fields in a libDXF donut
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDonut *
dxf_donut_init
(
        DxfDonut *donut
                /*!< libDXF donut entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                donut = dxf_donut_new ();
        }
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDonut struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Members common for all DXF drawable entities. */
        donut->id_code = 0;
        donut->linetype = strdup (DXF_DEFAULT_LINETYPE);
        donut->layer = strdup (DXF_DEFAULT_LAYER);
        donut->elevation = 0.0;
        donut->thickness = 0.0;
        donut->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        donut->visibility = DXF_DEFAULT_VISIBILITY;
        donut->color = DXF_COLOR_BYLAYER;
        donut->paperspace = DXF_MODELSPACE;
        donut->dictionary_owner_soft = strdup ("");
        donut->dictionary_owner_hard = strdup ("");
        /* Specific members for a libDXF donut. */
        donut->x0 = 0.0;
        donut->y0 = 0.0;
        donut->z0 = 0.0;
        donut->outside_diameter = 0.0;
        donut->inside_diameter = 0.0;
        donut->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (donut);
}


/*!
 * \brief Write DXF output to a file for a libDXF donut.
 *
 * A typical convenience function.\n
 * Draw a donut by means of two bulged vertices into a single polyline.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_donut_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDonut *donut
                /*!< Pointer to a donut struct. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPolyline *polyline = NULL;
        DxfVertex *vertex_1 = NULL;
        DxfVertex *vertex_2 = NULL;
        DxfSeqend *seqend = NULL;
        char *dxf_entity_name = strdup ("POLYLINE");
        double start_width;
        double end_width;
        int id_code = -1;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (donut->outside_diameter > donut->inside_diameter)
        {
                fprintf (stderr,
                  (_("Error in %s () outside diameter is smaller than the inside diameter for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        start_width = 0.5 * (donut->outside_diameter - donut->inside_diameter);
        end_width = 0.5 * (donut->outside_diameter - donut->inside_diameter);
        if (strcmp (donut->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, donut->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                donut->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (donut->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                donut->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Create and write a polyline primitive. */
        dxf_polyline_new (polyline);
        polyline = dxf_polyline_init (polyline);
        id_code = fp->last_id_code;
        id_code++;
        polyline->id_code = id_code;
        polyline->linetype = donut->linetype;
        polyline->layer = donut->layer;
        polyline->x0 = donut->x0;
        polyline->y0 = donut->y0;
        polyline->z0 = donut->z0;
        polyline->thickness = donut->thickness;
        polyline->start_width = 0.5 * start_width;
        polyline->end_width = 0.5 * end_width;
        polyline->color = donut->color;
        polyline->vertices_follow = 1;
        polyline->paperspace = donut->paperspace;
        polyline->flag = 1;
        polyline->polygon_mesh_M_vertex_count = 0;
        polyline->polygon_mesh_N_vertex_count = 0;
        polyline->smooth_M_surface_density = 0;
        polyline->smooth_N_surface_density = 0;
        polyline->surface_type = 0;
        dxf_polyline_write (fp, polyline);
        /*! \todo Hook up this polyline to the list of polylines. */
        /* Create and write the first vertex. */
        vertex_1 = dxf_vertex_new ();
        vertex_1 = dxf_vertex_init (vertex_1);
        id_code = fp->last_id_code;
        id_code++;
        vertex_1->id_code = id_code;
        vertex_1->layer = donut->layer;
        vertex_1->linetype = donut->linetype;
        vertex_1->x0 = donut->x0 - (0.25 * (donut->outside_diameter + donut->inside_diameter));
        vertex_1->y0 = donut->y0;
        vertex_1->z0 = donut->z0;
        vertex_1->thickness = donut->thickness;
        vertex_1->start_width = 0.5 * start_width;
        vertex_1->end_width = 0.5 * end_width;
        vertex_1->bulge = 1;
        vertex_1->curve_fit_tangent_direction = 0.0;
        vertex_1->color = donut->color;
        vertex_1->paperspace = donut->paperspace;
        vertex_1->flag = 0;
        dxf_vertex_write (fp, vertex_1);
        /*! \todo Hook up this vertex to the list of vertices. */
        /* Create and write the second vertex. */
        vertex_2 = dxf_vertex_new ();
        vertex_2 = dxf_vertex_init (vertex_2);
        id_code = fp->last_id_code;
        id_code++;
        vertex_2->id_code = id_code;
        vertex_2->layer = donut->layer;
        vertex_2->linetype = donut->linetype;
        vertex_2->x0 = donut->x0 + (0.25 * (donut->outside_diameter + donut->inside_diameter));
        vertex_2->y0 = donut->y0;
        vertex_2->z0 = donut->z0;
        vertex_2->thickness = donut->thickness;
        vertex_2->start_width = 0.5 * start_width;
        vertex_2->end_width = 0.5 * end_width;
        vertex_2->bulge = 1;
        vertex_2->curve_fit_tangent_direction = 0.0;
        vertex_2->color = donut->color;
        vertex_2->paperspace = donut->paperspace;
        vertex_2->flag = 0;
        dxf_vertex_write (fp, vertex_2);
        /*! \todo Hook up this vertex to the list of vertices. */
        /* Create and write the end of sequence marker. */
        dxf_seqend_new (seqend);
        seqend = dxf_seqend_init (seqend);
        id_code = fp->last_id_code;
        id_code++;
        seqend->id_code = id_code;
        seqend->layer = donut->layer;
        seqend->linetype = donut->linetype;
        dxf_seqend_write (fp, seqend);
        /*! \todo Hook up this seqend to the list of seqends. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a libDXF donut and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_donut_free
(
        DxfDonut *donut
                /*!< Pointer to the memory occupied by the libDXF donut
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (donut->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfDonut was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (donut->linetype);
        free (donut->layer);
        free (donut->dictionary_owner_soft);
        free (donut->dictionary_owner_hard);
        free (donut);
        donut = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
