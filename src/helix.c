/*!
 * \file helix.c
 *
 * \author Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF helix entity (\c HELIX).
 *
 * \since The \c HELIX entity was introduced in DXF R2007.
 *
 * \warning The \c HELIX entity requires AutoCAD version 2007 or higher.\n
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


#include "helix.h"


/*!
 * \brief Allocate memory for a DXF \c HELIX.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHelix *
dxf_helix_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHelix *helix = NULL;
        size_t size;

        size = sizeof (DxfHelix);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((helix = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                helix = NULL;
        }
        else
        {
                memset (helix, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HELIX
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHelix *
dxf_helix_init
(
        DxfHelix *helix
                /*!< DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                helix = dxf_helix_new ();
        }
        if (helix == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        helix->id_code = 0;
        helix->linetype = strdup (DXF_DEFAULT_LINETYPE);
        helix->layer = strdup (DXF_DEFAULT_LAYER);
        helix->thickness = 0.0;
        helix->radius = 0.0;
        helix->number_of_turns = 0.0;
        helix->turn_height = 0.0;
        helix->linetype_scale = 0.0;
        helix->visibility = 0;
        helix->color = DXF_COLOR_BYLAYER;
        helix->paperspace = DXF_MODELSPACE;
        helix->major_release_number = 0;
        helix->maintainance_release_number = 0;
        helix->graphics_data_size = 0;
        helix->constraint_type = 0;
        helix->shadow_mode = 0;
        helix->handedness = 0;
        helix->dictionary_owner_hard = strdup ("");
        helix->material = strdup ("");
        helix->dictionary_owner_soft = strdup ("");
        helix->lineweight = 0;
        helix->plot_style_name = strdup ("");
        helix->color_value = 0;
        helix->color_name = strdup ("");
        helix->transparency = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        helix->binary_graphics_data = NULL;
        helix->p0 = NULL;
        helix->p1 = NULL;
        helix->p2 = NULL;
        helix->spline = NULL;
        helix->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Read data from a DXF file into a DXF \c HELIX entity.
 *
 * The last line read from file contained the string "HELIX". \n
 * Now follows some data for the \c HELIX, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c helix. \n
 *
 * \return a pointer to \c helix when successful, \c NULL when an error
 * occurred.
 */
DxfHelix *
dxf_helix_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfHelix *helix
                /*!< DXF \c HELIX entity. */
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
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                helix = dxf_helix_init (helix);
        }
        if (helix->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                helix->binary_graphics_data = dxf_binary_graphics_data_init (helix->binary_graphics_data);
                if (helix->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (helix->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p0 = dxf_point_init (helix->p0);
                if (helix->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (helix->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p1 = dxf_point_init (helix->p1);
                if (helix->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (helix->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p2 = dxf_point_init (helix->p2);
                if (helix->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
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
                        fscanf (fp->fp, "%x\n", (uint *) &helix->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, helix->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, helix->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p1->z0);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the axis vector point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p2->x0);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the axis vector point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p2->y0);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the axis vector point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->p2->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->radius);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the number of
                         * turns. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->number_of_turns);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the turn
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->turn_height);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->paperspace);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing a major
                         * release number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &helix->major_release_number);
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing a maintenance
                         * release number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &helix->maintainance_release_number);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &helix->graphics_data_size);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbSpline") == 0))
                        {
                                helix->spline = dxf_spline_read (fp, helix->spline);
                        }
                        else if ((strcmp (temp_string, "AcDbEntity") != 0)
                                && ((strcmp (temp_string, "AcDbHelix") != 0)))
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
                        fscanf (fp->fp, "%" PRIi32 "\n", &helix->graphics_data_size);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing a constraint
                         * type value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->constraint_type);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->shadow_mode);
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing a handedness
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &helix->handedness);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, helix->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) helix->binary_graphics_data->next);
                        helix->binary_graphics_data = (DxfBinaryGraphicsData *) helix->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing a
                         * soft-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, helix->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, helix->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, helix->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, helix->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &helix->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, helix->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &helix->transparency);
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
        if (strcmp (helix->linetype, "") == 0)
        {
                helix->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (helix->layer, "") == 0)
        {
                helix->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Write DXF output for a DXF \c HELIX entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_helix_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHelix *helix
                /*!< DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("HELIX");
        int i;
        DxfPoint *iter = NULL;
        DxfBinaryGraphicsData *iter_310 = NULL;

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
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (helix->spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (helix->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () radius value equals 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, helix->id_code);
                fprintf (stderr, "    skipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_2007)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (strcmp (helix->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, helix->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                helix->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (helix->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, helix->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to default layer.\n")),
                  dxf_entity_name);
                helix->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (helix->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", helix->id_code);
        }
        fprintf (fp->fp, "330\n%s\n", helix->dictionary_owner_soft);
        fprintf (fp->fp, "100\nAcDbEntity\n");
        if (helix->paperspace != DXF_MODELSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", helix->layer);
        if (strcmp (helix->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", helix->linetype);
        }
        if (strcmp (helix->material, "") != 0)
        {
                fprintf (fp->fp, "347\n%s\n", helix->material);
        }
        if (helix->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", helix->color);
        }
        fprintf (fp->fp, "370\n%d\n", helix->lineweight);
        if (helix->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", helix->thickness);
        }
        if (helix->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", helix->linetype_scale);
        }
        if (helix->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", helix->visibility);
        }
#ifdef BUILD_64
        fprintf (fp->fp, "160\n%" PRIi32 "\n", helix->graphics_data_size);
#else
        fprintf (fp->fp, " 92\n%" PRIi32 "\n", helix->graphics_data_size);
#endif
        iter_310 = (DxfBinaryGraphicsData *) helix->binary_graphics_data;
        while (iter_310 != NULL)
        {
                fprintf (fp->fp, "310\n%s\n", iter_310->data_line);
                iter_310 = (DxfBinaryGraphicsData *) iter_310->next;
        }
        fprintf (fp->fp, "420\n%" PRIi32 "\n", helix->color_value);
        fprintf (fp->fp, "430\n%s\n", helix->color_name);
        fprintf (fp->fp, "440\n%" PRIi32 "\n", helix->transparency);
        fprintf (fp->fp, "390\n%s\n", helix->plot_style_name);
        fprintf (fp->fp, "284\n%hd\n", helix->shadow_mode);
        /* Write a spline to a DxfFile. */
        helix->spline->flag = 0;
        helix->spline->degree = 3;
        fprintf (fp->fp, "100\nAcDbSpline\n");
        fprintf (fp->fp, " 70\n%hd\n", helix->spline->flag);
        fprintf (fp->fp, " 71\n%hd\n", helix->spline->degree);
        fprintf (fp->fp, " 72\n%hd\n", helix->spline->number_of_knots);
        fprintf (fp->fp, " 73\n%hd\n", helix->spline->number_of_control_points);
        fprintf (fp->fp, " 74\n%hd\n", helix->spline->number_of_fit_points);
        fprintf (fp->fp, " 42\n%f\n", helix->spline->knot_tolerance);
        fprintf (fp->fp, " 43\n%f\n", helix->spline->control_point_tolerance);
        fprintf (fp->fp, " 12\n%f\n", helix->spline->p2->x0);
        fprintf (fp->fp, " 22\n%f\n", helix->spline->p2->y0);
        fprintf (fp->fp, " 32\n%f\n", helix->spline->p2->z0);
        fprintf (fp->fp, " 13\n%f\n", helix->spline->p3->x0);
        fprintf (fp->fp, " 23\n%f\n", helix->spline->p3->y0);
        fprintf (fp->fp, " 33\n%f\n", helix->spline->p3->z0);
        for (i = 0; i < helix->spline->number_of_knots; i++)
        {
                fprintf (fp->fp, " 40\n%f\n", helix->spline->knot_value->value);
                /*! \todo implement as a single linked list of double. */
        }
        if (helix->spline->number_of_fit_points != 0)
        {
                for (i = 0; i < helix->spline->number_of_fit_points; i++)
                {
                        fprintf (fp->fp, " 41\n%f\n", helix->spline->weight_value->value);
                        /*! \todo implement as a single linked list of double. */
                }
        }
        iter = (DxfPoint *) helix->spline->p0;
        while (iter != NULL)
        {
                fprintf (fp->fp, " 10\n%f\n", iter->x0);
                fprintf (fp->fp, " 20\n%f\n", iter->y0);
                fprintf (fp->fp, " 30\n%f\n", iter->z0);
                iter = (DxfPoint *) iter->next;
        }
        iter = (DxfPoint *) helix->spline->p1;
        while (iter != NULL)
        {
                fprintf (fp->fp, " 11\n%f\n", iter->x0);
                fprintf (fp->fp, " 21\n%f\n", iter->y0);
                fprintf (fp->fp, " 31\n%f\n", iter->z0);
                iter = (DxfPoint *) iter->next;
        }
        /* Continue writing helix entity parameters. */
        fprintf (fp->fp, "100\nAcDbHelix\n");
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", helix->major_release_number);
        fprintf (fp->fp, " 91\n%" PRIi32 "\n", helix->maintainance_release_number);
        fprintf (fp->fp, " 10\n%f\n", helix->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", helix->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", helix->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", helix->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", helix->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", helix->p1->z0);
        fprintf (fp->fp, " 12\n%f\n", helix->p2->x0);
        fprintf (fp->fp, " 22\n%f\n", helix->p2->y0);
        fprintf (fp->fp, " 32\n%f\n", helix->p2->z0);
        fprintf (fp->fp, " 40\n%f\n", helix->radius);
        fprintf (fp->fp, " 41\n%f\n", helix->number_of_turns);
        fprintf (fp->fp, " 42\n%f\n", helix->turn_height);
        fprintf (fp->fp, "290\n%d\n", helix->handedness);
        fprintf (fp->fp, "280\n%hd\n", helix->constraint_type);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HELIX and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_helix_free
(
        DxfHelix *helix
                /*!< Pointer to the memory occupied by the DXF \c HELIX
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (helix->linetype);
        free (helix->layer);
        dxf_binary_graphics_data_free_list ((DxfBinaryGraphicsData *) helix->binary_graphics_data);
        free (helix->dictionary_owner_hard);
        free (helix->material);
        free (helix->dictionary_owner_soft);
        free (helix->plot_style_name);
        free (helix->color_name);
        dxf_point_free (helix->p0);
        dxf_point_free (helix->p1);
        dxf_point_free (helix->p2);
        free (helix);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HELIX entities and all their data fields.
 */
void
dxf_helix_free_list
(
        DxfHelix *helices
                /*!< pointer to the first entry in a single linked list
                 * of DXF \c HELIX entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (helices == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (helices != NULL)
        {
                DxfHelix *iter = (DxfHelix *) helices->next;
                dxf_helix_free (helices);
                helices = (DxfHelix *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c HELIX entity.
 *
 * \return \c id_code when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_helix_get_id_code
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_id_code
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
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
        if (helix == NULL)
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
        helix->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c linetype from a DXF \c HELIX entity.
 *
 * \return \c linetype when sucessful, or \c NULL when an error occurred.
 */
char *
dxf_helix_get_linetype
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (helix->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_linetype
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c layer from a DXF \c HELIX entity.
 *
 * \return \c layer when sucessful, or \c NULL when an error occurred.
 */
char *
dxf_helix_get_layer
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (helix->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_layer
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c thickness from a DXF \c HELIX entity.
 *
 * \return \c thickness when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_helix_get_thickness
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_thickness
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c HELIX entity.
 *
 * \return \c linetype_scale when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_helix_get_linetype_scale
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_linetype_scale
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c visibility from a DXF \c HELIX entity.
 *
 * \return \c visibility when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_helix_get_visibility
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (helix->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_visibility
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c color from a DXF \c HELIX entity.
 *
 * \return \c color when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int16_t
dxf_helix_get_color
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->color);
}


/*!
 * \brief Set the \c color for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_color
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int16_t color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        helix->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c HELIX entity.
 *
 * \return \c paperspace flag value when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int16_t
dxf_helix_get_paperspace
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (helix->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_paperspace
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int16_t paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c HELIX entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_helix_get_graphics_data_size
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (helix->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_graphics_data_size
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c HELIX entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_helix_get_shadow_mode
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (helix->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_shadow_mode
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the pointer to the binary graphics data from a DXF 
 * \c HELIX entity.
 *
 * \return pointer to the binary graphics data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_helix_get_binary_graphics_data
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) helix->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the binary_graphics_data for a DXF
 * \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_binary_graphics_data
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c HELIX entity.
 *
 * \return pointer to the \c dictionary_owner_soft, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_helix_get_dictionary_owner_soft
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (helix->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_dictionary_owner_soft
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c HELIX entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_helix_get_object_owner_soft
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (helix->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_object_owner_soft
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c HELIX entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_helix_get_material
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (helix->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_material
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF
 * \c HELIX entity.
 *
 * \return a pointer to \c dictionary_owner_hard when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_helix_get_dictionary_owner_hard
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (helix->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_dictionary_owner_hard
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c lineweight from a DXF \c HELIX entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_helix_get_lineweight
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_lineweight
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c HELIX entity.
 *
 * \return \c plot_style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_helix_get_plot_style_name
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (helix->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_plot_style_name
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c color_value from a DXF \c HELIX entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_helix_get_color_value
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_color_value
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c color_name from a DXF \c HELIX entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_helix_get_color_name
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (helix->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_color_name
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c transparency from a DXF \c HELIX entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_helix_get_transparency
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_transparency
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis base point \c p0 from a DXF \c HELIX entity.
 *
 * \return axis base point \c p0 when sucessful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_helix_get_p0
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p0 ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) helix->p0);
}


/*!
 * \brief Set the axis base point \c p0 for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_p0
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        DxfPoint *p0
                /*!< an axis base point \c p0 for the * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->p0 = (DxfPoint *) p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis base point X-value \c x0 from a DXF \c HELIX.
 *
 * \return axis base point X-value \c x0 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_helix_get_x0
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p0->x0);
}


/*!
 * \brief Set the axis base point X-value \c x0 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_x0
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double x0
                /*!< the axis base point X-value \c x0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p0 = dxf_point_init (helix->p0);
                if (helix->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis base point Y-value \c y0 from a DXF \c HELIX.
 *
 * \return axis base point Y-value \c y0 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_helix_get_y0
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p0->y0);
}


/*!
 * \brief Set the axis base point Y-value \c y0 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_y0
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double y0
                /*!< the axis base point Y-value \c y0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p0 = dxf_point_init (helix->p0);
                if (helix->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis base point Z-value \c z0 from a DXF \c HELIX.
 *
 * \return axis base point Z-value \c z0 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_helix_get_z0
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p0->z0);
}


/*!
 * \brief Set the axis base point Z-value \c z0 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_z0
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double z0
                /*!< the axis base point Z-value \c z0 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p0 = dxf_point_init (helix->p0);
                if (helix->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the start point \c p1 from a DXF \c HELIX entity.
 *
 * \return start point \c p1 when sucessful, or \c NULL when an error
 * occurred.
 */
DxfPoint *
dxf_helix_get_p1
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p1 ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) helix->p1);
}


/*!
 * \brief Set the start point \c p1 for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_p1
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        DxfPoint *p1
                /*!< a start point \c p1 for the * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->p1 = (DxfPoint *) p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the start point X-value \c x1 from a DXF \c HELIX.
 *
 * \return start point X-value \c x1 when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_helix_get_x1
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p1->x0);
}


/*!
 * \brief Set the start point X-value \c x1 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_x1
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double x1
                /*!< the start point X-value \c x1 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p1 = dxf_point_init (helix->p1);
                if (helix->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the start point Y-value \c y1 from a DXF \c HELIX.
 *
 * \return start point Y-value \c y1 when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_helix_get_y1
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p1->y0);
}


/*!
 * \brief Set the start point Y-value \c y1 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_y1
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double y1
                /*!< the start point Y-value \c y1 to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p1 = dxf_point_init (helix->p1);
                if (helix->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the start point Z-value \c z1 from a DXF \c HELIX.
 *
 * \return start point Z-value \c z1 when successful, or \c EXIT_FAILURE
 * when an rror occurred.
 */
double
dxf_helix_get_z1
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p1->z0);
}


/*!
 * \brief Set the start point Z-value \c z1 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_z1
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double z1
                /*!< the start point Z-value \c z1 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p1 = dxf_point_init (helix->p1);
                if (helix->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis vector point \c p2 from a DXF \c HELIX entity.
 *
 * \return the axis vector point \c p2 when sucessful, or \c NULL when
 * an error occurred.
 */
DxfPoint *
dxf_helix_get_p2
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p2 ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) helix->p2);
}


/*!
 * \brief Set the axis vector point \c p2 for a DXF \c HELIX entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_p2
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        DxfPoint *p2
                /*!< an axis vector point \c p2 for the DXF \c HELIX
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->p2 = (DxfPoint *) p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis vector point X-value \c x2 from a DXF \c HELIX.
 *
 * \return axis vector point X-value \c x2 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_helix_get_x2
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p2->x0);
}


/*!
 * \brief Set the axis vector point X-value \c x2 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_x2
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double x2
                /*!< the axis vector point X-value \c x2 to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p2 = dxf_point_init (helix->p2);
                if (helix->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis vector point Y-value \c y2 from a DXF \c HELIX.
 *
 * \return axis vector point Y-value \c y2 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_helix_get_y2
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p2->y0);
}


/*!
 * \brief Set the axis vector point Y-value \c y2 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_y2
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double y2
                /*!< the axis vector point Y-value \c y2 to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p2 = dxf_point_init (helix->p2);
                if (helix->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis vector point Z-value \c z2 from a DXF \c HELIX.
 *
 * \return axis vector point Z-value \c z2 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_helix_get_z2
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->p2->z0);
}


/*!
 * \brief Set the axis vector point Z-value \c z2 for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_z2
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double z2
                /*!< the axis vector point Z-value \c z2 to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                helix->p2 = dxf_point_init (helix->p2);
                if (helix->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        helix->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c radius from a DXF \c HELIX entity.
 *
 * \return \c radius when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
double
dxf_helix_get_radius
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->radius);
}


/*!
 * \brief Set the \c radius for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_radius
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double radius
                /*!< the \c radius to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->radius = radius;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c number_of_turns from a DXF \c HELIX entity.
 *
 * \return \c number_of_turns when successful, or \c EXIT_FAILURE when
 * an error occurred.
 */
double
dxf_helix_get_number_of_turns
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->number_of_turns);
}


/*!
 * \brief Set the \c number_of_turns for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_number_of_turns
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double number_of_turns
                /*!< the \c number_of_turns to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->number_of_turns = number_of_turns;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c turn_height from a DXF \c HELIX entity.
 *
 * \return \c turn_height when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_helix_get_turn_height
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->turn_height);
}


/*!
 * \brief Set the \c turn_height for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_turn_height
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double turn_height
                /*!< the \c turn_height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->turn_height = turn_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c major_release_number from a DXF \c HELIX entity.
 *
 * \return \c major_release_number when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int32_t
dxf_helix_get_major_release_number
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->major_release_number);
}


/*!
 * \brief Set the \c major_release_number for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_major_release_number
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        int32_t major_release_number
                /*!< the \c major_release_number to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->major_release_number = major_release_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c maintainance_release_number from a DXF \c HELIX
 * entity.
 *
 * \return \c maintainance_release_number when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_helix_get_maintainance_release_number
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->maintainance_release_number);
}


/*!
 * \brief Set the \c maintainance_release_number for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_maintainance_release_number
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        int32_t maintainance_release_number
                /*!< the \c maintainance_release_number to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->maintainance_release_number = maintainance_release_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c constraint_type from a DXF \c HELIX.
 *
 * \return \c constraint_type when successful, or \c EXIT_FAILURE when
 * an error occurred.
 */
int16_t
dxf_helix_get_constraint_type
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->constraint_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (helix->constraint_type > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->constraint_type);
}


/*!
 * \brief Set the \c constraint_type for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_constraint_type
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        int16_t constraint_type
                /*!< the \c constraint_type to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (constraint_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (constraint_type > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        helix->constraint_type = constraint_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c handedness from a DXF \c HELIX.
 *
 * \return \c handedness when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int
dxf_helix_get_handedness
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->handedness < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (helix->handedness > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix->handedness);
}


/*!
 * \brief Set the \c handedness for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_handedness
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        int handedness
                /*!< the \c handedness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (handedness < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (handedness > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        helix->handedness = handedness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c spline from a DXF \c HELIX.
 *
 * \return \c spline when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfSpline *
dxf_helix_get_spline
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSpline *) helix->spline);
}


/*!
 * \brief Set the \c spline for a DXF \c HELIX.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_spline
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        DxfSpline *spline
                /*!< the \c spline to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->spline = (DxfSpline *) spline;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the pointer to the next \c HELIX entity from a DXF 
 * \c HELIX entity.
 *
 * \return pointer to the next \c HELIX entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHelix *
dxf_helix_get_next
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHelix *) helix->next);
}


/*!
 * \brief Set the pointer to the next \c HELIX for a DXF \c HELIX
 * entity.
 *
 * \return a pointer to \c helix when successful, or \c NULL when an
 * error occurred.
 */
DxfHelix *
dxf_helix_set_next
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        DxfHelix *next
                /*!< a pointer to the next \c HELIX for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->next = (struct DxfHelix *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the pointer to the last \c HELIX entity from a linked list of
 * DXF \c HELIX entity.
 *
 * \return pointer to the last \c HELIX entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHelix *
dxf_helix_get_last
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHelix *) helix);
        }
        DxfHelix *iter = (DxfHelix *) helix->next;
        while (iter->next != NULL)
        {
                iter = (DxfHelix *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHelix *) iter);
}


/* EOF*/
