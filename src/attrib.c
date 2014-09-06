/*!
 * \file attrib.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        DXF_DEBUG_BEGIN
#endif
        DxfAttrib *dxf_attrib = NULL;
        size_t size;

        size = sizeof (DxfAttrib);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_attrib = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfAttrib struct.\n")),
                  __FUNCTION__);
                dxf_attrib = NULL;
        }
        else
        {
                memset (dxf_attrib, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
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
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_attrib == NULL)
        {
                fprintf (stderr,
                  (_("WARNING in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_attrib = dxf_attrib_new ();
        }
        if (dxf_attrib == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfAttrib struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_attrib->value = strdup ("");
        dxf_attrib->tag_value = strdup ("");
        dxf_attrib->id_code = 0;
        dxf_attrib->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_attrib->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        dxf_attrib->layer = strdup (DXF_DEFAULT_LAYER);
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
        dxf_attrib->thickness = 0.0;
        dxf_attrib->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_attrib->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_attrib->color = DXF_COLOR_BYLAYER;
        dxf_attrib->paperspace = DXF_MODELSPACE;
        dxf_attrib->attr_flags = 0;
        dxf_attrib->text_flags = 0;
        dxf_attrib->hor_align = 0;
        dxf_attrib->field_length = 0;
        dxf_attrib->vert_align = 0;
        dxf_attrib->extr_x0 = 0.0;
        dxf_attrib->extr_y0 = 0.0;
        dxf_attrib->extr_z0 = 0.0;
        dxf_attrib->dictionary_owner_soft = strdup("");
        dxf_attrib->line_weight = 0;
        dxf_attrib->next = NULL;
#if DEBUG
        DXF_DEBUG_END
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
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAttrib *dxf_attrib
                /*!< DXF attrib entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_attrib == NULL)
        {
                fprintf (stderr,
                  (_("WARNING in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_attrib = dxf_attrib_new ();
                dxf_attrib_init (dxf_attrib);
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
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing the attribute
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attrib->value);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a tag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attrib->tag_value);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_attrib->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attrib->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attrib->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_attrib->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the align point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_attrib->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->rel_x_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->obl_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_attrib->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attrib->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attrib->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * attribute flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attrib->attr_flags);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * text flags value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attrib->text_flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the
                         * horizontal alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attrib->hor_align);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the
                         * field length value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attrib->field_length);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the
                         * vertical alignment value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_attrib->vert_align);
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
                                  (_("Error in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attrib->extr_z0);
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
        /* Handle ommitted members and/or illegal values. */
        if (strcmp (dxf_attrib->linetype, "") == 0)
        {
                dxf_attrib->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_attrib->layer, "") == 0)
        {
                dxf_attrib->layer = strdup (DXF_DEFAULT_LAYER);
        }
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
        DxfAttrib *dxf_attrib
                /*!< DXF attribute entity */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ATTRIB");

        /* Do some basic checks. */
        if (dxf_attrib == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attrib->value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () default value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib->id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attrib->tag_value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () tag value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib->id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attrib->text_style, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () text style string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib->id_code);
                fprintf (stderr,
                  (_("    default text style STANDARD applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_attrib->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (dxf_attrib->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib->id_code);
                fprintf (stderr,
                  (_("    %s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_attrib->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_attrib->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to the default layer.\n")),
                  dxf_entity_name);
                dxf_attrib->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_attrib->height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () height has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib->id_code);
                fprintf (stderr,
                  (_("    default height of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_attrib->height = 1.0;
        }
        if (dxf_attrib->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attrib->id_code);
                fprintf (stderr,
                  (_("    default relative X-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_attrib->rel_x_scale = 1.0;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_attrib->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_attrib->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "330\n%s\n", dxf_attrib->dictionary_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_attrib->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_attrib->layer);
        if (strcmp (dxf_attrib->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_attrib->linetype);
        }
        if (dxf_attrib->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_attrib->color);
        }
        if (dxf_attrib->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_attrib->linetype_scale);
        }
        if (dxf_attrib->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_attrib->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        if (dxf_attrib->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_attrib->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_attrib->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_attrib->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_attrib->z0);
        fprintf (fp->fp, " 40\n%f\n", dxf_attrib->height);
        fprintf (fp->fp, "  1\n%s\n", dxf_attrib->value);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbAttribute\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_attrib->tag_value);
        fprintf (fp->fp, " 70\n%d\n", dxf_attrib->attr_flags);
        if (dxf_attrib->field_length != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", dxf_attrib->field_length);
        }
        if (dxf_attrib->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", dxf_attrib->rot_angle);
        }
        if (dxf_attrib->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", dxf_attrib->rel_x_scale);
        }
        if (dxf_attrib->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", dxf_attrib->obl_angle);
        }
        if (strcmp (dxf_attrib->text_style, "STANDARD") != 0)
        {
                fprintf (fp->fp, "  7\n%s\n", dxf_attrib->text_style);
        }
        if (dxf_attrib->text_flags != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", dxf_attrib->text_flags);
        }
        if (dxf_attrib->hor_align != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", dxf_attrib->hor_align);
        }
        if (dxf_attrib->vert_align != 0)
        {
                fprintf (fp->fp, " 74\n%d\n", dxf_attrib->vert_align);
        }
        if ((dxf_attrib->hor_align != 0) || (dxf_attrib->vert_align != 0))
        {
                if ((dxf_attrib->x0 == dxf_attrib->x1)
                        && (dxf_attrib->y0 == dxf_attrib->y1)
                        && (dxf_attrib->z0 == dxf_attrib->z1))
                {
                        fprintf (stderr,
                          (_("Warning in %s () insertion point and alignment point are identical for the %s entity with id-code: %x.\n")),
                          __FUNCTION__, dxf_entity_name, dxf_attrib->id_code);
                        fprintf (stderr,
                          (_("    default justification applied to %s entity\n")),
                          dxf_entity_name);
                        dxf_attrib->hor_align = 0;
                        dxf_attrib->vert_align = 0;
                }
                else
                {
                        fprintf (fp->fp, " 11\n%f\n", dxf_attrib->x1);
                        fprintf (fp->fp, " 21\n%f\n", dxf_attrib->y1);
                        fprintf (fp->fp, " 31\n%f\n", dxf_attrib->z1);
                }
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (dxf_attrib->extr_x0 != 0.0)
                && (dxf_attrib->extr_y0 != 0.0)
                && (dxf_attrib->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", dxf_attrib->extr_x0);
                fprintf (fp->fp, "220\n%f\n", dxf_attrib->extr_y0);
                fprintf (fp->fp, "230\n%f\n", dxf_attrib->extr_z0);
        }
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
        DxfAttrib *dxf_attrib
                /*!< DXF \c ATTRIB entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_attrib->next != NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () pointer to next DxfAttrib was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_attrib->linetype);
        free (dxf_attrib->layer);
        free (dxf_attrib->value);
        free (dxf_attrib->tag_value);
        free (dxf_attrib->text_style);
        free (dxf_attrib->dictionary_owner_soft);
        free (dxf_attrib);
        dxf_attrib = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
