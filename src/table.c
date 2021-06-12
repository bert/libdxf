/*!
 * \file table.c
 *
 * \author Copyright (C) 2009, 2010, 2011, 2014, 2015, 2017, 2018, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF table entry (\c TABLE).
 *
 * \since The \c TABLE entity was introduced in DXF R2005.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2005.
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


#include "table.h"


/*!
 * \brief Allocate memory for a DXF \c TABLE cell.
 *
 * Fill the memory contents with zeros.
 *
 * \return a pointer to the allocated memory when successful,or \c NULL
 * when no memory was allocated.
 */
DxfTableCell *
dxf_table_cell_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTableCell *cell = NULL;
        size_t size;

        size = sizeof (DxfTableCell);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((cell = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTableCell struct.\n")),
                  __FUNCTION__);
                cell = NULL;
        }
        else
        {
                memset (cell, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (cell);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c TABLE
 * cell.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfTableCell *
dxf_table_cell_init
(
        DxfTableCell *cell
                /*!< a pointer to a DXF \c TABLE cell. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (cell == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                cell = dxf_table_cell_new ();
        }
        if (cell == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTableCell struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        cell->text_string = strdup ("");
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                cell->optional_text_string[i] = strdup ("");
                cell->attdef_soft_pointer[i] = strdup ("");
        }
        cell->text_style_name = strdup (DXF_DEFAULT_TEXTSTYLE);
        cell->color_bg = 0;
        cell->color_fg = DXF_COLOR_BYLAYER;
        cell->border_color_right = DXF_COLOR_BYLAYER;
        cell->border_color_bottom = DXF_COLOR_BYLAYER;
        cell->border_color_left = DXF_COLOR_BYLAYER;
        cell->border_color_top = DXF_COLOR_BYLAYER;
        cell->text_height = 1.0;
        cell->block_scale = 1.0;
        cell->block_rotation = 0.0;
        cell->alignment = 0;
        cell->type = 0;
        cell->flag = 0;
        cell->merged = 0;
        cell->autofit = 0;
        cell->border_width = 0.0;
        cell->border_height = 0.0;
        cell->override = 0;
        cell->virtual_edge = 0;
        cell->number_of_block_attdefs = 0;
        cell->border_lineweight_right = 1.0;
        cell->border_lineweight_bottom = 1.0;
        cell->border_lineweight_left = 1.0;
        cell->border_lineweight_top = 1.0;
        cell->color_fill_override = 0;
        cell->border_visibility_override_right = 0;
        cell->border_visibility_override_bottom = 0;
        cell->border_visibility_override_left = 0;
        cell->border_visibility_override_top = 0;
        cell->attdef_text_string = strdup ("");
        cell->block_table_record_hard_pointer = strdup ("");
        cell->field_object_pointer = strdup ("");
        cell->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (cell);
}


/*!
 * \brief Write DXF output to a file for a DXF \c TABLE cell.
 * 
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_table_cell_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfTableCell *cell
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (cell == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "171\n%d\n", cell->type);
        fprintf (fp->fp, "172\n%d\n", cell->flag);
        fprintf (fp->fp, "173\n%d\n", cell->merged);
        fprintf (fp->fp, "174\n%d\n", cell->autofit);
        fprintf (fp->fp, "175\n%lf\n", cell->border_width);
        fprintf (fp->fp, "176\n%lf\n", cell->border_height);
        fprintf (fp->fp, " 91\n%d\n", cell->override_flag);
        fprintf (fp->fp, "178\n%d\n", cell->virtual_edge);
        fprintf (fp->fp, "145\n%lf\n", cell->block_rotation);
        fprintf (fp->fp, "344\n%s\n", cell->field_object_pointer);
        i = 0;
        while ((cell->optional_text_string[i] != NULL)
          && (strcmp (cell->optional_text_string[i], "") != 0))
        {
                fprintf (fp->fp, "  2\n%s\n", cell->optional_text_string[i]);
                i++;
        }
        fprintf (fp->fp, "  1\n%s\n", cell->text_string);
        fprintf (fp->fp, "340\n%s\n", cell->block_table_record_hard_pointer);
        fprintf (fp->fp, "144\n%lf\n", cell->block_scale);
        fprintf (fp->fp, "179\n%d\n", cell->number_of_block_attdefs);
        i = 0;
        while ((cell->attdef_soft_pointer[i] != NULL)
          && (strcmp (cell->attdef_soft_pointer[i], "") != 0))
        {
                fprintf (fp->fp, "331\n%s\n", cell->attdef_soft_pointer[i]);
                i++;
        }
        if (cell->number_of_block_attdefs < (i + 1))
        {
                fprintf (stderr,
                  (_("Warning in %s () more attdefs encountered than expected.\n")),
                  __FUNCTION__);
        }
        else if (cell->number_of_block_attdefs > (i + 1))
        {
                fprintf (stderr,
                  (_("Warning in %s () less attdefs encountered than expected.\n")),
                  __FUNCTION__);
        }

#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c TABLE cell and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_table_cell_free
(
        DxfTableCell *cell
                /*!< a pointer to a DXF \c TABLE cell. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (cell == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (cell->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (cell->text_string);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (cell->optional_text_string[i]);
                free (cell->attdef_soft_pointer[i]);
        }
        free (cell->text_style_name);
        free (cell->attdef_text_string);
        free (cell->block_table_record_hard_pointer);
        free (cell->field_object_pointer);
        free (cell);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c TABLE cells and all their data fields.
 */
void
dxf_table_cell_free_list
(
        DxfTableCell *cells
                /*!< pointer to the single linked list of DXF \c TABLE
                 * cells. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (cells == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (cells != NULL)
        {
                DxfTableCell *iter = (DxfTableCell *) cells->next;
                dxf_table_cell_free (cells);
                cells = (DxfTableCell *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the pointer to the next \c table cell from a linked list
 * of DXF \c table cells.
 *
 * \return pointer to the next \c table cell, or \c NULL when an error
 * occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfTableCell *
dxf_table_cell_get_next
(
        DxfTableCell *cell
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (cell == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (cell->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfTableCell *) cell->next);
}


/*!
 * \brief Set the pointer to the next \c table cell for a DXF \c table
 * cell.
 *
 * \return a pointer to \c table cell when successful, or \c NULL when an
 * error occurred.
 */
DxfTableCell *
dxf_table_cell_set_next
(
        DxfTableCell *cell,
                /*!< a pointer to a DXF \c table cell. */
        DxfTableCell *next
                /*!< a pointer to the next \c table cell. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (cell == NULL)
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
        cell->next = (struct DxfTableCell *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (cell);
}


/*!
 * \brief Get the pointer to the last \c table cell from a linked
 * list of DXF \c table cells.
 *
 * \return pointer to the last \c table cell.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfTableCell *
dxf_table_cell_get_last
(
        DxfTableCell *cells
                /*!< a pointer to a linked list of DXF \c table cells. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (cells == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (cells->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfTableCell *) cells);
        }
        DxfTableCell *iter = (DxfTableCell *) cells->next;
        while (iter->next != NULL)
        {
                iter = (DxfTableCell *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfTableCell *) iter);
}


/*!
 * \brief Allocate memory for a DXF \c TABLE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfTable *
dxf_table_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTable *table = NULL;
        size_t size;

        size = sizeof (DxfTable);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((table = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTable struct.\n")),
                  __FUNCTION__);
                table = NULL;
        }
        else
        {
                memset (table, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c TABLE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfTable *
dxf_table_init
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                table = dxf_table_new ();
        }
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTable struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        table->id_code = 0;
        table->linetype = strdup (DXF_DEFAULT_LINETYPE);
        table->layer = strdup (DXF_DEFAULT_LAYER);
        table->elevation = 0.0;
        table->thickness = 0.0;
        table->visibility = 0;
        table->color = DXF_COLOR_BYLAYER;
        table->paperspace = DXF_MODELSPACE;
        table->graphics_data_size = 0;
        table->row_height = 0.0;
        table->column_height = 0.0;
        table->dictionary_owner_soft = strdup ("");
        table->dictionary_owner_hard = strdup ("");
        table->block_name = strdup ("");
        table->table_text_style_name = strdup ("");
        table->horizontal_cell_margin = 0.0;
        table->vertical_cell_margin = 0.0;
        table->table_cell_color_bg = 0;
        table->table_cell_color_fg = 0;
        table->table_cell_border_color_horizontal = DXF_COLOR_BYLAYER;
        table->table_cell_border_color_bottom = DXF_COLOR_BYLAYER;
        table->table_cell_border_color_vertical = DXF_COLOR_BYLAYER;
        table->table_cell_border_color_right = DXF_COLOR_BYLAYER;
        table->flow_direction = 0;
        table->table_value_flag = 0;
        table->number_of_rows = 0;
        table->number_of_columns = 0;
        table->override_flag = 0;
        table->border_color_override_flag = 0;
        table->border_lineweight_override_flag = 0;
        table->border_visibility_override_flag = 0;
        table->table_text_height = 0.0;
        table->table_cell_alignment = 0;
        table->table_cell_border_lineweight_right = 0.0;
        table->suppress_table_title = 0;
        table->suppress_header_row = 0;
        table->table_cell_color_fill_override = 0;
        table->tablestyle_object_pointer = strdup ("");
        table->owning_block_pointer = strdup ("");
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        table->binary_graphics_data = NULL;
        table->p0 = NULL;
        table->p1 = NULL;
        table->cells = NULL;
        table->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Read data from a DXF file into a DXF \c TABLE entity.
 *
 * The last line read from file contained the string "TABLE". \n
 * Now follows some data for the \c TABLE, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c table. \n
 *
 * \return a pointer to \c table.
 */
DxfTable *
dxf_table_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfBinaryData *iter310 = NULL;
        int i;
        int k;
        int l;

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
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                table = dxf_table_new ();
                table = dxf_table_init (table);
        }
        if (table->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                table->binary_graphics_data = dxf_binary_data_init (table->binary_graphics_data);
                if (table->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (table->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                table->p0 = dxf_point_init (table->p0);
                if (table->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (table->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                table->p1 = dxf_point_init (table->p1);
                if (table->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        i = 0;
        k = 0;
        l = 0;
        iter310 = (DxfBinaryData *) table->binary_graphics_data;
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
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a block name;
                         * an anonymous block begins with a *T value. */
                        fscanf (fp->fp, "%s\n", table->block_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &table->id_code);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &table->p0->x0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the horizontal direction
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &table->p1->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &table->p0->y0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the horizontal direction
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &table->p1->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &table->p0->z0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the horizontal direction
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &table->p1->z0);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the flag for
                         * table value (unsigned integer). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &table->table_value_flag);
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing the number of
                         * rows. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &table->number_of_rows);
                }
                else if ((strcmp (temp_string, "92") == 0)
                  && (i == 0))
                {
                        /* Now follows a string containing the
                         * number of bytes in the proxy entity graphics. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &table->graphics_data_size);
                        i++;
                }
                else if ((strcmp (temp_string, "92") == 0)
                  && (i == 1))
                {
                        /* Now follows a string containing the number of
                         * columns. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &table->number_of_columns);
                }
                else if (strcmp (temp_string, "93") == 0)
                {
                        /* Now follows a string containing the flag for
                         * an override. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &table->override_flag);
                }
                else if (strcmp (temp_string, "94") == 0)
                {
                        /* Now follows a string containing the flag for
                         * an override of the border color. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &table->border_color_override_flag);
                }
                else if (strcmp (temp_string, "95") == 0)
                {
                        /* Now follows a string containing the flag for
                         * an override of the border lineweight. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &table->border_lineweight_override_flag);
                }
                else if (strcmp (temp_string, "96") == 0)
                {
                        /* Now follows a string containing the flag for
                         * an override of the border visibility. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &table->border_visibility_override_flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbBlockReference") != 0))
                        && ((strcmp (temp_string, "AcDbBlockTable") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "141") == 0)
                {
                        /* Now follows a string containing the row
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &table->row_height);
                        k++;
                }
                else if (strcmp (temp_string, "142") == 0)
                {
                        /* Now follows a string containing the column
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &table->column_height);
                        l++;
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_data_init ((DxfBinaryData *) iter310->next);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing a soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", table->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "342") == 0)
                {
                        /* Now follows a string containing a hard pointer
                         * ID of the TABLESTYLE object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", table->tablestyle_object_pointer);
                }
                else if (strcmp (temp_string, "343") == 0)
                {
                        /* Now follows a string containing a hard pointer
                         * ID of the owning BLOCK record. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", table->owning_block_pointer);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing a hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", table->dictionary_owner_hard);
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
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Write DXF output to a file for a DXF \c TABLE entity.
 * 
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_table_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ACAD_TABLE");
        int i;

        /* Do some basic checks. */
        if (dxf_entity_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a char string.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (table->layer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\tSetting entity to default layer.\n")));
                table->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (table->linetype == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\tSetting entity to default linetype.\n")));
                table->layer = strdup (DXF_DEFAULT_LINETYPE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (table->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", table->id_code);
        }
        if (table->dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
        }
        else fprintf (fp->fp, "330\n%s\n", table->dictionary_owner_soft);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", table->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", table->graphics_data_size);
#endif
        }
        if (table->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
        }
        else
        {
                DxfBinaryData *iter;
                iter = (DxfBinaryData *) table->binary_graphics_data;
                while (iter != NULL)
                {
                        fprintf (fp->fp, "310\n%s\n", iter->data_line);
                        iter = (DxfBinaryData *) iter->next;
                }
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbBlockReference\n");
        }
        if (table->block_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
        }
        else fprintf (fp->fp, "  2\n%s\n", table->block_name);
        fprintf (fp->fp, " 10\n%f\n", table->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", table->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", table->p0->z0);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbTable\n");
        }
        fprintf (fp->fp, "280\n%d\n", table->table_data_version);
        if (table->tablestyle_object_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
        }
        else fprintf (fp->fp, "342\n%s\n", table->tablestyle_object_pointer);
        if (table->owning_block_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
        }
        else fprintf (fp->fp, "343\n%s\n", table->owning_block_pointer);
        fprintf (fp->fp, " 11\n%f\n", table->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", table->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", table->p1->z0);
        fprintf (fp->fp, " 90\n%d\n", table->table_value_flag);
        fprintf (fp->fp, " 91\n%d\n", table->number_of_rows);
        fprintf (fp->fp, " 92\n%d\n", table->number_of_columns);
        fprintf (fp->fp, " 93\n%d\n", table->override_flag);
        fprintf (fp->fp, " 94\n%d\n", table->border_color_override_flag);
        fprintf (fp->fp, " 95\n%d\n", table->border_lineweight_override_flag);
        fprintf (fp->fp, " 96\n%d\n", table->border_visibility_override_flag);
        /*! \todo implement a linked list of dxf_doubles. */
        for (i = 0; i < table->number_of_rows; i++)
        {
                fprintf (fp->fp, "141\n%f\n", table->row_height);
        }
        /*! \todo implemnet a linked list of doubles. */
        for (i = 0; i < table->number_of_columns; i++)
        {
                fprintf (fp->fp, "142\n%f\n", table->column_height);
        }

        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c TABLE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_table_free
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (table->linetype);
        free (table->layer);
        dxf_binary_data_free_list (table->binary_graphics_data);
        free (table->dictionary_owner_soft);
        free (table->dictionary_owner_hard);
        free (table->block_name);
        free (table->table_text_style_name);
        dxf_point_free_list ((DxfPoint *) table->p0);
        dxf_point_free_list ((DxfPoint *) table->p1);
        free (table->tablestyle_object_pointer);
        free (table->owning_block_pointer);
        dxf_table_cell_free_list ((DxfTableCell *) table->cells);
        free (table);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c TABLE entities and all their data fields.
 */
void
dxf_table_free_list
(
        DxfTable *tables
                /*!< pointer to the single linked list of DXF
                 * \c TABLE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (tables != NULL)
        {
                struct DxfTable *iter = tables->next;
                dxf_table_free (tables);
                tables = (DxfTable *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c TABLE entity.
 *
 * \return \c id_code, or \c EXIT_FAILURE when an error occurred.
 */
int
dxf_table_get_id_code
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_id_code
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
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
        if (table == NULL)
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
        table->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the linetype from a DXF \c TABLE entity.
 *
 * \return a pointer to \c linetype when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_table_get_linetype
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c linetype variable is not freed by this
 * function.
 */
DxfTable *
dxf_table_set_linetype
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c layer from a DXF \c TABLE entity.
 *
 * \return a pointer to \c layer when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_table_get_layer
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c layer variable is not freed by this function.
 */
DxfTable *
dxf_table_set_layer
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c elevation a this DXF \c TABLE entity.
 *
 * \return \c elevation when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_table_get_elevation
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_elevation
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c thickness from a DXF \c TABLE entity.
 *
 * \return \c thickness when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_table_get_thickness
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_thickness
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        table->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c TABLE entity.
 *
 * \return \c linetype_scale when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
double
dxf_table_get_linetype_scale
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_linetype_scale
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        table->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c visibility from a DXF \c TABLE entity.
 *
 * \return \c visibility if successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int16_t
dxf_table_get_visibility
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_visibility
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c color from a DXF \c TABLE entity.
 *
 * \return \c color if successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int16_t
dxf_table_get_color
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->color);
}


/*!
 * \brief Set the \c color for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_color
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c TABLE entity.
 *
 * \return \c paperspace flag value if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int16_t
dxf_table_get_paperspace
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_paperspace
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c TABLE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_table_get_graphics_data_size
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_graphics_data_size
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c TABLE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_table_get_shadow_mode
(
        DxfTable *table
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_shadow_mode
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c TABLE entity.
 *
 * \return pointer to the \c binary_graphics_data if successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_table_get_binary_graphics_data
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) table->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_binary_graphics_data
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the soft pointer to the \c dictionary_owner_soft from a
 * DXF \c TABLE entity.
 *
 * \return a pointer to the \c dictionary_owner_soft if successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_table_get_dictionary_owner_soft
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c TABL entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_dictionary_owner_soft
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c TABLE entity.
 *
 * \return a pointer to \c object_owner_soft if successful, or \c NULL
 * when an error occurred.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_table_get_object_owner_soft
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_object_owner_soft
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c TABLE entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_table_get_material
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_material
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c TABLE entity.
 *
 * \return a pointer to the \c dictionary_owner_hard when successful,
 * or \c NULL if an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_table_get_dictionary_owner_hard
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_dictionary_owner_hard
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c lineweight from a DXF \c TABLE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_table_get_lineweight
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_lineweight
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c TABLE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_table_get_plot_style_name
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_plot_style_name
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c color_value from a DXF \c TABLE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_table_get_color_value
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_color_value
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c color_name from a DXF \c TABLE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_table_get_color_name
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_color_name
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c transparency from a DXF \c TABLE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_table_get_transparency
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_transparency
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c block_name from a DXF \c TABLE entity.
 *
 * \return \c block_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_table_get_block_name
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->block_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->block_name));
}


/*!
 * \brief Set the \c block_name for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_block_name
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *block_name
                /*!< a string containing the \c block_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->block_name = strdup (block_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c table_text_style_name from a DXF \c TABLE entity.
 *
 * \return \c table_text_style_name when sucessful, or \c NULL when an
 * error occurred.
 */
char *
dxf_table_get_table_text_style_name
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->table_text_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (table->table_text_style_name));
}


/*!
 * \brief Set the \c table_text_style_name for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_table_text_style_name
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *table_text_style_name
                /*!< a string containing the \c table_text_style_name
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table_text_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->table_text_style_name = strdup (table_text_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the insertion point of a DXF \c TABLE entity.
 *
 * \return the insertion point \c p0, or \c NULL if an error occurred.
 */
DxfPoint *
dxf_table_get_p0
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_p0
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->p0 = (DxfPoint *) point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a DXF \c TABLE
 * entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_table_get_x0
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_x0
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double x0
                /*!< the X-value of the base point \c x0 of a DXF
                 * \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                table->p0 = dxf_point_init (table->p0);
                if (table->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        table->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a DXF \c TABLE
 * entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_table_get_y0
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a DXF \c TABLE
 * entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_y0
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a DXF
                 * \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                table->p0 = dxf_point_init (table->p0);
                if (table->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        table->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a DXF \c TABLE
 * entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_table_get_z0
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a DXF \c TABLE
 * entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_z0
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double z0
                /*!< the Z-value of the base point \c z0 of a DXF
                 * \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                table->p0 = dxf_point_init (table->p0);
                if (table->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        table->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the horizontal direction vector \c p1 of a DXF \c TABLE
 * entity.
 *
 * \return the horizontal direction vector \c p1 if successful,
 * or \c NULL when an error occurred.
 */
DxfPoint *
dxf_table_get_p1
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->p1);
}


/*!
 * \brief Set the horizontal direction vector \c p1 of a DXF \c TABLE
 * entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_p1
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->p1 = (DxfPoint *) point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the X-value of the horizontal direction vector \c x1
 * of a DXF \c TABLE entity.
 *
 * \return the X-value of the horizontal direction vector \c x1.
 */
double
dxf_table_get_x1
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->p1->x0);
}


/*!
 * \brief Set the X-value of the horizontal direction vector \c x1 of a
 * DXF \c 3DFACE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_x1
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double x1
                /*!< the X-value of the horizontal direction vector
                 * \c x1 of a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                table->p1 = dxf_point_init (table->p1);
                if (table->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        table->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the Y-value of the horizontal direction vector \c y1
 * of a DXF \c TABLE entity.
 *
 * \return the Y-value of the horizontal direction vector \c y1.
 */
double
dxf_table_get_y1
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->p1->y0);
}


/*!
 * \brief Set the Y-value of the horizontal direction vector \c y1 of a
 * DXF \c 3DFACE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_y1
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double y1
                /*!< the Y-value of the horizontal direction vector
                 * \c y1 of a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                table->p1 = dxf_point_init (table->p1);
                if (table->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        table->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the Z-value of the horizontal direction vector \c z1
 * of a DXF \c TABLE entity.
 *
 * \return the Z-value of the horizontal direction vector \c z1.
 */
double
dxf_table_get_z1
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->p1->z0);
}


/*!
 * \brief Set the Z-value of the horizontal direction vector \c z1 of a
 * DXF \c 3DFACE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_z1
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double z1
                /*!< the Z-value of the horizontal direction vector
                 * \c z1 of a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                table->p1 = dxf_point_init (table->p1);
                if (table->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        table->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the horizontal cell margin \c horizontal_cell_margin
 * of a DXF \c TABLE entity.
 *
 * \return the horizontal cell margin \c horizontal_cell_margin.
 */
double
dxf_table_get_horizontal_cell_margin
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->horizontal_cell_margin);
}


/*!
 * \brief Set the horizontal cell margin \c horizontal_cell_margin of a
 * DXF \c 3DFACE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_horizontal_cell_margin
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double horizontal_cell_margin
                /*!< the horizontal cell margin
                 * \c horizontal_cell_margin of a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->horizontal_cell_margin = horizontal_cell_margin;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the vertical cell margin \c vertical_cell_margin
 * of a DXF \c TABLE entity.
 *
 * \return the vertical cell margin \c vertical_cell_margin.
 */
double
dxf_table_get_vertical_cell_margin
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->vertical_cell_margin);
}


/*!
 * \brief Set the vertical cell margin \c vertical_cell_margin of a
 * DXF \c 3DFACE entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_vertical_cell_margin
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double vertical_cell_margin
                /*!< the vertical cell margin
                 * \c vertical_cell_margin of a DXF \c TABLE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->vertical_cell_margin = vertical_cell_margin;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c table_cell_color_bg value from a DXF \c TABLE
 * entity.
 *
 * \return \c table_cell_color_bg value if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_table_get_table_cell_color_bg
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->table_cell_color_bg < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->table_cell_color_bg > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_color_bg);
}


/*!
 * \brief Set the \c table_cell_color_bg for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_color_bg
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t table_cell_color_bg
                /*!< the \c table_cell_color_bg value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table_cell_color_bg < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (table_cell_color_bg > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->table_cell_color_bg = table_cell_color_bg;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c table_cell_color_fg value from a DXF \c TABLE
 * entity.
 *
 * \return \c table_cell_color_fg value if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_table_get_table_cell_color_fg
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->table_cell_color_fg < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->table_cell_color_fg > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_color_fg);
}


/*!
 * \brief Set the \c table_cell_color_fg for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_color_fg
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t table_cell_color_fg
                /*!< the \c table_cell_color_fg value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table_cell_color_fg < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (table_cell_color_fg > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->table_cell_color_fg = table_cell_color_fg;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c table_cell_border_color_horizontal value from a DXF
 * \c TABLE entity.
 *
 * \return \c table_cell_border_color_horizontal value if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_table_get_table_cell_border_color_horizontal
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->table_cell_border_color_horizontal < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->table_cell_border_color_horizontal > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_border_color_horizontal);
}


/*!
 * \brief Set the \c table_cell_border_color_horizontal for a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_border_color_horizontal
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t table_cell_border_color_horizontal
                /*!< the \c table_cell_border_color_horizontal value to
                 * be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table_cell_border_color_horizontal < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (table_cell_border_color_horizontal > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->table_cell_border_color_horizontal = table_cell_border_color_horizontal;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c table_cell_border_color_bottom value from a DXF
 * \c TABLE entity.
 *
 * \return \c table_cell_border_color_bottom value if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_table_get_table_cell_border_color_bottom
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->table_cell_border_color_bottom < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->table_cell_border_color_bottom > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_border_color_bottom);
}


/*!
 * \brief Set the \c table_cell_border_color_bottom for a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_border_color_bottom
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t table_cell_border_color_bottom
                /*!< the \c table_cell_border_color_bottom value to
                 * be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table_cell_border_color_bottom < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (table_cell_border_color_bottom > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->table_cell_border_color_bottom = table_cell_border_color_bottom;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c table_cell_border_color_vertical value from a DXF
 * \c TABLE entity.
 *
 * \return \c table_cell_border_color_vertical value if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_table_get_table_cell_border_color_vertical
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->table_cell_border_color_vertical < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->table_cell_border_color_vertical > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_border_color_vertical);
}


/*!
 * \brief Set the \c table_cell_border_color_vertical for a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_border_color_vertical
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t table_cell_border_color_vertical
                /*!< the \c table_cell_border_color_vertical value to
                 * be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table_cell_border_color_vertical < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (table_cell_border_color_vertical > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->table_cell_border_color_vertical = table_cell_border_color_vertical;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c table_cell_border_color_right value from a DXF
 * \c TABLE entity.
 *
 * \return \c table_cell_border_color_right value if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_table_get_table_cell_border_color_right
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (table->table_cell_border_color_right < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (table->table_cell_border_color_right > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_border_color_right);
}


/*!
 * \brief Set the \c table_cell_border_color_right for a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_border_color_right
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t table_cell_border_color_right
                /*!< the \c table_cell_border_color_right value to
                 * be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table_cell_border_color_right < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (table_cell_border_color_right > DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        table->table_cell_border_color_right = table_cell_border_color_right;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c flow_direction value from a DXF \c TABLE entity.
 *
 * \return \c flow_direction value if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int16_t
dxf_table_get_flow_direction
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->flow_direction);
}


/*!
 * \brief Set the \c flow_direction for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_flow_direction
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t flow_direction
                /*!< the \c flow_direction value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->flow_direction = flow_direction;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the \c table_value_flag from a DXF \c TABLE entity.
 *
 * \return \c table_value_flag if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int32_t
dxf_table_get_table_value_flag
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_value_flag);
}


/*!
 * \brief Set the \c table_value_flag for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_value_flag
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t table_value_flag
                /*!< the \c table_value_flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->table_value_flag = table_value_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c number_of_rows from a DXF \c TABLE entity.
 * \return \c number_of_rows if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int32_t
dxf_table_get_number_of_rows
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->number_of_rows);
}


/*!
 * \brief Set the \c number_of_rows for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_number_of_rows
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t number_of_rows
                /*!< the \c number_of_rows value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->number_of_rows = number_of_rows;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c number_of_columns from a DXF \c TABLE entity.
 * \return \c number_of_columns if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int32_t
dxf_table_get_number_of_columns
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->number_of_columns);
}


/*!
 * \brief Set the \c number_of_columns for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_number_of_columns
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t number_of_columns
                /*!< the \c number_of_columns value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->number_of_columns = number_of_columns;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c override_flag from a DXF \c TABLE entity.
 * \return \c override_flag if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int32_t
dxf_table_get_override_flag
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->override_flag);
}


/*!
 * \brief Set the \c override_flag for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_override_flag
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t override_flag
                /*!< the \c override_flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->override_flag = override_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c border_color_override_flag from a DXF \c TABLE entity.
 * \return \c border_color_override_flag if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int32_t
dxf_table_get_border_color_override_flag
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->border_color_override_flag);
}


/*!
 * \brief Set the \c border_color_override_flag for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_border_color_override_flag
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t border_color_override_flag
                /*!< the \c border_color_override_flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->border_color_override_flag = border_color_override_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c border_lineweight_override_flag from a DXF \c TABLE entity.
 * \return \c border_lineweight_override_flag if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int32_t
dxf_table_get_border_lineweight_override_flag
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->border_lineweight_override_flag);
}


/*!
 * \brief Set the \c border_lineweight_override_flag for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_border_lineweight_override_flag
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t border_lineweight_override_flag
                /*!< the \c border_lineweight_override_flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->border_lineweight_override_flag = border_lineweight_override_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c border_visibility_override_flag from a DXF \c TABLE entity.
 * \return \c border_visibility_override_flag if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int32_t
dxf_table_get_border_visibility_override_flag
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->border_visibility_override_flag);
}


/*!
 * \brief Set the \c border_visibility_override_flag for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_border_visibility_override_flag
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int32_t border_visibility_override_flag
                /*!< the \c border_visibility_override_flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->border_visibility_override_flag = border_visibility_override_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c table_text_height from a DXF \c TABLE entity.
 * \return \c table_text_height if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_table_get_table_text_height
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_text_height);
}


/*!
 * \brief Set the \c table_text_height for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_text_height
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double table_text_height
                /*!< the \c table_text_height value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->table_text_height = table_text_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c row_height from a DXF \c TABLE entity.
 * \return \c row_height if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_table_get_row_height
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->row_height);
}


/*!
 * \brief Set the \c row_height for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_row_height
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double row_height
                /*!< the \c row_height value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->row_height = row_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c column_height from a DXF \c TABLE entity.
 * \return \c column_height if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
double
dxf_table_get_column_height
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->column_height);
}


/*!
 * \brief Set the \c column_height for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_column_height
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double column_height
                /*!< the \c column_height value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->column_height = column_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c table_cell_alignment from a DXF \c TABLE entity.
 * \return \c table_cell_alignment if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int
dxf_table_get_table_cell_alignment
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_alignment);
}


/*!
 * \brief Set the \c table_cell_alignment for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_alignment
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int table_cell_alignment
                /*!< the \c table_cell_alignment value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->table_cell_alignment = table_cell_alignment;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c table_cell_border_lineweight_right from a DXF
 * \c TABLE entity.
 * \return \c table_cell_border_lineweight_right if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
double
dxf_table_get_table_cell_border_lineweight_right
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_border_lineweight_right);
}


/*!
 * \brief Set the \c table_cell_border_lineweight_right for a DXF
 * \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_border_lineweight_right
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        double table_cell_border_lineweight_right
                /*!< the \c table_cell_border_lineweight_right value to
                 * be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->table_cell_border_lineweight_right = table_cell_border_lineweight_right;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c table_data_version from a DXF \c TABLE entity.
 * \return \c table_data_version if successful, or \c EXIT_FAILURE when
 * an error occurred.
 */
int16_t
dxf_table_get_table_data_version
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_data_version);
}


/*!
 * \brief Set the \c table_data_version for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_data_version
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t table_data_version
                /*!< the \c table_data_version value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->table_data_version = table_data_version;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c suppress_table_title from a DXF \c TABLE entity.
 * \return \c suppress_table_title if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int16_t
dxf_table_get_suppress_table_title
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->suppress_table_title);
}


/*!
 * \brief Set the \c suppress_table_title for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_suppress_table_title
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t suppress_table_title
                /*!< the \c suppress_table_title value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->suppress_table_title = suppress_table_title;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c suppress_header_row from a DXF \c TABLE entity.
 * \return \c suppress_header_row if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
int16_t
dxf_table_get_suppress_header_row
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->suppress_header_row);
}


/*!
 * \brief Set the \c suppress_header_row for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_suppress_header_row
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t suppress_header_row
                /*!< the \c suppress_header_row value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->suppress_header_row = suppress_header_row;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c table_cell_color_fill_override from a DXF
 * \c TABLE entity.
 * \return \c table_cell_color_fill_override if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int16_t
dxf_table_get_table_cell_color_fill_override
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->table_cell_color_fill_override);
}


/*!
 * \brief Set the \c table_cell_color_fill_override for a DXF \c TABLE
 * entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_table_cell_color_fill_override
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        int16_t table_cell_color_fill_override
                /*!< the \c table_cell_color_fill_override value to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->table_cell_color_fill_override = table_cell_color_fill_override;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c tablestyle_object_pointer from a DXF \c TABLE
 * entity.
 * \return \c tablestyle_object_pointer if successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
char *
dxf_table_get_tablestyle_object_pointer
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->tablestyle_object_pointer);
}


/*!
 * \brief Set the \c tablestyle_object_pointer for a DXF \c TABLE
 * entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_tablestyle_object_pointer
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *tablestyle_object_pointer
                /*!< the \c tablestyle_object_pointer value to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->tablestyle_object_pointer = tablestyle_object_pointer;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c owning_block_pointer from a DXF \c TABLE entity.
 * \return \c owning_block_pointer if successful, or \c EXIT_FAILURE
 * when an error occurred.
 */
char *
dxf_table_get_owning_block_pointer
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->owning_block_pointer);
}


/*!
 * \brief Set the \c owning_block_pointer for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_owning_block_pointer
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        char *owning_block_pointer
                /*!< the \c owning_block_pointer value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->owning_block_pointer = owning_block_pointer;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 *
 * \brief Get the \c cells from a DXF \c TABLE entity.
 * \return \c cells if successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
struct DxfTableCell *
dxf_table_get_cells
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table->cells);
}


/*!
 * \brief Set a pointer to \c cells pointer for a DXF \c TABLE entity.
 *
 * \return a pointer to \c table when sucessful, \c NULL when an error
 * occurred.
 */
DxfTable *
dxf_table_set_cells
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        struct DxfTableCell *cells
                /*!< a pointer to \c cells to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        table->cells = cells;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the pointer to the next \c TABLE entity from a DXF 
 * \c TABLE entity.
 *
 * \return pointer to the next \c TABLE entity, or \c NULL when an error
 * occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfTable *
dxf_table_get_next
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfTable *) table->next);
}


/*!
 * \brief Set the pointer to the next \c TABLE for a DXF \c TABLE
 * entity.
 *
 * \return a pointer to \c table when successful, or \c NULL when an
 * error occurred.
 */
DxfTable *
dxf_table_set_next
(
        DxfTable *table,
                /*!< a pointer to a DXF \c TABLE entity. */
        DxfTable *next
                /*!< a pointer to the next \c TABLE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
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
        table->next = (struct DxfTable *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (table);
}


/*!
 * \brief Get the pointer to the last \c TABLE entity from a linked
 * list of DXF \c TABLE entities.
 *
 * \return pointer to the last \c TABLE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfTable *
dxf_table_get_last
(
        DxfTable *table
                /*!< a pointer to a DXF \c TABLE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (table == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (table->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfTable *) table);
        }
        DxfTable *iter = (DxfTable *) table->next;
        while (iter->next != NULL)
        {
                iter = (DxfTable *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfTable *) iter);
}


/* EOF */
