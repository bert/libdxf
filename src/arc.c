/*!
 * \file arc.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF arc entity (\c ARC).
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


#include "arc.h"


/*!
 * \brief Allocate memory for a DXF \c ARC.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfArc *
dxf_arc_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfArc *dxf_arc = NULL;
        size_t size;

        size = sizeof (DxfArc);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_arc = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfArc struct.\n")),
                  __FUNCTION__);
                dxf_arc = NULL;
        }
        else
        {
                memset (dxf_arc, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_arc);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c ARC
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfArc *
dxf_arc_init
(
        DxfArc *dxf_arc
                /*!< DXF arc entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_arc == NULL)
        {
                fprintf (stderr,
                  (_("WARNING in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_arc = dxf_arc_new ();
        }
        if (dxf_arc == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a DxfArc struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_arc->id_code = 0;
        dxf_arc->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_arc->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_arc->x0 = 0.0;
        dxf_arc->y0 = 0.0;
        dxf_arc->z0 = 0.0;
        dxf_arc->extr_x0 = 0.0;
        dxf_arc->extr_y0 = 0.0;
        dxf_arc->extr_z0 = 0.0;
        dxf_arc->elevation = 0.0;
        dxf_arc->thickness = 0.0;
        dxf_arc->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_arc->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_arc->radius = 0.0;
        dxf_arc->start_angle = 0.0;
        dxf_arc->end_angle = 0.0;
        dxf_arc->color = DXF_COLOR_BYLAYER;
        dxf_arc->paperspace = DXF_MODELSPACE;
        dxf_arc->dictionary_owner_soft = strdup ("");
        dxf_arc->dictionary_owner_hard = strdup ("");
        dxf_arc->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_arc);
}


/*!
 * \brief Read data from a DXF file into a DXF \c ARC entity.
 *
 * The last line read from file contained the string "ARC". \n
 * Now follows some data for the \c ARC, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_arc. \n
 *
 * \return a pointer to \c dxf_arc.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfArc *
dxf_arc_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfArc *dxf_arc
                /*!< DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_arc == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_arc = dxf_arc_new ();
                dxf_arc_init (dxf_arc);
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
                        fscanf (fp->fp, "%x\n", &dxf_arc->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_arc->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_arc->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_arc->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->radius);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * start angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->start_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->end_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_arc->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_arc->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_arc->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbCircle") != 0)))
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
                        fscanf (fp->fp, "%lf\n", &dxf_arc->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_arc->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_arc->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_arc->dictionary_owner_hard);
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
        if (strcmp (dxf_arc->linetype, "") == 0)
        {
                dxf_arc->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_arc->layer, "") == 0)
        {
                dxf_arc->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_arc);
}


/*!
 * \brief Write DXF output for a DXF \c ARC entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_arc_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfArc *dxf_arc
                /*!< DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ARC");

        /* Do some basic checks. */
        if (dxf_arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_arc->start_angle == dxf_arc->end_angle)
        {
                fprintf (stderr,
                  (_("Error in %s () start angle and end angle are identical for the %s entity with id-code: %x.\n")),
                    __FUNCTION__, dxf_entity_name, dxf_arc->id_code);
                fprintf (stderr,
                  (_("\tskipping %s entity.\n")), dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc->start_angle > 360.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () start angle is greater than 360 degrees for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc->start_angle < 0.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () start angle is lesser than 0 degrees for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc->end_angle > 360.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () end angle is greater than 360 degrees for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc->end_angle < 0.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () end angle is lesser than 0 degrees for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc->radius == 0.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () radius value equals 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_arc->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_arc->id_code);
                fprintf (stderr,
                  (_("    %s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_arc->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_arc->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_arc->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_arc->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_arc->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_arc->id_code);
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
        if ((strcmp (dxf_arc->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_arc->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_arc->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_arc->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_arc->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_arc->layer);
        if (strcmp (dxf_arc->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_arc->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_arc->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_arc->elevation);
        }
        if (dxf_arc->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_arc->color);
        }
        if (dxf_arc->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_arc->linetype_scale);
        }
        if (dxf_arc->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_arc->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbCircle\n");
        }
        if (dxf_arc->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_arc->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_arc->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_arc->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_arc->z0);
        fprintf (fp->fp, " 40\n%f\n", dxf_arc->radius);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbArc\n");
        }
        fprintf (fp->fp, " 50\n%f\n", dxf_arc->start_angle);
        fprintf (fp->fp, " 51\n%f\n", dxf_arc->end_angle);
        if ((fp->acad_version_number >= AutoCAD_12)
                && (dxf_arc->extr_x0 != 0.0)
                && (dxf_arc->extr_y0 != 0.0)
                && (dxf_arc->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", dxf_arc->extr_x0);
                fprintf (fp->fp, "220\n%f\n", dxf_arc->extr_y0);
                fprintf (fp->fp, "230\n%f\n", dxf_arc->extr_z0);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ARC and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_arc_free
(
        DxfArc *dxf_arc
                /*!< Pointer to the memory occupied by the DXF \c ARC
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_arc->next != NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () pointer to next DxfArc was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_arc->linetype);
        free (dxf_arc->layer);
        free (dxf_arc->dictionary_owner_soft);
        free (dxf_arc->dictionary_owner_hard);
        free (dxf_arc);
        dxf_arc = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
