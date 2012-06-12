/*!
 * \file ellipse.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF ellipse entity (\c ELLIPSE).
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


#include "ellipse.h"


/*!
 * \brief Allocate memory for a \c DxfEllipse.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfEllipse *
dxf_ellipse_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ellipse_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfEllipse *dxf_ellipse = NULL;
        size_t size;

        size = sizeof (DxfEllipse);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_ellipse = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_ellipse_new () could not allocate memory for a DxfEllipse struct.\n");
                dxf_ellipse = NULL;
        }
        else
        {
                memset (dxf_ellipse, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ellipse_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_ellipse);
}


/*!
 * \brief Allocate memory and initialize data fields in an \c ELLIPSE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfEllipse *
dxf_ellipse_init
(
        DxfEllipse *dxf_ellipse
                /*!< DXF ellipse entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ellipse_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_ellipse = dxf_ellipse_new ();
        if (dxf_ellipse == NULL)
        {
              fprintf (stderr, "ERROR in dxf_ellipse_init () could not allocate memory for a DxfEllipse struct.\n");
              return (NULL);
        }
        dxf_ellipse->common.id_code = 0;
        dxf_ellipse->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_ellipse->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_ellipse->x0 = 0.0;
        dxf_ellipse->y0 = 0.0;
        dxf_ellipse->z0 = 0.0;
        dxf_ellipse->x1 = 0.0;
        dxf_ellipse->y1 = 0.0;
        dxf_ellipse->z1 = 0.0;
        dxf_ellipse->extr_x0 = 0.0;
        dxf_ellipse->extr_y0 = 0.0;
        dxf_ellipse->extr_z0 = 0.0;
        dxf_ellipse->common.thickness = 0.0;
        dxf_ellipse->ratio = 0.0;
        dxf_ellipse->start_angle = 0.0;
        dxf_ellipse->end_angle = 0.0;
        dxf_ellipse->common.color = DXF_COLOR_BYLAYER;
        dxf_ellipse->common.paperspace = DXF_MODELSPACE;
        dxf_ellipse->common.acad_version_number = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ellipse_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_ellipse);
}


/*!
 * \brief Read data from a DXF file into an \c ELLIPSE entity.
 *
 * The last line read from file contained the string "ELLIPSE". \n
 * Now follows some data for the \c ELLIPSE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_ellipse. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ellipse_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfEllipse *dxf_ellipse,
                /*!< DXF ellipse entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ellipse_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_ellipse_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (0);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_ellipse->common.id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_ellipse->common.linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_ellipse->common.layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->z1);
                }
                else if ((acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_ellipse->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->common.thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->ratio);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * start angle. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->start_angle);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->end_angle);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_ellipse->common.color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_ellipse->common.paperspace);
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
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbEllipse") != 0)))
                        {
                                fprintf (stderr, "Error in dxf_ellipse_read () found a bad subclass marker in: %s in line: %d.\n",
                                        filename, *line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_ellipse->extr_z0);
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
                        fprintf (stderr, "Warning: in dxf_ellipse_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ellipse_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an ellipse entity (elliptic arc).
 *
 * This entity requires AutoCAD version R14 or higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ellipse_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to BYLAYER. */
        char *layer,
                /*!< group code = 8.*/
        double x0,
                /*!< group code = 10\n
                 * base point. */
        double y0,
                /*!< group code = 20\n
                 * base point. */
        double z0,
                /*!< group code = 30\n
                 * base point. */
        double x1,
                /*!< group code = 11\n
                 * base point. */
        double y1,
                /*!< group code = 21\n
                 * base point. */
        double z1,
                /*!< group code = 31\n
                 * base point. */
        double extr_x0,
                /*!< group code = 210\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_y0,
                /*!< group code = 220\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_z0,
                /*!< group code = 230\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 1.0. */
        double thickness,
                /*!< group code = 39\n
                 *  optional, defaults to 0.0. */
        double ratio,
                /*!< group code = 40\n
                 * ratio of minor axis to major axis. */
        double start_angle,
                /*!< group code = 41. */
        double end_angle,
                /*!< group code = 42. */
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ellipse_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("ELLIPSE");

        if (acad_version_number < AC1014) /* AutoCAD 14 */
        {
                fprintf (stderr, "Error in dxf_ellipse_write_lowlevel () too old an AutoCAD version used for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (ratio == 0.0)
        {
                fprintf (stderr, "Error in dxf_ellipse_write_lowlevel () ratio value equals 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_ellipse_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
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
        fprintf (fp, " 210\n%f\n", extr_x0);
        fprintf (fp, " 220\n%f\n", extr_y0);
        fprintf (fp, " 230\n%f\n", extr_z0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        fprintf (fp, " 40\n%f\n", ratio);
        fprintf (fp, " 41\n%f\n", start_angle);
        fprintf (fp, " 42\n%f\n", end_angle);
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ellipse_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an ellipse entity (elliptic arc).
 *
 * This entity requires AutoCAD version R14 or higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ellipse_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfEllipse dxf_ellipse,
                /*!< DXF ellipse entity */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_ellipse_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("ELLIPSE");

        if (acad_version_number < AC1014) /* AutoCAD 14 */
        {
                fprintf (stderr, "Error in dxf_ellipse_write_lowlevel () too old an AutoCAD version used for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_ellipse.common.id_code);
                return (EXIT_FAILURE);
        }
        if (dxf_ellipse.ratio == 0.0)
        {
                fprintf (stderr, "Error in dxf_ellipse_write () ratio value equals 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_ellipse.common.id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_ellipse.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_ellipse_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_ellipse.common.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_ellipse.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ellipse.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_ellipse.common.id_code);
        }
        if (strcmp (dxf_ellipse.common.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_ellipse.common.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_ellipse.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_ellipse.x0);
        fprintf (fp, " 20\n%f\n", dxf_ellipse.y0);
        fprintf (fp, " 30\n%f\n", dxf_ellipse.z0);
        fprintf (fp, " 11\n%f\n", dxf_ellipse.x1);
        fprintf (fp, " 21\n%f\n", dxf_ellipse.y1);
        fprintf (fp, " 31\n%f\n", dxf_ellipse.z1);
        fprintf (fp, " 210\n%f\n", dxf_ellipse.extr_x0);
        fprintf (fp, " 220\n%f\n", dxf_ellipse.extr_y0);
        fprintf (fp, " 230\n%f\n", dxf_ellipse.extr_z0);
        if (dxf_ellipse.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_ellipse.common.thickness);
        }
        fprintf (fp, " 40\n%f\n", dxf_ellipse.ratio);
        fprintf (fp, " 41\n%f\n", dxf_ellipse.start_angle);
        fprintf (fp, " 42\n%f\n", dxf_ellipse.end_angle);
        if (dxf_ellipse.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_ellipse.common.color);
        }
        if (dxf_ellipse.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_ellipse_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
