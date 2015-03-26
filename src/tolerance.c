/*!
 * \file tolerance.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF tolerance entity (\c TOLERANCE).
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


#include "tolerance.h"


/*!
 * \brief Allocate memory for a DXF \c TOLERANCE.
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
DxfTolerance *
dxf_tolerance_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTolerance *tolerance = NULL;
        size_t size;

        size = sizeof (DxfTolerance);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((tolerance = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTolerance struct.\n")),
                  __FUNCTION__);
                tolerance = NULL;
        }
        else
        {
                memset (tolerance, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c TOLERANCE entity.
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
DxfTolerance *
dxf_tolerance_init
(
        DxfTolerance *tolerance
                /*!< DXF tolerance entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                tolerance = dxf_tolerance_new ();
        }
        if (tolerance == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTolerance struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tolerance->id_code = 0;
        tolerance->linetype = strdup (DXF_DEFAULT_LINETYPE);
        tolerance->layer = strdup (DXF_DEFAULT_LAYER);
        tolerance->x0 = 0.0;
        tolerance->y0 = 0.0;
        tolerance->z0 = 0.0;
        tolerance->x1 = 0.0;
        tolerance->y1 = 0.0;
        tolerance->z1 = 0.0;
        tolerance->extr_x0 = 0.0;
        tolerance->extr_y0 = 0.0;
        tolerance->extr_z0 = 0.0;
        tolerance->elevation = 0.0;
        tolerance->thickness = 0.0;
        tolerance->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        tolerance->visibility = DXF_DEFAULT_VISIBILITY;
        tolerance->color = DXF_COLOR_BYLAYER;
        tolerance->paperspace = DXF_MODELSPACE;
        tolerance->dictionary_owner_soft = strdup ("");
        tolerance->dictionary_owner_hard = strdup ("");
        tolerance->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tolerance);
}


/* EOF*/
