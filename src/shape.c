/*!
 * \file shape.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF shape entity (\c SHAPE).
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


#include "shape.h"


/*!
 * \brief Allocate memory for a \c DxfShape.
 *
 * Fill the memory contents with zeros.
 */
DxfShape *
dxf_shape_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_shape_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfShape *dxf_shape = NULL;
        size_t size;

        size = sizeof (DxfShape);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_shape = malloc (size)) == NULL)
        {
                fprintf (stderr, "[File: %s: line: %d] Out of memory in dxf_shape_new ()\n",
                        __FILE__, __LINE__);
                dxf_shape = NULL;
        }
        else
        {
                memset (dxf_shape, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_shape_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_shape);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SHAPE 
 * entity to default values.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfShape *
dxf_shape_init
(
        DxfShape *dxf_shape
                /*!< DXF shape entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_shape_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_shape = dxf_shape_new ();
        if (dxf_shape == NULL)
        {
              fprintf(stderr, "ERROR: could not allocate memory for a DxfShape struct.\n");
              return (NULL);
        }
        dxf_shape->common.id_code = 0;
        dxf_shape->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_shape->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_shape->x0 = 0.0;
        dxf_shape->y0 = 0.0;
        dxf_shape->z0 = 0.0;
        dxf_shape->extr_x0 = 0.0;
        dxf_shape->extr_y0 = 0.0;
        dxf_shape->extr_z0 = 0.0;
        dxf_shape->size = 0.0;
        dxf_shape->rel_x_scale = 0.0;
        dxf_shape->rot_angle = 0.0;
        dxf_shape->obl_angle = 0.0;
        dxf_shape->common.color = DXF_COLOR_BYLAYER;
        dxf_shape->common.paperspace = DXF_MODELSPACE;
        dxf_shape->common.acad_version_number = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_shape_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_shape);
}


/*!
 * \brief Read data from a DXF file into a \c SHAPE entity.
 *
 * The last line read from file contained the string "SHAPE". \n
 * Hereafter follows some data for the \c SHAPE, to be terminated with
 * a "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 *
 * \return \c EXIT_SUCCESS when done, or \cEXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_shape_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfShape *dxf_shape,
                /*!< DXF arc entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_shape_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_shape)
        {
                dxf_shape = dxf_shape_new ();
        }
        line_number++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error: in dxf_shape_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        line_number++;
                        fscanf (fp, "%x\n", &dxf_shape->common.id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        line_number++;
                        fscanf (fp, "%s\n", dxf_shape->common.linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        line_number++;
                        fscanf (fp, "%s\n", dxf_shape->common.layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->z0);
                }
                else if ((acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_shape->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->common.thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * size. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->size);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X scale. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->rel_x_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * oblique angle. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->obl_angle);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        line_number++;
                        fscanf (fp, "%d\n", &dxf_shape->common.color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        line_number++;
                        fscanf (fp, "%d\n", &dxf_shape->common.paperspace);
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
                        fscanf (fp, "%lf\n", &dxf_shape->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        line_number++;
                        fscanf (fp, "%lf\n", &dxf_shape->extr_z0);
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
                        fprintf (stderr, "Warning: in dxf_shape_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_shape_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a shape entity.
 */
int
dxf_shape_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *shape_name,
                /*!< group code = 2. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to \c BYLAYER. */
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
        double size,
                /*!< group code = 40. */
        double rel_x_scale,
                /*!< group code = 41\n
                 * optional, defaults to 1.0. */
        double rot_angle,
                /*!< group code = 50\n
                 * optional, defaults to 0.0. */
        double obl_angle,
                /*!< group code = 51\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER. */
        int paperspace
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_shape_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("SHAPE");

        if (strcmp (shape_name, "") == 0)
        {
                fprintf (stderr, "Error: %s name string is empty for the %s entity with id-code: %x\n", dxf_entity_name, dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning: in dxf_shape_write_lowlevel () empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0", dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (size == 0.0)
        {
                fprintf (stderr, "Warning: in dxf_shape_write_lowlevel () size has a value of 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
        }
        if (rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning: in dxf_shape_write_lowlevel () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  2\n%s\n", shape_name);
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
        fprintf (fp, " 40\n%f\n", size);
        if (rel_x_scale != 1.0)
        {
                fprintf (fp, " 41\n%f\n", rel_x_scale);
        }
        if (rot_angle != 0.0)
        {
                fprintf (fp, " 50\n%f\n", rot_angle);
        }
        if (obl_angle != 0.0)
        {
                fprintf (fp, " 51\n%f\n", obl_angle);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_shape_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a shape entity.
 */
int
dxf_shape_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfShape dxf_shape
                /*!< DXF shape entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_shape_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("SHAPE");

        if (&dxf_shape == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr, "Error: in dxf_shape_write () NULL pointer passed to dxf_shape_write ().\n");
        }
                if (strcmp (dxf_shape.shape_name, "") == 0)
        {
                fprintf (stderr, "Error: in dxf_shape_write () %s name string is empty for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_entity_name, dxf_shape.common.id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_shape.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning: in dxf_shape_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_shape.common.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_shape.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_shape.size == 0.0)
        {
                fprintf (stderr, "Warning: in dxf_shape_write () size has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_shape.common.id_code);
        }
        if (dxf_shape.rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning: in dxf_shape_write () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_shape.common.id_code);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  2\n%s\n", dxf_shape.shape_name);
        if (dxf_shape.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_shape.common.id_code);
        }
        if (strcmp (dxf_shape.common.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_shape.common.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_shape.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_shape.x0);
        fprintf (fp, " 20\n%f\n", dxf_shape.y0);
        fprintf (fp, " 30\n%f\n", dxf_shape.z0);
        if (dxf_shape.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_shape.common.thickness);
        }
        fprintf (fp, " 40\n%f\n", dxf_shape.size);
        if (dxf_shape.rel_x_scale != 1.0)
        {
                fprintf (fp, " 41\n%f\n", dxf_shape.rel_x_scale);
        }
        if (dxf_shape.rot_angle != 0.0)
        {
                fprintf (fp, " 50\n%f\n", dxf_shape.rot_angle);
        }
        if (dxf_shape.obl_angle != 0.0)
        {
                fprintf (fp, " 51\n%f\n", dxf_shape.obl_angle);
        }
        if (dxf_shape.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_shape.common.color);
        }
        if (dxf_shape.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_shape_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
