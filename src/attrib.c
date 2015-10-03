/*!
 * \file attrib.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF attribute entity (\c ATTRIB).
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 * \brief Allocate memory and initialize data fields in a \c ATTRIB entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        attrib->value = strdup ("");
        attrib->tag_value = strdup ("");
        attrib->id_code = 0;
        attrib->linetype = strdup (DXF_DEFAULT_LINETYPE);
        attrib->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        attrib->layer = strdup (DXF_DEFAULT_LAYER);
        attrib->x0 = 0.0;
        attrib->y0 = 0.0;
        attrib->z0 = 0.0;
        attrib->x1 = 0.0;
        attrib->y1 = 0.0;
        attrib->z1 = 0.0;
        attrib->height = 0.0;
        attrib->rel_x_scale = 0.0;
        attrib->rot_angle = 0.0;
        attrib->obl_angle = 0.0;
        attrib->elevation = 0.0;
        attrib->thickness = 0.0;
        attrib->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        attrib->visibility = DXF_DEFAULT_VISIBILITY;
        attrib->color = DXF_COLOR_BYLAYER;
        attrib->paperspace = DXF_MODELSPACE;
        attrib->attr_flags = 0;
        attrib->text_flags = 0;
        attrib->hor_align = 0;
        attrib->field_length = 0;
        attrib->vert_align = 0;
        attrib->extr_x0 = 0.0;
        attrib->extr_y0 = 0.0;
        attrib->extr_z0 = 0.0;
        attrib->dictionary_owner_soft = strdup("");
        attrib->dictionary_owner_hard = strdup("");
        attrib->line_weight = 0;
        attrib->next = NULL;
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                        fscanf (fp->fp, "%s\n", attrib->value);
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
                        fscanf (fp->fp, "%lf\n", &attrib->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &attrib->z1);
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
        if (strcmp (attrib->linetype, "") == 0)
        {
                attrib->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (attrib->layer, "") == 0)
        {
                attrib->layer = strdup (DXF_DEFAULT_LAYER);
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (strcmp (attrib->value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () default value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attrib->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (attrib->tag_value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () tag value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attrib->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (attrib->text_style, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () text style string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attrib->id_code);
                fprintf (stderr,
                  (_("\tdefault text style STANDARD applied to %s entity.\n")),
                  dxf_entity_name);
                attrib->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (attrib->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, attrib->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                attrib->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (attrib->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attrib->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to the default layer.\n")),
                  dxf_entity_name);
                attrib->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (attrib->height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () height has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attrib->id_code);
                fprintf (stderr,
                  (_("\tdefault height of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                attrib->height = 1.0;
        }
        if (attrib->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, attrib->id_code);
                fprintf (stderr,
                  (_("\tdefault relative X-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                attrib->rel_x_scale = 1.0;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (attrib->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", attrib->id_code);
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
        if ((strcmp (attrib->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", attrib->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (attrib->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", attrib->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (attrib->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", attrib->layer);
        if (strcmp (attrib->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", attrib->linetype);
        }
        if (attrib->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", attrib->color);
        }
        if (attrib->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", attrib->linetype_scale);
        }
        if (attrib->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", attrib->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (attrib->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", attrib->elevation);
        }
        if (attrib->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", attrib->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", attrib->x0);
        fprintf (fp->fp, " 20\n%f\n", attrib->y0);
        fprintf (fp->fp, " 30\n%f\n", attrib->z0);
        fprintf (fp->fp, " 40\n%f\n", attrib->height);
        fprintf (fp->fp, "  1\n%s\n", attrib->value);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbAttribute\n");
        }
        fprintf (fp->fp, "  2\n%s\n", attrib->tag_value);
        fprintf (fp->fp, " 70\n%d\n", attrib->attr_flags);
        if (attrib->field_length != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", attrib->field_length);
        }
        if (attrib->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", attrib->rot_angle);
        }
        if (attrib->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", attrib->rel_x_scale);
        }
        if (attrib->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", attrib->obl_angle);
        }
        if (strcmp (attrib->text_style, "STANDARD") != 0)
        {
                fprintf (fp->fp, "  7\n%s\n", attrib->text_style);
        }
        if (attrib->text_flags != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", attrib->text_flags);
        }
        if (attrib->hor_align != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", attrib->hor_align);
        }
        if (attrib->vert_align != 0)
        {
                fprintf (fp->fp, " 74\n%d\n", attrib->vert_align);
        }
        if ((attrib->hor_align != 0) || (attrib->vert_align != 0))
        {
                if ((attrib->x0 == attrib->x1)
                        && (attrib->y0 == attrib->y1)
                        && (attrib->z0 == attrib->z1))
                {
                        fprintf (stderr,
                          (_("Warning in %s () insertion point and alignment point are identical for the %s entity with id-code: %x.\n")),
                          __FUNCTION__, dxf_entity_name, attrib->id_code);
                        fprintf (stderr,
                          (_("    default justification applied to %s entity\n")),
                          dxf_entity_name);
                        attrib->hor_align = 0;
                        attrib->vert_align = 0;
                }
                else
                {
                        fprintf (fp->fp, " 11\n%f\n", attrib->x1);
                        fprintf (fp->fp, " 21\n%f\n", attrib->y1);
                        fprintf (fp->fp, " 31\n%f\n", attrib->z1);
                }
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (attrib->extr_x0 != 0.0)
                && (attrib->extr_y0 != 0.0)
                && (attrib->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", attrib->extr_x0);
                fprintf (fp->fp, "220\n%f\n", attrib->extr_y0);
                fprintf (fp->fp, "230\n%f\n", attrib->extr_z0);
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (attrib->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfAttrib was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (attrib->linetype);
        free (attrib->layer);
        free (attrib->value);
        free (attrib->tag_value);
        free (attrib->text_style);
        free (attrib->dictionary_owner_soft);
        free (attrib->dictionary_owner_hard);
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result;

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
        result = attrib->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c ATTRIB entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 * \brief Test if the attribute is invisible.
 *
 * \return \c TRUE when the attribute is invisible, or \c FALSE when the
 * attribute is visible.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (attrib->attr_flags, 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the attribute is a constant attribute.
 *
 * \return \c TRUE when the attribute is a constant, or \c FALSE when
 * the attribute is not a constant attribute.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (attrib->attr_flags, 1);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the attribute input needs to be verified.
 *
 * \return \c TRUE when the input needs to be verified,
 * or \c FALSE when the input needs not to be verified.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (attrib->attr_flags, 2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if the attribute is preset (no prompt during insertion).
 *
 * \return \c TRUE when the attribute is preset,
 * or \c FALSE when the attribute is not preset.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (attrib->attr_flags, 3);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
