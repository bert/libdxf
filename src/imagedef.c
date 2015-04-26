/*!
 * \file imagedef.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF imagedef object (\c IMAGEDEF).
 *
 * \version The \c IMAGEDEF object was introduced in DXF R14.
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


#include "imagedef.h"


/*!
 * \brief Allocate memory for a \c DxfImagedef.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfImagedef *
dxf_imagedef_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfImagedef *imagedef = NULL;
        size_t size;

        size = sizeof (DxfImagedef);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((imagedef = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfImagedef struct.\n")),
                  __FUNCTION__);
                imagedef = NULL;
        }
        else
        {
                memset (imagedef, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (imagedef);
}


/*!
 * \brief Free the allocated memory for a DXF \c IMAGEDEF and all it's
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
dxf_imagedef_free
(
        DxfImagedef *imagedef
                /*!< Pointer to the memory occupied by the DXF
                 * \c IMAGEDEF object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (imagedef->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfImagedef was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (imagedef->dictionary_owner_soft);
        free (imagedef->dictionary_owner_hard);
        free (imagedef->file_name);
        free (imagedef->acad_image_dict_soft);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (imagedef->imagedef_reactor_soft[i]);
        }
        free (imagedef);
        imagedef = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
