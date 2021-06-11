/*!
 * \file seqend.c
 *
 * \author Copyright (C) 2008, 2010, 2013, 2014, 2015, 2017, 2019, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF end of sequence marker (\c SEQEND).
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


#include "seqend.h"


/*!
 * \brief Allocate memory for a DXF \c SEQEND.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSeqend *
dxf_seqend_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSeqend *seqend = NULL;
        size_t size;

        size = sizeof (DxfSeqend);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((seqend = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSeqend struct.\n")),
                  __FUNCTION__);
                seqend = NULL;
        }
        else
        {
                memset (seqend, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SEQEND
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSeqend *
dxf_seqend_init
(
        DxfSeqend *seqend
                /*!< a pointer to the DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                seqend = dxf_seqend_new ();
        }
        if (seqend == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfSeqend struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        seqend->id_code = 0;
        seqend->linetype = strdup (DXF_DEFAULT_LINETYPE);
        seqend->layer = strdup (DXF_DEFAULT_LAYER);
        seqend->elevation = 0.0;
        seqend->thickness = 0.0;
        seqend->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        seqend->visibility = DXF_DEFAULT_VISIBILITY;
        seqend->color = DXF_COLOR_BYLAYER;
        seqend->paperspace = DXF_MODELSPACE;
        seqend->graphics_data_size = 0;
        seqend->shadow_mode = 0;
        seqend->binary_graphics_data = dxf_binary_graphics_data_new ();
        seqend->binary_graphics_data = dxf_binary_graphics_data_init (seqend->binary_graphics_data);
        seqend->dictionary_owner_soft = strdup ("");
        seqend->material = strdup ("");
        seqend->dictionary_owner_hard = strdup ("");
        seqend->lineweight = 0;
        seqend->plot_style_name = strdup ("");
        seqend->color_value = 0;
        seqend->color_name = strdup ("");
        seqend->transparency = 0;
        seqend->app_name = strdup ("");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SEQEND entity.
 *
 * The last line read from file contained the string "SEQEND". \n
 * Now follows some data for the \c SEQEND, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c seqend. \n
 *
 * \return a pointer to \c seqend.
 */
DxfSeqend *
dxf_seqend_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSeqend *seqend
                /*!< a pointer to the DXF \c SEQEND entity. */
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
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                seqend = dxf_seqend_init (seqend);
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
                        /* Now follows a string containing an application
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->app_name);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &seqend->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->layer);
                }
                else if (strcmp (temp_string, "38") == 0)
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &seqend->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &seqend->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &seqend->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &seqend->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &seqend->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &seqend->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &seqend->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "AcDbEntity") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &seqend->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) seqend->binary_graphics_data->next);
                        seqend->binary_graphics_data = (DxfBinaryGraphicsData *) seqend->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &seqend->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &seqend->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, seqend->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &seqend->transparency);
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
        if (strcmp (seqend->linetype, "") == 0)
        {
                seqend->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (seqend->layer, "") == 0)
        {
                seqend->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Write DXF output to a file for an end of sequence marker
 * (\c SEQEND).
 *
 * No fields.\n
 * This entity marks the end of vertices (Vertex type name) for a 
 * Polyline (\c POLYLINE), a Light Wight Polyline (\c LWPOLYLINE)
 * or the end of Attribute entities (Attrib type name) for an Insert
 * entity (\c INSERT) that has Attributes (indicated by 66 group present
 * and nonzero).
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_seqend_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSeqend *seqend
                /*!< a pointer to the DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SEQEND");

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
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (seqend->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, seqend->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                seqend->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (seqend->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, seqend->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                seqend->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (seqend->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", seqend->id_code);
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
        if ((strcmp (seqend->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", seqend->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (seqend->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", seqend->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (seqend->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", seqend->layer);
        if (strcmp (seqend->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", seqend->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (seqend->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", seqend->material);
        }
        if (seqend->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", seqend->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", seqend->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (seqend->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", seqend->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (seqend->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", seqend->thickness);
        }
        if (seqend->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", seqend->linetype_scale);
        }
        if (seqend->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", seqend->visibility);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
          && (seqend->graphics_data_size > 0))
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", seqend->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", seqend->graphics_data_size);
#endif
                if (seqend->binary_graphics_data != NULL)
                {
                        DxfBinaryGraphicsData *iter;
                        iter = (DxfBinaryGraphicsData *) seqend->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", dxf_binary_graphics_data_get_data_line (iter));
                                iter = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_get_next (iter);
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", seqend->color_value);
                fprintf (fp->fp, "430\n%s\n", seqend->color_name);
                fprintf (fp->fp, "440\n%ld\n", seqend->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", seqend->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", seqend->shadow_mode);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SEQEND and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_seqend_free
(
        DxfSeqend *seqend
                /*!< a pointer to the memory occupied by the DXF \c SEQEND
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (seqend->linetype);
        free (seqend->layer);
        dxf_binary_graphics_data_free_list (seqend->binary_graphics_data);
        free (seqend->dictionary_owner_soft);
        free (seqend->material);
        free (seqend->dictionary_owner_hard);
        free (seqend->plot_style_name);
        free (seqend->color_name);
        free (seqend->app_name);
        free (seqend);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get the \c id_code from a DXF \c SEQEND entity.
 *
 * \return \c id_code.
 */
int
dxf_seqend_get_id_code
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_id_code
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
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
        if (seqend == NULL)
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
        seqend->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c linetype from a DXF \c SEQEND entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_seqend_get_linetype
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (seqend->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_linetype
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c layer from a DXF \c SEQEND entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_seqend_get_layer
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (seqend->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_layer
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c elevation from a DXF \c SEQEND entity.
 *
 * \return \c elevation.
 */
double
dxf_seqend_get_elevation
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_elevation
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        seqend->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c thickness from a DXF \c SEQEND entity.
 *
 * \return \c thickness.
 */
double
dxf_seqend_get_thickness
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_thickness
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c SEQEND entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_seqend_get_linetype_scale
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_linetype_scale
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c visibility from a DXF \c SEQEND entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_seqend_get_visibility
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_visibility
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c color from a DXF \c SEQEND entity.
 *
 * \return \c color.
 */
int
dxf_seqend_get_color
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->color);
}


/*!
 * \brief Set the \c color for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_color
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c SEQEND entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_seqend_get_paperspace
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (seqend->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_paperspace
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c SEQEND
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_seqend_get_graphics_data_size
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (seqend->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c SEQEND
 * entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_graphics_data_size
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c SEQEND entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_seqend_get_shadow_mode
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seqend->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c SEQEND entity.
 *
 * \return a pointer to \c seqend when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_shadow_mode
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c SEQEND entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_seqend_get_binary_graphics_data
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) seqend->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_binary_graphics_data
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SEQEND entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_seqend_get_dictionary_owner_soft
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (seqend->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_dictionary_owner_soft
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c SEQEND entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_seqend_get_material
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (seqend->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c SEQEND entity.
 *
 * \return a pointer to \c seqend when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_material
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SEQEND entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_seqend_get_dictionary_owner_hard
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (seqend->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SEQEND entity.
 */
DxfSeqend *
dxf_seqend_set_dictionary_owner_hard
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c lineweight from a DXF \c SEQEND entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_seqend_get_lineweight
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c SEQEND entity.
 *
 * \return a pointer to \c seqend when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_lineweight
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        seqend->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c SEQEND entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_seqend_get_plot_style_name
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (seqend->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c SEQEND entity.
 *
 * \return a pointer to \c seqend when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_plot_style_name
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c color_value from a DXF \c SEQEND entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_seqend_get_color_value
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c SEQEND entity.
 *
 * \return a pointer to \c seqend when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_color_value
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        seqend->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c color_name from a DXF \c SEQEND entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_seqend_get_color_name
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (seqend->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c SEQEND entity.
 *
 * \return a pointer to \c seqend when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_color_name
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
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
        seqend->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c transparency from a DXF \c SEQEND entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_seqend_get_transparency
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c SEQEND entity.
 *
 * \return a pointer to \c seqend when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_transparency
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        seqend->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/*!
 * \brief Get the \c app_name from a DXF \c SEQEND entity.
 *
 * \return \c app_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_seqend_get_app_name
(
        DxfSeqend *seqend
                /*!< a pointer to a DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seqend->app_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (seqend->app_name));
}


/*!
 * \brief Set the \c app_name for a DXF \c SEQEND entity.
 *
 * \return a pointer to \c seqend when successful, or \c NULL when an
 * error occurred.
 */
DxfSeqend *
dxf_seqend_set_app_name
(
        DxfSeqend *seqend,
                /*!< a pointer to a DXF \c SEQEND entity. */
        char *app_name
                /*!< a string containing the \c app_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (app_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        seqend->app_name = strdup (app_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seqend);
}


/* EOF */
