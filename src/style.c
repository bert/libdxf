/*!
 * \file style.c
 *
 * \author Copyright (C) 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF style entity (\c STYLE).
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


#include "style.h"


/*!
 * \brief Allocate memory for a DXF \c STYLE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfStyle *
dxf_style_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfStyle *dxf_style = NULL;
        size_t size;

        size = sizeof (DxfStyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_style = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfStyle struct.\n")),
                  __FUNCTION__);
                dxf_style = NULL;
        }
        else
        {
                memset (dxf_style, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_style);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c STYLE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfStyle *
dxf_style_init
(
        DxfStyle *dxf_style
                /*!< DXF style entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_style == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_style = dxf_style_new ();
        }
        if (dxf_style == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfStyle struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_style->id_code = 0;
        dxf_style->style_name = strdup ("");
        dxf_style->primary_font_filename = strdup ("");
        dxf_style->big_font_filename = strdup ("");
        dxf_style->height = 0.0;
        dxf_style->width = 0.0;
        dxf_style->last_height = 0.0;
        dxf_style->oblique_angle = 0.0;
        dxf_style->flag = 0;
        dxf_style->text_generation_flag = 0;
        dxf_style->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_style);
}


/*!
 * \brief Write DXF output for a DXF \c STYLE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_style_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfStyle *dxf_style
                /*!< DXF \c STYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("STYLE");

        /* Do some basic checks. */
        if (dxf_style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_style->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_style->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (dxf_style->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_style->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_style->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_style->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbTextStyleTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_style->style_name);
        fprintf (fp->fp, " 70\n%d\n", dxf_style->flag);
        fprintf (fp->fp, " 40\n%f\n", dxf_style->height);
        fprintf (fp->fp, " 41\n%f\n", dxf_style->width);
        fprintf (fp->fp, " 50\n%f\n", dxf_style->oblique_angle);
        fprintf (fp->fp, " 71\n%d\n", dxf_style->text_generation_flag);
        fprintf (fp->fp, " 42\n%f\n", dxf_style->last_height);
        fprintf (fp->fp, "  3\n%s\n", dxf_style->primary_font_filename);
        fprintf (fp->fp, "  4\n%s\n", dxf_style->big_font_filename);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c STYLE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_style_free
(
        DxfStyle *dxf_style
                /*!< Pointer to the memory occupied by the DXF \c STYLE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_style->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfStyle was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_style->style_name);
        free (dxf_style->primary_font_filename);
        free (dxf_style->big_font_filename);
        free (dxf_style);
        dxf_style = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
