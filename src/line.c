/*!
 * \file line.c
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF line entity (\c LINE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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


#include "line.h"


/*!
 * \brief Allocate memory for a DXF \c LINE entity.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLine *
dxf_line_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLine *line = NULL;
        size_t size;

        size = sizeof (DxfLine);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((line = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLine struct.\n")),
                  __FUNCTION__);
                line = NULL;
        }
        else
        {
                memset (line, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LINE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLine *
dxf_line_init
(
        DxfLine *line
                /*!< DXF line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                line = dxf_line_new ();
        }
        if (line == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfLine struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        line->id_code = 0;
        line->linetype = strdup (DXF_DEFAULT_LINETYPE);
        line->layer = strdup (DXF_DEFAULT_LAYER);
        line->x0 = 0.0;
        line->y0 = 0.0;
        line->z0 = 0.0;
        line->x1 = 0.0;
        line->y1 = 0.0;
        line->z1 = 0.0;
        line->extr_x0 = 0.0;
        line->extr_y0 = 0.0;
        line->extr_z0 = 0.0;
        line->elevation = 0.0;
        line->thickness = 0.0;
        line->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        line->visibility = DXF_DEFAULT_VISIBILITY;
        line->color = DXF_COLOR_BYLAYER;
        line->paperspace = DXF_MODELSPACE;
        line->dictionary_owner_soft = strdup ("");
        line->dictionary_owner_hard = strdup ("");
        line->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LINE entity.
 *
 * The last line read from file contained the string "LINE". \n
 * Now follows some data for the \c LINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c line.
 *
 * \return a pointer to \c line.
 */
DxfLine *
dxf_line_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLine *line
                /*!< DXF line entity. */
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
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                line = dxf_line_new ();
                line = dxf_line_init (line);
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
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &line->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", line->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", line->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the end point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the end point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the end point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (line->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &line->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &line->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &line->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbLine") != 0)))
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
                        fscanf (fp->fp, "%lf\n", &line->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", line->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", line->dictionary_owner_hard);
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
        if (strcmp (line->linetype, "") == 0)
        {
                line->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (line->layer, "") == 0)
        {
                line->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Write DXF output to fp for a DXF \c LINE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occured.
 */
int
dxf_line_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLine *line
                /*!< DXF line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LINE");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((line->x0 == line->x1)
                && (line->y0 == line->y1)
                && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () start point and end point are identical for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, line->id_code);
                dxf_entity_skip (dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (line->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, line->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                line->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (line->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, line->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                line->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (line->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", line->id_code);
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
        if ((strcmp (line->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", line->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (line->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", line->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (line->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", line->layer);
        if (strcmp (line->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", line->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (line->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", line->elevation);
        }
        if (line->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", line->color);
        }
        if (line->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", line->linetype_scale);
        }
        if (line->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", line->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbLine\n");
        }
        if (line->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", line->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", line->x0);
        fprintf (fp->fp, " 20\n%f\n", line->y0);
        fprintf (fp->fp, " 30\n%f\n", line->z0);
        fprintf (fp->fp, " 11\n%f\n", line->x1);
        fprintf (fp->fp, " 21\n%f\n", line->y1);
        fprintf (fp->fp, " 31\n%f\n", line->z1);
        if ((fp->acad_version_number >= AutoCAD_12)
                && (line->extr_x0 != 0.0)
                && (line->extr_y0 != 0.0)
                && (line->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", line->extr_x0);
                fprintf (fp->fp, "220\n%f\n", line->extr_y0);
                fprintf (fp->fp, "230\n%f\n", line->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LINE entity and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_line_free
(
        DxfLine *line
                /*!< Pointer to the memory occupied by the DXF \c LINE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (line->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfLine was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (line->linetype);
        free (line->layer);
        free (line->dictionary_owner_soft);
        free (line->dictionary_owner_hard);
        free (line);
        line = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c LINE
 * entities and all their data fields.
 */
void
dxf_line_free_chain
(
        DxfLine *lines
                /*!< pointer to the chain of DXF \c LINE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (lines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (lines != NULL)
        {
                struct DxfLine *iter = lines->next;
                dxf_line_free (lines);
                lines = (DxfLine *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c LINE entity.
 *
 * \return ID code.
 */
int
dxf_line_get_id_code
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = line->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_id_code
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the linetype from a DXF \c LINE entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_line_get_linetype
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (line->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_linetype
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the layer from a DXF \c LINE entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_line_get_layer
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (line->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the layer for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_layer
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the elevation from a DXF \c LINE entity.
 *
 * \return elevation.
 */
double
dxf_line_get_elevation
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = line->elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the elevation for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_elevation
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the thickness from a DXF \c LINE entity.
 *
 * \return thickness.
 */
double
dxf_line_get_thickness
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = line->thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the thickness for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_thickness
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the linetype scale from a DXF \c LINE entity.
 *
 * \return linetype scale.
 */
double
dxf_line_get_linetype_scale
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = line->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype scale for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_linetype_scale
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the visibility from a DXF \c LINE entity.
 *
 * \return visibility.
 */
int16_t
dxf_line_get_visibility
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = line->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the visibility for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_visibility
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the color from a DXF \c LINE entity.
 *
 * \return color.
 */
int
dxf_line_get_color
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = line->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_color
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        line->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c LINE entity.
 *
 * \return paperspace flag value.
 */
int
dxf_line_get_paperspace
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (line->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = line->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the paperspace flag for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_paperspace
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c LINE entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_line_get_dictionary_owner_soft
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (line->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c LINE entity.
 */
DxfLine *
dxf_line_set_dictionary_owner_soft
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c LINE entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_line_get_dictionary_owner_hard
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (line->dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c LINE entity.
 */
DxfLine *
dxf_line_set_dictionary_owner_hard
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the start point of a DXF \c LINE entity.
 *
 * \return the start point.
 */
DxfPoint *
dxf_line_get_start_point
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c LINE.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () a LINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = line->x0;
        p1->y0 = line->y0;
        p1->z0 = line->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (line->linetype != NULL)
                        {
                                p1->linetype = strdup (line->linetype);
                        }
                        if (line->layer != NULL)
                        {
                                p1->layer = strdup (line->layer);
                        }
                        p1->thickness = line->thickness;
                        p1->linetype_scale = line->linetype_scale;
                        p1->visibility = line->visibility;
                        p1->color = line->color;
                        p1->paperspace = line->paperspace;
                        if (line->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (line->dictionary_owner_soft);
                        }
                        if (line->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (line->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Set the start point of a DXF \c LINE entity.
 *
 * \return a pointer to a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_start_point
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->x0 = point->x0;
        line->y0 = point->y0;
        line->z0 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the end point of a DXF \c LINE entity.
 *
 * \return the end point.
 */
DxfPoint *
dxf_line_get_end_point
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c LINE.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p2 = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () a 3DLINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p2 = dxf_point_init (p2);
        if (p2 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        p2->id_code = id_code;
        p2->x0 = line->x1;
        p2->y0 = line->y1;
        p2->z0 = line->z1;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (line->linetype != NULL)
                        {
                                p2->linetype = strdup (line->linetype);
                        }
                        if (line->layer != NULL)
                        {
                                p2->layer = strdup (line->layer);
                        }
                        p2->thickness = line->thickness;
                        p2->linetype_scale = line->linetype_scale;
                        p2->visibility = line->visibility;
                        p2->color = line->color;
                        p2->paperspace = line->paperspace;
                        if (line->dictionary_owner_soft != NULL)
                        {
                                p2->dictionary_owner_soft = strdup (line->dictionary_owner_soft);
                        }
                        if (line->dictionary_owner_hard != NULL)
                        {
                                p2->dictionary_owner_hard = strdup (line->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p2);
}


/*!
 * \brief Set the end point of a DXF \c LINE entity.
 *
 * \return a pointer to a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_end_point
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->x1 = point->x0;
        line->y1 = point->y0;
        line->z1 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c LINE entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_line_get_extrusion_vector_as_point
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () a 3DLINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point = dxf_point_init (point);
        if (point == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        point->x0 = line->extr_x0;
        point->y0 = line->extr_y0;
        point->z0 = line->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_extrusion_vector
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double extr_x0,
                /*!<  X-value of the extrusion direction. */
        double extr_y0,
                /*!<  Y-value of the extrusion direction. */
        double extr_z0
                /*!<  Z-value of the extrusion direction. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->extr_x0 = extr_x0;
        line->extr_y0 = extr_y0;
        line->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the next \c LINE entity from a DXF 
 * \c LINE entity.
 *
 * \return pointer to the next \c LINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLine *
dxf_line_get_next
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLine *result;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfLine *) line->next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the next \c LINE for a DXF \c LINE
 * entity.
 */
DxfLine *
dxf_line_set_next
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        DxfLine *next
                /*!< a pointer to the next \c LINE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->next = (struct DxfLine *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Calculate the mid point of a DXF \c LINE entity.
 *
 * \return the mid point.
 */
DxfPoint *
dxf_line_calculate_mid_point
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c LINE.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () a 3DLINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point = dxf_point_init (point);
        if (point == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        point->id_code = id_code;
        point->x0 = (line->x0 + line->x1) / 2;
        point->y0 = (line->y0 + line->y1) / 2;
        point->z0 = (line->z0 + line->z1) / 2;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (line->linetype != NULL)
                        {
                                point->linetype = strdup (line->linetype);
                        }
                        if (line->layer != NULL)
                        {
                                point->layer = strdup (line->layer);
                        }
                        point->thickness = line->thickness;
                        point->linetype_scale = line->linetype_scale;
                        point->visibility = line->visibility;
                        point->color = line->color;
                        point->paperspace = line->paperspace;
                        if (line->dictionary_owner_soft != NULL)
                        {
                                point->dictionary_owner_soft = strdup (line->dictionary_owner_soft);
                        }
                        if (line->dictionary_owner_hard != NULL)
                        {
                                point->dictionary_owner_hard = strdup (line->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Calculate the length of a DXF \c LINE (straight distance
 * between start point and end point).
 *
 * \return the length of the \c line in drawing units.
 */
double
dxf_line_calculate_length
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        double length;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (0.0);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1)
          && (line->z0 == line->z1))
        {
                fprintf (stderr,
                  (_("Error in %s () endpoints with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (0.0);
        }
        length = sqrt
        (
          ((line->x1 - line->x0) * (line->x1 - line->x0))
          + ((line->y1 - line->y0) * (line->y1 - line->y0))
          + ((line->z1 - line->z0) * (line->z1 - line->z0))
        );
#if DEBUG
        DXF_DEBUG_END
#endif
        return (length);
}


/*!
 * \brief Create a DXF \c LINE by means of two DXF \c POINT entities.
 *
 * \return \c NULL when failed, a pointer to the DXF \c LINE entity
 * when successful.
 *
 * \warning Both DXF \c POINT entities need to be freed by the caller.
 */
DxfLine *
dxf_line_create_from_points
(
        DxfPoint *p1,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfPoint *p2,
                /*!< a pointer to a DXF \c POINT entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> Point 1.</li>
                 * <li value = "2"> Point 2.</li>
                 * </ol>
                 */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLine *line = NULL;

        /* Do some basic checks. */
        if ((p1 == NULL) || (p2 == NULL))
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((p1->x0 == p2->x0) && (p1->y0 == p2->y0) && (p1->z0 == p2->z0))
        {
                fprintf (stderr,
                  (_("Error in %s () points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((inheritance < 0) || (inheritance > 2))
        {
                fprintf (stderr,
                  (_("Error in %s () an illegal inherit value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line = dxf_line_init (line);
        if (line == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLine struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        line->id_code = id_code;
        line->x0 = p1->x0;
        line->y0 = p1->y0;
        line->z0 = p1->z0;
        line->x1 = p2->x0;
        line->y1 = p2->y0;
        line->z1 = p2->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (p1->linetype != NULL)
                        {
                                line->linetype = p1->linetype;
                        }
                        if (p1->layer != NULL)
                        {
                                line->layer = p1->layer;
                        }
                        line->thickness = p1->thickness;
                        line->linetype_scale = p1->linetype_scale;
                        line->visibility = p1->visibility;
                        line->color = p1->color;
                        line->paperspace = p1->paperspace;
                        if (p1->dictionary_owner_soft != NULL)
                        {
                                line->dictionary_owner_soft = strdup (p1->dictionary_owner_soft);
                        }
                        if (p1->dictionary_owner_hard != NULL)
                        {
                                line->dictionary_owner_hard = strdup (p1->dictionary_owner_hard);
                        }
                        break;
                case 2:
                        if (p2->linetype != NULL)
                        {
                                line->linetype = p2->linetype;
                        }
                        if (p2->layer != NULL)
                        {
                                line->layer = p2->layer;
                        }
                        line->thickness = p2->thickness;
                        line->linetype_scale = p2->linetype_scale;
                        line->visibility = p2->visibility;
                        line->color = p2->color;
                        line->paperspace = p2->paperspace;
                        if (p2->dictionary_owner_soft != NULL)
                        {
                                line->dictionary_owner_soft = strdup (p2->dictionary_owner_soft);
                        }
                        if (p2->dictionary_owner_hard != NULL)
                        {
                                line->dictionary_owner_hard = strdup (p2->dictionary_owner_hard);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/* EOF */
