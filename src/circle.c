/*!
 * \file circle.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF circle entity (\c CIRCLE).
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


#include "circle.h"


/*!
 * \brief Allocate memory for a \c DxfCircle.
 *
 * Fill the memory contents with zeros.
 */
DxfCircle *
dxf_circle_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_circle_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfCircle *dxf_circle = NULL;
        size_t size;

        size = sizeof (DxfCircle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_circle = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_circle_new () could not allocate memory for a DxfCircle struct.\n");
                dxf_circle = NULL;
        }
        else
        {
                memset (dxf_circle, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_circle_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_circle);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c CIRCLE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfCircle *
dxf_circle_init
(
        DxfCircle *dxf_circle
                /*!< DXF circle entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_circle_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_circle = dxf_circle_new ();
        if (dxf_circle == NULL)
        {
              fprintf(stderr, "ERROR in dxf_circle_init () could not allocate memory for a DxfCircle struct.\n");
              return (NULL);
        }
        dxf_circle->common.id_code = 0;
        dxf_circle->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_circle->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_circle->x0 = 0.0;
        dxf_circle->y0 = 0.0;
        dxf_circle->z0 = 0.0;
        dxf_circle->extr_x0 = 0.0;
        dxf_circle->extr_y0 = 0.0;
        dxf_circle->extr_z0 = 0.0;
        dxf_circle->common.thickness = 0.0;
        dxf_circle->radius = 0.0;
        dxf_circle->common.color = DXF_COLOR_BYLAYER;
        dxf_circle->common.paperspace = DXF_MODELSPACE;
        dxf_circle->common.acad_version_number = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_circle_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_circle);
}


/*!
 * \brief Read data from a DXF file into an \c CIRCLE entity.
 *
 * The last line read from file contained the string "CIRCLE". \n
 * Now follows some data for the \c CIRCLE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_circle. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_circle_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfCircle *dxf_circle,
                /*!< DXF circle entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_circle_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        line_number++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_circle_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (0);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        line_number++;
                        fscanf (fp, "%x\n", &dxf_circle->common.id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        line_number++;
                        fscanf (fp, "%s\n", dxf_circle->common.linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        line_number++;
                        fscanf (fp, "%s\n", dxf_circle->common.layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->z0);
                }
                else if ((acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_circle->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->common.thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->radius);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        line_number++;
                        fscanf (fp, "%d\n", &dxf_circle->common.color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        line_number++;
                        fscanf (fp, "%d\n", &dxf_circle->common.paperspace);
                }
                else if ((acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        line_number++;
                        fscanf (fp, "%s\n", temp_string);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_circle->extr_z0);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        line_number++;
                        fscanf (fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr, "Warning: in dxf_circle_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_circle_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a circle entity.
 */
int
dxf_circle_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * base point. */
        double y0,
                /*!< group code = 20\n
                 * base point. */
        double z0,
                /*!< group code = 30\n
                 * base point. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double radius,
                /*!< group code = 40. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to BYLAYER. */
        int paperspace,
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_circle_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("CIRCLE");

        if (radius == 0.0)
        {
                fprintf (stderr, "Error: in dxf_circle_write_lowlevel () radius value equals 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_circle_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
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
        fprintf (fp, " 30\n%f\n", z0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        fprintf (fp, " 40\n%f\n", radius);
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_circle_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/*!
 * \brief Write DXF output to fp for a circle entity.
 */
int
dxf_circle_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfCircle dxf_circle,
                /*!< DXF circle entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_circle_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("CIRCLE");

        if (dxf_circle.radius == 0.0)
        {
                fprintf (stderr, "Error in dxf_circle_write () radius value equals 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name,
                        dxf_circle.common.id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_circle.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_circle_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name,
                        dxf_circle.common.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name );
                dxf_circle.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_circle.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_circle.common.id_code);
        }
        if (strcmp (dxf_circle.common.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_circle.common.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_circle.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_circle.x0);
        fprintf (fp, " 20\n%f\n", dxf_circle.y0);
        fprintf (fp, " 30\n%f\n", dxf_circle.z0);
        if (dxf_circle.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_circle.common.thickness);
        }
        fprintf (fp, " 40\n%f\n", dxf_circle.radius);
        if (dxf_circle.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_circle.common.color);
        }
        if (dxf_circle.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_circle_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF */
