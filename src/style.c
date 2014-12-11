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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 * \brief Read data from a DXF file into a DXF \c STYLE entity.
 *
 * The last line read from file contained the string "STYLE". \n
 * Now follows some data for the \c STYLE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c TABLES
 * section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c dxf_style. \n
 *
 * \return a pointer to \c dxf_style.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfStyle *
dxf_style_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfStyle *dxf_style
                /*!< DXF \c STYLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_style == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_style = dxf_style_new ();
                dxf_style = dxf_style_init (dxf_style);
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
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_style->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a style name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_style->style_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a primary
                         * font filename. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_style->primary_font_filename);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing a big font
                         * filename. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_style->big_font_filename);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_style->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_style->width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * last used height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_style->last_height);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * oblique angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_style->oblique_angle);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_style->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text generation flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_style->text_generation_flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", dxf_style->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_style->dictionary_owner_hard);
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
        if (strcmp (dxf_style->style_name, "") == 0)
        {
                sprintf (dxf_style->style_name, "%i", dxf_style->id_code);
                fprintf (stderr,
                  (_("Warning in %s () illegal style name value found while reading from: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
        }
        if ((strcmp (dxf_style->primary_font_filename, "") == 0)
          && (dxf_style->flag == 1))
        {
                sprintf (dxf_style->primary_font_filename, "%i", dxf_style->id_code);
                fprintf (stderr,
                  (_("Warning in %s () illegal primary font filename value found while reading from: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
        }
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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


/*!
 * \brief Test if a shape file should be loaded.
 *
 * \return \c TRUE when a shape file should be loaded,
 * or \c FALSE when not.
 *
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_style_is_shape_file
(
        DxfStyle *dxf_style
                /*!< DXF style entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (dxf_style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (dxf_style->flag, 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF*/
