/*!
 * \file sortentstable.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF sortentstable object (\c SORTENTSTABLE).
 *
 * \version The \c SORTENTSTABLE object was introduced in DXF R14.
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


#include "sortentstable.h"


/*!
 * \brief Allocate memory for a \c DxfSortentsTable.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfSortentsTable *
dxf_sortentstable_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSortentsTable *sortentstable = NULL;
        size_t size;

        size = sizeof (DxfSortentsTable);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((sortentstable = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSortentsTable struct.\n")),
                  __FUNCTION__);
                sortentstable = NULL;
        }
        else
        {
                memset (sortentstable, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SORTENTSTABLE
 * object.
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
DxfSortentsTable *
dxf_sortentstable_init
(
        DxfSortentsTable *sortentstable
                /*!< DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                sortentstable = dxf_sortentstable_new ();
        }
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSortentsTable struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sortentstable->id_code = 0;
        sortentstable->dictionary_owner_soft = strdup ("");
        sortentstable->dictionary_owner_hard = strdup ("");
        sortentstable->block_owner = strdup ("");
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                sortentstable->entity_owner[i] = strdup ("");
                sortentstable->sort_handle[i] = 0;
        }
        sortentstable->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Free the allocated memory for a DXF \c SORTENTSTABLE and all
 * it's data fields.
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
dxf_sortentstable_free
(
        DxfSortentsTable *sortentstable
                /*!< Pointer to the memory occupied by the DXF
                 * \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (sortentstable->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfSortentsTable was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (sortentstable->dictionary_owner_soft);
        free (sortentstable->dictionary_owner_hard);
        free (sortentstable->block_owner);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (sortentstable->entity_owner[i]);
        }
        free (sortentstable);
        sortentstable = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
