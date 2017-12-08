/*!
 * \file text.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * allocated memory when succesful.
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
        text->text_value = strdup ("");
        text->linetype = strdup (DXF_DEFAULT_LINETYPE);
        text->text_style = strdup ("");
        text->layer = strdup (DXF_DEFAULT_LAYER);
        text->x0 = 0.0;
        text->y0 = 0.0;
        text->z0 = 0.0;
        text->x1 = 0.0;
        text->y1 = 0.0;
        text->z1 = 0.0;
        text->elevation = 0.0;
        text->thickness = 0.0;
        text->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        text->height = 0.0;
        text->rel_x_scale = 0.0;
        text->rot_angle = 0.0;
        text->obl_angle = 0.0;
        text->visibility = DXF_DEFAULT_VISIBILITY;
        text->color = DXF_COLOR_BYLAYER;
        text->paperspace = DXF_MODELSPACE;
        text->text_flags = 0;
        text->hor_align = 0;
        text->vert_align = 0;
        text->extr_x0 = 0.0;
        text->extr_y0 = 0.0;
        text->extr_z0 = 0.0;
        text->dictionary_owner_soft = strdup ("");
        text->dictionary_owner_hard = strdup ("");
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
                text = dxf_text_new ();
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
                        fscanf (fp->fp, "%s\n", text->text_value);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &text->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", text->linetype);
                }
                else if (strcmp (temp_string, "7") == 0)
                {
                        /* Now follows a string containing a text style
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", text->text_style);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", text->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &text->z0);
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
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbText") != 0)))
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
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", text->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", text->dictionary_owner_hard);
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
                fprintf (fp->fp, " 67\n%d\n", text->paperspace);
        }
        fprintf (fp->fp, "  8\n%s\n", text->layer);
        if (strcmp (text->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", text->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (text->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", text->elevation);
        }
        if (text->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", text->color);
        }
        if (text->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", text->linetype_scale);
        }
        if (text->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", text->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbText\n");
        }
        if (text->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", text->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", text->x0);
        fprintf (fp->fp, " 20\n%f\n", text->y0);
        fprintf (fp->fp, " 30\n%f\n", text->z0);
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
                if ((text->x0 == text->x1) && (text->y0 == text->y1) && (text->z0 == text->z1))
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
                        fprintf (fp->fp, " 11\n%f\n", text->x1);
                        fprintf (fp->fp, " 21\n%f\n", text->y1);
                        fprintf (fp->fp, " 31\n%f\n", text->z1);
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
        free (text->linetype);
        free (text->layer);
        free (text->text_value);
        free (text->text_style);
        free (text->dictionary_owner_soft);
        free (text->dictionary_owner_hard);
        free (text);
        text = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c TEXT
 * entities and all their data fields.
 */
void
dxf_text_free_chain
(
        DxfText *texts
                /*!< a pointer to the chain of DXF \c TEXT entities. */
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
                struct DxfText *iter = texts->next;
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


/* EOF */
