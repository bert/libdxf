/*!
 * \file dimension.c
 *
 * \author Copyright (C) 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dimension entity (\c DIMENSION).
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


#include "dimension.h"


/*!
 * \brief Allocate memory for a DXF \c DIMENSION.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDimension *
dxf_dimension_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimension_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfDimension *dxf_dimension = NULL;
        size_t size;

        size = sizeof (DxfDimension);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_dimension = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_dimension_new () could not allocate memory for a DxfArc struct.\n");
                dxf_dimension = NULL;
        }
        else
        {
                memset (dxf_dimension, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimension_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_dimension);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c
 * DIMENSION entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDimension *
dxf_dimension_init
(
        DxfDimension *dxf_dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimension_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_dimension = dxf_dimension_new ();
        if (dxf_dimension == NULL)
        {
              fprintf (stderr, "ERROR in dxf_dimension_init () could not allocate memory for a DxfDimension struct.\n");
              return (NULL);
        }
        dxf_dimension->id_code = 0;
        dxf_dimension->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_dimension->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_dimension->thickness = 0.0;
        dxf_dimension->color = DXF_COLOR_BYLAYER;
        dxf_dimension->paperspace = DXF_PAPERSPACE;
        dxf_dimension->dim_text = strdup ("");
        dxf_dimension->dimblock_name = strdup ("");
        dxf_dimension->dimstyle_name = strdup ("");
        dxf_dimension->x0 = 0.0;
        dxf_dimension->y0 = 0.0;
        dxf_dimension->z0 = 0.0;
        dxf_dimension->x1 = 0.0;
        dxf_dimension->y1 = 0.0;
        dxf_dimension->z1 = 0.0;
        dxf_dimension->x2 = 0.0;
        dxf_dimension->y2 = 0.0;
        dxf_dimension->z2 = 0.0;
        dxf_dimension->x3 = 0.0;
        dxf_dimension->y3 = 0.0;
        dxf_dimension->z3 = 0.0;
        dxf_dimension->x4 = 0.0;
        dxf_dimension->y4 = 0.0;
        dxf_dimension->z4 = 0.0;
        dxf_dimension->x5 = 0.0;
        dxf_dimension->y5 = 0.0;
        dxf_dimension->z5 = 0.0;
        dxf_dimension->x6 = 0.0;
        dxf_dimension->y6 = 0.0;
        dxf_dimension->z6 = 0.0;
        dxf_dimension->leader_length = 0.0;
        dxf_dimension->text_line_spacing_factor = 0.0;
        dxf_dimension->actual_measurement = 0.0;
        dxf_dimension->angle = 0.0;
        dxf_dimension->hor_dir = 0.0;
        dxf_dimension->obl_angle = 0.0;
        dxf_dimension->text_angle = 0.0;
        dxf_dimension->flag = 0;
        dxf_dimension->attachment_point = 0;
        dxf_dimension->text_line_spacing = 0;
        dxf_dimension->extr_x0 = 0.0;
        dxf_dimension->extr_y0 = 0.0;
        dxf_dimension->extr_z0 = 0.0;
        dxf_dimension->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimension_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_dimension);
}


/*!
 * \brief Free the allocated memory for a DXF \c DIMENSION and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dimension_free
(
        DxfDimension *dxf_dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimension_free () function.\n",
                __FILE__, __LINE__);
#endif
        if (dxf_dimension->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_dimension_free () pointer to next DxfDimension was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_dimension->linetype);
        free (dxf_dimension->layer);
        free (dxf_dimension->dim_text);
        free (dxf_dimension->dimblock_name);
        free (dxf_dimension->dimstyle_name);
        free (dxf_dimension);
        dxf_dimension = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimension_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
