/*!
 * \file shape.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2017, 2018, 2019,
 * 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF shape entity (\c SHAPE).
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


#include "shape.h"


/*!
 * \brief Allocate memory for a \c DxfShape.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfShape *
dxf_shape_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfShape *shape = NULL;
        size_t size;

        size = sizeof (DxfShape);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((shape = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfShape struct.\n")),
                  __FUNCTION__);
                shape = NULL;
        }
        else
        {
                memset (shape, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SHAPE 
 * entity to default values.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfShape *
dxf_shape_init
(
        DxfShape *shape
                /*!< a pointer to the DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                shape = dxf_shape_new ();
        }
        if (shape == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfShape struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        shape->id_code = 0;
        shape->linetype = strdup (DXF_DEFAULT_LINETYPE);
        shape->layer = strdup (DXF_DEFAULT_LAYER);
        shape->elevation = 0.0;
        shape->thickness = 0.0;
        shape->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        shape->visibility = DXF_DEFAULT_VISIBILITY;
        shape->color = DXF_COLOR_BYLAYER;
        shape->paperspace = DXF_MODELSPACE;
        shape->graphics_data_size = 0;
        shape->shadow_mode = 0;
        shape->binary_graphics_data = dxf_binary_graphics_data_new ();
        shape->binary_graphics_data = dxf_binary_graphics_data_init (shape->binary_graphics_data);
        shape->dictionary_owner_soft = strdup ("");
        shape->material = strdup ("");
        shape->dictionary_owner_hard = strdup ("");
        shape->lineweight = 0;
        shape->plot_style_name = strdup ("");
        shape->color_value = 0;
        shape->color_name = strdup ("");
        shape->transparency = 0;
        shape->shape_name = strdup ("");
        shape->p0->x0 = 0.0;
        shape->p0->y0 = 0.0;
        shape->p0->z0 = 0.0;
        shape->size = 0.0;
        shape->rel_x_scale = 0.0;
        shape->rot_angle = 0.0;
        shape->obl_angle = 0.0;
        shape->extr_x0 = 0.0;
        shape->extr_y0 = 0.0;
        shape->extr_z0 = 0.0;
        shape->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Read data from a DXF file into a \c SHAPE entity.
 *
 * The last line read from file contained the string "SHAPE". \n
 * Hereafter follows some data for the \c SHAPE, to be terminated with
 * a "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 *
 * \return a pointer to \c shape.
 */
DxfShape *
dxf_shape_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfShape *shape
                /*!< a pointer to the DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        char *dxf_entity_name = strdup ("SHAPE");

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
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                shape = dxf_shape_init (shape);
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
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a shape
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->shape_name);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &shape->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->p0->z0);
                }
                else if (strcmp (temp_string, "38") == 0)
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * size. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->size);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->rel_x_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * oblique angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->obl_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &shape->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &shape->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &shape->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &shape->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbShape") != 0)))
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
                        fscanf (fp->fp, "%lf\n", &shape->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &shape->extr_z0);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &shape->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) shape->binary_graphics_data->next);
                        shape->binary_graphics_data = (DxfBinaryGraphicsData *) shape->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &shape->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &shape->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, shape->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &shape->transparency);
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
        if (strcmp (shape->shape_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, shape->id_code);
                return (NULL);
        }
        if (strcmp (shape->linetype, "") == 0)
        {
                shape->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (shape->layer, "") == 0)
        {
                shape->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Write DXF output for a DXF \c SHAPE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_shape_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfShape *shape
                /*!< a pointer to the DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SHAPE");

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
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (shape->shape_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, shape->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (shape->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, shape->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                shape->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (shape->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, shape->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                shape->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (shape->size == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () size has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, shape->id_code);
        }
        if (shape->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning: in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, shape->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (shape->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", shape->id_code);
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
        if ((strcmp (shape->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", shape->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (shape->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", shape->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (shape->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", shape->layer);
        if (strcmp (shape->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", shape->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (shape->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", shape->material);
        }
        if (shape->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", shape->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", shape->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (shape->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", shape->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (shape->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", shape->thickness);
        }
        if (shape->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", shape->linetype_scale);
        }
        if (shape->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", shape->visibility);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
          && (shape->graphics_data_size > 0))
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", shape->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", shape->graphics_data_size);
#endif
                if (shape->binary_graphics_data != NULL)
                {
                        DxfBinaryGraphicsData *iter;
                        iter = (DxfBinaryGraphicsData *) shape->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", dxf_binary_graphics_data_get_data_line (iter));
                                iter = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_get_next (iter);
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", shape->color_value);
                fprintf (fp->fp, "430\n%s\n", shape->color_name);
                fprintf (fp->fp, "440\n%ld\n", shape->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", shape->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", shape->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbShape\n");
        }
        if (shape->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", shape->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", shape->x0);
        fprintf (fp->fp, " 20\n%f\n", shape->y0);
        fprintf (fp->fp, " 30\n%f\n", shape->z0);
        fprintf (fp->fp, " 40\n%f\n", shape->size);
        fprintf (fp->fp, "  2\n%s\n", shape->shape_name);
        if (shape->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", shape->rot_angle);
        }
        if (shape->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", shape->rel_x_scale);
        }
        if (shape->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", shape->obl_angle);
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (shape->extr_x0 != 0.0)
                && (shape->extr_y0 != 0.0)
                && (shape->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", shape->extr_x0);
                fprintf (fp->fp, "220\n%f\n", shape->extr_y0);
                fprintf (fp->fp, "230\n%f\n", shape->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SHAPE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_shape_free
(
        DxfShape *shape
                /*!< a pointer to the memory occupied by the DXF \c SHAPE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (shape->linetype);
        free (shape->layer);
        dxf_binary_graphics_data_free_list (shape->binary_graphics_data);
        free (shape->dictionary_owner_soft);
        free (shape->material);
        free (shape->dictionary_owner_hard);
        free (shape->plot_style_name);
        free (shape->color_name);
        free (shape->shape_name);
        dxf_point_free (shape->p0);
        free (shape);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SHAPE entities and all their data fields.
 */
void
dxf_shape_free_list
(
        DxfShape *shapes
                /*!< a pointer to the single linked list of DXF
                 * \c SHAPE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (shapes == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (shapes != NULL)
        {
                DxfShape *iter = (DxfShape *) shapes->next;
                dxf_shape_free (shapes);
                shapes = (DxfShape *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SHAPE entity.
 *
 * \return \c id_code.
 */
int
dxf_shape_get_id_code
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_id_code
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
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
        if (shape == NULL)
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
        shape->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c linetype from a DXF \c SHAPE entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_shape_get_linetype
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (shape->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_linetype
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c layer from a DXF \c SHAPE entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_shape_get_layer
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (shape->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_layer
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c elevation from a DXF \c SHAPE entity.
 *
 * \return \c elevation.
 */
double
dxf_shape_get_elevation
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_elevation
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c thickness from a DXF \c SHAPE entity.
 *
 * \return \c thickness.
 */
double
dxf_shape_get_thickness
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_thickness
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c SHAPE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_shape_get_linetype_scale
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_linetype_scale
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c visibility from a DXF \c SHAPE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_shape_get_visibility
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (shape->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_visibility
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c color from a DXF \c SHAPE entity.
 *
 * \return color.
 */
int
dxf_shape_get_color
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->color);
}


/*!
 * \brief Set the \c color for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_color
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c SHAPE entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_shape_get_paperspace
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (shape->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_paperspace
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c SHAPE entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_shape_get_graphics_data_size
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (shape->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_graphics_data_size
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c SHAPE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_shape_get_shadow_mode
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (shape->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_shadow_mode
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c SHAPE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_shape_get_binary_graphics_data
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) shape->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_binary_graphics_data
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SHAPE entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_shape_get_dictionary_owner_soft
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (shape->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_dictionary_owner_soft
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c SHAPE entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_shape_get_material
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (shape->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_material
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SHAPE entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_shape_get_dictionary_owner_hard
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (shape->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_dictionary_owner_hard
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c lineweight from a DXF \c SHAPE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_shape_get_lineweight
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_lineweight
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c SHAPE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_shape_get_plot_style_name
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (shape->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_plot_style_name
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c color_value from a DXF \c SHAPE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_shape_get_color_value
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_color_value
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c color_name from a DXF \c SHAPE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_shape_get_color_name
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (shape->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_color_name
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c transparency from a DXF \c SHAPE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_shape_get_transparency
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_transparency
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the insertion point \c p0 of a DXF \c SHAPE entity.
 *
 * \return the insertion point \c p0.
 */
DxfPoint *
dxf_shape_get_p0
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a DXF \c SHAPE entity.
 *
 * \return a pointer to a DXF \c SHAPE entity.
 */
DxfShape *
dxf_shape_set_p0
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a DXF \c SHAPE
 * entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_shape_get_x0
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a DXF \c SHAPE
 * entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_x0
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double x0
                /*!< the X-value of the insertion point \c x0 of a DXF
                 * \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a DXF \c SHAPE
 * entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_shape_get_y0
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a DXF \c SHAPE
 * entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_y0
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a DXF
                 * \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a DXF \c SHAPE
 * entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_shape_get_z0
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (shape->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a DXF \c SHAPE
 * entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_z0
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double z0
                /*!< the Z-value of the insertion point \c z0 of a DXF
                 * \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c size of a DXF \c SHAPE entity.
 *
 * \return the \c size.
 */
double
dxf_shape_get_size
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->size);
}


/*!
 * \brief Set the \c size of a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_size
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double size
                /*!< the \c size of a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->size = size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c rel_x_scale of a DXF \c SHAPE entity.
 *
 * \return the \c rel_x_scale.
 */
double
dxf_shape_get_rel_x_scale
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->rel_x_scale);
}


/*!
 * \brief Set the \c rel_x_scale of a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_rel_x_scale
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double rel_x_scale
                /*!< the \c rel_x_scale of a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->rel_x_scale = rel_x_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c rot_angle of a DXF \c SHAPE entity.
 *
 * \return the \c rot_angle.
 */
double
dxf_shape_get_rot_angle
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->rot_angle);
}


/*!
 * \brief Set the \c rot_angle of a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_rot_angle
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double rot_angle
                /*!< the \c rot_angle of a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->rot_angle = rot_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the \c obl_angle of a DXF \c SHAPE entity.
 *
 * \return the \c obl_angle.
 */
double
dxf_shape_get_obl_angle
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->obl_angle);
}


/*!
 * \brief Set the \c obl_angle of a DXF \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_obl_angle
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double obl_angle
                /*!< the \c obl_angle of a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->obl_angle = obl_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c SHAPE entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_shape_get_extr_x0
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_extr_x0
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c SHAPE entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_shape_get_extr_y0
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_extr_y0
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c SHAPE entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_shape_get_extr_z0
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c SHAPE entity.
 *
 * \return a pointer to \c shape when successful, or \c NULL when an
 * error occurred.
 */
DxfShape *
dxf_shape_set_extr_z0
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c SHAPE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        shape->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the pointer to the next \c SHAPE entity from a DXF
 * \c SHAPE entity.
 *
 * \return pointer to the next \c SHAPE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfShape *
dxf_shape_get_next
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfShape *) shape->next);
}


/*!
 * \brief Set the pointer to the next \c SHAPE for a DXF \c SHAPE
 * entity.
 */
DxfShape *
dxf_shape_set_next
(
        DxfShape *shape,
                /*!< a pointer to a DXF \c SHAPE entity. */
        DxfShape *next
                /*!< a pointer to the next \c SHAPE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
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
        shape->next = (struct DxfShape *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (shape);
}


/*!
 * \brief Get the pointer to the last \c SHAPE entity from a linked list
 * of DXF \c SHAPE entities.
 *
 * \return pointer to the last \c SHAPE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfShape *
dxf_shape_get_last
(
        DxfShape *shape
                /*!< a pointer to a DXF \c SHAPE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shape->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfShape *) shape);
        }
        DxfShape *iter = (DxfShape *) shape->next;
        while (iter->next != NULL)
        {
                iter = (DxfShape *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfShape *) iter);
}


/* EOF */
