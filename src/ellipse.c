/*!
 * \file ellipse.c
 *
 * \author Copyright (C) 2008, 2010, 2011, 2012, 2014, 2015, 2016, 2017,
 * 2018, 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF ellipse entity (\c ELLIPSE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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
 * allocated memory when successful.
 */
DxfEllipse *
dxf_ellipse_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfEllipse *ellipse = NULL;
        size_t size;

        size = sizeof (DxfEllipse);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ellipse = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                ellipse = NULL;
        }
        else
        {
                memset (ellipse, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c ELLIPSE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfEllipse *
dxf_ellipse_init
(
        DxfEllipse *ellipse
                /*!< Pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ellipse = dxf_ellipse_new ();
        }
        if (ellipse == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        ellipse->id_code = 0;
        ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        ellipse->elevation = 0.0;
        ellipse->thickness = 0.0;
        ellipse->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        ellipse->visibility = DXF_DEFAULT_VISIBILITY;
        ellipse->color = DXF_COLOR_BYLAYER;
        ellipse->paperspace = DXF_MODELSPACE;
        ellipse->graphics_data_size = 0;
        ellipse->shadow_mode = 0;
        ellipse->dictionary_owner_soft = strdup ("");
        ellipse->object_owner_soft = strdup ("");
        ellipse->material = strdup ("");
        ellipse->dictionary_owner_hard = strdup ("");
        ellipse->lineweight = 0;
        ellipse->plot_style_name = strdup ("");
        ellipse->color_value = 0;
        ellipse->color_name = strdup ("");
        ellipse->transparency = 0;
        ellipse->extr_x0 = 0.0;
        ellipse->extr_y0 = 0.0;
        ellipse->extr_z0 = 0.0;
        ellipse->ratio = 0.0;
        ellipse->start_angle = 0.0;
        ellipse->end_angle = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        ellipse->binary_graphics_data = NULL;
        ellipse->p0 = NULL;
        ellipse->p1 = NULL;
        ellipse->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Read data from a DXF file into a DXF \c ELLIPSE entity.
 *
 * The last line read from file contained the string "ELLIPSE". \n
 * Now follows some data for the \c ELLIPSE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c ellipse. \n
 *
 * \return a pointer to \c ellipse.
 */
DxfEllipse *
dxf_ellipse_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfEllipse *ellipse
                /*!< Pointer to a DXF \c ELLIPSE entity. */
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
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ellipse = dxf_ellipse_init (ellipse);
        }
        if (ellipse->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                ellipse->binary_graphics_data = dxf_binary_data_init (ellipse->binary_graphics_data);
                if (ellipse->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (ellipse->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                ellipse->p0 = dxf_point_init (ellipse->p0);
                if (ellipse->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (ellipse->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                ellipse->p1 = dxf_point_init (ellipse->p1);
                if (ellipse->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) ellipse->binary_graphics_data;
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
                        fscanf (fp->fp, "%x\n", (uint *) &ellipse->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ellipse->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ellipse->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->p1->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (ellipse->elevation = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->ratio);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * start angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->start_angle);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->end_angle);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &ellipse->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &ellipse->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &ellipse->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &ellipse->graphics_data_size);
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
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbEllipse") != 0)))
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
                        fscanf (fp->fp, "%" PRIi32 "\n", &ellipse->graphics_data_size);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ellipse->extr_z0);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &ellipse->shadow_mode);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ellipse->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ellipse->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ellipse->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ellipse->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &ellipse->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ellipse->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &ellipse->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ellipse->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &ellipse->transparency);
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
        if (strcmp (ellipse->linetype, "") == 0)
        {
                ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (ellipse->layer, "") == 0)
        {
                ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
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
        DxfEllipse *ellipse
                /*!< Pointer to a DXF \c ELLIPSE entity */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ELLIPSE");

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
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (ellipse->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (ellipse->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (ellipse->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ellipse->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                ellipse->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (ellipse->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ellipse->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                ellipse->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (ellipse->ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () ratio value equals 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ellipse->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (ellipse->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", ellipse->id_code);
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
        if ((strcmp (ellipse->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", ellipse->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (ellipse->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", ellipse->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (ellipse->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", ellipse->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (ellipse->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", ellipse->layer);
        if (strcmp (ellipse->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", ellipse->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (ellipse->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", ellipse->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (ellipse->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", ellipse->thickness);
        }
        if (ellipse->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", ellipse->color);
        }
        if (ellipse->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", ellipse->linetype_scale);
        }
        if (ellipse->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", ellipse->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", ellipse->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", ellipse->graphics_data_size);
#endif
                if (ellipse->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) ellipse->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", ellipse->color_value);
                fprintf (fp->fp, "430\n%s\n", ellipse->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", ellipse->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", ellipse->plot_style_name);
                fprintf (fp->fp, "284\n%hd\n", ellipse->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEllipse\n");
        }
        fprintf (fp->fp, " 10\n%f\n", ellipse->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", ellipse->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", ellipse->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", ellipse->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", ellipse->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", ellipse->p1->z0);
        fprintf (fp->fp, " 210\n%f\n", ellipse->extr_x0);
        fprintf (fp->fp, " 220\n%f\n", ellipse->extr_y0);
        fprintf (fp->fp, " 230\n%f\n", ellipse->extr_z0);
        fprintf (fp->fp, " 40\n%f\n", ellipse->ratio);
        fprintf (fp->fp, " 41\n%f\n", ellipse->start_angle);
        fprintf (fp->fp, " 42\n%f\n", ellipse->end_angle);
        /* Clean up. */
        free (dxf_entity_name);
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
        DxfEllipse *ellipse
                /*!< Pointer to the memory occupied by the DXF
                 * \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (ellipse->linetype);
        free (ellipse->layer);
        dxf_binary_data_free_list (ellipse->binary_graphics_data);
        free (ellipse->dictionary_owner_soft);
        free (ellipse->object_owner_soft);
        free (ellipse->material);
        free (ellipse->dictionary_owner_hard);
        free (ellipse->plot_style_name);
        free (ellipse->color_name);
        dxf_point_free_list (ellipse->p0);
        dxf_point_free_list (ellipse->p1);
        free (ellipse);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c ELLIPSE entities and all their data fields.
 */
void
dxf_ellipse_free_list
(
        DxfEllipse *ellipses
                /*!< pointer to the single linked list of DXF
                 * \c ELLIPSE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ellipses == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (ellipses != NULL)
        {
                DxfEllipse *iter = (DxfEllipse *) ellipses->next;
                dxf_ellipse_free (ellipses);
                ellipses = (DxfEllipse *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c ELLIPSE entity.
 *
 * \return \c id_code.
 */
int
dxf_ellipse_get_id_code
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_id_code
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
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
        if (ellipse == NULL)
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
        ellipse->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the linetype from a DXF \c ELLIPSE entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_ellipse_get_linetype
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ellipse->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_linetype
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the layer from a DXF \c ELLIPSE entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_ellipse_get_layer
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ellipse->layer));
}


/*!
 * \brief Set the layer for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_layer
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the elevation from a DXF \c ELLIPSE entity.
 *
 * \return elevation.
 */
double
dxf_ellipse_get_elevation
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_elevation
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the thickness from a DXF \c ELLIPSE entity.
 *
 * \return thickness.
 */
double
dxf_ellipse_get_thickness
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_thickness
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the linetype scale from a DXF \c ELLIPSE entity.
 *
 * \return \c linetype_scale if successful, \c EXIT_FAILURE when an
 * error occcured.
 */
double
dxf_ellipse_get_linetype_scale
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_linetype_scale
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative was passed.\n")),
                  __FUNCTION__);
        }
        ellipse->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the visibility from a DXF \c ELLIPSE entity.
 *
 * \return visibility.
 */
int16_t
dxf_ellipse_get_visibility
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ellipse->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_visibility
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        ellipse->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the color from a DXF \c ELLIPSE entity.
 *
 * \return color.
 */
int16_t
dxf_ellipse_get_color
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->color);
}


/*!
 * \brief Set the color for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_color
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int16_t color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c ELLIPSE entity.
 *
 * \return paperspace flag value.
 */
int16_t
dxf_ellipse_get_paperspace
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ellipse->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_paperspace
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int16_t paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c ELLIPSE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_ellipse_get_graphics_data_size
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ellipse->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c ELLIPSE
 * entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_graphics_data_size
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c ELLIPSE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_ellipse_get_shadow_mode
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ellipse->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_shadow_mode
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c ELLIPSE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_ellipse_get_binary_graphics_data
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) ellipse->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_binary_graphics_data
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c ELLIPSE entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_ellipse_get_dictionary_owner_soft
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ellipse->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_dictionary_owner_soft
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c ELLIPSE entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_ellipse_get_object_owner_soft
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ellipse->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_object_owner_soft
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_ellipse_get_material
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ellipse->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_material
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c ELLIPSE entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_ellipse_get_dictionary_owner_hard
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ellipse->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_dictionary_owner_hard
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the \c lineweight from a DXF \c ELLIPSE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_ellipse_get_lineweight
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_lineweight
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_ellipse_get_plot_style_name
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ellipse->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_plot_style_name
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the \c color_value from a DXF \c ELLIPSE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_ellipse_get_color_value
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_color_value
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the \c color_name from a DXF \c ELLIPSE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_ellipse_get_color_name
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ellipse->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_color_name
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the \c transparency from a DXF \c ELLIPSE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_ellipse_get_transparency
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_transparency
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the center point \c p0 of a DXF \c ELLIPSE entity.
 *
 * \return the center point \c p0.
 */
DxfPoint *
dxf_ellipse_get_p0
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->p0 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->p0);
}


/*!
 * \brief Set the center point \c p0 of a DXF \c ELLIPSE entity.
 *
 * \return a pointer to a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_p0
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->p0 = (DxfPoint *) p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the X-value of the center point \c x0 of a DXF \c ELLIPSE
 * entity.
 *
 * \return the X-value of the center point \c x0.
 */
double
dxf_ellipse_get_x0
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->p0->x0);
}


/*!
 * \brief Set the X-value of the center point \c x0 of a DXF \c ELLIPSE
 * entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_x0
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double x0
                /*!< the X-value of the center point \c x0 of a DXF
                 * \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                ellipse->p0 = dxf_point_init (ellipse->p0);
                if (ellipse->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        ellipse->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the Y-value of the center point \c y0 of a DXF \c ELLIPSE
 * entity.
 *
 * \return the Y-value of the center point \c y0.
 */
double
dxf_ellipse_get_y0
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->p0->y0);
}


/*!
 * \brief Set the Y-value of the center point \c y0 of a DXF \c ELLIPSE
 * entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_y0
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double y0
                /*!< the Y-value of the center point \c y0 of a DXF
                 * \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                ellipse->p0 = dxf_point_init (ellipse->p0);
                if (ellipse->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        ellipse->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the Z-value of the center point \c z0 of a DXF \c ELLIPSE
 * entity.
 *
 * \return the Z-value of the center point \c z0.
 */
double
dxf_ellipse_get_z0
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->p0->z0);
}


/*!
 * \brief Set the Z-value of the center point \c z0 of a DXF \c ELLIPSE
 * entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_z0
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double z0
                /*!< the Z-value of the center point \c z0 of a DXF
                 * \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                ellipse->p0 = dxf_point_init (ellipse->p0);
                if (ellipse->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        ellipse->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the end point of the major axis \c p1 (relative to the
 * center) of a DXF \c ELLIPSE entity.
 *
 * \return the end point \c p1.
 */
DxfPoint *
dxf_ellipse_get_p1
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->p1);
}


/*!
 * \brief Set the endpoint of the major axis \c p1 (relative to the
 * center) of a DXF \c ELLIPSE entity.
 *
 * \return a pointer to a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_p1
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the X-value \c x1 of the endpoint of the major axis
 * (relative to the center) of a DXF \c ELLIPSE entity.
 *
 * \return the X-value of the point \c x1.
 */
double
dxf_ellipse_get_x1
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->p1->x0);
}


/*!
 * \brief Set the X-value \c x1 of the endpoint of the major axis
 * (relative to the center) of a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_x1
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double x1
                /*!< the X-value \c x1 of a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                ellipse->p1 = dxf_point_init (ellipse->p1);
                if (ellipse->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        ellipse->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the Y-value \c y1 of the endpoint of the major axis
 * (relative to the center) of a DXF \c ELLIPSE entity.
 *
 * \return the Y-value of the point \c y1.
 */
double
dxf_ellipse_get_y1
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->p1->y0);
}


/*!
 * \brief Set the Y-value \c y1 of the endpoint of the major axis
 * (relative to the center) of a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_y1
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double y1
                /*!< the Y-value \c y1 of a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                ellipse->p1 = dxf_point_init (ellipse->p1);
                if (ellipse->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        ellipse->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the Z-value \c z1 of the endpoint of the major axis
 * (relative to the center) of a DXF \c ELLIPSE entity.
 *
 * \return the Y-value of the point \c z1.
 */
double
dxf_ellipse_get_z1
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->p1->z0);
}


/*!
 * \brief Set the Z-value \c z1 of the endpoint of the major axis
 * (relative to the center) of a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_z1
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double z1
                /*!< the Z-value \c z1 of a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                ellipse->p1 = dxf_point_init (ellipse->p1);
                if (ellipse->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        ellipse->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the ratio of minor axis to major axis from a DXF
 * \c ELLIPSE entity.
 *
 * \return \c ratio.
 */
double
dxf_ellipse_get_ratio
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->ratio < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ellipse->ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->ratio);
}


/*!
 * \brief Set the \c ratio of a DXF \c ELLIPSE entity.
 *
 * \return a pointer to \c ellipse when successful, or \c NULL when an
 * error occurred.
 */
DxfEllipse *
dxf_ellipse_set_ratio
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double ratio
                /*!< the \c ratio of a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ratio < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        ellipse->ratio = ratio;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the start angle from a DXF \c ELLIPSE entity.
 *
 * \return start angle.
 */
double
dxf_ellipse_get_start_angle
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->start_angle < -360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative out of range value was found.\n")),
                  __FUNCTION__);
        }
        if (ellipse->start_angle > 360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->start_angle);
}


/*!
 * \brief Set the start angle for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_start_angle
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double start_angle
                /*!< the start angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (start_angle < -360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative out of range value was passed.\n")),
                  __FUNCTION__);
        }
        if (start_angle > 360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        ellipse->start_angle = start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the end angle from a DXF \c ELLIPSE entity.
 *
 * \return end angle.
 */
double
dxf_ellipse_get_end_angle
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->end_angle < -360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative out of range value was found.\n")),
                  __FUNCTION__);
        }
        if (ellipse->end_angle > 360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->end_angle);
}


/*!
 * \brief Set the end angle for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_end_angle
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double end_angle
                /*!< the end angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (end_angle < -360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative out of range value was passed.\n")),
                  __FUNCTION__);
        }
        if (end_angle > 360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        ellipse->end_angle = end_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the X-value of the extrusion vector of a DXF \c ELLIPSE
 * entity.
 *
 * \return the X-value of the extrusion vector.
 */
double
dxf_ellipse_get_extr_x0
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector of a DXF \c ELLIPSE
 * entity.
 *
 * \return a pointer to a DXF \c ELLIPSE entity when successful, \c NULL
 * when an error occurred.
 */
DxfEllipse *
dxf_ellipse_set_extr_x0
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector of a DXF
                 * \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the Y-value of the extrusion vector of a DXF \c ELLIPSE
 * entity.
 *
 * \return the Y-value of the extrusion vector.
 */
double
dxf_ellipse_get_extr_y0
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector of a DXF \c ELLIPSE
 * entity.
 *
 * \return a pointer to a DXF \c ELLIPSE entity when successful, \c NULL
 * when an error occurred.
 */
DxfEllipse *
dxf_ellipse_set_extr_y0
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector of a DXF
                 * \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the Z-value of the extrusion vector of a DXF \c ELLIPSE
 * entity.
 *
 * \return the Z-value of the extrusion vector.
 */
double
dxf_ellipse_get_extr_z0
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector of a DXF \c ELLIPSE
 * entity.
 *
 * \return a pointer to a DXF \c ELLIPSE entity when successful, \c NULL
 * when an error occurred.
 */
DxfEllipse *
dxf_ellipse_set_extr_z0
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector of a DXF
                 * \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c ELLIPSE entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_ellipse_get_extrusion_vector_as_point
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
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
        point->x0 = ellipse->extr_x0;
        point->y0 = ellipse->extr_y0;
        point->z0 = ellipse->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF
 * \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_extrusion_vector_from_point
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->extr_x0 = (double) point->x0;
        ellipse->extr_y0 = (double) point->y0;
        ellipse->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Set the extrusion vector for a DXF \c ELLIPSE entity.
 */
DxfEllipse *
dxf_ellipse_set_extrusion_vector
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
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
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->extr_x0 = extr_x0;
        ellipse->extr_y0 = extr_y0;
        ellipse->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the pointer to the next \c ELLIPSE entity from a DXF 
 * \c ELLIPSE entity.
 *
 * \return pointer to the next \c ELLIPSE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfEllipse *
dxf_ellipse_get_next
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfEllipse *) ellipse->next);
}


/*!
 * \brief Set the pointer to the next \c ELLIPSE for a DXF \c ELLIPSE
 * entity.
 */
DxfEllipse *
dxf_ellipse_set_next
(
        DxfEllipse *ellipse,
                /*!< a pointer to a DXF \c ELLIPSE entity. */
        DxfEllipse *next
                /*!< a pointer to the next \c ELLIPSE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->next = (struct DxfEllipse *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the pointer to the last \c ELLIPSE entity from a linked list
 * of DXF \c ELLIPSE entities.
 *
 * \return pointer to the last \c ELLIPSE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfEllipse *
dxf_ellipse_get_last
(
        DxfEllipse *ellipse
                /*!< a pointer to a DXF \c ELLIPSE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfEllipse *) ellipse);
        }
        DxfEllipse *iter = (DxfEllipse *) ellipse->next;
        while (iter->next != NULL)
        {
                iter = (DxfEllipse *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfEllipse *) iter);
}


/* EOF */
