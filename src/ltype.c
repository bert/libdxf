/*!
 * \file ltype.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ltype_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfLType *dxf_ltype = NULL;
        size_t size;

        size = sizeof (DxfLType);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_ltype = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_ltype_new () could not allocate memory for a DxfArc struct.\n");
                dxf_ltype = NULL;
        }
        else
        {
                memset (dxf_ltype, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ltype_new () function.\n",
                __FILE__, __LINE__);
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ltype_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        dxf_ltype = dxf_ltype_new ();
        if (dxf_ltype == NULL)
        {
              fprintf (stderr, "ERROR in dxf_ltype_init () could not allocate memory for a DxfLType struct.\n");
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
        dxf_ltype->acad_version_number = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_arc_init () function.\n",
                __FILE__, __LINE__);
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
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfLType dxf_ltype
                /*!< DXF ltype entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ltype_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LTYPE");
        int i;

        /* Test for spoilers. */
        if (strcmp (dxf_ltype.linetype_name, "") == 0)
        {
                fprintf (stderr, "Warning: empty linetype name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_ltype.id_code);
                fprintf (stderr, "    %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* No spoilers found, write available data to file. */
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ltype.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_ltype.id_code);
        }
        if (dxf_ltype.acad_version_number >= AutoCAD_14)
        {
                fprintf (fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp, "100\nAcDbLinetypeTableRecord\n");
        }
        fprintf (fp, "  2\n%s\n", dxf_ltype.linetype_name);
        fprintf (fp, " 70\n%d\n", dxf_ltype.flag);
        if (dxf_ltype.description)
        {
                fprintf (fp, "  3\n%s\n", dxf_ltype.description);
        }
        else
        {
                fprintf (fp, "  3\n\n");
        }
        fprintf (fp, " 72\n%d\n", dxf_ltype.alignment);
        fprintf (fp, " 73\n%d\n", dxf_ltype.number_of_dash_length_items);
        fprintf (fp, " 40\n%f\n", dxf_ltype.total_pattern_length);
        for ((i = 1); (i <= dxf_ltype.number_of_dash_length_items); i++)
        {
                fprintf (fp, " 49\n%f\n", dxf_ltype.dash_length[i]);
                fprintf (fp, " 74\n%d\n", dxf_ltype.complex_element[i]);
                switch (dxf_ltype.complex_element[i])
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
                                fprintf (fp, "  9\n%s\n", dxf_ltype.complex_text_string[i]);
                                fprintf (fp, " 44\n%f\n", dxf_ltype.complex_x_offset[i]);
                                fprintf (fp, " 45\n%f\n", dxf_ltype.complex_y_offset[i]);
                                fprintf (fp, " 46\n%f\n", dxf_ltype.complex_scale[i]);
                                fprintf (fp, " 50\n%f\n", dxf_ltype.complex_rotation[i]);
                                fprintf (fp, " 75\n0\n");
                                fprintf (fp, "340\n%s\n", dxf_ltype.complex_style_pointer[i]);
                                break;
                        case 3:
                                /*
                                 * The complex is a text string.
                                 * Use an absolute rotation angle.
                                 */
                                fprintf (fp, "  9\n%s\n", dxf_ltype.complex_text_string[i]);
                                fprintf (fp, " 44\n%f\n", dxf_ltype.complex_x_offset[i]);
                                fprintf (fp, " 45\n%f\n", dxf_ltype.complex_y_offset[i]);
                                fprintf (fp, " 46\n%f\n", dxf_ltype.complex_scale[i]);
                                fprintf (fp, " 50\n%f\n", dxf_ltype.complex_rotation[i]);
                                fprintf (fp, " 75\n0\n");
                                fprintf (fp, "340\n%s\n", dxf_ltype.complex_style_pointer[i]);
                                break;
                        case 4:
                                /*
                                 * The complex is a shape.
                                 * Use a relative rotation angle.
                                 */
                                fprintf (fp, " 44\n%f\n", dxf_ltype.complex_x_offset[i]);
                                fprintf (fp, " 45\n%f\n", dxf_ltype.complex_y_offset[i]);
                                fprintf (fp, " 46\n%f\n", dxf_ltype.complex_scale[i]);
                                fprintf (fp, " 50\n%f\n", dxf_ltype.complex_rotation[i]);
                                fprintf (fp, " 75\n%d\n", dxf_ltype.complex_shape_number[i]);
                                fprintf (fp, "340\n%s\n", dxf_ltype.complex_style_pointer[i]);
                                break;
                        case 5:
                                /*
                                 * The complex is a shape.
                                 * Use an absolute rotation angle.
                                 */
                                fprintf (fp, " 44\n%f\n", dxf_ltype.complex_x_offset[i]);
                                fprintf (fp, " 45\n%f\n", dxf_ltype.complex_y_offset[i]);
                                fprintf (fp, " 46\n%f\n", dxf_ltype.complex_scale[i]);
                                fprintf (fp, " 50\n%f\n", dxf_ltype.complex_rotation[i]);
                                fprintf (fp, " 75\n%d\n", dxf_ltype.complex_shape_number[i]);
                                fprintf (fp, "340\n%s\n", dxf_ltype.complex_style_pointer[i]);
                                break;
                        default:
                                fprintf (stderr, "Warning: unknown complex element code for the %s entity with id-code: %x\n",
                                        dxf_entity_name, dxf_ltype.id_code);
                                break;
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ltype_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a \c LTYPE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ltype_write_lowlevel
(
        FILE *fp,
                /*!< File pointer to output file (or device). */
        int id_code,
                /*!< group code = 5.\n
                 * Entity handle; text string of up to 16 hexadecimal
                 * digits (fixed) */
        char *linetype_name,
                /*!< group code = 2. */
        char *description,
                /*!< group code = 3. */
        int flag,
                /*!< group code = 70\n
                 * bit coded:\n
                 * 16 = if set, table entry is externally dependent on an
                 *      Xref\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved\n
                 * 64 = if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.\n
                 * This flag is for the benefit of AutoCAD commands; it can
                 * be ignored by most programs that read DXF files, and need
                 * not be set by programs that write DXF files. */
        int alignment,
                /*!< group code = 72\n
                 * always 65; ASCII code for 'A'. */
        double total_pattern_length,
                /*!< group code = 40. */
        int number_of_dash_length_items,
                /*!< group code = 73. */
        char *complex_text_string[number_of_dash_length_items],
                /*!< group code = 9.\n
                 * Text string (one per element if code 74 = 2). */
        double complex_x_offset[number_of_dash_length_items],
                /*!< group code = 44.\n
                 * X offset value (optional).\n
                 * Multiple entries can exist. */
        double complex_y_offset[number_of_dash_length_items],
                /*!< group code = 45.\n
                 * Y offset value (optional).\n
                 * Multiple entries can exist. */
        double complex_scale[number_of_dash_length_items],
                /*!< group code = 46.\n
                 * Scale value (optional).\n
                 * Multiple entries can exist. */
        double dash_length[number_of_dash_length_items],
                /*!< group code = 49.\n
                 * Dash, dot or space length (one entry per element). */
        double complex_rotation[number_of_dash_length_items],
                /*!< group code = 50.\n
                 * R = (relative) or A = (absolute) rotation value in radians
                 * of embedded shape or text.\n
                 * One per element if code 74 specifies an embedded shape
                 * or text string. */
        int complex_element[number_of_dash_length_items],
                /*!< group code = 74.\n
                 * Complex linetype element type (one per element).\n
                 * Default is 0 (no embedded shape/text).\n
                 * The following codes are bit values:\n
                 * 1 = If set, group code 50 specifies an absolute
                 *     rotation; if not set, group code 50 specifies a
                 *     relative rotation.\n
                 * 2 = Embedded element is a text string.\n
                 * 4 = Embedded element is a shape. */
        int complex_shape_number[number_of_dash_length_items],
                /*!< group code = 75.\n
                 * Shape number (one per element) if code 74 specifies
                 * an embedded shape.\n
                 * If code 74 specifies an embedded text string, this
                 * value is set to 0.\n
                 * If code 74 is set to 0, code 75 is omitted. */
        char *complex_style_pointer[number_of_dash_length_items],
                /*!< group code = 340.\n
                 * Pointer to \c STYLE object.\n
                 * One per element if group code 74 > 0. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ltype_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LTYPE");
        int i;

        /* Test for spoilers. */
        if (strcmp (linetype_name, "") == 0)
        {
                fprintf (stderr, "Warning: empty linetype name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* No spoilers found, write available data to file. */
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (acad_version_number >= AutoCAD_14)
        {
                fprintf (fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp, "100\nAcDbLinetypeTableRecord\n");
        }
        fprintf (fp, "  2\n%s\n", linetype_name);
        fprintf (fp, " 70\n%d\n", flag);
        fprintf (fp, "  3\n%s\n", description);
        fprintf (fp, " 72\n%d\n", alignment);
        fprintf (fp, " 73\n%d\n", number_of_dash_length_items);
        fprintf (fp, " 40\n%f\n", total_pattern_length);
        for ((i = 1); (i <=number_of_dash_length_items); i++)
        {
                fprintf (fp, " 49\n%f\n", dash_length[i]);
                fprintf (fp, " 74\n%d\n", complex_element[i]);
                switch (complex_element[i])
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
                                fprintf (fp, "  9\n%s\n", complex_text_string[i]);
                                fprintf (fp, " 44\n%f\n", complex_x_offset[i]);
                                fprintf (fp, " 45\n%f\n", complex_y_offset[i]);
                                fprintf (fp, " 46\n%f\n", complex_scale[i]);
                                fprintf (fp, " 50\n%f\n", complex_rotation[i]);
                                fprintf (fp, " 75\n0\n");
                                fprintf (fp, "340\n%s\n", complex_style_pointer[i]);
                                break;
                        case 3:
                                /*
                                 * The complex is a text string.
                                 * Use an absolute rotation angle.
                                 */
                                fprintf (fp, "  9\n%s\n", complex_text_string[i]);
                                fprintf (fp, " 44\n%f\n", complex_x_offset[i]);
                                fprintf (fp, " 45\n%f\n", complex_y_offset[i]);
                                fprintf (fp, " 46\n%f\n", complex_scale[i]);
                                fprintf (fp, " 50\n%f\n", complex_rotation[i]);
                                fprintf (fp, " 75\n0\n");
                                fprintf (fp, "340\n%s\n", complex_style_pointer[i]);
                                break;
                        case 4:
                                /*
                                 * The complex is a shape.
                                 * Use a relative rotation angle.
                                 */
                                fprintf (fp, " 44\n%f\n", complex_x_offset[i]);
                                fprintf (fp, " 45\n%f\n", complex_y_offset[i]);
                                fprintf (fp, " 46\n%f\n", complex_scale[i]);
                                fprintf (fp, " 50\n%f\n", complex_rotation[i]);
                                fprintf (fp, " 75\n%d\n", complex_shape_number[i]);
                                fprintf (fp, "340\n%s\n", complex_style_pointer[i]);
                                break;
                        case 5:
                                /*
                                 * The complex is a shape.
                                 * Use an absolute rotation angle.
                                 */
                                fprintf (fp, " 44\n%f\n", complex_x_offset[i]);
                                fprintf (fp, " 45\n%f\n", complex_y_offset[i]);
                                fprintf (fp, " 46\n%f\n", complex_scale[i]);
                                fprintf (fp, " 50\n%f\n", complex_rotation[i]);
                                fprintf (fp, " 75\n%d\n", complex_shape_number[i]);
                                fprintf (fp, "340\n%s\n", complex_style_pointer[i]);
                                break;
                        default:
                                fprintf (stderr, "Warning: unknown complex element code for the %s entity with id-code: %x\n",
                                        dxf_entity_name, id_code);
                                break;
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ltype_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF */
