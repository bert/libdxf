/*!
 * \file object_id.c
 *
 * \author Copyright (C) 2016, 2017, 2018, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for DXF object ids.
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
 * For more details see http://www.autodesk.com.\n\n
 * <hr>
 */


#include "object_id.h"


/*!
 * \brief Allocate memory for a DXF \c object_id.
 *
 * Fill the memory contents with zeros.
 */
DxfObjectId *
dxf_object_id_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfObjectId *object_id = NULL;
        size_t size;

        size = sizeof (DxfObjectId);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((object_id = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfObjectId struct.\n")),
                  __FUNCTION__);
                object_id = NULL;
        }
        else
        {
                memset (object_id, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_id);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c object_id.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfObjectId *
dxf_object_id_init
(
        DxfObjectId *object_id
                /*!< DXF object_id. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                object_id = dxf_object_id_new ();
        }
        if (object_id == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfObjectId struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        object_id->data = strdup ("");
        object_id->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_id);
}


/*!
 * \brief Free the allocated memory for a DXF \c object_id and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_object_id_free
(
        DxfObjectId *object_id
                /*!< Pointer to the memory occupied by the DXF
                 * \c object_id. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (object_id->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (object_id->data);
        free (object_id);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c object_ids and all their data fields.
 */
void
dxf_object_id_free_list
(
        DxfObjectId *object_ids
                /*!< a pointer to the single linked list of DXF
                 * \c object_ids. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (object_ids == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (object_ids != NULL)
        {
                DxfObjectId *iter = (DxfObjectId *) object_ids->next;
                dxf_object_id_free (object_ids);
                object_ids = (DxfObjectId *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c group_code from a DXF \c object_id.
 *
 * \return \c group_code.
 */
int
dxf_object_id_get_group_code
(
        DxfObjectId *object_id
                /*!< a pointer to a DXF \c object_id. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((object_id->group_code != 330)
          && (object_id->group_code != 340)
          && (object_id->group_code != 350)
          && (object_id->group_code != 360))
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the group_code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_id->group_code);
}


/*!
 * \brief Set the \c group_code for a DXF \c object_id.
 *
 * \return a pointer to \c object_id when sucessful, \c NULL when an error
 * occurred.
 */
DxfObjectId *
dxf_object_id_set_group_code
(
        DxfObjectId *object_id,
                /*!< a pointer to a DXF \c object_id. */
        int group_code
                /*!< the \c group_code to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((group_code != 330)
          && (group_code != 340)
          && (group_code != 350)
          && (group_code != 360))
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid group_code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_id->group_code = group_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_id);
}


/*!
 * \brief Get the \c data from a DXF \c object_id.
 *
 * \return \c data when sucessful, \c NULL when an error occurred.
 */
char *
dxf_object_id_get_data
(
        DxfObjectId *object_id
                /*!< a pointer to a DXF \c object_id. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_id->data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the data member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (object_id->data));
}


/*!
 * \brief Set the \c data for a DXF \c object_id.
 */
DxfObjectId *
dxf_object_id_set_data
(
        DxfObjectId *object_id,
                /*!< a pointer to a DXF \c object_id. */
        char *data
                /*!< a string containing the \c data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_id->data = strdup (data);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_id);
}


/*!
 * \brief Get the \c length from a DXF \c object_id.
 *
 * \return \c length.
 */
int
dxf_object_id_get_length
(
        DxfObjectId *object_id
                /*!< a pointer to a DXF \c object_id. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (object_id->length < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the length member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_id->length);
}


/*!
 * \brief Set the \c length for a DXF \c object_id.
 *
 * \return a pointer to \c object_id when sucessful, \c NULL when an error
 * occurred.
 */
DxfObjectId *
dxf_object_id_set_length
(
        DxfObjectId *object_id,
                /*!< a pointer to a DXF \c object_id. */
        int length
                /*!< Length to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (length < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative length value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_id->length = length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_id);
}


/*!
 * \brief Get the pointer to the next DXF \c object_id from a DXF
 * \c object_id.
 *
 * \return pointer to the next \c object_id.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfObjectId *
dxf_object_id_get_next
(
        DxfObjectId *object_id
                /*!< a pointer to a DXF \ object_id. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_id->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfObjectId *) object_id->next);
}


/*!
 * \brief Set the pointer to the next DXF \c object_id for a DXF
 * \c object_id.
 */
DxfObjectId *
dxf_object_id_set_next
(
        DxfObjectId *object_id,
                /*!< a pointer to a DXF \c object_id. */
        DxfObjectId *next
                /*!< a pointer to the next DXF \c object_id for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object_id->next = (struct DxfObjectId *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object_id);
}


/*!
 * \brief Get the pointer to the last DXF \c object_id from a linked
 * list of DXF \c object_id.
 *
 * \return pointer to the last \c object_id.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfObjectId *
dxf_object_id_get_last
(
        DxfObjectId *object_id
                /*!< a pointer to a DXF \ object_id. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_id->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfObjectId *) object_id);
        }
        DxfObjectId *iter = (DxfObjectId *) object_id->next;
        while (iter->next != NULL)
        {
                iter = (DxfObjectId *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfObjectId *) iter);
}


/* EOF */
