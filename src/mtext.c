/*!
 * \file mtext.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF mtext entity (\c MTEXT).
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_mtext_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfMtext *dxf_mtext = NULL;
        size_t size;

        size = sizeof (DxfMtext);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_mtext = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_mtext_new () could not allocate memory for a DxfMtext struct.\n");
                dxf_mtext = NULL;
        }
        else
        {
                memset (dxf_mtext, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_mtext_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_mtext);
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
        DxfMtext *dxf_mtext
                /*!< DXF mtext entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_mtext_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        dxf_mtext = dxf_mtext_new ();
        if (dxf_mtext == NULL)
        {
              fprintf (stderr, "ERROR in dxf_mtext_init () could not allocate memory for a DxfMtext struct.\n");
              return (NULL);
        }
        dxf_mtext->common.id_code = 0;
        dxf_mtext->text_value = strdup ("");
        for (i = 1; i < MAX_NUMBER_ADDITIONAL; i++)
        {
                dxf_mtext->text_additional_value[i] = strdup ("");
        }
        dxf_mtext->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_mtext->text_style = strdup ("");
        dxf_mtext->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_mtext->x0 = 0.0;
        dxf_mtext->y0 = 0.0;
        dxf_mtext->z0 = 0.0;
        dxf_mtext->x1 = 0.0;
        dxf_mtext->y1 = 0.0;
        dxf_mtext->z1 = 0.0;
        dxf_mtext->height = 0.0;
        dxf_mtext->rectangle_width = 0.0;
        dxf_mtext->horizontal_width = 0.0;
        dxf_mtext->rectangle_height = 0.0;
        dxf_mtext->spacing_factor = 0.0;
        dxf_mtext->box_scale = 0.0;
        dxf_mtext->column_width = 0.0;
        dxf_mtext->column_gutter = 0.0;
        dxf_mtext->column_heights = 0.0;
        dxf_mtext->rot_angle = 0.0;
        dxf_mtext->common.color = DXF_COLOR_BYLAYER;
        dxf_mtext->background_color = 0;
        dxf_mtext->common.paperspace = DXF_MODELSPACE;
        dxf_mtext->attachment_point = 0;
        dxf_mtext->drawing_direction = 0;
        dxf_mtext->spacing_style = 0;
        dxf_mtext->column_type = 0;
        dxf_mtext->column_count = 0;
        dxf_mtext->column_flow = 0;
        dxf_mtext->column_autoheight = 0;
        dxf_mtext->background_fill = 0;
        dxf_mtext->common.acad_version_number = 0;
        dxf_mtext->extr_x0 = 0.0;
        dxf_mtext->extr_y0 = 0.0;
        dxf_mtext->extr_z0 = 0.0;
      //dxf_mtext->background_color_rgb = 0;
      //dxf_mtext->background_color_name = strdup ("");
      //dxf_mtext->bacground_transparency = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_mtext_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_mtext);
}


/*!
 * \brief Read data from a DXF file into a \c MTEXT entity.
 *
 * The last line read from file contained the string "MTEXT". \n
 * Now follows some data for the \c MTEXT, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_mtext. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mtext_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfMtext *dxf_mtext,
                /*!< DXF mtext entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_mtext_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_mtext)
        {
                dxf_mtext = dxf_mtext_new ();
        }
        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_mtext_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a text value. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_mtext->text_value);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a text value. */
                        (*line_number)++;
                        //fscanf (fp, "%s\n", dxf_mtext->text_additional_value[number_additional]);
                        //number_additional++;
                }
                /*!< I'm not sure this number_additional is correct.*/
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_mtext->common.id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_mtext->common.linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_mtext->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_mtext->common.layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->z0);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * reference rectangle width. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->rectangle_width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal width of the characters. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->horizontal_width);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * vertical rectangle height. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->rectangle_height);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the
                         * text line spacing factor. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->spacing_factor);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing the
                         * fill box scale (border around text). */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->box_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the
                         * column width. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->column_width);
                }
                else if (strcmp (temp_string, "49") == 0)
                {
                        /* Now follows a string containing the
                         * column gutter. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->column_gutter);
                }
                else if ((acad_version_number <= AutoCAD_2006)
                        && (strcmp (temp_string, "50") == 0))
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->rot_angle);
                }
                else if ((acad_version_number >= AutoCAD_2007)
                        && (strcmp (temp_string, "50") == 0))
                {
                        /* Can follows a string containing the
                         * rotation angle or column heights. */
                        (*line_number)++;
                /*!< Add more code here, I'm stop because the double use of group code 50*/
                }
                else if (strcmp (temp_string, "63") == 0)
                {
                        /* Now follows a string containing the
                         * color to use for background fill. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->background_color);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * attachment point. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->attachment_point);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * drawing direction. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->drawing_direction);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * mtext line spacing style. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->spacing_style);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the
                         * column type. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->column_type);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing the
                         * column count. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->column_count);
                }
                else if (strcmp (temp_string, "78") == 0)
                {
                        /* Now follows a string containing the
                         * column flow reverse. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->column_flow);
                }
                else if (strcmp (temp_string, "79") == 0)
                {
                        /* Now follows a string containing the
                         * column autoheight. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->column_autoheight);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * background fill setting. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_mtext->background_fill);
                }
                else if ((acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_mtext->extr_z0);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }

                else
                {
                        fprintf (stderr, "Warning: in dxf_mtext_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_mtext_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF */
