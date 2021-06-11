/*!
 * \file layer.c
 *
 * \author Copyright (C) 2008, 2012, 2013, 2014, 2015, 2017, 2018, 2019,
 * 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF layer table (\c LAYER).
 *
 * \note Xref-dependent layers are output during DXFOUT.\n
 * For these layers, the associated linetype name in the DXF file is
 * always CONTINUOUS.
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


#include "layer.h"


/*!
 * \brief Allocate memory for a DXF \c LAYER.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLayer *
dxf_layer_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLayer *layer = NULL;
        size_t size;

        size = sizeof (DxfLayer);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((layer = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLayer struct.\n")),
                  __FUNCTION__);
                layer = NULL;
        }
        else
        {
                memset (layer, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LAYER
 * table.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLayer *
dxf_layer_init
(
        DxfLayer *layer
                /*!< DXF LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer = dxf_layer_new ();
        }
        if (layer == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfLayer struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_layer_set_id_code (layer, 0);
        dxf_layer_set_layer_name (layer, strdup (""));
        dxf_layer_set_linetype (layer, strdup (DXF_DEFAULT_LINETYPE));
        dxf_layer_set_color (layer, DXF_COLOR_BYLAYER);
        dxf_layer_set_flag (layer, 0);
        dxf_layer_set_plotting_flag (layer, 0);
        dxf_layer_set_dictionary_owner_soft (layer, strdup (""));
        dxf_layer_set_material (layer, strdup (""));
        dxf_layer_set_dictionary_owner_hard (layer, strdup (""));
        dxf_layer_set_lineweight (layer, 0);
        dxf_layer_set_plot_style_name (layer, strdup (""));
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        dxf_layer_set_next (layer, NULL);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LAYER table.
 *
 * The last line read from file contained the string "LAYER". \n
 * Now follows some data for the \c LAYER, to be terminated with a "  0"
 * string announcing the following table, or the end of the \c TABLE
 * section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c layer. \n
 *
 * \return a pointer to \c layer.
 */
DxfLayer *
dxf_layer_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLayer *layer
                /*!< DXF LAYER table. */
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
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer = dxf_layer_init (layer);
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
                        /* Now follows a string containing the layer
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer->layer_name);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing the linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer->linetype);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &layer->color);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &layer->flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTable") != 0)
                        && ((strcmp (temp_string, "AcDbLayerTableRecord") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the plotting
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &layer->plotting_flag);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing the material. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the
                         * lineweight. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &layer->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing the plot style
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer->plot_style_name);
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
        if (strcmp (layer->layer_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () found a bad layer name in: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                fprintf (stderr,
                  (_("\tskipping layer.\n")));
                return (NULL);
        }
        if (strcmp (layer->linetype, "") == 0)
        {
                layer->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Write DXF output for a DXF \c LAYER table.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LAYER");

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
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_layer_get_layer_name (layer), "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty layer string for the %s table.\n")),
                  __FUNCTION__, dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_layer_get_linetype (layer), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s layer\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_layer_set_linetype (layer, strdup (DXF_DEFAULT_LINETYPE));
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (layer->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_layer_get_id_code (layer));
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
        if ((strcmp (dxf_layer_get_dictionary_owner_soft (layer), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_layer_get_dictionary_owner_soft (layer));
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTable\n");
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbLayerTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_layer_get_layer_name (layer));
        fprintf (fp->fp, " 70\n%d\n", dxf_layer_get_flag (layer));
        fprintf (fp->fp, " 62\n%d\n", dxf_layer_get_color (layer));
        fprintf (fp->fp, "  6\n%s\n", dxf_layer_get_linetype (layer));
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, "290\n%d\n", dxf_layer_get_plotting_flag (layer));
                fprintf (fp->fp, "370\n%hd\n", dxf_layer_get_lineweight (layer));
                fprintf (fp->fp, "390\n%s\n", dxf_layer_get_plot_style_name (layer));
        }
        if (fp->acad_version_number >= AutoCAD_2007)
        {
                fprintf (fp->fp, "347\n%s\n", dxf_layer_get_material (layer));
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LAYER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_free
(
        DxfLayer *layer
                /*!< Pointer to the memory occupied by the DXF \c LAYER
                 * table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_layer_get_layer_name (layer));
        free (dxf_layer_get_linetype (layer));
        free (dxf_layer_get_dictionary_owner_soft (layer));
        free (dxf_layer_get_material (layer));
        free (dxf_layer_get_dictionary_owner_hard (layer));
        free (dxf_layer_get_plot_style_name (layer));
        free (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c LAYER tables and all their data fields.
 */
void
dxf_layer_free_list
(
        DxfLayer *layers
                /*!< pointer to the single linked list of DXF \c LAYER
                 * tables. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (layers == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (layers != NULL)
        {
                DxfLayer *iter = (DxfLayer *) layers->next;
                dxf_layer_free (layers);
                layers = (DxfLayer *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c LAYER entity.
 *
 * \return ID code.
 */
int
dxf_layer_get_id_code
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c LAYER entity.
 */
DxfLayer *
dxf_layer_set_id_code
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
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
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the \c layer_name from a DXF \c LAYER entity.
 *
 * \return \c layer_name when sucessful, \c NULL when an error occurred.
 */
char *
dxf_layer_get_layer_name
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer->layer_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer->layer_name));
}


/*!
 * \brief Set the \c layer_name for a DXF \c LAYER entity.
 */
DxfLayer *
dxf_layer_set_layer_name
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        char *layer_name
                /*!< a string containing the \c layer_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer->layer_name = strdup (layer_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the linetype from a DXF \c LAYER entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_layer_get_linetype
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c LAYER entity.
 */
DxfLayer *
dxf_layer_set_linetype
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
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
        layer->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the color from a DXF \c LAYER entity.
 *
 * \return color.
 */
int
dxf_layer_get_color
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer->color);
}


/*!
 * \brief Set the color for a DXF \c LAYER entity.
 */
DxfLayer *
dxf_layer_set_color
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
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
        layer->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Test if layer is off.
 *
 * \return \c TRUE when layer is off, or \c FALSE when layer is on, or
 * (-1) when an error occurred.
 */
int
dxf_layer_is_off
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = (layer->color < 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Get the \c flag from a DXF \c LAYER entity.
 *
 * \return \c flag.
 */
int
dxf_layer_get_flag
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer->flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer->flag);
}


/*!
 * \brief Set the \c flag for a DXF \c LAYER entity.
 */
DxfLayer *
dxf_layer_set_flag
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        int flag
                /*!< a \c flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Test if layer is frozen.
 *
 * \return \c TRUE when layer is frozen, or \c FALSE when layer is
 * thawed, or (-1) when an error occurred.
 */
int
dxf_layer_is_frozen
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = ((DXF_CHECK_BIT (layer->flag, 0))
          || (DXF_CHECK_BIT (layer->flag, 1)));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is locked.
 *
 * \return \c TRUE when layer is locked, or \c FALSE when layer is not
 * locked, or (-1) when an error occurred.
 */
int
dxf_layer_is_locked
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (layer->flag, 2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is externally dependent on an xref.
 *
 * \return \c TRUE when layer is externally dependent on an xref,
 * or \c FALSE when layer is not externally dependent on an xref, or
 * (-1) when an error occurred.
 */
int
dxf_layer_is_xreferenced
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (layer->flag, 4);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is externally dependent on a xref and has been
 * successfully resolved.
 *
 * \return \c TRUE when layer is externally dependent on a xref and has
 * been successfully resolved, or \c FALSE when layer is not externally
 * dependent on a xref and has not been successfully resolved, or (-1)
 * when an error occurred.
 */
int
dxf_layer_is_xresolved
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = ((DXF_CHECK_BIT (layer->flag, 4))
          && (DXF_CHECK_BIT (layer->flag, 5)));
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if layer is internally referenced by an entity.
 *
 * \return \c TRUE when layer is internally referenced by an entity,
 * or \c FALSE when layer is not internally referenced by an entity, or
 * (-1) when an error occurred.
 */
int
dxf_layer_is_referenced
(
        DxfLayer *layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
        result = DXF_CHECK_BIT (layer->flag, 6);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Get the \c plotting_flag from a DXF \c LAYER entity.
 *
 * \return \c flag.
 */
int
dxf_layer_get_plotting_flag
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer->plotting_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer->plotting_flag);
}


/*!
 * \brief Set the \c plotting_flag for a DXF \c LAYER entity.
 */
DxfLayer *
dxf_layer_set_plotting_flag
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        int plotting_flag
                /*!< a \c plotting_flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (plotting_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer->plotting_flag = plotting_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c LAYER entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_layer_get_dictionary_owner_soft
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c LAYER entity.
 */
DxfLayer *
dxf_layer_set_dictionary_owner_soft
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
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
        layer->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c LAYER entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_layer_get_material
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c LAYER entity.
 *
 * \return a pointer to \c layer when successful, or \c NULL when an
 * error occurred.
 */
DxfLayer *
dxf_layer_set_material
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
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
        layer->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c LAYER entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_layer_get_dictionary_owner_hard
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c LAYER entity.
 */
DxfLayer *
dxf_layer_set_dictionary_owner_hard
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
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
        layer->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the \c lineweight from a DXF \c LAYER entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_layer_get_lineweight
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c LAYER entity.
 *
 * \return a pointer to \c layer when successful, or \c NULL when an
 * error occurred.
 */
DxfLayer *
dxf_layer_set_lineweight
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c LAYER entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_layer_get_plot_style_name
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c LAYER entity.
 *
 * \return a pointer to \c layer when successful, or \c NULL when an
 * error occurred.
 */
DxfLayer *
dxf_layer_set_plot_style_name
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
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
        layer->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the pointer to the next \c LAYER entity from a DXF 
 * \c LAYER entity.
 *
 * \return pointer to the next \c LAYER entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLayer *
dxf_layer_get_next
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLayer *) layer->next);
}


/*!
 * \brief Set the pointer to the next \c LAYER for a DXF \c LAYER
 * entity.
 */
DxfLayer *
dxf_layer_set_next
(
        DxfLayer *layer,
                /*!< a pointer to a DXF \c LAYER entity. */
        DxfLayer *next
                /*!< a pointer to the next \c LAYER for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
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
        layer->next = (struct DxfLayer *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer);
}


/*!
 * \brief Get the pointer to the last \c LAYER entity from a linked list
 * of DXF \c LAYER entities.
 *
 * \return pointer to the last \c LAYER entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLayer *
dxf_layer_get_last
(
        DxfLayer *layer
                /*!< a pointer to a DXF \c LAYER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfLayer *) layer);
        }
        DxfLayer *iter = (DxfLayer *) layer->next;
        while (iter->next != NULL)
        {
                iter = (DxfLayer *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLayer *) iter);
}


/* EOF */
