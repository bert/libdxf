/*!
 * \file shape.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF shape entity (\c SHAPE).
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


#include "shape.h"


/*!
 * \brief Allocate memory for a \c DxfShape.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfShape *
dxf_shape_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfShape *dxf_shape = NULL;
        size_t size;

        size = sizeof (DxfShape);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_shape = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfShape struct.\n")),
                  __FUNCTION__);
                dxf_shape = NULL;
        }
        else
        {
                memset (dxf_shape, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_shape);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SHAPE 
 * entity to default values.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfShape *
dxf_shape_init
(
        DxfShape *dxf_shape
                /*!< DXF shape entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_shape == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_shape = dxf_shape_new ();
        }
        if (dxf_shape == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfShape struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_shape->id_code = 0;
        dxf_shape->shape_name = strdup ("");
        dxf_shape->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_shape->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_shape->elevation = 0.0;
        dxf_shape->thickness = 0.0;
        dxf_shape->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_shape->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_shape->color = DXF_COLOR_BYLAYER;
        dxf_shape->paperspace = DXF_MODELSPACE;
        dxf_shape->dictionary_owner_soft = strdup ("");
        dxf_shape->dictionary_owner_hard = strdup ("");
        dxf_shape->x0 = 0.0;
        dxf_shape->y0 = 0.0;
        dxf_shape->z0 = 0.0;
        dxf_shape->extr_x0 = 0.0;
        dxf_shape->extr_y0 = 0.0;
        dxf_shape->extr_z0 = 0.0;
        dxf_shape->size = 0.0;
        dxf_shape->rel_x_scale = 0.0;
        dxf_shape->rot_angle = 0.0;
        dxf_shape->obl_angle = 0.0;
        dxf_shape->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_shape);
}


/*!
 * \brief Read data from a DXF file into a \c SHAPE entity.
 *
 * The last line read from file contained the string "SHAPE". \n
 * Hereafter follows some data for the \c SHAPE, to be terminated with
 * a "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 *
 * \return a pointer to \c dxf_shape.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfShape *
dxf_shape_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfShape *dxf_shape
                /*!< DXF shape entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        char *dxf_entity_name = strdup ("SHAPE");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dxf_shape == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_shape = dxf_shape_new ();
                dxf_shape = dxf_shape_init (dxf_shape);
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
                        return (NULL);
                }
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a shape
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_shape->shape_name);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_shape->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_shape->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_shape->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_shape->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * size. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->size);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * relative X scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->rel_x_scale);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->rot_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * oblique angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->obl_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_shape->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_shape->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_shape->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbShape") != 0)))
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
                        fscanf (fp->fp, "%lf\n", &dxf_shape->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_shape->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_shape->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_shape->dictionary_owner_hard);
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
        /* Handle omitted members and/or illegal values. */
        if (strcmp (dxf_shape->shape_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_shape->id_code);
                return (NULL);
        }
        if (strcmp (dxf_shape->linetype, "") == 0)
        {
                dxf_shape->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_shape->layer, "") == 0)
        {
                dxf_shape->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_shape);
}


/*!
 * \brief Write DXF output for a DXF \c SHAPE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_shape_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfShape *dxf_shape
                /*!< DXF shape entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SHAPE");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_shape == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_shape->shape_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_shape->id_code);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_shape->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_shape->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_shape->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_shape->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_shape->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_shape->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_shape->size == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () size has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_shape->id_code);
        }
        if (dxf_shape->rel_x_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning: in %s () relative X-scale factor has a value of 0.0 for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_shape->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_shape->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_shape->id_code);
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
        if ((strcmp (dxf_shape->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_shape->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_shape->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_shape->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_shape->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_shape->layer);
        if (strcmp (dxf_shape->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_shape->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_shape->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_shape->elevation);
        }
        if (dxf_shape->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_shape->color);
        }
        if (dxf_shape->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_shape->linetype_scale);
        }
        if (dxf_shape->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_shape->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbShape\n");
        }
        if (dxf_shape->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_shape->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_shape->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_shape->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_shape->z0);
        fprintf (fp->fp, " 40\n%f\n", dxf_shape->size);
        fprintf (fp->fp, "  2\n%s\n", dxf_shape->shape_name);
        if (dxf_shape->rot_angle != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", dxf_shape->rot_angle);
        }
        if (dxf_shape->rel_x_scale != 1.0)
        {
                fprintf (fp->fp, " 41\n%f\n", dxf_shape->rel_x_scale);
        }
        if (dxf_shape->obl_angle != 0.0)
        {
                fprintf (fp->fp, " 51\n%f\n", dxf_shape->obl_angle);
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (dxf_shape->extr_x0 != 0.0)
                && (dxf_shape->extr_y0 != 0.0)
                && (dxf_shape->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", dxf_shape->extr_x0);
                fprintf (fp->fp, "220\n%f\n", dxf_shape->extr_y0);
                fprintf (fp->fp, "230\n%f\n", dxf_shape->extr_z0);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SHAPE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_shape_free
(
        DxfShape *dxf_shape
                /*!< Pointer to the memory occupied by the DXF \c SHAPE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_shape->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfShape was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_shape->shape_name);
        free (dxf_shape->linetype);
        free (dxf_shape->layer);
        free (dxf_shape->dictionary_owner_soft);
        free (dxf_shape->dictionary_owner_hard);
        free (dxf_shape);
        dxf_shape = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
