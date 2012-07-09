/*!
 * \file attrib.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 */
DxfAttrib *
dxf_attrib_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attrib_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfAttrib *dxf_attrib = NULL;
        size_t size;

        size = sizeof (DxfAttrib);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_attrib = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_attrib_new () could not allocate memory for a DxfAttrib struct.\n");
                dxf_attrib = NULL;
        }
        else
        {
                memset (dxf_attrib, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attrib_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_attrib);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c ATTRIB entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfAttrib *
dxf_attrib_init
(
        DxfAttrib *dxf_attrib
                /*!< DXF attrib entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attrib_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_attrib = dxf_attrib_new ();
        if (dxf_attrib == NULL)
        {
              fprintf (stderr, "ERROR in dxf_attrib_init () could not allocate memory for a DxfAttrib struct.\n");
              return (NULL);
        }
        dxf_attrib->value = strdup ("");
        dxf_attrib->tag_value = strdup ("");
        dxf_attrib->common.id_code = 0;
        dxf_attrib->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_attrib->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        dxf_attrib->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_attrib->x0 = 0.0;
        dxf_attrib->y0 = 0.0;
        dxf_attrib->z0 = 0.0;
        dxf_attrib->x1 = 0.0;
        dxf_attrib->y1 = 0.0;
        dxf_attrib->z1 = 0.0;
        dxf_attrib->height = 0.0;
        dxf_attrib->rel_x_scale = 0.0;
        dxf_attrib->rot_angle = 0.0;
        dxf_attrib->obl_angle = 0.0;
        dxf_attrib->common.thickness = 0.0;
        dxf_attrib->common.color = DXF_COLOR_BYLAYER;
        dxf_attrib->common.paperspace = DXF_MODELSPACE;
        dxf_attrib->attr_flags = 0;
        dxf_attrib->text_flags = 0;
        dxf_attrib->hor_align = 0;
        dxf_attrib->field_length = 0;
        dxf_attrib->vert_align = 0;
        dxf_attrib->extr_x0 = 0.0;
        dxf_attrib->extr_y0 = 0.0;
        dxf_attrib->extr_z0 = 0.0;
        dxf_attrib->common.acad_version_number = 0;
        dxf_attrib->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attrib_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_attrib);
}


/*!
 * \brief Read data from a DXF file into an \c ATTRIB entity.
 *
 * The last line read from file contained the string "ATTRIB". \n
 * Now follows some data for the \c ATTRIB, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_attrib. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_attrib_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfAttrib *dxf_attrib,
                /*!< DXF attrib entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attrib_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_attrib)
        {
                dxf_attrib = dxf_attrib_new ();
        }
        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_attrib_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing the attribute
                         * value. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_attrib->value);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a tag value. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_attrib->tag_value);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_attrib->common.id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_attrib->common.linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_attrib->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_attrib->common.layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the align point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the align point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the align point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->z1);
                }
                else if ((acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_attrib->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->common.thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->rel_x_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->obl_angle);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_attrib->common.color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_attrib->common.paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * attribute flags value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_attrib->attr_flags);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text flags value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_attrib->text_flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal alignment value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_attrib->hor_align);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * field length value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_attrib->field_length);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the
                         * vertical alignment value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_attrib->vert_align);
                }
                else if ((acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbText") != 0)))
                        {
                                fprintf (stderr, "Error in dxf_attrib_read () found a bad subclass marker in: %s in line: %d.\n",
                                        filename, *line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_attrib->extr_z0);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr, "Warning: in dxf_attrib_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attrib_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a DXF \c ATTRIB entity.
 */
int
dxf_attrib_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *value,
                /*!< group code = 1. */
        char *tag_value,
                /*!< group code = 2. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to BYLAYER. */
        char *text_style,
                /*!< group code = 7\n
                 * optional, defaults to STANDARD. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * start point. */
        double y0,
                /*!< group code = 20\n
                 * start point. */
        double z0,
                /*!< group code = 30\n
                 * start point. */
        double x1,
                /*!< group code = 11\n
                 * alignment point. */
        double y1,
                /*!< group code = 21\n
                 * alignment point. */
        double z1,
                /*!< group code = 31\n
                 * alignment point. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        double height,
                /*!< group code = 40. */
        double rel_x_scale,
                /*!< group code = 41\n
                 * optional, defaults to 1.0. */
        double rot_angle,
                /*!< group code = 50\n
                 * optional, defaults to 0.0. */
        double obl_angle,
                /*!< group code = 51\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to BYLAYER. */
        int paperspace,
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int attr_flags,
                /*!< group code = 70\n
                 * bit codes:\n
                 * 1 = attribute is invisible (does not display)\n
                 * 2 = this is a constant attribute\n
                 * 4 = verification is required on input of this attribute\n
                 * 8 = attribute is preset (no prompt during insertion). */
        int text_flags,
                /*!< group code = 71\n
                 * optional,defaults to 0\n
                 * bit codes:\n
                 * 2 = text is backward (mirrored in X)\n
                 * 4 = text is upside down (mirrored in Y). */
        int hor_align,
                /*!< group code = 72\n
                 * optional, defaults to 0\n
                 * codes:\n
                 * 0 = left\n
                 * 1 = center\n
                 * 2 = right\n
                 * 3 = aligned, only when vert_align = 0\n
                 * 4 = middle, only when vert_align = 0\n
                 * 5 = fit, only when vert_align = 0. */
        int field_length,
                /*!< group code = 73\n
                 * optional, defaults to 0. */
        int vert_align
                /*!< group code = 74\n
                 * optional, defaults to 0\n
                 * codes:\n
                 * 0 = baseline\n
                 * 1 = bottom\n
                 * 2 = middle\n
                 * 3 = top. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attrib_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("ATTRIB");
        if (strcmp (value, "") == 0)
        {
                fprintf (stderr, "Error in dxf_attrib_write_lowlevel () default value string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (tag_value, "") == 0)
        {
                fprintf (stderr, "Error indxf_attrib_write_lowlevel () tag value string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (text_style, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_attrib_write_lowlevel () text style string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default text style STANDARD applied to %s entity.\n",
                        dxf_entity_name);
                text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_attrib_write_lowlevel () empty layer string for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to the default layer.\n",
                        dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (height == 0.0)
        {
                fprintf (stderr, "Warning in dxf_attrib_write_lowlevel () height has a value of 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default height of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                height = 1.0;
        }
        if (rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_attrib_write_lowlevel () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default relative X-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                rel_x_scale = 1.0;
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  1\n%s\n", value);
        fprintf (fp, "  2\n%s\n", tag_value);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        if (strcmp (text_style, "STANDARD") != 0)
        {
                fprintf (fp, "  7\n%s\n", text_style);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        if ((hor_align != 0) || (vert_align != 0))
        {
                if ((x0 == x1) && (y0 == y1) && (z0 == z1))
                {
                        fprintf (stderr, "Warning in dxf_attrib_write_lowlevel () insertion point and alignment point are identical for the %s entity with id-code: %x.\n",
                                dxf_entity_name, id_code);
                        fprintf (stderr, "    default justification applied to %s entity\n",
                                dxf_entity_name);
                        hor_align = 0;
                        vert_align = 0;
                }
                else
                {
                        fprintf (fp, " 11\n%f\n", x1);
                        fprintf (fp, " 21\n%f\n", y1);
                        fprintf (fp, " 31\n%f\n", z1);
                }
        }
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        fprintf (fp, " 40\n%f\n", height);
        if (rel_x_scale != 1.0)
        {
                fprintf (fp, " 41\n%f\n", rel_x_scale);
        }
        if (rot_angle != 0.0)
        {
                fprintf (fp, " 50\n%f\n", rot_angle);
        }
        if (obl_angle != 0.0)
        {
                fprintf (fp, " 51\n%f\n", obl_angle);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", attr_flags);
        if (text_flags != 0)
        {
                fprintf (fp, " 71\n%d\n", text_flags);
        }
        if (hor_align != 0)
        {
                fprintf (fp, " 72\n%d\n", hor_align);
        }
        if (field_length != 0)
        {
                fprintf (fp, " 73\n%d\n", field_length);
        }
        if (vert_align != 0)
        {
                fprintf (fp, " 74\n%d\n", vert_align);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attrib_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a DXF \c ATTRIB entity.
 */
int
dxf_attrib_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfAttrib dxf_attrib
                /*!< DXF attribute entity */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attrib_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("ATTRIB");
        if (strcmp (dxf_attrib.value, "") == 0)
        {
                fprintf (stderr, "Error in dxf_attrib_write () default value string is empty for the %s entity with id-code: %x.\n",
                         dxf_entity_name, dxf_attrib.common.id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attrib.tag_value, "") == 0)
        {
                fprintf (stderr, "Error in dxf_attrib_write () tag value string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attrib.common.id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attrib.text_style, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_attrib_write () text style string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attrib.common.id_code);
                fprintf (stderr, "    default text style STANDARD applied to %s entity.\n",
                        dxf_entity_name);
                dxf_attrib.text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (dxf_attrib.common.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_attrib_write () empty layer string for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attrib.common.id_code);
                fprintf (stderr, "    %s entity is relocated to the default layer.\n",
                        dxf_entity_name);
                dxf_attrib.common.layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_attrib.height == 0.0)
        {
                fprintf (stderr, "Warning in dxf_attrib_write () height has a value of 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attrib.common.id_code);
                fprintf (stderr, "    default height of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_attrib.height = 1.0;
        }
        if (dxf_attrib.rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_attrib_write () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attrib.common.id_code);
                fprintf (stderr, "    default relative X-scale of 1.0 applied to %s entity.\n", dxf_entity_name);
                dxf_attrib.rel_x_scale = 1.0;
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  1\n%s\n", dxf_attrib.value);
        fprintf (fp, "  2\n%s\n", dxf_attrib.tag_value);
        if (dxf_attrib.common.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_attrib.common.id_code);
        }
        if (strcmp (dxf_attrib.common.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_attrib.common.linetype);
        }
        if (strcmp (dxf_attrib.text_style, "STANDARD") != 0)
        {
                fprintf (fp, "  7\n%s\n", dxf_attrib.text_style);
        }
        fprintf (fp, "  8\n%s\n", dxf_attrib.common.layer);
        fprintf (fp, " 10\n%f\n", dxf_attrib.x0);
        fprintf (fp, " 20\n%f\n", dxf_attrib.y0);
        fprintf (fp, " 30\n%f\n", dxf_attrib.z0);
        if ((dxf_attrib.hor_align != 0) || (dxf_attrib.vert_align != 0))
        {
                if ((dxf_attrib.x0 == dxf_attrib.x1)
                        && (dxf_attrib.y0 == dxf_attrib.y1)
                        && (dxf_attrib.z0 == dxf_attrib.z1))
                {
                        fprintf (stderr, "Warning in dxf_attrib_write () insertion point and alignment point are identical for the %s entity with id-code: %x.\n",
                                dxf_entity_name, dxf_attrib.common.id_code);
                        fprintf (stderr, "    default justification applied to %s entity\n",
                                dxf_entity_name);
                        dxf_attrib.hor_align = 0;
                        dxf_attrib.vert_align = 0;
                }
                else
                {
                        fprintf (fp, " 11\n%f\n", dxf_attrib.x1);
                        fprintf (fp, " 21\n%f\n", dxf_attrib.y1);
                        fprintf (fp, " 31\n%f\n", dxf_attrib.z1);
                }
        }
        if (dxf_attrib.common.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_attrib.common.thickness);
        }
        fprintf (fp, " 40\n%f\n", dxf_attrib.height);
        if (dxf_attrib.rel_x_scale != 1.0)
        {
                fprintf (fp, " 41\n%f\n", dxf_attrib.rel_x_scale);
        }
        if (dxf_attrib.rot_angle != 0.0)
        {
                fprintf (fp, " 50\n%f\n", dxf_attrib.rot_angle);
        }
        if (dxf_attrib.obl_angle != 0.0)
        {
                fprintf (fp, " 51\n%f\n", dxf_attrib.obl_angle);
        }
        if (dxf_attrib.common.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_attrib.common.color);
        }
        if (dxf_attrib.common.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", dxf_attrib.attr_flags);
        if (dxf_attrib.text_flags != 0)
        {
                fprintf (fp, " 71\n%d\n", dxf_attrib.text_flags);
        }
        if (dxf_attrib.hor_align != 0)
        {
                fprintf (fp, " 72\n%d\n", dxf_attrib.hor_align);
        }
        if (dxf_attrib.field_length != 0)
        {
                fprintf (fp, " 73\n%d\n", dxf_attrib.field_length);
        }
        if (dxf_attrib.vert_align != 0)
        {
                fprintf (fp, " 74\n%d\n", dxf_attrib.vert_align);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attrib_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ATTRIB and all it's
 * data fields.
 */
int
dxf_attrib_free
(
        DxfAttrib *dxf_attrib
                /*!< DXF \c ATTRIB entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attrib_free () function.\n",
                __FILE__, __LINE__);
#endif
        free (dxf_attrib->common.linetype);
        free (dxf_attrib->common.layer);
        free (dxf_attrib->value);
        free (dxf_attrib->tag_value);
        free (dxf_attrib->text_style);
        free (dxf_attrib);
        dxf_attrib = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attrib_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
