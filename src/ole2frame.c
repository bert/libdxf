/*!
 * \file ole2frame.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF ole2frame entity (\c OLE2FRAME).
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


#include "ole2frame.h"


/*!
 * \brief Allocate memory for a \c DxfOle2Frame.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfOle2Frame *
dxf_ole2frame_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfOle2Frame *ole2frame = NULL;
        size_t size;

        size = sizeof (DxfOle2Frame);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ole2frame = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfOle2Frame struct.\n")),
                  __FUNCTION__);
                ole2frame = NULL;
        }
        else
        {
                memset (ole2frame, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c OLE2FRAME
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfOle2Frame *
dxf_ole2frame_init
(
        DxfOle2Frame *ole2frame
                /*!< DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ole2frame = dxf_ole2frame_new ();
        }
        if (ole2frame == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfOle2Frame struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        ole2frame->id_code = 0;
        ole2frame->linetype = strdup (DXF_DEFAULT_LINETYPE);
        ole2frame->layer = strdup (DXF_DEFAULT_LAYER);
        ole2frame->elevation = 0.0;
        ole2frame->thickness = 0.0;
        ole2frame->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        ole2frame->visibility = DXF_DEFAULT_VISIBILITY;
        ole2frame->color = DXF_COLOR_BYLAYER;
        ole2frame->paperspace = DXF_MODELSPACE;
        ole2frame->dictionary_owner_soft = strdup ("");
        ole2frame->dictionary_owner_hard = strdup ("");
        ole2frame->end_of_data = strdup ("");
        ole2frame->length_of_binary_data = strdup ("");
        ole2frame->x0 = 0.0;
        ole2frame->y0 = 0.0;
        ole2frame->z0 = 0.0;
        ole2frame->x1 = 0.0;
        ole2frame->y1 = 0.0;
        ole2frame->z1 = 0.0;
        ole2frame->ole_version_number = 1;
        ole2frame->ole_object_type = 0;
        ole2frame->tilemode_descriptor = 0;
        ole2frame->length = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                ole2frame->binary_data[i] = strdup ("");
        }
        ole2frame->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Free the allocated memory for a DXF \c OLE2FRAME and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
int
dxf_ole2frame_free
(
        DxfOle2Frame *ole2frame
                /*!< Pointer to the memory occupied by the DXF
                 * \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (ole2frame->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfOle2Frame was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (ole2frame->end_of_data);
        free (ole2frame->length_of_binary_data);
        free (ole2frame->linetype);
        free (ole2frame->layer);
        free (ole2frame->dictionary_owner_soft);
        free (ole2frame->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (ole2frame->binary_data[i]);
        }
        free (ole2frame);
        ole2frame = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
