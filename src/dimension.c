/*!
 * \file dimension.c
 *
 * \author Copyright (C) 2012, 2014, 2015, 2016, 2017, 2018, 2019, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dimension entity (\c DIMENSION).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
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


#include "dimension.h"


/*!
 * \brief Allocate memory for a DXF \c DIMENSION.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfDimension *
dxf_dimension_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDimension *dimension = NULL;
        size_t size;

        size = sizeof (DxfDimension);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dimension = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                dimension = NULL;
        }
        else
        {
                memset (dimension, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c
 * DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_init
(
        DxfDimension *dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dimension = dxf_dimension_new ();
        }
        if (dimension == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        dimension->id_code = 0;
        dimension->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dimension->layer = strdup (DXF_DEFAULT_LAYER);
        dimension->elevation = 0.0;
        dimension->thickness = 0.0;
        dimension->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dimension->visibility = DXF_DEFAULT_VISIBILITY;
        dimension->color = DXF_COLOR_BYLAYER;
        dimension->paperspace = DXF_PAPERSPACE;
        dimension->graphics_data_size = 0;
        dimension->shadow_mode = 0;
        dimension->dictionary_owner_soft = strdup ("");
        dimension->object_owner_soft = strdup ("");
        dimension->material = strdup ("");
        dimension->dictionary_owner_hard = strdup ("");
        dimension->lineweight = 0;
        dimension->plot_style_name = strdup ("");
        dimension->color_value = 0;
        dimension->color_name = strdup ("");
        dimension->transparency = 0;
        dimension->dim_text = strdup ("");
        dimension->dimblock_name = strdup ("");
        dimension->dimstyle_name = strdup ("");
        dimension->p0->x0 = 0.0;
        dimension->p0->y0 = 0.0;
        dimension->p0->z0 = 0.0;
        dimension->p1->x0 = 0.0;
        dimension->p1->y0 = 0.0;
        dimension->p1->z0 = 0.0;
        dimension->p2->x0 = 0.0;
        dimension->p2->y0 = 0.0;
        dimension->p2->z0 = 0.0;
        dimension->p3->x0 = 0.0;
        dimension->p3->y0 = 0.0;
        dimension->p3->z0 = 0.0;
        dimension->p4->x0 = 0.0;
        dimension->p4->y0 = 0.0;
        dimension->p4->z0 = 0.0;
        dimension->p5->x0 = 0.0;
        dimension->p5->y0 = 0.0;
        dimension->p5->z0 = 0.0;
        dimension->p6->x0 = 0.0;
        dimension->p6->y0 = 0.0;
        dimension->p6->z0 = 0.0;
        dimension->leader_length = 0.0;
        dimension->text_line_spacing_factor = 0.0;
        dimension->actual_measurement = 0.0;
        dimension->angle = 0.0;
        dimension->hor_dir = 0.0;
        dimension->obl_angle = 0.0;
        dimension->text_angle = 0.0;
        dimension->flag = 0;
        dimension->attachment_point = 0;
        dimension->text_line_spacing = 0;
        dimension->extr_x0 = 0.0;
        dimension->extr_y0 = 0.0;
        dimension->extr_z0 = 0.0;
        dimension->version_number = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        dimension->binary_graphics_data = NULL;
        dimension->p0 = NULL;
        dimension->p1 = NULL;
        dimension->p2 = NULL;
        dimension->p3 = NULL;
        dimension->p4 = NULL;
        dimension->p5 = NULL;
        dimension->p6 = NULL;
        dimension->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DIMENSION entity.
 *
 * The last line read from file contained the string "DIMENSION". \n
 * Now follows some data for the \c DIMENSION, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDimension *dimension
                /*!< DXF \c DIMENSION entity. */
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
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dimension = dxf_dimension_init (dimension);
        }
        if (dimension->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                dimension->binary_graphics_data = dxf_binary_data_init (dimension->binary_graphics_data);
                if (dimension->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (dimension->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p0 = dxf_point_init (dimension->p0);
                if (dimension->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (dimension->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p1 = dxf_point_init (dimension->p1);
                if (dimension->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (dimension->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p2 = dxf_point_init (dimension->p2);
                if (dimension->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (dimension->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p3 = dxf_point_init (dimension->p3);
                if (dimension->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (dimension->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p4 = dxf_point_init (dimension->p4);
                if (dimension->p4 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (dimension->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p5 = dxf_point_init (dimension->p5);
                if (dimension->p5 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (dimension->p6 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p6 = dxf_point_init (dimension->p6);
                if (dimension->p6 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) dimension->binary_graphics_data;
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
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->dim_text);
                }
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a dimension
                         * block name string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->dimblock_name);
                }
                if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a dimension
                         * style name string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->dimstyle_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &dimension->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p1->z0);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p2->x0);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p2->y0);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p2->z0);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p3->x0);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p3->y0);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p3->z0);
                }
                else if (strcmp (temp_string, "14") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p4->x0);
                }
                else if (strcmp (temp_string, "24") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p4->y0);
                }
                else if (strcmp (temp_string, "34") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p4->z0);
                }
                else if (strcmp (temp_string, "15") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p5->x0);
                }
                else if (strcmp (temp_string, "25") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p5->y0);
                }
                else if (strcmp (temp_string, "35") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p5->z0);
                }
                else if (strcmp (temp_string, "16") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p6->x0);
                }
                else if (strcmp (temp_string, "26") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p6->y0);
                }
                else if (strcmp (temp_string, "36") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->p6->z0);
                }
                else if (strcmp (temp_string, "38") == 0)
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the leader
                         * length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->leader_length);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the text line
                         * spacing factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->text_line_spacing_factor);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the actual
                         * measurement. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->actual_measurement);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the angle of
                         * rotated, horizontal, or vertical linear
                         * dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the horizontal
                         * direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->hor_dir);
                }
                else if (strcmp (temp_string, "52") == 0)
                {
                        /* Now follows a string containing the oblique
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->obl_angle);
                }
                else if (strcmp (temp_string, "53") == 0)
                {
                        /* Now follows a string containing the text
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->text_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing a flag
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the attachment
                         * point value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->attachment_point);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the text line
                         * spacing value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->text_line_spacing);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &dimension->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                          && (strcmp (temp_string, "AcDbDimension") != 0)
                          && (strcmp (temp_string, "AcDbAlignedDimension") != 0)
                          && (strcmp (temp_string, "AcDbRotatedDimension") != 0)
                          && (strcmp (temp_string, "AcDb3PointAngularDimension") != 0)
                          && (strcmp (temp_string, "AcDbDiametricDimension") != 0)
                          && (strcmp (temp_string, "AcDbRadialDimension") != 0)
                          && (strcmp (temp_string, "AcDbOrdinateDimension") != 0))
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
                        fscanf (fp->fp, "%" PRIi32 "\n", &dimension->graphics_data_size);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->extr_z0);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing the version
                         * number value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->version_number);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->shadow_mode);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &dimension->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimension->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &dimension->transparency);
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
        if (strcmp (dxf_dimension_get_linetype (dimension), "") == 0)
        {
                dxf_dimension_set_linetype (dimension, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_dimension_get_layer (dimension), "") == 0)
        {
                dxf_dimension_set_layer (dimension, strdup (DXF_DEFAULT_LAYER));
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Write DXF output for a DXF \c DIMENSION entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dimension_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDimension *dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("DIMENSION");

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
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((dimension->flag > 6)
          || (dimension->flag < 0))
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
        }
        if (strcmp (dimension->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dimension->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dimension->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dimension->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dimension->id_code);
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
        if ((strcmp (dimension->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dimension->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dimension->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dimension->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dimension->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", dimension->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dimension->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dimension->layer);
        if (strcmp (dimension->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dimension->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (dimension->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", dimension->material);
        }
        if (dimension->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", dimension->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%hd\n", dimension->lineweight);
        }
        if (dimension->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dimension->linetype_scale);
        }
        if (dimension->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", dimension->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", dimension->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", dimension->graphics_data_size);
#endif
                if (dimension->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) dimension->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", dimension->color_value);
                fprintf (fp->fp, "430\n%s\n", dimension->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", dimension->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", dimension->plot_style_name);
                fprintf (fp->fp, "284\n%hd\n", dimension->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbDimension\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dimension->dimblock_name);
        if (fp->acad_version_number >= AutoCAD_2010)
        {
                fprintf (fp->fp, "280\n%d\n", dimension->version_number);
        }
        fprintf (fp->fp, " 10\n%f\n", dimension->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", dimension->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", dimension->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", dimension->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", dimension->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", dimension->p1->z0);
        fprintf (fp->fp, " 70\n%hd\n", dimension->flag);
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 71\n%hd\n", dimension->attachment_point);
                fprintf (fp->fp, " 72\n%hd\n", dimension->text_line_spacing);
                fprintf (fp->fp, " 41\n%f\n", dimension->text_line_spacing_factor);
                fprintf (fp->fp, " 42\n%f\n", dimension->actual_measurement);
        }
        fprintf (fp->fp, "  1\n%s\n", dimension->dim_text);
        fprintf (fp->fp, " 53\n%f\n", dimension->text_angle);
        fprintf (fp->fp, " 51\n%f\n", dimension->hor_dir);
        fprintf (fp->fp, "210\n%fn", dimension->extr_x0);
        fprintf (fp->fp, "220\n%fn", dimension->extr_y0);
        fprintf (fp->fp, "230\n%fn", dimension->extr_z0);
        fprintf (fp->fp, "  3\n%s\n", dimension->dimstyle_name);
        /* Rotated, horizontal, or vertical dimension. */
        if (dimension->flag == 0)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbAlignedDimension\n");
                }
                fprintf (fp->fp, " 12\n%f\n", dimension->p2->x0);
                fprintf (fp->fp, " 22\n%f\n", dimension->p2->y0);
                fprintf (fp->fp, " 32\n%f\n", dimension->p2->z0);
                fprintf (fp->fp, " 13\n%f\n", dimension->p3->x0);
                fprintf (fp->fp, " 23\n%f\n", dimension->p3->y0);
                fprintf (fp->fp, " 33\n%f\n", dimension->p3->z0);
                fprintf (fp->fp, " 14\n%f\n", dimension->p4->x0);
                fprintf (fp->fp, " 24\n%f\n", dimension->p4->y0);
                fprintf (fp->fp, " 34\n%f\n", dimension->p4->z0);
                fprintf (fp->fp, " 50\n%f\n", dimension->angle);
                fprintf (fp->fp, " 52\n%f\n", dimension->obl_angle);
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbRotatedDimension\n");
                }
        }
        /* Aligned dimension. */
        else if (dimension->flag == 1)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbAlignedDimension\n");
                }
                fprintf (fp->fp, " 12\n%f\n", dimension->p2->x0);
                fprintf (fp->fp, " 22\n%f\n", dimension->p2->y0);
                fprintf (fp->fp, " 32\n%f\n", dimension->p2->z0);
                fprintf (fp->fp, " 13\n%f\n", dimension->p3->x0);
                fprintf (fp->fp, " 23\n%f\n", dimension->p3->y0);
                fprintf (fp->fp, " 33\n%f\n", dimension->p3->z0);
                fprintf (fp->fp, " 14\n%f\n", dimension->p4->x0);
                fprintf (fp->fp, " 24\n%f\n", dimension->p4->y0);
                fprintf (fp->fp, " 34\n%f\n", dimension->p4->z0);
                fprintf (fp->fp, " 50\n%f\n", dimension->angle);
        }
        /* Angular dimension. */
        else if (dimension->flag == 2)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDb3PointAngularDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dimension->p3->x0);
                fprintf (fp->fp, " 23\n%f\n", dimension->p3->y0);
                fprintf (fp->fp, " 33\n%f\n", dimension->p3->z0);
                fprintf (fp->fp, " 14\n%f\n", dimension->p4->x0);
                fprintf (fp->fp, " 24\n%f\n", dimension->p4->y0);
                fprintf (fp->fp, " 34\n%f\n", dimension->p4->z0);
                fprintf (fp->fp, " 15\n%f\n", dimension->p5->x0);
                fprintf (fp->fp, " 25\n%f\n", dimension->p5->y0);
                fprintf (fp->fp, " 35\n%f\n", dimension->p5->z0);
                fprintf (fp->fp, " 16\n%f\n", dimension->p6->x0);
                fprintf (fp->fp, " 26\n%f\n", dimension->p6->y0);
                fprintf (fp->fp, " 36\n%f\n", dimension->p6->z0);
        }
        /* Diameter dimension. */
        else if (dimension->flag == 3)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbDiametricDimension\n");
                }
                fprintf (fp->fp, " 15\n%f\n", dimension->p5->x0);
                fprintf (fp->fp, " 25\n%f\n", dimension->p5->y0);
                fprintf (fp->fp, " 35\n%f\n", dimension->p5->z0);
                fprintf (fp->fp, " 40\n%f\n", dimension->leader_length);
        }
        /* Radius dimension. */
        else if (dimension->flag == 4)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbRadialDimension\n");
                }
                fprintf (fp->fp, " 15\n%f\n", dimension->p5->x0);
                fprintf (fp->fp, " 25\n%f\n", dimension->p5->y0);
                fprintf (fp->fp, " 35\n%f\n", dimension->p5->z0);
                fprintf (fp->fp, " 40\n%f\n", dimension->leader_length);
        }
        /* Angular 3-point dimension. */
        else if (dimension->flag == 5)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDb3PointAngularDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dimension->p3->x0);
                fprintf (fp->fp, " 23\n%f\n", dimension->p3->y0);
                fprintf (fp->fp, " 33\n%f\n", dimension->p3->z0);
                fprintf (fp->fp, " 14\n%f\n", dimension->p4->x0);
                fprintf (fp->fp, " 24\n%f\n", dimension->p4->y0);
                fprintf (fp->fp, " 34\n%f\n", dimension->p4->z0);
                fprintf (fp->fp, " 15\n%f\n", dimension->p5->x0);
                fprintf (fp->fp, " 25\n%f\n", dimension->p5->y0);
                fprintf (fp->fp, " 35\n%f\n", dimension->p5->z0);
                fprintf (fp->fp, " 16\n%f\n", dimension->p6->x0);
                fprintf (fp->fp, " 26\n%f\n", dimension->p6->y0);
                fprintf (fp->fp, " 36\n%f\n", dimension->p6->z0);
        }
        /* Ordinate dimension. */
        else if (dimension->flag == 6)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbOrdinateDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dimension->p3->x0);
                fprintf (fp->fp, " 23\n%f\n", dimension->p3->y0);
                fprintf (fp->fp, " 33\n%f\n", dimension->p3->z0);
                fprintf (fp->fp, " 14\n%f\n", dimension->p4->x0);
                fprintf (fp->fp, " 24\n%f\n", dimension->p4->y0);
                fprintf (fp->fp, " 34\n%f\n", dimension->p4->z0);
        }
        if (dimension->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dimension->thickness);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c DIMENSION and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dimension_free
(
        DxfDimension *dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dimension->linetype);
        free (dimension->layer);
        dxf_binary_data_free_list (dimension->binary_graphics_data);
        free (dimension->dim_text);
        free (dimension->dimblock_name);
        free (dimension->dimstyle_name);
        free (dimension->dictionary_owner_soft);
        free (dimension->object_owner_soft);
        free (dimension->material);
        free (dimension->dictionary_owner_hard);
        free (dimension->plot_style_name);
        free (dimension->color_name);
        free (dimension);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c DIMENSION entities and all their data fields.
 */
void
dxf_dimension_free_list
(
        DxfDimension *dimensions
                /*!< pointer to the single linked list of DXF
                 * \c DIMENSION entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dimensions == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return;
        }
        while (dimensions != NULL)
        {
                DxfDimension *iter = (DxfDimension *) dxf_dimension_get_next (dimensions);
                dxf_dimension_free (dimensions);
                dimensions = (DxfDimension *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c DIMENSION entity.
 *
 * \return \c id_code, or \c DXF_ERROR when an error occurred.
 */
int
dxf_dimension_get_id_code
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (DXF_ERROR);
        }
        if (dimension->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_id_code
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
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
        if (dimension == NULL)
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
        dimension->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c linetype from a DXF \c DIMENSION entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_dimension_get_linetype
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_linetype
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c layer from a DXF \c DIMENSION entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_dimension_get_layer
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->layer));
}


/*!
 * \brief Set the layer for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_layer
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c elevation from a DXF \c DIMENSION entity.
 *
 * \return \c elevation, or \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_elevation
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_elevation
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c thickness from a DXF \c DIMENSION entity.
 *
 * \return \c thickness, or \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_thickness
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_thickness
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c DIMENSION entity.
 *
 * \return \c linetype_scale, or \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_linetype_scale
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_linetype_scale
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c visibility from a DXF \c DIMENSION entity.
 *
 * \return \c visibility, or \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_dimension_get_visibility
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (dimension->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_visibility
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c color from a DXF \c DIMENSION entity.
 *
 * \return \c color, or \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_dimension_get_color
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->color);
}


/*!
 * \brief Set the color for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_color
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c DIMENSION entity.
 *
 * \return \c paperspace flag value, or \c EXIT_FAILURE when an error
 * occurred.
 */
int16_t
dxf_dimension_get_paperspace
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (dimension->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_paperspace
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c DIMENSION
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_dimension_get_graphics_data_size
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (dimension->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_graphics_data_size
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c DIMENSION entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_dimension_get_shadow_mode
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (dimension->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_shadow_mode
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF 
 * \c DIMENSION entity.
 *
 * \return pointer to the \c binary_graphics_data, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_dimension_get_binary_graphics_data
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) dimension->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_binary_graphics_data
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c DIMENSION entity.
 *
 * \return pointer to the \c dictionary_owner_soft, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_dimension_get_dictionary_owner_soft
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_dictionary_owner_soft
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c DIMENSION entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_dimension_get_object_owner_soft
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c DIMENSION entity.
 */
DxfDimension *
dxf_dimension_set_object_owner_soft
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_dimension_get_material
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c DIMENSION
 * entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_material
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c DIMENSION entity.
 *
 * \return pointer to the \c dictionary_owner_hard, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_dimension_get_dictionary_owner_hard
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_dictionary_owner_hard
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c lineweight from a DXF \c DIMENSION entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_dimension_get_lineweight
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_lineweight
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_dimension_get_plot_style_name
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_plot_style_name
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c color_value from a DXF \c DIMENSION entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_dimension_get_color_value
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_color_value
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c color_name from a DXF \c DIMENSION entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_dimension_get_color_name
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_color_name
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c transparency from a DXF \c DIMENSION entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_dimension_get_transparency
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_transparency
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c dim_text from a DXF \c DIMENSION entity.
 *
 * \return \c dim_text when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_dimension_get_dim_text
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dim_text ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->dim_text));
}


/*!
 * \brief Set the \c dim_text for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_dim_text
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dim_text
                /*!< a string containing the \c dim_text for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dim_text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->dim_text = strdup (dim_text);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c dimblock_name from a DXF \c DIMENSION entity.
 *
 * \return \c dimblock_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_dimension_get_dimblock_name
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dimblock_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->dimblock_name));
}


/*!
 * \brief Set the \c dimblock_name for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_dimblock_name
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dimblock_name
                /*!< a string containing the \c dimblock_name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimblock_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->dimblock_name = strdup (dimblock_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c dimstyle_name from a DXF \c DIMENSION entity.
 *
 * \return \c dimstyle_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_dimension_get_dimstyle_name
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dimstyle_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimension->dimstyle_name));
}


/*!
 * \brief Set the \c dimstyle_name for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_dimstyle_name
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dimstyle_name
                /*!< a string containing the \c dimstyle_name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->dimblock_name = strdup (dimstyle_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point \c p0 for all dimension types of a
 * DXF \c DIMENSION entity.
 *
 * \return the definition point \c p0, or \c NULL when an error
 * occurred.
 */
DxfPoint *
dxf_dimension_get_p0
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p0);
}


/*!
 * \brief Set the definition point \c p0 for all dimension types of a
 * DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_p0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->p0 = (DxfPoint *) p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the X-value \c x0 of the definition point for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return the X-value \c x0 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_x0
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p0 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p0->x0);
}


/*!
 * \brief Set the X-value \c x0 of the definition point for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_x0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double x0
                /*!< the X-value \c x0 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p0 = dxf_point_init (dimension->p0);
                if (dimension->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Y-value \c y0 of the definition point for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return the Y-value \c y0 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_y0
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p0 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p0->y0);
}


/*!
 * \brief Set the Y-value \c y0 of the definition point for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_y0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double y0
                /*!< the Y-value \c y0 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p0 = dxf_point_init (dimension->p0);
                if (dimension->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Z-value \c z0 of the definition point for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return the Z-value \c z0 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_z0
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p0 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p0->z0);
}


/*!
 * \brief Set the Z-value \c z0 of the definition point for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_z0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double z0
                /*!< the Z-value \c z0 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p0 = dxf_point_init (dimension->p0);
                if (dimension->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the middle point \c p1 of the dimension text for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return the definition point \c p1, or \c NULL when an error
 * occurred.
 */
DxfPoint *
dxf_dimension_get_p1
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p1);
}


/*!
 * \brief Set the middle point \c p1 of the dimension text for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_p1
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->p1 = (DxfPoint *) p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the X-value \c x1 of the middle point of the dimension
 * text for all dimension types of a DXF \c DIMENSION entity.
 *
 * \return the X-value \c x1 of the middle point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_x1
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p1->x0);
}


/*!
 * \brief Set the X-value \c x1 of the middle point for all dimension
 * types of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_x1
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double x1
                /*!< the X-value \c x1 of the middle point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p1 = dxf_point_init (dimension->p1);
                if (dimension->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Y-value \c y1 of the middle point of the dimension
 * text for all dimension types of a DXF \c DIMENSION entity.
 *
 * \return the Y-value \c y1 of the middle point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_y1
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p1->y0);
}


/*!
 * \brief Set the Y-value \c y1 of the middle point for all
 * dimension types of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_y1
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double y1
                /*!< the Y-value \c y1 of the middle point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p1 = dxf_point_init (dimension->p1);
                if (dimension->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Z-value \c z1 of the middle point of the
 * dimension text for all dimension types of a DXF \c DIMENSION
 * entity.
 *
 * \return the Z-value \c z1 of the middle point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_z1
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p1->z0);
}


/*!
 * \brief Set the Z-value \c z1 of the middle point for all dimension
 * types of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_z1
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double z1
                /*!< the Z-coordinate value \c z1 of the middle point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p1 = dxf_point_init (dimension->p1);
                if (dimension->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point \c p2 for linear and angular
 * dimensions of a DXF \c DIMENSION entity.
 *
 * \return the definition point \c p2, or \c NULL when an error
 * occurred.
 */
DxfPoint *
dxf_dimension_get_p2
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p2);
}


/*!
 * \brief Set the definition point \c p2 for linear and angular
 * dimensions of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_p2
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *p2
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->p2 = (DxfPoint *) p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the X-value \c x2 of the definition point for linear and
 * angular dimensions of a DXF \c DIMENSION entity.
 *
 * \return the X-value \c x2 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_x2
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p2 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p2->x0);
}


/*!
 * \brief Set the X-value \c x2 of the definition point for linear and
 * angular dimensions of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_x2
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double x2
                /*!< the X-value \c x2 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p2 = dxf_point_init (dimension->p2);
                if (dimension->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Y-value \c y2 of the definition point for linear and
 * angular dimensions of a DXF \c DIMENSION entity.
 *
 * \return the Y-value \c y2 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_y2
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p2 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p2->y0);
}


/*!
 * \brief Set the Y-value \c y2 of the definition point for linear and
 * angular dimensions of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_y2
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double y2
                /*!< the Y-coordinate value \c y2 of the definition
                 * point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p2 = dxf_point_init (dimension->p2);
                if (dimension->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Z-value \c z2 of the definition point for linear and
 * angular dimensions of a DXF \c DIMENSION entity.
 *
 * \return the Z-value \c z2 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_z2
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p2 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p2->z0);
}


/*!
 * \brief Set the Z-value \c z2 of the definition point for linear and
 * angular dimensions of a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_z2
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double z2
                /*!< the Z-value \c z2 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p2 = dxf_point_init (dimension->p2);
                if (dimension->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point \c p3 for linear and angular
 * dimensions for a DXF \c DIMENSION entity.
 *
 * \return the definition point \c p3, or \c NULL when an error
 * occurred.
 */
DxfPoint *
dxf_dimension_get_p3
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p3);
}


/*!
 * \brief Set the definition point \c p3 for linear and angular
 * dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_p3
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *p3
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->p3 = (DxfPoint *) p3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the X-value \c x3 of the definition point for a linear
 * and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the X-value \c x3 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_x3
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p3 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p3->x0);
}


/*!
 * \brief Set the X-value \c x3 of the definition point for linear and
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_x3
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double x3
                /*!< the X-coordinate value \c x3 of the definition
                 * point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p3 = dxf_point_init (dimension->p3);
                if (dimension->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p3->x0 = x3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Y-value \c y3 of the definition point for a linear
 * and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the Y-value \c y3 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_y3
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p3 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p3->y0);
}


/*!
 * \brief Set the Y-value \c y3 of the definition point for linear and
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_y3
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double y3
                /*!< the Y-coordinate value \c y3 of the definition
                 * point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p3 = dxf_point_init (dimension->p3);
                if (dimension->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p3->y0 = y3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Z-value \c z3 of the definition point for a linear
 * and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the Z-value \c z3 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_z3
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p3 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p3->z0);
}


/*!
 * \brief Set the Z-value \c z3 of the definition point for linear and
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_z3
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double z3
                /*!< the Z-coordinate value \c z3 of the definition
                 * point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p3 = dxf_point_init (dimension->p3);
                if (dimension->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p3->z0 = z3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point \c p4 for linear and angular
 * dimensions for a DXF \c DIMENSION entity.
 *
 * \return the definition point \c p4, or \c NULL when an error
 * occurred.
 */
DxfPoint *
dxf_dimension_get_p4
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p4);
}


/*!
 * \brief Set the definition point \c p4 for linear and angular
 * dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_p4
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *p4
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->p4 = (DxfPoint *) p4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the X-value \c x4 of the definition point for a linear
 * and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the X-value \c x4 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_x4
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p4 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p4->x0);
}


/*!
 * \brief Set the X-value \c x4 of the definition point for linear and
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_x4
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double x4
                /*!< the X-value \c x4 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p4 = dxf_point_init (dimension->p4);
                if (dimension->p4 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p4->x0 = x4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Y-value \c y4 of the definition point for a linear
 * and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the Y-value \c y4 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_y4
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p4 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p4->y0);
}


/*!
 * \brief Set the Y-value \c y4 of the definition point for linear and
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_y4
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double y4
                /*!< the Y-value \c y4 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p4 = dxf_point_init (dimension->p4);
                if (dimension->p4 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p4->y0 = y4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Z-value \c z4 of the definition point for a linear
 * and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the Z-value \c z4 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_z4
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p4 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p4->z0);
}


/*!
 * \brief Set the Z-value \c z4 of the definition point for linear and
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_z4
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double z4
                /*!< the Z-value \c z4 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p4 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p4 = dxf_point_init (dimension->p4);
                if (dimension->p4 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p4->z0 = z4;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point \c p5 for diameter, radius, and
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the definition point \c p5, or \c NULL when an error
 * occurred.
 */
DxfPoint *
dxf_dimension_get_p5
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p5);
}


/*!
 * \brief Set the definition point \c p5 for diameter, radius, and
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_p5
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *p5
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p5 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->p5 = (DxfPoint *) p5;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the X-value \c x5 of the definition point for diameter,
 * radius, and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the X-value \c x5 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_x5
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p5 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p5->x0);
}


/*!
 * \brief Set the X-value \c x5 of the definition point for diameter,
 * radius, and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_x5
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double x5
                /*!< the X-value \c x5 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p5 = dxf_point_init (dimension->p5);
                if (dimension->p5 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p5->x0 = x5;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Y-value \c y5 of the definition point for diameter,
 * radius, and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the Y-value \c y5 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_y5
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p5 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p5->y0);
}


/*!
 * \brief Set the Y-value \c y5 of the definition point for diameter,
 * radius, and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_y5
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double y5
                /*!< the Y-value \c y5 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p5 = dxf_point_init (dimension->p5);
                if (dimension->p5 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p5->y0 = y5;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Z-value \c z5 of the definition point for diameter,
 * radius, and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the Z-value \c z5 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_z5
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p5 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p5->z0);
}


/*!
 * \brief Set the Z-value \c z5 of the definition point for diameter,
 * radius, and angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_z5
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double z5
                /*!< the Z-value \c z5 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p5 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p5 = dxf_point_init (dimension->p5);
                if (dimension->p5 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p5->z0 = z5;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point \c p6 defining the dimension arc for
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the definition point \c p6, or \c NULL when an error
 * occurred.
 */
DxfPoint *
dxf_dimension_get_p6
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p6 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p6);
}


/*!
 * \brief Set the definition point \c p6 defining the dimension arc for
 * angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_p6
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *p6
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p6 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->p6 = (DxfPoint *) p6;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the X-value \c x6 of the definition point defining the
 * dimension arc for angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the X-value \c x6 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_x6
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p6 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p6->x0);
}


/*!
 * \brief Set the X-value \c x6 of the point defining the dimension arc
 * for angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_x6
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double x6
                /*!< the X-value \c x6 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p6 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p6 = dxf_point_init (dimension->p6);
                if (dimension->p6 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p6->x0 = x6;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Y-value \c y6 of the definition point defining the
 * dimension arc for angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the Y-value \c y6 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_y6
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p6 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p6->y0);
}


/*!
 * \brief Set the Y-value \c y6 of the point defining the dimension arc
 * for angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_y6
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double y6
                /*!< the Y-value \c y6 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p6 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p6 = dxf_point_init (dimension->p6);
                if (dimension->p6 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p6->y0 = y6;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Z-value \c z6 of the definition point defining the
 * dimension arc for angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return the Z-value \c z6 of the definition point, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_dimension_get_z6
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->p6 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->p6->z0);
}


/*!
 * \brief Set the Z-value \c z6 of the point defining the dimension arc
 * for angular dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_z6
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double z6
                /*!< the Z-value \c z6 of the definition point. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->p6 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                dimension->p6 = dxf_point_init (dimension->p6);
                if (dimension->p6 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        dimension->p6->z0 = z6;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c leader_length from a DXF \c DIMENSION entity.
 *
 * \return \c leader_length, or \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_leader_length
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->leader_length);
}


/*!
 * \brief Set the \c leader_length for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_leader_length
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double leader_length
                /*!< the leader length to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->leader_length = leader_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c text_line_spacing factor from a DXF \c DIMENSION
 * entity.
 *
 * \return \c text_line_spacing factor, or \c EXIT_FAILURE when an error
 * occurred.
 */
double
dxf_dimension_get_text_line_spacing_factor
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->text_line_spacing_factor);
}


/*!
 * \brief Set the \c text_line_spacing factor for a DXF \c DIMENSION
 * entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_text_line_spacing_factor
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double text_line_spacing_factor
                /*!< the text line spacing factor to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->text_line_spacing_factor = text_line_spacing_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c actual_measurement from a DXF \c DIMENSION entity.
 *
 * \return \c actual_measurement, or \c EXIT_FAILURE when an error
 * occurred.
 */
double
dxf_dimension_get_actual_measurement
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->actual_measurement);
}


/*!
 * \brief Set the \c actual_measurement for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_actual_measurement
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double actual_measurement
                /*!< the actual measurement to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->actual_measurement = actual_measurement;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c angle of rotated, horizontal, or vertical linear
 * dimensions from a DXF \c DIMENSION entity.
 *
 * \return \c angle, or \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_angle
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->angle);
}


/*!
 * \brief Set the \c angle of rotated, horizontal, or vertical linear
 * dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_angle
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double angle
                /*!< the angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->angle = angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the horizontal direction \c hor_dir from a DXF
 * \c DIMENSION entity.
 *
 * \return horizontal direction \c hor_dir, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_dimension_get_hor_dir
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->hor_dir);
}


/*!
 * \brief Set the horizontal direction \c hor_dir for a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_hor_dir
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double hor_dir
                /*!< the horizontal direction to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->hor_dir = hor_dir;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the oblique angle \c obl_angle from a DXF \c DIMENSION
 * entity.
 *
 * \return oblique angle \c obl_angle, or \c EXIT_FAILURE when an error
 * occurred.
 */
double
dxf_dimension_get_obl_angle
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->obl_angle);
}


/*!
 * \brief Set the oblique angle \c obl_angle for a DXF \c DIMENSION
 * entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_obl_angle
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double obl_angle
                /*!< the oblique angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->obl_angle = obl_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c text_angle from a DXF \c DIMENSION entity.
 *
 * \return \c text_angle, or \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_text_angle
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->text_angle);
}


/*!
 * \brief Set the \c text_angle for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_text_angle
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double text_angle
                /*!< the text angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->text_angle = text_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the value of the \c flag of a DXF \c DIMENSION.
 *
 * \return The value of the \c flag, or \c DXF_ERROR when an error
 * occurred.
 */
int16_t
dxf_dimension_get_flag
(
        DxfDimension *dimension
                /*!< Pointer to the DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dimension == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
              return (DXF_ERROR);
        }
        if (dimension->flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->flag);
}


/*!
 * \brief Set the \c flag for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_flag
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t flag
                /*!< the flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        dimension->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c attachment_point of a DXF \c DIMENSION.
 *
 * \return The \c attachment_point, or \c DXF_ERROR when an error occurred.
 */
int16_t
dxf_dimension_get_attachment_point
(
        DxfDimension *dimension
                /*!< Pointer to the DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dimension == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
              return (DXF_ERROR);
        }
        if (dimension->attachment_point < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (dimension->attachment_point > 9)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->attachment_point);
}


/*!
 * \brief Set the \c attachment_point for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_attachment_point
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t attachment_point
                /*!< the attachment point to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attachment_point < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (attachment_point > 9)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        dimension->attachment_point = attachment_point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c text_line_spacing of a DXF \c DIMENSION.
 *
 * \return The \c text_line_spacing, or \c DXF_ERROR when an error occurred.
 */
int16_t
dxf_dimension_get_text_line_spacing
(
        DxfDimension *dimension
                /*!< Pointer to the DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dimension == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
              return (DXF_ERROR);
        }
        if (dimension->text_line_spacing < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (dimension->text_line_spacing > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->text_line_spacing);
}


/*!
 * \brief Set the text line spacing for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_text_line_spacing
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t text_line_spacing
                /*!< the text line spacing to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_line_spacing < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (text_line_spacing > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        dimension->text_line_spacing = text_line_spacing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the X-value \c extr_x0 of the extrusion vector of a DXF
 * \c DIMENSION entity.
 *
 * \return the X-value \c extr_x0 of the extrusion vector, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_extr_x0
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->extr_x0);
}


/*!
 * \brief Set the X-value \c extr_x0 of the extrusion vector of a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_extr_x0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double extr_x0
                /*!< the X-value \c extr_x0 of the extrusion vector. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Y-value \c extr_y0 of the extrusion vector of a DXF
 * \c DIMENSION entity.
 *
 * \return the Y-value \c extr_y0 of the extrusion vector, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_extr_y0
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->extr_y0);
}


/*!
 * \brief Set the Y-value \c extr_y0 of the extrusion vector of a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_extr_y0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double extr_y0
                /*!< the Y-value \c extr_y0 of the extrusion vector. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the Z-value \c extr_z0 of the extrusion vector of a DXF
 * \c DIMENSION entity.
 *
 * \return the Z-value \c extr_z0 of the extrusion vector, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_dimension_get_extr_z0
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->extr_z0);
}


/*!
 * \brief Set the Z-value \c extr_z0 of the extrusion vector of a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_extr_z0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double extr_z0
                /*!< the Z-value \c extr_z0 of the extrusion vector. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c DIMENSION entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates, or
 * \c NULL when an error occurred.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_dimension_get_extrusion_vector_as_point
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
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
        point->x0 = dimension->extr_x0;
        point->y0 = dimension->extr_y0;
        point->z0 = dimension->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector values for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_extrusion_vector
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
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
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->extr_x0 = extr_x0;
        dimension->extr_y0 = extr_y0;
        dimension->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c version_number from a DXF \c DIMENSION entity.
 *
 * \return \c version_number when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_dimension_get_version_number
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->version_number != 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->version_number);
}


/*!
 * \brief Set the \c version_number for a DXF \c DIMENSION entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_version_number
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t version_number
                /*!< the version_number to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (version_number != 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
        dimension->version_number = version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the pointer to the next \c DIMENSION entity from a DXF 
 * \c DIMENSION entity.
 *
 * \return pointer to the next \c DIMENSION entity, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDimension *
dxf_dimension_get_next
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDimension *) dimension->next);
}


/*!
 * \brief Set the pointer to the next \c DIMENSION for a DXF \c DIMENSION
 * entity.
 *
 * \return a pointer to \c dimension when successful, or \c NULL when an
 * error occurred.
 */
DxfDimension *
dxf_dimension_set_next
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfDimension *next
                /*!< a pointer to the next \c DIMENSION for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->next = (struct DxfDimension *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the pointer to the last \c DIMENSION entity from a linked
 * list of DXF \c DIMENSION entities.
 *
 * \return pointer to the last \c DIMENSION entity, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDimension *
dxf_dimension_get_last
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfDimension *) dimension);
        }
        DxfDimension *iter = (DxfDimension *) dimension->next;
        while (iter->next != NULL)
        {
                iter = (DxfDimension *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDimension *) iter);
}


/* EOF */
