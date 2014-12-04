/*!
 * \file solid.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF solid entity (\c SOLID).
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
        DXF_DEBUG_BEGIN
#endif
        DxfSolid *dxf_solid = NULL;
        size_t size;

        size = sizeof (DxfSolid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_solid = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSolid struct.\n")),
                  __FUNCTION__);
                dxf_solid = NULL;
        }
        else
        {
                memset (dxf_solid, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
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
        DXF_DEBUG_BEGIN
#endif
        dxf_solid = dxf_solid_new ();
        if (dxf_solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSolid struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_solid->id_code = 0;
        dxf_solid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_solid->layer = strdup (DXF_DEFAULT_LAYER);
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
        dxf_solid->thickness = 0.0;
        dxf_solid->color = DXF_COLOR_BYLAYER;
        dxf_solid->paperspace = DXF_MODELSPACE;
        dxf_solid->acad_version_number = 0;
        dxf_solid->next = NULL;
#if DEBUG
        DXF_DEBUG_END
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
DxfSolid *
dxf_solid_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSolid *dxf_solid
                /*!< DXF solid entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        if (!dxf_solid)
        {
                dxf_solid = dxf_solid_new ();
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
                        fscanf (fp->fp, "%x\n", &dxf_solid->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_solid->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_solid->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->z3);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_solid->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_solid->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_solid->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_solid->extr_z0);
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_solid);
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
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSolid *dxf_solid
                /*!< DXF solid entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SOLID");

        if (strcmp (dxf_solid->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_solid->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_solid->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_solid->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_solid->id_code);
        }
        if (strcmp (dxf_solid->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_solid->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_solid->layer);
        fprintf (fp->fp, " 10\n%f\n", dxf_solid->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_solid->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_solid->z0);
        fprintf (fp->fp, " 11\n%f\n", dxf_solid->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_solid->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_solid->z1);
        fprintf (fp->fp, " 12\n%f\n", dxf_solid->x2);
        fprintf (fp->fp, " 22\n%f\n", dxf_solid->y2);
        fprintf (fp->fp, " 32\n%f\n", dxf_solid->z2);
        fprintf (fp->fp, " 13\n%f\n", dxf_solid->x3);
        fprintf (fp->fp, " 23\n%f\n", dxf_solid->y3);
        fprintf (fp->fp, " 33\n%f\n", dxf_solid->z3);
        if (dxf_solid->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_solid->thickness);
        }
        if (dxf_solid->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_solid->color);
        }
        if (dxf_solid->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
