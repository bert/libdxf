/*!
 * \file xline.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020. 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF xline entity (\c XLINE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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


#include "xline.h"


/*!
 * \brief Allocate memory for a \c DxfXLine.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfXLine *
dxf_xline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfXLine *xline = NULL;
        size_t size;

        size = sizeof (DxfXLine);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((xline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfXLine struct.\n")),
                  __FUNCTION__);
                xline = NULL;
        }
        else
        {
                memset (xline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Allocate memory and initialize data fields in an \c XLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfXLine *
dxf_xline_init
(
        DxfXLine *xline
                /*!< a pointer to the DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                xline = dxf_xline_new ();
        }
        if (xline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfXLine struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        xline->id_code = 0;
        xline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        xline->layer = strdup (DXF_DEFAULT_LAYER);
        xline->elevation = 0.0;
        xline->thickness = 0.0;
        xline->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        xline->visibility = DXF_DEFAULT_VISIBILITY;
        xline->color = DXF_COLOR_BYLAYER;
        xline->paperspace = DXF_MODELSPACE;
        xline->graphics_data_size = 0;
        xline->shadow_mode = 0;
        xline->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        xline->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) xline->binary_graphics_data);
        xline->dictionary_owner_soft = strdup ("");
        xline->material = strdup ("");
        xline->dictionary_owner_hard = strdup ("");
        xline->lineweight = 0;
        xline->plot_style_name = strdup ("");
        xline->color_value = 0;
        xline->color_name = strdup ("");
        xline->transparency = 0;
        xline->p0 = (DxfPoint *) dxf_point_new ();
        xline->p0 = dxf_point_init ((DxfPoint *) xline->p0);
        xline->p0->x0 = 0.0;
        xline->p0->y0 = 0.0;
        xline->p0->z0 = 0.0;
        xline->p1 = (DxfPoint *) dxf_point_new ();
        xline->p1 = dxf_point_init ((DxfPoint *) xline->p1);
        xline->p1->x0 = 0.0;
        xline->p1->y0 = 0.0;
        xline->p1->z0 = 0.0;
        xline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Read data from a DXF file into a DXF \c XLINE entity.
 *
 * The last line read from file contained the string "XLINE". \n
 * Now follows some data for the \c XLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c xline.
 *
 * \return a pointer to \c xline.
 */
DxfXLine *
dxf_xline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfXLine *xline
                /*!< a pointer to the DXF \c XLINE entity. */
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
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                xline = dxf_xline_init (xline);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                xline->p0 = dxf_point_init (xline->p0);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                xline->p1 = dxf_point_init (xline->p1);
        }
        if (xline->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                xline->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) xline->binary_graphics_data);
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
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &xline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, xline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, xline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->p1->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &xline->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &xline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &xline->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &xline->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &xline->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbXline") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &xline->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &xline->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, xline->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) xline->binary_graphics_data->next);
                        xline->binary_graphics_data = (DxfBinaryGraphicsData *) xline->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, xline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, xline->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, xline->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &xline->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, xline->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &xline->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, xline->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &xline->transparency);
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
        if (strcmp (xline->linetype, "") == 0)
        {
                xline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (xline->layer, "") == 0)
        {
                xline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Write DXF output to fp for a DXF \c XLINE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occured.
 */
int
dxf_xline_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfXLine *xline
                /*!< a pointer to the DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("XLINE");

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
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (xline->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () entity contains no binary graphics data.\n")),
                  __FUNCTION__);
        }
        if ((xline->p0->x0 == xline->p1->x0)
                && (xline->p0->y0 == xline->p1->y0)
                && (xline->p0->z0 == xline->p1->z0))
        {
                fprintf (stderr,
                  (_("Error in %s () start point and end point are identical for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, xline->id_code);
                dxf_entity_skip (dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (xline->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, xline->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                xline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (xline->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", xline->id_code);
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
        if ((strcmp (xline->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", xline->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (xline->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", xline->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (xline->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", xline->layer);
        if (strcmp (xline->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", xline->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (xline->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", xline->material);
        }
        if (xline->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", xline->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", xline->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (xline->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", xline->elevation);
        }
        if (xline->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", xline->linetype_scale);
        }
        if (xline->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", xline->visibility);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
          && (xline->binary_graphics_data)
          && (xline->graphics_data_size > 0))
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", xline->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", xline->graphics_data_size);
#endif
                if (xline->binary_graphics_data)
                {
                        DxfBinaryGraphicsData *iter;
                        iter = xline->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", dxf_binary_graphics_data_get_data_line (iter));
                                iter = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_get_next (iter);
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", xline->color_value);
                fprintf (fp->fp, "430\n%s\n", xline->color_name);
                fprintf (fp->fp, "440\n%ld\n", xline->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", xline->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", xline->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbXline\n");
        }
        if (xline->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", xline->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", xline->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", xline->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", xline->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", xline->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", xline->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", xline->p1->z0);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c XLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_xline_free
(
        DxfXLine *xline
                /*!< a pointer to the memory occupied by the DXF \c XLINE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (xline->linetype);
        free (xline->layer);
        dxf_binary_graphics_data_free_list (xline->binary_graphics_data);
        free (xline->dictionary_owner_soft);
        free (xline->material);
        free (xline->dictionary_owner_hard);
        free (xline->plot_style_name);
        free (xline->color_name);
        dxf_point_free (xline->p0);
        dxf_point_free (xline->p1);
        free (xline);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c XLINE entities and all their data fields.
 */
void
dxf_xline_free_list
(
        DxfXLine *xlines
                /*!< a pointer to the single linked list of DXF \c XLINE
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (xlines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (xlines != NULL)
        {
                DxfXLine *iter = (DxfXLine *) xlines->next;
                dxf_xline_free (xlines);
                xlines = (DxfXLine *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c XLINE entity.
 *
 * \return ID code.
 */
int
dxf_xline_get_id_code
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_id_code
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
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
        if (xline == NULL)
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
        xline->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the linetype from a DXF \c XLINE entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_xline_get_linetype
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (xline->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_linetype
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the layer from a DXF \c XLINE entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_xline_get_layer
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (xline->layer));
}


/*!
 * \brief Set the layer for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_layer
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the elevation from a DXF \c XLINE entity.
 *
 * \return \c elevation.
 */
double
dxf_xline_get_elevation
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_elevation
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the thickness from a DXF \c XLINE entity.
 *
 * \return \c thickness.
 */
double
dxf_xline_get_thickness
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_thickness
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the linetype scale from a DXF \c XLINE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_xline_get_linetype_scale
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_linetype_scale
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c visibility from a DXF \c XLINE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_xline_get_visibility
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c LINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_visibility
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c color from a DXF \c XLINE entity.
 *
 * \return \c color.
 */
int
dxf_xline_get_color
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->color);
}


/*!
 * \brief Set the \c color for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_color
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c XLINE entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_xline_get_paperspace
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (xline->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_paperspace
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative paperspace value was passed.\n")),
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
        xline->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c XLINE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_xline_get_graphics_data_size
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (xline->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_graphics_data_size
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c XLINE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_xline_get_shadow_mode
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c XLINE entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_shadow_mode
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
                  (_("Error in %s () an out of range was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c XLINE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_xline_get_binary_graphics_data
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) xline->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_binary_graphics_data
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c XLINE entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_xline_get_dictionary_owner_soft
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (xline->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_dictionary_owner_soft
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_xline_get_material
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (xline->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_material
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c XLINE entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_xline_get_dictionary_owner_hard
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (xline->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_dictionary_owner_hard
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c lineweight from a DXF \c XLINE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_xline_get_lineweight
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c XLINE entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_lineweight
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c XLINE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_xline_get_plot_style_name
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (xline->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c XLINE entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_plot_style_name
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c color_value from a DXF \c XLINE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_xline_get_color_value
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c XLINE entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_color_value
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c color_name from a DXF \c XLINE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_xline_get_color_name
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (xline->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c XLINE entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_color_name
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the \c transparency from a DXF \c XLINE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_xline_get_transparency
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c XLINE entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_transparency
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the start point \c p0 of a DXF \c XLINE entity.
 *
 * \return the start point \c p0.
 */
DxfPoint *
dxf_xline_get_p0
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) xline->p0);
}


/*!
 * \brief Set the start point \c p0 of a DXF \c XLINE entity.
 *
 * \return a pointer to a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_p0
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the X-value of the start point \c x0 of a DXF \c XLINE
 * entity.
 *
 * \return the X-value of the start point \c x0.
 */
double
dxf_xline_get_x0
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->p0->x0);
}


/*!
 * \brief Set the X-value of the start point \c x0 of a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_x0
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double x0
                /*!< the X-value of the start point \c x0 of a DXF
                 * \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the Y-value of the start point \c y0 of a DXF
 * \c XLINE entity.
 *
 * \return the Y-value of the start point \c y0.
 */
double
dxf_xline_get_y0
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->p0->y0);
}


/*!
 * \brief Set the Y-value of the start point \c y0 of a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_y0
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double y0
                /*!< the Y-value of the start point \c y0 of a DXF
                 * \c xline entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the Z-value of the start point \c z0 of a DXF \c XLINE
 * entity.
 *
 * \return the Z-value of the start point \c z0.
 */
double
dxf_xline_get_z0
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->p0->z0);
}


/*!
 * \brief Set the Z-value of the start point \c z0 of a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_z0
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double z0
                /*!< the Z-value of the start point \c z0 of a DXF
                 * \c xline entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the end point \c p1 of a DXF \c XLINE entity.
 *
 * \return the end point \c p1.
 */
DxfPoint *
dxf_xline_get_p1
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->p1);
}


/*!
 * \brief Set the end point \c p1 of a DXF \c XLINE entity.
 *
 * \return a pointer to a DXF \c XLINE entity.
 */
DxfXLine *
dxf_xline_set_p1
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the X-value of the end point \c x1 of a DXF \c XLINE
 * entity.
 *
 * \return the X-value of the end point \c x1.
 */
double
dxf_xline_get_x1
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->p1->x0);
}


/*!
 * \brief Set the X-value of the end point \c x1 of a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_x1
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double x1
                /*!< the X-value of the end point \c x1 of a DXF
                 * \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the Y-value of the end point \c y1 of a DXF
 * \c XLINE entity.
 *
 * \return the Y-value of the end point \c y1.
 */
double
dxf_xline_get_y1
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->p1->y0);
}


/*!
 * \brief Set the Y-value of the end point \c y1 of a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_y1
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double y1
                /*!< the Y-value of the end point \c y1 of a DXF
                 * \c xline entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the Z-value of the end point \c z1 of a DXF \c XLINE
 * entity.
 *
 * \return the Z-value of the end point \c z1.
 */
double
dxf_xline_get_z1
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline->p1->z0);
}


/*!
 * \brief Set the Z-value of the end point \c z1 of a DXF \c XLINE
 * entity.
 *
 * \return a pointer to \c xline when successful, or \c NULL when an
 * error occurred.
 */
DxfXLine *
dxf_xline_set_z1
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        double z1
                /*!< the Z-value of the end point \c z1 of a DXF
                 * \c xline entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        xline->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the pointer to the next \c XLINE entity from a DXF 
 * \c XLINE entity.
 *
 * \return pointer to the next \c XLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfXLine *
dxf_xline_get_next
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfXLine *) xline->next);
}


/*!
 * \brief Set the pointer to the next \c XLINE for a DXF \c XLINE
 * entity.
 */
DxfXLine *
dxf_xline_set_next
(
        DxfXLine *xline,
                /*!< a pointer to a DXF \c XLINE entity. */
        DxfXLine *next
                /*!< a pointer to the next \c XLINE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
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
        xline->next = (struct DxfXLine *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (xline);
}


/*!
 * \brief Get the pointer to the last \c XLINE entity from a linked list
 * of DXF \c XLINE entities.
 *
 * \return pointer to the last \c XLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfXLine *
dxf_xline_get_last
(
        DxfXLine *xline
                /*!< a pointer to a DXF \c XLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (xline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xline->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfXLine *) xline);
        }
        DxfXLine *iter = (DxfXLine *) xline->next;
        while (iter->next != NULL)
        {
                iter = (DxfXLine *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfXLine *) iter);
}


/* EOF */
