/*!
 * \file image.c
 *
 * \author Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF image entity (\c IMAGE).
 *
 * \since The \c IMAGE entity was introduced in DXF R14.
 *
 * \warning The image entity requires AutoCAD version R14 or higher.\n
 *
 * \htmlinclude "image.html"
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
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


#include "image.h"


/*!
 * \brief Allocate memory for a DXF \c IMAGE.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfImage *
dxf_image_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfImage *image = NULL;
        size_t size;

        size = sizeof (DxfImage);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((image = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                image = NULL;
        }
        else
        {
                memset (image, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c IMAGE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfImage *
dxf_image_init
(
        DxfImage *image
                /*!< DXF image entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                image = dxf_image_new ();
        }
        if (image == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        image->id_code = 0;
        image->linetype = strdup (DXF_DEFAULT_LINETYPE);
        image->layer = strdup (DXF_DEFAULT_LAYER);
        image->elevation = 0.0;
        image->thickness = 0.0;
        image->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        image->visibility = DXF_DEFAULT_VISIBILITY;
        image->color = DXF_COLOR_BYLAYER;
        image->paperspace = DXF_MODELSPACE;
        image->graphics_data_size = 0;
        image->shadow_mode = 0;
        image->dictionary_owner_soft = strdup ("");
        image->material = strdup ("");
        image->dictionary_owner_hard = strdup ("");
        image->lineweight = 0;
        image->plot_style_name = strdup ("");
        image->color_value = 0;
        image->color_name = strdup ("");
        image->transparency = 0;
        image->image_display_properties = 0;
        image->clipping_boundary_type = 0;
        image->class_version = 0;
        image->number_of_clip_boundary_vertices = 0;
        image->clipping_state = 0;
        image->brightness = 50;
        image->contrast = 50;
        image->fade = 50;
        image->imagedef_object = strdup ("");
        image->imagedef_reactor_object = strdup ("");
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        image->p0 = NULL;
        image->p1 = NULL;
        image->p2 = NULL;
        image->p3 = NULL;
        image->p4 = NULL;
        image->binary_graphics_data = NULL;
        image->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Read data from a DXF file into a DXF \c IMAGE entity.
 *
 * The last line read from file contained the string "IMAGE". \n
 * Now follows some data for the \c IMAGE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c image. \n
 *
 * \return a pointer to \c image.
 */
DxfImage *
dxf_image_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfImage *image
                /*!< DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfPoint *iter = NULL;
        int next_x4;
        DxfBinaryData *iter310 = NULL;
        int iter330;
        int iter360;

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
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                image = dxf_image_init (image);
        }
        if (image->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                image->binary_graphics_data = dxf_binary_data_init (image->binary_graphics_data);
                if (image->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (image->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p0 = dxf_point_init (image->p0);
                if (image->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (image->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p1 = dxf_point_init (image->p1);
                if (image->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (image->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p2 = dxf_point_init (image->p2);
                if (image->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (image->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p3 = dxf_point_init (image->p3);
                if (image->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (image->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p4 = dxf_point_init (image->p4);
                if (image->p4 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter = (DxfPoint *) image->p4;
        next_x4 = 0;
        iter310 = (DxfBinaryData *) image->binary_graphics_data;
        iter330 = 0;
        iter360 = 0;
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
                        fscanf (fp->fp, "%x\n", (uint *) &image->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the insertion point coordinate. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the insertion point coordinate. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the insertion point coordinate. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the U-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the U-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the U-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p1->z0);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the V-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p2->x0);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the V-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p2->y0);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the V-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p2->z0);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * U-value of image size in pixels. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p3->x0);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * V-value of image size in pixels. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->p3->y0);
                }
                else if (strcmp (temp_string, "14") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of a clip boundary vertex. */
                        (fp->line_number)++;
                        if (next_x4)
                        {
                                iter->next = (struct DxfPoint *) dxf_point_init ((DxfPoint *) iter->next);
                                iter = (DxfPoint *) iter->next;
                                next_x4 = 0;
                        }
                        fscanf (fp->fp, "%lf\n", &iter->x0);
                }
                else if (strcmp (temp_string, "24") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of a clip boundary vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->y0);
                        next_x4 = 1;
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (image->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &image->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * image display properties. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->image_display_properties);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * clipping boundary type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->clipping_boundary_type);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the class
                         * version. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &image->class_version);
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing the number of
                         * clip boundary vertices. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &image->number_of_clip_boundary_vertices);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &image->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbRasterImage") != 0)))
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
                        fscanf (fp->fp, "%d\n", &image->graphics_data_size);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing the clipping
                         * state. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->clipping_state);
                }
                else if (strcmp (temp_string, "281") == 0)
                {
                        /* Now follows a string containing the
                         * brightness value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->brightness);
                }
                else if (strcmp (temp_string, "282") == 0)
                {
                        /* Now follows a string containing the contrast
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->contrast);
                }
                else if (strcmp (temp_string, "283") == 0)
                {
                        /* Now follows a string containing the fade
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->fade);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->shadow_mode);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a hard
                         * reference to imagedef object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->imagedef_object);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        if (iter360 == 0)
                        {
                                /* Now follows a string containing a hard-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->dictionary_owner_hard);
                        }
                        if (iter360 == 1)
                        {
                                /* Now follows a string containing a hard
                                 * reference to imagedef_reactor object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->imagedef_reactor_object);
                        }
                        iter360++;
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &image->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &image->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, image->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &image->transparency);
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
        if (strcmp (image->linetype, "") == 0)
        {
                image->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (image->layer, "") == 0)
        {
                image->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Write DXF output for a DXF \c IMAGE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_image_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfImage *image
                /*!< DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("IMAGE");
        DxfPoint *iter = NULL;

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
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (strcmp (image->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, image->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                image->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (image->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, image->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to default layer.\n")),
                  dxf_entity_name);
                image->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (image->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", image->id_code);
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
        if ((strcmp (image->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", image->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (image->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", image->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (image->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", image->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (image->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", image->layer);
        if (strcmp (image->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", image->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (image->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", image->material);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (image->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", image->elevation);
        }
        if (image->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", image->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", image->lineweight);
        }
        if (image->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", image->linetype_scale);
        }
        if (image->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", image->visibility);
        }        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", image->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", image->graphics_data_size);
#endif
                if (image->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) image->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", image->color_value);
                fprintf (fp->fp, "430\n%s\n", image->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", image->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", image->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", image->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbRasterImage\n");
        }
        if (image->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", image->thickness);
        }
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", image->class_version);
        fprintf (fp->fp, " 10\n%f\n", image->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", image->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", image->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", image->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", image->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", image->p1->z0);
        fprintf (fp->fp, " 12\n%f\n", image->p2->x0);
        fprintf (fp->fp, " 22\n%f\n", image->p2->y0);
        fprintf (fp->fp, " 32\n%f\n", image->p2->z0);
        fprintf (fp->fp, " 13\n%f\n", image->p3->x0);
        fprintf (fp->fp, " 23\n%f\n", image->p3->y0);
        fprintf (fp->fp, "340\n%s\n", image->imagedef_object);
        fprintf (fp->fp, " 70\n%hd\n", image->image_display_properties);
        fprintf (fp->fp, "280\n%hd\n", image->clipping_state);
        fprintf (fp->fp, "281\n%hd\n", image->brightness);
        fprintf (fp->fp, "282\n%hd\n", image->contrast);
        fprintf (fp->fp, "283\n%hd\n", image->fade);
        fprintf (fp->fp, "360\n%s\n", image->imagedef_reactor_object);
        fprintf (fp->fp, " 71\n%hd\n", image->clipping_boundary_type);
        fprintf (fp->fp, " 91\n%" PRIi32 "\n", image->number_of_clip_boundary_vertices);
        /* Now follows a sinle linked list of points (vertices).
         * We do not keep track of the number of points (vertices),
         * we just traverse down until the first NULL pointer is found.  */
        iter = (DxfPoint *) image->p4;
        while (iter != NULL)
        {
                fprintf (fp->fp, " 14\n%f\n", iter->x0);
                fprintf (fp->fp, " 24\n%f\n", iter->y0);
                iter = (DxfPoint *) iter->next;
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c IMAGE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_image_free
(
        DxfImage *image
                /*!< Pointer to the memory occupied by the DXF \c IMAGE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (image->linetype);
        free (image->layer);
        dxf_binary_data_free_list (image->binary_graphics_data);
        free (image->dictionary_owner_soft);
        free (image->material);
        free (image->dictionary_owner_hard);
        free (image->object_owner_soft);
        free (image->plot_style_name);
        free (image->color_name);
        dxf_point_free (image->p0);
        dxf_point_free (image->p1);
        dxf_point_free (image->p2);
        dxf_point_free (image->p3);
        dxf_point_free_list (image->p4);
        free (image->imagedef_object);
        free (image->imagedef_reactor_object);
        free (image);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c IMAGE entities and all their data fields.
 */
void
dxf_image_free_list
(
        DxfImage *images
                /*!< pointer to the single linked list of DXF \c IMAGE
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (images == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (images != NULL)
        {
                DxfImage *iter = (DxfImage *) images->next;
                dxf_image_free (images);
                images = (DxfImage *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c IMAGE entity.
 *
 * \return \c id_code when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_image_get_id_code
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_id_code
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
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
        if (image == NULL)
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
        image->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c linetype from a DXF \c IMAGE entity.
 *
 * \return \c linetype when sucessful, or \c NULL when an error occurred.
 */
char *
dxf_image_get_linetype
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_linetype
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c layer from a DXF \c IMAGE entity.
 *
 * \return \c layer when sucessful, or \c NULL when an error occurred.
 */
char *
dxf_image_get_layer
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_layer
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c elevation from a DXF \c IMAGE entity.
 *
 * \return \c elevation when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_image_get_elevation
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_elevation
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c thickness from a DXF \c IMAGE entity.
 *
 * \return \c thickness when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_image_get_thickness
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_thickness
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c IMAGE entity.
 *
 * \return \c linetype_scale when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_image_get_linetype_scale
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_linetype_scale
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c visibility from a DXF \c IMAGE entity.
 *
 * \return \c visibility when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_image_get_visibility
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_visibility
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c color from a DXF \c IMAGE entity.
 *
 * \return \c color when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int16_t
dxf_image_get_color
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->color);
}


/*!
 * \brief Set the \c color for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_color
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c IMAGE entity.
 *
 * \return \c paperspace flag value when successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int16_t
dxf_image_get_paperspace
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_paperspace
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c IMAGE
 * entity.
 *
 * \return \c graphics_data_size flag value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_image_get_graphics_data_size
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_graphics_data_size
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c IMAGE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_image_get_shadow_mode
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_shadow_mode
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF 
 * \c IMAGE entity.
 *
 * \return a pointer to the \c binary_graphics_data when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_image_get_binary_graphics_data
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) image->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_binary_graphics_data
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF
 * \c IMAGE entity.
 *
 * \return a pointer to \c dictionary_owner_soft when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_image_get_dictionary_owner_soft
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_dictionary_owner_soft
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c IMAGE entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_image_get_object_owner_soft
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c IMAGE entity.
 */
DxfImage *
dxf_image_set_object_owner_soft
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c IMAGE entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_image_get_material
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_material
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF
 * \c IMAGE entity.
 *
 * \return a pointer to \c dictionary_owner_hard when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_image_get_dictionary_owner_hard
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_dictionary_owner_hard
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c lineweight from a DXF \c IMAGE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_image_get_lineweight
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_lineweight
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c IMAGE entity.
 *
 * \return \c plot_style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_image_get_plot_style_name
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_plot_style_name
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c color_value from a DXF \c IMAGE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_image_get_color_value
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_color_value
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c color_name from a DXF \c IMAGE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_image_get_color_name
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_color_name
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c transparency from a DXF \c IMAGE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_image_get_transparency
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_transparency
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the insertion point \c p0 of a DXF \c IMAGE entity.
 *
 * \return the insertion point \c p0.
 */
DxfPoint *
dxf_image_get_p0
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a DXF \c IMAGE entity.
 *
 * \return a pointer to a DXF \c IMAGE entity.
 */
DxfImage *
dxf_image_set_p0
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a DXF \c IMAGE
 * entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_image_get_x0
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_x0
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double x0
                /*!< the X-value of the insertion point \c x0 of a DXF
                 * \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p0 = dxf_point_init (image->p0);
                if (image->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a DXF \c IMAGE
 * entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_image_get_y0
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_y0
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a DXF
                 * \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p0 = dxf_point_init (image->p0);
                if (image->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a DXF \c IMAGE
 * entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_image_get_z0
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_z0
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double z0
                /*!< the Z-value of the insertion point \c z0 of a DXF
                 * \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p0 = dxf_point_init (image->p0);
                if (image->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the U-vector of a single pixel \c p1 of a DXF \c IMAGE
 * entity.
 *
 * \return the U-vector of a single pixel \c p1.
 */
DxfPoint *
dxf_image_get_p1
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p1);
}


/*!
 * \brief Set the U-vector of a single pixel \c p1 of a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to a DXF \c IMAGE entity.
 */
DxfImage *
dxf_image_set_p1
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the X-value of the U-vector of a single pixel \c x1 of a
 * DXF \c IMAGE entity.
 *
 * \return the X-value of the U-vector of a single pixel \c x1.
 */
double
dxf_image_get_x1
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p1->x0);
}


/*!
 * \brief Set the X-value of the U-vector of a single pixel \c x1 of a
 * DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_x1
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double x1
                /*!< the X-value of the U-vector of a single pixel \c x1
                 * of a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p1 = dxf_point_init (image->p1);
                if (image->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the Y-value of the U-vector of a single pixel \c y1 of a
 * DXF \c IMAGE entity.
 *
 * \return the Y-value of the U-vector of a single pixel \c y1.
 */
double
dxf_image_get_y1
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p1->y0);
}


/*!
 * \brief Set the Y-value of the U-vector of a single pixel \c y1 of a
 * DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_y1
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double y1
                /*!< the Y value of the U-vector of a single pixel \c y1
                 * of a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p1 = dxf_point_init (image->p1);
                if (image->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the Z-value of the U-vector of a single pixel \c z1 of a
 * DXF \c IMAGE entity.
 *
 * \return the Z-value of the U-vector of a single pixel \c z1.
 */
double
dxf_image_get_z1
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p1->z0);
}


/*!
 * \brief Set the Z-value of the U-vector of a single pixel \c z1 of a
 * DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_z1
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double z1
                /*!< the Z-value of the U-vector of a single pixel \c z1
                 * of a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p1 = dxf_point_init (image->p1);
                if (image->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the V-vector of a single pixel \c p2 of a DXF \c IMAGE
 * entity.
 *
 * \return the V-vector of a single pixel \c p2.
 */
DxfPoint *
dxf_image_get_p2
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p2);
}


/*!
 * \brief Set the V-vector of a single pixel \c p2 of a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to a DXF \c IMAGE entity.
 */
DxfImage *
dxf_image_set_p2
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        DxfPoint *p2
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->p2 = p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the X-value of the V-vector of a single pixel \c x2 of a
 * DXF \c IMAGE entity.
 *
 * \return the X-value of the V-vector of a single pixel \c x2.
 */
double
dxf_image_get_x2
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p2->x0);
}


/*!
 * \brief Set the X-value of the V-vector of a single pixel \c x2 of a
 * DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_x2
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double x2
                /*!< the X-value of the V-vector of a single pixel \c x2
                 * of a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p2 = dxf_point_init (image->p2);
                if (image->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the Y-value of the V-vector of a single pixel \c y2 of a
 * DXF \c IMAGE entity.
 *
 * \return the Y-value of the V-vector of a single pixel \c y2.
 */
double
dxf_image_get_y2
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p2->y0);
}


/*!
 * \brief Set the Y-value of the V-vector of a single pixel \c y2 of a
 * DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_y2
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double y2
                /*!< the Y-value of the V-vector of a single pixel \c y2
                 * of a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p2 = dxf_point_init (image->p2);
                if (image->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the Z-value of the V-vector of a single pixel \c z2 of a
 * DXF \c IMAGE entity.
 *
 * \return the Z-value of the V-vector of a single pixel \c z2.
 */
double
dxf_image_get_z2
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p2->z0);
}


/*!
 * \brief Set the Z-value of the V-vector of a single pixel \c z2 of a
 * DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_z2
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double z2
                /*!< the Z-value of the V-vector of a single pixel \c z2
                 * of a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p2 = dxf_point_init (image->p2);
                if (image->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the U- and V-value of the image in pixel size \c p3 of a
 * DXF \c IMAGE entity.
 *
 * \return the U- and V-value of the image in pixel size \c p3.
 */
DxfPoint *
dxf_image_get_p3
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p3);
}


/*!
 * \brief Set the U- and V-value of the image in pixel size \c p3 of a
 * DXF \c IMAGE entity.
 *
 * \return a pointer to a DXF \c IMAGE entity.
 */
DxfImage *
dxf_image_set_p3
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        DxfPoint *p3
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->p3 = p3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the U-value of the image in pixel size \c x3 of a
 * DXF \c IMAGE entity.
 *
 * \return the U-value of the image in pixel size \c x3.
 */
double
dxf_image_get_x3
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p3->x0);
}


/*!
 * \brief Set the U-value of the image in pixel size \c x3 of a DXF
 * \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_x3
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double x3
                /*!< the U-value of the image in pixel size \c x3 of a
                 * DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p3 = dxf_point_init (image->p3);
                if (image->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p3->x0 = x3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the V-value of the image in pixel size \c y3 of a
 * DXF \c IMAGE entity.
 *
 * \return the V-value of the image in pixel size \c y3.
 */
double
dxf_image_get_y3
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p3->y0);
}


/*!
 * \brief Set the V-value of the image in pixel size \c y3 of a DXF
 * \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_y3
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double y3
                /*!< the V-value of the image in pixel size \c y3 of a
                 * DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p3 = dxf_point_init (image->p3);
                if (image->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p3->y0 = y3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the clip boundary vertex (in OCS) (multiple entries) \c p4
 * of a DXF \c IMAGE entity.
 *
 * \return the clip boundary vertex (in OCS) (multiple entries) \c p4.
 */
DxfPoint *
dxf_image_get_p4
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p4);
}


/*!
 * \brief Set the clip boundary vertex (in OCS) (multiple entries)
 * \c p4 of a DXF \c IMAGE entity.
 *
 * \return a pointer to a DXF \c IMAGE entity.
 */
DxfImage *
dxf_image_set_p4
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        DxfPoint *p4
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->p4 = p4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the X-value of the clip boundary vertex (in OCS) (multiple
 * entries) \c x4 of a DXF \c IMAGE entity.
 *
 * \return the X-value of the clip boundary vertex (in OCS) (multiple
 * entries) \c x4.
 */
double
dxf_image_get_x4
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p4->x0);
}


/*!
 * \brief Set the X-value of the clip boundary vertex (in OCS) (multiple
 * entries) \c x4 of a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_x4
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double x4
                /*!< the X-value of the clip boundary vertex (in OCS)
                 * (multiple entries) \c x4 of a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p4 = dxf_point_init (image->p4);
                if (image->p4 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p4->x0 = x4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the Y-value of the clip boundary vertex (in OCS) (multiple
 * entries) \c y4 of a DXF \c IMAGE entity.
 *
 * \return the Y-value of the clip boundary vertex (in OCS) (multiple
 * entries) \c y4.
 */
double
dxf_image_get_y4
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->p4->y0);
}


/*!
 * \brief Set the Y-value of the clip boundary vertex (in OCS) (multiple
 * entries) \c y4 of a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_y4
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        double y4
                /*!< the Y-value of the clip boundary vertex (in OCS)
                 * (multiple entries) \c y4 of a DXF \c IMAGE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                image->p4 = dxf_point_init (image->p4);
                if (image->p4 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        image->p4->y0 = y4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c image_display_properties value from a DXF \c IMAGE
 * entity.
 *
 * \return \c graphics_data_size flag value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_image_get_image_display_properties
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->image_display_properties < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->image_display_properties > 15)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->image_display_properties);
}


/*!
 * \brief Set the \c image_display_properties value for a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_image_display_properties
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t image_display_properties
                /*!< the \c image_display_properties value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image_display_properties < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (image_display_properties > 15)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        image->image_display_properties = image_display_properties;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c clipping_boundary_type value from a DXF \c IMAGE
 * entity.
 *
 * \return \c clipping_boundary_type value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_image_get_clipping_boundary_type
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->clipping_boundary_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->clipping_boundary_type > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->clipping_boundary_type);
}


/*!
 * \brief Set the \c clipping_boundary_type value for a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_clipping_boundary_type
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t clipping_boundary_type
                /*!< the \c clipping_boundary_type value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (clipping_boundary_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (clipping_boundary_type > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        image->clipping_boundary_type = clipping_boundary_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c class_version from a DXF \c IMAGE entity.
 *
 * \return \c class_version when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_image_get_class_version
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->class_version);
}


/*!
 * \brief Set the \c class_version for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_class_version
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int32_t class_version
                /*!< the \c class_version to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->class_version = class_version;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c number_of_clip_boundary_vertices from a DXF
 * \c IMAGE entity.
 *
 * \return \c number_of_clip_boundary_vertices when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_image_get_number_of_clip_boundary_vertices
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->number_of_clip_boundary_vertices);
}


/*!
 * \brief Set the \c number_of_clip_boundary_vertices for a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_number_of_clip_boundary_vertices
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int32_t number_of_clip_boundary_vertices
                /*!< the \c number_of_clip_boundary_vertices to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->number_of_clip_boundary_vertices = number_of_clip_boundary_vertices;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c clipping_state flag value from a DXF \c IMAGE
 * entity.
 *
 * \return \c clipping_state flag value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_image_get_clipping_state
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->clipping_state < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->clipping_state > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->clipping_state);
}


/*!
 * \brief Set the \c clipping_state flag value for a DXF \c IMAGE
 * entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_clipping_state
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t clipping_state
                /*!< the \c clipping_state flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (clipping_state < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (clipping_state > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        image->clipping_state = clipping_state;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c brightness value from a DXF \c IMAGE entity.
 *
 * \return \c brightness value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_image_get_brightness
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->brightness < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->brightness > 100)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->brightness);
}


/*!
 * \brief Set the \c brightness value for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_brightness
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t brightness
                /*!< the \c brightness value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (brightness < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (brightness > 100)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        image->brightness = brightness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c contrast value from a DXF \c IMAGE entity.
 *
 * \return \c contrast value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_image_get_contrast
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->contrast < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->contrast > 100)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->contrast);
}


/*!
 * \brief Set the \c contrast value for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_contrast
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t contrast
                /*!< the \c contrast value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (contrast < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (contrast > 100)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        image->contrast = contrast;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c fade value from a DXF \c IMAGE entity.
 *
 * \return \c fade value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_image_get_fade
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (image->fade < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (image->fade > 100)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image->fade);
}


/*!
 * \brief Set the \c fade value for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_fade
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        int16_t fade
                /*!< the \c fade value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (fade < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (fade > 100)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        image->fade = fade;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c imagedef_object from a DXF \c IMAGE entity.
 *
 * \return \c imagedef_object when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_image_get_imagedef_object
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->imagedef_object ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->imagedef_object));
}


/*!
 * \brief Set the \c imagedef_object for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_imagedef_object
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *imagedef_object
                /*!< a string containing the \c imagedef_object for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (imagedef_object == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->imagedef_object = strdup (imagedef_object);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the \c imagedef_reactor_object from a DXF \c IMAGE entity.
 *
 * \return \c imagedef_reactor_object when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_image_get_imagedef_reactor_object
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->imagedef_reactor_object ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (image->imagedef_reactor_object));
}


/*!
 * \brief Set the \c imagedef_reactor_object for a DXF \c IMAGE entity.
 *
 * \return a pointer to \c image when successful, or \c NULL when an
 * error occurred.
 */
DxfImage *
dxf_image_set_imagedef_reactor_object
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        char *imagedef_reactor_object
                /*!< a string containing the \c imagedef_reactor_object
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (imagedef_reactor_object == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        image->imagedef_reactor_object = strdup (imagedef_reactor_object);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the pointer to the next \c IMAGE entity from a DXF 
 * \c IMAGE entity.
 *
 * \return pointer to the next \c IMAGE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfImage *
dxf_image_get_next
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfImage *) image->next);
}


/*!
 * \brief Set the pointer to the next \c IMAGE for a DXF \c IMAGE
 * entity.
 */
DxfImage *
dxf_image_set_next
(
        DxfImage *image,
                /*!< a pointer to a DXF \c IMAGE entity. */
        DxfImage *next
                /*!< a pointer to the next \c IMAGE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
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
        image->next = (struct DxfImage *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (image);
}


/*!
 * \brief Get the pointer to the last \c IMAGE entity from a linked list of
 * DXF \c IMAGE entities.
 *
 * \return pointer to the last \c IMAGE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfImage *
dxf_image_get_last
(
        DxfImage *image
                /*!< a pointer to a DXF \c IMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (image == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (image->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfImage *) image);
        }
        DxfImage *iter = (DxfImage *) image->next;
        while (iter->next != NULL)
        {
                iter = (DxfImage *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfImage *) iter);
}


/* EOF */
