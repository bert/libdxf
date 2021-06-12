/*!
 * \file surface.c
 *
 * \author Copyright (C) 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF surface entity (\c SURFACE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * \since The \c SURFACE entity was introduced in DXF R2007.
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


#include "surface.h"


/*!
 * \brief Allocate memory for a DXF \c SURFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurface *
dxf_surface_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSurface *surface = NULL;
        size_t size;

        size = sizeof (DxfSurface);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((surface = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                surface = NULL;
        }
        else
        {
                memset (surface, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c SURFACE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurface *
dxf_surface_init
(
        DxfSurface *surface
                /*!< a pointer to the DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                surface = dxf_surface_new ();
        }
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        surface->binary_graphics_data = (DxfBinaryData *) dxf_binary_data_init (surface->binary_graphics_data);
        if (surface->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->proprietary_data = (DxfProprietaryData *) dxf_proprietary_data_init (surface->proprietary_data);
        if (surface->proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->additional_proprietary_data = (DxfProprietaryData *) dxf_proprietary_data_init (surface->additional_proprietary_data);
        if (surface->additional_proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        surface->id_code = 0;
        surface->linetype = strdup (DXF_DEFAULT_LINETYPE);
        surface->layer = strdup (DXF_DEFAULT_LAYER);
        surface->elevation = 0.0;
        surface->thickness = 0.0;
        surface->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        surface->visibility = DXF_DEFAULT_VISIBILITY;
        surface->color = DXF_COLOR_BYLAYER;
        surface->paperspace = DXF_MODELSPACE;
        surface->graphics_data_size = 0;
        surface->shadow_mode = 0;
        surface->dictionary_owner_soft = strdup ("");
        surface->object_owner_soft = strdup ("");
        surface->material = strdup ("");
        surface->dictionary_owner_hard = strdup ("");
        surface->lineweight = 0;
        surface->plot_style_name = strdup ("");
        surface->color_value = 0;
        surface->color_name = strdup ("");
        surface->transparency = 0;
        surface->modeler_format_version_number = 1;
        surface->number_of_U_isolines = 0;
        surface->number_of_V_isolines = 0;
        surface->type = 0;
        surface->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SURFACE entity.
 *
 * The last line read from file contained the string "SURFACE". \n
 * Now follows some data for the \c SURFACE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c surface. \n
 *
 * \return a pointer to \c surface.
 */
DxfSurface *
dxf_surface_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfBinaryData *iter310 = NULL;
        int iter330;
        int i;

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
        if (fp->acad_version_number < AutoCAD_2007)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                surface = dxf_surface_init (surface);
        }
        iter310 = (DxfBinaryData *) surface->binary_graphics_data;
        iter330 = 0;
        i = 1;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "  1") == 0)
                {
                        /* Now follows a string containing proprietary
                         * data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->proprietary_data->line);
                        surface->proprietary_data->order = i;
                        i++;
                        dxf_proprietary_data_init ((DxfProprietaryData *) surface->proprietary_data->next);
                        surface->proprietary_data = (DxfProprietaryData *) surface->proprietary_data->next;
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->additional_proprietary_data->line);
                        surface->additional_proprietary_data->order = i;
                        i++;
                        dxf_proprietary_data_init ((DxfProprietaryData *) surface->additional_proprietary_data->next);
                        surface->additional_proprietary_data = (DxfProprietaryData *) surface->additional_proprietary_data->next;
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &surface->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->layer);
                }
                else if (strcmp (temp_string, "38") == 0)
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &surface->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &surface->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &surface->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &surface->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &surface->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &surface->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &surface->modeler_format_version_number);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &surface->number_of_U_isolines);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &surface->number_of_V_isolines);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &surface->graphics_data_size);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbModelerGeometry") == 0)
                          || (strcmp (temp_string, "AcDbSurface") == 0))
                        {
                                /* Do nothing. */
                        }
                        else if ((strcmp (temp_string, "AcDbExtrudedSurface") == 0))
                        {
                                surface->type = EXTRUDED;
                                if (surface->extruded_surface == NULL)
                                {
                                        surface->extruded_surface = (struct DxfSurfaceExtruded *) dxf_surface_extruded_new ();
                                }
//                                surface->extruded_surface = dxf_surface_extruded_read (fp, surface->extruded_surface);
                                return (surface);
                        }
                        else if ((strcmp (temp_string, "AcDbLoftedSurface") == 0))
                        {
                                surface->type = LOFTED;
                                if (surface->lofted_surface == NULL)
                                {
                                        surface->lofted_surface = (struct DxfSurfaceLofted *) dxf_surface_lofted_new ();
                                }
//                                surface->lofted_surface = dxf_surface_lofted_read (fp, surface->lofted_surface);
                                return (surface);
                        }
                        else if ((strcmp (temp_string, "AcDbRevolvedSurface") == 0))
                        {
                                surface->type = REVOLVED;
                                if (surface->revolved_surface == NULL)
                                {
                                        surface->revolved_surface = (struct DxfSurfaceRevolved *) dxf_surface_revolved_new ();
                                }
//                                surface->revolved_surface = dxf_surface_revolved_read (fp, surface->revolved_surface);
                                return (surface);
                        }
                        else if ((strcmp (temp_string, "AcDbSweptSurface") == 0))
                        {
                                surface->type = SWEPT;
                                if (surface->swept_surface == NULL)
                                {
                                        surface->swept_surface = (struct DxfSurfaceSwept *) dxf_surface_swept_new ();
                                }
//                                surface->swept_surface = dxf_surface_swept_read (fp, surface->swept_surface);
                                return (surface);
                        }
                        else
                        {
                                surface->type = NO_TYPE;
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                                return (surface);
                        }
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &surface->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &surface->shadow_mode);
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
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &surface->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &surface->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, surface->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &surface->transparency);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (surface->linetype, "") == 0)
        {
                surface->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (surface->layer, "") == 0)
        {
                surface->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Write DXF output to \c fp for a DXF \c SURFACE entity.
 */
int
dxf_surface_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSurface *surface
                /*!< a pointer to the DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SURFACE");

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
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (surface->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, surface->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                surface->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (surface->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", surface->id_code);
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
        if ((strcmp (surface->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", surface->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (surface->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", surface->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (surface->paperspace == 1)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", surface->layer);
        if (strcmp (surface->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", surface->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (surface->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", surface->material);
        }
        if (surface->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", surface->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", surface->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (surface->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", surface->elevation);
        }
        if (surface->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", surface->linetype_scale);
        }
        if (surface->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", surface->visibility);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
          && (surface->graphics_data_size > 0))
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", surface->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%d\n", surface->graphics_data_size);
#endif
                if (surface->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = surface->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", dxf_binary_data_get_data_line (iter));
                                iter = (DxfBinaryData *) dxf_binary_data_get_next (iter);
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", surface->color_value);
                fprintf (fp->fp, "430\n%s\n", surface->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", surface->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", surface->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", surface->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbModelerGeometry\n");
        }
        if (surface->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", surface->thickness);
        }
        if (surface->modeler_format_version_number != 0)
        {
                fprintf (fp->fp, " 70\n%hd\n", surface->modeler_format_version_number);
        }
        if (surface->proprietary_data != NULL)
        {
                DxfProprietaryData *iter1a;
                iter1a = (DxfProprietaryData *) surface->proprietary_data;
                while (iter1a != NULL)
                {
                        fprintf (fp->fp, "  1\n%s\n", iter1a->line);
                        iter1a = (DxfProprietaryData *) iter1a->next;
                }
        }
        if (surface->additional_proprietary_data != NULL)
        {
                DxfProprietaryData *iter3a;
                iter3a = (DxfProprietaryData *) surface->additional_proprietary_data;
                while (iter3a != NULL)
                {
                        fprintf (fp->fp, "  3\n%s\n", iter3a->line);
                        iter3a = (DxfProprietaryData *) iter3a->next;
                }
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSurface\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, " 71\n%hd\n", surface->number_of_U_isolines);
                fprintf (fp->fp, " 72\n%hd\n", surface->number_of_V_isolines);
        }
        if (surface->type == EXTRUDED)
        {
                dxf_surface_extruded_write (fp, (DxfSurfaceExtruded *) surface->extruded_surface);
        }
        else if (surface->type == LOFTED)
        {
                dxf_surface_lofted_write (fp, (DxfSurfaceLofted *) surface->lofted_surface);
        }
        else if (surface->type == REVOLVED)
        {
                dxf_surface_revolved_write (fp, (DxfSurfaceRevolved *) surface->revolved_surface);
        }
        else if (surface->type == SWEPT)
        {
                dxf_surface_swept_write (fp, (DxfSurfaceSwept *) surface->swept_surface);
        }
        else if (surface->type == NO_TYPE)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NO_TYPE value was passed.\n")),
                  __FUNCTION__);
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () an unknown type value was passed.\n")),
                  __FUNCTION__);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SURFACE entity and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_surface_free
(
        DxfSurface *surface
                /*!< a pointer to the memory occupied by the DXF
                 * \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (surface->linetype);
        free (surface->layer);
        free (surface->dictionary_owner_soft);
        free (surface->object_owner_soft);
        free (surface->material);
        free (surface->dictionary_owner_hard);
        free (surface->plot_style_name);
        free (surface->color_name);
        dxf_proprietary_data_free_list (surface->proprietary_data);
        dxf_proprietary_data_free_list (surface->additional_proprietary_data);
        free (surface);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SURFACE entities and all their data fields.
 */
void
dxf_surface_free_list
(
        DxfSurface *surfaces
                /*!< a pointer to the single linked list of DXF
                 * \c SURFACE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (surfaces != NULL)
        {
                DxfSurface *iter = (DxfSurface *) surfaces->next;
                dxf_surface_free (surfaces);
                surfaces = (DxfSurface *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SURFACE entity.
 *
 * \return \c id_code.
 */
int
dxf_surface_get_id_code
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_id_code
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
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
        if (surface == NULL)
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
        surface->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c linetype from a DXF \c SURFACE entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_surface_get_linetype
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 *
 * \note the pointer to \c linetype is not freed.
 */
DxfSurface *
dxf_surface_set_linetype
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c layer from a DXF \c SURFACE entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_surface_get_layer
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_layer
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c elevation from a DXF \c SURFACE entity.
 *
 * \return \c elevation.
 */
double
dxf_surface_get_elevation
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_elevation
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c thickness from a DXF \c SURFACE entity.
 *
 * \return \c thickness.
 */
double
dxf_surface_get_thickness
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->thickness == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_thickness
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        if (thickness == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        surface->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c SURFACE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_surface_get_linetype_scale
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->linetype_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_linetype_scale
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        if (linetype_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        surface->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c visibility from a DXF \c SURFACE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_surface_get_visibility
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_visibility
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c color from a DXF \c SURFACE entity.
 *
 * \return color.
 */
int16_t
dxf_surface_get_color
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->color);
}


/*!
 * \brief Set the \c color for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_color
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c SURFACE entity.
 *
 * \return \c paperspace flag value.
 */
int16_t
dxf_surface_get_paperspace
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_paperspace
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c SURFACE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_surface_get_graphics_data_size
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c SURFACE
 * entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_graphics_data_size
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c SURFACE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_surface_get_shadow_mode
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_shadow_mode
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c SURFACE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_surface_get_binary_graphics_data
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) surface->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_binary_graphics_data
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SURFACE entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_surface_get_dictionary_owner_soft
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_dictionary_owner_soft
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c SURFACE entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_surface_get_object_owner_soft
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c SURFACE entity.
 */
DxfSurface *
dxf_surface_set_object_owner_soft
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c SURFACE
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_surface_get_material
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c SURFACE
 * entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_material
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SURFACE entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_surface_get_dictionary_owner_hard
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_dictionary_owner_hard
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c lineweight from a DXF \c SURFACE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_surface_get_lineweight
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_lineweight
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c SURFACE entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_surface_get_plot_style_name
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_plot_style_name
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c color_value from a DXF \c SURFACE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_surface_get_color_value
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_color_value
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c color_name from a DXF \c SURFACE entity.
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_surface_get_color_name
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (surface->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_color_name
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c transparency from a DXF \c SURFACE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_surface_get_transparency
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_transparency
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the \c proprietary_data from a DXF \c
 * SURFACE entity.
 *
 * \return pointer to the \c proprietary_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfProprietaryData *
dxf_surface_get_proprietary_data
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->proprietary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfProprietaryData *) surface->proprietary_data);
}


/*!
 * \brief Set the proprietary data for a DXF \c SURFACE entity.
 *
 * \return a pointer to \c surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurface *
dxf_surface_set_proprietary_data
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        DxfProprietaryData *proprietary_data
                /*!< a pointer to a linked list containing the
                 * \c proprietary_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->proprietary_data = proprietary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the \c additional_proprietary_data from a DXF \c SURFACE
 * entity.
 *
 * \return pointer to the \c additional_proprietary_data.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
DxfProprietaryData *
dxf_surface_get_additional_proprietary_data
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->additional_proprietary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfProprietaryData *) surface->additional_proprietary_data);
}


/*!
 * \brief Set the pointer to the additional proprietary data for a DXF
 * \c SURFACE entity.
 */
DxfSurface *
dxf_surface_set_additional_proprietary_data
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        DxfProprietaryData *additional_proprietary_data
                /*!< an array containing the additional proprietary data
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (additional_proprietary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->additional_proprietary_data = additional_proprietary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the modeler format version number from a DXF \c SURFACE
 * entity.
 *
 * \return \c modeler_format_version_number.
 */
int16_t
dxf_surface_get_modeler_format_version_number
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->modeler_format_version_number != 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->modeler_format_version_number);
}


/*!
 * \brief Set the modeler format version number for a DXF \c SURFACE
 * entity.
 */
DxfSurface *
dxf_surface_set_modeler_format_version_number
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t modeler_format_version_number
                /*!< Modeler format version number (currently = 1). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (modeler_format_version_number != 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        surface->modeler_format_version_number = modeler_format_version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the number of U isolines from a DXF \c SURFACE entity.
 *
 * \return \c number_of_U_isolines.
 */
int16_t
dxf_surface_get_number_of_U_isolines
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->number_of_U_isolines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->number_of_U_isolines == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->number_of_U_isolines);
}


/*!
 * \brief Set the number of U isolines for a DXF \c SURFACE entity.
 */
DxfSurface *
dxf_surface_set_number_of_U_isolines
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t number_of_U_isolines
                /*!< Number of U isolines. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_U_isolines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (number_of_U_isolines == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        surface->number_of_U_isolines = number_of_U_isolines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the number of V isolines from a DXF \c SURFACE entity.
 *
 * \return \c number_of_V_isolines.
 */
int16_t
dxf_surface_get_number_of_V_isolines
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (surface->number_of_V_isolines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (surface->number_of_V_isolines == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface->number_of_V_isolines);
}


/*!
 * \brief Set the number of V isolines for a DXF \c SURFACE entity.
 */
DxfSurface *
dxf_surface_set_number_of_V_isolines
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        int16_t number_of_V_isolines
                /*!< Number of V isolines. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_V_isolines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (number_of_V_isolines == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        surface->number_of_V_isolines = number_of_V_isolines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the next \c SURFACE entity from a DXF 
 * \c SURFACE entity.
 *
 * \return pointer to the next \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurface *
dxf_surface_get_next
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurface *) surface->next);
}


/*!
 * \brief Set the pointer to the next \c SURFACE for a DXF \c SURFACE
 * entity.
 */
DxfSurface *
dxf_surface_set_next
(
        DxfSurface *surface,
                /*!< a pointer to a DXF \c SURFACE entity. */
        DxfSurface *next
                /*!< a pointer to the next \c SURFACE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
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
        surface->next = (struct DxfSurface *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (surface);
}


/*!
 * \brief Get the pointer to the last \c SURFACE entity from a linked list
 * of DXF \c SURFACE entities.
 *
 * \return pointer to the last \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurface *
dxf_surface_get_last
(
        DxfSurface *surface
                /*!< a pointer to a DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfSurface *) surface);
        }
        DxfSurface *iter = (DxfSurface *) surface->next;
        while (iter->next != NULL)
        {
                iter = (DxfSurface *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurface *) iter);
}


/*!
 * \brief Allocate memory for a DXF extruded \c SURFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSurfaceExtruded *extruded_surface = NULL;
        size_t size;

        size = sizeof (DxfSurfaceExtruded);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((extruded_surface = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                extruded_surface = NULL;
        }
        else
        {
                memset (extruded_surface, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * extruded \c SURFACE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_init
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to the DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                extruded_surface = dxf_surface_extruded_new ();
        }
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        extruded_surface->p0 = (DxfPoint *) dxf_point_init (extruded_surface->p0);
        if (extruded_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->p1 = (DxfPoint *) dxf_point_init (extruded_surface->p1);
        if (extruded_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->transform_matrix = (DxfDouble *) dxf_double_init (extruded_surface->transform_matrix);
        if (extruded_surface->transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->sweep_matrix = (DxfDouble *) dxf_double_init (extruded_surface->sweep_matrix);
        if (extruded_surface->sweep_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->path_matrix = (DxfDouble *) dxf_double_init (extruded_surface->path_matrix);
        if (extruded_surface->path_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->binary_data = (DxfBinaryData *) dxf_binary_data_init (extruded_surface->binary_data);
        if (extruded_surface->binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        extruded_surface->draft_angle = 0.0;
        extruded_surface->draft_start_distance = 0.0;
        extruded_surface->draft_end_distance = 0.0;
        extruded_surface->twist_angle = 0.0;
        extruded_surface->scale_factor = 0.0;
        extruded_surface->align_angle = 0.0;
        extruded_surface->sweep_alignment_option = 0;
        extruded_surface->class_ID = 0;
        extruded_surface->binary_data_size = 0;
        extruded_surface->solid_flag =0;
        extruded_surface->align_start_flag = 0;
        extruded_surface->bank_flag = 0;
        extruded_surface->base_point_set_flag = 0;
        extruded_surface->sweep_transform_computed_flag = 0;
        extruded_surface->path_transform_computed_flag = 0;
        extruded_surface->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Read data from a DXF file into a DXF extruded \c SURFACE
 * entity.
 * 
 * The last line read from file contained the string
 * "AcDbExtrudedSurface". \n
 * Now follows some data for the extruded \c SURFACE, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c extruded_surface. \n
 *
 * \return a pointer to \c extruded_surface.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfDouble *iter40 = NULL;
        DxfDouble *iter46 = NULL;
        DxfDouble *iter47 = NULL;
        int iter90;
        DxfBinaryData *iter310 = NULL;

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
        if (fp->acad_version_number < AutoCAD_2007)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                extruded_surface = dxf_surface_extruded_init (extruded_surface);
        }
        iter40 = (DxfDouble *) extruded_surface->transform_matrix;
        iter46 = (DxfDouble *) extruded_surface->sweep_matrix;
        iter47 = (DxfDouble *) extruded_surface->path_matrix;
        iter90 = 0;
        iter310 = (DxfBinaryData *) extruded_surface->binary_data;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the sweep vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the sweep vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the sweep vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the reference vector for
                         * controlling twist. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the reference vector for
                         * controlling twist. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the reference vector for
                         * controlling twist. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->p1->z0);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * transform matrix value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter40->value);
                        iter40->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter40->next);
                        iter40 = (DxfDouble *) iter40->next;
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * draft angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->draft_angle);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * draft start distance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->draft_start_distance);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the
                         * draft end distance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->draft_end_distance);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing the
                         * twist angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->twist_angle);
                }
                else if (strcmp (temp_string, "46") == 0)
                {
                        /* Now follows a string containing a sweep
                         * matrix value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter46->value);
                        iter46->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter46->next);
                        iter46 = (DxfDouble *) iter46->next;
                }
                else if (strcmp (temp_string, "47") == 0)
                {
                        /* Now follows a string containing a path
                         * matrix value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter47->value);
                        iter47->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter47->next);
                        iter47 = (DxfDouble *) iter47->next;
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the
                         * scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->scale_factor);
                }
                else if (strcmp (temp_string, "49") == 0)
                {
                        /* Now follows a string containing the
                         * align angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &extruded_surface->align_angle);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the sweep
                         * alignment option number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &extruded_surface->sweep_alignment_option);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        if (iter90 == 0)
                        {
                                /* Now follows a string containing the
                                 * class ID value. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &extruded_surface->class_ID);
                        }
                        if (iter90 == 1)
                        {
                                /* Now follows a string containing the
                                 * class ID value. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &extruded_surface->binary_data_size);
                        }
                        iter90++;

                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the solid
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &extruded_surface->solid_flag);
                }
                else if (strcmp (temp_string, "292") == 0)
                {
                        /* Now follows a string containing the align
                         * start fla. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &extruded_surface->align_start_flag);
                }
                else if (strcmp (temp_string, "293") == 0)
                {
                        /* Now follows a string containing the bank flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &extruded_surface->bank_flag);
                }
                else if (strcmp (temp_string, "294") == 0)
                {
                        /* Now follows a string containing the base
                         * point set flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &extruded_surface->base_point_set_flag);
                }
                else if (strcmp (temp_string, "295") == 0)
                {
                        /* Now follows a string containing the sweep
                         * entity transform computed flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &extruded_surface->sweep_transform_computed_flag);
                }
                else if (strcmp (temp_string, "296") == 0)
                {
                        /* Now follows a string containing the path
                         * entity transform computed flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &extruded_surface->path_transform_computed_flag);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_data_init ((DxfBinaryData *) iter310->next);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
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
        return (extruded_surface);
}


/*!
 * \brief Write DXF output to \c fp for a extruded DXF \c SURFACE entity.
 */
int
dxf_surface_extruded_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to the extruded DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbExtrudedSurface\n");
        }
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", extruded_surface->class_ID);
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", extruded_surface->binary_data_size);
        if (extruded_surface->binary_data != NULL)
        {
                DxfBinaryData *iter310;
                iter310 = (DxfBinaryData *) extruded_surface->binary_data;
                while (iter310 != NULL)
                {
                        fprintf (fp->fp, "310\n%s\n", iter310->data_line);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
        }
        fprintf (fp->fp, " 10\n%f\n", extruded_surface->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", extruded_surface->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", extruded_surface->p0->z0);
        if (extruded_surface->transform_matrix != NULL)
        {
                DxfDouble *iter40;
                iter40 = (DxfDouble *) extruded_surface->transform_matrix;
                while (iter40 != NULL)
                {
                        fprintf (fp->fp, " 40\n%f\n", iter40->value);
                        iter40 = (DxfDouble *) iter40->next;
                }
        }
        fprintf (fp->fp, " 42\n%f\n", extruded_surface->draft_angle);
        fprintf (fp->fp, " 43\n%f\n", extruded_surface->draft_start_distance);
        fprintf (fp->fp, " 44\n%f\n", extruded_surface->draft_end_distance);
        fprintf (fp->fp, " 45\n%f\n", extruded_surface->twist_angle);
        fprintf (fp->fp, " 48\n%f\n", extruded_surface->scale_factor);
        fprintf (fp->fp, " 49\n%f\n", extruded_surface->align_angle);
        if (extruded_surface->sweep_matrix != NULL)
        {
                DxfDouble *iter46;
                iter46 = (DxfDouble *) extruded_surface->sweep_matrix;
                while (iter46 != NULL)
                {
                        fprintf (fp->fp, " 46\n%f\n", iter46->value);
                        iter46 = (DxfDouble *) iter46->next;
                }
        }
        if (extruded_surface->path_matrix != NULL)
        {
                DxfDouble *iter47;
                iter47 = (DxfDouble *) extruded_surface->path_matrix;
                while (iter47 != NULL)
                {
                        fprintf (fp->fp, " 47\n%f\n", iter47->value);
                        iter47 = (DxfDouble *) iter47->next;
                }
        }
        fprintf (fp->fp, "290\n%d\n", extruded_surface->solid_flag);
        fprintf (fp->fp, " 70\n%hd\n", extruded_surface->sweep_alignment_option);
        fprintf (fp->fp, "292\n%d\n", extruded_surface->align_start_flag);
        fprintf (fp->fp, "293\n%d\n", extruded_surface->bank_flag);
        fprintf (fp->fp, "294\n%d\n", extruded_surface->base_point_set_flag);
        fprintf (fp->fp, "295\n%d\n", extruded_surface->sweep_transform_computed_flag);
        fprintf (fp->fp, "296\n%d\n", extruded_surface->path_transform_computed_flag);
        fprintf (fp->fp, " 11\n%f\n", extruded_surface->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", extruded_surface->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", extruded_surface->p1->z0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF extruded \c SURFACE entity
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_surface_extruded_free
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to the memory occupied by the DXF
                 * extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_point_free (extruded_surface->p0);
        dxf_point_free (extruded_surface->p1);
        dxf_double_free_list (extruded_surface->transform_matrix);
        dxf_double_free_list (extruded_surface->sweep_matrix);
        dxf_double_free_list (extruded_surface->path_matrix);
        dxf_binary_data_free_list (extruded_surface->binary_data);
        free (extruded_surface);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * extruded \c SURFACE entities and all their data fields.
 */
void
dxf_surface_extruded_free_list
(
        DxfSurfaceExtruded *extruded_surfaces
                /*!< a pointer to the single linked list of DXF
                 * extruded \c SURFACE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (extruded_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (extruded_surfaces != NULL)
        {
                DxfSurfaceExtruded *iter = (DxfSurfaceExtruded *) extruded_surfaces->next;
                dxf_surface_extruded_free (extruded_surfaces);
                extruded_surfaces = (DxfSurfaceExtruded *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the sweep vector of a DXF extruded \c SURFACE entity.
 *
 * \return the sweep vector \c p0.
 */
DxfPoint *
dxf_surface_extruded_get_p0
(
        DxfSurfaceExtruded *extruded_surfaces
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surfaces->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surfaces->p0);
}


/*!
 * \brief Set the sweep vector \c p0 for a DXF extruded \c SURFACE
 * entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_p0
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        DxfPoint *p0
                /*!< the sweep vector \c p0 to be set for the entity.\n
                 * This is the entry of a single linked list. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
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
        extruded_surface->p0 = (DxfPoint *) p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the X-value of the sweep vector \c x0 of a DXF extruded
 * \c SURFACE entity.
 *
 * \return the X-value of the sweep vector \c x0.
 */
double
dxf_surface_extruded_get_x0
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->p0->x0);
}


/*!
 * \brief Set the X-value of the sweep vector \c x0 of a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_x0
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double x0
                /*!< the X-value of the sweep vector \c x0 of a DXF
                 * extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the Y-value of the sweep vector \c y0 of a DXF extruded
 * \c SURFACE entity.
 *
 * \return the Y-value of the sweep vector \c y0.
 */
double
dxf_surface_extruded_get_y0
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->p0->y0);
}


/*!
 * \brief Set the Y-value of the sweep vector \c y0 of a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_y0
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double y0
                /*!< the Y-value of the sweep vector \c y0 of a DXF
                 * extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the Z-value of the sweep vector \c z0 of a DXF extruded
 * \c SURFACE entity.
 *
 * \return the Z-value of the sweep vector \c z0.
 */
double
dxf_surface_extruded_get_z0
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->p0->z0);
}


/*!
 * \brief Set the Z-value of the sweep vector \c z0 of a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_z0
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double z0
                /*!< the Z-value of the sweep vector \c z0 of a DXF
                 * extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the reference vector for controlling twist of a DXF
 * extruded \c SURFACE entity.
 *
 * \return the reference vector for controlling twist \c p1.
 */
DxfPoint *
dxf_surface_extruded_get_p1
(
        DxfSurfaceExtruded *extruded_surfaces
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surfaces->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surfaces->p1);
}


/*!
 * \brief Set the reference vector for controlling twist \c p1 for a DXF
 * extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL when an
 * error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_p1
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        DxfPoint *p1
                /*!< the reference vector for controlling twist \c p0 to
                 * be set for the entity.\n
                 * This is the entry of a single linked list. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
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
        extruded_surface->p1 = (DxfPoint *) p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the X-value of the reference vector for controlling twist
 * \c x1 of a DXF extruded \c SURFACE entity.
 *
 * \return the X-value of the reference vector for controlling twist
 * \c x1.
 */
double
dxf_surface_extruded_get_x1
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->p1->x0);
}


/*!
 * \brief Set the X-value of the reference vector for controlling twist
 * \c x1 of a DXF extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_x1
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double x1
                /*!< the X-value of the reference vector for controlling
                 * twist \c x1 of a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the Y-value of the reference vector for controlling twist
 * \c y1 of a DXF extruded \c SURFACE entity.
 *
 * \return the Y-value of the reference vector for controlling twist
 * \c y1.
 */
double
dxf_surface_extruded_get_y1
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->p1->y0);
}


/*!
 * \brief Set the Y-value of the reference vector for controlling twist
 * \c y1 of a DXF extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_y1
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double y1
                /*!< the Y-value of the reference vector for controlling
                 * twist \c y1 of a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the Z-value of the reference vector for controlling twist
 * \c z1 of a DXF extruded \c SURFACE entity.
 *
 * \return the Z-value of the reference vector for controlling twist
 * \c z1.
 */
double
dxf_surface_extruded_get_z1
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->p1->z0);
}


/*!
 * \brief Set the Z-value of the reference vector for controlling twist
 * \c z1 of a DXF extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_z1
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double z1
                /*!< the Z-value of the reference vector for controlling
                 * twist \c z1 of a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the transform matrix \c transform_matrix of a DXF extruded
 * \c SURFACE entity.
 *
 * \return the transform matrix \c transform_matrix.
 */
DxfDouble *
dxf_surface_extruded_get_transform_matrix
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) extruded_surface->transform_matrix);
}


/*!
 * \brief Set the transform matrix \c transform_matrix of a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_transform_matrix
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        DxfDouble *transform_matrix
                /*!< the transform matrix \c transform_matrix of a DXF
                 * extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->transform_matrix = (DxfDouble *) transform_matrix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the draft angle \c draft_angle of a DXF extruded
 * \c SURFACE entity.
 *
 * \return the draft angle \c draft_angle.
 */
double
dxf_surface_extruded_get_draft_angle
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->draft_angle);
}


/*!
 * \brief Set the draft angle \c draft_angle of a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_draft_angle
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double draft_angle
                /*!< the draft angle \c draft_angle of a DXF extruded
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->draft_angle = draft_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the draft start distance \c draft_start_distance of a DXF
 * extruded \c SURFACE entity.
 *
 * \return the draft start distance \c draft_start_distance.
 */
double
dxf_surface_extruded_get_draft_start_distance
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->draft_start_distance);
}


/*!
 * \brief Set the draft start distance \c draft_start_distance of a DXF
 * extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_draft_start_distance
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double draft_start_distance
                /*!< the draft start distance \c draft_start_distance of
                 * a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->draft_start_distance = draft_start_distance;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the draft end distance \c draft_end_distance of a DXF
 * extruded \c SURFACE entity.
 *
 * \return the draft end distance \c draft_end_distance.
 */
double
dxf_surface_extruded_get_draft_end_distance
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->draft_end_distance);
}


/*!
 * \brief Set the draft end distance \c draft_end_distance of a DXF
 * extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_draft_end_distance
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double draft_end_distance
                /*!< the draft end distance \c draft_end_distance of
                 * a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->draft_end_distance = draft_end_distance;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the twist angle \c twist_angle of a DXF extruded
 * \c SURFACE entity.
 *
 * \return the twist angle \c twist_angle.
 */
double
dxf_surface_extruded_get_twist_angle
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->twist_angle);
}


/*!
 * \brief Set the twist angle \c twist_angle of a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_twist_angle
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double twist_angle
                /*!< the twist angle \c twist_angle of a DXF extruded
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->twist_angle = twist_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the sweep matrix \c sweep_matrix of a DXF extruded
 * \c SURFACE entity.
 *
 * \note \c sweep_matrix is a pointer to a single linked list of type
 * \c DxfDouble.
 *
 * \return the sweep matrix \c sweep_matrix.
 */
DxfDouble *
dxf_surface_extruded_get_sweep_matrix
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->sweep_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) extruded_surface->sweep_matrix);
}


/*!
 * \brief Set the sweep matrix \c sweep_matrix of a DXF extruded
 * \c SURFACE entity.
 *
 * \note \c sweep_matrix is a pointer to a single linked list of type
 * \c DxfDouble.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_sweep_matrix
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        DxfDouble *sweep_matrix
                /*!< the sweep matrix \c sweep_matrix of a DXF
                 * extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sweep_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->sweep_matrix = (DxfDouble *) sweep_matrix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the path matrix \c path_matrix of a DXF extruded
 * \c SURFACE entity.
 *
 * \note \c path_matrix is a pointer to a single linked list of type
 * \c DxfDouble.
 *
 * \return the path matrix \c path_matrix.
 */
DxfDouble *
dxf_surface_extruded_get_path_matrix
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->path_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) extruded_surface->path_matrix);
}


/*!
 * \brief Set the path matrix \c path_matrix of a DXF extruded
 * \c SURFACE entity.
 *
 * \note \c path_matrix is a pointer to a single linked list of type
 * \c DxfDouble.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_path_matrix
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        DxfDouble *path_matrix
                /*!< the path matrix \c path_matrix of a DXF
                 * extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (path_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->path_matrix = (DxfDouble *) path_matrix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the scale factor \c scale_factor of a DXF extruded
 * \c SURFACE entity.
 *
 * \return the scale factor \c scale_factor.
 */
double
dxf_surface_extruded_get_scale_factor
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->scale_factor);
}


/*!
 * \brief Set the scale factor \c scale_factor of a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_scale_factor
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double scale_factor
                /*!< the scale factor \c scale_factor of a DXF extruded
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->scale_factor = scale_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the align angle \c align_angle of a DXF extruded
 * \c SURFACE entity.
 *
 * \return the align angle \c align_angle.
 */
double
dxf_surface_extruded_get_align_angle
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->align_angle);
}


/*!
 * \brief Set the align angle \c align_angle of a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_align_angle
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        double align_angle
                /*!< the align angle \c align_angle of a DXF extruded
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->align_angle = align_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c sweep_alignment_option from a DXF \c SURFACE entity.
 *
 * \return \c sweep_alignment_option.
 */
int16_t
dxf_surface_extruded_get_sweep_alignment_option
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->sweep_alignment_option < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (extruded_surface->sweep_alignment_option > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->sweep_alignment_option);
}


/*!
 * \brief Set the \c sweep_alignment_option for a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_sweep_alignment_option
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int16_t sweep_alignment_option
                /*!< the \c sweep_alignment_option to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sweep_alignment_option < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (sweep_alignment_option > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        extruded_surface->sweep_alignment_option = sweep_alignment_option;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c class_ID from a DXF extruded \c SURFACE entity.
 *
 * \return \c class_ID.
 */
int32_t
dxf_surface_extruded_get_class_ID
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->class_ID);
}


/*!
 * \brief Set the \c class_ID for a DXF extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_class_ID
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int32_t class_ID
                /*!< the \c class_ID to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->class_ID = class_ID;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c binary_data_size from a DXF extruded \c SURFACE
 * entity.
 *
 * \return \c binary_data_size.
 */
int32_t
dxf_surface_extruded_get_binary_data_size
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (extruded_surface->binary_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (extruded_surface->binary_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->binary_data_size);
}


/*!
 * \brief Set the \c binary_data_size for a DXF extruded \c SURFACE
 * entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_binary_data_size
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int32_t binary_data_size
                /*!< the \c binary_data_size to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (binary_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (binary_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
        extruded_surface->binary_data_size = binary_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c solid_flag from a DXF extruded \c SURFACE entity.
 *
 * \return \c solid_flag.
 */
int
dxf_surface_extruded_get_solid_flag
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->solid_flag);
}


/*!
 * \brief Set the \c solid_flag for a DXF extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_solid_flag
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int solid_flag
                /*!< the \c solid_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->solid_flag = solid_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c align_start_flag from a DXF extruded \c SURFACE
 * entity.
 *
 * \return \c align_start_flag.
 */
int
dxf_surface_extruded_get_align_start_flag
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->align_start_flag);
}


/*!
 * \brief Set the \c align_start_flag for a DXF extruded \c SURFACE
 * entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_align_start_flag
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int align_start_flag
                /*!< the \c align_start_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->align_start_flag = align_start_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c bank_flag from a DXF extruded \c SURFACE entity.
 *
 * \return \c bank_flag.
 */
int
dxf_surface_extruded_get_bank_flag
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->bank_flag);
}


/*!
 * \brief Set the \c bank_flag for a DXF extruded \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_bank_flag
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int bank_flag
                /*!< the \c bank_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->bank_flag = bank_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c base_point_set_flag from a DXF extruded \c SURFACE
 * entity.
 *
 * \return \c base_point_set_flag.
 */
int
dxf_surface_extruded_get_align_base_point_set_flag
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->base_point_set_flag);
}


/*!
 * \brief Set the \c base_point_set_flag for a DXF extruded \c SURFACE
 * entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_base_point_set_flag
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int base_point_set_flag
                /*!< the \c base_point_set_flag to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->base_point_set_flag = base_point_set_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c sweep_transform_computed_flag from a DXF extruded
 * \c SURFACE entity.
 *
 * \return \c sweep_transform_computed_flag.
 */
int
dxf_surface_extruded_get_align_sweep_transform_computed_flag
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->sweep_transform_computed_flag);
}


/*!
 * \brief Set the \c sweep_transform_computed_flag for a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_sweep_transform_computed_flag
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int sweep_transform_computed_flag
                /*!< the \c sweep_transform_computed_flag to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->sweep_transform_computed_flag = sweep_transform_computed_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the \c path_transform_computed_flag from a DXF extruded
 * \c SURFACE entity.
 *
 * \return \c path_transform_computed_flag.
 */
int
dxf_surface_extruded_get_path_transform_computed_flag
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface->path_transform_computed_flag);
}


/*!
 * \brief Set the \c path_transform_computed_flag for a DXF extruded
 * \c SURFACE entity.
 *
 * \return a pointer to \c extruded_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_path_transform_computed_flag
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        int path_transform_computed_flag
                /*!< the \c path_transform_computed_flag to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        extruded_surface->path_transform_computed_flag = path_transform_computed_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the pointer to the \c binary_data from a DXF extruded
 * \c SURFACE entity.
 *
 * \return pointer to the \c binary_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_surface_extruded_get_binary_data
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->binary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) extruded_surface->binary_data);
}


/*!
 * \brief Set the pointer to the \c binary_data for a DXF extruded
 * \c SURFACE entity.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_binary_data
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
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
        extruded_surface->binary_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the pointer to the next DXF extruded \c SURFACE entity
 * from a DXF  \c SURFACE entity.
 *
 * \return pointer to the next DXF extruded \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_get_next
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurfaceExtruded *) extruded_surface->next);
}


/*!
 * \brief Set the pointer to the next DXF extruded \c SURFACE for a DXF
 * extruded \c SURFACE entity.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_set_next
(
        DxfSurfaceExtruded *extruded_surface,
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
        DxfSurfaceExtruded *next
                /*!< a pointer to the next DXF extruded \c SURFACE for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
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
        extruded_surface->next = (struct DxfSurfaceExtruded *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (extruded_surface);
}


/*!
 * \brief Get the pointer to the last DXF extruded \c SURFACE entity
 * from a linked list of DXF extruded \c SURFACE entities.
 *
 * \return pointer to the last DXF extruded \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurfaceExtruded *
dxf_surface_extruded_get_last
(
        DxfSurfaceExtruded *extruded_surface
                /*!< a pointer to a DXF extruded \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (extruded_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (extruded_surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfSurfaceExtruded *) extruded_surface);
        }
        DxfSurfaceExtruded *iter = (DxfSurfaceExtruded *) extruded_surface->next;
        while (iter->next != NULL)
        {
                iter = (DxfSurfaceExtruded *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurfaceExtruded *) iter);
}


/*!
 * \brief Allocate memory for a DXF lofted \c SURFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceLofted *
dxf_surface_lofted_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSurfaceLofted *lofted_surface = NULL;
        size_t size;

        size = sizeof (DxfSurfaceLofted);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((lofted_surface = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                lofted_surface = NULL;
        }
        else
        {
                memset (lofted_surface, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF lofted
 * \c SURFACE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceLofted *
dxf_surface_lofted_init
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to the DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                lofted_surface = dxf_surface_lofted_new ();
        }
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        lofted_surface->transform_matrix = (DxfDouble *) dxf_double_init (lofted_surface->transform_matrix);
        if (lofted_surface->transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        lofted_surface->start_draft_angle = 0.0;
        lofted_surface->end_draft_angle = 0.0;
        lofted_surface->start_draft_magnitude = 0.0;
        lofted_surface->end_draft_magnitude = 0.0;
        lofted_surface->plane_normal_lofting_type = 0;
        lofted_surface->arc_length_parameterization_flag = 0;
        lofted_surface->no_twist_flag = 0;
        lofted_surface->align_direction_flag = 0;
        lofted_surface->create_simple_surfaces_flag = 0;
        lofted_surface->create_closed_surface_flag = 0;
        lofted_surface->solid_flag = 0;
        lofted_surface->create_ruled_surface_flag = 0;
        lofted_surface->virtual_guide_flag = 0;
        lofted_surface->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Read data from a DXF file into a DXF lofted \c SURFACE
 * entity.
 * 
 * The last line read from file contained the string
 * "AcDbLoftedSurface". \n
 * Now follows some data for the lofted \c SURFACE, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c lofted_surface. \n
 *
 * \return a pointer to \c lofted_surface.
 */
DxfSurfaceLofted *
dxf_surface_lofted_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfDouble *iter40 = NULL;

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
        if (fp->acad_version_number < AutoCAD_2007)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                lofted_surface = dxf_surface_lofted_init (lofted_surface);
        }
        iter40 = (DxfDouble *) lofted_surface->transform_matrix;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * transform matrix value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter40->value);
                        iter40->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter40->next);
                        iter40 = (DxfDouble *) iter40->next;
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the start
                         * draft angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lofted_surface->start_draft_angle);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the end
                         * draft angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lofted_surface->end_draft_angle);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the start
                         * draft magnitude. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lofted_surface->start_draft_magnitude);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the end
                         * draft magnitude. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lofted_surface->end_draft_magnitude);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the plane
                         * normal lofting type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &lofted_surface->plane_normal_lofting_type);
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the arc
                         * length parameterization flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lofted_surface->arc_length_parameterization_flag);
                }
                else if (strcmp (temp_string, "291") == 0)
                {
                        /* Now follows a string containing the no twist
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lofted_surface->no_twist_flag);
                }
                else if (strcmp (temp_string, "292") == 0)
                {
                        /* Now follows a string containing the align
                         * direction flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lofted_surface->align_direction_flag);
                }
                else if (strcmp (temp_string, "293") == 0)
                {
                        /* Now follows a string containing the create
                         * simple surfaces flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lofted_surface->create_simple_surfaces_flag);
                }
                else if (strcmp (temp_string, "294") == 0)
                {
                        /* Now follows a string containing the create
                         * closed surface flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lofted_surface->create_closed_surface_flag);
                }
                else if (strcmp (temp_string, "295") == 0)
                {
                        /* Now follows a string containing the solid
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lofted_surface->solid_flag);
                }
                else if (strcmp (temp_string, "296") == 0)
                {
                        /* Now follows a string containing the create
                         * ruled surface flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lofted_surface->create_ruled_surface_flag);
                }
                else if (strcmp (temp_string, "297") == 0)
                {
                        /* Now follows a string containing the virtual
                         * guide flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lofted_surface->virtual_guide_flag);
                }
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Write DXF output to \c fp for a lofted DXF \c SURFACE entity.
 */
int
dxf_surface_lofted_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to the lofted DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbLoftedSurface\n");
        }
        if (lofted_surface->transform_matrix != NULL)
        {
                DxfDouble *iter40;
                iter40 = (DxfDouble *) lofted_surface->transform_matrix;
                while (iter40 != NULL)
                {
                        fprintf (fp->fp, " 40\n%f\n", iter40->value);
                        iter40 = (DxfDouble *) iter40->next;
                }
        }
        /*! \todo add Entity data for cross sections. */
        /*! \todo add Entity data for guide curves. */
        /*! \todo add Entity data for path curves. */
        fprintf (fp->fp, " 70\n%hd\n", lofted_surface->plane_normal_lofting_type);
        fprintf (fp->fp, " 41\n%f\n", lofted_surface->start_draft_angle);
        fprintf (fp->fp, " 42\n%f\n", lofted_surface->end_draft_angle);
        fprintf (fp->fp, " 43\n%f\n", lofted_surface->start_draft_magnitude);
        fprintf (fp->fp, " 44\n%f\n", lofted_surface->end_draft_magnitude);
        fprintf (fp->fp, "290\n%d\n", lofted_surface->arc_length_parameterization_flag);
        fprintf (fp->fp, "291\n%d\n", lofted_surface->no_twist_flag);
        fprintf (fp->fp, "292\n%d\n", lofted_surface->align_direction_flag);
        fprintf (fp->fp, "293\n%d\n", lofted_surface->create_simple_surfaces_flag);
        fprintf (fp->fp, "294\n%d\n", lofted_surface->create_closed_surface_flag);
        fprintf (fp->fp, "295\n%d\n", lofted_surface->solid_flag);
        fprintf (fp->fp, "296\n%d\n", lofted_surface->create_ruled_surface_flag);
        fprintf (fp->fp, "297\n%d\n", lofted_surface->virtual_guide_flag);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}

/*!
 * \brief Free the allocated memory for a DXF lofted \c SURFACE entity
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_surface_lofted_free
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to the memory occupied by the DXF
                 * lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lofted_surface->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_double_free_list (lofted_surface->transform_matrix);
        free (lofted_surface);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * lofted \c SURFACE entities and all their data fields.
 */
void
dxf_surface_lofted_free_list
(
        DxfSurfaceLofted *lofted_surfaces
                /*!< a pointer to the single linked list of DXF
                 * lofted \c SURFACE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (lofted_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (lofted_surfaces != NULL)
        {
                DxfSurfaceLofted *iter = (DxfSurfaceLofted *) lofted_surfaces->next;
                dxf_surface_lofted_free (lofted_surfaces);
                lofted_surfaces = (DxfSurfaceLofted *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the transform matrix \c transform_matrix of a DXF lofted
 * \c SURFACE entity.
 *
 * \return the transform matrix \c transform_matrix.
 */
DxfDouble *
dxf_surface_lofted_get_transform_matrix
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lofted_surface->transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) lofted_surface->transform_matrix);
}


/*!
 * \brief Set the transform matrix \c transform_matrix of a DXF lofted
 * \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_transform_matrix
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        DxfDouble *transform_matrix
                /*!< the transform matrix \c transform_matrix of a DXF
                 * lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->transform_matrix = (DxfDouble *) transform_matrix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the start draft angle \c start_draft_angle of a DXF lofted
 * \c SURFACE entity.
 *
 * \return the start draft angle \c start_draft_angle.
 */
double
dxf_surface_lofted_get_start_draft_angle
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->start_draft_angle);
}


/*!
 * \brief Set the start draft angle \c start_draft_angle of a DXF lofted
 * \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_start_draft_angle
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        double start_draft_angle
                /*!< the start draft angle \c start_draft_angle of a DXF
                 * lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->start_draft_angle = start_draft_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the end draft angle \c end_draft_angle of a DXF lofted
 * \c SURFACE entity.
 *
 * \return the end draft angle \c end_draft_angle.
 */
double
dxf_surface_lofted_get_end_draft_angle
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->end_draft_angle);
}


/*!
 * \brief Set the end draft angle \c end_draft_angle of a DXF lofted
 * \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_end_draft_angle
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        double end_draft_angle
                /*!< the end draft angle \c end_draft_angle of a DXF
                 * lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->end_draft_angle = end_draft_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the start draft magnitude \c start_draft_magnitude of a
 * DXF lofted \c SURFACE entity.
 *
 * \return the start draft magnitude \c start_draft_magnitude.
 */
double
dxf_surface_lofted_get_start_draft_magnitude
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->start_draft_magnitude);
}


/*!
 * \brief Set the start draft magnitude \c start_draft_magnitude of a
 * DXF lofted \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_start_draft_magnitude
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        double start_draft_magnitude
                /*!< the start draft magnitude \c start_draft_magnitude
                 * of a DXF lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->start_draft_magnitude = start_draft_magnitude;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the end draft magnitude \c end_draft_magnitude of a
 * DXF lofted \c SURFACE entity.
 *
 * \return the end draft magnitude \c end_draft_magnitude.
 */
double
dxf_surface_lofted_get_end_draft_magnitude
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->end_draft_magnitude);
}


/*!
 * \brief Set the end draft magnitude \c end_draft_magnitude of a
 * DXF lofted \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_end_draft_magnitude
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        double end_draft_magnitude
                /*!< the end draft magnitude \c end_draft_magnitude
                 * of a DXF lofted \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->end_draft_magnitude = end_draft_magnitude;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c plane_normal_lofting_type from a DXF lofted
 * \c SURFACE entity.
 *
 * \return \c plane_normal_lofting_type.
 */
int16_t
dxf_surface_lofted_get_plane_normal_lofting_type
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->plane_normal_lofting_type);
}


/*!
 * \brief Set the \c plane_normal_lofting_type for a DXF lofted
 * \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_plane_normal_lofting_type
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int16_t plane_normal_lofting_type
                /*!< the \c plane_normal_lofting_type to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->plane_normal_lofting_type = plane_normal_lofting_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c arc_length_parameterization_flag from a DXF lofted
 * \c SURFACE entity.
 *
 * \return \c arc_length_parameterization_flag.
 */
int
dxf_surface_lofted_get_arc_length_parameterization_flag
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->arc_length_parameterization_flag);
}


/*!
 * \brief Set the \c arc_length_parameterization_flag for a DXF lofted
 * \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_arc_length_parameterization_flag
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int arc_length_parameterization_flag
                /*!< the \c arc_length_parameterization_flag to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->arc_length_parameterization_flag = arc_length_parameterization_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c no_twist_flag from a DXF lofted \c SURFACE entity.
 *
 * \return \c no_twist_flag.
 */
int
dxf_surface_lofted_get_no_twist_flag
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->no_twist_flag);
}


/*!
 * \brief Set the \c no_twist_flag for a DXF lofted \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_no_twist_flag
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int no_twist_flag
                /*!< the \c no_twist_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->no_twist_flag = no_twist_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c align_direction_flag from a DXF lofted \c SURFACE
 * entity.
 *
 * \return \c align_direction_flag.
 */
int
dxf_surface_lofted_get_align_direction_flag
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->align_direction_flag);
}


/*!
 * \brief Set the \c align_direction_flag for a DXF lofted \c SURFACE
 * entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_align_direction_flag
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int align_direction_flag
                /*!< the \c align_direction_flag to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->align_direction_flag = align_direction_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c create_simple_surfaces_flag from a DXF lofted \c SURFACE
 * entity.
 *
 * \return \c create_simple_surfaces_flag.
 */
int
dxf_surface_lofted_get_create_simple_surfaces_flag
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->create_simple_surfaces_flag);
}


/*!
 * \brief Set the \c create_simple_surfaces_flag for a DXF lofted
 * \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_create_simple_surfaces_flag
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int create_simple_surfaces_flag
                /*!< the \c create_simple_surfaces_flag to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->create_simple_surfaces_flag = create_simple_surfaces_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c create_closed_surface_flag from a DXF lofted \c SURFACE
 * entity.
 *
 * \return \c create_closed_surface_flag.
 */
int
dxf_surface_lofted_get_create_closed_surface_flag
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->create_closed_surface_flag);
}


/*!
 * \brief Set the \c create_closed_surface_flag for a DXF lofted
 * \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_create_closed_surface_flag
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int create_closed_surface_flag
                /*!< the \c create_closed_surface_flag to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->create_closed_surface_flag = create_closed_surface_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c solid_flag from a DXF lofted \c SURFACE entity.
 *
 * \return \c solid_flag.
 */
int
dxf_surface_lofted_get_solid_flag
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->solid_flag);
}


/*!
 * \brief Set the \c solid_flag for a DXF lofted \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_solid_flag
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int solid_flag
                /*!< the \c solid_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->solid_flag = solid_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c create_ruled_surface_flag from a DXF lofted
 * \c SURFACE entity.
 *
 * \return \c create_ruled_surface_flag.
 */
int
dxf_surface_lofted_get_create_ruled_surface_flag
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->create_ruled_surface_flag);
}


/*!
 * \brief Set the \c create_ruled_surface_flag for a DXF lofted
 * \c SURFACE entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_create_ruled_surface_flag
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int create_ruled_surface_flag
                /*!< the \c create_ruled_surface_flag to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->create_ruled_surface_flag = create_ruled_surface_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the \c virtual_guide_flag from a DXF lofted \c SURFACE
 * entity.
 *
 * \return \c virtual_guide_flag.
 */
int
dxf_surface_lofted_get_virtual_guide_flag
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface->virtual_guide_flag);
}


/*!
 * \brief Set the \c virtual_guide_flag for a DXF lofted \c SURFACE
 * entity.
 *
 * \return a pointer to \c lofted_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_virtual_guide_flag
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        int virtual_guide_flag
                /*!< the \c virtual_guide_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lofted_surface->virtual_guide_flag = virtual_guide_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the pointer to the next DXF lofted \c SURFACE entity
 * from a DXF  \c SURFACE entity.
 *
 * \return pointer to the next DXF lofted \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurfaceLofted *
dxf_surface_lofted_get_next
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lofted_surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurfaceLofted *) lofted_surface->next);
}


/*!
 * \brief Set the pointer to the next DXF lofted \c SURFACE for a DXF
 * lofted \c SURFACE entity.
 */
DxfSurfaceLofted *
dxf_surface_lofted_set_next
(
        DxfSurfaceLofted *lofted_surface,
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
        DxfSurfaceLofted *next
                /*!< a pointer to the next DXF lofted \c SURFACE for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
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
        lofted_surface->next = (struct DxfSurfaceLofted *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lofted_surface);
}


/*!
 * \brief Get the pointer to the last DXF lofted \c SURFACE entity
 * from a linked list of DXF lofted \c SURFACE entities.
 *
 * \return pointer to the last DXF lofted \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurfaceLofted *
dxf_surface_lofted_get_last
(
        DxfSurfaceLofted *lofted_surface
                /*!< a pointer to a DXF lofted \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lofted_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lofted_surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfSurfaceLofted *) lofted_surface);
        }
        DxfSurfaceLofted *iter = (DxfSurfaceLofted *) lofted_surface->next;
        while (iter->next != NULL)
        {
                iter = (DxfSurfaceLofted *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurfaceLofted *) iter);
}


/*!
 * \brief Allocate memory for a DXF revolved \c SURFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSurfaceRevolved *revolved_surface = NULL;
        size_t size;

        size = sizeof (DxfSurfaceRevolved);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((revolved_surface = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                revolved_surface = NULL;
        }
        else
        {
                memset (revolved_surface, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * revolved \c SURFACE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_init
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to the DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                revolved_surface = dxf_surface_revolved_new ();
        }
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        revolved_surface->p0 = (DxfPoint *) dxf_point_init (revolved_surface->p0);
        if (revolved_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->p1 = (DxfPoint *) dxf_point_init (revolved_surface->p1);
        if (revolved_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->transform_matrix = (DxfDouble *) dxf_double_init (revolved_surface->transform_matrix);
        if (revolved_surface->transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->binary_data = (DxfBinaryData *) dxf_binary_data_init (revolved_surface->binary_data);
        if (revolved_surface->binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        revolved_surface->revolve_angle = 0.0;
        revolved_surface->start_angle = 0.0;
        revolved_surface->draft_angle = 0.0;
        revolved_surface->start_draft_distance = 0.0;
        revolved_surface->end_draft_distance = 0.0;
        revolved_surface->twist_angle = 0.0;
        revolved_surface->ID = 0;
        revolved_surface->binary_data_size = 0;
        revolved_surface->solid_flag =0;
        revolved_surface->close_to_axis_flag = 0;
        revolved_surface->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Read data from a DXF file into a DXF revolved \c SURFACE
 * entity.
 * 
 * The last line read from file contained the string
 * "AcDbRevolvedSurface". \n
 * Now follows some data for the revolved \c SURFACE, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c revolved_surface. \n
 *
 * \return a pointer to \c revolved_surface.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfDouble *iter42 = NULL;
        int iter90;
        DxfBinaryData *iter310 = NULL;

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
        if (fp->acad_version_number < AutoCAD_2007)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                revolved_surface = dxf_surface_revolved_init (revolved_surface);
        }
        iter42 = (DxfDouble *) revolved_surface->transform_matrix;
        iter90 = 0;
        iter310 = (DxfBinaryData *) revolved_surface->binary_data;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the axis point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the axis point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the axis point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the axis vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the axis vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the axis vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->p1->z0);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the revolve
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->revolve_angle);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the start
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->start_angle);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * transform matrix value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter42->value);
                        iter42->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter42->next);
                        iter42 = (DxfDouble *) iter42->next;
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the draft
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->draft_angle);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the start
                         * draft distance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->start_draft_distance);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing the end draft
                         * distance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->end_draft_distance);
                }
                else if (strcmp (temp_string, "46") == 0)
                {
                        /* Now follows a string containing the twist
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &revolved_surface->twist_angle);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        if (iter90 == 0)
                        {
                                /* Now follows a string containing the
                                 * ID of the revolve entity. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &revolved_surface->ID);
                        }
                        if (iter90 == 1)
                        {
                                /* Now follows a string containing the
                                 * binary data size. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &revolved_surface->binary_data_size);
                        }
                        iter90++;
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the solid
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &revolved_surface->solid_flag);
                }
                else if (strcmp (temp_string, "291") == 0)
                {
                        /* Now follows a string containing the close to
                         * axis flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &revolved_surface->close_to_axis_flag);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_data_init ((DxfBinaryData *) iter310->next);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Write DXF output to \c fp for a revolved DXF \c SURFACE entity.
 */
int
dxf_surface_revolved_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to the revolved DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbRevolvedSurface\n");
        }
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", revolved_surface->ID);
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", revolved_surface->binary_data_size);
        if (revolved_surface->binary_data != NULL)
        {
                DxfBinaryData *iter310;
                iter310 = (DxfBinaryData *) revolved_surface->binary_data;
                while (iter310 != NULL)
                {
                        fprintf (fp->fp, "310\n%s\n", iter310->data_line);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
        }
        fprintf (fp->fp, " 10\n%f\n", revolved_surface->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", revolved_surface->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", revolved_surface->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", revolved_surface->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", revolved_surface->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", revolved_surface->p1->z0);
        fprintf (fp->fp, " 40\n%f\n", revolved_surface->revolve_angle);
        fprintf (fp->fp, " 41\n%f\n", revolved_surface->start_angle);
        if (revolved_surface->transform_matrix != NULL)
        {
                DxfDouble *iter42;
                iter42 = (DxfDouble *) revolved_surface->transform_matrix;
                while (iter42 != NULL)
                {
                        fprintf (fp->fp, " 40\n%f\n", iter42->value);
                        iter42 = (DxfDouble *) iter42->next;
                }
        }
        fprintf (fp->fp, " 43\n%f\n", revolved_surface->draft_angle);
        fprintf (fp->fp, " 44\n%f\n", revolved_surface->start_draft_distance);
        fprintf (fp->fp, " 45\n%f\n", revolved_surface->end_draft_distance);
        fprintf (fp->fp, " 46\n%f\n", revolved_surface->twist_angle);
        fprintf (fp->fp, "290\n%d\n", revolved_surface->solid_flag);
        fprintf (fp->fp, "291\n%d\n", revolved_surface->close_to_axis_flag);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF revolved \c SURFACE entity
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_surface_revolved_free
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to the memory occupied by the DXF
                 * revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (revolved_surface->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_point_free (revolved_surface->p0);
        dxf_point_free (revolved_surface->p1);
        dxf_double_free_list (revolved_surface->transform_matrix);
        dxf_binary_data_free_list (revolved_surface->binary_data);
        free (revolved_surface);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * revolved \c SURFACE entities and all their data fields.
 */
void
dxf_surface_revolved_free_list
(
        DxfSurfaceRevolved *revolved_surfaces
                /*!< a pointer to the single linked list of DXF
                 * revolved \c SURFACE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (revolved_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (revolved_surfaces != NULL)
        {
                DxfSurfaceRevolved *iter = (DxfSurfaceRevolved *) revolved_surfaces->next;
                dxf_surface_revolved_free (revolved_surfaces);
                revolved_surfaces = (DxfSurfaceRevolved *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the axis point of a DXF revolved \c SURFACE entity.
 *
 * \return the axis point \c p0.
 */
DxfPoint *
dxf_surface_revolved_get_p0
(
        DxfSurfaceRevolved *revolved_surfaces
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surfaces->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surfaces->p0);
}


/*!
 * \brief Set the axis point \c p0 for a DXF revolved \c SURFACE
 * entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_p0
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        DxfPoint *p0
                /*!< the axis point \c p0 to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
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
        revolved_surface->p0 = (DxfPoint *) p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the X-value of the axis point \c x0 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the X-value of the axis point \c x0.
 */
double
dxf_surface_revolved_get_x0
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (revolved_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->p0->x0);
}


/*!
 * \brief Set the X-value of the axis point \c x0 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_x0
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double x0
                /*!< the X-value of the axis point \c x0 of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the Y-value of the axis point \c y0 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the Y-value of the axis point \c y0.
 */
double
dxf_surface_revolved_get_y0
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (revolved_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->p0->y0);
}


/*!
 * \brief Set the Y-value of the axis point \c y0 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_y0
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double y0
                /*!< the Y-value of the axis point \c y0 of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the Z-value of the axis point \c z0 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the Z-value of the axis point \c z0.
 */
double
dxf_surface_revolved_get_z0
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (revolved_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->p0->z0);
}


/*!
 * \brief Set the Z-value of the axis point \c z0 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_z0
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double z0
                /*!< the Z-value of the axis point \c z0 of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the axis vector of a DXF revolved \c SURFACE entity.
 *
 * \return the axis vector \c p1.
 */
DxfPoint *
dxf_surface_revolved_get_p1
(
        DxfSurfaceRevolved *revolved_surfaces
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surfaces->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surfaces->p1);
}


/*!
 * \brief Set the axis vector \c p1 for a DXF revolved \c SURFACE
 * entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_p1
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        DxfPoint *p1
                /*!< the axis vector \c p1 to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
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
        revolved_surface->p1 = (DxfPoint *) p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the X-value of the axis vector \c x1 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the X-value of the axis vector \c x1.
 */
double
dxf_surface_revolved_get_x1
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (revolved_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->p1->x0);
}


/*!
 * \brief Set the X-value of the axis vector \c x1 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_x1
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double x1
                /*!< the X-value of the axis vector \c x1 of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the Y-value of the axis vector \c y1 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the Y-value of the axis vector \c y1.
 */
double
dxf_surface_revolved_get_y1
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (revolved_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->p1->y0);
}


/*!
 * \brief Set the Y-value of the axis vector \c y1 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_y1
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double y1
                /*!< the Y-value of the axis vector \c y1 of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the Z-value of the axis vector \c z1 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the Z-value of the axis vector \c z1.
 */
double
dxf_surface_revolved_get_z1
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (revolved_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->p1->z0);
}


/*!
 * \brief Set the Z-value of the axis vector \c z1 of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_z1
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double z1
                /*!< the Z-value of the axis vector \c z1 of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the revolve angle \c revolve_angle of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the revolve angle \c revolve_angle.
 */
double
dxf_surface_revolved_get_revolve_angle
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->revolve_angle);
}


/*!
 * \brief Set the revolve angle \c revolve_angle of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_revolve_angle
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double revolve_angle
                /*!< the revolve angle \c revolve_angle of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->revolve_angle = revolve_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the start angle \c start_angle of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the start angle \c start_angle.
 */
double
dxf_surface_revolved_get_start_angle
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->start_angle);
}


/*!
 * \brief Set the start angle \c start_angle of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_start_angle
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double start_angle
                /*!< the start angle \c start_angle of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->start_angle = start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the transform matrix \c transform_matrix of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the transform matrix \c transform_matrix.
 */
DxfDouble *
dxf_surface_revolved_get_transform_matrix
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) revolved_surface->transform_matrix);
}


/*!
 * \brief Set the transform matrix \c transform_matrix of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_transform_matrix
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        DxfDouble *transform_matrix
                /*!< the transform matrix \c transform_matrix of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (transform_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->transform_matrix = (DxfDouble *) transform_matrix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the draft angle \c draft_angle of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the draft angle \c draft_angle.
 */
double
dxf_surface_revolved_get_draft_angle
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->draft_angle);
}


/*!
 * \brief Set the draft angle \c draft_angle of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_draft_angle
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double draft_angle
                /*!< the draft angle \c draft_angle of a DXF
                 * revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->draft_angle = draft_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the start draft distance \c start_draft_distance of a DXF
 * revolved \c SURFACE entity.
 *
 * \return the start draft distance \c start_draft_distance.
 */
double
dxf_surface_revolved_get_start_draft_distance
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->start_draft_distance);
}


/*!
 * \brief Set the start draft distance \c start_draft_distance of a DXF
 * revolved \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_start_draft_distance
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double start_draft_distance
                /*!< the start draft distance \c start_draft_distance of
                 * a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->start_draft_distance = start_draft_distance;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the end draft distance \c end_draft_distance of a DXF
 * revolved \c SURFACE entity.
 *
 * \return the end draft distance \c end_draft_distance.
 */
double
dxf_surface_revolved_get_end_draft_distance
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->end_draft_distance);
}


/*!
 * \brief Set the end draft distance \c end_draft_distance of a DXF
 * revolved \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_end_draft_distance
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double end_draft_distance
                /*!< the end draft distance \c end_draft_distance of
                 * a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->end_draft_distance = end_draft_distance;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the twist angle \c twist_angle of a DXF revolved
 * \c SURFACE entity.
 *
 * \return the twist angle \c twist_angle.
 */
double
dxf_surface_revolved_get_twist_angle
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->twist_angle);
}


/*!
 * \brief Set the twist angle \c twist_angle of a DXF revolved
 * \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_twist_angle
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        double twist_angle
                /*!< the twist angle \c twist_angle of a DXF revolved
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->twist_angle = twist_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the \c ID from a DXF revolved \c SURFACE entity.
 *
 * \return \c ID.
 */
int32_t
dxf_surface_revolved_get_ID
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->ID);
}


/*!
 * \brief Set the \c ID for a DXF revolved \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_ID
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        int32_t ID
                /*!< the \c ID to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->ID = ID;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the \c binary_data_size from a DXF revolved \c SURFACE
 * entity.
 *
 * \return \c binary_data_size.
 */
int32_t
dxf_surface_revolved_get_binary_data_size
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->binary_data_size);
}


/*!
 * \brief Set the \c binary_data_size for a DXF revolved \c SURFACE
 * entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_binary_data_size
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        int32_t binary_data_size
                /*!< the \c binary_data_size to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->binary_data_size = binary_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the \c solid_flag from a DXF revolved \c SURFACE entity.
 *
 * \return \c solid_flag.
 */
int
dxf_surface_revolved_get_solid_flag
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->solid_flag);
}


/*!
 * \brief Set the \c solid_flag for a DXF revolved \c SURFACE entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_solid_flag
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        int solid_flag
                /*!< the \c solid_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->solid_flag = solid_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the \c close_to_axis_flag from a DXF revolved \c SURFACE
 * entity.
 *
 * \return \c close_to_axis_flag.
 */
int
dxf_surface_revolved_get_close_to_axis_flag
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface->close_to_axis_flag);
}


/*!
 * \brief Set the \c close_to_axis_flag for a DXF revolved \c SURFACE
 * entity.
 *
 * \return a pointer to \c revolved_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_close_to_axis_flag
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        int close_to_axis_flag
                /*!< the \c close_to_axis_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        revolved_surface->close_to_axis_flag = close_to_axis_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the pointer to the \c binary_data from a DXF revolved
 * \c SURFACE entity.
 *
 * \return pointer to the \c binary_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_surface_revolved_get_binary_data
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->binary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) revolved_surface->binary_data);
}


/*!
 * \brief Set the pointer to the \c binary_data for a DXF revolved
 * \c SURFACE entity.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_binary_data
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
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
        revolved_surface->binary_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the pointer to the next DXF revolved \c SURFACE entity
 * from a DXF revolved \c SURFACE entity.
 *
 * \return pointer to the next DXF revolved \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_get_next
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurfaceRevolved *) revolved_surface->next);
}


/*!
 * \brief Set the pointer to the next DXF revolved \c SURFACE for a DXF
 * revolved \c SURFACE entity.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_set_next
(
        DxfSurfaceRevolved *revolved_surface,
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
        DxfSurfaceRevolved *next
                /*!< a pointer to the next DXF revolved \c SURFACE for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
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
        revolved_surface->next = (struct DxfSurfaceRevolved *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (revolved_surface);
}


/*!
 * \brief Get the pointer to the last DXF revolved \c SURFACE entity
 * from a linked list of DXF revolved \c SURFACE entities.
 *
 * \return pointer to the last DXF revolved \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurfaceRevolved *
dxf_surface_revolved_get_last
(
        DxfSurfaceRevolved *revolved_surface
                /*!< a pointer to a DXF revolved \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (revolved_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (revolved_surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfSurfaceRevolved *) revolved_surface);
        }
        DxfSurfaceRevolved *iter = (DxfSurfaceRevolved *) revolved_surface->next;
        while (iter->next != NULL)
        {
                iter = (DxfSurfaceRevolved *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurfaceRevolved *) iter);
}


/*!
 * \brief Allocate memory for a DXF swept \c SURFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceSwept *
dxf_surface_swept_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSurfaceSwept *swept_surface = NULL;
        size_t size;

        size = sizeof (DxfSurfaceSwept);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((swept_surface = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                swept_surface = NULL;
        }
        else
        {
                memset (swept_surface, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF swept
 * \c SURFACE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSurfaceSwept *
dxf_surface_swept_init
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to the DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                swept_surface = dxf_surface_swept_new ();
        }
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        swept_surface->p1 = (DxfPoint *) dxf_point_init (swept_surface->p1);
        if (swept_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->transform_sweep_matrix = (DxfDouble *) dxf_double_init (swept_surface->transform_sweep_matrix);
        if (swept_surface->transform_sweep_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->transform_path_matrix = (DxfDouble *) dxf_double_init (swept_surface->transform_path_matrix);
        if (swept_surface->transform_path_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->transform_sweep_matrix2 = (DxfDouble *) dxf_double_init (swept_surface->transform_sweep_matrix2);
        if (swept_surface->transform_sweep_matrix2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->transform_path_matrix2 = (DxfDouble *) dxf_double_init (swept_surface->transform_path_matrix2);
        if (swept_surface->transform_path_matrix2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->sweep_binary_data = (DxfBinaryData *) dxf_binary_data_init (swept_surface->sweep_binary_data);
        if (swept_surface->sweep_binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->path_binary_data = (DxfBinaryData *) dxf_binary_data_init (swept_surface->path_binary_data);
        if (swept_surface->path_binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        swept_surface->draft_angle = 0.0;
        swept_surface->start_draft_distance = 0.0;
        swept_surface->end_draft_distance = 0.0;
        swept_surface->twist_angle = 0.0;
        swept_surface->scale_factor = 1.0;
        swept_surface->align_angle = 0.0;
        swept_surface->sweep_alignment_option = 0;
        swept_surface->sweep_ID = 0;
        swept_surface->sweep_binary_data_size = 0;
        swept_surface->path_ID = 0;
        swept_surface->path_binary_data_size = 0;
        swept_surface->solid_flag = 0;
        swept_surface->align_start_flag = 0;
        swept_surface->bank_flag = 0;
        swept_surface->base_point_set_flag = 0;
        swept_surface->sweep_transform_computed_flag = 0;
        swept_surface->path_transform_computed_flag = 0;
        swept_surface->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Read data from a DXF file into a DXF swept \c SURFACE
 * entity.
 * 
 * The last line read from file contained the string
 * "AcDbSweptSurface". \n
 * Now follows some data for the swept \c SURFACE, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c swept_surface. \n
 *
 * \return a pointer to \c swept_surface.
 */
DxfSurfaceSwept *
dxf_surface_swept_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfDouble *iter40 = NULL;
        DxfDouble *iter41 = NULL;
        DxfDouble *iter46 = NULL;
        DxfDouble *iter47 = NULL;
        int iter90;
        DxfBinaryData *iter310 = NULL;

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
        if (fp->acad_version_number < AutoCAD_2007)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                swept_surface = dxf_surface_swept_init (swept_surface);
        }
        iter40 = (DxfDouble *) swept_surface->transform_sweep_matrix;
        iter41 = (DxfDouble *) swept_surface->transform_path_matrix;
        iter46 = (DxfDouble *) swept_surface->transform_sweep_matrix2;
        iter47 = (DxfDouble *) swept_surface->transform_path_matrix2;
        iter90 = 0;
        iter310 = (DxfBinaryData *) swept_surface->sweep_binary_data;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the reference vector for
                         * controling twist. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the reference vector for
                         * controling twist. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the reference vector for
                         * controling twist. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->p1->z0);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * transform sweep matrix value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter40->value);
                        iter40->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter40->next);
                        iter40 = (DxfDouble *) iter40->next;
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * transform path matrix value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter41->value);
                        iter41->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter41->next);
                        iter41 = (DxfDouble *) iter41->next;
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the draft
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->draft_angle);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the start
                         * draft distance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->start_draft_distance);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the end draft
                         * distance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->end_draft_distance);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing the twist
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->twist_angle);
                }
                else if (strcmp (temp_string, "46") == 0)
                {
                        /* Now follows a string containing the
                         * transform sweep matrix 2 value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter46->value);
                        iter46->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter46->next);
                        iter46 = (DxfDouble *) iter46->next;
                }
                else if (strcmp (temp_string, "47") == 0)
                {
                        /* Now follows a string containing the
                         * transform path matrix 2 value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter47->value);
                        iter47->next = (struct DxfDouble *) dxf_double_init ((DxfDouble *) iter47->next);
                        iter47 = (DxfDouble *) iter47->next;
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the scale
                         * factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->scale_factor);
                }
                else if (strcmp (temp_string, "49") == 0)
                {
                        /* Now follows a string containing the align
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &swept_surface->align_angle);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the sweep
                         * alignment option number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &swept_surface->sweep_alignment_option);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        if (iter90 == 0)
                        {
                                /* Now follows a string containing the
                                 * ID of the sweep entity. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &swept_surface->sweep_ID);
                        }
                        if (iter90 == 1)
                        {
                                /* Now follows a string containing the
                                 * sweep binary data size. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &swept_surface->sweep_binary_data_size);
                        }
                        if (iter90 == 2)
                        {
                                /* Now follows a string containing the
                                 * ID of the path entity. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &swept_surface->path_ID);
                        }
                        if (iter90 == 3)
                        {
                                /* Now follows a string containing the
                                 * path binary data size. */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%" PRIi32 "\n", &swept_surface->path_binary_data_size);
                        }
                        iter90++;
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing the solid
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &swept_surface->solid_flag);
                }
                else if (strcmp (temp_string, "292") == 0)
                {
                        /* Now follows a string containing the align
                         * start flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &swept_surface->align_start_flag);
                }
                else if (strcmp (temp_string, "293") == 0)
                {
                        /* Now follows a string containing the bank
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &swept_surface->bank_flag);
                }
                else if (strcmp (temp_string, "294") == 0)
                {
                        /* Now follows a string containing the base
                         * point set flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &swept_surface->base_point_set_flag);
                }
                else if (strcmp (temp_string, "295") == 0)
                {
                        /* Now follows a string containing the sweep
                         * transform computed flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &swept_surface->sweep_transform_computed_flag);
                }
                else if (strcmp (temp_string, "296") == 0)
                {
                        /* Now follows a string containing the path
                         * transform completed flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &swept_surface->path_transform_computed_flag);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /*! \todo Fix the parsing of binary data. */
                        /* Now follows a string containing binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_data_init ((DxfBinaryData *) iter310->next);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Write DXF output to \c fp for a swept DXF \c SURFACE entity.
 */
int
dxf_surface_swept_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to the swept DXF \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSweptSurface\n");
        }
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", swept_surface->sweep_ID);
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", swept_surface->sweep_binary_data_size);
        if (swept_surface->sweep_binary_data != NULL)
        {
                DxfBinaryData *iter310;
                iter310 = (DxfBinaryData *) swept_surface->sweep_binary_data;
                while (iter310 != NULL)
                {
                        fprintf (fp->fp, "310\n%s\n", iter310->data_line);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
        }


#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF swept \c SURFACE entity
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_surface_swept_free
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to the memory occupied by the DXF swept
                 * \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (swept_surface->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_point_free (swept_surface->p1);
        dxf_double_free_list (swept_surface->transform_sweep_matrix);
        dxf_double_free_list (swept_surface->transform_path_matrix);
        dxf_double_free_list (swept_surface->transform_sweep_matrix2);
        dxf_double_free_list (swept_surface->transform_path_matrix2);
        dxf_binary_data_free_list (swept_surface->sweep_binary_data);
        dxf_binary_data_free_list (swept_surface->path_binary_data);
        free (swept_surface);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * swept \c SURFACE entities and all their data fields.
 */
void
dxf_surface_swept_free_list
(
        DxfSurfaceSwept *swept_surfaces
                /*!< a pointer to the single linked list of DXF swept
                 * \c SURFACE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (swept_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (swept_surfaces != NULL)
        {
                DxfSurfaceSwept *iter = (DxfSurfaceSwept *) swept_surfaces->next;
                dxf_surface_swept_free (swept_surfaces);
                swept_surfaces = (DxfSurfaceSwept *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the reference vector for twist of a DXF swept \c SURFACE
 * entity.
 *
 * \return the reference vector for twist \c p1.
 */
DxfPoint *
dxf_surface_swept_get_p1
(
        DxfSurfaceSwept *swept_surfaces
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surfaces == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surfaces->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surfaces->p1);
}


/*!
 * \brief Set the reference vector for twist \c p1 for a DXF swept
 * \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_p1
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        DxfPoint *p1
                /*!< the reference vector for twist \c p1 to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
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
        swept_surface->p1 = (DxfPoint *) p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the X-value of the reference vector for twist \c x1 of a
 * DXF swept \c SURFACE entity.
 *
 * \return the X-value of the reference vector for twist \c x1.
 */
double
dxf_surface_swept_get_x1
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (swept_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->p1->x0);
}


/*!
 * \brief Set the X-value of the reference vector for twist \c x1 of a
 * DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_x1
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double x1
                /*!< the X-value of the reference vector for twist \c x1
                 * of a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the Y-value of the reference vector for twist \c y1 of a
 * DXF swept \c SURFACE entity.
 *
 * \return the Y-value of the reference vector for twist \c y1.
 */
double
dxf_surface_swept_get_y1
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (swept_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->p1->y0);
}


/*!
 * \brief Set the Y-value of the reference vector for twist \c y1 of a
 * DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_y1
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double y1
                /*!< the Y-value of the reference vector for twist \c y1
                 * of a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the Z-value of the reference vector for twist \c z1 of a
 * DXF swept \c SURFACE entity.
 *
 * \return the Z-value of the reference vector for twist \c z1.
 */
double
dxf_surface_swept_get_z1
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (swept_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->p1->z0);
}


/*!
 * \brief Set the Z-value of the reference vector for twist \c z1 of a
 * DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_z1
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double z1
                /*!< the Z-value of the reference vector for twist \c z1
                 * of a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the transform sweep matrix \c transform_sweep_matrix of a
 * DXF swept \c SURFACE entity.
 *
 * \return the transform sweep matrix \c transform_sweep_matrix.
 */
DxfDouble *
dxf_surface_swept_get_transform_sweep_matrix
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->transform_sweep_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) swept_surface->transform_sweep_matrix);
}


/*!
 * \brief Set the transform sweep matrix \c transform_sweep_matrix of a
 * DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_transform_sweep_matrix
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        DxfDouble *transform_sweep_matrix
                /*!< the transform sweep matrix
                 * \c transform_sweep_matrix of a DXF swept \c SURFACE
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (transform_sweep_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->transform_sweep_matrix = (DxfDouble *) transform_sweep_matrix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the transform path matrix \c transform_path_matrix of a
 * DXF swept \c SURFACE entity.
 *
 * \return the transform path matrix \c transform_path_matrix.
 */
DxfDouble *
dxf_surface_swept_get_transform_path_matrix
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->transform_path_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) swept_surface->transform_path_matrix);
}


/*!
 * \brief Set the transform path matrix \c transform_path_matrix of a
 * DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_transform_path_matrix
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        DxfDouble *transform_path_matrix
                /*!< the transform path matrix \c transform_path_matrix
                 * of a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (transform_path_matrix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->transform_path_matrix = (DxfDouble *) transform_path_matrix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the draft angle \c draft_angle of a DXF swept
 * \c SURFACE entity.
 *
 * \return the draft angle \c draft_angle.
 */
double
dxf_surface_swept_get_draft_angle
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->draft_angle);
}


/*!
 * \brief Set the draft angle \c draft_angle of a DXF swept
 * \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_draft_angle
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double draft_angle
                /*!< the draft angle \c draft_angle of a DXF swept
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->draft_angle = draft_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the start draft distance \c start_draft_distance of a DXF
 * swept \c SURFACE entity.
 *
 * \return the start draft distance \c start_draft_distance.
 */
double
dxf_surface_swept_get_start_draft_distance
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->start_draft_distance);
}


/*!
 * \brief Set the start draft distance \c start_draft_distance of a DXF
 * swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_start_draft_distance
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double start_draft_distance
                /*!< the start draft distance \c start_draft_distance of
                 * a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->start_draft_distance = start_draft_distance;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the end draft distance \c end_draft_distance of a DXF
 * swept \c SURFACE entity.
 *
 * \return the end draft distance \c end_draft_distance.
 */
double
dxf_surface_swept_get_end_draft_distance
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->end_draft_distance);
}


/*!
 * \brief Set the end draft distance \c end_draft_distance of a DXF
 * swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_end_draft_distance
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double end_draft_distance
                /*!< the end draft distance \c end_draft_distance of
                 * a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->end_draft_distance = end_draft_distance;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the twist angle \c twist_angle of a DXF swept \c SURFACE
 * entity.
 *
 * \return the twist angle \c twist_angle.
 */
double
dxf_surface_swept_get_twist_angle
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->twist_angle);
}


/*!
 * \brief Set the twist angle \c twist_angle of a DXF swept \c SURFACE
 * entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_twist_angle
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double twist_angle
                /*!< the twist angle \c twist_angle of a DXF swept
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->twist_angle = twist_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the second transform sweep matrix
 * \c transform_sweep_matrix2 of a DXF swept \c SURFACE entity.
 *
 * \return the second transform sweep matrix \c transform_sweep_matrix2.
 */
DxfDouble *
dxf_surface_swept_get_transform_sweep_matrix2
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->transform_sweep_matrix2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) swept_surface->transform_sweep_matrix2);
}


/*!
 * \brief Set the second transform sweep matrix
 * \c transform_sweep_matrix2 of a DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_transform_sweep_matrix2
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        DxfDouble *transform_sweep_matrix2
                /*!< the second transform sweep matrix
                 * \c transform_sweep_matrix2 of a DXF swept \c SURFACE
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (transform_sweep_matrix2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->transform_sweep_matrix2 = (DxfDouble *) transform_sweep_matrix2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the second transform path matrix \c transform_path_matrix2
 * of a DXF swept \c SURFACE entity.
 *
 * \return the transform path matrix2 \c transform_path_matrix2.
 */
DxfDouble *
dxf_surface_swept_get_transform_path_matrix2
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->transform_path_matrix2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) swept_surface->transform_path_matrix2);
}


/*!
 * \brief Set the second transform path matrix \c transform_path_matrix2
 * of a DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_transform_path_matrix2
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        DxfDouble *transform_path_matrix2
                /*!< the second transform path matrix
                 * \c transform_path_matrix2 of a DXF swept \c SURFACE
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (transform_path_matrix2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->transform_path_matrix2 = (DxfDouble *) transform_path_matrix2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the scale factor \c scale_factor of a DXF swept \c SURFACE
 * entity.
 *
 * \return the scale factor \c scale_factor.
 */
double
dxf_surface_swept_get_scale_factor
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->scale_factor);
}


/*!
 * \brief Set the scale factor \c scale_factor of a DXF swept \c SURFACE
 * entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_scale_factor
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double scale_factor
                /*!< the scale factor \c scale_factor of a DXF swept
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->scale_factor = scale_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the align angle \c align_angle of a DXF swept \c SURFACE
 * entity.
 *
 * \return the align angle \c align_angle.
 */
double
dxf_surface_swept_get_align_angle
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->align_angle);
}


/*!
 * \brief Set the align angle \c align_angle of a DXF swept \c SURFACE
 * entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_align_angle
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        double align_angle
                /*!< the align angle \c align_angle of a DXF swept
                 * \c SURFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->align_angle = align_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c sweep_alignment_option from a DXF swept \c SURFACE
 * entity.
 *
 * \return \c sweep_alignment_option.
 */
int16_t
dxf_surface_swept_get_sweep_alignment_option
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (swept_surface->sweep_alignment_option < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (swept_surface->sweep_alignment_option > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->sweep_alignment_option);
}


/*!
 * \brief Set the \c sweep_alignment_option for a DXF swept
 * \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_sweep_alignment_option
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int16_t sweep_alignment_option
                /*!< the \c sweep_alignment_option to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sweep_alignment_option < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (sweep_alignment_option > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        swept_surface->sweep_alignment_option = sweep_alignment_option;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c sweep_ID from a DXF swept \c SURFACE entity.
 *
 * \return \c sweep_ID.
 */
int32_t
dxf_surface_swept_get_sweep_ID
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->sweep_ID);
}


/*!
 * \brief Set the \c sweep_ID for a DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_sweep_ID
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int32_t sweep_ID
                /*!< the \c sweep_ID to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->sweep_ID = sweep_ID;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c sweep_binary_data_size from a DXF swept \c SURFACE
 * entity.
 *
 * \return \c sweep_binary_data_size.
 */
int32_t
dxf_surface_swept_get_sweep_binary_data_size
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->sweep_binary_data_size);
}


/*!
 * \brief Set the \c sweep_binary_data_size for a DXF swept \c SURFACE
 * entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_sweep_binary_data_size
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int32_t sweep_binary_data_size
                /*!< the \c sweep_binary_data_size to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->sweep_binary_data_size = sweep_binary_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c path_ID from a DXF swept \c SURFACE entity.
 *
 * \return \c path_ID.
 */
int32_t
dxf_surface_swept_get_path_ID
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->path_ID);
}


/*!
 * \brief Set the \c path_ID for a DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_path_ID
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int32_t path_ID
                /*!< the \c path_ID to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->path_ID = path_ID;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c path_binary_data_size from a DXF swept \c SURFACE
 * entity.
 *
 * \return \c path_binary_data_size.
 */
int32_t
dxf_surface_swept_get_path_binary_data_size
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->path_binary_data_size);
}


/*!
 * \brief Set the \c path_binary_data_size for a DXF swept \c SURFACE
 * entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_path_binary_data_size
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int32_t path_binary_data_size
                /*!< the \c path_binary_data_size to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->path_binary_data_size = path_binary_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c solid_flag from a DXF swept \c SURFACE entity.
 *
 * \return \c solid_flag.
 */
int
dxf_surface_swept_get_solid_flag
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->solid_flag);
}


/*!
 * \brief Set the \c solid_flag for a DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_solid_flag
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int solid_flag
                /*!< the \c solid_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->solid_flag = solid_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c align_start_flag from a DXF swept \c SURFACE
 * entity.
 *
 * \return \c align_start_flag.
 */
int
dxf_surface_swept_get_align_start_flag
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->align_start_flag);
}


/*!
 * \brief Set the \c align_start_flag for a DXF swept \c SURFACE
 * entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_align_start_flag
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int align_start_flag
                /*!< the \c align_start_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->align_start_flag = align_start_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c bank_flag from a DXF swept \c SURFACE entity.
 *
 * \return \c bank_flag.
 */
int
dxf_surface_swept_get_bank_flag
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->bank_flag);
}


/*!
 * \brief Set the \c bank_flag for a DXF swept \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_bank_flag
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int bank_flag
                /*!< the \c bank_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->bank_flag = bank_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c base_point_set_flag from a DXF swept \c SURFACE
 * entity.
 *
 * \return \c base_point_set_flag.
 */
int
dxf_surface_swept_get_base_point_set_flag
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->base_point_set_flag);
}


/*!
 * \brief Set the \c base_point_set_flag for a DXF swept \c SURFACE
 * entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_base_point_set_flag
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int base_point_set_flag
                /*!< the \c base_point_set_flag to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->base_point_set_flag = base_point_set_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the \c sweep_transform_computed_flag from a DXF swept
 * \c SURFACE entity.
 *
 * \return \c sweep_transform_computed_flag.
 */
int
dxf_surface_swept_get_sweep_transform_computed_flag
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface->sweep_transform_computed_flag);
}


/*!
 * \brief Set the \c sweep_transform_computed_flag for a DXF swept
 * \c SURFACE entity.
 *
 * \return a pointer to \c swept_surface when successful, or \c NULL
 * when an error occurred.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_sweep_transform_computed_flag
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        int sweep_transform_computed_flag
                /*!< the \c sweep_transform_computed_flag to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->sweep_transform_computed_flag = sweep_transform_computed_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the pointer to the \c sweep_binary_data from a DXF swept
 * \c SURFACE entity.
 *
 * \return pointer to the \c sweep_binary_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_surface_swept_get_sweep_binary_data
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->sweep_binary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) swept_surface->sweep_binary_data);
}


/*!
 * \brief Set the pointer to the \c sweep_binary_data for a DXF swept
 * \c SURFACE entity.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_sweep_binary_data
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        DxfBinaryData *sweep_binary_data
                /*!< a string containing the pointer to the
                 * \c sweep_binary_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sweep_binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->sweep_binary_data = (DxfBinaryData *) sweep_binary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the pointer to the \c path_binary_data from a DXF swept
 * \c SURFACE entity.
 *
 * \return pointer to the \c path_binary_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_surface_swept_get_path_binary_data
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->path_binary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) swept_surface->path_binary_data);
}


/*!
 * \brief Set the pointer to the \c path_binary_data for a DXF swept
 * \c SURFACE entity.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_path_binary_data
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        DxfBinaryData *path_binary_data
                /*!< a string containing the pointer to the
                 * \c path_binary_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (path_binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        swept_surface->path_binary_data = (DxfBinaryData *) path_binary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the pointer to the next DXF sept \c SURFACE entity
 * from a DXF swept \c SURFACE entity.
 *
 * \return pointer to the next DXF swept \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurfaceSwept *
dxf_surface_swept_get_next
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurfaceSwept *) swept_surface->next);
}


/*!
 * \brief Set the pointer to the next DXF swept \c SURFACE for a DXF
 * swept \c SURFACE entity.
 */
DxfSurfaceSwept *
dxf_surface_swept_set_next
(
        DxfSurfaceSwept *swept_surface,
                /*!< a pointer to a DXF swept \c SURFACE entity. */
        DxfSurfaceSwept *next
                /*!< a pointer to the next DXF swept \c SURFACE for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
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
        swept_surface->next = (struct DxfSurfaceSwept *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (swept_surface);
}


/*!
 * \brief Get the pointer to the last DXF swept \c SURFACE entity
 * from a linked list of DXF swept \c SURFACE entities.
 *
 * \return pointer to the last DXF swept \c SURFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSurfaceSwept *
dxf_surface_swept_get_last
(
        DxfSurfaceSwept *swept_surface
                /*!< a pointer to a DXF swept \c SURFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (swept_surface == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (swept_surface->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfSurfaceSwept *) swept_surface);
        }
        DxfSurfaceSwept *iter = (DxfSurfaceSwept *) swept_surface->next;
        while (iter->next != NULL)
        {
                iter = (DxfSurfaceSwept *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSurfaceSwept *) iter);
}


/* EOF */
