/*!
 * \file style.c
 *
 * \author Copyright (C) 2014, 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF style entity (\c STYLE).
 *
 * A STYLE table item is also used to record shape file LOAD command
 * requests.
 *
 * In this case the first bit (1) is set in the 70 group flags and only
 * the 3 group (shape file name) is meaningful (all the other groups are
 * output, however).
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
 * allocated memory when successful.
 */
DxfStyle *
dxf_style_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfStyle *style = NULL;
        size_t size;

        size = sizeof (DxfStyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((style = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfStyle struct.\n")),
                  __FUNCTION__);
                style = NULL;
        }
        else
        {
                memset (style, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c STYLE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfStyle *
dxf_style_init
(
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                style = dxf_style_new ();
        }
        if (style == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfStyle struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        style->id_code = 0;
        style->style_name = strdup ("");
        style->primary_font_filename = strdup ("");
        style->big_font_filename = strdup ("");
        style->height = 0.0;
        style->width = 0.0;
        style->last_height = 0.0;
        style->oblique_angle = 0.0;
        style->flag = 0;
        style->text_generation_flag = 0;
        style->dictionary_owner_soft = strdup ("");
        style->dictionary_owner_hard = strdup ("");
        style->ttf_flags = 0;
        style->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Read data from a DXF file into a DXF \c STYLE entity.
 *
 * The last line read from file contained the string "STYLE". \n
 * Now follows some data for the \c STYLE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c TABLES
 * section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c style. \n
 *
 * \return a pointer to \c style.
 */
DxfStyle *
dxf_style_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

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
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                style = dxf_style_init (style);
        }
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
                        fscanf (fp->fp, "%x\n", (uint *) &style->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a style name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, style->style_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a primary
                         * font filename. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, style->primary_font_filename);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing a big font
                         * filename. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, style->big_font_filename);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &style->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &style->width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * last used height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &style->last_height);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * oblique angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &style->oblique_angle);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &style->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text generation flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &style->text_generation_flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTableRecord") != 0)
                        && ((strcmp (temp_string, "AcDbTextStyleTableRecord") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, style->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, style->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else if (strcmp (temp_string, "1071") == 0)
                {
                        /* Now follows a string containing true type font flags. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &style->ttf_flags);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (style->style_name, "") == 0)
        {
                sprintf (style->style_name, "%i", style->id_code);
                fprintf (stderr,
                  (_("Warning in %s () illegal style name value found while reading from: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
        }
        if ((strcmp (style->primary_font_filename, "") == 0)
          && (style->flag == 1))
        {
                sprintf (style->primary_font_filename, "%i", style->id_code);
                fprintf (stderr,
                  (_("Warning in %s () illegal primary font filename value found while reading from: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
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
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("STYLE");

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
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (style->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", style->id_code);
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
        if ((strcmp (style->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", style->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (style->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", style->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbTextStyleTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", style->style_name);
        fprintf (fp->fp, " 70\n%d\n", style->flag);
        fprintf (fp->fp, " 40\n%f\n", style->height);
        fprintf (fp->fp, " 41\n%f\n", style->width);
        fprintf (fp->fp, " 50\n%f\n", style->oblique_angle);
        fprintf (fp->fp, " 71\n%d\n", style->text_generation_flag);
        fprintf (fp->fp, " 42\n%f\n", style->last_height);
        fprintf (fp->fp, "  3\n%s\n", style->primary_font_filename);
        fprintf (fp->fp, "  4\n%s\n", style->big_font_filename);
        fprintf (fp->fp, "1071\n%d\n", style->ttf_flags);
        /* Clean up. */
        free (dxf_entity_name);
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
        DxfStyle *style
                /*!< a pointer to the memory occupied by the DXF \c STYLE
                 * symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (style->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (style->style_name);
        free (style->primary_font_filename);
        free (style->big_font_filename);
        free (style->dictionary_owner_soft);
        free (style->dictionary_owner_hard);
        free (style);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c STYLE symbol table entries and all their data fields.
 */
void
dxf_style_free_list
(
        DxfStyle *styles
                /*!< a pointer to the single linked list of DXF
                 * \c STYLE symbol table entries. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (styles == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (styles != NULL)
        {
                DxfStyle *iter = (DxfStyle *) styles->next;
                dxf_style_free (styles);
                styles = (DxfStyle *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c STYLE symbol table entries.
 *
 * \return \c id_code.
 */
int
dxf_style_get_id_code
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table
                 * entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (style->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c STYLE symbol table entries.
 */
DxfStyle *
dxf_style_set_id_code
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        int id_code
                /*!< the \c id_code to be set for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        style->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c style_name from a DXF \c STYLE symbol table entries.
 *
 * \return \c style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_style_get_style_name
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style->style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (style->style_name));
}


/*!
 * \brief Set the \c style_name for a DXF \c STYLE symbol table entries.
 *
 * \return a pointer to \c style when successful, or \c NULL when an
 * error occurred.
 */
DxfStyle *
dxf_style_set_color_name
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        char *style_name
                /*!< a string containing the \c style_name for the
                 * symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        style->style_name = strdup (style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c primary_font_filename from a DXF \c STYLE symbol
 * table entries.
 *
 * \return \c primary_font_filename when sucessful, or \c NULL when an
 * error occurred.
 */
char *
dxf_style_get_primary_font_filename
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style->primary_font_filename ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (style->primary_font_filename));
}


/*!
 * \brief Set the \c primary_font_filename for a DXF \c STYLE symbol
 * table entries.
 *
 * \return a pointer to \c style when successful, or \c NULL when an
 * error occurred.
 */
DxfStyle *
dxf_style_set_primary_font_filename
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        char *primary_font_filename
                /*!< a string containing the \c primary_font_filename
                 * for the symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (primary_font_filename == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        style->primary_font_filename = strdup (primary_font_filename);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c big_font_filename from a DXF \c STYLE symbol
 * table entries.
 *
 * \return \c big_font_filename when sucessful, or \c NULL when an
 * error occurred.
 */
char *
dxf_style_get_big_font_filename
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style->big_font_filename ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (style->big_font_filename));
}


/*!
 * \brief Set the \c big_font_filename for a DXF \c STYLE symbol
 * table entries.
 *
 * \return a pointer to \c style when successful, or \c NULL when an
 * error occurred.
 */
DxfStyle *
dxf_style_set_big_font_filename
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        char *big_font_filename
                /*!< a string containing the \c big_font_filename for
                 * the symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (big_font_filename == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        style->big_font_filename = strdup (big_font_filename);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c height from a DXF \c STYLE symbol table entries.
 *
 * \return \c height.
 */
double
dxf_style_get_height
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style->height);
}


/*!
 * \brief Set the \c height for a DXF \c STYLE symbol table entries.
 */
DxfStyle *
dxf_style_set_height
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        double height
                /*!< the \c height to be set for the entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        style->height = height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c width from a DXF \c STYLE symbol table entries.
 *
 * \return \c width.
 */
double
dxf_style_get_width
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style->width);
}


/*!
 * \brief Set the \c width for a DXF \c STYLE symbol table entries.
 */
DxfStyle *
dxf_style_set_width
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        double width
                /*!< the \c width to be set for the entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        style->width = width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c last_height from a DXF \c STYLE symbol table entries.
 *
 * \return \c last_height.
 */
double
dxf_style_get_last_height
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style->last_height);
}


/*!
 * \brief Set the \c last_height for a DXF \c STYLE symbol table entries.
 */
DxfStyle *
dxf_style_set_last_height
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        double last_height
                /*!< the \c last_height to be set for the entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        style->last_height = last_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c oblique_angle from a DXF \c STYLE symbol table
 * entries.
 *
 * \return \c oblique_angle.
 */
double
dxf_style_get_oblique_angle
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style->oblique_angle);
}


/*!
 * \brief Set the \c oblique_angle for a DXF \c STYLE symbol table
 * entries.
 */
DxfStyle *
dxf_style_set_oblique_angle
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        double oblique_angle
                /*!< the \c oblique_angle to be set for the entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        style->oblique_angle = oblique_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c flag from a DXF \c STYLE symbol table entries.
 *
 * \return \c flag.
 */
int
dxf_style_get_flag
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table
                 * entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (style->flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (style->flag > 0x01111111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style->flag);
}


/*!
 * \brief Set the \c flag for a DXF \c STYLE symbol table entries.
 */
DxfStyle *
dxf_style_set_flag
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        int flag
                /*!< the \c flag to be set for the entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (flag > 0x01111111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        style->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Test if a shape file should be loaded.
 *
 * \return \c TRUE when a shape file should be loaded,
 * or \c FALSE when not, or (-1) when an error occured.
 */
int
dxf_style_is_shape_file
(
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (style->flag, 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if a shape text is vertically oriented.
 *
 * \return \c TRUE when vertical oriented,
 * or \c FALSE when not vertically oriented, or (-1) when an error
 * occured.
 */
int
dxf_style_is_text_vertical
(
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (style->flag, 2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if style is externally dependent on an xref.
 *
 * \return \c TRUE when style is externally dependent on an xref,
 * or \c FALSE when style is not externally dependent on an xref,
 * or (-1) when an error occured.
 */
int
dxf_style_is_xreferenced
(
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (style->flag, 4);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if style is externally dependent on a xref and has been
 * successfully resolved.
 *
 * \return \c TRUE when style is externally dependent on a xref and has
 * been successfully resolved,
 * or \c FALSE when style is not externally dependent on a xref and has
 * not been successfully resolved, or (-1) when an error occured.
 */
int
dxf_style_is_xresolved
(
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = ((DXF_CHECK_BIT (style->flag, 4))
          && (DXF_CHECK_BIT (style->flag, 5)));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if style is internally referenced by an entity.
 *
 * \return \c TRUE when style is internally referenced by an entity,
 * or \c FALSE when style is not internally referenced by an entity,
 * or (-1) when an error occured.
 */
int
dxf_style_is_referenced
(
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (style->flag, 6);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Get the \c text_generation_flag from a DXF \c STYLE symbol
 * table entries.
 *
 * \return \c text_generation_flag.
 */
int
dxf_style_get_text_generation_flag
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table
                 * entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (style->text_generation_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (style->text_generation_flag > 0x111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style->text_generation_flag);
}


/*!
 * \brief Set the \c text_generation_flag for a DXF \c STYLE symbol
 * table entries.
 */
DxfStyle *
dxf_style_set_text_generation_flag
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entries. */
        int text_generation_flag
                /*!< the \c text_generation_flag to be set for the
                 * entries. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_generation_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (text_generation_flag > 0x111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        style->text_generation_flag = text_generation_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Test if a text is backward.
 *
 * \return \c TRUE when a text is backward,
 * or \c FALSE when not, or (-1) when an error occured.
 */
int
dxf_style_is_text_backward
(
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (style->text_generation_flag, 1);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if a text is upside down.
 *
 * \return \c TRUE when a text is upside down,
 * or \c FALSE when not, or (-1) when an error occured.
 */
int
dxf_style_is_text_upside_down
(
        DxfStyle *style
                /*!< a pointer to the DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (style->text_generation_flag, 2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c STYLE symbol table entry.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_style_get_dictionary_owner_soft
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (style->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c STYLE symbol table entry.
 */
DxfStyle *
dxf_style_set_dictionary_owner_soft
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
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
        style->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c STYLE symbol table entry.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_style_get_dictionary_owner_hard
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (style->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c STYLE symbol table entry.
 */
DxfStyle *
dxf_style_set_dictionary_owner_hard
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
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
        style->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the \c ttf_flags from a DXF \c STYLE symbol table entry.
 *
 * \return \c ttf_flags when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_style_get_ttf_flags
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (style->ttf_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style->ttf_flags);
}


/*!
 * \brief Set the \c ttf_flags for a DXF \c STYLE symbol table entry.
 *
 * \return a pointer to \c style when successful, or \c NULL when an
 * error occurred.
 */
DxfStyle *
dxf_style_set_ttf_flags
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
        int32_t ttf_flags
                /*!< the \c ttf_flags to be set for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ttf_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative class_version value was passed.\n")),
                  __FUNCTION__);
        }
        style->ttf_flags = ttf_flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the pointer to the next \c STYLE symbol table entry from a
 * DXF \c STYLE symbol table entry.
 *
 * \return pointer to the next \c STYLE symbol table entry.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfStyle *
dxf_style_get_next
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfStyle *) style->next);
}


/*!
 * \brief Set the pointer to the next \c STYLE symbol table entry for a
 * DXF \c STYLE symbol table entry.
 */
DxfStyle *
dxf_style_set_next
(
        DxfStyle *style,
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
        DxfStyle *next
                /*!< a pointer to the next \c STYLE symbol table entry
                 * for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
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
        style->next = (struct DxfStyle *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (style);
}


/*!
 * \brief Get the pointer to the last \c STYLE symbol table entry from a
 * linked list of DXF \c STYLE symbol table entries.
 *
 * \return pointer to the last \c STYLE symbol table entry.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfStyle *
dxf_style_get_last
(
        DxfStyle *style
                /*!< a pointer to a DXF \c STYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfStyle *) style);
        }
        DxfStyle *iter = (DxfStyle *) style->next;
        while (iter->next != NULL)
        {
                iter = (DxfStyle *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfStyle *) iter);
}


/* EOF*/
