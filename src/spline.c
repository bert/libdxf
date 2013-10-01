/*!
 * \file spline.c
 * 
 * \author Copyright (C) 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * 
 * \brief Functions for a DXF spline entity (\c SPLINE).
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


#include "spline.h"


/*!
 * \brief Allocate memory for a DXF \c SPLINE.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfSpline *
dxf_spline_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_spline_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfSpline *dxf_spline = NULL;
        size_t size;

        size = sizeof (DxfSpline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_spline = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_spline_new () could not allocate memory for a DxfSpline struct.\n");
                dxf_spline = NULL;
        }
        else
        {
                memset (dxf_spline, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_spline_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_spline);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SPLINE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfSpline *
dxf_spline_init
(
        DxfSpline *dxf_spline
                /*!< DXF spline entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_spline_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        dxf_spline = dxf_spline_new ();
        if (dxf_spline == NULL)
        {
              fprintf (stderr, "ERROR in dxf_spline_init () could not allocate memory for a DxfSpline struct.\n");
              return (NULL);
        }
        dxf_spline->id_code = 0;
        dxf_spline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_spline->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_spline->thickness = 0.0;
        dxf_spline->linetype_scale = 1.0;
        dxf_spline->visibility = 0;
        dxf_spline->color = DXF_COLOR_BYLAYER;
        dxf_spline->paperspace = DXF_MODELSPACE;
        dxf_spline->graphics_data_size = 0;
        dxf_spline->shadow_mode = 0;
        dxf_spline->dictionary_owner_soft = strdup ("");
        dxf_spline->material = strdup ("");
        dxf_spline->dictionary_owner_hard = strdup ("");
        dxf_spline->lineweight = 0;
        dxf_spline->plot_style_name = strdup ("");
        dxf_spline->color_value = 0;
        dxf_spline->color_name = strdup ("");
        dxf_spline->transparency = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_spline->binary_graphics_data[i] = strdup ("");
                dxf_spline->x0[i] = 0.0;
                dxf_spline->y0[i] = 0.0;
                dxf_spline->z0[i] = 0.0;
                dxf_spline->x1[i] = 0.0;
                dxf_spline->y1[i] = 0.0;
                dxf_spline->z1[i] = 0.0;
                dxf_spline->knot_value[i] = 0.0;
                dxf_spline->weight_value[i] = 0.0;
        }
        dxf_spline->x2 = 0.0;
        dxf_spline->y2 = 0.0;
        dxf_spline->z2 = 0.0;
        dxf_spline->x3 = 0.0;
        dxf_spline->y3 = 0.0;
        dxf_spline->z3 = 0.0;
        dxf_spline->extr_x0 = 0.0;
        dxf_spline->extr_y0 = 0.0;
        dxf_spline->extr_z0 = 0.0;
        dxf_spline->knot_tolerance = 0.0;
        dxf_spline->control_point_tolerance = 0.0;
        dxf_spline->fit_tolerance = 0.0;
        dxf_spline->flag = 0;
        dxf_spline->degree = 0;
        dxf_spline->number_of_knots = 0;
        dxf_spline->number_of_control_points = 0;
        dxf_spline->number_of_fit_points = 0;
        dxf_spline->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_spline_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_spline);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SPLINE entity.
 *
 * The last line read from file contained the string "SPLINE". \n
 * Now follows some data for the \c SPLINE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_spline. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSpline *dxf_spline
                /*!< DXF \c SPLINE entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_spline_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;
        int i_x0;
        int i_y0;
        int i_z0;
        int i_x1;
        int i_y1;
        int i_z1;
        int i_knot_value;
        int i_weight_value;
        int i_graphics_data_size;

        if (!dxf_spline)
        {
                dxf_spline = dxf_spline_new ();
        }
        i_x0 = 0;
        i_y0 = 0;
        i_z0 = 0;
        i_x1 = 0;
        i_y1 = 0;
        i_z1 = 0;
        i_knot_value = 0;
        i_weight_value = 0;
        i_graphics_data_size = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr, "Error in dxf_spline_read () while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_spline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_spline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_spline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the control point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->x0[i_x0]);
                        i_x0++;
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of control point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->y0[i_y0]);
                        i_y0++;
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the control point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->z0[i_z0]);
                        i_z0++;
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the fit point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->x1[i_x1]);
                        i_x1++;
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the fit point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->y1[i_y1]);
                        i_y1++;
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the fit point coordinate
                         * (multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->z1[i_z1]);
                        i_z1++;
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the end tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the end tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the end tangent,
                         * may be omitted (in WCS). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->z3);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a thickness value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->thickness);
                        i_knot_value++;
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a knot value (one entry per knot, multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->knot_value[i_knot_value]);
                        i_knot_value++;
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a weight value (one entry per knot, multiple entries). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->weight_value[i_weight_value]);
                        i_weight_value++;
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a knot tolerance value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->knot_tolerance);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a control point tolerance value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->control_point_tolerance);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a fit point tolerance value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->fit_tolerance);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a linetype scale value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_spline->linetype_scale);
                        i_knot_value++;
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_spline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_spline->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_spline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a flag value (bit coded). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_spline->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a degree of spline curve value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_spline->degree);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a number of knots value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_spline->number_of_knots);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a number of control points value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_spline->number_of_control_points);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a number of fit points value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_spline->number_of_fit_points);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_spline->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_spline->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_spline->binary_graphics_data[i_graphics_data_size]);
                        i_graphics_data_size++;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing a
                         * soft-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_spline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_spline->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_spline->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_spline->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_spline->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &dxf_spline->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_spline->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &dxf_spline->transparency);
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
                        fprintf (stderr, "Warning: in dxf_spline_read () unknown string tag found while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_spline_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SPLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spline_free
(
        DxfSpline *dxf_spline
                /*!< Pointer to the memory occupied by the DXF \c SPLINE
                 * entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_spline_free () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        if (dxf_spline->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_spline_free () pointer to next DxfSpline was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_spline->linetype);
        free (dxf_spline->layer);
        free (dxf_spline->dictionary_owner_soft);
        free (dxf_spline->material);
        free (dxf_spline->dictionary_owner_hard);
        free (dxf_spline->plot_style_name);
        free (dxf_spline->color_name);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_spline->binary_graphics_data[i]);
        }
        free (dxf_spline);
        dxf_spline = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_spline_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
