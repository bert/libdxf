/*!
 * \file mline.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mline entity (\c MLINE).
 *
 * \version The \c MLINE entity was introduced in DXF R13.
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


#include "mline.h"


/*!
 * \brief Allocate memory for a \c DxfMline.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfMline *
dxf_mline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMline *mline = NULL;
        size_t size;

        size = sizeof (DxfMline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfMline struct.\n")),
                  __FUNCTION__);
                mline = NULL;
        }
        else
        {
                memset (mline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c MLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfMline *
dxf_mline_init
(
        DxfMline *mline
                /*!< DXF mline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mline = dxf_mline_new ();
        }
        if (mline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfMline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        mline->id_code = 0;
        mline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mline->layer = strdup (DXF_DEFAULT_LAYER);
        mline->elevation = 0.0;
        mline->thickness = 0.0;
        mline->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        mline->visibility = DXF_DEFAULT_VISIBILITY;
        mline->color = DXF_COLOR_BYLAYER;
        mline->paperspace = DXF_MODELSPACE;
        mline->dictionary_owner_soft = strdup ("");
        mline->dictionary_owner_hard = strdup ("");
        mline->style_name = strdup ("");
        mline->x0 = 0.0;
        mline->y0 = 0.0;
        mline->z0 = 0.0;
        mline->x1 = 0.0;
        mline->y1 = 0.0;
        mline->z1 = 0.0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                mline->x2[i] = 0.0;
                mline->y2[i] = 0.0;
                mline->z2[i] = 0.0;
                mline->x3[i] = 0.0;
                mline->y3[i] = 0.0;
                mline->z3[i] = 0.0;
                mline->element_parameters[i] = 0.0;
                mline->area_fill_parameters[i] = 0.0;
        }
        mline->scale_factor = 1.0;
        mline->justification = 0;
        mline->flags = 0;
        mline->number_of_vertices = 0;
        mline->number_of_elements = 0;
        mline->number_of_area_fill_parameters = 0;
        mline->extr_x0 = 0.0;
        mline->extr_y0 = 0.0;
        mline->extr_z0 = 1.0;
        mline->mlinestyle_dictionary = strdup ("");
        mline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Free the allocated memory for a DXF \c MLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_mline_free
(
        DxfMline *mline
                /*!< Pointer to the memory occupied by the DXF \c MLINE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfMline was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (mline->linetype);
        free (mline->layer);
        free (mline->dictionary_owner_soft);
        free (mline->dictionary_owner_hard);
        free (mline->style_name);
        free (mline->mlinestyle_dictionary);
        free (mline);
        mline = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
