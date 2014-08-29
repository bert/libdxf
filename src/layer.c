/*!
 * \file layer.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF layer table.
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
 * allocated memory when succesful.
 */
DxfLayer *
dxf_layer_new ()
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        DxfLayer *dxf_layer = NULL;
        size_t size;

        size = sizeof (DxfLayer);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_layer = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfLayer struct.\n")),
                  __FUNCTION__);
                dxf_layer = NULL;
        }
        else
        {
                memset (dxf_layer, 0, size);
        }
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (dxf_layer);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LAYER
 * table.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLayer *
dxf_layer_init
(
        DxfLayer *dxf_layer
                /*!< DXF LAYER table. */
)
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        dxf_layer = dxf_layer_new ();
        if (dxf_layer == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a DxfLayer struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_layer->layer_name = strdup ("");
        dxf_layer->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_layer->color = DXF_COLOR_BYLAYER;
        dxf_layer->flag = 0;
        dxf_layer->plotting_flag = 0;
        dxf_layer->material = strdup ("");
        dxf_layer->lineweight = 0;
        dxf_layer->plot_style_name = strdup ("");
        dxf_layer->next = NULL;
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (dxf_layer);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LAYER table.
 *
 * The last line read from file contained the string "LAYER". \n
 * Now follows some data for the \c LAYER, to be terminated with a "  0"
 * string announcing the following table, or the end of the \c TABLE
 * section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c dxf_layer. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLayer *dxf_layer
                /*!< DXF LAYER table. */
)
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        char *temp_string = NULL;

        if (!dxf_layer)
        {
                dxf_layer = dxf_layer_new ();
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
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing the layer
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_layer->layer_name);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing the linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_layer->linetype);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_layer->color);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_layer->flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTable") != 0)
                        && ((strcmp (temp_string, "AcDbLayerTableRecord") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the plotting
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_layer->plotting_flag);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing the material. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_layer->material);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the
                         * lineweight. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_layer->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing the plot style
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_layer->plot_style_name);
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
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (EXIT_SUCCESS);
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
        DxfLayer *dxf_layer
                /*!< DXF \c LAYER table. */
)
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        char *dxf_entity_name = strdup ("LAYER");

        if (dxf_layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_layer->layer_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty layer string for the %s table.\n")),
                  __FUNCTION__, dxf_entity_name);
                return (EXIT_FAILURE);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTable\n");
                fprintf (fp->fp, "100\nAcDbLayerTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_layer->layer_name);
        fprintf (fp->fp, "  6\n%s\n", dxf_layer->linetype);
        fprintf (fp->fp, " 62\n%d\n", dxf_layer->color);
        fprintf (fp->fp, " 70\n%d\n", dxf_layer->flag);
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, "290\n%d\n", dxf_layer->plotting_flag);
                fprintf (fp->fp, "370\n%hd\n", dxf_layer->lineweight);
                fprintf (fp->fp, "390\n%s\n", dxf_layer->plot_style_name);
        }
        if (fp->acad_version_number >= AutoCAD_2007)
        {
                fprintf (fp->fp, "347\n%s\n", dxf_layer->material);
        }
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
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
        DxfLayer *dxf_layer
                /*!< Pointer to the memory occupied by the DXF \c LAYER
                 * table. */
)
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        if (dxf_layer->next != NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () pointer to next DxfLayer was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_layer->layer_name);
        free (dxf_layer->linetype);
        free (dxf_layer->material);
        free (dxf_layer->plot_style_name);
        free (dxf_layer);
        dxf_layer = NULL;
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
