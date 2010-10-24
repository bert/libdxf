/*!
 * \file solid.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF solid entity (\c SOLID).
 *
 * A DXF \c SOLID entity is a filled shape made with up to four point
 * (X, Y, Z)-coordinates.\n
 * A filled triangle can be formed by duplicating the third coordinate at the
 * fourth coordinate position.\n
 * A diabolo shaped solid can be formed by "twisting" the \SHAPE form in it's
 * plane, by "swapping" the third and fourth coordinate set.
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


#include "solid.h"


/*!
 * \brief Allocate memory for a \c DxfSolid.
 *
 * Fill the memory contents with zeros.
 */
DxfSolid *
dxf_solid_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_solid_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfSolid *dxf_solid = NULL;
        size_t size;

        size = sizeof (DxfSolid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_solid = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_solid_new () could not allocate memory for a DxfSolid struct.\n");
                dxf_solid = NULL;
        }
        else
        {
                memset (dxf_solid, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_solid_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_solid);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SOLID entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfSolid *
dxf_solid_init
(
        DxfSolid *dxf_solid
                /*!< DXF solid entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_solid_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_solid = dxf_solid_new ();
        if (dxf_solid == NULL)
        {
              fprintf (stderr, "ERROR in dxf_solid_init () could not allocate memory for a DxfSolid struct.\n");
              return (NULL);
        }
        dxf_solid->common.id_code = 0;
        dxf_solid->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_solid->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_solid->x0 = 0.0;
        dxf_solid->y0 = 0.0;
        dxf_solid->z0 = 0.0;
        dxf_solid->x1 = 0.0;
        dxf_solid->y1 = 0.0;
        dxf_solid->z1 = 0.0;
        dxf_solid->x2 = 0.0;
        dxf_solid->y2 = 0.0;
        dxf_solid->z2 = 0.0;
        dxf_solid->x3 = 0.0;
        dxf_solid->y3 = 0.0;
        dxf_solid->z3 = 0.0;
        dxf_solid->extr_x0 = 0.0;
        dxf_solid->extr_y0 = 0.0;
        dxf_solid->extr_z0 = 0.0;
        dxf_solid->common.thickness = 0.0;
        dxf_solid->common.color = DXF_COLOR_BYLAYER;
        dxf_solid->common.paperspace = DXF_MODELSPACE;
        dxf_solid->common.acad_version_number = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_solid_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_solid);
}


/*!
 * \brief Read data from a DXF file into an \c SOLID entity.
 *
 * The last line read from file contained the string "SOLID". \n
 * Now follows some data for the \c SOLID, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_solid_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfSolid *dxf_solid,
                /*!< DXF solid entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_solid_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_solid_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (0);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_solid->common.id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_solid->common.linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_solid->common.layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->x2);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->z3);
                }
                else if ((acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_solid->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->common.thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_solid->common.color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_solid->common.paperspace);
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
                        fscanf (fp, "%lf\n", &dxf_solid->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_solid->extr_z0);
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
                        fprintf (stderr, "Warning in dxf_solid_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_solid_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a solid entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_solid_write_lowlevel
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
                 * base point X-value, bottom left. */
        double y0,
                /*!< group code = 20\n
                 * base point Y-value, bottom left. */
        double z0,
                /*!< group code = 30\n
                 * base point Z-value, bottom left. */
        double x1,
                /*!< group code = 11\n
                 * alignment point X-vaule, bottom right. */
        double y1,
                /*!< group code = 21\n
                 * alignment point Y-vaule, bottom right. */
        double z1,
                /*!< group code = 31\n
                 * alignment point Z-vaule, bottom right. */
        double x2,
                /*!< group code = 12\n
                 * alignment point X-value, top left. */
        double y2,
                /*!< group code = 22\n
                 * alignment point Y-value, top left. */
        double z2,
                /*!< group code = 32\n
                 * alignment point Z-value, top left. */
        double x3,
                /*!< group code = 13\n
                 * alignment point X-value, top right. */
        double y3,
                /*!< group code = 23\n
                 * alignment point Y-value, top right. */
        double z3,
                /*!< group code = 33\n
                 * alignment point Z-value, top right. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER */
        int paperspace
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_solid_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("SOLID");

        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_solid_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
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
        fprintf (fp, " 11\n%f\n", x1);
        fprintf (fp, " 21\n%f\n", y1);
        fprintf (fp, " 31\n%f\n", z1);
        fprintf (fp, " 12\n%f\n", x2);
        fprintf (fp, " 22\n%f\n", y2);
        fprintf (fp, " 32\n%f\n", z2);
        fprintf (fp, " 13\n%f\n", x3);
        fprintf (fp, " 23\n%f\n", y3);
        fprintf (fp, " 33\n%f\n", z3);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
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
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_solid_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a solid entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_solid_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfSolid dxf_solid
                /*!< DXF solid entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_solid_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("SOLID");

        if (strcmp (dxf_solid.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_solid_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_solid.common.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_solid.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_solid.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_solid.common.id_code);
        }
        if (strcmp (dxf_solid.common.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_solid.common.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_solid.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_solid.x0);
        fprintf (fp, " 20\n%f\n", dxf_solid.y0);
        fprintf (fp, " 30\n%f\n", dxf_solid.z0);
        fprintf (fp, " 11\n%f\n", dxf_solid.x1);
        fprintf (fp, " 21\n%f\n", dxf_solid.y1);
        fprintf (fp, " 31\n%f\n", dxf_solid.z1);
        fprintf (fp, " 12\n%f\n", dxf_solid.x2);
        fprintf (fp, " 22\n%f\n", dxf_solid.y2);
        fprintf (fp, " 32\n%f\n", dxf_solid.z2);
        fprintf (fp, " 13\n%f\n", dxf_solid.x3);
        fprintf (fp, " 23\n%f\n", dxf_solid.y3);
        fprintf (fp, " 33\n%f\n", dxf_solid.z3);
        if (dxf_solid.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_solid.common.thickness);
        }
        if (dxf_solid.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_solid.common.color);
        }
        if (dxf_solid.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_solid_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
