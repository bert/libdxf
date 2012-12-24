/*!
 * \file attdef.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF attribute definition entity (\c ATTDEF).
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
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attdef_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfAttdef *dxf_attdef = NULL;
        size_t size;

        size = sizeof (DxfAttdef);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_attdef = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_attdef_new () could not allocate memory for a DxfAttdef struct.\n");
                dxf_attdef = NULL;
        }
        else
        {
                memset (dxf_attdef, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attdef_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_attdef);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c ATTDEF entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfAttdef *
dxf_attdef_init
(
        DxfAttdef *dxf_attdef
                /*!< DXF attdef entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attdef_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_attdef = dxf_attdef_new ();
        if (dxf_attdef == NULL)
        {
              fprintf (stderr, "ERROR in dxf_attdef_init () could not allocate memory for a DxfAttdef struct.\n");
              return (NULL);
        }
        dxf_attdef->default_value = strdup ("");
        dxf_attdef->tag_value = strdup ("");
        dxf_attdef->prompt_value = strdup ("");
        dxf_attdef->id_code = 0;
        dxf_attdef->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_attdef->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        dxf_attdef->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_attdef->x0 = 0.0;
        dxf_attdef->y0 = 0.0;
        dxf_attdef->z0 = 0.0;
        dxf_attdef->x1 = 0.0;
        dxf_attdef->y1 = 0.0;
        dxf_attdef->z1 = 0.0;
        dxf_attdef->height = 0.0;
        dxf_attdef->rel_x_scale = 0.0;
        dxf_attdef->rot_angle = 0.0;
        dxf_attdef->obl_angle = 0.0;
        dxf_attdef->thickness = 0.0;
        dxf_attdef->color = DXF_COLOR_BYLAYER;
        dxf_attdef->paperspace = DXF_MODELSPACE;
        dxf_attdef->attr_flags = 0;
        dxf_attdef->text_flags = 0;
        dxf_attdef->hor_align = 0;
        dxf_attdef->field_length = 0;
        dxf_attdef->vert_align = 0;
        dxf_attdef->extr_x0 = 0.0;
        dxf_attdef->extr_y0 = 0.0;
        dxf_attdef->extr_z0 = 0.0;
        dxf_attdef->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attdef_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_attdef);
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
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_attdef_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAttdef *dxf_attdef
                /*!< DXF attdef entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attdef_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_attdef)
        {
                dxf_attdef = dxf_attdef_new ();
        }
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr, "Error in dxf_attdef_read () while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing the attribute
                         * default value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attdef->default_value);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a tag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attdef->tag_value);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a prompt
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attdef->prompt_value);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_attdef->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attdef->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attdef->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attdef->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_attdef->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->rel_x_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->obl_angle);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attdef->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attdef->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * attribute flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attdef->attr_flags);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attdef->text_flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attdef->hor_align);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * field length value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attdef->field_length);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the
                         * vertical alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attdef->vert_align);
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
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbText") != 0)
                        && (strcmp (temp_string, "AcDbAttributeDefinition") != 0))
                        {
                                fprintf (stderr, "Error in dxf_attdef_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->extr_z0);
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
                        fprintf (stderr, "Warning: in dxf_attdef_read () unknown string tag found while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attdef_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a attribute definition entity.
 */
int
dxf_attdef_write_lowlevel
(
        FILE *fp,
                /*!< File pointer to output file (or device). */
        int id_code,
                /*!< Identification number for the entity.\n
                 * this is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *default_value,
                /*!< Default value for the attribute.\n
                 * Group code = 1. */
        char *tag_value,
                /*!< Tagname for the attribute.\n
                 * Group code = 2. */
        char *prompt_value,
                /*!< Prompt text for the value to be stored in the attribute.\n
                 * Group code = 3. */
        char *linetype,
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *text_style,
                /*!< The style used for the presentation of the value of the
                 * attribute.\n
                 * Defaults to \c STANDARD if  ommitted in the DXF file.\n
                 * Group code = 7. */
        char *layer,
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double x0,
                /*!< X-value of the starting point coordinate.\n
                 * Group code = 10. */
        double y0,
                /*!< Y-value of the starting point coordinate.\n
                 * Group code = 20. */
        double z0,
                /*!< Z-value of the starting point coordinate.\n
                 * Group code = 30. */
        double x1,
                /*!< X-value of the alignment point coordinate.\n
                 * Group code = 11. */
        double y1,
                /*!< Y-value of the alignment point coordinate.\n
                 * Group code = 21. */
        double z1,
                /*!< Z-value of the alignment point coordinate.\n
                 * Group code = 31. */
        double extr_x0,
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0,
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0,
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file.\n
                 * Group code = 230. */
        double thickness,
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double height,
                /*!< Character height of the attribute value.\n
                 * Group code = 40. */
        double rel_x_scale,
                /*!< Relative scale in the X-direction.\n
                 * Defaults to 1.0 if ommitted from DXF file.\n
                 * Group code = 41. */
        double rot_angle,
                /*!< Rotation angle of the attribute value.\n
                 * Defaults to 0.0 if ommitted from DXF file.\n
                 * Group code = 50. */
        double obl_angle,
                /*!< Oblique angle of the attribute value.\n
                 * Defaults to 0.0 if ommitted from DXF file.\n
                 * Group code = 51. */
        int color,
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace,
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Defaults to \c MODELSPACE if ommitted in the DXF file.\n
                 * Group code = 67. */
        int attr_flags,
                /*!< Attribute flags.\n
                 * Bit coded:\n
                 * 1 = attribute is invisible (does not display).\n
                 * 2 = this is a constant attribute.\n
                 * 4 = verification is required on input of this attribute.\n
                 * 8 = attribute is preset (no prompt during insertion).\n
                 * Group code = 70. */
        int text_flags,
                /*!< Text flags.\n
                 * Bit coded:\n
                 * 2 = text is backward (mirrored in X).\n
                 * 4 = text is upside down (mirrored in Y).\n
                 * Defaults to 0 if ommited from DXF file.\n
                 * Group code = 71. */
        int hor_align,
                /*!< Horizontal alignment.\n
                 * Bit coded:\n
                 * 0 = left.\n
                 * 1 = center.\n
                 * 2 = right.\n
                 * 3 = aligned, only when vert_align = 0.\n
                 * 4 = middle, only when vert_align = 0.\n
                 * 5 = fit, only when vert_align = 0. \n
                 * Defaults to 0 if ommitted from DXF file.\n
                 * Group code = 72. */
        int field_length,
                /*!< Field length.\n
                 * Defaults to 0 if ommitted from DXF file.\n
                 * Group code = 73. */
        int vert_align,
                /*!< Vertical alignment.\n
                 * Bit coded:\n
                 * 0 = baseline.\n
                 * 1 = bottom.\n
                 * 2 = middle.\n
                 * 3 = top.\n
                 * Defaults to 0 if ommitted from DXF file.\n
                 * Group code = 74. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attdef_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("ATTDEF");
        if (strcmp (tag_value, "") == 0)
        {
                fprintf (stderr, "Error in dxf_attdef_write_lowlevel () default value string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (text_style, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_attdef_write_lowlevel () text style string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default text style STANDARD applied to %s entity.\n",
                        dxf_entity_name);
                text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_attdef_write_lowlevel () empty layer string for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to default layer.\n",
                        dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (height == 0.0)
        {
                fprintf (stderr, "Warning in dxf_attdef_write_lowlevel () height has a value of 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default height of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                height = 1.0;
        }
        if (rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_attdef_write_lowlevel () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default relative X-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                rel_x_scale = 1.0;
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  1\n%s\n", default_value);
        fprintf (fp, "  2\n%s\n", tag_value);
        fprintf (fp, "  3\n%s\n", prompt_value);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (acad_version_number >= AutoCAD_13)
        {
                fprintf (fp, "100\nAcDbEntity\n");
                fprintf (fp, "100\nAcDbText\n");
                fprintf (fp, "100\nAcDbAttributeDefinition\n");
        }
        if (strcmp (linetype, "BYLAYER") != 0)
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
                        fprintf (stderr, "Warning in dxf_attdef_write_lowlevel () insertion point and alignment point are identical for the attdef entity with id-code: %x\n",
                                id_code);
                        fprintf (stderr, "    default justification applied to %s entity.\n",
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
        if (acad_version_number >= AutoCAD_12)
        {
                fprintf (fp, "210\n%f\n", extr_x0);
                fprintf (fp, "220\n%f\n", extr_y0);
                fprintf (fp, "230\n%f\n", extr_z0);
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
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attdef_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a attribute definition entity.
 */
int
dxf_attdef_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfAttdef *dxf_attdef
                /*!< attribute definition entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attdef_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("ATTDEF");
        if (dxf_attdef == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr, "Error in dxf_attdef_write () a NULL pointer was passed.\n");
        }
        if (strcmp (dxf_attdef->tag_value, "") == 0)
        {
                fprintf (stderr, "Error in dxf_attdef_write () default value string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attdef->id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attdef->text_style, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_attdef_write () text style string is empty for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attdef->id_code);
                fprintf (stderr, "    default text style STANDARD applied to %s entity.\n",
                        dxf_entity_name);
                dxf_attdef->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (dxf_attdef->layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_attdef_write () empty layer string for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attdef->id_code);
                fprintf (stderr, "    %s entity is relocated to the default layer.\n",
                        dxf_entity_name);
                dxf_attdef->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_attdef->height == 0.0)
        {
                fprintf (stderr, "Warning in dxf_attdef_write () height has a value of 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attdef->id_code);
                fprintf (stderr, "    default height of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_attdef->height = 1.0;
        }
        if (dxf_attdef->rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_attdef_write () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_attdef->id_code);
                fprintf (stderr, "    default relative X-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_attdef->rel_x_scale = 1.0;
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp->fp, "  1\n%s\n", dxf_attdef->default_value);
        fprintf (fp->fp, "  2\n%s\n", dxf_attdef->tag_value);
        fprintf (fp->fp, "  3\n%s\n", dxf_attdef->prompt_value);
        if (dxf_attdef->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_attdef->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
                fprintf (fp->fp, "100\nAcDbText\n");
                fprintf (fp->fp, "100\nAcDbAttributeDefinition\n");
        }
        if (strcmp (dxf_attdef->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_attdef->linetype);
        }
        if (strcmp (dxf_attdef->text_style, "STANDARD") != 0)
        {
                fprintf (fp->fp, "  7\n%s\n", dxf_attdef->text_style);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_attdef->layer);
        fprintf (fp->fp, " 10\n%f\n", dxf_attdef->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_attdef->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_attdef->z0);
        if ((dxf_attdef->hor_align != 0) || (dxf_attdef->vert_align != 0))
        {
                if ((dxf_attdef->x0 == dxf_attdef->x1)
                        && (dxf_attdef->y0 == dxf_attdef->y1)
                        && (dxf_attdef->z0 == dxf_attdef->z1))
                {
                        fprintf (stderr, "Warning in dxf_attdef_write () insertion point and alignment point are identical for the %s entity with id-code: %x.\n",
                                dxf_entity_name, dxf_attdef->id_code);
                        fprintf (stderr, "    default justification applied to %s entity.\n",
                                dxf_entity_name);
                        dxf_attdef->hor_align = 0;
                        dxf_attdef->vert_align = 0;
                }
                else
                {
                        fprintf (fp->fp, " 11\n%f\n", dxf_attdef->x1);
                        fprintf (fp->fp, " 21\n%f\n", dxf_attdef->y1);
                        fprintf (fp->fp, " 31\n%f\n", dxf_attdef->z1);
                }
        }
        if (fp->acad_version_number >= AutoCAD_12)
        {
                fprintf (fp->fp, "210\n%f\n", dxf_attdef->extr_x0);
                fprintf (fp->fp, "220\n%f\n", dxf_attdef->extr_y0);
                fprintf (fp->fp, "230\n%f\n", dxf_attdef->extr_z0);
        }
        if (dxf_attdef->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_attdef->thickness);
        }
        fprintf (fp->fp, " 40\n%f\n", dxf_attdef->height);
        if (dxf_attdef->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", dxf_attdef->rel_x_scale);
        }
        if (dxf_attdef->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", dxf_attdef->rot_angle);
        }
        if (dxf_attdef->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", dxf_attdef->obl_angle);
        }
        if (dxf_attdef->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_attdef->color);
        }
        if (dxf_attdef->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, " 70\n%d\n", dxf_attdef->attr_flags);
        if (dxf_attdef->text_flags != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", dxf_attdef->text_flags);
        }
        if (dxf_attdef->hor_align != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", dxf_attdef->hor_align);
        }
        if (dxf_attdef->field_length != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", dxf_attdef->field_length);
        }
        if (dxf_attdef->vert_align != 0)
        {
                fprintf (fp->fp, " 74\n%d\n", dxf_attdef->vert_align);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attdef_write () function.\n",
                __FILE__, __LINE__);
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
        DxfAttdef *dxf_attdef
                /*!< DXF \c ATTDEF entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_attdef_free () function.\n",
                __FILE__, __LINE__);
#endif
        if (dxf_attdef->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_attdef_free () pointer to next DxfAttdef was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_attdef->linetype);
        free (dxf_attdef->layer);
        free (dxf_attdef->default_value);
        free (dxf_attdef->tag_value);
        free (dxf_attdef->prompt_value);
        free (dxf_attdef->text_style);
        free (dxf_attdef);
        dxf_attdef = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_attdef_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
