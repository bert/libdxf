/*!
 * \file solid.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2017, 2018, 2019,
 * 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF solid entity (\c SOLID).
 *
 * A DXF \c SOLID entity is a filled shape made with up to four point
 * (X, Y, Z)-coordinates.\n
 * A filled triangle can be formed by duplicating the third coordinate at the
 * fourth coordinate position.\n
 * A diabolo shaped solid can be formed by "twisting" the \c SOLID form in it's
 * plane, by "swapping" the third and fourth coordinate set.
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


#include "solid.h"


/*!
 * \brief Allocate memory for a DXF \c SOLID entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return a pointer to the allocated memory.
 */
DxfSolid *
dxf_solid_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSolid *solid = NULL;
        size_t size;

        size = sizeof (DxfSolid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((solid = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSolid struct.\n")),
                  __FUNCTION__);
                solid = NULL;
        }
        else
        {
                memset (solid, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SOLID entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSolid *
dxf_solid_init
(
        DxfSolid *solid
                /*!< a pointer to the DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                solid = dxf_solid_new ();
        }
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSolid struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->id_code = 0;
        solid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        solid->layer = strdup (DXF_DEFAULT_LAYER);
        solid->elevation = 0.0;
        solid->thickness = 0.0;
        solid->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        solid->visibility = DXF_DEFAULT_VISIBILITY;
        solid->color = DXF_COLOR_BYLAYER;
        solid->paperspace = DXF_MODELSPACE;
        solid->graphics_data_size = 0;
        solid->shadow_mode = 0;
        solid->binary_graphics_data = dxf_binary_graphics_data_new ();
        solid->binary_graphics_data = dxf_binary_graphics_data_init (solid->binary_graphics_data);
        solid->dictionary_owner_soft = strdup ("");
        solid->material = strdup ("");
        solid->dictionary_owner_hard = strdup ("");
        solid->lineweight = 0;
        solid->plot_style_name = strdup ("");
        solid->color_value = 0;
        solid->color_name = strdup ("");
        solid->transparency = 0;
        solid->p0 = (DxfPoint *) dxf_point_new ();
        solid->p0 = (DxfPoint *) dxf_point_init ((DxfPoint *) solid->p0);
        solid->p0->x0 = 0.0;
        solid->p0->y0 = 0.0;
        solid->p0->z0 = 0.0;
        solid->p1 = (DxfPoint *) dxf_point_new ();
        solid->p1 = (DxfPoint *) dxf_point_init ((DxfPoint *) solid->p1);
        solid->p1->x0 = 0.0;
        solid->p1->y0 = 0.0;
        solid->p1->z0 = 0.0;
        solid->p2 = (DxfPoint *) dxf_point_new ();
        solid->p2 = (DxfPoint *) dxf_point_init ((DxfPoint *) solid->p2);
        solid->p2->x0 = 0.0;
        solid->p2->y0 = 0.0;
        solid->p2->z0 = 0.0;
        solid->p3 = (DxfPoint *) dxf_point_new ();
        solid->p3 = (DxfPoint *) dxf_point_init ((DxfPoint *) solid->p3);
        solid->p3->x0 = 0.0;
        solid->p3->y0 = 0.0;
        solid->p3->z0 = 0.0;
        solid->extr_x0 = 0.0;
        solid->extr_y0 = 0.0;
        solid->extr_z0 = 0.0;
        solid->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SOLID entity.
 *
 * The last line read from file contained the string "SOLID". \n
 * Now follows some data for the \c SOLID, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 *
 * \return a pointer to the DXF \c SOLID entity when done, or \c NULL
 * when an error occurred while reading from the input file.
 */
DxfSolid *
dxf_solid_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSolid *solid
                /*!< a pointer to the DXF \c SOLID entity. */
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
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                solid = dxf_solid_init (solid);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                solid->p0 = dxf_point_init (solid->p0);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                solid->p1 = dxf_point_new ();
                solid->p1 = dxf_point_init (solid->p1);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                solid->p2 = dxf_point_init (solid->p2);
        }
        if (solid->p3== NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                solid->p3 = dxf_point_init (solid->p3);
        }
        /* Start reading and parsing. */
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
                        fscanf (fp->fp, "%x\n", (uint *) &solid->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, solid->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, solid->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p1->z0);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p2->x0);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p2->y0);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p2->z0);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p3->x0);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p3->y0);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->p3->z0);
                }
                else if (strcmp (temp_string, "38") == 0)
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &solid->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->graphics_data_size);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->extr_z0);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &solid->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, solid->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) solid->binary_graphics_data->next);
                        solid->binary_graphics_data = (DxfBinaryGraphicsData *) solid->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, solid->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, solid->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, solid->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &solid->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, solid->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &solid->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, solid->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &solid->transparency);
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
        if (strcmp (solid->linetype, "") == 0)
        {
                solid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (solid->layer, "") == 0)
        {
                solid->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Write DXF output to fp for a DXF \c SOLID entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_solid_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSolid *solid
                /*!< a pointer to the DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SOLID");

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
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (solid->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, solid->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                solid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (solid->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, solid->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                solid->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (solid->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (solid->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", solid->id_code);
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
        if ((strcmp (solid->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", solid->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (solid->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", solid->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (solid->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", solid->layer);
        if (strcmp (solid->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", solid->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (solid->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", solid->material);
        }
        if (solid->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", solid->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", solid->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (solid->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", solid->elevation);
        }
        if (solid->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", solid->linetype_scale);
        }
        if (solid->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", solid->visibility);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
          && (solid->graphics_data_size > 0))
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", solid->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", solid->graphics_data_size);
#endif
                if (solid->binary_graphics_data != NULL)
                {
                        DxfBinaryGraphicsData *iter;
                        iter = solid->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", dxf_binary_graphics_data_get_data_line (iter));
                                iter = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_get_next (iter);
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", solid->color_value);
                fprintf (fp->fp, "430\n%s\n", solid->color_name);
                fprintf (fp->fp, "440\n%ld\n", solid->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", solid->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", solid->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbTrace\n");
        }
        fprintf (fp->fp, " 10\n%f\n", solid->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", solid->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", solid->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", solid->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", solid->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", solid->p1->z0);
        fprintf (fp->fp, " 12\n%f\n", solid->p2->x0);
        fprintf (fp->fp, " 22\n%f\n", solid->p2->y0);
        fprintf (fp->fp, " 32\n%f\n", solid->p2->z0);
        fprintf (fp->fp, " 13\n%f\n", solid->p3->x0);
        fprintf (fp->fp, " 23\n%f\n", solid->p3->y0);
        fprintf (fp->fp, " 33\n%f\n", solid->p3->z0);
        if (solid->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", solid->thickness);
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (solid->extr_x0 != 0.0)
                && (solid->extr_y0 != 0.0)
                && (solid->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", solid->extr_x0);
                fprintf (fp->fp, "220\n%f\n", solid->extr_y0);
                fprintf (fp->fp, "230\n%f\n", solid->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SOLID and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_solid_free
(
        DxfSolid *solid
                /*!< a pointer to the memory occupied by the DXF \c SOLID
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (solid->linetype);
        free (solid->layer);
        free (solid->dictionary_owner_soft);
        free (solid->dictionary_owner_hard);
        free (solid);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SOLID entities and all their data fields.
 */
void
dxf_solid_free_list
(
        DxfSolid *solids
                /*!< pointer to the single linked list of DXF \c SOLID
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (solids == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (solids != NULL)
        {
                DxfSolid *iter = (DxfSolid *) solids->next;
                dxf_solid_free (solids);
                solids = (DxfSolid *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SOLID entity.
 *
 * \return \c id_code.
 */
int
dxf_solid_get_id_code
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_id_code
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
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
        if (solid == NULL)
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
        solid->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c linetype from a DXF \c SOLID entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_solid_get_linetype
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_linetype
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c layer from a DXF \c SOLID entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_solid_get_layer
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_layer
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c elevation from a DXF \c SOLID entity.
 *
 * \return \c elevation.
 */
double
dxf_solid_get_elevation
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_elevation
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c thickness from a DXF \c SOLID entity.
 *
 * \return \c thickness.
 */
double
dxf_solid_get_thickness
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_thickness
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c SOLID entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_solid_get_linetype_scale
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_linetype_scale
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c visibility from a DXF \c SOLID entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_solid_get_visibility
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (solid->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_visibility
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c color from a DXF \c SOLID entity.
 *
 * \return \c color.
 */
int
dxf_solid_get_color
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->color);
}


/*!
 * \brief Set the \c color for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_color
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c SOLID entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_solid_get_paperspace
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (solid->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_paperspace
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c SOLID entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_solid_get_graphics_data_size
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (solid->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_graphics_data_size
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        solid->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c SOLID entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_solid_get_shadow_mode
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (solid->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_shadow_mode
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c SOLID entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_solid_get_binary_graphics_data
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) solid->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_binary_graphics_data
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SOLID entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_solid_get_dictionary_owner_soft
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_dictionary_owner_soft
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c SOLID entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_solid_get_object_owner_soft
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_object_owner_soft
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c SOLID entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_solid_get_material
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_material
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SOLID entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_solid_get_dictionary_owner_hard
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_dictionary_owner_hard
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c lineweight from a DXF \c SOLID entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_solid_get_lineweight
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_lineweight
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c SOLID entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_solid_get_plot_style_name
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_plot_style_name
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c color_value from a DXF \c SOLID entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_solid_get_color_value
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_color_value
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c color_name from a DXF \c SOLID entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_solid_get_color_name
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_color_name
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c transparency from a DXF \c SOLID entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_solid_get_transparency
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_transparency
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the base point \c p0 of a DXF \c SOLID entity.
 *
 * \return the base point \c p0.
 */
DxfPoint *
dxf_solid_get_p0
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p0);
}


/*!
 * \brief Set the base point \c p0 of a DXF \c SOLID entity.
 *
 * \return a pointer to a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_p0
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the X-value of the base point \c x0 of a DXF \c SOLID
 * entity.
 *
 * \return the X-value of the base point \c x0.
 */
double
dxf_solid_get_x0
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p0->x0);
}


/*!
 * \brief Set the X-value of the base point \c x0 of a DXF \c SOLID
 * entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_x0
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double x0
                /*!< the X-value of the base point \c x0 of a DXF
                 * \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Y-value of the base point \c y0 of a DXF \c SOLID
 * entity.
 *
 * \return the Y-value of the base point \c y0.
 */
double
dxf_solid_get_y0
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p0->y0);
}


/*!
 * \brief Set the Y-value of the base point \c y0 of a DXF \c SOLID
 * entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_y0
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double y0
                /*!< the Y-value of the base point \c y0 of a DXF
                 * \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Z-value of the base point \c z0 of a DXF \c SOLID
 * entity.
 *
 * \return the Z-value of the base point \c z0.
 */
double
dxf_solid_get_z0
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p0->z0);
}


/*!
 * \brief Set the Z-value of the base point \c z0 of a DXF \c SOLID
 * entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_z0
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double z0
                /*!< the Y-value of the base point \c z0 of a DXF
                 * \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the first alignment point \c p1 of a DXF \c SOLID entity.
 *
 * \return the first alignment point \c p1.
 */
DxfPoint *
dxf_solid_get_p1
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p1);
}


/*!
 * \brief Set the first alignment point \c p1 of a DXF \c SOLID entity.
 *
 * \return a pointer to a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_p1
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the X-value of the first alignment point \c x1 of a DXF
 * \c SOLID entity.
 *
 * \return the X-value of the first alignment point \c x1.
 */
double
dxf_solid_get_x1
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p1->x0);
}


/*!
 * \brief Set the X-value of the first alignment point \c x1 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_x1
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double x1
                /*!< the X-value of the first alignment point \c x1 of a
                 * DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Y-value of the first alignment point \c y1 of a DXF
 * \c SOLID entity.
 *
 * \return the Y-value of the first alignment point \c y1.
 */
double
dxf_solid_get_y1
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p1->y0);
}


/*!
 * \brief Set the Y-value of the first alignment point \c y1 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_y1
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double y1
                /*!< the Y-value of the first alignment point \c y1 of a
                 * DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Z-value of the first alignment point \c z1 of a DXF
 * \c SOLID entity.
 *
 * \return the Z-value of the first alignment point \c z1.
 */
double
dxf_solid_get_z1
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p1->z0);
}


/*!
 * \brief Set the Z-value of the first alignment point \c z1 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_z1
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double z1
                /*!< the Z-value of the first alignment point \c z1 of a
                 * DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the second alignment point \c p2 of a DXF \c SOLID entity.
 *
 * \return the second alignment point \c p2.
 */
DxfPoint *
dxf_solid_get_p2
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p2);
}


/*!
 * \brief Set the second alignment point \c p2 of a DXF \c SOLID entity.
 *
 * \return a pointer to a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_p2
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        DxfPoint *p2
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p2 = p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the X-value of the second alignment point \c x2 of a DXF
 * \c SOLID entity.
 *
 * \return the X-value of the second alignment point \c x2.
 */
double
dxf_solid_get_x2
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p2->x0);
}


/*!
 * \brief Set the X-value of the second alignment point \c x2 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_x2
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double x2
                /*!< the X-value of the second alignment point \c x2 of
                 * a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Y-value of the second alignment point \c y2 of a DXF
 * \c SOLID entity.
 *
 * \return the Y-value of the second alignment point \c y2.
 */
double
dxf_solid_get_y2
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p2->y0);
}


/*!
 * \brief Set the Y-value of the second alignment point \c y2 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_y2
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double y2
                /*!< the Y-value of the second alignment point \c y2 of
                 * a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Z-value of the second alignment point \c z2 of a DXF
 * \c SOLID entity.
 *
 * \return the Z-value of the second alignment point \c z2.
 */
double
dxf_solid_get_z2
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p2->z0);
}


/*!
 * \brief Set the Z-value of the second alignment point \c z2 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_z2
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double z2
                /*!< the Z-value of the second alignment point \c z2 of
                 * a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the third alignment point \c p3 of a DXF \c SOLID entity.
 *
 * \return the third alignment point \c p3.
 */
DxfPoint *
dxf_solid_get_p3
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p3);
}


/*!
 * \brief Set the third alignment point \c p3 of a DXF \c SOLID entity.
 *
 * \return a pointer to a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_p3
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        DxfPoint *p3
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p3 = p3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the X-value of the third alignment point \c x3 of a DXF
 * \c SOLID entity.
 *
 * \return the X-value of the third alignment point \c x3.
 */
double
dxf_solid_get_x3
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p3->x0);
}


/*!
 * \brief Set the X-value of the third alignment point \c x3 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_x3
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double x3
                /*!< the X-value of the third alignment point \c x3 of
                 * a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p3->x0 = x3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Y-value of the third alignment point \c y3 of a DXF
 * \c SOLID entity.
 *
 * \return the Y-value of the third alignment point \c y3.
 */
double
dxf_solid_get_y3
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p3->y0);
}


/*!
 * \brief Set the Y-value of the third alignment point \c y3 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_y3
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double y3
                /*!< the Y-value of the third alignment point \c y3 of
                 * a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p3->y0 = y3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Z-value of the third alignment point \c z3 of a DXF
 * \c SOLID entity.
 *
 * \return the Z-value of the third alignment point \c z3.
 */
double
dxf_solid_get_z3
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->p3->z0);
}


/*!
 * \brief Set the Z-value of the third alignment point \c z3 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_z3
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double z3
                /*!< the Z-value of the third alignment point \c z3 of
                 * a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->p3->z0 = z3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c SOLID entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_solid_get_extrusion_vector_as_point
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point = dxf_point_init (point);
        if (point == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        point->x0 = solid->extr_x0;
        point->y0 = solid->extr_y0;
        point->z0 = solid->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF
 * \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_extrusion_vector_from_point
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->extr_x0 = (double) point->x0;
        solid->extr_y0 = (double) point->y0;
        solid->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Set the extrusion vector for a DXF \c SOLID entity.
 */
DxfSolid *
dxf_solid_set_extrusion_vector
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
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
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->extr_x0 = extr_x0;
        solid->extr_y0 = extr_y0;
        solid->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c SOLID entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_solid_get_extr_x0
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_extr_x0
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c SOLID entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_solid_get_extr_y0
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_extr_y0
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c SOLID entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_solid_get_extr_z0
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c SOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
DxfSolid *
dxf_solid_set_extr_z0
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c SOLID entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the next \c SOLID entity from a DXF
 * \c SOLID entity.
 *
 * \return pointer to the next \c SOLID entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSolid *
dxf_solid_get_next
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSolid *) solid->next);
}


/*!
 * \brief Set the pointer to the next \c SOLID for a DXF \c SOLID
 * entity.
 */
DxfSolid *
dxf_solid_set_next
(
        DxfSolid *solid,
                /*!< a pointer to a DXF \c SOLID entity. */
        DxfSolid *next
                /*!< a pointer to the next \c SOLID for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
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
        solid->next = (struct DxfSolid *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the last \c SOLID entity from a linked list
 * of DXF \c SOLID entities.
 *
 * \return pointer to the last \c SOLID entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSolid *
dxf_solid_get_last
(
        DxfSolid *solid
                /*!< a pointer to a DXF \c SOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfSolid *) solid);
        }
        DxfSolid *iter = (DxfSolid *) solid->next;
        while (iter->next != NULL)
        {
                iter = (DxfSolid *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSolid *) iter);
}


/* EOF */
