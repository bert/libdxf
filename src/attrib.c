/*!
 * \file attrib.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF attribute entity (\c ATTRIB).
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


#include "attrib.h"


/*!
 * \brief Allocate memory for a DXF \c ATTRIB.
 *
 * Fill the memory contents with zeros.
 */
DxfAttrib *
dxf_attrib_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAttrib *attrib = NULL;
        size_t size;

        size = sizeof (DxfAttrib);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((attrib = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfAttrib struct.\n")),
                  __FUNCTION__);
                attrib = NULL;
        }
        else
        {
                memset (attrib, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c ATTRIB entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfAttrib *
dxf_attrib_init
(
        DxfAttrib *attrib
                /*!< DXF attrib entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                attrib = dxf_attrib_new ();
        }
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfAttrib struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_attrib_set_id_code (attrib, 0);
        dxf_attrib_set_linetype (attrib, strdup (DXF_DEFAULT_LINETYPE));
        dxf_attrib_set_text_style (attrib, strdup (DXF_DEFAULT_TEXTSTYLE));
        dxf_attrib_set_layer (attrib, strdup (DXF_DEFAULT_LAYER));
        dxf_attrib_set_elevation (attrib, 0.0);
        dxf_attrib_set_thickness (attrib, 0.0);
        dxf_attrib_set_linetype_scale (attrib, DXF_DEFAULT_LINETYPE_SCALE);
        dxf_attrib_set_visibility (attrib, DXF_DEFAULT_VISIBILITY);
        dxf_attrib_set_color (attrib, DXF_COLOR_BYLAYER);
        dxf_attrib_set_paperspace (attrib, DXF_MODELSPACE);
        dxf_attrib_set_graphics_data_size (attrib, 0);
        dxf_attrib_set_shadow_mode (attrib, 0);
        dxf_attrib_set_binary_graphics_data (attrib, (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ());
        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) dxf_attrib_get_binary_graphics_data (attrib));
        dxf_attrib_set_dictionary_owner_soft (attrib, strdup(""));
        dxf_attrib_set_material (attrib, strdup (""));
        dxf_attrib_set_dictionary_owner_hard (attrib, strdup(""));
        dxf_attrib_set_lineweight (attrib, 0);
        dxf_attrib_set_plot_style_name (attrib, strdup (""));
        dxf_attrib_set_color_value (attrib, 0);
        dxf_attrib_set_color_name (attrib, strdup (""));
        dxf_attrib_set_transparency (attrib, 0);
        dxf_attrib_set_default_value (attrib, strdup (""));
        dxf_attrib_set_tag_value (attrib, strdup (""));
        dxf_attrib_set_p0 (attrib, dxf_point_new ());
        dxf_point_init ((DxfPoint *) dxf_attrib_get_p0 (attrib));
        dxf_attrib_set_x0 (attrib, 0.0);
        dxf_attrib_set_y0 (attrib, 0.0);
        dxf_attrib_set_z0 (attrib, 0.0);
        dxf_attrib_set_p1 (attrib, dxf_point_new ());
        dxf_point_init ((DxfPoint *) dxf_attrib_get_p1 (attrib));
        dxf_attrib_set_x1 (attrib, 0.0);
        dxf_attrib_set_y1 (attrib, 0.0);
        dxf_attrib_set_z1 (attrib, 0.0);
        dxf_attrib_set_height (attrib, 0.0);
        dxf_attrib_set_rel_x_scale (attrib, 0.0);
        dxf_attrib_set_rot_angle (attrib, 0.0);
        dxf_attrib_set_obl_angle (attrib, 0.0);
        dxf_attrib_set_attr_flags (attrib, 0);
        dxf_attrib_set_text_flags (attrib, 0);
        dxf_attrib_set_hor_align (attrib, 0);
        dxf_attrib_set_field_length (attrib, 0);
        dxf_attrib_set_vert_align (attrib, 0);
        dxf_attrib_set_extr_x0 (attrib, 0.0);
        dxf_attrib_set_extr_y0 (attrib, 0.0);
        dxf_attrib_set_extr_z0 (attrib, 1.0);
        dxf_attrib_set_lineweight (attrib, 0);
        dxf_attrib_set_next (attrib, NULL);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Read data from a DXF file into an \c ATTRIB entity.
 *
 * The last line read from file contained the string "ATTRIB". \n
 * Now follows some data for the \c ATTRIB, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c attrib. \n
 *
 * \return a pointer to \c attrib.
 */
DxfAttrib *
dxf_attrib_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAttrib *attrib
                /*!< DXF attrib entity. */
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
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                attrib = dxf_attrib_new ();
                attrib = dxf_attrib_init (attrib);
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
                        /* Now follows a string containing the attribute
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attrib->default_value);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a tag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attrib->tag_value);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &attrib->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attrib->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attrib->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attrib->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->p1->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (attrib->elevation = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->rel_x_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->obl_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &attrib->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attrib->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attrib->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * attribute flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attrib->attr_flags);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attrib->text_flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attrib->hor_align);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * field length value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attrib->field_length);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the
                         * vertical alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &attrib->vert_align);
                }
                else if ((fp->acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbText") != 0)
                        && (strcmp (temp_string, "AcDbAttribute") != 0))
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
                        fscanf (fp->fp, "%lf\n", &attrib->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attrib->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", attrib->dictionary_owner_hard);
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
        if (strcmp (dxf_attrib_get_linetype (attrib), "") == 0)
        {
                dxf_attrib_set_linetype (attrib, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_attrib_get_layer (attrib), "") == 0)
        {
                dxf_attrib_set_layer (attrib, strdup (DXF_DEFAULT_LAYER));
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a DXF \c ATTRIB entity.
 */
int
dxf_attrib_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfAttrib *attrib
                /*!< DXF attribute entity */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ATTRIB");

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
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attrib_get_default_value (attrib), "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () default value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib_get_id_code (attrib));
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attrib_get_tag_value (attrib), "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () tag value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib_get_id_code (attrib));
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attrib_get_text_style (attrib), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () text style string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib_get_id_code (attrib));
                fprintf (stderr,
                  (_("\tdefault text style STANDARD applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_attrib_set_text_style (attrib, strdup (DXF_DEFAULT_TEXTSTYLE));
        }
        if (strcmp (dxf_attrib_get_linetype (attrib), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib_get_id_code (attrib));
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_attrib_set_linetype (attrib, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_attrib_get_layer (attrib), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib_get_id_code (attrib));
                fprintf (stderr,
                  (_("\t%s entity is relocated to the default layer.\n")),
                  dxf_entity_name);
                dxf_attrib_set_layer (attrib, strdup (DXF_DEFAULT_LAYER));
        }
        if (dxf_attrib_get_height (attrib) == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () height has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib_get_id_code (attrib));
                fprintf (stderr,
                  (_("\tdefault height of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_attrib_set_height (attrib, 1.0);
        }
        if (dxf_attrib_get_rel_x_scale (attrib) == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib_get_id_code (attrib));
                fprintf (stderr,
                  (_("\tdefault relative X-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_attrib_set_rel_x_scale (attrib, 1.0);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_attrib_get_id_code (attrib) != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_attrib_get_id_code (attrib));
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
        if ((strcmp (dxf_attrib_get_dictionary_owner_soft (attrib), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_attrib_get_dictionary_owner_soft (attrib));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_attrib_get_dictionary_owner_hard (attrib), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_attrib_get_dictionary_owner_hard (attrib));
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_attrib_get_paperspace (attrib) == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_attrib_get_layer (attrib));
        if (strcmp (dxf_attrib_get_linetype (attrib), DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_attrib_get_linetype (attrib));
        }
        if (dxf_attrib_get_color (attrib) != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_attrib_get_color (attrib));
        }
        if (dxf_attrib_get_linetype_scale (attrib) != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_attrib_get_linetype_scale (attrib));
        }
        if (dxf_attrib_get_visibility (attrib) != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_attrib_get_visibility (attrib));
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_attrib_get_elevation (attrib) != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_attrib_get_elevation (attrib));
        }
        if (dxf_attrib_get_thickness (attrib) != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_attrib_get_thickness (attrib));
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_attrib_get_x0 (attrib));
        fprintf (fp->fp, " 20\n%f\n", dxf_attrib_get_y0 (attrib));
        fprintf (fp->fp, " 30\n%f\n", dxf_attrib_get_z0 (attrib));
        fprintf (fp->fp, " 40\n%f\n", dxf_attrib_get_height (attrib));
        fprintf (fp->fp, "  1\n%s\n", dxf_attrib_get_default_value (attrib));
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbAttribute\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_attrib_get_tag_value (attrib));
        fprintf (fp->fp, " 70\n%d\n", dxf_attrib_get_attr_flags (attrib));
        if (dxf_attrib_get_field_length (attrib) != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", dxf_attrib_get_field_length (attrib));
        }
        if (dxf_attrib_get_rot_angle (attrib) != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", dxf_attrib_get_rot_angle (attrib));
        }
        if (dxf_attrib_get_rel_x_scale (attrib)!= 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", dxf_attrib_get_rel_x_scale (attrib));
        }
        if (dxf_attrib_get_obl_angle (attrib) != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", dxf_attrib_get_obl_angle (attrib));
        }
        if (strcmp (dxf_attrib_get_text_style (attrib), "STANDARD") != 0)
        {
                fprintf (fp->fp, "  7\n%s\n", dxf_attrib_get_text_style (attrib));
        }
        if (dxf_attrib_get_text_flags (attrib) != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", dxf_attrib_get_text_flags (attrib));
        }
        if (dxf_attrib_get_hor_align (attrib) != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", dxf_attrib_get_hor_align (attrib));
        }
        if (dxf_attrib_get_vert_align (attrib) != 0)
        {
                fprintf (fp->fp, " 74\n%d\n", dxf_attrib_get_vert_align (attrib));
        }
        if ((dxf_attrib_get_hor_align (attrib) != 0) || (dxf_attrib_get_vert_align (attrib) != 0))
        {
                if ((dxf_attrib_get_x0 (attrib) == dxf_attrib_get_x1 (attrib))
                        && (dxf_attrib_get_y0 (attrib) == dxf_attrib_get_y0 (attrib))
                        && (dxf_attrib_get_z0 (attrib) == dxf_attrib_get_z0 (attrib)))
                {
                        fprintf (stderr,
                          (_("Warning in %s () insertion point and alignment point are identical for the %s entity with id-code: %x.\n")),
                          __FUNCTION__, dxf_entity_name, dxf_attrib_get_id_code (attrib));
                        fprintf (stderr,
                          (_("    default justification applied to %s entity\n")),
                          dxf_entity_name);
                        dxf_attrib_set_hor_align (attrib, 0);
                        dxf_attrib_set_vert_align (attrib, 0);
                }
                else
                {
                        fprintf (fp->fp, " 11\n%f\n", dxf_attrib_get_x1 (attrib));
                        fprintf (fp->fp, " 21\n%f\n", dxf_attrib_get_y1 (attrib));
                        fprintf (fp->fp, " 31\n%f\n", dxf_attrib_get_z1 (attrib));
                }
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (dxf_attrib_get_extr_x0 (attrib) != 0.0)
                && (dxf_attrib_get_extr_y0 (attrib) != 0.0)
                && (dxf_attrib_get_extr_z0 (attrib) != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", dxf_attrib_get_extr_x0 (attrib));
                fprintf (fp->fp, "220\n%f\n", dxf_attrib_get_extr_y0 (attrib));
                fprintf (fp->fp, "230\n%f\n", dxf_attrib_get_extr_z0 (attrib));
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ATTRIB and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_attrib_free
(
        DxfAttrib *attrib
                /*!< DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfAttrib was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (attrib->linetype);
        free (attrib->layer);
        free (attrib->default_value);
        free (attrib->tag_value);
        free (attrib->text_style);
        dxf_binary_graphics_data_free_chain (attrib->binary_graphics_data);
        free (attrib->dictionary_owner_soft);
        free (attrib->material);
        free (attrib->dictionary_owner_hard);
        free (attrib->plot_style_name);
        free (attrib->color_name);
        dxf_point_free (attrib->p0);
        dxf_point_free (attrib->p1);
        free (attrib);
        attrib = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c ATTRIB
 * entities and all their data fields.
 */
void
dxf_attrib_free_chain
(
        DxfAttrib *attribs
                /*!< pointer to the chain of DXF ATTRIB entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (attribs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (attribs != NULL)
        {
                struct DxfAttrib *iter = attribs->next;
                dxf_attrib_free (attribs);
                attribs = (DxfAttrib *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c ATTRIB entity.
 *
 * \return ID code.
 */
int
dxf_attrib_get_id_code
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_id_code
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
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
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the linetype from a DXF \c ATTRIB entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_attrib_get_linetype
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_linetype
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the layer from a DXF \c ATTRIB entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_attrib_get_layer
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->layer));
}


/*!
 * \brief Set the layer for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_layer
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the elevation from a DXF \c ATTRIB entity.
 *
 * \return elevation.
 */
double
dxf_attrib_get_elevation
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_elevation
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the thickness from a DXF \c ATTRIB entity.
 *
 * \return thickness.
 */
double
dxf_attrib_get_thickness
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_thickness
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the linetype scale from a DXF \c ATTRIB entity.
 *
 * \return linetype scale.
 */
double
dxf_attrib_get_linetype_scale
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_linetype_scale
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the visibility from a DXF \c ATTRIB entity.
 *
 * \return visibility.
 */
int16_t
dxf_attrib_get_visibility
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_visibility
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the color from a DXF \c ATTRIB entity.
 *
 * \return color.
 */
int
dxf_attrib_get_color
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->color);
}


/*!
 * \brief Set the color for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_color
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        attrib->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c ATTRIB entity.
 *
 * \return paperspace flag value.
 */
int
dxf_attrib_get_paperspace
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (attrib->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_paperspace
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c ATTRIB
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_attrib_get_graphics_data_size
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        if (attrib->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c ATTRIB
 * entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_graphics_data_size
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero graphics_data_size value was passed.\n")),
                  __FUNCTION__);
        }
        attrib->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c ATTRIB entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_attrib_get_shadow_mode
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_shadow_mode
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c ATTRIB entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_attrib_get_binary_graphics_data
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the binary_graphics_data member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) attrib->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_binary_graphics_data
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c ATTRIB entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attrib_get_dictionary_owner_soft
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_dictionary_owner_soft
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_attrib_get_material
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the material member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_material
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c ATTRIB entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attrib_get_dictionary_owner_hard
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_dictionary_owner_hard
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the \c lineweight from a DXF \c ATTRIB entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_attrib_get_lineweight
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_lineweight
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_attrib_get_plot_style_name
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the plot_style_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_plot_style_name
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the \c color_value from a DXF \c ATTRIB entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_attrib_get_color_value
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_color_value
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the \c color_name from a DXF \c ATTRIB entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_attrib_get_color_name
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the color_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_color_name
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the \c transparency from a DXF \c ATTRIB entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_attrib_get_transparency
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_transparency
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the default value from a DXF \c ATTRIB entity.
 *
 * \return default value.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attrib_get_default_value
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->default_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the default_value member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->default_value));
}


/*!
 * \brief Set the default value for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_default_value
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *default_value
                /*!< a string containing the default_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->default_value = strdup (default_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the tag value from a DXF \c ATTRIB entity.
 *
 * \return tag value.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attrib_get_tag_value
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->tag_value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the tag_value member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->tag_value));
}


/*!
 * \brief Set the tag value for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_tag_value
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *tag_value
                /*!< a string containing the tag_value for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->tag_value = strdup (tag_value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the text style from a DXF \c ATTRIB entity.
 *
 * \return text style.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_attrib_get_text_style
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->text_style ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the tag_value member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (attrib->text_style));
}


/*!
 * \brief Set the text style for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_text_style
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        char *text_style
                /*!< a string containing the text style for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->text_style = strdup (text_style);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the text start point \c p0 of a DXF \c ATTRIB entity.
 *
 * \return the text start point \c p0.
 */
DxfPoint *
dxf_attrib_get_p0
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->p0 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->p0);
}


/*!
 * \brief Set the text start point \c p0 of a DXF \c ATTRIB entity.
 *
 * \return a pointer to a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_p0
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the X-value of the text start point \c x0 of a DXF
 * \c ATTRIB entity.
 *
 * \return the X-value of the text start point \c x0.
 */
double
dxf_attrib_get_x0
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->p0->x0);
}


/*!
 * \brief Set the X-value of the text start point \c x0 of a DXF
 * \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_x0
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double x0
                /*!< the X-value of the text start point \c x0 of a DXF
                 * \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the Y-value of the text start point \c y0 of a DXF
 * \c ATTRIB entity.
 *
 * \return the Y-value of the text start point \c y0.
 */
double
dxf_attrib_get_y0
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->p0->y0);
}


/*!
 * \brief Set the Y-value of the text start point \c y0 of a DXF
 * \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_y0
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double y0
                /*!< the Y-value of the text start point \c y0 of a DXF
                 * \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the Z-value of the text start point \c z0 of a DXF
 * \c ATTRIB entity.
 *
 * \return the Z-value of the text start point \c z0.
 */
double
dxf_attrib_get_z0
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->p0->z0);
}


/*!
 * \brief Set the Z-value of the text start point \c z0 of a DXF
 * \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_z0
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double z0
                /*!< the Z-value of the text start point \c z0 of a DXF
                 * \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the alignment point \c p1 of a DXF \c ATTRIB entity.
 *
 * \return the alignment point.
 */
DxfPoint *
dxf_attrib_get_p1
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                __FUNCTION__);
              return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->p1);
}


/*!
 * \brief Set the alignment point \c p1 of a DXF \c ATTRIB entity.
 *
 * \return a pointer to a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_p1
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the X-value \c x1 of the alignment of a DXF \c ATTRIB
 * entity.
 *
 * \return the X-value of the point \c x1.
 */
double
dxf_attrib_get_x1
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->p1->x0);
}


/*!
 * \brief Set the X-value \c x1 of the alinment point of a DXF
 * \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_x1
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double x1
                /*!< the X-value \c x1 of a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the Y-value \c y1 of the alignment point of a DXF
 * \c ATTRIB entity.
 *
 * \return the Y-value of the point \c y1.
 */
double
dxf_attrib_get_y1
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->p1->y0);
}


/*!
 * \brief Set the Y-value \c y1 of the alignment point of a DXF
 * \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_y1
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double y1
                /*!< the Y-value \c y1 of a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the Z-value \c z1 of the alignment point of a DXF
 * \c ATTRIB entity.
 *
 * \return the Y-value of the point \c z1.
 */
double
dxf_attrib_get_z1
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->p1->z0);
}


/*!
 * \brief Set the Z-value \c z1 of the alignment point of a DXF
 * \c ATTRIB entity.
 *
 * \return a pointer to \c attrib when successful, or \c NULL when an
 * error occurred.
 */
DxfAttrib *
dxf_attrib_set_z1
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double z1
                /*!< the Z-value \c z1 of a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the height from a DXF \c ATTRIB entity.
 *
 * \return height.
 */
double
dxf_attrib_get_height
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->height < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the height member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->height);
}


/*!
 * \brief Set the height for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_height
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double height
                /*!< the height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (height < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative height value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->height = height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the relative X scale from a DXF \c ATTRIB entity.
 *
 * \return relative X scale.
 */
double
dxf_attrib_get_rel_x_scale
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->height < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the rel_x_scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->rel_x_scale);
}


/*!
 * \brief Set the relative X scale for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_rel_x_scale
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double rel_x_scale
                /*!< the relative X scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->rel_x_scale = rel_x_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the rotation angle from a DXF \c ATTRIB entity.
 *
 * \return rotation angle.
 */
double
dxf_attrib_get_rot_angle
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        return (attrib->rot_angle);
}


/*!
 * \brief Set the rotation angle for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_rot_angle
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double rot_angle
                /*!< the rotation angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Unify the rotation angle. */
        attrib->rot_angle = rot_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the oblique angle from a DXF \c ATTRIB entity.
 *
 * \return oblique angle.
 */
double
dxf_attrib_get_obl_angle
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        return (attrib->obl_angle);
}


/*!
 * \brief Set the oblique angle for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_obl_angle
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double obl_angle
                /*!< the oblique angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Unify the oblique angle. */
        attrib->obl_angle = obl_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the attribute flags from a DXF \c ATTRIB entity.
 *
 * \return attribute flags.
 */
int
dxf_attrib_get_attr_flags
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->attr_flags < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the attr_flags member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->attr_flags > 8)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the attr_flags member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->attr_flags);
}


/*!
 * \brief Set the attribute flags for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_attr_flags
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int attr_flags
                /*!< the attribute flags to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attr_flags < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value in attribute flags was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attr_flags > 8)
        {
                fprintf (stderr,
                  (_("Error in %s () a invalid value in attribute flags was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->attr_flags = attr_flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Test if the attribute is invisible.
 *
 * \return \c TRUE when the attribute is invisible, or \c FALSE when the
 * attribute is visible.
 */
int
dxf_attrib_is_invisible
(
        DxfAttrib *attrib
                /*!< DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (attrib->attr_flags, 0));
}


/*!
 * \brief Test if the attribute is a constant attribute.
 *
 * \return \c TRUE when the attribute is a constant, or \c FALSE when
 * the attribute is not a constant attribute.
 */
int
dxf_attrib_is_constant
(
        DxfAttrib *attrib
                /*!< DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (attrib->attr_flags, 1));
}


/*!
 * \brief Test if the attribute input needs to be verified.
 *
 * \return \c TRUE when the input needs to be verified,
 * or \c FALSE when the input needs not to be verified.
 */
int
dxf_attrib_is_verification_required
(
        DxfAttrib *attrib
                /*!< DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (attrib->attr_flags, 2));
}


/*!
 * \brief Test if the attribute is preset (no prompt during insertion).
 *
 * \return \c TRUE when the attribute is preset,
 * or \c FALSE when the attribute is not preset.
 */
int
dxf_attrib_is_preset
(
        DxfAttrib *attrib
                /*!< DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (attrib->attr_flags, 3));
}


/*!
 * \brief Get the text flags from a DXF \c ATTRIB entity.
 *
 * \return text flags.
 */
int
dxf_attrib_get_text_flags
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->text_flags < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the text flags member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->text_flags > 4)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the text flags member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->text_flags);
}


/*!
 * \brief Set the text flags for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_text_flags
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int text_flags
                /*!< the text flags to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_flags < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value in text flags was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (text_flags > 4)
        {
                fprintf (stderr,
                  (_("Error in %s () a invalid value in text flags was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->text_flags = text_flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the horizontal alignment from a DXF \c ATTRIB entity.
 *
 * \return horizontal alignment.
 */
int
dxf_attrib_get_hor_align
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->hor_align < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the hor_align member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->hor_align > 5)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the hor_align member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->hor_align);
}


/*!
 * \brief Set the horizontal alignment for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_hor_align
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int hor_align
                /*!< the horizontal alignment to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hor_align < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value in horizontal alignment was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hor_align > 5)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value in horizontal alignment was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->hor_align = hor_align;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the field length from a DXF \c ATTRIB entity.
 *
 * \return field length.
 *
 * \note Not currently used in DXF R14.
 */
int
dxf_attrib_get_field_length
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->field_length < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the field_length member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->field_length);
}


/*!
 * \brief Set the field length for a DXF \c ATTRIB entity.
 *
 * \note Not currently used in DXF R14.
 */
DxfAttrib *
dxf_attrib_set_field_length
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        int field_length
                /*!< the field length to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (field_length < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value in field length was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->field_length = field_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the vertical text alignment from a DXF \c ATTRIB entity.
 *
 * \return horizontal alignment.
 */
int
dxf_attrib_get_vert_align
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->vert_align < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the vert_align member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (attrib->vert_align > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the vert_align member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->vert_align);
}


/*!
 * \brief Set the vertical text alignment for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_vert_align
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTDEF entity. */
        int vert_align
                /*!< the vertical text alignment to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vert_align < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value in vertical alignment was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vert_align > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value in vertical alignment was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->vert_align = vert_align;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the X-value of the extrusion vector of a DXF \c ATTRIB
 * entity.
 *
 * \return the X-value of the extrusion vector.
 */
double
dxf_attrib_get_extr_x0
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector of a DXF \c ATTRIB
 * entity.
 *
 * \return a pointer to \c attrib when successful, \c NULL when an error
 * occurred.
 */
DxfAttrib *
dxf_attrib_set_extr_x0
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector of a DXF
                 * \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the Y-value of the extrusion vector of a DXF \c ATTRIB
 * entity.
 *
 * \return the Y-value of the extrusion vector.
 */
double
dxf_attrib_get_extr_y0
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector of a DXF \c ATTRIB
 * entity.
 *
 * \return a pointer to \c attrib when successful, \c NULL when an error
 * occurred.
 */
DxfAttrib *
dxf_attrib_set_extr_y0
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector of a DXF
                 * \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the Z-value of the extrusion vector of a DXF \c ATTRIB
 * entity.
 *
 * \return the Z-value of the extrusion vector.
 */
double
dxf_attrib_get_extr_z0
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector of a DXF \c ATTRIB
 * entity.
 *
 * \return a pointer to \c attrib when successful, \c NULL when an error
 * occurred.
 */
DxfAttrib *
dxf_attrib_set_extr_z0
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector of a DXF
                 * \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c ATTRIB entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_attrib_get_extrusion_vector_as_point
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (attrib == NULL)
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
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        point->x0 = attrib->extr_x0;
        point->y0 = attrib->extr_y0;
        point->z0 = attrib->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF
 * \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_extrusion_vector_from_point
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->extr_x0 = (double) point->x0;
        attrib->extr_y0 = (double) point->y0;
        attrib->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Set the extrusion vector for a DXF \c ATTRIB entity.
 */
DxfAttrib *
dxf_attrib_set_extrusion_vector
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
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
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        attrib->extr_x0 = extr_x0;
        attrib->extr_y0 = extr_y0;
        attrib->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the pointer to the next \c ATTRIB entity from a DXF 
 * \c ATTRIB entity.
 *
 * \return pointer to the next \c ATTRIB entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfAttrib *
dxf_attrib_get_next
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfAttrib *) attrib->next);
}


/*!
 * \brief Set the pointer to the next \c ATTRIB for a DXF \c ATTRIB
 * entity.
 */
DxfAttrib *
dxf_attrib_set_next
(
        DxfAttrib *attrib,
                /*!< a pointer to a DXF \c ATTRIB entity. */
        DxfAttrib *next
                /*!< a pointer to the next \c ATTRIB for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
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
        attrib->next = (struct DxfAttrib *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (attrib);
}


/*!
 * \brief Get the pointer to the last \c ATTRIB entity from a linked
 * list of DXF \c ATTRIB entities.
 *
 * \return pointer to the last \c ATTRIB entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfAttrib *
dxf_attrib_get_last
(
        DxfAttrib *attrib
                /*!< a pointer to a DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attrib->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfAttrib *) attrib);
        }
        DxfAttrib *iter = (DxfAttrib *) attrib->next;
        while (iter->next != NULL)
        {
                iter = (DxfAttrib *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfAttrib *) iter);
}


/* EOF */
