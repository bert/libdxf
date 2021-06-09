/*!
 * \file layer_name.c
 *
 * \author Copyright (C) 2017, 2018, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF layer name object.
 *
 * \since The \c LAYER_NAME object was introduced in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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


#include "layer_name.h"


/*!
 * \brief Allocate memory for a \c DxfLayerName.
 *
 * Fill the memory contents with zeros.
 */
DxfLayerName *
dxf_layer_name_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLayerName *layer_name = NULL;
        size_t size;

        size = sizeof (DxfLayerName);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((layer_name = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                layer_name = NULL;
        }
        else
        {
                memset (layer_name, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_name);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c LAYER_NAME
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLayerName *
dxf_layer_name_init
(
        DxfLayerName *layer_name
                /*!< DXF \c LAYER_NAME object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer_name = dxf_layer_name_new ();
        }
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer_name->name = strdup ("");
        layer_name->length = 0;
        layer_name->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_name);
}


/*!
 * \brief Free the allocated memory for a DXF \c LAYER_NAME and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_name_free
(
        DxfLayerName *layer_name
                /*!< Pointer to the memory occupied by the DXF
                 * \c LAYER_NAME object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer_name->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (layer_name->name);
        free (layer_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c LAYER_NAME objects and all their data fields.
 */
void
dxf_layer_name_free_list
(
        DxfLayerName *layer_names
                /*!< pointer to the single linked list of DXF
                 * \c LAYER_NAME objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (layer_names == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (layer_names != NULL)
        {
                DxfLayerName *iter = (DxfLayerName *) layer_names->next;
                dxf_layer_name_free (layer_names);
                layer_names = (DxfLayerName *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c name from a DXF \c LAYER_NAME object.
 *
 * \return \c name.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_layer_name_get_name
(
        DxfLayerName *layer_name
                /*!< a pointer to a DXF \c LAYER_NAME object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer_name->name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer_name->name));
}


/*!
 * \brief Set the \c name for a DXF \c LAYER_NAME object.
 */
DxfLayerName *
dxf_layer_name_set_name
(
        DxfLayerName *layer_name,
                /*!< a pointer to a DXF \c LAYER_NAME object. */
        char *name
                /*!< a string containing the \c name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer_name->name = strdup (name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_name);
}


/*!
 * \brief Get the \c length from the \c name member in a DXF
 * \c LAYER_NAME object.
 *
 * \return \c length.
 */
int
dxf_layer_name_get_length
(
        DxfLayerName *layer_name
                /*!< a pointer to a DXF \c LAYER_NAME object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer_name->length < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_name->length);
}


/*!
 * \brief Set the \c length of the \c name member for a DXF
 * \c LAYER_NAME object.
 */
DxfLayerName *
dxf_layer_name_set_length
(
        DxfLayerName *layer_name,
                /*!< a pointer to a DXF \c LAYER_NAME object. */
        int length
                /*!< \c length. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (length < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer_name->length = length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_name);
}


/*!
 * \brief Get the pointer to the next \c LAYER_NAME object from a DXF 
 * \c LAYER_NAME object.
 *
 * \return pointer to the next \c LAYER_NAME object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLayerName *
dxf_layer_name_get_next
(
        DxfLayerName *layer_name
                /*!< a pointer to a DXF \c LAYER_NAME object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer_name->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLayerName *) layer_name->next);
}


/*!
 * \brief Set the pointer to the next \c LAYER_NAME object for a DXF
 * \c LAYER_NAME object.
 */
DxfLayerName *
dxf_layer_name_set_next
(
        DxfLayerName *layer_name,
                /*!< a pointer to a DXF \c LAYER_NAME object. */
        DxfLayerName *next
                /*!< a pointer to the next \c LAYER_NAME object for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
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
        layer_name->next = (struct DxfLayerName *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_name);
}


/*!
 * \brief Get the pointer to the last \c LAYER_NAME object from a
 * linked list of DXF \c LAYER_NAME object.
 *
 * \return pointer to the last \c LAYER_NAME object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLayerName *
dxf_layer_name_get_last
(
        DxfLayerName *layer_name
                /*!< a pointer to a DXF \c LAYER_NAME object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer_name->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfLayerName *) layer_name);
        }
        DxfLayerName *iter = (DxfLayerName *) layer_name->next;
        while (iter->next != NULL)
        {
                iter = (DxfLayerName *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLayerName *) iter);
}


/* EOF */
