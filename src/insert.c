/*!
 * \file insert.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF insert entity (\c INSERT).
 *
 * A DXF \c INSERT entity is an insertion for a (external) \c BLOCK entity.\n
 * Whilst a \c BLOCK only resides in the block table only once as a
 * definition, an \c INSERT entity can insert blocks as singlular entities
 * and also as [rectanglar, polar] arrays in the drawing.
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
 * \brief Allocate memory for a \c DxfArc.
 *
 * Fill the memory contents with zeros.
 */
DxfInsert *
dxf_insert_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_insert_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfInsert *dxf_insert = NULL;
        size_t size;

        size = sizeof (DxfInsert);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_insert = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_insert_new () could not allocate memory for a DxfInsert struct.\n");
                dxf_insert = NULL;
        }
        else
        {
                memset (dxf_insert, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_insert_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_insert);
}


/*!
 * \brief Write DXF output to fp for an insert entity.
 */
int
dxf_insert_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *block_name,
                /*!< group code = 2. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, if omitted defaults to BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * base point. */
        double y0,
                /*!< group code = 20\n
                 * base point. */
        double z0,
                /*!< group code = 30\n
                 * base point. */
        double thickness,
                /*!< group code = 39\n
                 * optional, if omitted defaults to 0.0. */
        double rel_x_scale,
                /*!< group code = 41\n
                 * optional, if omitted defaults to 1.0. */
        double rel_y_scale,
                /*!< group code = 42\n
                 * optional, if omitted defaults to 1.0. */
        double rel_z_scale,
                /*!< group code = 43\n
                 * optional, if omitted defaults to 1.0. */
        double column_spacing,
                /*!< group code = 44\n
                 * optional, if omitted defaults to 0.0. */
        double row_spacing,
                /*!< group code = 45\n
                 * optional, if omitted defaults to 0.0. */
        double rot_angle,
                /*!< group code = 50\n
                 * optional, if omitted defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, if omitted defaults to BYLAYER. */
        int attribute_follows,
                /*!< group code = 66\n
                 * optional, if omitted defaults to 0. */
        int paperspace,
                /*!< group code = 67\n
                 * optional, if omitted defaults to 0 (modelspace). */
        int columns,
                /*!< group code = 70\n
                 * optional, if omitted defaults to 1. */
        int rows
                /*!< group code = 71\n
                 * optional, if omitted defaults to 1. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_insert_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("INSERT");

        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_insert_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0.\n",
                        dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_insert_write_lowlevel () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default relative X-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                rel_x_scale = 1.0;
        }
        if (rel_y_scale == 0.0)
        {
                fprintf (stderr, "Warning dxf_insert_write_lowlevel () relative Y-scale factor has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default relative Y-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                rel_y_scale = 1.0;
        }
        if (rel_z_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_insert_write_lowlevel () relative Z-scale factor has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default relative Z-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                rel_z_scale = 1.0;
        }
        if ((columns > 1) && (column_spacing == 0.0))
        {
                fprintf (stderr, "Warning in dxf_insert_write_lowlevel () number of columns is greater than 1 and the column spacing has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default number of columns value of 1 applied to %s entity.\n",
                        dxf_entity_name);
                columns = 1;
        }
        if ((rows > 1) && (row_spacing == 0.0))
        {
                fprintf (stderr, "Warning in dxf_insert_write_lowlevel () number of rows is greater than 1 and the row spacing has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    default number of rows value of 1 applied to %s entity.\n",
                        dxf_entity_name);
                rows = 1;
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  2\n%s\n", block_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        if (rel_x_scale != 1.0)
        {
                fprintf (fp, " 41\n%f\n", rel_x_scale);
        }
        if (rel_y_scale != 1.0)
        {
                fprintf (fp, " 42\n%f\n", rel_y_scale);
        }
        if (rel_z_scale != 1.0)
        {
                fprintf (fp, " 43\n%f\n", rel_z_scale);
        }
        if ((columns > 1) && (column_spacing > 0.0))
        {
                fprintf (fp, " 44\n%f\n", column_spacing);
        }
        if ((rows > 1) && (row_spacing > 0.0))
        {
                fprintf (fp, " 45\n%f\n", row_spacing);
        }
        if (rot_angle != 0.0)
        {
                fprintf (fp, " 50\n%f\n", rot_angle);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (attribute_follows != 0)
        {
                fprintf (fp, " 66\n%d\n", attribute_follows);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        if (columns > 1)
        {
                fprintf (fp, " 70\n%d\n", columns);
        }
        if (rows > 1)
        {
                fprintf (fp, " 71\n%d\n", rows);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_insert2 () function.\n",
                __FILE__, __LINE__);
#endif
                return (EXIT_SUCCESS);
}

/*!
 * \brief Write DXF output to fp for an insert entity.
 */
int
dxf_insert_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfInsert dxf_insert
                /*!< DXF insert entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_insert_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("INSERT");

        if (strcmp (dxf_insert.layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_insert_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_insert.id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0.\n",
                        dxf_entity_name);
                dxf_insert.layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_insert.rel_x_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_insert_write () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_insert.id_code);
                fprintf (stderr, "    default relative X-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_insert.rel_x_scale = 1.0;
        }
        if (dxf_insert.rel_y_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_insert_write () relative Y-scale factor has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_insert.id_code);
                fprintf (stderr, "    default relative Y-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_insert.rel_y_scale = 1.0;
        }
        if (dxf_insert.rel_z_scale == 0.0)
        {
                fprintf (stderr, "Warning in dxf_insert_write () relative Z-scale factor has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_insert.id_code);
                fprintf (stderr, "    default relative Z-scale of 1.0 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_insert.rel_z_scale = 1.0;
        }
        if ((dxf_insert.columns > 1) && (dxf_insert.column_spacing == 0.0))
        {
                fprintf (stderr, "Warning in dxf_insert_write () number of columns is greater than 1 and the column spacing has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_insert.id_code);
                fprintf (stderr, "    default number of columns value of 1 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_insert.columns = 1;
        }
        if ((dxf_insert.rows > 1) && (dxf_insert.row_spacing == 0.0))
        {
                fprintf (stderr, "Warning in dxf_insert_write () number of rows is greater than 1 and the row spacing has a value of 0.0 for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_insert.id_code);
                fprintf (stderr, "    default number of rows value of 1 applied to %s entity.\n",
                        dxf_entity_name);
                dxf_insert.rows = 1;
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  2\n%s\n", dxf_insert.block_name);
        if (dxf_insert.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_insert.id_code);
        }
        if (strcmp (dxf_insert.linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_insert.linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_insert.layer);
        fprintf (fp, " 10\n%f\n", dxf_insert.x0);
        fprintf (fp, " 20\n%f\n", dxf_insert.y0);
        fprintf (fp, " 30\n%f\n", dxf_insert.z0);
        if (dxf_insert.thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_insert.thickness);
        }
        if (dxf_insert.rel_x_scale != 1.0)
        {
                fprintf (fp, " 41\n%f\n", dxf_insert.rel_x_scale);
        }
        if (dxf_insert.rel_y_scale != 1.0)
        {
                fprintf (fp, " 42\n%f\n", dxf_insert.rel_y_scale);
        }
        if (dxf_insert.rel_z_scale != 1.0)
        {
                fprintf (fp, " 43\n%f\n", dxf_insert.rel_z_scale);
        }
        if ((dxf_insert.columns > 1) && (dxf_insert.column_spacing > 0.0))
        {
                fprintf (fp, " 44\n%f\n", dxf_insert.column_spacing);
        }
        if ((dxf_insert.rows > 1) && (dxf_insert.row_spacing > 0.0))
        {
                fprintf (fp, " 45\n%f\n", dxf_insert.row_spacing);
        }
        if (dxf_insert.rot_angle != 0.0)
        {
                fprintf (fp, " 50\n%f\n", dxf_insert.rot_angle);
        }
        if (dxf_insert.color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_insert.color);
        }
        if (dxf_insert.attribute_follows != 0)
        {
                fprintf (fp, " 66\n%d\n", dxf_insert.attribute_follows);
        }
        if (dxf_insert.paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        if (dxf_insert.columns > 1)
        {
                fprintf (fp, " 70\n%d\n", dxf_insert.columns);
        }
        if (dxf_insert.rows > 1)
        {
                fprintf (fp, " 71\n%d\n", dxf_insert.rows);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_insert_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

/* EOF */
