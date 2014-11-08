/*!
 * \file point.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF point entity (\c POINT).
 *
 * Point entities have an optional 50 group that determines the
 * orientation of \c PDMODE images.\n
 * The group value is the negative of the Entity Coordinate Systems
 * (ECS) angle of the UCS X axis in effect when the point was drawn.\n
 * The X-axis of the UCS in effect when the point was drawn is always
 * parallel to the XY plane for the point's ECS, and the angle between
 * the UCS X axis and the ECS X axis is a single 2D angle.\n
 * The value in group 50 is the angle from horizontal (the effective
 * X-axis) to the ECS X axis.\n
 *
 * Entity Coordinate Systems (ECS) are described ... somewhere else.
 *
 * \todo Add a link to somewhere else.
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


#include "point.h"


/*!
 * \brief Allocate memory for a \c DxfPoint.
 *
 * Fill the memory contents with zeros.
 */
DxfPoint *
dxf_point_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *dxf_point = NULL;
        size_t size;

        size = sizeof (DxfPoint);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_point = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                  __FUNCTION__);
                dxf_point = NULL;
        }
        else
        {
                memset (dxf_point, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_point);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c POINT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfPoint *
dxf_point_init
(
        DxfPoint *dxf_point
                /*!< DXF point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        dxf_point = dxf_point_new ();
        if (dxf_point == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_point->id_code = 0;
        dxf_point->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_point->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_point->x0 = 0.0;
        dxf_point->y0 = 0.0;
        dxf_point->z0 = 0.0;
        dxf_point->extr_x0 = 0.0;
        dxf_point->extr_y0 = 0.0;
        dxf_point->extr_z0 = 0.0;
        dxf_point->thickness = 0.0;
        dxf_point->color = DXF_COLOR_BYLAYER;
        dxf_point->paperspace = DXF_MODELSPACE;
        dxf_point->acad_version_number = 0;
        dxf_point->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_point);
}


/*!
 * \brief Read data from a DXF file into a \c POINT entity.
 *
 * The last line read from file contained the string "POINT". \n
 * Now follows some data for the \c POINT, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_point. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_point_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfPoint *dxf_point
                /*!< DXF ellipse entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

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
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_point->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_point->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_point->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_point->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_point->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_point->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_point->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_point->z0);
                        /*! \todo Consider to add 
                         * dxf_line->z1 = dxf_line->z0;
                         * for the elevation could affect both
                         * Z-coordinates. */
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_point->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_point->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_point->paperspace);
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
                        fscanf (fp->fp, "%lf\n", &dxf_point->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_point->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_point->extr_z0);
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
                          (_("Warning: in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a point entity.
 * 
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_point_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfPoint *dxf_point
                /*!< DXF point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("POINT");

        if (strcmp (dxf_point->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name,
                        dxf_point->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_point->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_point->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_point->id_code);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_point->layer);
        fprintf (fp->fp, " 10\n%f\n", dxf_point->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_point->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_point->z0);
        if (dxf_point->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_point->thickness);
        }
        if (dxf_point->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_point->color);
        }
        if (dxf_point->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
