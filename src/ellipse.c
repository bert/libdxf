/*!
 * \file ellipse.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * \brief Allocate memory for a DXF \c ELLIPSE.
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
        DXF_DEBUG_BEGIN
#endif
        DxfEllipse *dxf_ellipse = NULL;
        size_t size;

        size = sizeof (DxfEllipse);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_ellipse = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfEllipse struct.\n")),
                  __FUNCTION__);
                dxf_ellipse = NULL;
        }
        else
        {
                memset (dxf_ellipse, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ellipse);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c ELLIPSE
 * entity.
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
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ellipse = dxf_ellipse_new ();
        }
        if (dxf_ellipse == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfEllipse struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_ellipse->id_code = 0;
        dxf_ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_ellipse->x0 = 0.0;
        dxf_ellipse->y0 = 0.0;
        dxf_ellipse->z0 = 0.0;
        dxf_ellipse->x1 = 0.0;
        dxf_ellipse->y1 = 0.0;
        dxf_ellipse->z1 = 0.0;
        dxf_ellipse->extr_x0 = 0.0;
        dxf_ellipse->extr_y0 = 0.0;
        dxf_ellipse->extr_z0 = 0.0;
        dxf_ellipse->elevation = 0.0;
        dxf_ellipse->thickness = 0.0;
        dxf_ellipse->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_ellipse->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_ellipse->ratio = 0.0;
        dxf_ellipse->start_angle = 0.0;
        dxf_ellipse->end_angle = 0.0;
        dxf_ellipse->color = DXF_COLOR_BYLAYER;
        dxf_ellipse->paperspace = DXF_MODELSPACE;
        dxf_ellipse->dictionary_owner_soft = strdup ("");
        dxf_ellipse->dictionary_owner_hard = strdup ("");
        dxf_ellipse->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ellipse);
}


/*!
 * \brief Read data from a DXF file into a DXF \c ELLIPSE entity.
 *
 * The last line read from file contained the string "ELLIPSE". \n
 * Now follows some data for the \c ELLIPSE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_ellipse. \n
 *
 * \return a pointer to \c dxf_ellipse.
 */
DxfEllipse *
dxf_ellipse_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfEllipse *dxf_ellipse
                /*!< DXF ellipse entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_ellipse = dxf_ellipse_new ();
                dxf_ellipse_init (dxf_ellipse);
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
                        fscanf (fp->fp, "%x\n", &dxf_ellipse->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ellipse->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ellipse->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_ellipse->elevation = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->ratio);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * start angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->start_angle);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->end_angle);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_ellipse->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ellipse->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_ellipse->paperspace);
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
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbEllipse") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_ellipse->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ellipse->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_ellipse->dictionary_owner_hard);
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
        if (strcmp (dxf_ellipse->linetype, "") == 0)
        {
                dxf_ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_ellipse->layer, "") == 0)
        {
                dxf_ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_ellipse);
}


/*!
 * \brief Write DXF output to a file for a DXF \c ELLIPSE entity.
 *
 * The ellipse entity (elliptic arc) requires AutoCAD version R14 or
 * higher.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ellipse_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfEllipse *dxf_ellipse
                /*!< DXF ellipse entity */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ELLIPSE");

        /* Do some basic checks. */
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_ellipse->ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () ratio value equals 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_ellipse->id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_ellipse->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_ellipse->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_ellipse->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_ellipse->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_ellipse->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_ellipse->id_code);
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
        if ((strcmp (dxf_ellipse->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_ellipse->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_ellipse->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_ellipse->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_ellipse->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_ellipse->layer);
        if (strcmp (dxf_ellipse->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_ellipse->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_ellipse->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_ellipse->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (dxf_ellipse->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_ellipse->thickness);
        }
        if (dxf_ellipse->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_ellipse->color);
        }
        if (dxf_ellipse->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_ellipse->linetype_scale);
        }
        if (dxf_ellipse->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_ellipse->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEllipse\n");
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_ellipse->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_ellipse->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_ellipse->z0);
        fprintf (fp->fp, " 11\n%f\n", dxf_ellipse->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_ellipse->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_ellipse->z1);
        fprintf (fp->fp, " 210\n%f\n", dxf_ellipse->extr_x0);
        fprintf (fp->fp, " 220\n%f\n", dxf_ellipse->extr_y0);
        fprintf (fp->fp, " 230\n%f\n", dxf_ellipse->extr_z0);
        fprintf (fp->fp, " 40\n%f\n", dxf_ellipse->ratio);
        fprintf (fp->fp, " 41\n%f\n", dxf_ellipse->start_angle);
        fprintf (fp->fp, " 42\n%f\n", dxf_ellipse->end_angle);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ELLIPSE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ellipse_free
(
        DxfEllipse *dxf_ellipse
                /*!< Pointer to the memory occupied by the DXF
                 * \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_ellipse->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfEllipse was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_ellipse->linetype);
        free (dxf_ellipse->layer);
        free (dxf_ellipse->dictionary_owner_soft);
        free (dxf_ellipse->dictionary_owner_hard);
        free (dxf_ellipse);
        dxf_ellipse = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
