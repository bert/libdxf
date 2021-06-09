/*!
 * \file attdef.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017,
 * 2018, 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF attribute definition entity (\c ATTDEF).
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


#include "attdef.h"


/*!
 * \brief Allocate memory for a \c DxfAttdef.
 *
 * Fill the memory contents with zeros.
 */
DxfAttdef *
dxf_attdef_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAttdef *attdef = NULL;
        size_t size;

        size = sizeof (DxfAttdef);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((attdef = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                attdef = NULL;
        }
        else
        {
                memset (attdef, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c ATTDEF entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfAttdef *
dxf_attdef_init
(
        DxfAttdef *attdef
                /*!< DXF attdef entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                attdef = dxf_attdef_new ();
        }
        if (attdef == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        attdef->id_code = 0;
        attdef->linetype = strdup (DXF_DEFAULT_LINETYPE);
        attdef->layer = strdup (DXF_DEFAULT_LAYER);
        attdef->elevation = 0.0;
        attdef->thickness = 0.0;
        attdef->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        attdef->visibility = DXF_DEFAULT_VISIBILITY;
        attdef->color = DXF_COLOR_BYLAYER;
        attdef->paperspace = DXF_MODELSPACE;
        attdef->graphics_data_size = 0;
        attdef->shadow_mode = 0;
        attdef->dictionary_owner_soft = strdup ("");
        attdef->object_owner_soft = strdup ("");
        attdef->material = strdup ("");
        attdef->dictionary_owner_hard = strdup ("");
        attdef->lineweight = 0.0;
        attdef->plot_style_name = strdup ("");
        attdef->color_value = 0;
        attdef->color_name = strdup ("");
        attdef->transparency = 0;
        attdef->default_value = strdup ("");
        attdef->tag_value = strdup ("");
        attdef->prompt_value = strdup ("");
        attdef->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        attdef->height = 0.0;
        attdef->rel_x_scale = 0.0;
        attdef->rot_angle = 0.0;
        attdef->obl_angle = 0.0;
        attdef->attr_flags = 0;
        attdef->text_flags = 0;
        attdef->hor_align = 0;
        attdef->field_length = 0;
        attdef->vert_align = 0;
        attdef->extr_x0 = 0.0;
        attdef->extr_y0 = 0.0;
        attdef->extr_z0 = 1.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        attdef->binary_graphics_data = NULL;
        attdef->p0 = NULL;
        attdef->p1 = NULL;
        attdef->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Read data from a DXF file into an \c ATTDEF entity.
 *
 * The last line read from file contained the string "ATTDEF". \n
 * Now follows some data for the \c ATTDEF, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_attdef. \n
 *
 * \return a pointer to \c attdef.
 */
DxfAttdef *
dxf_attdef_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAttdef *attdef
                /*!< DXF attdef entity. */
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
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                attdef = dxf_attdef_init (attdef);
                if (attdef == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (attdef->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                attdef->binary_graphics_data = dxf_binary_data_init (attdef->binary_graphics_data);
                if (attdef->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (attdef->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                attdef->p0 = dxf_point_init (attdef->p0);
                if (attdef->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (attdef->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                attdef->p1 = dxf_point_init (attdef->p1);
                if (attdef->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) attdef->binary_graphics_data;
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
                        /* Now follows a string containing the attribute
                         * default value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->default_value);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a tag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->tag_value);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a prompt
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->prompt_value);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &attdef->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->p1->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (attdef->elevation = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->rel_x_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->obl_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * attribute flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->attr_flags);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->text_flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->hor_align);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * field length value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->field_length);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the
                         * vertical alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->vert_align);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &attdef->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
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
                        && (strcmp (temp_string, "AcDbText") != 0)
                        && (strcmp (temp_string, "AcDbAttributeDefinition") != 0))
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
                        fscanf (fp->fp, "%" PRIi32 "\n", &attdef->graphics_data_size);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attdef->extr_z0);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->shadow_mode);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attdef->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &attdef->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, attdef->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &attdef->transparency);
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
        if (strcmp (attdef->linetype, "") == 0)
        {
                attdef->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (attdef->layer, "") == 0)
        {
                attdef->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Write DXF output to fp for a attribute definition entity.
 */
int
dxf_attdef_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfAttdef *attdef
                /*!< attribute definition entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ATTDEF");

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
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (attdef->tag_value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () default tag value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (attdef->text_style, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () text style string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\tdefault text style STANDARD applied to %s entity.\n")),
                  dxf_entity_name);
                attdef->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (attdef->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                attdef->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (attdef->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                attdef->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (attdef->height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () height has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\tdefault height of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                attdef->height = 1.0;
        }
        if (attdef->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attdef->id_code);
                fprintf (stderr,
                  (_("\tdefault relative X-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                attdef->rel_x_scale = 1.0;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (attdef->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", attdef->id_code);
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
        if ((strcmp (attdef->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", attdef->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (attdef->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", attdef->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (attdef->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", attdef->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (attdef->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", attdef->layer);
        if (strcmp (attdef->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", attdef->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (attdef->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", attdef->material);
        }
        if (attdef->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", attdef->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", attdef->lineweight);
        }
        if (attdef->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", attdef->thickness);
        }
        if (attdef->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", attdef->linetype_scale);
        }
        if (attdef->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", attdef->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", attdef->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", attdef->graphics_data_size);
#endif
                if (attdef->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) attdef->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", attdef->color_value);
                fprintf (fp->fp, "430\n%s\n", attdef->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", attdef->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", attdef->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", attdef->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        fprintf (fp->fp, " 10\n%f\n", attdef->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", attdef->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", attdef->p0->z0);
        fprintf (fp->fp, " 40\n%f\n", attdef->height);
        fprintf (fp->fp, "  1\n%s\n", attdef->default_value);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbAttributeDefinition\n");
        }
        fprintf (fp->fp, "  3\n%s\n", attdef->prompt_value);
        fprintf (fp->fp, "  2\n%s\n", attdef->tag_value);
        fprintf (fp->fp, " 70\n%hd\n", attdef->attr_flags);
        if (attdef->field_length != 0)
        {
                fprintf (fp->fp, " 73\n%hd\n", attdef->field_length);
        }
        if (attdef->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", attdef->rot_angle);
        }
        if (attdef->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", attdef->rel_x_scale);
        }
        if (attdef->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", attdef->obl_angle);
        }
        if (strcmp (attdef->text_style, "STANDARD") != 0)
        {
                fprintf (fp->fp, "  7\n%s\n", attdef->text_style);
        }
        if (attdef->text_flags != 0)
        {
                fprintf (fp->fp, " 71\n%hd\n", attdef->text_flags);
        }
        if (attdef->hor_align != 0)
        {
                fprintf (fp->fp, " 72\n%hd\n", attdef->hor_align);
        }
        if (attdef->vert_align != 0)
        {
                fprintf (fp->fp, " 74\n%hd\n", attdef->vert_align);
        }
        if ((attdef->hor_align != 0) || (attdef->vert_align != 0))
        {
                if ((attdef->p0->x0 == attdef->p1->x0)
                        && (attdef->p0->y0 == attdef->p1->y0)
                        && (attdef->p0->z0 == attdef->p1->z0))
                {
                        fprintf (stderr,
                          (_("Warning in %s () insertion point and alignment point are identical for the %s entity with id-code: %x.\n")),
                          __FUNCTION__, dxf_entity_name, attdef->id_code);
                        fprintf (stderr,
                          (_("\tdefault justification applied to %s entity.\n")),
                          dxf_entity_name);
                        attdef->hor_align = 0;
                        attdef->vert_align = 0;
                }
                else
                {
                        fprintf (fp->fp, " 11\n%f\n", attdef->p1->x0);
                        fprintf (fp->fp, " 21\n%f\n", attdef->p1->y0);
                        fprintf (fp->fp, " 31\n%f\n", attdef->p1->z0);
                }
        }
        if (fp->acad_version_number >= AutoCAD_12)
        {
                fprintf (fp->fp, "210\n%f\n", attdef->extr_x0);
                fprintf (fp->fp, "220\n%f\n", attdef->extr_y0);
                fprintf (fp->fp, "230\n%f\n", attdef->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocate memory for a DXF \c ATTDEF and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_attdef_free
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (attdef->linetype);
        free (attdef->layer);
        dxf_binary_data_free_list (attdef->binary_graphics_data);
        free (attdef->dictionary_owner_soft);
        free (attdef->object_owner_soft);
        free (attdef->material);
        free (attdef->dictionary_owner_hard);
        free (attdef->plot_style_name);
        free (attdef->color_name);
        free (attdef->default_value);
        free (attdef->tag_value);
        free (attdef->prompt_value);
        free (attdef->text_style);
        dxf_point_free_list (attdef->p0);
        dxf_point_free_list (attdef->p1);
        free (attdef);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c ATTDEF entities and all their data fields.
 */
void
dxf_attdef_free_list
(
        DxfAttdef *attdefs
                /*!< pointer to the single linked list of DXF \c ATTDEF
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (attdefs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (attdefs != NULL)
        {
                DxfAttdef *iter = (DxfAttdef *) attdefs->next;
                dxf_attdef_free (attdefs);
                attdefs = (DxfAttdef *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c ATTDEF entity.
 *
 * \return ID code.
 */
int
dxf_attdef_get_id_code
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_id_code
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
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
        if (attdef == NULL)
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
        attdef->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the linetype from a DXF \c ATTDEF entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_attdef_get_linetype
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_linetype
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the layer from a DXF \c ATTDEF entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_attdef_get_layer
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->layer));
}


/*!
 * \brief Set the layer for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_layer
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the elevation from a DXF \c ATTDEF entity.
 *
 * \return elevation.
 */
double
dxf_attdef_get_elevation
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_elevation
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the thickness from a DXF \c ATTDEF entity.
 *
 * \return thickness.
 */
double
dxf_attdef_get_thickness
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_thickness
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the linetype scale from a DXF \c ATTDEF entity.
 *
 * \return linetype scale.
 */
double
dxf_attdef_get_linetype_scale
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_linetype_scale
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the visibility from a DXF \c ATTDEF entity.
 *
 * \return visibility.
 */
int16_t
dxf_attdef_get_visibility
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (attdef->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_visibility
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the color from a DXF \c ATTDEF entity.
 *
 * \return color.
 */
int16_t
dxf_attdef_get_color
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->color);
}


/*!
 * \brief Set the color for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_color
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c ATTDEF entity.
 *
 * \return paperspace flag value.
 */
int16_t
dxf_attdef_get_paperspace
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (attdef->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_paperspace
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c ATTDEF
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_attdef_get_graphics_data_size
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (attdef->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c ATTDEF
 * entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_graphics_data_size
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c ATTDEF entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_attdef_get_shadow_mode
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (attdef->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_shadow_mode
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c ATTDEF entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_attdef_get_binary_graphics_data
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) attdef->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_binary_graphics_data
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c ATTDEF entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attdef_get_dictionary_owner_soft
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_dictionary_owner_soft
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c ATTDEF entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attdef_get_object_owner_soft
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_object_owner_soft
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_attdef_get_material
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_material
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c ATTDEF entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attdef_get_dictionary_owner_hard
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_dictionary_owner_hard
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the \c lineweight from a DXF \c ATTDEF entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_attdef_get_lineweight
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_lineweight
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_attdef_get_plot_style_name
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_plot_style_name
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the \c color_value from a DXF \c ATTDEF entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_attdef_get_color_value
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_color_value
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the \c color_name from a DXF \c ATTDEF entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_attdef_get_color_name
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_color_name
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the \c transparency from a DXF \c ATTDEF entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_attdef_get_transparency
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_transparency
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the default value from a DXF \c ATTDEF entity.
 *
 * \return default value.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attdef_get_default_value
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->default_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->default_value));
}


/*!
 * \brief Set the default value for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_default_value
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *default_value
                /*!< a string containing the default_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (default_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->default_value = strdup (default_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the tag value from a DXF \c ATTDEF entity.
 *
 * \return tag value.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attdef_get_tag_value
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->tag_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->tag_value));
}


/*!
 * \brief Set the tag value for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_tag_value
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *tag_value
                /*!< a string containing the tag_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tag_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->tag_value = strdup (tag_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the promp value from a DXF \c ATTDEF entity.
 *
 * \return prompt value.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attdef_get_prompt_value
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->prompt_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->prompt_value));
}


/*!
 * \brief Set the prompt value for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_prompt_value
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *prompt_value
                /*!< a string containing the prompt_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (prompt_value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->prompt_value = strdup (prompt_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the text style from a DXF \c ATTDEF entity.
 *
 * \return text style.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attdef_get_text_style
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->text_style ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attdef->text_style));
}


/*!
 * \brief Set the text style for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_text_style
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        char *text_style
                /*!< a string containing the text style for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->text_style = strdup (text_style);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the first alignment point \c p0 of a DXF \c ATTDEF entity.
 *
 * \return the first alignment point \c p0.
 */
DxfPoint *
dxf_attdef_get_p0
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->p0);
}


/*!
 * \brief Set the first alignment point \c p0 of a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, \c NULL when an error
 * occurred.
 */
DxfAttdef *
dxf_attdef_set_p0
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the X-value of the first alignment point \c x0 of a DXF
 * \c ATTDEF entity.
 *
 * \return the X-value of the first alignment point \c x0.
 */
double
dxf_attdef_get_x0
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->p0->x0);
}


/*!
 * \brief Set the X-value of the first alignment point \c x0 of a DXF
 * \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_x0
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double x0
                /*!< the X-value of the first alignment point \c x0 of a
                 * DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                attdef->p0 = dxf_point_init (attdef->p0);
                if (attdef->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        attdef->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the Y-value of the first alignment point \c y0 of a DXF
 * \c ATTDEF entity.
 *
 * \return the Y-value of the first alignment point \c y0.
 */
double
dxf_attdef_get_y0
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->p0->y0);
}


/*!
 * \brief Set the Y-value of the first alignment point \c y0 of a DXF
 * \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_y0
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double y0
                /*!< the Y-value of the first alignment point \c y0 of a
                 * DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                attdef->p0 = dxf_point_init (attdef->p0);
                if (attdef->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        attdef->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the Z-value of the first alignment point \c z0 of a DXF
 * \c ATTDEF entity.
 *
 * \return the Z-value of the first alignment point \c z0.
 */
double
dxf_attdef_get_z0
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->p0->z0);
}


/*!
 * \brief Set the Z-value of the first alignment point \c z0 of a DXF
 * \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_z0
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double z0
                /*!< the Z-value of the fisrt alignment point \c z0 of a
                 * DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                attdef->p0 = dxf_point_init (attdef->p0);
                if (attdef->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        attdef->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the second alignment point \c p1 of a DXF \c ATTDEF entity.
 *
 * \return the second alignment point \c p1.
 */
DxfPoint *
dxf_attdef_get_p1
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->p1);
}


/*!
 * \brief Set the second alignment point \c p1 of a DXF \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, \c NULL when an error
 * occurred.
 */
DxfAttdef *
dxf_attdef_set_p1
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the X-value of the second alignment point \c x1 of a DXF
 * \c ATTDEF entity.
 *
 * \return the X-value of the second alignment point \c x1.
 */
double
dxf_attdef_get_x1
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->p1->x0);
}


/*!
 * \brief Set the X-value of the second alignment point \c x1 of a DXF
 * \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_x1
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double x1
                /*!< the X-value of the second alignment point \c x0 of
                 * a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                attdef->p1 = dxf_point_init (attdef->p1);
                if (attdef->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        attdef->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the Y-value of the second alignment point \c y1 of a DXF
 * \c ATTDEF entity.
 *
 * \return the Y-value of the second alignment point \c y1.
 */
double
dxf_attdef_get_y1
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->p1->y0);
}


/*!
 * \brief Set the Y-value of the second alignment point \c y1 of a DXF
 * \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_y1
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double y1
                /*!< the Y-value of the second alignment point \c y1 of a DXF
                 * \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                attdef->p1 = dxf_point_init (attdef->p1);
                if (attdef->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        attdef->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the Z-value of the second alignment point \c z1 of a DXF
 * \c ATTDEF entity.
 *
 * \return the Z-value of the second alignment point \c z1.
 */
double
dxf_attdef_get_z1
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->p1->z0);
}


/*!
 * \brief Set the Z-value of the second alignment point \c z1 of a DXF
 * \c ATTDEF entity.
 *
 * \return a pointer to \c attdef when successful, or \c NULL when an
 * error occurred.
 */
DxfAttdef *
dxf_attdef_set_z1
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double z1
                /*!< the Z-value of the second alignment point \c z0 of
                 * a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                attdef->p1 = dxf_point_init (attdef->p1);
                if (attdef->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        attdef->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the height from a DXF \c ATTDEF entity.
 *
 * \return height.
 */
double
dxf_attdef_get_height
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->height < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->height);
}


/*!
 * \brief Set the height for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_height
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double height
                /*!< the height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->height = height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the relative X scale from a DXF \c ATTDEF entity.
 *
 * \return relative X scale.
 */
double
dxf_attdef_get_rel_x_scale
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->rel_x_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->rel_x_scale);
}


/*!
 * \brief Set the relative X scale for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_rel_x_scale
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double rel_x_scale
                /*!< the relative X scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rel_x_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        attdef->rel_x_scale = rel_x_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the rotation angle from a DXF \c ATTDEF entity.
 *
 * \return rotation angle.
 */
double
dxf_attdef_get_rot_angle
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        /*! \todo Unify the rotation angle. */
        return (attdef->rot_angle);
}


/*!
 * \brief Set the rotation angle for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_rot_angle
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double rot_angle
                /*!< the rotation angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Unify the rotation angle. */
        attdef->rot_angle = rot_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the oblique angle from a DXF \c ATTDEF entity.
 *
 * \return oblique angle.
 */
double
dxf_attdef_get_obl_angle
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        /*! \todo Unify the oblique angle. */
        return (attdef->obl_angle);
}


/*!
 * \brief Set the oblique angle for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_obl_angle
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double obl_angle
                /*!< the oblique angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Unify the oblique angle. */
        attdef->obl_angle = obl_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the attribute flags from a DXF \c ATTDEF entity.
 *
 * \return attribute flags.
 */
int16_t
dxf_attdef_get_attr_flags
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->attr_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (attdef->attr_flags > 8)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->attr_flags);
}


/*!
 * \brief Set the attribute flags for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_attr_flags
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t attr_flags
                /*!< the attribute flags to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attr_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (attr_flags > 8)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        attdef->attr_flags = attr_flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Test if the attribute definition is invisible.
 *
 * \return \c TRUE when the attribute definition is invisible,
 * or \c FALSE when the attribute definition is visible.
 */
int
dxf_attdef_is_invisible
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (attdef->attr_flags, 0));
}


/*!
 * \brief Test if the attribute definition is a constant attribute.
 *
 * \return \c TRUE when the attribute definition is a constant,
 * or \c FALSE when the attribute definition is not a constant.
 */
int
dxf_attdef_is_constant
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (attdef->attr_flags, 1));
}


/*!
 * \brief Test if the attribute definition input needs to be verified.
 *
 * \return \c TRUE when the input needs to be verified,
 * or \c FALSE when the input needs not to be verified.
 */
int
dxf_attdef_is_verification_required
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (attdef->attr_flags, 2));
}


/*!
 * \brief Test if the attribute definition is preset (no prompt during
 * insertion).
 *
 * \return \c TRUE when the attributre definition is preset,
 * or \c FALSE when the attribute definition is not preset.
 */
int
dxf_attdef_is_preset
(
        DxfAttdef *attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (attdef->attr_flags, 3));
}


/*!
 * \brief Get the text flags from a DXF \c ATTDEF entity.
 *
 * \return text flags.
 */
int16_t
dxf_attdef_get_text_flags
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->text_flags < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (attdef->text_flags > 4)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->text_flags);
}


/*!
 * \brief Set the text flags for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_text_flags
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t text_flags
                /*!< the text flags to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        if (text_flags > 4)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        attdef->text_flags = text_flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the horizontal alignment from a DXF \c ATTDEF entity.
 *
 * \return horizontal alignment.
 */
int16_t
dxf_attdef_get_hor_align
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->hor_align < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (attdef->hor_align > 5)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->hor_align);
}


/*!
 * \brief Set the horizontal alignment for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_hor_align
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t hor_align
                /*!< the horizontal alignment to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->hor_align = hor_align;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the field length from a DXF \c ATTDEF entity.
 *
 * \return field length.
 *
 * \note Not currently used in DXF R14.
 */
int16_t
dxf_attdef_get_field_length
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->field_length < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->field_length);
}


/*!
 * \brief Set the field length for a DXF \c ATTDEF entity.
 *
 * \note Not currently used in DXF R14.
 */
DxfAttdef *
dxf_attdef_set_field_length
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t field_length
                /*!< the field length to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (field_length < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        attdef->field_length = field_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the vertical text alignment from a DXF \c ATTDEF entity.
 *
 * \return horizontal alignment.
 */
int16_t
dxf_attdef_get_vert_align
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->vert_align < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attdef->vert_align > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->vert_align);
}


/*!
 * \brief Set the vertical text alignment for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_vert_align
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int16_t vert_align
                /*!< the vertical text alignment to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->vert_align = vert_align;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the X-value of the extrusion vector of a DXF \c ATTDEF
 * entity.
 *
 * \return the X-value of the extrusion vector.
 */
double
dxf_attdef_get_extr_x0
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector of a DXF \c ATTDEF
 * entity.
 *
 * \return a pointer to \c attdef when successful, \c NULL when an error
 * occurred.
 */
DxfAttdef *
dxf_attdef_set_extr_x0
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector of the entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the Y-value of the extrusion vector of a DXF \c ATTDEF
 * entity.
 *
 * \return the Y-value of the extrusion vector.
 */
double
dxf_attdef_get_extr_y0
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector of a DXF \c ATTDEF
 * entity.
 *
 * \return a pointer to \c attdef when successful, \c NULL when an error
 * occurred.
 */
DxfAttdef *
dxf_attdef_set_extr_y0
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector of a DXF
                 * \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the Z-value of the extrusion vector of a DXF \c ATTDEF
 * entity.
 *
 * \return the Z-value of the extrusion vector.
 */
double
dxf_attdef_get_extr_z0
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector of a DXF \c ATTDEF
 * entity.
 *
 * \return a pointer to \c attdef when successful, \c NULL when an error
 * occurred.
 */
DxfAttdef *
dxf_attdef_set_extr_z0
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector of a DXF
                 * \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c ATTDEF entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_attdef_get_extrusion_vector_as_point
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (attdef == NULL)
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
        point->x0 = attdef->extr_x0;
        point->y0 = attdef->extr_y0;
        point->z0 = attdef->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF
 * \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_extrusion_vector_from_point
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->extr_x0 = (double) point->x0;
        attdef->extr_y0 = (double) point->y0;
        attdef->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Set the extrusion vector for a DXF \c ATTDEF entity.
 */
DxfAttdef *
dxf_attdef_set_extrusion_vector
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
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
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attdef->extr_x0 = extr_x0;
        attdef->extr_y0 = extr_y0;
        attdef->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the pointer to the next \c ATTDEF entity from a DXF 
 * \c ATTDEF entity.
 *
 * \return pointer to the next \c ATTDEF entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfAttdef *
dxf_attdef_get_next
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfAttdef *) attdef->next);
}


/*!
 * \brief Set the pointer to the next \c ATTDEF for a DXF \c ATTDEF
 * entity.
 */
DxfAttdef *
dxf_attdef_set_next
(
        DxfAttdef *attdef,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        DxfAttdef *next
                /*!< a pointer to the next \c ATTDEF for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
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
        attdef->next = (struct DxfAttdef *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attdef);
}


/*!
 * \brief Get the pointer to the last \c ATTDEF entity from a linked
 * list DXF of \c ATTDEF entities.
 *
 * \return pointer to the last \c ATTDEF entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfAttdef *
dxf_attdef_get_last
(
        DxfAttdef *attdef
                /*!< a pointer to a DXF \c ATTDEF entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attdef->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfAttdef *) attdef);
        }
        DxfAttdef *iter = (DxfAttdef *) attdef->next;
        while (iter->next != NULL)
        {
                iter = (DxfAttdef *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfAttdef *) iter);
}


/* EOF */
