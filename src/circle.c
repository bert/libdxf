/*!
 * \file circle.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2016, 2017, 2018,
 * 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF circle entity (\c CIRCLE).
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#include "circle.h"


/*!
 * \brief Allocate memory for a DXF \c CIRCLE.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_new.png
 *
 * Fill the memory contents with zeros.
 */
DxfCircle *
dxf_circle_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfCircle *circle = NULL;
        size_t size;

        size = sizeof (DxfCircle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((circle = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                circle = NULL;
        }
        else
        {
                memset (circle, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_init.png
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfCircle *
dxf_circle_init
(
        DxfCircle *circle
                /*!< DXF circle entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                circle = dxf_circle_new ();
        }
        if (circle == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        circle->id_code = 0;
        circle->linetype = strdup (DXF_DEFAULT_LINETYPE);
        circle->layer = strdup (DXF_DEFAULT_LAYER);
        circle->elevation = 0.0;
        circle->thickness = 0.0;
        circle->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        circle->visibility = DXF_DEFAULT_VISIBILITY;
        circle->color = DXF_COLOR_BYLAYER;
        circle->paperspace = DXF_MODELSPACE;
        circle->graphics_data_size = 0;
        circle->shadow_mode = 0;
        circle->dictionary_owner_soft = strdup ("");
        circle->object_owner_soft = strdup ("");
        circle->material = strdup ("");
        circle->dictionary_owner_hard = strdup ("");
        circle->lineweight = 0;
        circle->plot_style_name = strdup ("");
        circle->color_value = 0;
        circle->color_name = strdup ("");
        circle->transparency = 0;
        circle->p0->x0 = 0.0;
        circle->p0->y0 = 0.0;
        circle->p0->z0 = 0.0;
        circle->radius = 0.0;
        circle->extr_x0 = 0.0;
        circle->extr_y0 = 0.0;
        circle->extr_z0 = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        circle->binary_graphics_data = NULL;
        circle->p0 = NULL;
        circle->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Read data from a DXF file into a DXF \c CIRCLE entity.
 *
 * The last line read from file contained the string "CIRCLE". \n
 * Now follows some data for the \c CIRCLE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c circle. \n
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_read.png
 *
 * \return a pointer to \c circle.
 */
DxfCircle *
dxf_circle_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfCircle *circle
                /*!< DXF circle entity. */
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
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                circle = dxf_circle_init (circle);
        }
        if (circle->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                circle->binary_graphics_data = dxf_binary_data_init (circle->binary_graphics_data);
                if (circle->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (circle->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                circle->p0 = dxf_point_init (circle->p0);
                if (circle->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) circle->binary_graphics_data;
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
                        fscanf (fp->fp, "%x\n", (uint *) &circle->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, circle->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, circle->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->p0->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (circle->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->radius);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &circle->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &circle->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &circle->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &circle->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbCircle") != 0))
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
                        fscanf (fp->fp, "%" PRIi32 "\n", &circle->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &circle->shadow_mode);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &circle->extr_z0);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, circle->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, circle->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, circle->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, circle->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &circle->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, circle->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &circle->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, circle->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &circle->transparency);
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
        if (strcmp (circle->linetype, "") == 0)
        {
                circle->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (circle->layer, "") == 0)
        {
                circle->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Write DXF output to file for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_write.png
 */
int
dxf_circle_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfCircle *circle
                /*!< DXF circle entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("CIRCLE");

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
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (circle->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, circle->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                circle->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (circle->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, circle->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name );
                circle->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (circle->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () radius value equals 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, circle->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (circle->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", circle->id_code);
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
        if ((strcmp (circle->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", circle->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (circle->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", circle->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (circle->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", circle->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (circle->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", circle->layer);
        if (strcmp (circle->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", circle->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (circle->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", circle->material);
        }
        if (circle->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", circle->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%hd\n", circle->lineweight);
        }
        if (circle->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", circle->linetype_scale);
        }
        if (circle->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", circle->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", circle->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", circle->graphics_data_size);
#endif
                if (circle->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) circle->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", circle->color_value);
                fprintf (fp->fp, "430\n%s\n", circle->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", circle->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", circle->plot_style_name);
                fprintf (fp->fp, "284\n%hd\n", circle->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbCircle\n");
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (circle->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", circle->elevation);
        }
        if (circle->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", circle->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", circle->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", circle->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", circle->p0->z0);
        fprintf (fp->fp, " 40\n%f\n", circle->radius);
        if ((fp->acad_version_number >= AutoCAD_12)
                && (circle->extr_x0 != 0.0)
                && (circle->extr_y0 != 0.0)
                && (circle->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", circle->extr_x0);
                fprintf (fp->fp, "220\n%f\n", circle->extr_y0);
                fprintf (fp->fp, "230\n%f\n", circle->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c CIRCLE and all it's
 * data fields.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_free.png
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_circle_free
(
        DxfCircle *circle
                /*!< Pointer to the memory occupied by the DXF \c CIRCLE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->next != NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (circle->linetype);
        free (circle->layer);
        dxf_binary_data_free (circle->binary_graphics_data);
        free (circle->dictionary_owner_soft);
        free (circle->dictionary_owner_hard);
        free (circle);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c CIRCLE entities and all their data fields.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_free_list.png
 */
void
dxf_circle_free_list
(
        DxfCircle *circles
                /*!< pointer to the single linked list of DXF \c CIRCLE
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (circles == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (circles != NULL)
        {
                DxfCircle *iter = (DxfCircle *) circles->next;
                dxf_circle_free (circles);
                circles = (DxfCircle *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_id_code.png
 *
 * \return ID code.
 */
int
dxf_circle_get_id_code
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_id_code.png
 */
DxfCircle *
dxf_circle_set_id_code
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
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
        if (circle == NULL)
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
        circle->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the linetype from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_linetype.png
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_circle_get_linetype
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (circle->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_linetype.png
 */
DxfCircle *
dxf_circle_set_linetype
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the layer from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_layer.png
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_circle_get_layer
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (circle->layer));
}


/*!
 * \brief Set the layer for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_layer.png
 */
DxfCircle *
dxf_circle_set_layer
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the elevation from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_elevation.png
 *
 * \return elevation.
 */
double
dxf_circle_get_elevation
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_elevation.png
 */
DxfCircle *
dxf_circle_set_elevation
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        circle->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the thickness from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_thickness.png
 *
 * \return thickness.
 */
double
dxf_circle_get_thickness
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_thickness.png
 */
DxfCircle *
dxf_circle_set_thickness
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the linetype scale from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_linetype_scale.png
 *
 * \return linetype scale.
 */
double
dxf_circle_get_linetype_scale
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_linetype_scale.png
 */
DxfCircle *
dxf_circle_set_linetype_scale
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the visibility from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_visibility.png
 *
 * \return visibility.
 */
int16_t
dxf_circle_get_visibility
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (circle->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_visibility.png
 */
DxfCircle *
dxf_circle_set_visibility
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the color from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_color.png
 *
 * \return color.
 */
int16_t
dxf_circle_get_color
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->color);
}


/*!
 * \brief Set the color for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_color.png
 */
DxfCircle *
dxf_circle_set_color
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        int16_t color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_paperspace.png
 *
 * \return paperspace flag value.
 */
int16_t
dxf_circle_get_paperspace
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (circle->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_paperspace.png
 */
DxfCircle *
dxf_circle_set_paperspace
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        int16_t paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_graphics_data_size.png
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_circle_get_graphics_data_size
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (circle->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_graphics_data_size.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_graphics_data_size
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_shadow_mode.png
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_circle_get_shadow_mode
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (circle->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_shadow_mode.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_shadow_mode
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the pointer to the binary graphics data from a DXF 
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_binary_graphics_data.png
 *
 * \return pointer to the binary graphics data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_circle_get_binary_graphics_data
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the binary_graphics_data member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) circle->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the binary_graphics_data for a DXF
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_binary_graphics_data.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 *
 * \warning no copy is made of the contents of \c data.
 */
DxfCircle *
dxf_circle_set_binary_graphics_data
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_dictionary_owner_soft.png
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning no checks are performed on the returned pointer (string).
 */
char *
dxf_circle_get_dictionary_owner_soft
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (circle->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_dictionary_owner_soft.png
 */
DxfCircle *
dxf_circle_set_dictionary_owner_soft
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_object_owner_soft.png
 *
 * \return soft pointer to the object owner.
 *
 * \warning no checks are performed on the returned pointer (string).
 */
char *
dxf_circle_get_object_owner_soft
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (circle->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_object_owner_soft.png
 */
DxfCircle *
dxf_circle_set_object_owner_soft
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_material.png
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_circle_get_material
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (circle->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_material.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_material
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_dictionary_owner_hard.png
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_circle_get_dictionary_owner_hard
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (circle->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_dictionary_owner_hard.png
 */
DxfCircle *
dxf_circle_set_dictionary_owner_hard
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c lineweight from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_lineweight.png
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_circle_get_lineweight
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_lineweight.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_lineweight
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        circle->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_plot_style_name.png
 *
 * \return \c plot_style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_circle_get_plot_style_name
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (circle->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_plot_style_name.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_plot_style_name
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c color_value from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_color_value.png
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_circle_get_color_value
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_color_value.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_color_value
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        circle->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c color_name from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_color_name.png
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_circle_get_color_name
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (circle->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_color_name.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_color_name
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c transparency from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_transparency.png
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_circle_get_transparency
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_transparency.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_transparency
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        circle->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the base point \c p0 of a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_p0.png
 *
 * \return the base point.
 */
DxfPoint *
dxf_circle_get_p0
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->p0);
}


/*!
 * \brief Set the base point \c p0 of a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_p0.png
 *
 * \return a pointer to a DXF \c CIRCLE entity.
 */
DxfCircle *
dxf_circle_set_p0
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->p0 = (DxfPoint *) point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the X-value of the base point \c x0 of a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_x0.png
 *
 * \return the X-value of the base point \c x0.
 */
double
dxf_circle_get_x0
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->p0->x0);
}


/*!
 * \brief Set the X-value of the base point \c x0 of a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_x0.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_x0
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double x0
                /*!< the X-value of the base point \c x0 of a DXF
                 * \c CIRCLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                circle->p0 = dxf_point_init (circle->p0);
                if (circle->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        circle->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the Y-value of the base point \c y0 of a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_y0.png
 *
 * \return the Y-value of the base point \c y0.
 */
double
dxf_circle_get_y0
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->p0->y0);
}


/*!
 * \brief Set the Y-value of the base point \c y0 of a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_y0.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_y0
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double y0
                /*!< the Y-value of the base point \c y0 of a DXF
                 * \c CIRCLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                circle->p0 = dxf_point_init (circle->p0);
                if (circle->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        circle->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the Z-value of the base point \c z0 of a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_z0.png
 *
 * \return the Z-value of the base point \c z0.
 */
double
dxf_circle_get_z0
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->p0->z0);
}


/*!
 * \brief Set the Z-value of the base point \c z0 of a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_z0.png
 *
 * \return a pointer to \c circle when successful, or \c NULL when an
 * error occurred.
 */
DxfCircle *
dxf_circle_set_z0
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double z0
                /*!< the Z-value of the base point \c z0 of a DXF
                 * \c CIRCLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                circle->p0 = dxf_point_init (circle->p0);
                if (circle->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        circle->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the radius from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_radius.png
 *
 * \return radius.
 */
double
dxf_circle_get_radius
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (circle->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->radius);
}


/*!
 * \brief Set the radius for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_radius.png
 */
DxfCircle *
dxf_circle_set_radius
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double radius
                /*!< the radius to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        circle->radius = radius;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_extrusion_vector_as_point.png
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning no other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_circle_get_extrusion_vector_as_point
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (circle == NULL)
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
        point->x0 = circle->extr_x0;
        point->y0 = circle->extr_y0;
        point->z0 = circle->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_extrusion_vector.png
 */
DxfCircle *
dxf_circle_set_extrusion_vector
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
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
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        circle->extr_x0 = extr_x0;
        circle->extr_y0 = extr_y0;
        circle->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c extr_x0 from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_extr_x0.png
 *
 * \return \c extr_xo.
 */
double
dxf_circle_get_extr_x0
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->extr_x0);
}


/*!
 * \brief Set the \c extr_x0 for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_extr_x0.png
 */
DxfCircle *
dxf_circle_set_extr_x0
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double extr_x0
                /*!< the \c extr_x0 to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        circle->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c extr_y0 from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_extr_y0.png
 *
 * \return \c extr_xo.
 */
double
dxf_circle_get_extr_y0
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->extr_y0);
}


/*!
 * \brief Set the \c extr_y0 for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_extr_y0.png
 */
DxfCircle *
dxf_circle_set_extr_y0
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double extr_y0
                /*!< the \c extr_y0 to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        circle->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c extr_z0 from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_extr_z0.png
 *
 * \return \c extr_zo.
 */
double
dxf_circle_get_extr_z0
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle->extr_z0);
}


/*!
 * \brief Set the \c extr_z0 for a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_extr_z0.png
 */
DxfCircle *
dxf_circle_set_extr_z0
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        double extr_z0
                /*!< the \c extr_z0 to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        circle->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the \c area from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_area.png
 *
 * \return \c area.
 *
 * \note a negative radius (!) will give a positive area.
 */
double
dxf_circle_get_area
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (circle->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (M_PI * circle->radius * circle->radius);
}


/*!
 * \brief Get the \c circumference from a DXF \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_circumference.png
 *
 * \return \c circumference.
 *
 * \note the absolute value radius is used for the calculation.
 */
double
dxf_circle_get_circumference
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (circle->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (2 * M_PI * fabs (circle->radius));
}


/*!
 * \brief Test if a DXF \c POINT lies within, on top or outside a DXF
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_test_point_in_circle.png
 *
 * \return \c INSIDE if the point lies inside the circle,
 * \c OUTSIDE if the point lies outside the circle,
 * \c ON_EDGE if the point lies on top the circle.
 *
 * \note A two-dimensional circle on a plane wit z = 0.0.
 */
int
dxf_circle_test_point_in_circle
(
        DxfPoint *point,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
        double dy;
        double dx;

#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (circle->radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (circle->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
        dx = circle->p0->x0 - point->x0;
        dy = circle->p0->y0 - point->y0;
        /* "<" to not include the edge */
        if (dx * dx + dy * dy < circle->radius * circle->radius)
                return (INSIDE);
        /* ">" to not include the edge */
        else if (dx * dx + dy * dy > circle->radius * circle->radius)
                return (OUTSIDE);
        /* "==" to detect on edge */
        else if (dx * dx + dy * dy == circle->radius * circle->radius)
                return (ON_EDGE);
#if DEBUG
        DXF_DEBUG_END
#endif
        /* dead code */
        return (EXIT_FAILURE);
}


/*!
 * \brief Get the pointer to the next \c CIRCLE entity from a DXF 
 * \c CIRCLE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_next.png
 *
 * \return pointer to the next \c CIRCLE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfCircle *
dxf_circle_get_next
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfCircle *) circle->next);
}


/*!
 * \brief Set the pointer to the next \c CIRCLE for a DXF \c CIRCLE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_set_next.png
 */
DxfCircle *
dxf_circle_set_next
(
        DxfCircle *circle,
                /*!< a pointer to a DXF \c CIRCLE entity. */
        DxfCircle *next
                /*!< a pointer to the next \c CIRCLE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
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
        circle->next = (struct DxfCircle *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (circle);
}


/*!
 * \brief Get the pointer to the last \c CIRCLE entity from a linked
 * list of DXF \c CIRCLE entities.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_circle_get_last.png
 *
 * \return pointer to the last \c CIRCLE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfCircle *
dxf_circle_get_last
(
        DxfCircle *circle
                /*!< a pointer to a DXF \c CIRCLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (circle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (circle->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfCircle *) circle);
        }
        DxfCircle *iter = (DxfCircle *) circle->next;
        while (iter->next != NULL)
        {
                iter = (DxfCircle *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfCircle *) iter);
}


/* EOF */
