/*!
 * \file mtext.c
 *
 * \author Copyright (C) 2012, 2013, 2014, 2015, 2017, 2018, 2019, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2012, 2013 by Paolo Caroni <kenren89@gmail.com>.
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
 * allocated memory when successful.
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
        mtext->p0->x0 = 0.0;
        mtext->p0->y0 = 0.0;
        mtext->p0->z0 = 0.0;
        mtext->p1->x0 = 0.0;
        mtext->p1->y0 = 0.0;
        mtext->p1->z0 = 0.0;
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
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mtext->text_value);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a text value. */
                        (fp->line_number)++;
                        //fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mtext->text_additional_value[number_additional]);
                        //number_additional++;
                }
                /*!< I'm not sure this number_additional is correct.*/
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &mtext->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mtext->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mtext->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mtext->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mtext->p1->z0);
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
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
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
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
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
        fprintf (fp->fp, " 10\n%f\n", mtext->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", mtext->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", mtext->p0->z0);
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
        fprintf (fp->fp, " 11\n%f\n", mtext->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", mtext->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", mtext->p1->z0);
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

        /* Do some basic checks. */
        if (mtext == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mtext->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c MTEXT entities and all their data fields.
 */
void
dxf_mtext_free_list
(
        DxfMtext *mtexts
                /*!< a pointer to the single linked list of DXF \c MTEXT
                 * entities. */
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
                DxfMtext *iter = (DxfMtext *) mtexts->next;
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


/*!
 * \brief Set the \c shadow_mode for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_shadow_mode
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
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
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c MTEXT entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_mtext_get_binary_graphics_data
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
        if (mtext->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) mtext->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_binary_graphics_data
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
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
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c MTEXT entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mtext_get_dictionary_owner_soft
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
        if (mtext->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_dictionary_owner_soft
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
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
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c MTEXT entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_mtext_get_material
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
        if (mtext->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_material
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
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
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c MTEXT entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mtext_get_dictionary_owner_hard
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
        if (mtext->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_dictionary_owner_hard
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
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
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c lineweight from a DXF \c MTEXT entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mtext_get_lineweight
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
        return (mtext->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_lineweight
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
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
        mtext->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c MTEXT entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_mtext_get_plot_style_name
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
        if (mtext->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_plot_style_name
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
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
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c color_value from a DXF \c MTEXT entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mtext_get_color_value
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
        return (mtext->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_color_value
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
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
        mtext->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c color_name from a DXF \c MTEXT entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mtext_get_color_name
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
        if (mtext->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_color_name
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
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
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c transparency from a DXF \c MTEXT entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mtext_get_transparency
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
        return (mtext->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_transparency
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
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
        mtext->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c text_value from a DXF \c MTEXT entity.
 *
 * \return \c text_value when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mtext_get_text_value
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
        if (mtext->text_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->text_value));
}


/*!
 * \brief Set the \c text_value for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_text_value
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *text_value
                /*!< a string containing the \c text_value for the
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
        if (text_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->text_value = strdup (text_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c text_style from a DXF \c MTEXT entity.
 *
 * \return \c text_style when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mtext_get_text_style
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
        if (mtext->text_style ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->text_style));
}


/*!
 * \brief Set the \c text_style for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_text_style
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *text_style
                /*!< a string containing the \c text_style for the
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
        if (text_style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->text_style = strdup (text_style);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the insertion point \c p0 of a DXF \c MTEXT entity.
 *
 * \return the insertion point \c p0.
 */
DxfPoint *
dxf_mtext_get_p0
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a DXF \c MTEXT entity.
 *
 * \return a pointer to a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_p0
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
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
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a DXF \c MTEXT
 * entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_mtext_get_x0
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a DXF \c MTEXT
 * entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_x0
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double x0
                /*!< the X-value of the insertion point \c x0 of a DXF
                 * \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a DXF \c MTEXT
 * entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_mtext_get_y0
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a DXF \c MTEXT
 * entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_y0
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a DXF
                 * \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a DXF \c MTEXT
 * entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_mtext_get_z0
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a DXF \c MTEXT
 * entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_z0
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double z0
                /*!< the Z-value of the insertion point \c z0 of a DXF
                 * \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the direction vector \c p1 of a DXF \c MTEXT entity.
 *
 * \return the direction vector \c p1.
 */
DxfPoint *
dxf_mtext_get_p1
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->p1);
}


/*!
 * \brief Set the direction vector \c p1 of a DXF \c MTEXT entity.
 *
 * \return a pointer to a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_p1
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
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
        if (p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the X-value of the direction vector \c x0 of a DXF
 * \c MTEXT entity.
 *
 * \return the X-value of the direction vector \c x0.
 */
double
dxf_mtext_get_x1
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->p1->x0);
}


/*!
 * \brief Set the X-value of the direction vector \c x1 of a DXF
 * \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_x1
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double x1
                /*!< the X-value of the direction vector \c x1 of a DXF
                 * \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the Y-value of the direction vector \c y1 of a DXF
 * \c MTEXT entity.
 *
 * \return the Y-value of the direction vector \c y1.
 */
double
dxf_mtext_get_y1
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->p1->y0);
}


/*!
 * \brief Set the Y-value of the direction vector \c y1 of a DXF
 * \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_y1
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double y1
                /*!< the Y-value of the direction vector \c y1 of a DXF
                 * \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the Z-value of the direction vector \c z1 of a DXF
 * \c MTEXT entity.
 *
 * \return the Z-value of the direction vector \c z1.
 */
double
dxf_mtext_get_z1
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->p1->z0);
}


/*!
 * \brief Set the Z-value of the direction vector \c z1 of a DXF
 * \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_z1
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double z1
                /*!< the Z-value of the direction vector \c z1 of a DXF
                 * \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the nominal (initial) text \c height of a DXF \c MTEXT
 * entity.
 *
 * \return the nominal (initial) text \c height.
 */
double
dxf_mtext_get_height
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->height);
}


/*!
 * \brief Set the nominal (initial) text \c height of a DXF \c MTEXT
 * entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_height
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double height
                /*!< the nominal (initial) text \c height of a DXF
                 * \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->height = height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c rectangle_width of a DXF \c MTEXT
 * entity.
 *
 * \return the \c rectangle_width.
 */
double
dxf_mtext_get_rectangle_width
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->rectangle_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->rectangle_width);
}


/*!
 * \brief Set the \c rectangle_width of a DXF \c MTEXT
 * entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_rectangle_width
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double rectangle_width
                /*!< the \c rectangle_width of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (rectangle_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->rectangle_width = rectangle_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c horizontal_width of a DXF \c MTEXT entity.
 *
 * \return the \c horizontal_width.
 */
double
dxf_mtext_get_horizontal_width
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->horizontal_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->horizontal_width);
}


/*!
 * \brief Set the \c horizontal_width of a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_horizontal_width
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double horizontal_width
                /*!< the \c horizontal_width of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (horizontal_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->horizontal_width = horizontal_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c rectangle_height of a DXF \c MTEXT entity.
 *
 * \return the \c rectangle_height.
 */
double
dxf_mtext_get_rectangle_height
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->rectangle_height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->rectangle_height);
}


/*!
 * \brief Set the \c rectangle_height of a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_rectangle_height
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double rectangle_height
                /*!< the \c rectangle_height of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (rectangle_height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->rectangle_height = rectangle_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c spacing_factor of a DXF \c MTEXT entity.
 *
 * \return the \c spacing_factor.
 */
double
dxf_mtext_get_spacing_factor
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->spacing_factor < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->spacing_factor);
}


/*!
 * \brief Set the \c spacing_factor of a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_spacing_factor
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double spacing_factor
                /*!< the \c spacing_factor of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (spacing_factor < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->spacing_factor = spacing_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c box_scale of a DXF \c MTEXT entity.
 *
 * \return the \c box_scale.
 */
double
dxf_mtext_get_box_scale
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->box_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->box_scale);
}


/*!
 * \brief Set the \c box_scale of a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_box_scale
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double box_scale
                /*!< the \c box_scale of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (box_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->box_scale = box_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c column_width of a DXF \c MTEXT entity.
 *
 * \return the \c column_width.
 */
double
dxf_mtext_get_column_width
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->column_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->column_width);
}


/*!
 * \brief Set the \c column_width of a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_column_width
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double column_width
                /*!< the \c column_width of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (column_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->column_width = column_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c column_gutter of a DXF \c MTEXT entity.
 *
 * \return the \c column_width.
 */
double
dxf_mtext_get_column_gutter
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->column_gutter < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->column_gutter);
}


/*!
 * \brief Set the \c column_gutter of a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_column_gutter
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double column_gutter
                /*!< the \c column_gutter of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (column_gutter < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->column_gutter = column_gutter;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c column_heights of a DXF \c MTEXT entity.
 *
 * \return the \c column_heights.
 */
double
dxf_mtext_get_column_heights
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (mtext->column_heights < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->column_heights);
}


/*!
 * \brief Set the \c column_heights of a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_column_heights
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double column_heights
                /*!< the \c column_heights of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        if (column_heights < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->column_heights = column_heights;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c rot_angle of a DXF \c MTEXT entity.
 *
 * \return the \c rot_angle.
 */
double
dxf_mtext_get_rot_angle
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        return (mtext->rot_angle);
}


/*!
 * \brief Set the \c rot_angle of a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_rot_angle
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double rot_angle
                /*!< the \c rot_angle of a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        mtext->rot_angle = rot_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c background_color from a DXF \c MTEXT entity.
 *
 * \return \c background_color.
 */
int
dxf_mtext_get_background_color
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
        if (mtext->background_color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->background_color);
}


/*!
 * \brief Set the \c background_color for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_background_color
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int background_color
                /*!< the \c background_color to be set for the entity. */
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
        if (background_color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->background_color = background_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c attachment_point from a DXF \c MTEXT entity.
 *
 * \return \c attachment_point.
 */
int
dxf_mtext_get_attachment_point
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
        if (mtext->attachment_point < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mtext->attachment_point > 9)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->attachment_point);
}


/*!
 * \brief Set the \c attachment_point for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_attachment_point
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int attachment_point
                /*!< the \c attachment_point to be set for the entity. */
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
        if (attachment_point < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (attachment_point > 9)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->attachment_point = attachment_point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c drawing_direction from a DXF \c MTEXT entity.
 *
 * \return \c drawing_direction.
 */
int
dxf_mtext_get_drawing_direction
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
        if (mtext->drawing_direction < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mtext->drawing_direction > 5)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->drawing_direction);
}


/*!
 * \brief Set the \c drawing_direction for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_drawing_direction
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int drawing_direction
                /*!< the \c drawing_direction to be set for the entity. */
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
        if (drawing_direction < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (drawing_direction > 5)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->drawing_direction = drawing_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c spacing_style from a DXF \c MTEXT entity.
 *
 * \return \c spacing_style.
 */
int
dxf_mtext_get_spacing_style
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
        if (mtext->spacing_style < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mtext->spacing_style > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->spacing_style);
}


/*!
 * \brief Set the \c spacing_style for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_spacing_style
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int spacing_style
                /*!< the \c spacing_style to be set for the entity. */
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
        if (spacing_style < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (spacing_style > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->spacing_style = spacing_style;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c column_type from a DXF \c MTEXT entity.
 *
 * \return \c column_type.
 */
int
dxf_mtext_get_column_type
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
        if (mtext->column_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->column_type);
}


/*!
 * \brief Set the \c column_type for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_column_type
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int column_type
                /*!< the \c column_type to be set for the entity. */
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
        if (column_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->column_type = column_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c column_count from a DXF \c MTEXT entity.
 *
 * \return \c column_count.
 */
int
dxf_mtext_get_column_count
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
        if (mtext->column_count < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->column_count);
}


/*!
 * \brief Set the \c column_count for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_column_count
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int column_count
                /*!< the \c column_count to be set for the entity. */
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
        if (column_count < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->column_count = column_count;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c column_flow from a DXF \c MTEXT entity.
 *
 * \return \c column_flow.
 */
int
dxf_mtext_get_column_flow
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
        if (mtext->column_flow < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->column_flow);
}


/*!
 * \brief Set the \c column_flow for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_column_flow
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int column_flow
                /*!< the \c column_flow to be set for the entity. */
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
        if (column_flow < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->column_flow = column_flow;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c column_autoheight from a DXF \c MTEXT entity.
 *
 * \return \c column_autoheight.
 */
int
dxf_mtext_get_column_autoheight
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
        if (mtext->column_autoheight < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->column_autoheight);
}


/*!
 * \brief Set the \c column_autoheight for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_column_autoheight
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int column_autoheight
                /*!< the \c column_autoheight to be set for the entity. */
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
        if (column_autoheight < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->column_autoheight = column_autoheight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c background_fill from a DXF \c MTEXT entity.
 *
 * \return \c background_fill.
 */
int
dxf_mtext_get_background_fill
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
        if (mtext->background_fill < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mtext->background_fill > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext->background_fill);
}


/*!
 * \brief Set the \c background_fill for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_background_fill
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int background_fill
                /*!< the \c background_fill to be set for the entity. */
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
        if (background_fill < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (background_fill > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mtext->background_fill = background_fill;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c MTEXT entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_mtext_get_extr_x0
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        return (mtext->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_extr_x0
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        mtext->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c MTEXT entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_mtext_get_extr_y0
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        return (mtext->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_extr_y0
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        mtext->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c MTEXT entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_mtext_get_extr_z0
(
        DxfMtext *mtext
                /*!< a pointer to a DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        return (mtext->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_extr_z0
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c MTEXT entity. */
)
{
#ifdef DEBUG
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
        mtext->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF
 * \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_extrusion_vector_from_point
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
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
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->extr_x0 = (double) point->x0;
        mtext->extr_y0 = (double) point->y0;
        mtext->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Set the extrusion vector for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_extrusion_vector
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        double extr_x0,
                /*!<  X-value of the extrusion direction. */
        double extr_y0,
                /*!<  Y-value of the extrusion direction. */
        double extr_z0
                /*!<  Z-value of the extrusion direction. */
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
        mtext->extr_x0 = extr_x0;
        mtext->extr_y0 = extr_y0;
        mtext->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c background_color_rgb from a DXF \c MTEXT entity.
 *
 * \return \c background_color_rgb.
 */
int32_t
dxf_mtext_get_background_color_rgb
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
        return (mtext->background_color_rgb);
}


/*!
 * \brief Set the \c background_color_rgb for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_background_color_rgb
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int32_t background_color_rgb
                /*!< the \c background_color_rgb to be set for the entity. */
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
        mtext->background_color_rgb = background_color_rgb;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c background_color_name from a DXF \c MTEXT entity.
 *
 * \return \c background_color_name when sucessful, or \c NULL when an
 * error occurred.
 */
char *
dxf_mtext_get_background_color_name
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
        if (mtext->background_color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mtext->background_color_name));
}


/*!
 * \brief Set the \c background_color_name for a DXF \c MTEXT entity.
 *
 * \return a pointer to \c mtext when successful, or \c NULL when an
 * error occurred.
 */
DxfMtext *
dxf_mtext_set_background_color_name
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        char *background_color_name
                /*!< a string containing the \c color_name for the
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
        if (background_color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->background_color_name = strdup (background_color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the \c background_transparency from a DXF \c MTEXT entity.
 *
 * \return \c background_transparency.
 */
int32_t
dxf_mtext_get_background_transparency
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
        return (mtext->background_transparency);
}


/*!
 * \brief Set the \c background_transparency for a DXF \c MTEXT entity.
 */
DxfMtext *
dxf_mtext_set_background_transparency
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        int32_t background_transparency
                /*!< the \c background_transparency to be set for the
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
        mtext->background_transparency = background_transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the pointer to the next \c MTEXT entity from a DXF 
 * \c MTEXT entity.
 *
 * \return pointer to the next \c MTEXT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMtext *
dxf_mtext_get_next
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
        if (mtext->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMtext *) mtext->next);
}


/*!
 * \brief Set the pointer to the next \c MTEXT for a DXF \c MTEXT
 * entity.
 */
DxfMtext *
dxf_mtext_set_next
(
        DxfMtext *mtext,
                /*!< a pointer to a DXF \c MTEXT entity. */
        DxfMtext *next
                /*!< a pointer to the next \c MTEXT for the entity. */
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
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mtext->next = (struct DxfMtext *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mtext);
}


/*!
 * \brief Get the pointer to the last \c MTEXT entity from a linked list
 * of DXF \c MTEXT entities.
 *
 * \return pointer to the last \c MTEXT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMtext *
dxf_mtext_get_last
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
        if (mtext->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMtext *) mtext);
        }
        DxfMtext *iter = (DxfMtext *) mtext->next;
        while (iter->next != NULL)
        {
                iter = (DxfMtext *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMtext *) iter);
}


/* EOF */
