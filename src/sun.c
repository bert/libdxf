/*!
 * \file sun.c
 *
 * \author Copyright (C) 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF sun entity (\c SUN).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * \since The \c SUN entity was introduced in DXF R2007.
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


#include "sun.h"


/*!
 * \brief Allocate memory for a DXF \c SUN entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSun *
dxf_sun_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSun *sun = NULL;
        size_t size;

        size = sizeof (DxfSun);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((sun = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                sun = NULL;
        }
        else
        {
                memset (sun, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SUN
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSun *
dxf_sun_init
(
        DxfSun *sun
                /*!< a pointer to the DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                sun = dxf_sun_new ();
        }
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->id_code = 0;
        sun->linetype = strdup (DXF_DEFAULT_LINETYPE);
        sun->layer = strdup (DXF_DEFAULT_LAYER);
        sun->elevation = 0.0;
        sun->thickness = 0.0;
        sun->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        sun->visibility = DXF_DEFAULT_VISIBILITY;
        sun->color = DXF_COLOR_BYLAYER;
        sun->paperspace = DXF_MODELSPACE;
        sun->graphics_data_size = 0;
        sun->shadow_mode = 0;
        sun->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        sun->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (sun->binary_graphics_data);
        sun->dictionary_owner_soft = strdup ("");
        sun->object_owner_soft = strdup ("");
        sun->material = strdup ("");
        sun->dictionary_owner_hard = strdup ("");
        sun->lineweight = 0;
        sun->plot_style_name = strdup ("");
        sun->color_value = 0;
        sun->color_name = strdup ("");
        sun->transparency = 0;
        sun->intensity = 0.0;
        sun->sun_color = DXF_COLOR_BYLAYER;
        sun->shadow_type = 0;
        sun->shadow_map_size = 0;
        sun->version = 0;
        sun->julian_day = 0;
        sun->time = 0;
        sun->shadow_softness = 0;
        sun->status = 0;
        sun->shadows = 0;
        sun->daylight_savings_time = 0;
        sun->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SUN entity.
 *
 * The last line read from file contained the string "SUN". \n
 * Now follows some data for the \c SUN, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c sun. \n
 *
 * \return a pointer to \c sun.
 */
DxfSun *
dxf_sun_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSun *sun
                /*!< a pointer to the DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int iter92;
        DxfBinaryGraphicsData *iter310 = NULL;
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
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                sun = dxf_sun_init (sun);
        }
        iter92 = 0;
        iter310 = (DxfBinaryGraphicsData *) sun->binary_graphics_data;
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
                        fscanf (fp->fp, "%x\n", (uint *) &sun->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sun->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sun->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &sun->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &sun->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * intensity. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &sun->intensity);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &sun->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &sun->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &sun->color);
                }
                else if (strcmp (temp_string, "63") == 0)
                {
                        /* Now follows a string containing the sun
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &sun->sun_color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &sun->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * shadow_type value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &sun->shadow_type);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * shadow_map_size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &sun->shadow_map_size);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * version value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &sun->version);
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing the
                         * julian_day value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &sun->julian_day);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        if (iter92 == 0)
                        {
                                /* Now follows a string containing the
                                 * graphics data size value. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &sun->graphics_data_size);
                        }
                        if (iter92 == 1)
                        {
                                /* Now follows a string containing the
                                 * time value. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &sun->time);
                        }
                        iter92++;
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbSun") != 0)))
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
                        fscanf (fp->fp, "%d\n", &sun->graphics_data_size);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing the shadow
                         * softness value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &sun->shadow_softness);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &sun->shadow_mode);
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the status
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &sun->status);
                }
                else if (strcmp (temp_string, "291") == 0)
                {
                        /* Now follows a string containing the shadows
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &sun->shadows);
                }
                else if (strcmp (temp_string, "292") == 0)
                {
                        /* Now follows a string containing the daylight
                         * savings time value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &sun->daylight_savings_time);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) iter310->next);
                        iter310 = (DxfBinaryGraphicsData *) iter310->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sun->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sun->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sun->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sun->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &sun->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sun->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &sun->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sun->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &sun->transparency);
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
        if (strcmp (sun->linetype, "") == 0)
        {
                sun->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (sun->layer, "") == 0)
        {
                sun->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Write DXF output for a DXF \c SUN entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_sun_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSun *sun
                /*!< a pointer to the DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SUN");

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
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (sun->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, (uint) sun->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                sun->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (sun->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, (uint) sun->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                sun->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (sun->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", (uint) sun->id_code);
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
        if ((strcmp (sun->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", sun->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (sun->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", sun->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (sun->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", sun->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (sun->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", sun->layer);
        if (strcmp (sun->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", sun->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (sun->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", sun->material);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (sun->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", sun->elevation);
        }
        if (sun->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", sun->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", sun->lineweight);
        }
        if (sun->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", sun->linetype_scale);
        }
        if (sun->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", sun->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", sun->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", sun->graphics_data_size);
#endif
                if (sun->binary_graphics_data != NULL)
                {
                        DxfBinaryGraphicsData *iter;
                        iter = (DxfBinaryGraphicsData *) sun->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryGraphicsData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", sun->color_value);
                fprintf (fp->fp, "430\n%s\n", sun->color_name);
                fprintf (fp->fp, "440\n%ld\n", sun->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", sun->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", sun->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSun\n");
        }
        if (sun->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", sun->thickness);
        }
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", sun->version);
        fprintf (fp->fp, "290\n%d\n", sun->status);
        fprintf (fp->fp, " 63\n%d\n", sun->sun_color);
        fprintf (fp->fp, " 40\n%f\n", sun->intensity);
        fprintf (fp->fp, "291\n%d\n", sun->shadows);
        fprintf (fp->fp, " 91\n%" PRIi32 "\n", sun->julian_day);
        fprintf (fp->fp, " 92\n%" PRIi32 "\n", sun->time);
        fprintf (fp->fp, "292\n%d\n", sun->daylight_savings_time);
        fprintf (fp->fp, " 70\n%d\n", sun->shadow_type);
        fprintf (fp->fp, " 71\n%d\n", sun->shadow_map_size);
        fprintf (fp->fp, "280\n%" PRIi16 "\n", sun->shadow_softness);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SUN entity and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_sun_free
(
        DxfSun *sun
                /*!< a pointer to the memory occupied by the DXF \c SUN
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (sun->linetype);
        free (sun->layer);
        free (sun->dictionary_owner_soft);
        free (sun->object_owner_soft);
        free (sun->material);
        free (sun->dictionary_owner_hard);
        free (sun->plot_style_name);
        free (sun->color_name);
        free (sun);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SUN entities and all their data fields.
 */
void
dxf_sun_free_list
(
        DxfSun *suns
                /*!< a pointer to the single linked list of DXF
                 * \c SUN entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (suns == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (suns != NULL)
        {
                DxfSun *iter = (DxfSun *) suns->next;
                dxf_sun_free (suns);
                suns = (DxfSun *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SUN entity.
 *
 * \return \c id_code.
 */
int
dxf_sun_get_id_code
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_id_code
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int id_code
                /*!< the \c id_code to be set for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c linetype from a DXF \c SUN entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_sun_get_linetype
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_linetype
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c layer from a DXF \c SUN entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_sun_get_layer
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_layer
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c elevation from a DXF \c SUN entity.
 *
 * \return \c elevation.
 */
double
dxf_sun_get_elevation
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_elevation
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c thickness from a DXF \c SUN entity.
 *
 * \return \c thickness.
 */
double
dxf_sun_get_thickness
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_thickness
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c SUN entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_sun_get_linetype_scale
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_linetype_scale
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c visibility from a DXF \c SUN entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_sun_get_visibility
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_visibility
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c color from a DXF \c SUN entity.
 *
 * \return color.
 */
int
dxf_sun_get_color
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->color);
}


/*!
 * \brief Set the \c color for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_color
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        }
        sun->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c SUN entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_sun_get_paperspace
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_paperspace
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c SUN entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_sun_get_graphics_data_size
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_graphics_data_size
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c SUN entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_sun_get_shadow_mode
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_shadow_mode
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c SUN entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_sun_get_binary_graphics_data
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) sun->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_binary_graphics_data
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SUN entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sun_get_dictionary_owner_soft
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_dictionary_owner_soft
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c SUN entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sun_get_object_owner_soft
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c SUN entity.
 */
DxfSun *
dxf_sun_set_object_owner_soft
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c SUN entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_sun_get_material
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_material
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SUN entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sun_get_dictionary_owner_hard
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_dictionary_owner_hard
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c lineweight from a DXF \c SUN entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_sun_get_lineweight
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_lineweight
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c SUN entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_sun_get_plot_style_name
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_plot_style_name
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c color_value from a DXF \c SUN entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_sun_get_color_value
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_color_value
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c color_name from a DXF \c SUN entity.
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_sun_get_color_name
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sun->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_color_name
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c transparency from a DXF \c SUN entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_sun_get_transparency
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_transparency
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c intensity from a DXF \c SUN entity.
 *
 * \return \c intensity.
 */
double
dxf_sun_get_intensity
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->intensity < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->intensity);
}


/*!
 * \brief Set the \c intensity for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_intensity
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        double intensity
                /*!< the \c intensity to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (intensity < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        sun->intensity = intensity;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c sun_color from a DXF \c SUN entity.
 *
 * \return \c sun_color.
 */
int
dxf_sun_get_sun_color
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->sun_color);
}


/*!
 * \brief Set the \c sun_color for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_sun_color
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int sun_color
                /*!< the \c sun_color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->sun_color = sun_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c shadow_type from a DXF \c SUN entity.
 *
 * \return \c shadow_type.
 */
int
dxf_sun_get_shadow_type
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->shadow_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->shadow_type > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->shadow_type);
}


/*!
 * \brief Set the \c shadow_type for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_shadow_type
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int shadow_type
                /*!< the \c shadow_type to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->shadow_type = shadow_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c shadow_map_size from a DXF \c SUN entity.
 *
 * \return \c shadow_map_size.
 */
int
dxf_sun_get_shadow_map_size
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->shadow_map_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->shadow_map_size);
}


/*!
 * \brief Set the \c shadow_map_size for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_shadow_map_size
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int shadow_map_size
                /*!< the \c shadow_map_size to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_map_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        sun->shadow_map_size = shadow_map_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c version from a DXF \c SUN entity.
 *
 * \return \c version when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_sun_get_version
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->version);
}


/*!
 * \brief Set the \c version for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_version
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int32_t version
                /*!< the \c version to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->version = version;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c julian_day from a DXF \c SUN entity.
 *
 * \return \c julian_day when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_sun_get_julian_day
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->julian_day);
}


/*!
 * \brief Set the \c julian_day for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_julian_day
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int32_t julian_day
                /*!< the \c julian_day to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->julian_day = julian_day;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c time from a DXF \c SUN entity.
 *
 * \return \c time when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_sun_get_time
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->time);
}


/*!
 * \brief Set the \c time for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_time
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int32_t time
                /*!< the \c time to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->time = time;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c shadow_softness from a DXF \c SUN entity.
 *
 * \return \c shadow_softness when successful, or \c EXIT_FAILURE when
 * an error occurred.
 */
int16_t
dxf_sun_get_shadow_softness
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->shadow_softness);
}


/*!
 * \brief Set the \c shadow_softness for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_shadow_softness
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int16_t shadow_softness
                /*!< the \c shadow_softness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sun->shadow_softness = shadow_softness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c status from a DXF \c SUN entity.
 *
 * \return \c status.
 */
int
dxf_sun_get_status
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->status < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->status > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->status);
}


/*!
 * \brief Set the \c status for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_status
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int status
                /*!< the \c status to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (status < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (status > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
        sun->status = status;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c shadows from a DXF \c SUN entity.
 *
 * \return \c shadows.
 */
int
dxf_sun_get_shadows
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->shadows < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->shadows > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->shadows);
}


/*!
 * \brief Set the \c shadows for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_shadows
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int shadows
                /*!< the \c shadows to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadows < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (shadows > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
        sun->shadows = shadows;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the \c daylight_savings_time from a DXF \c SUN entity.
 *
 * \return \c daylight_savings_time.
 */
int
dxf_sun_get_daylight_savings_time
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sun->daylight_savings_time < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (sun->daylight_savings_time > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun->daylight_savings_time);
}


/*!
 * \brief Set the \c daylight_savings_time for a DXF \c SUN entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_daylight_savings_time
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        int daylight_savings_time
                /*!< the \c daylight_savings_time to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (daylight_savings_time < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (daylight_savings_time > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
        sun->daylight_savings_time = daylight_savings_time;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the next \c SUN entity from a DXF
 * \c SUN entity.
 *
 * \return pointer to the next \c SUN entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSun *
dxf_sun_get_next
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSun *) sun->next);
}


/*!
 * \brief Set the pointer to the next \c SUN for a DXF \c SUN
 * entity.
 *
 * \return a pointer to \c sun when successful, or \c NULL when an error
 * occurred.
 */
DxfSun *
dxf_sun_set_next
(
        DxfSun *sun,
                /*!< a pointer to a DXF \c SUN entity. */
        DxfSun *next
                /*!< a pointer to the next \c SUN for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
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
        sun->next = (struct DxfSun *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sun);
}


/*!
 * \brief Get the pointer to the last \c SUN entity from a linked list
 * of DXF \c SUN entities.
 *
 * \return pointer to the last \c SUN entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSun *
dxf_sun_get_last
(
        DxfSun *sun
                /*!< a pointer to a DXF \c SUN entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sun == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sun->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfSun *) sun);
        }
        DxfSun *iter = (DxfSun *) sun->next;
        while (iter->next != NULL)
        {
                iter = (DxfSun *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSun *) iter);
}


/* EOF */
