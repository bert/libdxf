/*!
 * \file ray.c
 *
 * \author Copyright (C) 2013 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF ray entity (\c RAY).
 *
 * \warning The ray entity requires AutoCAD version R13 or higher.\n
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


#include "ray.h"


/*!
 * \brief Allocate memory for a \c DxfRay.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfRay *
dxf_ray_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfRay *dxf_ray = NULL;
        size_t size;

        size = sizeof (DxfRay);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_ray = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRay struct.\n")),
                  __FUNCTION__);
                dxf_ray = NULL;
        }
        else
        {
                memset (dxf_ray, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ray);
}


/*!
 * \brief Allocate memory and initialize data fields in an \c RAY entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfRay *
dxf_ray_init
(
        DxfRay *dxf_ray
                /*!< DXF line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_ray == NULL)
        {
                fprintf (stderr,
                  (_("WARNING in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ray = dxf_ray_new ();
        }
        if (dxf_ray == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfRay struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_ray->id_code = 0;
        dxf_ray->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_ray->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_ray->x0 = 0.0;
        dxf_ray->y0 = 0.0;
        dxf_ray->z0 = 0.0;
        dxf_ray->x1 = 0.0;
        dxf_ray->y1 = 0.0;
        dxf_ray->z1 = 0.0;
        dxf_ray->thickness = 0.0;
        dxf_ray->color = DXF_COLOR_BYLAYER;
        dxf_ray->paperspace = DXF_MODELSPACE;
        dxf_ray->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ray);
}


/*!
 * \brief Read data from a DXF file into an \c LINE entity.
 *
 * The last line read from file contained the string "LINE". \n
 * Now follows some data for the \c LINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_ray.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfRay *
dxf_ray_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfRay *dxf_ray
                /*!< DXF ellipse entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_ray == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ray = dxf_ray_new ();
                dxf_ray_init (dxf_ray);
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
                        fscanf (fp->fp, "%x\n", &dxf_ray->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ray->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ray->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_ray->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->z0);
                        /*! \todo Consider to add 
                         * dxf_ray->z1 = dxf_ray.z0;
                         * for the elevation could affect both
                         * Z-coordinates. */
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ray->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ray->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbRay") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
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
        /* Handle omitted members and/or illegal values. */
        if (strcmp (dxf_ray->linetype, "") == 0)
        {
                dxf_ray->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_ray->layer, "") == 0)
        {
                dxf_ray->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ray);
}


/*!
 * \brief Write DXF output to fp for a line entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occured.
 */
int
dxf_ray_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfRay *dxf_ray
                /*!< DXF line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("RAY");

        /* Do some basic checks. */
        if (dxf_ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((dxf_ray->x0 == dxf_ray->x1)
                && (dxf_ray->y0 == dxf_ray->y1)
                && (dxf_ray->z0 == dxf_ray->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () start point and end point are identical for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_ray->id_code);
                dxf_entity_skip (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_ray->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_ray->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_ray->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_ray->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_ray->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                dxf_ray->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ray->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_ray->id_code);
        }
        if (strcmp (dxf_ray->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_ray->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_ray->layer);
        fprintf (fp->fp, " 10\n%f\n", dxf_ray->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_ray->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_ray->z0);
        fprintf (fp->fp, " 11\n%f\n", dxf_ray->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_ray->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_ray->z1);
        if (dxf_ray->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_ray->thickness);
        }
        if (dxf_ray->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_ray->color);
        }
        if (dxf_ray->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c RAY and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ray_free
(
        DxfRay *dxf_ray
                /*!< Pointer to the memory occupied by the DXF \c RAY
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_ray->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfRay was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_ray->linetype);
        free (dxf_ray->layer);
        free (dxf_ray);
        dxf_ray = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
