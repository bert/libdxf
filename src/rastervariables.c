/*!
 * \file rastervariables.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF rastervariables object (\c RASTERVARIABLES).
 *
 * \version The \c RASTERVARIABLES object was introduced in DXF R14.
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


#include "rastervariables.h"


/*!
 * \brief Allocate memory for a \c DxfRasterVariables.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfRasterVariables *
dxf_rastervariables_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfRasterVariables *rastervariables = NULL;
        size_t size;

        size = sizeof (DxfRasterVariables);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((rastervariables = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRasterVariables struct.\n")),
                  __FUNCTION__);
                rastervariables = NULL;
        }
        else
        {
                memset (rastervariables, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rastervariables);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c RASTERVARIABLES
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
DxfRasterVariables *
dxf_rastervariables_init
(
        DxfRasterVariables *rastervariables
                /*!< DXF \c RASTERVARIABLES object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rastervariables == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                rastervariables = dxf_rastervariables_new ();
        }
        if (rastervariables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRasterVariables struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        rastervariables->id_code = 0;
        rastervariables->dictionary_owner_soft = strdup ("");
        rastervariables->dictionary_owner_hard = strdup ("");
        rastervariables->display_image_frame = 0;
        rastervariables->display_quality = 0;
        rastervariables->units = 0;
        rastervariables->class_version = 0;
        rastervariables->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rastervariables);
}


/* EOF*/
