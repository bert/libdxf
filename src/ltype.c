/*!
 * \file ltype.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF ltype entity (\c LTYPE).
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Error in %s () could not allocate memory for a DxfArc struct.\n")),
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
 * \brief Allocate memory and initialize data fields for a DXF \c LTYPE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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

        /* Do some basic checks. */
        if (dxf_ltype == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ltype = dxf_ltype_new ();
        }
        if (dxf_ltype == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfLType struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_ltype->id_code = 0;
        dxf_ltype->linetype_name = strdup ("");
        dxf_ltype->description = strdup ("");
        dxf_ltype->total_pattern_length = 0.0;
        dxf_ltype->number_of_linetype_elements = 1;
        for ((i = 0); (i < dxf_ltype->number_of_linetype_elements); i++)
        {
                dxf_ltype->complex_text_string[i] = strdup ("");
                dxf_ltype->complex_x_offset[i] = 0.0;
                dxf_ltype->complex_y_offset[i] = 0.0;
                dxf_ltype->complex_scale[i] = 0.0;
                dxf_ltype->dash_length[i] = 0.0;
                dxf_ltype->complex_rotation[i] = 0.0;
                dxf_ltype->complex_element[i] = 1;
                dxf_ltype->complex_shape_number[i] = 0;
                dxf_ltype->complex_style_pointer[i] = strdup ("");
        }
        dxf_ltype->flag = 0;
        dxf_ltype->alignment = 65;
        dxf_ltype->dictionary_owner_soft = strdup ("");
        dxf_ltype->dictionary_owner_hard = strdup ("");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ltype);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LTYPE entity.
 *
 * The last line read from file contained the string "LTYPE". \n
 * Now follows some data for the \c LTYPE, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c dxf_ltype. \n
 *
 * \return a pointer to \c dxf_ltype.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfLType *
dxf_ltype_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLType *dxf_ltype
                /*!< DXF ltype entity. */
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
                return (NULL);
        }
        if (dxf_ltype == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ltype = dxf_ltype_new ();
                dxf_ltype = dxf_ltype_init (dxf_ltype);
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
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_ltype->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ltype->linetype_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a description. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ltype->description);
                }
                else if (strcmp (temp_string, "9") == 0)
                {
                        /* Now follows a string containing a complex
                         * text string (multiple entries possible). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ltype->complex_text_string[element]);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the total
                         * pattern length value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ltype->total_pattern_length);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing a complex
                         * x offset value (multiple entries possible). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ltype->complex_x_offset[element]);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing a complex
                         * y offset value (multiple entries possible). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ltype->complex_y_offset[element]);
                }
                else if (strcmp (temp_string, "46") == 0)
                {
                        /* Now follows a string containing a complex
                         * scale value (multiple entries possible). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ltype->complex_scale[element]);
                }
                else if (strcmp (temp_string, "49") == 0)
                {
                        /* Now follows a string containing a dash length
                         * value (multiple entries possible). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ltype->dash_length[element]);
                        element++;
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
                        fscanf (fp->fp, "%lf\n", &dxf_ltype->complex_rotation[element]);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ltype->flag);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ltype->alignment);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the number of
                         * dash length items value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ltype->number_of_linetype_elements);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing a complex
                         * element value (multiple entries possible). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ltype->complex_element[element]);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing a complex
                         * element value (multiple entries possible). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ltype->complex_shape_number[element]);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ltype->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a complex
                         * style pointer string (multiple entries possible). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ltype->complex_style_pointer[element]);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ltype->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
        if (strcmp (dxf_ltype->linetype_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s (): empty linetype name string for the entity with id-code: %x\n")),
                  __FUNCTION__, dxf_ltype->id_code);
                fprintf (stderr,
                  (_("\tentity is discarded from output.\n")));
                return (NULL);
        }
        if (dxf_ltype->alignment != 65)
        {
                dxf_ltype->alignment = 65;
        }
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
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
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ltype->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_ltype->id_code);
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
        if ((strcmp (dxf_ltype->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_ltype->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_ltype->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_ltype->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
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
        fprintf (fp->fp, " 73\n%d\n", dxf_ltype->number_of_linetype_elements);
        fprintf (fp->fp, " 40\n%f\n", dxf_ltype->total_pattern_length);
        for ((i = 0); (i < dxf_ltype->number_of_linetype_elements); i++)
        {
                fprintf (fp->fp, " 49\n%f\n", dxf_ltype->dash_length[i]);
                fprintf (fp->fp, " 74\n%d\n", dxf_ltype->complex_element[i]);
                switch (dxf_ltype->complex_element[i])
                {
                        case 0:
                                /* No embedded shape/text. */
                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype->complex_x_offset[i]);
                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype->complex_y_offset[i]);
                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype->complex_scale[i]);
                                fprintf (fp->fp, " 75\n0\n");
                                break;
                        case 1:
                                /* Specify an absolute rotation. */
                                fprintf (fp->fp, " 44\n%f\n", dxf_ltype->complex_x_offset[i]);
                                fprintf (fp->fp, " 45\n%f\n", dxf_ltype->complex_y_offset[i]);
                                fprintf (fp->fp, " 46\n%f\n", dxf_ltype->complex_scale[i]);
                                fprintf (fp->fp, " 75\n0\n");
                                fprintf (fp->fp, "340\n%s\n", dxf_ltype->complex_style_pointer[i]);
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                (_("Error in %s () pointer to next DxfLType was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_ltype->linetype_name);
        free (dxf_ltype->description);
        for ((i = 0); (i <= dxf_ltype->number_of_linetype_elements); i++)
        {
                dxf_ltype->complex_text_string[i] = NULL;
                dxf_ltype->complex_style_pointer[i] = NULL;
        }
        free (dxf_ltype->dictionary_owner_soft);
        free (dxf_ltype->dictionary_owner_hard);
        free (dxf_ltype);
        dxf_ltype = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
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
        DxfLType *dxf_ltype
                /*!< DXF ltype entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (dxf_ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (dxf_ltype->flag, 4);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
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
        DxfLType *dxf_ltype
                /*!< DXF ltype entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (dxf_ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = ((DXF_CHECK_BIT (dxf_ltype->flag, 4))
          && (DXF_CHECK_BIT (dxf_ltype->flag, 5)));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
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
        DxfLType *dxf_ltype
                /*!< DXF ltype entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (dxf_ltype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (dxf_ltype->flag, 6);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
