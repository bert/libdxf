/*!
 * \file mtext.c
 *
 * \author Copyright (C) 2012, 2013, 2014, 2015, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mtext entity (\c MTEXT).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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


#include "mtext.h"


/*!
 * \brief Allocate memory for a \c DxfMtext.
 *
 * Fill the memory contents with zeros.
 */
DxfMtext *
dxf_mtext_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMtext *mtext = NULL;
        size_t size;

        size = sizeof (DxfMtext);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mtext = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfMtext struct.\n")),
                  __FUNCTION__);
                mtext = NULL;
        }
        else
        {
                memset (mtext, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c MTEXT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfMtext *
dxf_mtext_init
(
        DxfMtext *mtext
                /*!< a pointer to the DXF mtext entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mtext = dxf_mtext_new ();
        }
        if (mtext == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfMtext struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        mtext->id_code = 0;
        mtext->text_value = strdup ("");
        for (i = 1; i < DXF_MAX_PARAM; i++)
        {
                mtext->text_additional_value[i] = strdup ("");
        }
        mtext->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mtext->text_style = strdup ("");
        mtext->layer = strdup (DXF_DEFAULT_LAYER);
        mtext->x0 = 0.0;
        mtext->y0 = 0.0;
        mtext->z0 = 0.0;
        mtext->x1 = 0.0;
        mtext->y1 = 0.0;
        mtext->z1 = 0.0;
        mtext->elevation = 0.0;
        mtext->thickness = 0.0;
        mtext->height = 0.0;
        mtext->rectangle_width = 0.0;
        mtext->horizontal_width = 0.0;
        mtext->rectangle_height = 0.0;
        mtext->spacing_factor = 0.0;
        mtext->box_scale = 0.0;
        mtext->column_width = 0.0;
        mtext->column_gutter = 0.0;
        mtext->column_heights = 0.0;
        mtext->rot_angle = 0.0;
        mtext->color = DXF_COLOR_BYLAYER;
        mtext->background_color = 0;
        mtext->paperspace = DXF_MODELSPACE;
        mtext->attachment_point = 0;
        mtext->drawing_direction = 0;
        mtext->spacing_style = 0;
        mtext->column_type = 0;
        mtext->column_count = 0;
        mtext->column_flow = 0;
        mtext->column_autoheight = 0;
        mtext->background_fill = 0;
        mtext->extr_x0 = 0.0;
        mtext->extr_y0 = 0.0;
        mtext->extr_z0 = 0.0;
        mtext->background_color_rgb = 0;
        mtext->background_color_name = strdup ("");
        mtext->background_transparency = 0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Read data from a DXF file into a \c MTEXT entity.
 *
 * The last line read from file contained the string "MTEXT". \n
 * Now follows some data for the \c MTEXT, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c mtext. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfMtext *
dxf_mtext_read
(
        DxfFile *fp,
                /*!< DXF filepointer to the input file (or device). */
        DxfMtext *mtext
                /*!< a pointer to the DXF mtext entity. */
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
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mtext = dxf_mtext_new ();
                mtext = dxf_mtext_init (mtext);
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
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a text value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mtext->text_value);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a text value. */
                        (fp->line_number)++;
                        //fscanf (fp->fp, "%s\n", mtext->text_additional_value[number_additional]);
                        //number_additional++;
                }
                /*!< I'm not sure this number_additional is correct.*/
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &mtext->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mtext->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mtext->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mtext->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                  && DXF_FLATLAND
                  && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * reference rectangle width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->rectangle_width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal width of the characters. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->horizontal_width);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * vertical rectangle height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->rectangle_height);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the
                         * text line spacing factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->spacing_factor);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing the
                         * fill box scale (border around text). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->box_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the
                         * column width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->column_width);
                }
                else if (strcmp (temp_string, "49") == 0)
                {
                        /* Now follows a string containing the
                         * column gutter. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->column_gutter);
                }
                else if ((fp->acad_version_number <= AutoCAD_2006)
                        && (strcmp (temp_string, "50") == 0))
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->rot_angle);
                }
                else if ((fp->acad_version_number >= AutoCAD_2007)
                        && (strcmp (temp_string, "50") == 0))
                {
                        /* Can follows a string containing the
                         * rotation angle or column heights. */
                        (fp->line_number)++;
                /*!< Add more code here, I'm stop because the double use of group code 50*/
                }
                else if (strcmp (temp_string, "63") == 0)
                {
                        /* Now follows a string containing the
                         * color to use for background fill. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->background_color);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * attachment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->attachment_point);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * drawing direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->drawing_direction);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * mtext line spacing style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->spacing_style);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the
                         * column type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->column_type);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing the
                         * column count. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->column_count);
                }
                else if (strcmp (temp_string, "78") == 0)
                {
                        /* Now follows a string containing the
                         * column flow reverse. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->column_flow);
                }
                else if (strcmp (temp_string, "79") == 0)
                {
                        /* Now follows a string containing the
                         * column autoheight. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->column_autoheight);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * background fill setting. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mtext->background_fill);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbMText") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->extr_z0);
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
        if (strcmp (mtext->linetype, "") == 0)
        {
                mtext->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (mtext->layer, "") == 0)
        {
                mtext->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a DXF \c ARC entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \warning This entity requires AutoCAD version R13 or higher.
 * When the \c follow_strict_version_rules flag is set to \c TRUE in the
 * \c DxfFile struct, this entity will be skipped from file.
 * When the \c follow_strict_version_rules flag is set to \c FALSE in the
 * \c DxfFile struct, libdxf will write this entity to file and report
 * with a warning message to \c stderr.
 */
int
dxf_mtext_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfMtext *mtext
                /*!< a pointer to the DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("MTEXT");
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
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((fp->acad_version_number < AutoCAD_13)
          && (fp->follow_strict_version_rules))
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, mtext->id_code);
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, mtext->id_code);
        }
        if (strcmp (mtext->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, mtext->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                mtext->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (mtext->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, mtext->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                mtext->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (mtext->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", mtext->id_code);
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
        if ((strcmp (mtext->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", mtext->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (mtext->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", mtext->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (mtext->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", mtext->layer);
        if (strcmp (mtext->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", mtext->linetype);
        }
        if (mtext->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", mtext->color);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (mtext->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", mtext->elevation);
        }
        if (mtext->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", mtext->thickness);
        }
        if (mtext->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", mtext->linetype_scale);
        }
        if (mtext->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", mtext->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbMText\n");
        }
        fprintf (fp->fp, " 10\n%f\n", mtext->x0);
        fprintf (fp->fp, " 20\n%f\n", mtext->y0);
        fprintf (fp->fp, " 30\n%f\n", mtext->z0);
        fprintf (fp->fp, " 40\n%f\n", mtext->height);
        fprintf (fp->fp, " 41\n%f\n", mtext->rectangle_width);
        fprintf (fp->fp, " 71\n%d\n", mtext->attachment_point);
        fprintf (fp->fp, " 72\n%d\n", mtext->drawing_direction);
        fprintf (fp->fp, "  1\n%s\n", mtext->text_value);
        i = 0;
        while (strlen (mtext->text_additional_value[i]) > 0)
        {
                fprintf (fp->fp, "  3\n%s\n", mtext->text_additional_value[i]);
                i++;
        }
        fprintf (fp->fp, "  7\n%s\n", mtext->text_style);

        if ((fp->acad_version_number >= AutoCAD_12)
                && (mtext->extr_x0 != 0.0)
                && (mtext->extr_y0 != 0.0)
                && (mtext->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", mtext->extr_x0);
                fprintf (fp->fp, "220\n%f\n", mtext->extr_y0);
                fprintf (fp->fp, "230\n%f\n", mtext->extr_z0);
        }
        fprintf (fp->fp, " 11\n%f\n", mtext->x1);
        fprintf (fp->fp, " 21\n%f\n", mtext->y1);
        fprintf (fp->fp, " 31\n%f\n", mtext->z1);
        fprintf (fp->fp, " 42\n%f\n", mtext->horizontal_width);
        fprintf (fp->fp, " 43\n%f\n", mtext->rectangle_height);
        fprintf (fp->fp, " 50\n%f\n", mtext->rot_angle);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c MTEXT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mtext_free
(
        DxfMtext *mtext
                /*!< a pointer to the DXF mtext entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (mtext->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfMtext was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (mtext->linetype);
        free (mtext->layer);
        free (mtext->text_value);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (mtext->text_additional_value[i]);
        }
        free (mtext->text_style);
        free (mtext->dictionary_owner_soft);
        free (mtext->dictionary_owner_hard);
        free (mtext->background_color_name);
        free (mtext);
        mtext = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c MTEXT
 * entities and all their data fields.
 */
void
dxf_mtext_free_chain
(
        DxfMtext *mtexts
                /*!< a pointer to the chain of DXF \c MTEXT entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (mtexts == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (mtexts != NULL)
        {
                struct DxfMtext *iter = mtexts->next;
                dxf_mtext_free (mtexts);
                mtexts = (DxfMtext *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c MTEXT entity.
 *
 * \return \c id_code.
 */
int
dxf_mtext_get_id_code
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_id_code
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
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
        if (mtext == NULL)
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
        mtext->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c linetype from a DXF \c MTEXT entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_mtext_get_linetype
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mtext->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_linetype
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c layer from a DXF \c MTEXT entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_mtext_get_layer
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mtext->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_layer
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c elevation from a DXF \c MTEXT entity.
 *
 * \return \c elevation.
 */
double
dxf_mtext_get_elevation
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_elevation
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c thickness from a DXF \c MTEXT entity.
 *
 * \return \c thickness.
 */
double
dxf_mtext_get_thickness
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_thickness
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c MTEXT entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_mtext_get_linetype_scale
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_linetype_scale
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c visibility from a DXF \c MTEXT entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_mtext_get_visibility
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_visibility
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c color from a DXF \c MTEXT entity.
 *
 * \return \c color.
 */
int
dxf_mtext_get_color
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->color);
}


/*!
 * \brief Set the \c color for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_color
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c MTEXT entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_mtext_get_paperspace
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mtext->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_paperspace
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c MTEXT entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_mtext_get_graphics_data_size
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mtext->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_graphics_data_size
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c MTEXT entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mtext_get_shadow_mode
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->shadow_mode);
}


/* EOF */
