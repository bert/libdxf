/*!
 * \file spline.c
 * 
 * \author Copyright (C) 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * 
 * \brief Functions for a DXF spline entity (\c SPLINE).
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


#include "spline.h"


/*!
 * \brief Allocate memory for a DXF \c SPLINE.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfSpline *
dxf_spline_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_spline_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfSpline *dxf_spline = NULL;
        size_t size;

        size = sizeof (DxfSpline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_spline = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_spline_new () could not allocate memory for a DxfSpline struct.\n");
                dxf_spline = NULL;
        }
        else
        {
                memset (dxf_spline, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_spline_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_spline);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SPLINE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfSpline *
dxf_spline_init
(
        DxfSpline *dxf_spline
                /*!< DXF spline entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_spline_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        dxf_spline = dxf_spline_new ();
        if (dxf_spline == NULL)
        {
              fprintf (stderr, "ERROR in dxf_spline_init () could not allocate memory for a DxfSpline struct.\n");
              return (NULL);
        }
        dxf_spline->id_code = 0;
        dxf_spline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_spline->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_spline->thickness = 0.0;
        dxf_spline->linetype_scale = 1.0;
        dxf_spline->visibility = 0;
        dxf_spline->color = DXF_COLOR_BYLAYER;
        dxf_spline->paperspace = DXF_MODELSPACE;
        dxf_spline->graphics_data_size = 0;
        dxf_spline->shadow_mode = 0;
        dxf_spline->dictionary_owner_soft = strdup ("");
        dxf_spline->material = strdup ("");
        dxf_spline->dictionary_owner_hard = strdup ("");
        dxf_spline->lineweight = 0;
        dxf_spline->plot_style_name = strdup ("");
        dxf_spline->color_value = 0;
        dxf_spline->color_name = strdup ("");
        dxf_spline->transparency = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_spline->binary_graphics_data[i] = strdup ("");
                dxf_spline->x0[i] = 0.0;
                dxf_spline->y0[i] = 0.0;
                dxf_spline->z0[i] = 0.0;
                dxf_spline->x1[i] = 0.0;
                dxf_spline->y1[i] = 0.0;
                dxf_spline->z1[i] = 0.0;
                dxf_spline->knot_value[i] = 0.0;
                dxf_spline->weight_value[i] = 0.0;
        }
        dxf_spline->x2 = 0.0;
        dxf_spline->y2 = 0.0;
        dxf_spline->z2 = 0.0;
        dxf_spline->x3 = 0.0;
        dxf_spline->y3 = 0.0;
        dxf_spline->z3 = 0.0;
        dxf_spline->extr_x0 = 0.0;
        dxf_spline->extr_y0 = 0.0;
        dxf_spline->extr_z0 = 0.0;
        dxf_spline->knot_tolerance = 0.0;
        dxf_spline->control_point_tolerance = 0.0;
        dxf_spline->fit_tolerance = 0.0;
        dxf_spline->flag = 0;
        dxf_spline->degree = 0;
        dxf_spline->number_of_knots = 0;
        dxf_spline->number_of_control_points = 0;
        dxf_spline->number_of_fit_points = 0;
        dxf_spline->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_spline_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_spline);
}


/* EOF */
