/*!
 * \file ltype.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF ltype entity.
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


#include "ltype.h"


/*!
 * \brief Allocate memory for a \c DxfLType.
 *
 * Fill the memory contents with zeros.
 */
DxfLType *
dxf_ltype_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLType *dxf_ltype = NULL;
        size_t size;

        size = sizeof (DxfLType);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_ltype = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfArc struct.\n")),
                  __FUNCTION__);
                dxf_ltype = NULL;
        }
        else
        {
                memset (dxf_ltype, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ltype);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c LTYPE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLType *
dxf_ltype_init
(
        DxfLType *dxf_ltype
                /*!< DXF LType entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        dxf_ltype = dxf_ltype_new ();
        if (dxf_ltype == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a DxfLType struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_ltype->id_code = 0;
        dxf_ltype->linetype_name = strdup ("");
        dxf_ltype->description = strdup ("");
        dxf_ltype->total_pattern_length = 0.0;
        dxf_ltype->number_of_dash_length_items = 1;
        for ((i = 1); (i <= dxf_ltype->number_of_dash_length_items); i++)
        {
                dxf_ltype->dash_length[i] = 0.0;
        }
        dxf_ltype->flag = 0;
        dxf_ltype->alignment = 65;
        dxf_ltype->number_of_dash_length_items = 1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ltype);
}


/*!
 * \brief Write DXF output to a file for a \c LTYPE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ltype_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLType *dxf_ltype
                /*!< DXF ltype entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LTYPE");
        int i;

        /* Do some basic checks. */
        if (dxf_ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_ltype->linetype_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s (): empty linetype name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_ltype->id_code);
                fprintf (stderr,
                  (_("    %s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ltype->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_ltype->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbLinetypeTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_ltype->linetype_name);
        fprintf (fp->fp, " 70\n%d\n", dxf_ltype->flag);
        if (dxf_ltype->description)
        {
                fprintf (fp->fp, "  3\n%s\n", dxf_ltype->description);
        }
        else
        {
                fprintf (fp->fp, "  3\n\n");
        }
        fprintf (fp->fp, " 72\n%d\n", dxf_ltype->alignment);
        fprintf (fp->fp, " 73\n%d\n", dxf_ltype->number_of_dash_length_items);
        fprintf (fp->fp, " 40\n%f\n", dxf_ltype->total_pattern_length);
        for ((i = 1); (i <= dxf_ltype->number_of_dash_length_items); i++)
        {
                fprintf (fp->fp, " 49\n%f\n", dxf_ltype->dash_length[i]);
                fprintf (fp->fp, " 74\n%d\n", dxf_ltype->complex_element[i]);
                switch (dxf_ltype->complex_element[i])
                {
                        case 0:
                                /* No embedded shape/text. */
                                break;
                        case 1:
                                /* Specify an absolute rotation. */
                                break;
                        case 2:
                                /*
                                 * The complex is a text string.
                                 * Use a relative rotation angle.
                                 */
                                fprintf (fp->fp, "  9\n%s\n", dxf_ltype->complex_text_string[i]);
                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype->complex_x_offset[i]);
                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype->complex_y_offset[i]);
                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype->complex_scale[i]);
                                fprintf (fp->fp, " 50\n%f\n", dxf_ltype->complex_rotation[i]);
                                fprintf (fp->fp, " 75\n0\n");
                                fprintf (fp->fp, "340\n%s\n", dxf_ltype->complex_style_pointer[i]);
                                break;
                        case 3:
                                /*
                                 * The complex is a text string.
                                 * Use an absolute rotation angle.
                                 */
                                fprintf (fp->fp, "  9\n%s\n", dxf_ltype->complex_text_string[i]);
                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype->complex_x_offset[i]);
                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype->complex_y_offset[i]);
                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype->complex_scale[i]);
                                fprintf (fp->fp, " 50\n%f\n", dxf_ltype->complex_rotation[i]);
                                fprintf (fp->fp, " 75\n0\n");
                                fprintf (fp->fp, "340\n%s\n", dxf_ltype->complex_style_pointer[i]);
                                break;
                        case 4:
                                /*
                                 * The complex is a shape.
                                 * Use a relative rotation angle.
                                 */
                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype->complex_x_offset[i]);
                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype->complex_y_offset[i]);
                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype->complex_scale[i]);
                                fprintf (fp->fp, " 50\n%f\n", dxf_ltype->complex_rotation[i]);
                                fprintf (fp->fp, " 75\n%d\n", dxf_ltype->complex_shape_number[i]);
                                fprintf (fp->fp, "340\n%s\n", dxf_ltype->complex_style_pointer[i]);
                                break;
                        case 5:
                                /*
                                 * The complex is a shape.
                                 * Use an absolute rotation angle.
                                 */
                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype->complex_x_offset[i]);
                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype->complex_y_offset[i]);
                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype->complex_scale[i]);
                                fprintf (fp->fp, " 50\n%f\n", dxf_ltype->complex_rotation[i]);
                                fprintf (fp->fp, " 75\n%d\n", dxf_ltype->complex_shape_number[i]);
                                fprintf (fp->fp, "340\n%s\n", dxf_ltype->complex_style_pointer[i]);
                                break;
                        default:
                                fprintf (stderr,
                                  (_("Warning in %s (): unknown complex element code for the %s entity with id-code: %x\n")),
                                  __FUNCTION__, dxf_entity_name, dxf_ltype->id_code);
                                break;
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LTYPE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ltype_free
(
        DxfLType *dxf_ltype
                /*!< Pointer to the memory occupied by the DXF \c LTYPE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_ltype->next != NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () pointer to next DxfLType was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_ltype->linetype_name);
        free (dxf_ltype->description);
        for ((i = 0); (i <= dxf_ltype->number_of_dash_length_items); i++)
        {
                dxf_ltype->complex_text_string[i] = NULL;
                dxf_ltype->complex_style_pointer[i] = NULL;
        }
        free (dxf_ltype);
        dxf_ltype = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
