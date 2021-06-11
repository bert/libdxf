/*!
 * \file light.c
 *
 * \author Copyright (C) 2018, 2019, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF light entity (\c LIGHT).
 *
 * \since The \c LIGHT entity was introduced in DXF R2007.
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


#include "light.h"


/*!
 * \brief Allocate memory for a DXF \c LIGHT.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLight *
dxf_light_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLight *light = NULL;
        size_t size;

        size = sizeof (DxfLight);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((light = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                light = NULL;
        }
        else
        {
                memset (light, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LIGHT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLight *
dxf_light_init
(
        DxfLight *light
                /*!< DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                light = dxf_light_new ();
                if (light == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        /* Assign initial values to members. */
        light->id_code = 0;
        light->linetype = strdup (DXF_DEFAULT_LINETYPE);
        light->layer = strdup (DXF_DEFAULT_LAYER);
        light->thickness = 0.0;
        light->linetype_scale = 0.0;
        light->visibility = 0;
        light->color = DXF_COLOR_BYLAYER;
        light->paperspace = DXF_MODELSPACE;
        light->graphics_data_size = 0;
        light->shadow_mode = 0;
        light->dictionary_owner_hard = strdup ("");
        light->material = strdup ("");
        light->dictionary_owner_soft = strdup ("");
        light->lineweight = 0;
        light->plot_style_name = strdup ("");
        light->color_value = 0;
        light->color_name = strdup ("");
        light->transparency = 0;
        light->light_name = strdup ("");
        light->intensity = 0.0;
        light->attenuation_start_limit = 0.0;
        light->attenuation_end_limit = 0.0;
        light->hotspot_angle = 0.0;
        light->falloff_angle = 0.0;
        light->light_type = 0;
        light->attenuation_type = 0;
        light->shadow_type = 0;
        light->version_number = 0;
        light->shadow_map_size = 0;
        light->shadow_map_softness = 0;
        light->status = 0;
        light->plot_glyph = 0;
        light->use_attenuation_limits = 0;
        light->cast_shadows =0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        light->binary_graphics_data = NULL;
        light->p0 = NULL;
        light->p1 = NULL;
        light->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LIGHT entity.
 *
 * The last line read from file contained the string "LIGHT".\n
 * Now follows some data for the \c LIGHT, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC.\n
 * While parsing the DXF file store data in \c light.\n
 *
 * \return a pointer to \c light when successful, \c NULL when an error
 * occurred.
 */
DxfLight *
dxf_light_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLight *light
                /*!< DXF \c LIGHT entity. */
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
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                light = dxf_light_init (light);
                if (light == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (light->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                light->binary_graphics_data = dxf_binary_data_init (light->binary_graphics_data);
                if (light->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (light->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                light->p0 = dxf_point_init (light->p0);
                if (light->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (light->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                light->p1 = dxf_point_init (light->p1);
                if (light->p1 == NULL)
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
                        fscanf (fp->fp, "%x\n", (uint *) &light->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, light->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, light->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->p1->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * intensity. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->intensity);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * attenuation start limit. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->attenuation_start_limit);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * attenuation end limit. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->attenuation_end_limit);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the hotspot
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->hotspot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the falloff
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &light->falloff_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &light->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &light->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &light->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing a light type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hi\n", &light->light_type);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing an
                         * attenuation type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hi\n", &light->attenuation_type);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing a shadow type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hi\n", &light->shadow_type);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing a version
                         * number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &light->version_number);
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing a shadow map
                         * size. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &light->shadow_map_size);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &light->graphics_data_size);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                                && ((strcmp (temp_string, "AcDbLight") != 0)))
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
                        fscanf (fp->fp, "%d\n", &light->graphics_data_size);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing a shadow map
                         * softness value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hi\n", &light->shadow_map_softness);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &light->shadow_mode);
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing a status
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &light->status);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, light->binary_graphics_data->data_line);
                        dxf_binary_data_init ((DxfBinaryData *) light->binary_graphics_data->next);
                        light->binary_graphics_data = (DxfBinaryData *) light->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing a
                         * soft-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, light->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, light->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, light->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &light->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, light->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &light->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, light->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &light->transparency);
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
        if (strcmp (light->linetype, "") == 0)
        {
                light->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (light->layer, "") == 0)
        {
                light->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Write DXF output for a DXF \c LIGHT entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_light_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLight *light
                /*!< DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LIGHT");
        DxfBinaryData *iter_310 = NULL;

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
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
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
        if (strcmp (light->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, light->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                light->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (light->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, light->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to default layer.\n")),
                  dxf_entity_name);
                light->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (light->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", light->id_code);
        }
        fprintf (fp->fp, "330\n%s\n", light->dictionary_owner_soft);
        fprintf (fp->fp, "100\nAcDbEntity\n");
        if (light->paperspace != DXF_MODELSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", light->layer);
        if (strcmp (light->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", light->linetype);
        }
        if (strcmp (light->material, "") != 0)
        {
                fprintf (fp->fp, "347\n%s\n", light->material);
        }
        if (light->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", light->color);
        }
        fprintf (fp->fp, "370\n%d\n", light->lineweight);
        if (light->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", light->thickness);
        }
        if (light->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", light->linetype_scale);
        }
        if (light->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", light->visibility);
        }
#ifdef BUILD_64
        fprintf (fp->fp, "160\n%d\n", light->graphics_data_size);
#else
        fprintf (fp->fp, " 92\n%d\n", light->graphics_data_size);
#endif
        iter_310 = (DxfBinaryData *) light->binary_graphics_data;
        while (iter_310 != NULL)
        {
                fprintf (fp->fp, "310\n%s\n", iter_310->data_line);
                iter_310 = (DxfBinaryData *) iter_310->next;
        }
        fprintf (fp->fp, "420\n%ld\n", light->color_value);
        fprintf (fp->fp, "430\n%s\n", light->color_name);
        fprintf (fp->fp, "440\n%ld\n", light->transparency);
        fprintf (fp->fp, "390\n%s\n", light->plot_style_name);
        fprintf (fp->fp, "284\n%d\n", light->shadow_mode);
        fprintf (fp->fp, "100\nAcDbLight\n");
        fprintf (fp->fp, " 90\n%i\n", light->version_number);
        fprintf (fp->fp, "  1\n%s\n", light->light_name);
        fprintf (fp->fp, " 70\n%hi\n", light->light_type);
        fprintf (fp->fp, "290\n%d\n", light->status);
        fprintf (fp->fp, "291\n%d\n", light->plot_glyph);
        fprintf (fp->fp, " 40\n%f\n", light->intensity);
        fprintf (fp->fp, " 10\n%f\n", light->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", light->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", light->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", light->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", light->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", light->p1->z0);
        fprintf (fp->fp, " 72\n%hi\n", light->attenuation_type);
        fprintf (fp->fp, "292\n%d\n", light->use_attenuation_limits);
        fprintf (fp->fp, " 41\n%f\n", light->attenuation_start_limit);
        fprintf (fp->fp, " 42\n%f\n", light->attenuation_end_limit);
        fprintf (fp->fp, " 50\n%f\n", light->hotspot_angle);
        fprintf (fp->fp, " 51\n%f\n", light->falloff_angle);
        fprintf (fp->fp, "293\n%d\n", light->cast_shadows);
        fprintf (fp->fp, " 73\n%hi\n", light->shadow_type);
        fprintf (fp->fp, " 91\n%i\n", light->shadow_map_size);
        fprintf (fp->fp, "280\n%d\n", light->shadow_map_softness);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LIGHT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_light_free
(
        DxfLight *light
                /*!< Pointer to the memory occupied by the DXF \c LIGHT
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (light->linetype);
        free (light->layer);
        dxf_binary_data_free_list ((DxfBinaryData *) light->binary_graphics_data);
        free (light->dictionary_owner_hard);
        free (light->material);
        free (light->dictionary_owner_soft);
        free (light->plot_style_name);
        free (light->color_name);
        free (light->light_name);
        dxf_point_free (light->p0);
        dxf_point_free (light->p1);
        free (light);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c LIGHT entities and all their data fields.
 */
void
dxf_light_free_list
(
        DxfLight *light_list
                /*!< pointer to the first entry in a single linked list
                 * of DXF \c LIGHT entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (light_list == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (light_list != NULL)
        {
                DxfLight *iter = (DxfLight *) light_list->next;
                dxf_light_free (light_list);
                light_list = (DxfLight *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c LIGHT entity.
 *
 * \return \c id_code when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_light_get_id_code
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_id_code
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
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
        if (light == NULL)
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
        light->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c linetype from a DXF \c LIGHT entity.
 *
 * \return \c linetype when sucessful, or \c NULL when an error occurred.
 */
char *
dxf_light_get_linetype
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (light->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_linetype
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c layer from a DXF \c LIGHT entity.
 *
 * \return \c layer when sucessful, or \c NULL when an error occurred.
 */
char *
dxf_light_get_layer
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (light->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_layer
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c thickness from a DXF \c LIGHT entity.
 *
 * \return \c thickness when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_light_get_thickness
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_thickness
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c LIGHT entity.
 *
 * \return \c linetype_scale when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_light_get_linetype_scale
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_linetype_scale
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c visibility from a DXF \c LIGHT entity.
 *
 * \return \c visibility when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_light_get_visibility
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (light->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_visibility
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c color from a DXF \c LIGHT entity.
 *
 * \return \c color when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_light_get_color
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->color);
}


/*!
 * \brief Set the \c color for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_color
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c LIGHT entity.
 *
 * \return \c paperspace flag value when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int
dxf_light_get_paperspace
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (light->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_paperspace
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c LIGHT entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_light_get_graphics_data_size
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (light->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_graphics_data_size
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c LIGHT entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_light_get_shadow_mode
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (light->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_shadow_mode
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the pointer to the binary graphics data from a DXF 
 * \c LIGHT entity.
 *
 * \return pointer to the binary graphics data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_light_get_binary_graphics_data
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) light->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the binary_graphics_data for a DXF
 * \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_binary_graphics_data
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c LIGHT entity.
 *
 * \return pointer to the \c dictionary_owner_soft, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_light_get_dictionary_owner_soft
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (light->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_dictionary_owner_soft
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c LIGHT entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_light_get_object_owner_soft
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (light->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c LIGHT entity.
 */
DxfLight *
dxf_light_set_object_owner_soft
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c LIGHT entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_light_get_material
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (light->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_material
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF
 * \c LIGHT entity.
 *
 * \return a pointer to \c dictionary_owner_hard when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_light_get_dictionary_owner_hard
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (light->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_dictionary_owner_hard
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c lineweight from a DXF \c LIGHT entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_light_get_lineweight
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_lineweight
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c LIGHT entity.
 *
 * \return \c plot_style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_light_get_plot_style_name
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (light->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_plot_style_name
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c color_value from a DXF \c LIGHT entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_light_get_color_value
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_color_value
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c color_name from a DXF \c LIGHT entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_light_get_color_name
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (light->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_color_name
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c transparency from a DXF \c LIGHT entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_light_get_transparency
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_transparency
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the light position point \c p0 from a DXF \c LIGHT entity.
 *
 * \return light position point \c p0 when sucessful, or \c NULL when an
 * error occurred.
 */
DxfPoint *
dxf_light_get_p0
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->p0 ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) light->p0);
}


/*!
 * \brief Set the light position point \c p0 for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_p0
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        DxfPoint *p0
                /*!< a light position point \c p0 for the * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->p0 = (DxfPoint *) p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the light position point X-value \c x0 from a DXF \c LIGHT.
 *
 * \return light position point X-value \c x0 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_light_get_x0
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->p0->x0);
}


/*!
 * \brief Set the light position point X-value \c x0 for a DXF \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_x0
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double x0
                /*!< the light position point X-value \c x0 to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                light->p0 = dxf_point_init (light->p0);
                if (light->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        light->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the light position point Y-value \c y0 from a DXF \c LIGHT.
 *
 * \return light position point Y-value \c y0 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_light_get_y0
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->p0->y0);
}


/*!
 * \brief Set the light position point Y-value \c y0 for a DXF \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_y0
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double y0
                /*!< the light position point Y-value \c y0 to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                light->p0 = dxf_point_init (light->p0);
                if (light->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        light->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the light position point Z-value \c z0 from a DXF \c LIGHT.
 *
 * \return light position point Z-value \c z0 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_light_get_z0
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->p0->z0);
}


/*!
 * \brief Set the light position point Z-value \c z0 for a DXF \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_z0
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double z0
                /*!< the light position point Z-value \c z0 to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                light->p0 = dxf_point_init (light->p0);
                if (light->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        light->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the target location point \c p1 from a DXF \c LIGHT entity.
 *
 * \return target location point \c p1 when sucessful, or \c NULL when
 * an error occurred.
 */
DxfPoint *
dxf_light_get_p1
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->p1 ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) light->p1);
}


/*!
 * \brief Set the target location point \c p1 for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_p1
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        DxfPoint *p1
                /*!< a target location point \c p1 for the * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->p1 = (DxfPoint *) p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the target location point X-value \c x1 from a DXF
 * \c LIGHT.
 *
 * \return target location point X-value \c x1 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_light_get_x1
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->p1->x0);
}


/*!
 * \brief Set the light target location point X-value \c x1 for a DXF
 * \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_x1
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double x1
                /*!< the light target location point X-value \c x1 to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                light->p1 = dxf_point_init (light->p1);
                if (light->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        light->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the target location point Y-value \c y1 from a DXF
 * \c LIGHT.
 *
 * \return target location point Y-value \c y1 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_light_get_y1
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->p1->y0);
}


/*!
 * \brief Set the light target location point Y-value \c y1 for a DXF
 * \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_y1
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double y1
                /*!< the light target location point Y-value \c y1 to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                light->p1 = dxf_point_init (light->p1);
                if (light->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        light->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the target location point Z-value \c z1 from a DXF
 * \c LIGHT.
 *
 * \return target location point Z-value \c z1 when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_light_get_z1
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->p1->z0);
}


/*!
 * \brief Set the light target location point Z-value \c z1 for a DXF
 * \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_z1
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double z1
                /*!< the light target location point Z-value \c z1 to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                light->p1 = dxf_point_init (light->p1);
                if (light->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        light->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c intensity from a DXF \c LIGHT.
 *
 * \return \c intensity when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_light_get_intensity
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->intensity);
}


/*!
 * \brief Set the \c intensity for a DXF \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_intensity
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double intensity
                /*!< the \c intensity to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->intensity = intensity;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c attenuation_start_limit from a DXF \c LIGHT.
 *
 * \return \c attenuation_start_limit when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_light_get_attenuation_start_limit
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->attenuation_start_limit);
}


/*!
 * \brief Set the \c attenuation_start_limit for a DXF \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_attenuation_start_limit
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double attenuation_start_limit
                /*!< the \c attenuation_start_limit to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->attenuation_start_limit = attenuation_start_limit;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c attenuation_end_limit from a DXF \c LIGHT.
 *
 * \return \c attenuation_end_limit when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_light_get_attenuation_end_limit
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->attenuation_end_limit);
}


/*!
 * \brief Set the \c attenuation_end_limit for a DXF \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_attenuation_end_limit
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double attenuation_end_limit
                /*!< the \c attenuation_end_limit to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->attenuation_end_limit = attenuation_end_limit;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c hotspot_angle from a DXF \c LIGHT.
 *
 * \return \c hotspot_angle when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_light_get_hotspot_angle
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->hotspot_angle);
}


/*!
 * \brief Set the \c hotspot_angle for a DXF \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_hotspot_angle
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double hotspot_angle
                /*!< the \c hotspot_angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->hotspot_angle = hotspot_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c falloff_angle from a DXF \c LIGHT.
 *
 * \return \c falloff_angle when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_light_get_falloff_angle
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->falloff_angle);
}


/*!
 * \brief Set the \c falloff_angle for a DXF \c LIGHT.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_falloff_angle
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT. */
        double falloff_angle
                /*!< the \c falloff_angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->falloff_angle = falloff_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c light_type from a DXF \c LIGHT entity.
 *
 * \return \c light_type when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int16_t
dxf_light_get_light_type
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->light_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (light->light_type > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->light_type);
}


/*!
 * \brief Set the \c light_type for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_light_type
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t light_type
                /*!< the \c light_type to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (light_type > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        light->light_type = light_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c attenuation_type from a DXF \c LIGHT entity.
 *
 * \return \c attenuation_type when successful, or \c EXIT_FAILURE when
 * an error occurred.
 */
int16_t
dxf_light_get_attenuation_type
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->attenuation_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (light->attenuation_type > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->attenuation_type);
}


/*!
 * \brief Set the \c attenuation_type for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_attenuation_type
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t attenuation_type
                /*!< the \c attenuation_type to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attenuation_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (attenuation_type > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        light->attenuation_type = attenuation_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c shadow_type from a DXF \c LIGHT entity.
 *
 * \return \c shadow_type when successful, or \c EXIT_FAILURE when
 * an error occurred.
 */
int16_t
dxf_light_get_shadow_type
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (light->shadow_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (light->shadow_type > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->shadow_type);
}


/*!
 * \brief Set the \c shadow_type for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_shadow_type
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t shadow_type
                /*!< the \c shadow_type to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_type > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        light->shadow_type = shadow_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c version_number from a DXF \c LIGHT entity.
 *
 * \return \c version_number when successful, or \c EXIT_FAILURE when
 * an error occurred.
 */
int16_t
dxf_light_get_version_number
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->version_number);
}


/*!
 * \brief Set the \c version_number for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_version_number
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t version_number
                /*!< the \c version_number to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->version_number = version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c shadow_map_size from a DXF \c LIGHT entity.
 *
 * \return \c shadow_map_size when successful, or \c EXIT_FAILURE when
 * an error occurred.
 */
int16_t
dxf_light_get_shadow_map_size
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->shadow_map_size);
}


/*!
 * \brief Set the \c shadow_map_size for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_shadow_map_size
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t shadow_map_size
                /*!< the \c shadow_map_size to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->shadow_map_size = shadow_map_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c shadow_map_softness from a DXF \c LIGHT entity.
 *
 * \return \c shadow_map_softness when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int16_t
dxf_light_get_shadow_map_softness
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->shadow_map_softness);
}


/*!
 * \brief Set the \c shadow_map_softness for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_shadow_map_softness
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int16_t shadow_map_softness
                /*!< the \c shadow_map_softness to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->shadow_map_softness = shadow_map_softness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c status from a DXF \c LIGHT entity.
 *
 * \return \c status when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_light_get_status
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->status);
}


/*!
 * \brief Set the \c status for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_status
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int status
                /*!< the \c status to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->status = status;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c plot_glyph from a DXF \c LIGHT entity.
 *
 * \return \c plot_glyph when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int
dxf_light_get_plot_glyph
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->plot_glyph);
}


/*!
 * \brief Set the \c plot_glyph for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_plot_glyph
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int plot_glyph
                /*!< the \c plot_glyph to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->plot_glyph = plot_glyph;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c use_attenuation_limits from a DXF \c LIGHT entity.
 *
 * \return \c use_attenuation_limits when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int
dxf_light_get_use_attenuation_limits
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->use_attenuation_limits);
}


/*!
 * \brief Set the \c use_attenuation_limits for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_use_attenuation_limits
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int use_attenuation_limits
                /*!< the \c use_attenuation_limits to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->use_attenuation_limits = use_attenuation_limits;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the \c cast_shadows from a DXF \c LIGHT entity.
 *
 * \return \c cast_shadows when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int
dxf_light_get_cast_shadows
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light->cast_shadows);
}


/*!
 * \brief Set the \c cast_shadows for a DXF \c LIGHT entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_cast_shadows
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        int cast_shadows
                /*!< the \c cast_shadows to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        light->cast_shadows = cast_shadows;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the pointer to the next \c LIGHT entity from a DXF 
 * \c LIGHT entity.
 *
 * \return pointer to the next \c LIGHT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLight *
dxf_light_get_next
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLight *) light->next);
}


/*!
 * \brief Set the pointer to the next \c LIGHT for a DXF \c LIGHT
 * entity.
 *
 * \return a pointer to \c light when successful, or \c NULL when an
 * error occurred.
 */
DxfLight *
dxf_light_set_next
(
        DxfLight *light,
                /*!< a pointer to a DXF \c LIGHT entity. */
        DxfLight *next
                /*!< a pointer to the next \c LIGHT for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
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
        light->next = (struct DxfLight *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (light);
}


/*!
 * \brief Get the pointer to the last \c LIGHT entity from a linked list of
 * DXF \c LIGHT entity.
 *
 * \return pointer to the last \c LIGHT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLight *
dxf_light_get_last
(
        DxfLight *light
                /*!< a pointer to a DXF \c LIGHT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (light == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (light->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfLight *) light);
        }
        DxfLight *iter = (DxfLight *) light->next;
        while (iter->next != NULL)
        {
                iter = (DxfLight *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLight *) iter);
}


/* EOF*/
