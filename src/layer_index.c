/*!
 * \file layer_index.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF layer_index object (\c LAYER_INDEX).
 *
 * \version The \c LAYER_INDEX object was introduced in DXF R14.
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


#include "layer_index.h"


/*!
 * \brief Allocate memory for a \c DxfLayerIndex.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfLayerIndex *
dxf_layer_index_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLayerIndex *layer_index = NULL;
        size_t size;

        size = sizeof (DxfLayerIndex);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((layer_index = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLayerIndex struct.\n")),
                  __FUNCTION__);
                layer_index = NULL;
        }
        else
        {
                memset (layer_index, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c LAYER_INDEX
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
DxfLayerIndex *
dxf_layer_index_init
(
        DxfLayerIndex *layer_index
                /*!< DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer_index = dxf_layer_index_new ();
        }
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLayerIndex struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer_index->id_code = 0;
        layer_index->dictionary_owner_soft = strdup ("");
        layer_index->dictionary_owner_hard = strdup ("");
        layer_index->time_stamp = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                layer_index->layer_name[i] = strdup ("");
                layer_index->number_of_entries[i] = 0;
                layer_index->hard_owner_reference[i] = strdup ("");
        }
        layer_index->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Free the allocated memory for a DXF \c LAYER_INDEX and all it's
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
dxf_layer_index_free
(
        DxfLayerIndex *layer_index
                /*!< Pointer to the memory occupied by the DXF
                 * \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (layer_index->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfLayerIndex was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (layer_index->dictionary_owner_soft);
        free (layer_index->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (layer_index->layer_name[i]);
                free (layer_index->hard_owner_reference[i]);
        }
        free (layer_index);
        layer_index = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
