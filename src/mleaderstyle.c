/*!
 * \file mleaderstyle.c
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mleaderstyle entity (\c MLEADERSTYLE).
 *
 * \since The \c MLEADERSTYLE entity was introduced in DXF R2007.
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


#include "mleaderstyle.h"


/*!
 * \brief Allocate memory for a DXF \c MLEADERSTYLE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMLeaderstyle *mleaderstyle = NULL;
        size_t size;

        size = sizeof (DxfMLeaderstyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mleaderstyle = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                mleaderstyle = NULL;
        }
        else
        {
                memset (mleaderstyle, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c MLEADERSTYLE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMLeaderstyle *
dxf_mleaderstyle_init
(
        DxfMLeaderstyle *mleaderstyle
                /*!< a pointer to the DXF \c MLEADERSTYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mleaderstyle = dxf_mleaderstyle_new ();
        }
        if (mleaderstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mleaderstyle->id_code = 0;
        mleaderstyle->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mleaderstyle->layer = strdup (DXF_DEFAULT_LAYER);
        mleaderstyle->elevation = 0.0;
        mleaderstyle->thickness = 0.0;
        mleaderstyle->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        mleaderstyle->visibility = DXF_DEFAULT_VISIBILITY;
        mleaderstyle->color = DXF_COLOR_BYLAYER;
        mleaderstyle->paperspace = DXF_MODELSPACE;
        mleaderstyle->graphics_data_size = 0;
        mleaderstyle->shadow_mode = 0;
        mleaderstyle->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        mleaderstyle->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (mleaderstyle->binary_graphics_data);
        mleaderstyle->dictionary_owner_soft = strdup ("");
        mleaderstyle->object_owner_soft = strdup ("");
        mleaderstyle->material = strdup ("");
        mleaderstyle->dictionary_owner_hard = strdup ("");
        mleaderstyle->lineweight = 0;
        mleaderstyle->plot_style_name = strdup ("");
        mleaderstyle->color_value = 0;
        mleaderstyle->color_name = strdup ("");
        mleaderstyle->transparency = 0;
        mleaderstyle->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mleaderstyle);
}


/* EOF*/
