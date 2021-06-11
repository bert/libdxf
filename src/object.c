/*!
 * \file object.c
 *
 * \author Copyright (C) 2009, 2010, 2012, 2014, 2015, 2017, 2018, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for DXF objects.
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


#include "object.h"


/*!
 * \brief Allocate memory for a DXF \c object.
 *
 * Fill the memory contents with zeros.
 */
DxfObject *
dxf_object_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfObject *object = NULL;
        size_t size;

        size = sizeof (DxfObject);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((object = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfObject struct.\n")),
                  __FUNCTION__);
                object = NULL;
        }
        else
        {
                memset (object, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c OBJECT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfObject *
dxf_object_init
(
        DxfObject *object
                /*!< DXF object entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (object == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                object = dxf_object_new ();
        }
        if (object == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfObject struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        object->entity_type = UNKNOWN_ENTITY;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                /*! \todo Add code for initialising a DxfParam. */
        }
        object->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object);
}


/*!
 * \brief Write DXF output to a file for a table of objects.
 *
 * Appears only in \c TABLES section.\n
 */
int
dxf_object_write_objects
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfObject *dxf_objects_list
                /*!< Pointer to a list of DXF objects. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /*! \todo Add code here. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c object and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_object_free
(
        DxfObject *object
                /*!< Pointer to the memory occupied by the DXF \c object
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (object->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (object);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c objects and all their data fields.
 *
 */
void
dxf_object_free_list
(
        DxfObject *objects
                /*!< a pointer to the single linked list of DXF
                 * \c objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (objects == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (objects != NULL)
        {
                DxfObject *iter = (DxfObject *) objects->next;
                dxf_object_free (objects);
                objects = (DxfObject *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c entity_type from a DXF \c OBJECT entity.
 *
 * \return \c entity_type.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfEntityType *
dxf_object_get_entity_type
(
        DxfObject *object
                /*!< a pointer to a DXF \c OBJECT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object->entity_type == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfEntityType *) object->entity_type);
}


/*!
 * \brief Set the \c entity_type to the DXF \c OBJECT entity.
 */
DxfObject *
dxf_object_set_entity_type
(
        DxfObject *object,
                /*!< an DXF \c OBJECT entity. */
        DxfEntityType entity_type
                /*!< a pointer to the \c entity_type for the DXF
                 * \c OBJECT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_type == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        object->entity_type = entity_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object);
}


/*!
 * \brief Get the pointer to the next \c OBJECT entity from a DXF
 * \c OBJECT entity.
 *
 * \return pointer to the next \c OBJECT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfObject *
dxf_object_get_next
(
        DxfObject *object
                /*!< a pointer to a DXF \c OBJECT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfObject *) object->next);
}


/*!
 * \brief Set the pointer to the next \c OBJECT for a DXF \c OBJECT
 * entity.
 */
DxfObject *
dxf_object_set_next
(
        DxfObject *object,
                /*!< a pointer to a DXF \c OBJECT entity. */
        DxfObject *next
                /*!< a pointer to the next \c OBJECT for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object == NULL)
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
        object->next = (struct DxfObject *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (object);
}


/*!
 * \brief Get the pointer to the last \c OBJECT entity from a linked
 * list of DXF \c OBJECT entities.
 *
 * \return pointer to the last \c OBJECT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfObject *
dxf_object_get_last
(
        DxfObject *object
                /*!< a pointer to a DXF \c OBJECT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (object == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfObject *) object);
        }
        DxfObject *iter = (DxfObject *) object->next;
        while (iter->next != NULL)
        {
                iter = (DxfObject *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfObject *) iter);
}


/* EOF */
