/*!
 * \file ltype.c
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015, 2017, 2018, 2019, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF ltype symbol table entry (\c LTYPE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
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
        DxfLType *ltype = NULL;
        size_t size;

        size = sizeof (DxfLType);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ltype = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfArc struct.\n")),
                  __FUNCTION__);
                ltype = NULL;
        }
        else
        {
                memset (ltype, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Allocate memory and initialize data fields for a DXF \c LTYPE
 * symbol table entry.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLType *
dxf_ltype_init
(
        DxfLType *ltype
                /*!< a pointer to the DXF \c LTYPE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ltype = dxf_ltype_new ();
        }
        if (ltype == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfLType struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        ltype->id_code = 0;
        ltype->linetype_name = strdup ("");
        ltype->description = strdup ("");
        ltype->total_pattern_length = 0.0;
        ltype->number_of_linetype_elements = 0;
        ltype->flag = 0;
        ltype->alignment = 65;
        ltype->dictionary_owner_soft = strdup ("");
        ltype->dictionary_owner_hard = strdup ("");
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        ltype->complex_text_string = NULL;
        ltype->complex_x_offset = NULL;
        ltype->complex_y_offset = NULL;
        ltype->complex_scale = NULL;
        ltype->dash_length = NULL;
        ltype->complex_rotation = NULL;
        ltype->complex_element = NULL;
        ltype->complex_shape_number = NULL;
        ltype->complex_style_pointer = NULL;
        ltype->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LTYPE symbol table entry.
 *
 * The last line read from file contained the string "LTYPE". \n
 * Now follows some data for the \c LTYPE, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c ltype. \n
 *
 * \return a pointer to \c ltype.
 */
DxfLType *
dxf_ltype_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLType *ltype
                /*!< a pointer to the DXF \c LTYPE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int element;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ltype = dxf_ltype_init (ltype);
        }
        element = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &ltype->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ltype->linetype_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a description. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ltype->description);
                }
                else if (strcmp (temp_string, "9") == 0)
                {
                        /* Now follows a string containing a complex
                         * text string (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ltype->complex_text_string->value);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the total
                         * pattern length value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ltype->total_pattern_length);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing a complex
                         * x offset value (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
//                        fscanf (fp->fp, "%lf\n", ltype->complex_x_offset);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing a complex
                         * y offset value (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
//                        fscanf (fp->fp, "%lf\n", &ltype->complex_y_offset);
                }
                else if (strcmp (temp_string, "46") == 0)
                {
                        /* Now follows a string containing a complex
                         * scale value (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
//                        fscanf (fp->fp, "%lf\n", &ltype->complex_scale);
                }
                else if (strcmp (temp_string, "49") == 0)
                {
                        /* Now follows a string containing a dash length
                         * value (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
//                        fscanf (fp->fp, "%lf\n", &ltype->dash_length);
//                        element++;
                        /*! \todo We are assuming that 49 is the first
                         * group code that is encountered for each
                         * element in the linetype definition.\n
                         * This assumption breaks the "rule" of parsing
                         * the dxf file regardless the order in which
                         * group codes appear within an entity.
                         */
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing a complex
                         * rotation value (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
//                        fscanf (fp->fp, "%lf\n", &ltype->complex_rotation);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ltype->flag);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ltype->alignment);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the number of
                         * dash length items value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ltype->number_of_linetype_elements);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing a complex
                         * element value (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
//                        fscanf (fp->fp, "%d\n", &ltype->complex_element);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing a complex
                         * element value (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
//                        fscanf (fp->fp, "%d\n", &ltype->complex_shape_number[element]);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ltype->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a complex
                         * style pointer string (multiple entries possible). */
                        (fp->line_number)++;
                        /*! \todo add code for proper implementation. */
//                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ltype->complex_style_pointer[element]);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ltype->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (ltype->linetype_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s (): empty linetype name string for the entity with id-code: %x\n")),
                  __FUNCTION__, ltype->id_code);
                fprintf (stderr,
                  (_("\tentity is discarded from output.\n")));
                return (NULL);
        }
        if (ltype->alignment != 65)
        {
                ltype->alignment = 65;
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Write DXF output to a file for a \c LTYPE symbol table entry.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ltype_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLType *ltype
                /*!< a pointer to the DXF \c LTYPE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LTYPE");
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (ltype->linetype_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s (): empty linetype name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ltype->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (ltype->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", ltype->id_code);
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
        if ((strcmp (ltype->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", ltype->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (ltype->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", ltype->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbLinetypeTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", ltype->linetype_name);
        fprintf (fp->fp, " 70\n%d\n", ltype->flag);
        if (ltype->description)
        {
                fprintf (fp->fp, "  3\n%s\n", ltype->description);
        }
        else
        {
                fprintf (fp->fp, "  3\n\n");
        }
        fprintf (fp->fp, " 72\n%d\n", ltype->alignment);
        fprintf (fp->fp, " 73\n%d\n", ltype->number_of_linetype_elements);
        fprintf (fp->fp, " 40\n%f\n", ltype->total_pattern_length);
        for ((i = 0); (i < ltype->number_of_linetype_elements); i++)
        {
                                /*! \todo add code for a proper implementation. */
//                fprintf (fp->fp, " 49\n%f\n", dxf_ltype_get_dash_length (ltype, i));
//                fprintf (fp->fp, " 74\n%d\n", dxf_ltype_get_complex_element (ltype, i));
                switch (ltype->complex_element->value)
                {
                        case 0:
                                /* No embedded shape/text. */
                                /*! \todo add code for a proper implementation. */
//                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype_get_complex_x_offset (ltype, i));
//                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype_get_complex_y_offset (ltype, i));
//                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype_get_complex_scale (ltype, i));
//                                fprintf (fp->fp, " 75\n0\n");
                                break;
                        case 1:
                                /* Specify an absolute rotation. */
                                /*! \todo add code for a proper implementation. */
//                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype_get_complex_x_offset (ltype, i));
//                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype_get_complex_y_offset (ltype, i));
//                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype_get_complex_scale (ltype, i));
//                                fprintf (fp->fp, " 75\n0\n");
//                                fprintf (fp->fp, "340\n%s\n", dxf_ltype_get_complex_style_pointer (ltype, i));
                                break;
                        case 2:
                                /*
                                 * The complex is a text string.
                                 * Use a relative rotation angle.
                                 */
                                /*! \todo add code for a proper implementation. */
//                                fprintf (fp->fp, "  9\n%s\n", ltype->get_complex_text_string->value;
//                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype_get_complex_x_offset (ltype, i));
//                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype_get_complex_y_offset (ltype, i));
//                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype_get_complex_scale (ltype, i));
//                                fprintf (fp->fp, " 50\n%f\n", dxf_ltype_get_complex_rotation (ltype, i));
//                                fprintf (fp->fp, " 75\n0\n");
//                                fprintf (fp->fp, "340\n%s\n", dxf_ltype_get_complex_style_pointer (ltype, i));
                                break;
                        case 3:
                                /*
                                 * The complex is a text string.
                                 * Use an absolute rotation angle.
                                 */
                                /*! \todo add code for a proper implementation. */
//                                fprintf (fp->fp, "  9\n%s\n", ltype->get_complex_text_string->value;
//                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype_get_complex_x_offset (ltype, i));
//                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype_get_complex_y_offset (ltype, i));
//                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype_get_complex_scale (ltype, i));
//                                fprintf (fp->fp, " 50\n%f\n", dxf_ltype_get_complex_rotation (ltype, i));
//                                fprintf (fp->fp, " 75\n0\n");
//                                fprintf (fp->fp, "340\n%s\n", dxf_ltype_get_complex_style_pointer (ltype, i));
                                break;
                        case 4:
                                /*
                                 * The complex is a shape.
                                 * Use a relative rotation angle.
                                 */
                                /*! \todo add code for a proper implementation. */
//                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype_get_complex_x_offset (ltype, i));
//                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype_get_complex_y_offset (ltype, i));
//                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype_get_complex_scale (ltype, i));
//                                fprintf (fp->fp, " 50\n%f\n", dxf_ltype_get_complex_rotation (ltype, i));
//                                fprintf (fp->fp, " 75\n%d\n", dxf_ltype_get_complex_shape_number (ltype, i));
//                                fprintf (fp->fp, "340\n%s\n", dxf_ltype_get_complex_style_pointer (ltype, i));
                                break;
                        case 5:
                                /*
                                 * The complex is a shape.
                                 * Use an absolute rotation angle.
                                 */
                                /*! \todo add code for a proper implementation. */
//                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype_get_complex_x_offset (ltype, i));
//                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype_get_complex_y_offset (ltype, i));
//                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype_get_complex_scale (ltype, i));
//                                fprintf (fp->fp, " 50\n%f\n", dxf_ltype_get_complex_rotation (ltype, i));
//                                fprintf (fp->fp, " 75\n%d\n", dxf_ltype_get_complex_shape_number (ltype, i));
//                                fprintf (fp->fp, "340\n%s\n", dxf_ltype_get_complex_style_pointer (ltype, i));
                                break;
                        default:
                                fprintf (stderr,
                                  (_("Warning in %s (): unknown complex element code for the %s entity with id-code: %x\n")),
                                  __FUNCTION__, dxf_entity_name, ltype->id_code);
                                break;
                }
        }
        /* Clean up. */
        free (dxf_entity_name);
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
        DxfLType *ltype
                /*!< a pointer to the memory occupied by the DXF \c LTYPE
                 * symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ltype->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (ltype->linetype_name);
        free (ltype->description);
        free (ltype->complex_style_pointer);
        free (ltype->dictionary_owner_soft);
        free (ltype->dictionary_owner_hard);
        dxf_char_free_list (ltype->complex_text_string);
        dxf_double_free_list (ltype->complex_x_offset);
        dxf_double_free_list (ltype->complex_y_offset);
        dxf_double_free_list (ltype->complex_scale);
        dxf_double_free_list (ltype->dash_length);
        dxf_double_free_list (ltype->complex_rotation);
        dxf_int16_free_list (ltype->complex_element);
        dxf_int16_free_list (ltype->complex_shape_number);
        dxf_char_free_list (ltype->complex_style_pointer);
        free (ltype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c LTYPE symbol table entries and all their data fields.
 */
void
dxf_ltype_free_list
(
        DxfLType *ltypes
                /*!< a pointer to the single linked list of DXF
                 * \c LTYPE symbol table entries. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ltypes == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (ltypes != NULL)
        {
                DxfLType *iter = (DxfLType *) ltypes->next;
                dxf_ltype_free (ltypes);
                ltypes = (DxfLType *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c LTYPE entity.
 *
 * \return ID code.
 */
int
dxf_ltype_get_id_code
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ltype->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_id_code
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the \c linetype_name from a DXF \c LTYPE entity.
 *
 * \return \c linetype_name when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_ltype_get_linetype_name
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->linetype_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ltype->linetype_name));
}


/*!
 * \brief Set the \c linetype_name for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_linetype_name
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        char *linetype_name
                /*!< a string containing the \c linetype_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->linetype_name = strdup (linetype_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the \c description from a DXF \c LTYPE entity.
 *
 * \return \c description when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_ltype_get_description
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->description ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ltype->description));
}


/*!
 * \brief Set the \c description for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_description
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        char *description
                /*!< a string containing the \c description for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (description == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->description = strdup (description);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the pointer to the linked list of \c complex_text_string
 * values from a DXF \c LTYPE entity.
 *
 * \return \c complex_text_string when sucessful, \c NULL when an error
 * occurred.
 */
DxfChar *
dxf_ltype_get_complex_text_string
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_text_string == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->complex_text_string);
}


/*!
 * \brief Set the pointer to the linked list of \c complex_text_string
 * values  for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_complex_text_string
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfChar *complex_text_string
                /*!< a linked list of strings containing the
                 * \c complex_text_string values for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (complex_text_string == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_text_string == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                ltype->complex_text_string = dxf_char_init (ltype->complex_text_string);
                if (ltype->complex_text_string == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory for a DxfChar struct.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        /*! \todo add code. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the \c total_pattern_length from a DXF \c LTYPE entity.
 *
 * \return \c total_pattern_length, \c EXIT_FAILURE when an error
 * occurred.
 */
double
dxf_ltype_get_total_pattern_length
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->total_pattern_length);
}


/*!
 * \brief Set the \c total_pattern_length for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_total_pattern_length
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        double total_pattern_length
                /*!< the \c total_pattern_length to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->total_pattern_length = total_pattern_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the pointer to the linked list of \c complex_x_offset
 * values from a DXF \c LTYPE entity.
 *
 * \return \c complex_x_offset when sucessful, \c NULL when an error
 * occurred.
 */
DxfDouble *
dxf_ltype_get_complex_x_offset
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_x_offset == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was foundd.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->complex_x_offset);
}


/*!
 * \brief Set the pointer of a linked list of \c complex_x_offset
 * values for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_complex_x_offset
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfDouble *complex_x_offset
                /*!< a pointer to a linked list of \c complex_x_offset
                 * values for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (complex_x_offset == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->complex_x_offset = complex_x_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the pointer to the linked list of \c complex_y_offset
 * values from a DXF \c LTYPE entity.
 *
 * \return \c complex_y_offset when sucessful, \c NULL when an error
 * occurred.
 */
DxfDouble *
dxf_ltype_get_complex_y_offset
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_y_offset == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->complex_y_offset);
}


/*!
 * \brief Set the \c complex_y_offset for index \c i for a DXF
 * \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_complex_y_offset
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfDouble *complex_y_offset
                /*!< a double containing the \c complex_y_offset for
                 * index \c i of the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (complex_y_offset == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->complex_y_offset = complex_y_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get a pointer to a linked list of \c complex_scale values of a
 * DXF \c LTYPE entity.
 *
 * \return \c complex_scale when sucessful, \c NULL when an error
 * occurred.
 */
DxfDouble *
dxf_ltype_get_complex_scale
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_scale == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->complex_scale);
}


/*!
 * \brief Set a pointer to a linked list of \c complex_scale values for
 * a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_complex_scale
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfDouble *complex_scale
                /*!< a DxfDouble containing a linked list of
                 * \c complex_scale values of the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (complex_scale == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->complex_scale = complex_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get a pointer to a linked list of \c dash_length values from a
 * DXF \c LTYPE entity.
 *
 * \return \c dash_length when sucessful, \c NULL when an error
 * occurred.
 */
DxfDouble *
dxf_ltype_get_dash_length
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->dash_length == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->dash_length);
}


/*!
 * \brief Set a pointer to a linked list of \c dash_length values for a
 * DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_dash_length
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfDouble *dash_length
                /*!< a double containing the \c dash_length for
                 * index \c i of the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dash_length == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->dash_length = dash_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get a pointer to a linked list of \c complex_rotation values
 * of a DXF \c LTYPE entity.
 *
 * \return \c complex_rotation when sucessful, \c NULL when an error
 * occurred.
 */
DxfDouble *
dxf_ltype_get_complex_rotation
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_rotation == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->complex_rotation);
}


/*!
 * \brief Set a pointer of a linked list of \c complex_rotation values
 * for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_complex_rotation
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfDouble *complex_rotation
                /*!< a pointer to a linked list containing
                 * \c complex_rotation values of a \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (complex_rotation == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->complex_rotation = complex_rotation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the \c flag from a DXF \c LTYPE entity.
 *
 * \return \c flag when successful, \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ltype_get_flag
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ltype->flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->flag);
}


/*!
 * \brief Set the \c flag for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_flag
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c ARC entity. */
        int flag
                /*!< flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Test if ltype is externally dependent on an xref.
 *
 * \return \c TRUE when ltype is externally dependent on an xref,
 * or \c FALSE when ltype is not externally dependent on an xref.
 */
int
dxf_ltype_is_xreferenced
(
        DxfLType *ltype
                /*!< a pointer to the DXF \c LTYPE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (ltype->flag, 4));
}


/*!
 * \brief Test if ltype is externally dependent on a xref and has been
 * successfully resolved.
 *
 * \return \c TRUE when ltype is externally dependent on a xref and has
 * been successfully resolved,
 * or \c FALSE when ltype is not externally dependent on a xref and has
 * not been successfully resolved.
 */
int
dxf_ltype_is_xresolved
(
        DxfLType *ltype
                /*!< a pointer to the DXF \c LTYPE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DXF_CHECK_BIT (ltype->flag, 4))
          && (DXF_CHECK_BIT (ltype->flag, 5)));
}


/*!
 * \brief Test if ltype is internally referenced by an entity.
 *
 * \return \c TRUE when ltype is internally referenced by an entity,
 * or \c FALSE when ltype is not internally referenced by an entity.
 */
int
dxf_ltype_is_referenced
(
        DxfLType *ltype
                /*!< a pointer to the DXF \c LTYPE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (ltype->flag, 6));
}


/*!
 * \brief Get the \c alignment from a DXF \c LTYPE entity.
 *
 * \return \c alignment when successful, \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ltype_get_alignment
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ltype->alignment != 65)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->alignment);
}


/*!
 * \brief Set the \c alignment for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_alignment
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c ARC entity. */
        int alignment
                /*!< alignment to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (alignment != 65)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->alignment = alignment;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the \c number_of_linetype_elements from a DXF \c LTYPE entity.
 *
 * \return \c number_of_linetype_elements, \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ltype_get_number_of_linetype_elements
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ltype->number_of_linetype_elements < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->number_of_linetype_elements);
}


/*!
 * \brief Set the \c number_of_linetype_elements for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error
 * occurred.
 */
DxfLType *
dxf_ltype_set_number_of_linetype_elements
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c ARC entity. */
        int number_of_linetype_elements
                /*!< \c number_of_linetype_elements to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_linetype_elements < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->number_of_linetype_elements = number_of_linetype_elements;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the pointer to a linked list of \c complex_element from a
 * DXF \c LTYPE entity.
 *
 * \return \c complex_element when sucessful, \c NULL when an error
 * occurred.
 */
DxfInt16 *
dxf_ltype_get_complex_element
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_element == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->complex_element);
}


/*!
 * \brief Set the pointer of linked list of \c complex_element for a DXF
 * \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error occurred.
 */
DxfLType *
dxf_ltype_set_complex_element
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfInt16 *complex_element
                /*!< a pointer to a linked list of \c complex_element
                 * values for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (complex_element == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->complex_element = complex_element;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the pointer to the linked list of \c complex_shape_number
 * values from a DXF \c LTYPE entity.
 *
 * \return \c complex_shape_number when sucessful, \c NULL when an error
 * occurred.
 */
DxfInt16 *
dxf_ltype_get_complex_shape_number
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_shape_number == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->complex_shape_number);
}


/*!
 * \brief Set the pointer to a linked list of \c complex_shape_number
 * values for a DXF \c LTYPE entity.
 *
 * \return \c ltype when sucessful, \c NULL when an error occurred.
 */
DxfLType *
dxf_ltype_set_complex_shape_number
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfInt16 *complex_shape_number
                /*!< a pointer to a linked list of \c complex_shape_number
                 * values for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (complex_shape_number == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->complex_shape_number = complex_shape_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c LTYPE entity.
 *
 * \return soft pointer to the dictionary owner \dictonary_owner_soft,
 * \c NULL when an error occurred.
 *
 * \warning no checks are performed on the returned pointer (string).
 */
char *
dxf_ltype_get_dictionary_owner_soft
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ltype->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c LTYPE entity.
 *
 * \return \c ltype when successful, or \c NULL when an error occurred.
 */
DxfLType *
dxf_ltype_set_dictionary_owner_soft
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get a pointer to a linked list of \c complex_style_pointer
 * from a DXF \c LTYPE entity.
 *
 * \return \c complex_style_pointer when sucessful, \c NULL when an
 * error occurred.
 */
DxfChar *
dxf_ltype_get_complex_style_pointer
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->complex_style_pointer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype->complex_style_pointer);
}


/*!
 * \brief Set a pointer to a linked list of \c complex_style_pointer for
 * a DXF \c LTYPE entity.
 *
 * \return \c ltype when successful, or \c NULL when an error occurred.
 */
DxfLType *
dxf_ltype_set_complex_style_pointer
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfChar *complex_style_pointer
                /*!< a string containing the \c complex_style_pointer
                 * for index \c i of the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (complex_style_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->complex_style_pointer = complex_style_pointer;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c LTYPE entity.
 *
 * \return A hard pointer to the dictionary owner \c dictionay_owner_hard,
 * or \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_ltype_get_dictionary_owner_hard
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ltype->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c LTYPE entity.
 *
 * \return \c ltype when successful, or \c NULL when an error occurred.
 */
DxfLType *
dxf_ltype_set_dictionary_owner_hard
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ltype->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the pointer to the next \c LTYPE entity from a DXF 
 * \c LTYPE entity.
 *
 * \return pointer to the next \c LTYPE entity, or \c NULL when an error
 * occurred..
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLType *
dxf_ltype_get_next
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLType *) ltype->next);
}


/*!
 * \brief Set the pointer to the next \c LTYPE for a DXF \c LTYPE
 * entity.
 *
 * \return pointer to the \c LTYPE entity, or \c NULL when an error
 * occurred..
 */
DxfLType *
dxf_ltype_set_next
(
        DxfLType *ltype,
                /*!< a pointer to a DXF \c LTYPE entity. */
        DxfLType *next
                /*!< a pointer to the next \c LTYPE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
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
        ltype->next = (struct DxfLType *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ltype);
}


/*!
 * \brief Get the pointer to the last \c LTYPE entity from a linked list
 * of DXF \c LTYPE entities.
 *
 * \return pointer to the last \c LTYPE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLType *
dxf_ltype_get_last
(
        DxfLType *ltype
                /*!< a pointer to a DXF \c LTYPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltype->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfLType *) ltype);
        }
        DxfLType *iter = (DxfLType *) ltype->next;
        while (iter->next != NULL)
        {
                iter = (DxfLType *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLType *) iter);
}


/* EOF */
