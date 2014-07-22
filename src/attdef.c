/*!
 * \file attdef.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        DxfAttdef *dxf_attdef = NULL;
        size_t size;

        size = sizeof (DxfAttdef);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_attdef = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfAttdef struct.\n")),
                  __FUNCTION__);
                dxf_attdef = NULL;
        }
        else
        {
                memset (dxf_attdef, 0, size);
        }
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
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
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        dxf_attdef = dxf_attdef_new ();
        if (dxf_attdef == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a DxfAttdef struct.\n")),
                __FUNCTION__);
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
        dxf_attdef->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_attdef->visibility = DXF_DEFAULT_VISIBILITY;
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
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
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
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
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
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
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
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_attdef->linetype_scale);
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
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_attdef->visibility);
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
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
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
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        char *dxf_entity_name = strdup ("ATTDEF");

        /* Do some basic checks. */
        if (dxf_attdef == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attdef->tag_value, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () default value string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attdef->id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_attdef->text_style, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () text style string is empty for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attdef->id_code);
                fprintf (stderr,
                  (_("    default text style STANDARD applied to %s entity.\n")),
                  dxf_entity_name);
                dxf_attdef->text_style = strdup (DXF_DEFAULT_TEXTSTYLE);
        }
        if (strcmp (dxf_attdef->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attdef->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_attdef->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_attdef->height == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () height has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attdef->id_code);
                fprintf (stderr,
                  (_("    default height of 1.0 applied to %s entity.\n")),
                    dxf_entity_name);
                dxf_attdef->height = 1.0;
        }
        if (dxf_attdef->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_attdef->id_code);
                fprintf (stderr, "    default relative X-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_attdef->rel_x_scale = 1.0;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_attdef->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_attdef->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_attdef->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_attdef->layer);
        if (strcmp (dxf_attdef->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_attdef->linetype);
        }
        if (dxf_attdef->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_attdef->color);
        }
        if (dxf_attdef->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_attdef->linetype_scale);
        }
        if (dxf_attdef->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_attdef->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        if (dxf_attdef->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_attdef->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_attdef->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_attdef->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_attdef->z0);
        fprintf (fp->fp, " 40\n%f\n", dxf_attdef->height);
        fprintf (fp->fp, "  1\n%s\n", dxf_attdef->default_value);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbAttributeDefinition\n");
        }
        fprintf (fp->fp, "  3\n%s\n", dxf_attdef->prompt_value);
        fprintf (fp->fp, "  2\n%s\n", dxf_attdef->tag_value);
        fprintf (fp->fp, " 70\n%d\n", dxf_attdef->attr_flags);
        if (dxf_attdef->field_length != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", dxf_attdef->field_length);
        }
        if (dxf_attdef->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", dxf_attdef->rot_angle);
        }
        if (dxf_attdef->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", dxf_attdef->rel_x_scale);
        }
        if (dxf_attdef->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", dxf_attdef->obl_angle);
        }
        if (strcmp (dxf_attdef->text_style, "STANDARD") != 0)
        {
                fprintf (fp->fp, "  7\n%s\n", dxf_attdef->text_style);
        }
        if (dxf_attdef->text_flags != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", dxf_attdef->text_flags);
        }
        if (dxf_attdef->hor_align != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", dxf_attdef->hor_align);
        }
        if (dxf_attdef->vert_align != 0)
        {
                fprintf (fp->fp, " 74\n%d\n", dxf_attdef->vert_align);
        }
        if ((dxf_attdef->hor_align != 0) || (dxf_attdef->vert_align != 0))
        {
                if ((dxf_attdef->x0 == dxf_attdef->x1)
                        && (dxf_attdef->y0 == dxf_attdef->y1)
                        && (dxf_attdef->z0 == dxf_attdef->z1))
                {
                        fprintf (stderr,
                          (_("Warning in %s () insertion point and alignment point are identical for the %s entity with id-code: %x.\n")),
                          __FUNCTION__, dxf_entity_name, dxf_attdef->id_code);
                        fprintf (stderr,
                          (_("    default justification applied to %s entity.\n")),
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
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
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
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        if (dxf_attdef->next != NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () pointer to next DxfAttdef was not NULL.\n")),
                __FUNCTION__);
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
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
