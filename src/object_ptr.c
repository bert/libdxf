/*!
 * \file object_ptr.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF object_ptr object (\c OBJECT_PTR).
 *
 * \version The \c OBJECT_PTR object was introduced in DXF R14.
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


#include "object_ptr.h"


/*!
 * \brief Allocate memory for a \c DxfObjectPtr.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfObjectPtr *
dxf_object_ptr_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfObjectPtr *object_ptr = NULL;
        size_t size;

        size = sizeof (DxfObjectPtr);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((object_ptr = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfObjectPtr struct.\n")),
                  __FUNCTION__);
                object_ptr = NULL;
        }
        else
        {
                memset (object_ptr, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_ptr);
}


/*!
 * \brief Free the allocated memory for a DXF \c OBJECT_PTR and all it's
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
dxf_object_ptr_free
(
        DxfObjectPtr *object_ptr
                /*!< Pointer to the memory occupied by the DXF
                 * \c OBJECT_PTR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (object_ptr->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfObjectPtr was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (object_ptr->dictionary_owner_soft);
        free (object_ptr->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (object_ptr->xdata[i]);
        }
        free (object_ptr);
        object_ptr = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
