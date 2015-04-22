/*!
 * \file group.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF group object (\c GROUP).
 *
 * \version The \c GROUP object was introduced in DXF R13.
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


#include "group.h"


/*!
 * \brief Allocate memory for a \c DxfGroup.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfGroup *
dxf_group_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfGroup *group = NULL;
        size_t size;

        size = sizeof (DxfGroup);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((group = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfGroup struct.\n")),
                  __FUNCTION__);
                group = NULL;
        }
        else
        {
                memset (group, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c GROUP
 * object.
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
DxfGroup *
dxf_group_init
(
        DxfGroup *group
                /*!< DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                group = dxf_group_new ();
        }
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfGroup struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        group->id_code = 0;
        group->description = strdup ("");
        group->handle_entity_in_group = strdup ("");
        group->unnamed_flag = 0;
        group->selectability_flag = 0;
        group->dictionary_owner_soft = strdup ("");
        group->dictionary_owner_hard = strdup ("");
        group->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Free the allocated memory for a DXF \c GROUP and all it's
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
dxf_group_free
(
        DxfGroup *group
                /*!< Pointer to the memory occupied by the DXF
                 * \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfGroup was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (group->dictionary_owner_soft);
        free (group->dictionary_owner_hard);
        free (group->description);
        free (group->handle_entity_in_group);
        free (group);
        group = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
