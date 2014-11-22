/*!
 * \file object.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        DxfObject *dxf_object = NULL;
        size_t size;

        size = sizeof (DxfObject);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_object = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfObject struct.\n")),
                  __FUNCTION__);
                dxf_object = NULL;
        }
        else
        {
                memset (dxf_object, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_object);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c OBJECT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfObject *
dxf_object_init
(
        DxfObject *dxf_object
                /*!< DXF object entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (dxf_object == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_object = dxf_object_new ();
        }
        if (dxf_object == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfObject struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_object->entity_type = UNKNOWN_ENTITY;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                /*! \todo Add code for initialising a DxfParam. */
        }
        dxf_object->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_object);
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
        DxfObject *dxf_object
                /*!< Pointer to the memory occupied by the DXF \c object
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_object->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfObject was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_object);
        dxf_object = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
