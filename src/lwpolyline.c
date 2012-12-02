/*!
 * \file lwpolyline.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF light weight polyline entity (\c LWPOLYLINE).
 *
 * \warning This entity requires AutoCAD version 2004 or higher.
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


#include "lwpolyline.h"


/*!
 * \brief Allocate memory for a \c DxfLWPolyline.
 *
 * Fill the memory contents with zeros.
 */
DxfLWPolyline *
dxf_lwpolyline_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_lwpolyline_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfLWPolyline *dxf_lwpolyline = NULL;
        size_t size;

        size = sizeof (DxfLWPolyline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_lwpolyline = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_lwpolyline_new () could not allocate memory for a DxfArc struct.\n");
                dxf_lwpolyline = NULL;
        }
        else
        {
                memset (dxf_lwpolyline, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_lwpolyline_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_lwpolyline);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c LWPOLYLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLWPolyline *
dxf_lwpolyline_init
(
        DxfLWPolyline *dxf_lwpolyline
                /*!< DXF light weight polyline entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_lwpolyline_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_lwpolyline = dxf_lwpolyline_new ();
        if (dxf_lwpolyline == NULL)
        {
              fprintf (stderr, "ERROR in dxf_lwpolyline_init () could not allocate memory for a DxfLWPolyline struct.\n");
              return (NULL);
        }
        dxf_lwpolyline->id_code = 0;
        dxf_lwpolyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_lwpolyline->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_lwpolyline->x0 = 0.0;
        dxf_lwpolyline->y0 = 0.0;
        dxf_lwpolyline->thickness = 0.0;
        dxf_lwpolyline->start_width = 0.0;
        dxf_lwpolyline->end_width = 0.0;
        dxf_lwpolyline->constant_width = 0.0;
        dxf_lwpolyline->color = DXF_COLOR_BYLAYER;
        dxf_lwpolyline->paperspace = DXF_MODELSPACE;
        dxf_lwpolyline->flag = 0;
        dxf_lwpolyline->number_vertices = 0;
        dxf_lwpolyline->extr_x0 = 0.0;
        dxf_lwpolyline->extr_y0 = 0.0;
        dxf_lwpolyline->extr_z0 = 0.0;
        dxf_lwpolyline->acad_version_number = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_lwpolyline_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_lwpolyline);
}


/*!
 * \brief Read data from a DXF file into an \c LWPOLYLINE entity.
 *
 * The last line read from file contained the string "LWPOLYLINE". \n
 * Now follows some data for the \c LWPOLYLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_lwpolyline. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfLWPolyline *dxf_lwpolyline,
                /*!< DXF light weight polyline entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_lwpolyline_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_lwpolyline)
        {
                dxf_lwpolyline = dxf_lwpolyline_new ();
        }
        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_lwpolyline_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_lwpolyline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_lwpolyline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_lwpolyline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the primary point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the primary point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->y0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * starting width. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->start_width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * end width. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->end_width);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * constant width. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->constant_width);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_lwpolyline->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_lwpolyline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_lwpolyline->flag);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the number
                         * of following vertices. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_lwpolyline->number_vertices);
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
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_lwpolyline->extr_z0);
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
                        fprintf (stderr, "Warning: in dxf_lwpolyline_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_lwpolyline_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a light weight polyline entity.
 *
 * \warning This entity requires AutoCAD version 2004 or higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to \c BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * defaults to 0.0. */
        double y0,
                /*!< group code = 20\n
                 * defaults to 0.0. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double start_width,
                /*!< group code = 40\n
                 * optional, defaults to 0.0. */
        double end_width,
                /*!< group code = 41\n
                 * optional, defaults to 0.0. */
        double constant_width,
                /*!< group code = 43\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER. */
        int paperspace,
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int flag,
                /*!< group code = 70\n
                 * optional, defaults to 0. */
        int number_vertices,
                /*!< group code = 90. */
        double extr_x0,
                /*!< group code = 210\n
                 * Extrusion direction (optional; default = 0, 0, 1)\n
                 * DXF: X value;\n
                 * APP: 3D vector\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double extr_y0,
                /*!< group code = 220
                 * DXF: Y value of extrusion direction (optional). */
        double extr_z0,
                /*!< group code = 230
                 * DXF: Z value of extrusion direction (optional). */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_lwpolyline_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LWPOLYLINE");

        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_lwpolyline_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n",
                        dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        if ((constant_width = 0.0) && (start_width != end_width))
        {
                fprintf (fp, " 40\n%f\n", start_width);
                fprintf (fp, " 41\n%f\n", end_width);
        }
        else
        {
                fprintf (fp, " 43\n%f\n", constant_width);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", flag);
        fprintf (fp, " 90\n%d\n", number_vertices);
        if (acad_version_number >= AutoCAD_12)
        {
                fprintf (fp, "210\n%f\n", extr_x0);
                fprintf (fp, "220\n%f\n", extr_y0);
                fprintf (fp, "230\n%f\n", extr_z0);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_lwpolyline_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a light weight polyline entity.
 *
 * \warning This entity requires AutoCAD version 2004 or higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfLWPolyline dxf_lwpolyline,
                /*!< DXF polyline entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_lwpolyline_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("LWPOLYLINE");

        if (strcmp (dxf_lwpolyline.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_lwpolyline_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_lwpolyline.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0\n",
                        dxf_entity_name);
                dxf_lwpolyline.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_lwpolyline.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_lwpolyline.id_code);
        }
        if (strcmp (dxf_lwpolyline.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_lwpolyline.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_lwpolyline.layer);
        fprintf (fp, " 10\n%f\n", dxf_lwpolyline.x0);
        fprintf (fp, " 20\n%f\n", dxf_lwpolyline.y0);
        if (dxf_lwpolyline.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_lwpolyline.thickness);
        }
        if ((dxf_lwpolyline.constant_width = 0.0)
                && (dxf_lwpolyline.start_width != dxf_lwpolyline.end_width))
        {
                fprintf (fp, " 40\n%f\n", dxf_lwpolyline.start_width);
                fprintf (fp, " 41\n%f\n", dxf_lwpolyline.end_width);
        }
        else
        {
                fprintf (fp, " 43\n%f\n", dxf_lwpolyline.constant_width);
        }
        if (dxf_lwpolyline.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_lwpolyline.color);
        }
        if (dxf_lwpolyline.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", dxf_lwpolyline.flag);
        fprintf (fp, " 90\n%d\n", dxf_lwpolyline.number_vertices);
        if (dxf_lwpolyline.acad_version_number >= AutoCAD_12)
        {
                fprintf (fp, "210\n%f\n", dxf_lwpolyline.extr_x0);
                fprintf (fp, "220\n%f\n", dxf_lwpolyline.extr_y0);
                fprintf (fp, "230\n%f\n", dxf_lwpolyline.extr_z0);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_lwpolyline_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
