/*!
 * \file ray.c
 *
 * \author Copyright (C) 2013 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Warning in %s () a NULL pointer was passed.\n")),
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
        dxf_ray->elevation = 0.0;
        dxf_ray->thickness = 0.0;
        dxf_ray->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_ray->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_ray->color = DXF_COLOR_BYLAYER;
        dxf_ray->paperspace = DXF_MODELSPACE;
        dxf_ray->dictionary_owner_soft = strdup ("");
        dxf_ray->dictionary_owner_hard = strdup ("");
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dxf_ray == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ray = dxf_ray_new ();
                dxf_ray = dxf_ray_init (dxf_ray);
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
                        && (dxf_ray->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ray->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_ray->visibility);
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
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ray->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ray->dictionary_owner_hard);
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
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
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ray->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_ray->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (dxf_ray->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_ray->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_ray->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_ray->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_ray->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_ray->layer);
        if (strcmp (dxf_ray->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_ray->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_ray->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_ray->elevation);
        }
        if (dxf_ray->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_ray->color);
        }
        if (dxf_ray->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_ray->linetype_scale);
        }
        if (dxf_ray->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_ray->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbRay\n");
        }
        if (dxf_ray->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_ray->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_ray->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_ray->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_ray->z0);
        fprintf (fp->fp, " 11\n%f\n", dxf_ray->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_ray->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_ray->z1);
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        free (dxf_ray->dictionary_owner_soft);
        free (dxf_ray->dictionary_owner_hard);
        free (dxf_ray);
        dxf_ray = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
