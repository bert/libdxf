/*!
 * \file light.c
 *
 * \author Copyright (C) 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        }
        if (light == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
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
        light->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (light->binary_graphics_data);
        light->dictionary_owner_hard = strdup ("");
        light->material = strdup ("");
        light->dictionary_owner_soft = strdup ("");
        light->lineweight = 0;
        light->plot_style_name = strdup ("");
        light->color_value = 0;
        light->color_name = strdup ("");
        light->transparency = 0;
        light->light_name = strdup ("");
        light->p0 = dxf_point_init (light->p0);
        light->p1 = dxf_point_init (light->p1);
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
        int i;

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
                light = dxf_light_new ();
                light = dxf_light_init (light);
        }
        i = 0;
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
                        fscanf (fp->fp, "%x\n", &light->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", light->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", light->layer);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", light->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) light->binary_graphics_data->next);
                        light->binary_graphics_data = (DxfBinaryGraphicsData *) light->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing a
                         * soft-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", light->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", light->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", light->dictionary_owner_hard);
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
                        fscanf (fp->fp, "%s\n", light->plot_style_name);
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
                        fscanf (fp->fp, "%s\n", light->color_name);
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
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
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
        iter_310 = (DxfBinaryGraphicsData *) light->binary_graphics_data;
        while (iter_310 != NULL)
        {
                fprintf (fp->fp, "310\n%s\n", iter_310->data_line);
                iter_310 = (DxfBinaryGraphicsData *) iter_310->next;
        }
        fprintf (fp->fp, "420\n%ld\n", light->color_value);
        fprintf (fp->fp, "430\n%s\n", light->color_name);
        fprintf (fp->fp, "440\n%ld\n", light->transparency);
        fprintf (fp->fp, "390\n%s\n", light->plot_style_name);
        fprintf (fp->fp, "284\n%d\n", light->shadow_mode);
        fprintf (fp->fp, "100\nAcDbLight\n");
        fprintf (fp->fp, " 90\n%hi\n", light->version_number);
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
        fprintf (fp->fp, " 91\n%hi\n", light->shadow_map_size);
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
        dxf_binary_graphics_data_free_list ((DxfBinaryGraphicsData *) light->binary_graphics_data);
        free (light->dictionary_owner_hard);
        free (light->material);
        free (light->dictionary_owner_soft);
        free (light->plot_style_name);
        free (light->color_name);
        free (light->light_name);
        dxf_point_free (light->p0);
        dxf_point_free (light->p1);
        free (light);
        light = NULL;
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


/* EOF*/
