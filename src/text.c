/*!
 * \file text.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2017, 2018, 2019,
 * 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief DXF text entity (\c TEXT).
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


#include "text.h"


/*!
 * \brief Allocate memory for a \c DxfText.
 *
 * Fill the memory contents with zeros.
 */
DxfText *
dxf_text_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfText *text = NULL;
        size_t size;

        size = sizeof (DxfText);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((text = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfText struct.\n")),
                  __FUNCTION__);
                text = NULL;
        }
        else
        {
                memset (text, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c TEXT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfText *
dxf_text_init
(
        DxfText *text
                /*!< a pointer to the DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                text = dxf_text_new ();
        }
        if (text == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfText struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        text->id_code = 0;
        text->linetype = strdup (DXF_DEFAULT_LINETYPE);
        text->layer = strdup (DXF_DEFAULT_LAYER);
        text->elevation = 0.0;
        text->thickness = 0.0;
        text->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        text->visibility = DXF_DEFAULT_VISIBILITY;
        text->color = DXF_COLOR_BYLAYER;
        text->paperspace = DXF_MODELSPACE;
        text->graphics_data_size = 0;
        text->shadow_mode = 0;
        text->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        text->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) text->binary_graphics_data);
        text->dictionary_owner_soft = strdup ("");
        text->material = strdup ("");
        text->dictionary_owner_hard = strdup ("");
        text->lineweight = 0;
        text->plot_style_name = strdup ("");
        text->color_value = 0;
        text->color_name = strdup ("");
        text->transparency = 0;
        text->text_value = strdup ("");
        text->text_style = strdup ("");
        text->p0 = (DxfPoint *) dxf_point_new ();
        text->p0 = dxf_point_init ((DxfPoint *) text->p0);
        text->p0->x0 = 0.0;
        text->p0->y0 = 0.0;
        text->p0->z0 = 0.0;
        text->p1 = (DxfPoint *) dxf_point_new ();
        text->p1 = dxf_point_init ((DxfPoint *) text->p1);
        text->p1->x0 = 0.0;
        text->p1->y0 = 0.0;
        text->p1->z0 = 0.0;
        text->height = 0.0;
        text->rel_x_scale = 0.0;
        text->rot_angle = 0.0;
        text->obl_angle = 0.0;
        text->text_flags = 0;
        text->hor_align = 0;
        text->vert_align = 0;
        text->extr_x0 = 0.0;
        text->extr_y0 = 0.0;
        text->extr_z0 = 0.0;
        text->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Read data from a DXF file into a \c TEXT entity.
 *
 * The last line read from file contained the string "TEXT". \n
 * Now follows some data for the \c TEXT, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c text. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfText *
dxf_text_read
(
        DxfFile *fp,
                /*!< filepointer to the input file (or device). */
        DxfText *text
                /*!< a pointer to the DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("TEXT");
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
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                text = dxf_text_init (text);
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
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a text value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->text_value);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &text->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the first alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the first alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the first alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the second alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the second alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the second alignment point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->p1->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (text->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->rel_x_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * oblique angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->obl_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &text->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &text->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &text->paperspace);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &text->text_flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal alignment flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &text->hor_align);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * vertical alignment flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &text->vert_align);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &text->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbText") != 0)))
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
                        fscanf (fp->fp, "%d\n", &text->graphics_data_size);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->extr_z0);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &text->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) text->binary_graphics_data->next);
                        text->binary_graphics_data = (DxfBinaryGraphicsData *) text->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &text->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &text->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, text->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &text->transparency);
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
                          (_("Warning: in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (text->text_value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () text value string is empty for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, text->id_code);
                dxf_entity_skip (dxf_entity_name);
                return (NULL);
        }
        if (strcmp (text->linetype, "") == 0)
        {
                text->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (text->layer, "") == 0)
        {
                text->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Write DXF output to fp for a text entity.
 */
int
dxf_text_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfText *text
                /*!< a pointer to the DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("TEXT");

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
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (text->text_value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () text value string is empty for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, text->id_code);
                dxf_entity_skip (dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (text->text_style, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () text style string is empty for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, text->id_code);
                text->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);        }
        if (strcmp (text->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, text->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                text->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (text->height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () height has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, text->id_code);
        }
        if (text->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, text->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (text->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", text->id_code);
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
        if ((strcmp (text->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", text->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (text->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", text->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (text->paperspace == 1)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", text->layer);
        if (strcmp (text->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", text->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (text->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", text->material);
        }
        if (text->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", text->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", text->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (text->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", text->elevation);
        }
        if (text->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", text->linetype_scale);
        }
        if (text->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", text->visibility);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
          && (text->graphics_data_size > 0))
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", text->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", text->graphics_data_size);
#endif
                if (text->binary_graphics_data != NULL)
                {
                        DxfBinaryGraphicsData *iter;
                        iter = text->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", dxf_binary_graphics_data_get_data_line (iter));
                                iter = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_get_next (iter);
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", text->color_value);
                fprintf (fp->fp, "430\n%s\n", text->color_name);
                fprintf (fp->fp, "440\n%ld\n", text->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", text->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", text->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        if (text->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", text->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", text->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", text->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", text->p0->z0);
        fprintf (fp->fp, " 40\n%f\n", text->height);
        fprintf (fp->fp, "  1\n%s\n", text->text_value);
        if (text->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", text->rot_angle);
        }
        if (text->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", text->rel_x_scale);
        }
        if (text->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", text->obl_angle);
        }
        if (strcmp (text->text_style, DXF_DEFAULT_TEXTSTYLE) != 0)
        {
                fprintf (fp->fp, "  7\n%s\n", text->text_style);
        }
        if (text->text_flags != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", text->text_flags);
        }
        if (text->hor_align != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", text->hor_align);
        }
        if ((text->hor_align != 0) || (text->vert_align != 0))
        {
                if ((text->p0->x0 == text->p1->x0)
                  && (text->p0->y0 == text->p1->y0)
                  && (text->p0->z0 == text->p1->z0))
                {
                        fprintf (stderr,
                          (_("Warning in %s () insertion point and alignment point are identical for the %s entity with id-code: %x\n")),
                          __FUNCTION__, dxf_entity_name, text->id_code);
                        fprintf (stderr,
                          (_("\tdefault justification applied to %s entity\n")),
                          dxf_entity_name);
                        text->hor_align = 0;
                        text->vert_align = 0;
                }
                else
                {
                        fprintf (fp->fp, " 11\n%f\n", text->p1->x0);
                        fprintf (fp->fp, " 21\n%f\n", text->p1->y0);
                        fprintf (fp->fp, " 31\n%f\n", text->p1->z0);
                }
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (text->extr_x0 != 0.0)
                && (text->extr_y0 != 0.0)
                && (text->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", text->extr_x0);
                fprintf (fp->fp, "220\n%f\n", text->extr_y0);
                fprintf (fp->fp, "230\n%f\n", text->extr_z0);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        if (text->vert_align != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", text->vert_align);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c TEXT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_text_free
(
        DxfText *text
                /*!< a pointer to the memory occupied by the DXF \c TEXT
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (text->linetype);
        free (text->layer);
        dxf_binary_graphics_data_free_list (text->binary_graphics_data);
        free (text->dictionary_owner_soft);
        free (text->material);
        free (text->dictionary_owner_hard);
        free (text->plot_style_name);
        free (text->color_name);
        free (text->text_value);
        free (text->text_style);
        dxf_point_free (text->p0);
        dxf_point_free (text->p1);
        free (text);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c TEXT entities and all their data fields.
 */
void
dxf_text_free_list
(
        DxfText *texts
                /*!< a pointer to the single linked list of DXF \c TEXT
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (texts == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (texts != NULL)
        {
                DxfText *iter = (DxfText *) texts->next;
                dxf_text_free (texts);
                texts = (DxfText *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c TEXT entity.
 *
 * \return \c id_code.
 */
int
dxf_text_get_id_code
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_id_code
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
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
        if (text == NULL)
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
        text->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c linetype from a DXF \c TEXT entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_text_get_linetype
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_linetype
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c layer from a DXF \c TEXT entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_text_get_layer
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_layer
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c elevation from a DXF \c TEXT entity.
 *
 * \return \c elevation.
 */
double
dxf_text_get_elevation
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_elevation
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c thickness from a DXF \c TEXT entity.
 *
 * \return \c thickness.
 */
double
dxf_text_get_thickness
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_thickness
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c TEXT entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_text_get_linetype_scale
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_linetype_scale
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c visibility from a DXF \c TEXT entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_text_get_visibility
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (text->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_visibility
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c color from a DXF \c TEXT entity.
 *
 * \return \c color.
 */
int
dxf_text_get_color
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->color);
}


/*!
 * \brief Set the \c color for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_color
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c TEXT entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_text_get_paperspace
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (text->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_paperspace
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c TEXT entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_text_get_graphics_data_size
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (text->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_graphics_data_size
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c TEXT entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_text_get_shadow_mode
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (text->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_shadow_mode
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c TEXT entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_text_get_binary_graphics_data
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) text->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c TEXT entity.
 */
DxfText *
dxf_text_set_binary_graphics_data
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c TEXT entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_text_get_dictionary_owner_soft
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c TEXT entity.
 */
DxfText *
dxf_text_set_dictionary_owner_soft
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c TEXT entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_text_get_material
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_material
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c TEXT entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_text_get_dictionary_owner_hard
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c TEXT entity.
 */
DxfText *
dxf_text_set_dictionary_owner_hard
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c lineweight from a DXF \c TEXT entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_text_get_lineweight
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_lineweight
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c TEXT entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_text_get_plot_style_name
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_plot_style_name
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c color_value from a DXF \c TEXT entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_text_get_color_value
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_color_value
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c color_name from a DXF \c TEXT entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_text_get_color_name
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_color_name
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c transparency from a DXF \c TEXT entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_text_get_transparency
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_transparency
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c text_value from a DXF \c TEXT entity.
 *
 * \return \c text_value when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_text_get_text_value
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->text_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->text_value));
}


/*!
 * \brief Set the \c text_value for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_text_value
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *text_value
                /*!< a string containing the \c text_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->text_value = strdup (text_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c text_style from a DXF \c TEXT entity.
 *
 * \return \c text_style when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_text_get_text_style
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->text_style ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (text->text_style));
}


/*!
 * \brief Set the \c text_style for a DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_text_style
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        char *text_style
                /*!< a string containing the \c text_style for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_style == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->text_style = strdup (text_style);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the alignment point \c p0 of a DXF \c TEXT entity.
 *
 * \return the alignment point \c p0.
 */
DxfPoint *
dxf_text_get_p0
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->p0);
}


/*!
 * \brief Set the alignment point \c p0 of a DXF \c TEXT entity.
 *
 * \return a pointer to a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_p0
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the X-value of the alignment point \c x0 of a DXF \c TEXT
 * entity.
 *
 * \return the X-value of the alignment point \c x0.
 */
double
dxf_text_get_x0
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->p0->x0);
}


/*!
 * \brief Set the X-value of the alignment point \c x0 of a DXF \c TEXT
 * entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_x0
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double x0
                /*!< the X-value of the alignment point \c x0 of a DXF
                 * \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the Y-value of the alignment point \c y0 of a DXF \c TEXT
 * entity.
 *
 * \return the Y-value of the alignment point \c y0.
 */
double
dxf_text_get_y0
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->p0->y0);
}


/*!
 * \brief Set the Y-value of the alignment point \c y0 of a DXF \c TEXT
 * entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_y0
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double y0
                /*!< the Y-value of the alignment point \c y0 of a DXF
                 * \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the Z-value of the alignment point \c z0 of a DXF \c TEXT
 * entity.
 *
 * \return the Z-value of the alignment point \c z0.
 */
double
dxf_text_get_z0
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->p0->z0);
}


/*!
 * \brief Set the Z-value of the alignment point \c z0 of a DXF \c TEXT
 * entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_z0
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double z0
                /*!< the Z-value of the alignment point \c z0 of a DXF
                 * \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the second alignment point \c p1 of a DXF \c TEXT entity.
 *
 * \return the second alignment point \c p1.
 */
DxfPoint *
dxf_text_get_p1
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->p1);
}


/*!
 * \brief Set the second alignment point \c p1 of a DXF \c TEXT entity.
 *
 * \return a pointer to a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_p1
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the X-value of the second alignment point \c x1 of a
 * DXF \c TEXT entity.
 *
 * \return the X-value of the second alignment point \c x1.
 */
double
dxf_text_get_x1
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->p1->x0);
}


/*!
 * \brief Set the X-value of the second alignment point \c x1 of a
 * DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_x1
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double x1
                /*!< the X-value of the second alignment point \c x1 of
                 * a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the Y-value of the second alignment point \c y1 of a
 * DXF \c TEXT entity.
 *
 * \return the Y-value of the second alignment point \c y1.
 */
double
dxf_text_get_y1
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->p1->y0);
}


/*!
 * \brief Set the Y-value of the second alignment point \c y1 of a
 * DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_y1
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double y1
                /*!< the Y-value of the second alignment point \c y1 of
                 * a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the Z-value of the second alignment point \c z1 of a
 * DXF \c TEXT entity.
 *
 * \return the Z-value of the second alignment point \c z1.
 */
double
dxf_text_get_z1
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->p1->z0);
}


/*!
 * \brief Set the Z-value of the second alignment point \c z1 of a
 * DXF \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_z1
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double z1
                /*!< the Z-value of the second alignment point \c z1 of
                 * a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c height from a DXF \c TEXT entity.
 *
 * \return \c height.
 */
double
dxf_text_get_height
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (text->height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->height);
}


/*!
 * \brief Set the \c height for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_height
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double height
                /*!< the \c height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        text->height = height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c rel_x_scale from a DXF \c TEXT entity.
 *
 * \return \c rel_x_scale.
 */
double
dxf_text_get_rel_x_scale
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->rel_x_scale);
}


/*!
 * \brief Set the \c rel_x_scale for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_rel_x_scale
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double rel_x_scale
                /*!< the \c rel_x_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        text->rel_x_scale = rel_x_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c rot_angle from a DXF \c TEXT entity.
 *
 * \return \c rot_angle.
 */
double
dxf_text_get_rot_angle
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->rot_angle < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->rot_angle);
}


/*!
 * \brief Set the \c rot_angle for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_rot_angle
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double rot_angle
                /*!< the \c rot_angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rot_angle < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        text->rot_angle = rot_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c obl_angle from a DXF \c TEXT entity.
 *
 * \return \c obl_angle.
 */
double
dxf_text_get_obl_angle
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->obl_angle < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->obl_angle);
}


/*!
 * \brief Set the \c obl_angle for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_obl_angle
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double obl_angle
                /*!< the \c obl_angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->obl_angle = obl_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c text_flags from a DXF \c TEXT entity.
 *
 * \return \c text_flags.
 */
int
dxf_text_get_text_flags
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->text_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (text->text_flags > 0x1111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->text_flags);
}


/*!
 * \brief Set the \c text_flags for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_text_flags
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int text_flags
                /*!< the \c text_flags to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (text_flags > 0x1111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        text->text_flags = text_flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c hor_align from a DXF \c TEXT entity.
 *
 * \return \c hor_align.
 */
int
dxf_text_get_hor_align
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->hor_align < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (text->hor_align > 5)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->hor_align);
}


/*!
 * \brief Set the \c hor_align for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_hor_align
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int hor_align
                /*!< the \c hor_align to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hor_align < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (hor_align > 5)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        text->hor_align = hor_align;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the \c vert_align from a DXF \c TEXT entity.
 *
 * \return \c vert_align.
 */
int
dxf_text_get_vert_align
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (text->vert_align < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (text->vert_align > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->vert_align);
}


/*!
 * \brief Set the \c vert_align for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_vert_align
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        int vert_align
                /*!< the \c vert_align to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vert_align < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (vert_align > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        text->vert_align = vert_align;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c TEXT entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_text_get_extrusion_vector_as_point
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (text == NULL)
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
        point->x0 = text->extr_x0;
        point->y0 = text->extr_y0;
        point->z0 = text->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c TEXT entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_text_get_extr_x0
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_extr_x0
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c TEXT entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_text_get_extr_y0
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_extr_y0
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c TEXT entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_text_get_extr_z0
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c TEXT entity.
 *
 * \return a pointer to \c text when successful, or \c NULL when an
 * error occurred.
 */
DxfText *
dxf_text_set_extr_z0
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c TEXT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF \c TEXT
 * entity.
 */
DxfText *
dxf_text_set_extrusion_vector_from_point
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->extr_x0 = (double) point->x0;
        text->extr_y0 = (double) point->y0;
        text->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Set the extrusion vector for a DXF \c TEXT entity.
 */
DxfText *
dxf_text_set_extrusion_vector
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
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
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        text->extr_x0 = extr_x0;
        text->extr_y0 = extr_y0;
        text->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the pointer to the next \c TEXT entity from a DXF
 * \c TEXT entity.
 *
 * \return pointer to the next \c TEXT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfText *
dxf_text_get_next
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfText *) text->next);
}


/*!
 * \brief Set the pointer to the next \c TEXT for a DXF \c TEXT
 * entity.
 */
DxfText *
dxf_text_set_next
(
        DxfText *text,
                /*!< a pointer to a DXF \c TEXT entity. */
        DxfText *next
                /*!< a pointer to the next \c TEXT for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
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
        text->next = (struct DxfText *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (text);
}


/*!
 * \brief Get the pointer to the last \c TEXT entity from a linked list
 * of DXF \c TEXT entities.
 *
 * \return pointer to the last \c TEXT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfText *
dxf_text_get_last
(
        DxfText *text
                /*!< a pointer to a DXF \c TEXT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfText *) text);
        }
        DxfText *iter = (DxfText *) text->next;
        while (iter->next != NULL)
        {
                iter = (DxfText *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfText *) iter);
}


/* EOF */
