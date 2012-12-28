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
 * \brief Write DXF output for a DXF \c DIMENSION entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dimension_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDimension *dxf_dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimension_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("DIMENSION");

        if (dxf_dimension == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr, "Error in dxf_dimension_write () a NULL pointer was passed.\n");
        }
        if (strcmp (dxf_dimension->layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_dimension_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_dimension->id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_dimension->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
                fprintf (fp->fp, "100\nAcDbDimension\n");
        }
        fprintf (fp->fp, "  1\n%s\n", dxf_dimension->dim_text);
        fprintf (fp->fp, "  2\n%s\n", dxf_dimension->dimblock_name);
        fprintf (fp->fp, "  3\n%s\n", dxf_dimension->dimstyle_name);
        if (dxf_dimension->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_dimension->id_code);
        }
        if (strcmp (dxf_dimension->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_dimension->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_dimension->layer);
        fprintf (fp->fp, " 10\n%f\n", dxf_dimension->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_dimension->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_dimension->z0);
        fprintf (fp->fp, " 11\n%f\n", dxf_dimension->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_dimension->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_dimension->z1);
        fprintf (fp->fp, " 12\n%f\n", dxf_dimension->x2);
        fprintf (fp->fp, " 22\n%f\n", dxf_dimension->y2);
        fprintf (fp->fp, " 32\n%f\n", dxf_dimension->z2);
        /* Rotated, horizontal, or vertical dimension. */
        if (dxf_dimension->flag == 0)
        {
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
                fprintf (fp->fp, " 50\n%f\n", dxf_dimension->angle);
                fprintf (fp->fp, " 52\n%f\n", dxf_dimension->obl_angle);
        }
        /* Aligned dimension. */
        if (dxf_dimension->flag == 1)
        {
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
                fprintf (fp->fp, " 50\n%f\n", dxf_dimension->angle);
        }
        /* Angular dimension. */
        if (dxf_dimension->flag == 2)
        {
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
                fprintf (fp->fp, " 15\n%f\n", dxf_dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dxf_dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dxf_dimension->z5);
                fprintf (fp->fp, " 16\n%f\n", dxf_dimension->x6);
                fprintf (fp->fp, " 26\n%f\n", dxf_dimension->y6);
                fprintf (fp->fp, " 36\n%f\n", dxf_dimension->z6);
        }
        /* Diameter dimension. */
        if (dxf_dimension->flag == 3)
        {
                fprintf (fp->fp, " 15\n%f\n", dxf_dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dxf_dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dxf_dimension->z5);
        }
        /* Radius dimension. */
        if (dxf_dimension->flag == 4)
        {
                fprintf (fp->fp, " 15\n%f\n", dxf_dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dxf_dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dxf_dimension->z5);
        }
        /* Angular 3-point dimension. */
        if (dxf_dimension->flag == 5)
        {
                fprintf (fp->fp, " 15\n%f\n", dxf_dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dxf_dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dxf_dimension->z5);
                fprintf (fp->fp, " 16\n%f\n", dxf_dimension->x6);
                fprintf (fp->fp, " 26\n%f\n", dxf_dimension->y6);
                fprintf (fp->fp, " 36\n%f\n", dxf_dimension->z6);
        }
        /* Ordinate dimension. */
        if (dxf_dimension->flag == 6)
        {
                fprintf (fp->fp, " 13\n%f\n", dxf_dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dxf_dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dxf_dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dxf_dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dxf_dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dxf_dimension->z4);
        }
        if (dxf_dimension->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_dimension->thickness);
        }
        fprintf (fp->fp, " 40\n%f\n", dxf_dimension->leader_length);
        fprintf (fp->fp, " 41\n%f\n", dxf_dimension->text_line_spacing_factor);
        fprintf (fp->fp, " 42\n%f\n", dxf_dimension->actual_measurement);
        fprintf (fp->fp, " 51\n%f\n", dxf_dimension->hor_dir);
        fprintf (fp->fp, " 53\n%f\n", dxf_dimension->text_angle);
        if (dxf_dimension->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_dimension->color);
        }
        if (dxf_dimension->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, " 70\n%d\n", dxf_dimension->flag);
        fprintf (fp->fp, " 71\n%d\n", dxf_dimension->attachment_point);
        fprintf (fp->fp, " 72\n%d\n", dxf_dimension->text_line_spacing);
        fprintf (fp->fp, "210\n%fn", dxf_dimension->extr_x0);
        fprintf (fp->fp, "220\n%fn", dxf_dimension->extr_y0);
        fprintf (fp->fp, "230\n%fn", dxf_dimension->extr_z0);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimension_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
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
