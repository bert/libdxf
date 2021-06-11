/*!
 * \file insert.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2017, 2018, 2019,
 * 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF insert entity (\c INSERT).
 *
 * A DXF \c INSERT entity is an insertion for a (external) \c BLOCK entity.\n
 * Whilst a \c BLOCK only resides in the block table only once as a
 * definition, an \c INSERT entity can insert blocks as singlular entities
 * and also as [rectanglar, polar] arrays in the drawing.
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


#include "insert.h"


/*!
 * \brief Allocate memory for a \c DxfInsert.
 *
 * Fill the memory contents with zeros.
 */
DxfInsert *
dxf_insert_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfInsert *insert = NULL;
        size_t size;

        size = sizeof (DxfInsert);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((insert = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                insert = NULL;
        }
        else
        {
                memset (insert, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c INSERT entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfInsert *
dxf_insert_init
(
        DxfInsert *insert
                /*!< DXF insert entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                insert = dxf_insert_new ();
        }
        if (insert == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        insert->id_code = 0;
        insert->linetype = strdup (DXF_DEFAULT_LINETYPE);
        insert->layer = strdup (DXF_DEFAULT_LAYER);
        insert->elevation = 0.0;
        insert->thickness = 0.0;
        insert->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        insert->visibility = DXF_DEFAULT_VISIBILITY;
        insert->color = DXF_COLOR_BYLAYER;
        insert->paperspace = DXF_MODELSPACE;
        insert->graphics_data_size = 0;
        insert->shadow_mode = 0;
        insert->dictionary_owner_soft = strdup ("");
        insert->material = strdup ("");
        insert->dictionary_owner_hard = strdup ("");
        insert->lineweight = 0.0;
        insert->plot_style_name = strdup ("");
        insert->color_value = 0;
        insert->color_name = strdup ("");
        insert->transparency = 0;
        insert->block_name = strdup ("");
        insert->rel_x_scale = 1.0;
        insert->rel_y_scale = 1.0;
        insert->rel_z_scale = 1.0;
        insert->column_spacing = 0.0;
        insert->row_spacing = 0.0;
        insert->rot_angle = 0.0;
        insert->attributes_follow = 0;
        insert->columns = 0;
        insert->rows = 0;
        insert->extr_x0 = 0.0;
        insert->extr_y0 = 0.0;
        insert->extr_z0 = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        insert->binary_graphics_data = NULL;
        insert->p0 = NULL;
        insert->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Read data from a DXF file into an \c INSERT entity.
 *
 * The last line read from file contained the string "INSERT". \n
 * Now follows some data for the \c INSERT, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c insert. \n
 *
 * \return a pointer to \c insert.
 */
DxfInsert *
dxf_insert_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfInsert *insert
                /*!< DXF insert entity. */
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
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                insert = dxf_insert_init (insert);
        }
        if (insert->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                insert->binary_graphics_data = (DxfBinaryData *) dxf_binary_data_init (insert->binary_graphics_data);
                if (insert->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (insert->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                insert->p0 = dxf_point_init (insert->p0);
                if (insert->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
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
                        /* Now follows a string containing a block name
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, insert->block_name);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &insert->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, insert->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, insert->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->p0->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (insert->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->thickness);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->rel_x_scale);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * relative Y-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->rel_y_scale);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * relative Z-scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->rel_z_scale);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the
                         * column spacing. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->column_spacing);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing the
                         * row spacing. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->row_spacing);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->rot_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &insert->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &insert->color);
                }
                else if (strcmp (temp_string, "66") == 0)
                {
                        /* Now follows a string containing the
                         * attributes follow flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &insert->attributes_follow);
                        /*!
                         * \todo After a set attributes_follow flag is
                         * detected, parsing of following entities should
                         * be implemented until the end of sequence
                         * marker (\c SEQEND) is encountered. */
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &insert->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * number of columns. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &insert->columns);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * number of rows. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &insert->rows);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbBlockReference") != 0))
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
                        fscanf (fp->fp, "%lf\n", &insert->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &insert->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, insert->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, insert->dictionary_owner_hard);
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
        if (strcmp (insert->linetype, "") == 0)
        {
                insert->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (insert->layer, "") == 0)
        {
                insert->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Write DXF output for a DXF \c INSERT entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_insert_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfInsert *insert
                /*!< DXF insert entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("INSERT");

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
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (insert->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, insert->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                insert->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (insert->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, insert->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0.\n")),
                  dxf_entity_name);
                insert->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (insert->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, insert->id_code);
                fprintf (stderr,
                  (_("\tdefault relative X-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                insert->rel_x_scale = 1.0;
        }
        if (insert->rel_y_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative Y-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, insert->id_code);
                fprintf (stderr,
                  (_("\tdefault relative Y-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                insert->rel_y_scale = 1.0;
        }
        if (insert->rel_z_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () relative Z-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, insert->id_code);
                fprintf (stderr,
                  (_("\tdefault relative Z-scale of 1.0 applied to %s entity.\n")),
                  dxf_entity_name);
                insert->rel_z_scale = 1.0;
        }
        if ((insert->columns > 1)
          && (insert->column_spacing == 0.0))
        {
                fprintf (stderr,
                  (_("Warning in %s () number of columns is greater than 1 and the column spacing has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, insert->id_code);
                fprintf (stderr,
                  (_("\tdefault number of columns value of 1 applied to %s entity.\n")),
                  dxf_entity_name);
                insert->columns = 1;
        }
        if ((insert->rows > 1)
          && (insert->row_spacing == 0.0))
        {
                fprintf (stderr,
                  (_("Warning in %s () number of rows is greater than 1 and the row spacing has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, insert->id_code);
                fprintf (stderr,
                  (_("\tdefault number of rows value of 1 applied to %s entity.\n")),
                  dxf_entity_name);
                insert->rows = 1;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (insert->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", insert->id_code);
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
        if ((strcmp (insert->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", insert->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (insert->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", insert->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (insert->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", insert->layer);
        if (strcmp (insert->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", insert->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (insert->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", insert->elevation);
        }
        if (insert->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", insert->thickness);
        }
        if (insert->color!= DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", insert->color);
        }
        if (insert->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", insert->linetype_scale);
        }
        if (insert->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", insert->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbBlockReference\n");
        }
        if (insert->attributes_follow != 0)
        {
                fprintf (fp->fp, " 66\n%d\n", insert->attributes_follow);
                /*!
                 * \todo After a set attributes_follow flag is
                 * detected, the writing of following entities should
                 * be implemented and an end of sequence
                 * marker (\c SEQEND) written. */
        }
        fprintf (fp->fp, "  2\n%s\n", insert->block_name);
        fprintf (fp->fp, " 10\n%f\n", insert->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", insert->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", insert->p0->z0);
        if (insert->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", insert->rel_x_scale);
        }
        if (insert->rel_y_scale != 1.0)
        {
                fprintf (fp->fp, " 42\n%f\n", insert->rel_y_scale);
        }
        if (insert->rel_z_scale != 1.0)
        {
                fprintf (fp->fp, " 43\n%f\n", insert->rel_z_scale);
        }
        if (insert->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", insert->rot_angle);
        }
        if (insert->columns > 1)
        {
                fprintf (fp->fp, " 70\n%d\n", insert->columns);
        }
        if (insert->rows > 1)
        {
                fprintf (fp->fp, " 71\n%d\n", insert->rows);
        }
        if ((insert->columns > 1)
          && (insert->column_spacing > 0.0))
        {
                fprintf (fp->fp, " 44\n%f\n", insert->column_spacing);
        }
        if ((insert->rows > 1)
          && (insert->row_spacing > 0.0))
        {
                fprintf (fp->fp, " 45\n%f\n", insert->row_spacing);
        }
        if (fp->acad_version_number >= AutoCAD_12)
        {
                fprintf (fp->fp, "210\n%f\n", insert->extr_x0);
                fprintf (fp->fp, "220\n%f\n", insert->extr_y0);
                fprintf (fp->fp, "230\n%f\n", insert->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c INSERT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_insert_free
(
        DxfInsert *insert
                /*!< Pointer to the memory occupied by the DXF \c INSERT
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (insert->linetype);
        free (insert->layer);
        dxf_binary_data_free_list (insert->binary_graphics_data);
        free (insert->dictionary_owner_soft);
        free (insert->material);
        free (insert->dictionary_owner_hard);
        free (insert->plot_style_name);
        free (insert->color_name);
        free (insert->block_name);
        dxf_point_free_list (insert->p0);
        free (insert);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c INSERT entities and all their data fields.
 */
void
dxf_insert_free_list
(
        DxfInsert *inserts
                /*!< pointer to the single linked list of DXF \c INSERT
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (inserts == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (inserts != NULL)
        {
                DxfInsert *iter = (DxfInsert *) inserts->next;
                dxf_insert_free (inserts);
                inserts = (DxfInsert *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c INSERT entity.
 *
 * \return ID code.
 */
int
dxf_insert_get_id_code
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_id_code
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
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
        if (insert == NULL)
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
        insert->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the linetype from a DXF \c INSERT entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_insert_get_linetype
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (insert->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_linetype
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the layer from a DXF \c INSERT entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_insert_get_layer
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (insert->layer));
}


/*!
 * \brief Set the layer for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_layer
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the elevation from a DXF \c INSERT entity.
 *
 * \return elevation.
 */
double
dxf_insert_get_elevation
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_elevation
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the thickness from a DXF \c INSERT entity.
 *
 * \return thickness.
 */
double
dxf_insert_get_thickness
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_thickness
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the linetype scale from a DXF \c INSERT entity.
 *
 * \return linetype scale.
 */
double
dxf_insert_get_linetype_scale
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_linetype_scale
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the visibility from a DXF \c INSERT entity.
 *
 * \return visibility.
 */
int16_t
dxf_insert_get_visibility
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_visibility
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the color from a DXF \c INSERT entity.
 *
 * \return color.
 */
int
dxf_insert_get_color
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->color);
}


/*!
 * \brief Set the color for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_color
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c INSERT entity.
 *
 * \return paperspace flag value.
 */
int
dxf_insert_get_paperspace
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (insert->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_paperspace
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c INSERT
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_insert_get_graphics_data_size
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (insert->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c INSERT
 * entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_graphics_data_size
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        insert->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c INSERT entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_insert_get_shadow_mode
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_shadow_mode
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c INSERT entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_insert_get_binary_graphics_data
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) insert->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_binary_graphics_data
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c INSERT entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_insert_get_dictionary_owner_soft
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (insert->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_dictionary_owner_soft
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c INSERT entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_insert_get_material
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (insert->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_material
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c INSERT entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_insert_get_dictionary_owner_hard
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (insert->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_dictionary_owner_hard
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the \c lineweight from a DXF \c INSERT entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_insert_get_lineweight
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_lineweight
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c INSERT entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_insert_get_plot_style_name
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (insert->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_plot_style_name
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the \c color_value from a DXF \c INSERT entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_insert_get_color_value
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_color_value
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the \c color_name from a DXF \c INSERT entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_insert_get_color_name
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (insert->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_color_name
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the \c transparency from a DXF \c INSERT entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_insert_get_transparency
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_transparency
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the \c block_name from a DXF \c INSERT entity.
 *
 * \return \c block_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_insert_get_block_name
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->block_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (insert->block_name));
}


/*!
 * \brief Set the \c block_name for a DXF \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_block_name
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        char *block_name
                /*!< a string containing the \c block_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->block_name = strdup (block_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the base point \c p0 of a DXF \c INSERT entity.
 *
 * \return the base point \c p0.
 */
DxfPoint *
dxf_insert_get_p0
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->p0);
}


/*!
 * \brief Set the base point \c p0 of a DXF \c INSERT entity.
 *
 * \return a pointer to a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_p0
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the X-value of the base point \c x0 of a DXF \c INSERT
 * entity.
 *
 * \return the X-value of the base point \c x0.
 */
double
dxf_insert_get_x0
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->p0->x0);
}


/*!
 * \brief Set the X-value of the base point \c x0 of a DXF \c INSERT
 * entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_x0
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double x0
                /*!< the X-value of the base point \c x0 of a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                insert->p0 = dxf_point_init (insert->p0);
                if (insert->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        insert->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the Y-value of the base point \c y0 of a DXF \c INSERT
 * entity.
 *
 * \return the Y-value of the base point \c y0.
 */
double
dxf_insert_get_y0
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->p0->y0);
}


/*!
 * \brief Set the Y-value of the base point \c y0 of a DXF \c INSERT
 * entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_y0
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double y0
                /*!< the Y-value of the base point \c y0 of a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                insert->p0 = dxf_point_init (insert->p0);
                if (insert->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        insert->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the Z-value of the base point \c z0 of a DXF \c INSERT
 * entity.
 *
 * \return the Z-value of the base point \c z0.
 */
double
dxf_insert_get_z0
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->p0->z0);
}


/*!
 * \brief Set the Z-value of the base point \c z0 of a DXF \c INSERT
 * entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_z0
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double z0
                /*!< the Z-value of the base point \c z0 of a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                insert->p0 = dxf_point_init (insert->p0);
                if (insert->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        insert->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the releative X scale factor \c rel_x_scale of a DXF
 * \c INSERT entity.
 *
 * \return the relative X scale factor \c rel_x_scale.
 */
double
dxf_insert_get_rel_x_scale
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->rel_x_scale);
}


/*!
 * \brief Set the relative X scale factor \c rel_x_scale of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_rel_x_scale
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double rel_x_scale
                /*!< the relative X scale factor \c rel_x_scale of a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        insert->rel_x_scale = rel_x_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the releative Y scale factor \c rel_y_scale of a DXF
 * \c INSERT entity.
 *
 * \return the relative Y scale factor \c rel_y_scale.
 */
double
dxf_insert_get_rel_y_scale
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->rel_y_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->rel_y_scale);
}


/*!
 * \brief Set the relative Y scale factor \c rel_y_scale of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_rel_y_scale
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double rel_y_scale
                /*!< the relative Y scale factor \c rel_y_scale of a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rel_y_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        insert->rel_y_scale = rel_y_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the releative Z scale factor \c rel_z_scale of a DXF
 * \c INSERT entity.
 *
 * \return the relative Z scale factor \c rel_z_scale.
 */
double
dxf_insert_get_rel_z_scale
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->rel_z_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->rel_z_scale);
}


/*!
 * \brief Set the relative Z scale factor \c rel_z_scale of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_rel_z_scale
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double rel_z_scale
                /*!< the relative Z scale factor \c rel_z_scale of a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rel_z_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        insert->rel_z_scale = rel_z_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the column spacing value \c column_spacing of a DXF
 * \c INSERT entity.
 *
 * \return the column spacing value \c column_spacing.
 */
double
dxf_insert_get_column_spacing
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->column_spacing < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->column_spacing);
}


/*!
 * \brief Set the column spacing value \c column_spacing of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_column_spacing
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double column_spacing
                /*!< the column spacing value \c column_spacing of a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (column_spacing < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        insert->column_spacing = column_spacing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the row spacing value \c row_spacing of a DXF
 * \c INSERT entity.
 *
 * \return the row spacing value \c row_spacing.
 */
double
dxf_insert_get_row_spacing
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->row_spacing < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->row_spacing);
}


/*!
 * \brief Set the row spacing value \c row_spacing of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_row_spacing
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double row_spacing
                /*!< the row spacing value \c row_spacing for a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (row_spacing < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        insert->row_spacing = row_spacing;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the rotation angle value \c rot_angle of a DXF
 * \c INSERT entity.
 *
 * \return the rotation angle value \c rot_angle.
 */
double
dxf_insert_get_rot_angle
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->rot_angle < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        /*! \todo We need to normalize the return value in the range 0.0
         * ... 360.0. */
        return (insert->rot_angle);
}


/*!
 * \brief Set the rotation angle value \c rot_angle of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_rot_angle
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double rot_angle
                /*!< the rotation angle value \c rot_angle for a DXF
                 * \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        if (rot_angle > 360.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        insert->rot_angle = rot_angle;
        /*! \todo We need to normalize the value in the range 0.0
         * ... 360.0 before returning. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the attributes follow \c attributes_follow from a DXF
 * \c INSERT entity.
 *
 * \return attributes follow \c attributes_follow value.
 */
int
dxf_insert_get_attributes_follow
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->attributes_follow < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->attributes_follow > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->attributes_follow);
}


/*!
 * \brief Set the attributes follow \c attributes_follow for a DXF
 * \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_attributes_follow
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int attributes_follow
                /*!< Attributes follow value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attributes_follow < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (attributes_follow > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->attributes_follow = attributes_follow;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the number of columns \c columns from a DXF \c INSERT
 * entity.
 *
 * \return number of columns \c columns.
 */
int
dxf_insert_get_columns
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->columns < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->columns);
}


/*!
 * \brief Set the number of columns \c columns for a DXF
 * \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_columns
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int columns
                /*!< Number of columns value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (columns < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->columns = columns;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the number of rows \c rows from a DXF \c INSERT
 * entity.
 *
 * \return number of rows \c rows.
 */
int
dxf_insert_get_rows
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (insert->rows < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->rows);
}


/*!
 * \brief Set the number of rows \c rows for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_rows
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        int rows
                /*!< Number of rows value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (rows < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->rows = rows;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c INSERT entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_insert_get_extr_x0
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_extr_x0
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c INSERT entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_insert_get_extr_y0
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_extr_y0
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c INSERT entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_insert_get_extr_z0
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c INSERT entity.
 *
 * \return a pointer to \c insert when successful, or \c NULL when an
 * error occurred.
 */
DxfInsert *
dxf_insert_set_extr_z0
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c INSERT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF
 * \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_extrusion_vector_from_point
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->extr_x0 = (double) point->x0;
        insert->extr_y0 = (double) point->y0;
        insert->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Set the extrusion vector for a DXF \c INSERT entity.
 */
DxfInsert *
dxf_insert_set_extrusion_vector
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
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
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        insert->extr_x0 = extr_x0;
        insert->extr_y0 = extr_y0;
        insert->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the pointer to the next \c INSERT entity from a DXF 
 * \c INSERT entity.
 *
 * \return pointer to the next \c INSERT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfInsert *
dxf_insert_get_next
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInsert *) insert->next);
}


/*!
 * \brief Set the pointer to the next \c INSERT for a DXF \c INSERT
 * entity.
 */
DxfInsert *
dxf_insert_set_next
(
        DxfInsert *insert,
                /*!< a pointer to a DXF \c INSERT entity. */
        DxfInsert *next
                /*!< a pointer to the next \c INSERT for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
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
        insert->next = (struct DxfInsert *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (insert);
}


/*!
 * \brief Get the pointer to the last \c INSERT entity from a linked
 * list of DXF \c INSERT entities.
 *
 * \return pointer to the last \c INSERT entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfInsert *
dxf_insert_get_last
(
        DxfInsert *insert
                /*!< a pointer to a DXF \c INSERT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (insert == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (insert->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfInsert *) insert);
        }
        DxfInsert *iter = (DxfInsert *) insert->next;
        while (iter->next != NULL)
        {
                iter = (DxfInsert *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInsert *) iter);
}


/* EOF */
