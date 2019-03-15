/*!
 * \file rtext.c
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF rtext entity (\c RTEXT).
 *
 * \version According to DXF R15.
 * \version According to DXF R2000.
 *
 * \since Introduced in version R15.
 *
 * \deprecated As of version R2002.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#include "rtext.h"


/*!
 * \brief Allocate memory for a \c DxfRText.
 *
 * Fill the memory contents with zeros.
 */
DxfRText *
dxf_rtext_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfRText *rtext = NULL;
        size_t size;

        size = sizeof (DxfRText);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((rtext = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRText struct.\n")),
                  __FUNCTION__);
                rtext = NULL;
        }
        else
        {
                memset (rtext, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c RTEXT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfRText *
dxf_rtext_init
(
        DxfRText *rtext
                /*!< a pointer to the DXF \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                rtext = dxf_rtext_new ();
        }
        if (rtext == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfRText struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        rtext->id_code = 0;
        rtext->linetype = strdup (DXF_DEFAULT_LINETYPE);
        rtext->layer = strdup (DXF_DEFAULT_LAYER);
        rtext->elevation = 0.0;
        rtext->thickness = 0.0;
        rtext->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        rtext->visibility = DXF_DEFAULT_VISIBILITY;
        rtext->color = DXF_COLOR_BYLAYER;
        rtext->paperspace = DXF_MODELSPACE;
        rtext->graphics_data_size = 0;
        rtext->shadow_mode = 0;
        rtext->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        rtext->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) rtext->binary_graphics_data);
        rtext->dictionary_owner_soft = strdup ("");
        rtext->material = strdup ("");
        rtext->dictionary_owner_hard = strdup ("");
        rtext->lineweight = 0;
        rtext->plot_style_name = strdup ("");
        rtext->color_value = 0;
        rtext->color_name = strdup ("");
        rtext->transparency = 0;
        rtext->text_value = strdup ("");
        rtext->text_style = strdup ("");
        rtext->p0 = (DxfPoint *) dxf_point_new ();
        rtext->p0 = dxf_point_init ((DxfPoint *) rtext->p0);
        rtext->p0->x0 = 0.0;
        rtext->p0->y0 = 0.0;
        rtext->p0->z0 = 0.0;
        rtext->height = 0.0;
        rtext->rot_angle = 0.0;
        rtext->type_flags = 0;
        rtext->extr_x0 = 0.0;
        rtext->extr_y0 = 0.0;
        rtext->extr_z0 = 0.0;
        rtext->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (rtext);
}


/*!
 * \brief Free the allocated memory for a DXF \c RTEXT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_rtext_free
(
        DxfRText *rtext
                /*!< a pointer to the memory occupied by the DXF
                 * \c RTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (rtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (rtext->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (rtext->linetype);
        free (rtext->layer);
        dxf_binary_graphics_data_free_list (rtext->binary_graphics_data);
        free (rtext->dictionary_owner_soft);
        free (rtext->material);
        free (rtext->dictionary_owner_hard);
        free (rtext->plot_style_name);
        free (rtext->color_name);
        free (rtext->text_value);
        free (rtext->text_style);
        dxf_point_free (rtext->p0);
        free (rtext);
        rtext = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
