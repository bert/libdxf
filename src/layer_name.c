/*!
 * \file layer_name.c
 *
 * \author Copyright (C) 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * allocated memory when succesful.
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


/* EOF */
