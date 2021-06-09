/*!
 * \file line.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017,
 * 2018, 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_line_new.png
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
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
                  (_("Error in %s () could not allocate memory.\n")),
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
 * allocated memory when successful.
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
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Initialize new structs for members. */
        line->binary_graphics_data = (DxfBinaryData *) dxf_binary_data_init (line->binary_graphics_data);
        if (line->binary_graphics_data == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        line->p0 = (DxfPoint *) dxf_point_init (line->p0);
        if (line->p0 == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        line->p1 = (DxfPoint *) dxf_point_init (line->p1);
        if (line->p1 == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        line->id_code = 0;
        line->linetype = strdup (DXF_DEFAULT_LINETYPE);
        line->layer = strdup (DXF_DEFAULT_LAYER);
        line->elevation = 0.0;
        line->thickness = 0.0;
        line->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        line->visibility = DXF_DEFAULT_VISIBILITY;
        line->color = DXF_COLOR_BYLAYER;
        line->paperspace = DXF_MODELSPACE;
        line->graphics_data_size = 0;
        line->shadow_mode = 0;
        line->dictionary_owner_soft = strdup ("");
        line->object_owner_soft = strdup ("");
        line->material = strdup ("");
        line->dictionary_owner_hard = strdup ("");
        line->lineweight = 0;
        line->plot_style_name = strdup ("");
        line->color_value = 0;
        line->color_name = strdup ("");
        line->transparency = 0;
        line->extr_x0 = 0.0;
        line->extr_y0 = 0.0;
        line->extr_z0 = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        line->binary_graphics_data = NULL;
        line->p0 = NULL;
        line->p1 = NULL;
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
        DxfBinaryData *iter310 = NULL;
        int iter330;

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
                line = dxf_line_init (line);
        }
        if (line->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                line->binary_graphics_data = dxf_binary_data_init (line->binary_graphics_data);
                if (line->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                line->p0 = dxf_point_init (line->p0);
                if (line->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                line->p1 = dxf_point_init (line->p1);
                if (line->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) line->binary_graphics_data;
        iter330 = 0;
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
                        fscanf (fp->fp, "%x\n", (uint *) &line->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, line->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, line->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the end point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the end point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the end point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &line->p1->z0);
                }
                else if (strcmp (temp_string, "38") == 0)
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
                        fscanf (fp->fp, "%hd\n", &line->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &line->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &line->graphics_data_size);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbLine") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &line->graphics_data_size);
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
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &line->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_data_init ((DxfBinaryData *) iter310->next);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, line->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, line->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, line->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, line->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &line->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, line->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &line->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, line->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &line->transparency);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
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
        if ((line->p0->x0 == line->p1->x0)
                && (line->p0->y0 == line->p1->y0)
                && (line->p0->z0 == line->p1->z0))
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
        if ((strcmp (line->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", line->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (line->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", line->layer);
        if (strcmp (line->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", line->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (line->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", line->material);
        }
        if (line->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", line->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%hd\n", line->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (line->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", line->elevation);
        }
        if (line->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", line->thickness);
        }
        if (line->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", line->linetype_scale);
        }
        if (line->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", line->visibility);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
          && (line->graphics_data_size > 0))
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", line->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", line->graphics_data_size);
#endif
                if (line->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) line->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", line->color_value);
                fprintf (fp->fp, "430\n%s\n", line->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", line->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", line->plot_style_name);
                fprintf (fp->fp, "284\n%hd\n", line->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbLine\n");
        }
        fprintf (fp->fp, " 10\n%f\n", line->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", line->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", line->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", line->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", line->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", line->p1->z0);
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
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (line->linetype);
        free (line->layer);
        dxf_binary_data_free_list (line->binary_graphics_data);
        free (line->dictionary_owner_soft);
        free (line->object_owner_soft);
        free (line->material);
        free (line->dictionary_owner_hard);
        free (line->plot_style_name);
        free (line->color_name);
        dxf_point_free (line->p0);
        dxf_point_free (line->p1);
        free (line);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c LINE entities and all their data fields.
 */
void
dxf_line_free_list
(
        DxfLine *lines
                /*!< pointer to the single linked list of DXF \c LINE
                 * entities. */
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
                DxfLine *iter = (DxfLine *) lines->next;
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
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->id_code);
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
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
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
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->linetype));
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
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->layer));
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
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->elevation);
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
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->thickness);
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
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
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
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->linetype_scale);
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
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
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
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (line->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->visibility);
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
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Waning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
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
int16_t
dxf_line_get_color
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->color);
}


/*!
 * \brief Set the color for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_color
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int16_t color
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
                  (_("Warning in %s () a negative value was passed.\n")),
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
int16_t
dxf_line_get_paperspace
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (line->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_paperspace
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int16_t paperspace
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
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        line->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c LINE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_line_get_graphics_data_size
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (line->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_graphics_data_size
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
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
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        line->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c LINE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_line_get_shadow_mode
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (line->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c LINE entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_shadow_mode
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
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
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        line->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c LINE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_line_get_binary_graphics_data
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
        if (line->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) line->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c LINE entity.
 */
DxfLine *
dxf_line_set_binary_graphics_data
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
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
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->binary_graphics_data = (DxfBinaryData *) data;
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
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->dictionary_owner_soft));
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
 * \brief Get the pointer to the \c material from a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_line_get_material
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
        if (line->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_material
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
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
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->material = strdup (material);
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
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->dictionary_owner_hard));
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
 * \brief Get the \c lineweight from a DXF \c LINE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_line_get_lineweight
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c LINE entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_lineweight
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
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
        line->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c LINE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_line_get_plot_style_name
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
        if (line->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c LINE entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_plot_style_name
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
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
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c color_value from a DXF \c LINE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_line_get_color_value
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c LINE entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_color_value
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
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
        line->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c color_name from a DXF \c LINE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_line_get_color_name
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
        if (line->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (line->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c LINE entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_color_name
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
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
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the \c transparency from a DXF \c LINE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_line_get_transparency
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c LINE entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_transparency
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
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
        line->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the start point \c p0 of a DXF \c LINE entity.
 *
 * \return the start point \c p0.
 */
DxfPoint *
dxf_line_get_p0
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) line->p0);
}


/*!
 * \brief Set the start point \c p0 of a DXF \c LINE entity.
 *
 * \return a pointer to a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_p0
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        DxfPoint *p0
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
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the X-value of the start point \c x0 of a DXF \c LINE
 * entity.
 *
 * \return the X-value of the start point \c x0.
 */
double
dxf_line_get_x0
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p0->x0);
}


/*!
 * \brief Set the X-value of the start point \c x0 of a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_x0
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double x0
                /*!< the X-value of the start point \c x0 of a DXF
                 * \c LINE entity. */
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
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                line->p0 = dxf_point_init (line->p0);
                if (line->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        line->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Y-value of the start point \c y0 of a DXF
 * \c LINE entity.
 *
 * \return the Y-value of the start point \c y0.
 */
double
dxf_line_get_y0
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p0->y0);
}


/*!
 * \brief Set the Y-value of the start point \c y0 of a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_y0
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double y0
                /*!< the Y-value of the start point \c y0 of a DXF
                 * \c line entity. */
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
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                line->p0 = dxf_point_init (line->p0);
                if (line->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        line->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Z-value of the start point \c z0 of a DXF \c LINE
 * entity.
 *
 * \return the Z-value of the start point \c z0.
 */
double
dxf_line_get_z0
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p0->z0);
}


/*!
 * \brief Set the Z-value of the start point \c z0 of a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_z0
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double z0
                /*!< the Z-value of the start point \c z0 of a DXF
                 * \c line entity. */
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
        if (line->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                line->p0 = dxf_point_init (line->p0);
                if (line->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        line->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the end point \c p1 of a DXF \c LINE entity.
 *
 * \return the end point \c p1.
 */
DxfPoint *
dxf_line_get_p1
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p1);
}


/*!
 * \brief Set the end point \c p1 of a DXF \c LINE entity.
 *
 * \return a pointer to a DXF \c LINE entity.
 */
DxfLine *
dxf_line_set_p1
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        DxfPoint *p1
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
        if (p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the X-value of the end point \c x1 of a DXF \c LINE
 * entity.
 *
 * \return the X-value of the end point \c x1.
 */
double
dxf_line_get_x1
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p1->x0);
}


/*!
 * \brief Set the X-value of the end point \c x1 of a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_x1
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double x1
                /*!< the X-value of the end point \c x1 of a DXF
                 * \c LINE entity. */
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
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                line->p1 = dxf_point_init (line->p1);
                if (line->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        line->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Y-value of the end point \c y1 of a DXF
 * \c LINE entity.
 *
 * \return the Y-value of the end point \c y1.
 */
double
dxf_line_get_y1
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p1->y0);
}


/*!
 * \brief Set the Y-value of the end point \c y1 of a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_y1
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double y1
                /*!< the Y-value of the end point \c y1 of a DXF
                 * \c line entity. */
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
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                line->p1 = dxf_point_init (line->p1);
                if (line->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        line->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Z-value of the end point \c z1 of a DXF \c LINE
 * entity.
 *
 * \return the Z-value of the end point \c z1.
 */
double
dxf_line_get_z1
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->p1->z0);
}


/*!
 * \brief Set the Z-value of the end point \c z1 of a DXF \c LINE
 * entity.
 *
 * \return a pointer to \c line when successful, or \c NULL when an
 * error occurred.
 */
DxfLine *
dxf_line_set_z1
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double z1
                /*!< the Z-value of the end point \c z1 of a DXF
                 * \c line entity. */
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
        if (line->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                line->p1 = dxf_point_init (line->p1);
                if (line->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        line->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the X-value of the extrusion vector of a DXF \c LINE
 * entity.
 *
 * \return the X-value of the extrusion vector.
 */
double
dxf_line_get_extr_x0
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector of a DXF \c LINE
 * entity.
 *
 * \return a pointer to a DXF \c LINE entity when successful, \c NULL
 * when an error occurred.
 */
DxfLine *
dxf_line_set_extr_x0
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector of a DXF
                 * \c LINE entity. */
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
        line->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Y-value of the extrusion vector of a DXF \c LINE
 * entity.
 *
 * \return the Y-value of the extrusion vector.
 */
double
dxf_line_get_extr_y0
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector of a DXF \c LINE
 * entity.
 *
 * \return a pointer to a DXF \c LINE entity when successful, \c NULL
 * when an error occurred.
 */
DxfLine *
dxf_line_set_extr_y0
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector of a DXF
                 * \c LINE entity. */
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
        line->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Z-value of the extrusion vector of a DXF \c LINE
 * entity.
 *
 * \return the Z-value of the extrusion vector.
 */
double
dxf_line_get_extr_z0
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector of a DXF \c LINE
 * entity.
 *
 * \return a pointer to a DXF \c LINE entity when successful, \c NULL
 * when an error occurred.
 */
DxfLine *
dxf_line_set_extr_z0
(
        DxfLine *line,
                /*!< a pointer to a DXF \c LINE entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector of a DXF
                 * \c POLYLINE entity. */
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
        line->extr_z0 = extr_z0;
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
        if ((line->p0->x0 == line->p1->x0)
          && (line->p0->y0 == line->p1->y0)
          && (line->p0->z0 == line->p1->z0))
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
                  (_("Error in %s () could not allocate memory.\n")),
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
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLine *) line->next);
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
 * \brief Get the pointer to the last \c LINE entity from a linked list
 * of DXF \c LINE entities.
 *
 * \return pointer to the last \c LINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLine *
dxf_line_get_last
(
        DxfLine *line
                /*!< a pointer to a DXF \c LINE entity. */
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
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfLine *) line);
        }
        DxfLine *iter = (DxfLine *) line->next;
        while (iter->next != NULL)
        {
                iter = (DxfLine *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLine *) iter);
}


/*!
 * \brief Get the mid point of a DXF \c LINE entity.
 *
 * \return the mid point.
 */
DxfPoint *
dxf_line_get_mid_point
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
        if ((line->p0->x0 == line->p1->x0)
          && (line->p0->y0 == line->p1->y0)
          && (line->p0->z0 == line->p1->z0))
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
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                __FUNCTION__);
        }
        point->id_code = id_code;
        point->x0 = (line->p0->x0 + line->p1->x0) / 2;
        point->y0 = (line->p0->y0 + line->p1->y0) / 2;
        point->z0 = (line->p0->z0 + line->p1->z0) / 2;
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
dxf_line_get_length
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
        if ((line->p0->x0 == line->p1->x0)
          && (line->p0->y0 == line->p1->y0)
          && (line->p0->z0 == line->p1->z0))
        {
                fprintf (stderr,
                  (_("Error in %s () endpoints with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (0.0);
        }
        length = sqrt
        (
          ((line->p1->x0 - line->p0->x0) * (line->p1->x0 - line->p0->x0))
          + ((line->p1->y0 - line->p0->y0) * (line->p1->y0 - line->p0->y0))
          + ((line->p1->z0 - line->p0->z0) * (line->p1->z0 - line->p0->z0))
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
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                __FUNCTION__);
        }
        line->id_code = id_code;
        line->p0->x0 = p1->x0;
        line->p0->y0 = p1->y0;
        line->p0->z0 = p1->z0;
        line->p1->x0 = p2->x0;
        line->p1->y0 = p2->y0;
        line->p1->z0 = p2->z0;
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
                        line->graphics_data_size = p1->graphics_data_size;
                        line-> shadow_mode = p1->shadow_mode;
                        /*! \todo Do a deep copy of \c binary_graphics_data. */
                        line->binary_graphics_data = p1->binary_graphics_data;
                        if (p1->dictionary_owner_soft != NULL)
                        {
                                line->dictionary_owner_soft = strdup (p1->dictionary_owner_soft);
                        }
                        if (p1->material != NULL)
                        {
                                line->material = strdup (p1->material);
                        }
                        if (p1->dictionary_owner_hard != NULL)
                        {
                                line->dictionary_owner_hard = strdup (p1->dictionary_owner_hard);
                        }
                        line->lineweight = p1->lineweight;
                        if (p1->plot_style_name != NULL)
                        {
                                line->plot_style_name = strdup (p1->plot_style_name);
                        }
                        line->color_value = p1->color_value;
                        if (p1->color_name != NULL)
                        {
                                line->color_name = strdup (p1->color_name);
                        }
                        line->transparency = p1->transparency;
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
                        line->graphics_data_size = p2->graphics_data_size;
                        line-> shadow_mode = p2->shadow_mode;
                        /*! \todo Do a deep copy of \c binary_graphics_data. */
                        line->binary_graphics_data = p2->binary_graphics_data;
                        if (p2->dictionary_owner_soft != NULL)
                        {
                                line->dictionary_owner_soft = strdup (p2->dictionary_owner_soft);
                        }
                        if (p2->material != NULL)
                        {
                                line->material = strdup (p2->material);
                        }
                        if (p2->dictionary_owner_hard != NULL)
                        {
                                line->dictionary_owner_hard = strdup (p2->dictionary_owner_hard);
                        }
                        line->lineweight = p2->lineweight;
                        if (p2->plot_style_name != NULL)
                        {
                                line->plot_style_name = strdup (p2->plot_style_name);
                        }
                        line->color_value = p2->color_value;
                        if (p2->color_name != NULL)
                        {
                                line->color_name = strdup (p2->color_name);
                        }
                        line->transparency = p2->transparency;
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
