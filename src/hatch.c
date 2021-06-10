/*!
 * \file hatch.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2016, 2017, 2018,
 * 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF hatch entity (\c HATCH).
 *
 * \warning The hatch entity requires AutoCAD version R14 or higher.\n
 *
 * \htmlinclude "hatch.html"
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


#include "hatch.h"


/* dxf_hatch functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH.
 *
 * Fill the memory contents with zeros.
 */
DxfHatch *
dxf_hatch_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatch *hatch = NULL;
        size_t size;

        size = sizeof (DxfHatch);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((hatch = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                hatch = NULL;
        }
        else
        {
                memset (hatch, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatch *
dxf_hatch_init
(
        DxfHatch *hatch
                /*!< DXF hatch entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                hatch = dxf_hatch_new ();
        }
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        hatch->id_code = 0;
        hatch->linetype = strdup (DXF_DEFAULT_LINETYPE);
        hatch->layer = strdup (DXF_DEFAULT_LAYER);
        hatch->elevation = 0.0;
        hatch->thickness = 0.0;
        hatch->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        hatch->visibility = DXF_DEFAULT_VISIBILITY;
        hatch->color = DXF_COLOR_BYLAYER;
        hatch->paperspace = DXF_MODELSPACE;
        hatch->graphics_data_size = 0;
        hatch->shadow_mode = 0;
        hatch->dictionary_owner_soft = strdup ("");
        hatch->object_owner_soft = strdup ("");
        hatch->material = strdup ("");
        hatch->dictionary_owner_hard = strdup ("");
        hatch->lineweight = 0;
        hatch->plot_style_name = strdup ("");
        hatch->color_value = 0;
        hatch->color_name = strdup ("");
        hatch->transparency = 0;
        hatch->pattern_name = strdup ("");
        hatch->pattern_scale = 1.0;
        hatch->pixel_size = 1.0;
        hatch->pattern_angle = 0.0;
        hatch->solid_fill = 0;
        hatch->associative = 1;
        hatch->hatch_style = 0;
        hatch->hatch_pattern_type = 0;
        hatch->pattern_double = 0;
        hatch->number_of_pattern_def_lines = 0;
        hatch->number_of_boundary_paths = 0;
        hatch->number_of_seed_points = 0;
        hatch->extr_x0 = 0.0;
        hatch->extr_y0 = 0.0;
        hatch->extr_z0 = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        hatch->binary_graphics_data = NULL;
        hatch->p0 = NULL;
        hatch->paths = NULL;
        hatch->patterns = NULL;
        hatch->def_lines = NULL;
        hatch->seed_points = NULL;
        hatch->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Write DXF output to a file for a hatch entity (\c HATCH).
 */
int
dxf_hatch_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfHatch *hatch
                /*!< DXF hatch entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("HATCH");
        DxfHatchPatternDefLine *line = NULL;
        DxfHatchPatternSeedPoint *point = NULL;

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
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (hatch->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (hatch->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning: empty layer string for the %s entity with id-code: %x\n")),
                        dxf_entity_name, hatch->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0")),
                        dxf_entity_name);
                hatch->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (strcmp (hatch->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning: empty linetype string for the %s entity with id-code: %x\n")),
                        dxf_entity_name, hatch->id_code);
                fprintf (stderr,
                  (_("    %s entity is reset to default linetype")),
                        dxf_entity_name);
                hatch->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (hatch->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", hatch->id_code);
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
        if ((strcmp (hatch->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", hatch->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (hatch->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", hatch->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (hatch->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", hatch->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (hatch->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", hatch->layer);
        if (strcmp (hatch->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", hatch->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (hatch->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", hatch->material);
        }
        if (hatch->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", hatch->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", hatch->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (hatch->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", hatch->elevation);
        }
        if (hatch->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", hatch->thickness);
        }
        if (hatch->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", hatch->linetype_scale);
        }
        if (hatch->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", hatch->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", hatch->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", hatch->graphics_data_size);
#endif
                if (hatch->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) hatch->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", hatch->color_value);
                fprintf (fp->fp, "430\n%s\n", hatch->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", hatch->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", hatch->plot_style_name);
                fprintf (fp->fp, "284\n%hd\n", hatch->shadow_mode);
        }
        fprintf (fp->fp, "100\nAcDbHatch\n");
        fprintf (fp->fp, " 10\n%f\n", hatch->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", hatch->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", hatch->p0->z0);
        fprintf (fp->fp, "210\n%f\n", hatch->extr_x0);
        fprintf (fp->fp, "220\n%f\n", hatch->extr_y0);
        fprintf (fp->fp, "230\n%f\n", hatch->extr_z0);
        fprintf (fp->fp, "  2\n%s\n", hatch->pattern_name);
        fprintf (fp->fp, " 70\n%hd\n", hatch->solid_fill);
        fprintf (fp->fp, " 71\n%hd\n", hatch->associative);
        fprintf (fp->fp, " 91\n%" PRIi32 "\n", hatch->number_of_boundary_paths);
        dxf_hatch_boundary_path_write (fp, (DxfHatchBoundaryPath *) hatch->paths);
        fprintf (fp->fp, " 75\n%hd\n", hatch->hatch_style);
        fprintf (fp->fp, " 76\n%hd\n", hatch->hatch_pattern_type);
        if (!hatch->solid_fill)
        {
                fprintf (fp->fp, " 52\n%f\n", hatch->pattern_angle);
                fprintf (fp->fp, " 41\n%f\n", hatch->pattern_scale);
                fprintf (fp->fp, " 77\n%hd\n", hatch->pattern_double);
        }
        fprintf (fp->fp, " 78\n%hd\n", hatch->number_of_pattern_def_lines);
        line = (DxfHatchPatternDefLine *) hatch->def_lines;
        while (line != NULL)
        {
                dxf_hatch_pattern_def_line_write (fp, (DxfHatchPatternDefLine *) line);
                line = (DxfHatchPatternDefLine *) line->next;
        }
        fprintf (fp->fp, " 47\n%f\n", hatch->pixel_size);
        fprintf (fp->fp, " 98\n%" PRIi32 "\n", hatch->number_of_seed_points);
        point = (DxfHatchPatternSeedPoint *) hatch->seed_points;
        while (point != NULL)
        {
                dxf_hatch_pattern_seedpoint_write (fp, (DxfHatchPatternSeedPoint *) point);
                point = (DxfHatchPatternSeedPoint *) point->next;
        }
        /* Clean up. */
        dxf_hatch_pattern_def_line_free (line);
        dxf_hatch_pattern_seedpoint_free (point);
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_free
(
        DxfHatch *hatch
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (hatch->linetype);
        free (hatch->layer);
        dxf_binary_data_free_list ((DxfBinaryData *) hatch->binary_graphics_data);
        free (hatch->dictionary_owner_soft);
        free (hatch->material);
        free (hatch->dictionary_owner_hard);
        free (hatch->plot_style_name);
        free (hatch->color_name);
        free (hatch->pattern_name);
        dxf_point_free ((DxfPoint *) hatch->p0);
        dxf_hatch_boundary_path_free_list ((DxfHatchBoundaryPath *) hatch->paths);
        dxf_hatch_pattern_free_list ((DxfHatchPattern *) hatch->patterns);
        dxf_hatch_pattern_def_line_free_list ((DxfHatchPatternDefLine *) hatch->def_lines);
        dxf_hatch_pattern_seedpoint_free_list ((DxfHatchPatternSeedPoint *) hatch->seed_points);
        free (hatch);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH entities and all their data fields.
 */
void
dxf_hatch_free_list
(
        DxfHatch *hatches
                /*!< pointer to the single linked list of DXF \c HATCH
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatches == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatches != NULL)
        {
                DxfHatch *iter = (DxfHatch *) hatches->next;
                dxf_hatch_free (hatches);
                hatches = (DxfHatch *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH.
 *
 * \return ID code.
 */
int
dxf_hatch_get_id_code
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_id_code
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH pattern. */
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
        if (hatch == NULL)
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
        hatch->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the linetype from a DXF \c HATCH entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_hatch_get_linetype
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_linetype
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the layer from a DXF \c HATCH entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_hatch_get_layer
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->layer));
}


/*!
 * \brief Set the layer for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_layer
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the elevation from a DXF \c HATCH entity.
 *
 * \return elevation.
 */
double
dxf_hatch_get_elevation
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_elevation
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the thickness from a DXF \c HATCH entity.
 *
 * \return thickness.
 */
double
dxf_hatch_get_thickness
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_thickness
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the linetype scale from a DXF \c HATCH entity.
 *
 * \return linetype scale.
 */
double
dxf_hatch_get_linetype_scale
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_linetype_scale
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the visibility from a DXF \c HATCH entity.
 *
 * \return visibility.
 */
int16_t
dxf_hatch_get_visibility
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_visibility
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the color from a DXF \c HATCH entity.
 *
 * \return color.
 */
int16_t
dxf_hatch_get_color
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->color);
}


/*!
 * \brief Set the color for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_color
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        int16_t color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c HATCH entity.
 *
 * \return paperspace flag value.
 */
int16_t
dxf_hatch_get_paperspace
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_paperspace
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        int16_t paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the graphics data size value from a DXF \c HATCH entity.
 *
 * \return graphics data size flag value.
 */
int32_t
dxf_hatch_get_graphics_data_size
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->graphics_data_size);
}


/*!
 * \brief Set the graphics data size value for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_graphics_data_size
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        int32_t graphics_data_size
                /*!< the graphics data size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pointer to the binary graphics data from a DXF 
 * \c HATCH entity.
 *
 * \return pointer to the binary graphics data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_hatch_get_binary_graphics_data
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) hatch->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the binary_graphics_data for a DXF
 * \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_binary_graphics_data
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c HATCH entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_hatch_get_dictionary_owner_soft
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_dictionary_owner_soft
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c HATCH entity.
 *
 * \return soft pointer to the object_owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_hatch_get_object_owner_soft
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_object_owner_soft
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c HATCH entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_hatch_get_material
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c HATCH entity.
 *
 * \return a pointer to \c hatch when successful, or \c NULL when an
 * error occurred.
 */
DxfHatch *
dxf_hatch_set_material
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c HATCH entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_hatch_get_dictionary_owner_hard
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_dictionary_owner_hard
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the \c lineweight from a DXF \c HATCH entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_hatch_get_lineweight
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->lineweight < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->lineweight == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c HATCH entity.
 *
 * \return a pointer to \c hatch when successful, or \c NULL when an
 * error occurred.
 */
DxfHatch *
dxf_hatch_set_lineweight
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lineweight < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (lineweight == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        hatch->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c HATCH entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_hatch_get_plot_style_name
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c HATCH entity.
 *
 * \return a pointer to \c hatch when successful, or \c NULL when an
 * error occurred.
 */
DxfHatch *
dxf_hatch_set_plot_style_name
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the \c color_value from a DXF \c HATCH entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_hatch_get_color_value
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c HATCH entity.
 *
 * \return a pointer to \c hatch when successful, or \c NULL when an
 * error occurred.
 */
DxfHatch *
dxf_hatch_set_color_value
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the \c color_name from a DXF \c HATCH entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_hatch_get_color_name
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c HATCH entity.
 *
 * \return a pointer to \c hatch when successful, or \c NULL when an
 * error occurred.
 */
DxfHatch *
dxf_hatch_set_color_name
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the \c transparency from a DXF \c HATCH entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_hatch_get_transparency
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c HATCH entity.
 *
 * \return a pointer to \c hatch when successful, or \c NULL when an
 * error occurred.
 */
DxfHatch *
dxf_hatch_set_transparency
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pattern name from a DXF \c HATCH entity.
 *
 * \return pattern name when sucessful, \c NULL when an error occurred.
 */
char *
dxf_hatch_get_pattern_name
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->pattern_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (hatch->pattern_name));
}


/*!
 * \brief Set the pattern name for a DXF \c HATCH entity.
 */
DxfHatch *
dxf_hatch_set_pattern_name
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        char *pattern_name
                /*!< a string containing the pattern_name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (pattern_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->pattern_name = strdup (pattern_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the base point of a DXF \c HATCH entity.
 *
 * \return the base point \c p0.
 */
DxfPoint *
dxf_hatch_get_p0
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->p0);
}


/*!
 * \brief Set the base point \c p0 of a DXF \c HATCH entity.
 *
 * \return a pointer to \c hatch when successful, or \c NULL when an
 * error occurred.
 */
DxfHatch *
dxf_hatch_set_p0
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->p0 = (DxfPoint *) point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the base point X-value from a DXF \c HATCH.
 *
 * \return base point X-value.
 */
double
dxf_hatch_get_x0
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->p0->x0);
}


/*!
 * \brief Set the base point X-value for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_x0
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double x0
                /*!< the base point X-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                hatch->p0 = dxf_point_init (hatch->p0);
                if (hatch->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        hatch->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the base point Y-value from a DXF \c HATCH.
 *
 * \return base point Y-value.
 */
double
dxf_hatch_get_y0
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->p0->y0);
}


/*!
 * \brief Set the base point Y-value for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_y0
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double y0
                /*!< the base point Y-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                hatch->p0 = dxf_point_init (hatch->p0);
                if (hatch->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        hatch->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the base point Z-value from a DXF \c HATCH.
 *
 * \return base point Z-value.
 */
double
dxf_hatch_get_z0
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->p0->z0);
}


/*!
 * \brief Set the base point Z-value for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_z0
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double z0
                /*!< the base point Z-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                hatch->p0 = dxf_point_init (hatch->p0);
                if (hatch->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        hatch->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pattern scale from a DXF \c HATCH.
 *
 * \return pattern scale.
 */
double
dxf_hatch_get_pattern_scale
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->pattern_scale);
}


/*!
 * \brief Set the pattern scale for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_pattern_scale
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double pattern_scale
                /*!< the pattern scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->pattern_scale = pattern_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pixel size from a DXF \c HATCH.
 *
 * \return pixel size.
 */
double
dxf_hatch_get_pixel_size
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->pixel_size < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->pixel_size == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->pixel_size);
}


/*!
 * \brief Set the pixel size for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_pixel_size
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double pixel_size
                /*!< the pixel size to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (pixel_size < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (pixel_size == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        hatch->pixel_size = pixel_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pattern angle from a DXF \c HATCH.
 *
 * \return pattern angle.
 */
double
dxf_hatch_get_pattern_angle
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->pattern_angle);
}


/*!
 * \brief Set the pattern angle for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_pattern_angle
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double pattern_angle
                /*!< the pattern angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->pattern_angle = pattern_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the solid fill flag value from a DXF \c HATCH.
 *
 * \return solid fill flag value.
 */
int16_t
dxf_hatch_get_solid_fill
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->solid_fill < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->solid_fill > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->solid_fill);
}


/*!
 * \brief Set the solid fill flag value for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_solid_fill
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH pattern. */
        int16_t solid_fill
                /*!< the solid fill flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid_fill < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (solid_fill > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        hatch->solid_fill = solid_fill;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the associative flag value from a DXF \c HATCH.
 *
 * \return associative flag value.
 */
int16_t
dxf_hatch_get_associative
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->associative < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->associative > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->associative);
}


/*!
 * \brief Set the associative flag value for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_associative
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH pattern. */
        int16_t associative
                /*!< the associative flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (associative < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (associative > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        hatch->associative = associative;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the hatch_style flag value from a DXF \c HATCH.
 *
 * \return hatch_style flag value.
 */
int16_t
dxf_hatch_get_hatch_style
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->hatch_style < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->hatch_style > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->hatch_style);
}


/*!
 * \brief Set the hatch_style flag value for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_hatch_style
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH pattern. */
        int16_t hatch_style
                /*!< the hatch_style flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch_style < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (hatch_style > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        hatch->hatch_style = hatch_style;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the hatch_pattern_type flag value from a DXF \c HATCH.
 *
 * \return hatch_pattern_type flag value.
 */
int16_t
dxf_hatch_get_hatch_pattern_type
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->hatch_pattern_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->hatch_pattern_type > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->hatch_pattern_type);
}


/*!
 * \brief Set the hatch_pattern_type flag value for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_hatch_pattern_type
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH pattern. */
        int16_t hatch_pattern_type
                /*!< the hatch_pattern_type flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch_pattern_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (hatch_pattern_type > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        hatch->hatch_pattern_type = hatch_pattern_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pattern_double flag value from a DXF \c HATCH.
 *
 * \return pattern_double flag value.
 */
int16_t
dxf_hatch_get_pattern_double
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (hatch->pattern_double < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (hatch->pattern_double > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->pattern_double);
}


/*!
 * \brief Set the pattern_double flag value for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_pattern_double
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH pattern. */
        int16_t pattern_double
                /*!< the pattern_double flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (pattern_double < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (pattern_double > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        hatch->pattern_double = pattern_double;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the X-value of the extrusion direction from a DXF \c HATCH.
 *
 * \return X-value.
 */
double
dxf_hatch_get_extr_x0
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion direction for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_extr_x0
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double extr_x0
                /*!< the X-value of the extrusion direction to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the Y-value of the extrusion direction from a DXF \c HATCH.
 *
 * \return Y-value.
 */
double
dxf_hatch_get_extr_y0
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion direction for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_extr_y0
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double extr_y0
                /*!< the Y-value of the extrusion direction to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the Z-value of the extrusion direction from a DXF \c HATCH.
 *
 * \return Z-value.
 */
double
dxf_hatch_get_extr_z0
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion direction for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_extr_z0
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        double extr_z0
                /*!< the Z-value of the extrusion direction to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the first boundary path from a DXF \c HATCH.
 *
 * \return pointer to the first boundary path.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPath *
dxf_hatch_get_boundary_paths
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->paths == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPath *) hatch->paths);
}


/*!
 * \brief Set the first boundary path for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_boundary_paths
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        DxfHatchBoundaryPath *paths
                /*!< the first boundary path to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paths == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->paths = (struct DxfHatchBoundaryPath *) paths;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the first pattern from a DXF \c HATCH.
 *
 * \return pointer to the first pattern.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPattern *
dxf_hatch_get_patterns
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->patterns == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPattern *) hatch->patterns);
}


/*!
 * \brief Set the first pattern for a DXF \c HATCH.
 */
DxfHatch *
dxf_hatch_set_patterns
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH. */
        DxfHatchPattern *patterns
                /*!< the first pattern to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (patterns == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        hatch->patterns = (struct DxfHatchPattern *) patterns;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pointer to the next \c HATCH entity from a DXF 
 * \c HATCH entity.
 *
 * \return pointer to the next \c HATCH entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatch *
dxf_hatch_get_next
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatch *) hatch->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH for a DXF \c HATCH
 * entity.
 */
DxfHatch *
dxf_hatch_set_next
(
        DxfHatch *hatch,
                /*!< a pointer to a DXF \c HATCH entity. */
        DxfHatch *next
                /*!< a pointer to the next \c HATCH for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
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
        hatch->next = (struct DxfHatch *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (hatch);
}


/*!
 * \brief Get the pointer to the last \c HATCH entity from a linked list
 * of DXF \c HATCH entities.
 *
 * \return pointer to the last \c HATCH entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatch *
dxf_hatch_get_last
(
        DxfHatch *hatch
                /*!< a pointer to a DXF \c HATCH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (hatch->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatch *) hatch);
        }
        DxfHatch *iter = (DxfHatch *) hatch->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatch *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatch *) iter);
}


/* dxf_hatch_pattern functions. */


/*!
 * \brief Allocate memory for a DXF \c HATCH pattern.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchPattern *
dxf_hatch_pattern_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchPattern *pattern = NULL;
        size_t size;

        size = sizeof (DxfHatchPattern);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((pattern = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                pattern = NULL;
        }
        else
        {
                memset (pattern, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * pattern entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchPattern *
dxf_hatch_pattern_init
(
        DxfHatchPattern *pattern
                /*!< DXF hatch pattern entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                pattern = dxf_hatch_pattern_new ();
        }
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        pattern->id_code = 0;
        pattern->number_of_def_lines = 0;
        pattern->number_of_seed_points = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        pattern->def_lines = NULL;
        pattern->seed_points = NULL;
        pattern->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH pattern and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_free
(
        DxfHatchPattern *pattern
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * pattern entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (pattern->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (pattern->def_lines);
        free (pattern->seed_points);
        free (pattern);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH patterns and all their data fields.
 */
void
dxf_hatch_pattern_free_list
(
        DxfHatchPattern *patterns
                /*!< pointer to the single linked list of DXF \c HATCH
                 * patterns. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (patterns == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (patterns != NULL)
        {
                DxfHatchPattern *iter = (DxfHatchPattern *) patterns->next;
                dxf_hatch_pattern_free (patterns);
                patterns = (DxfHatchPattern *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH pattern.
 *
 * \return ID code.
 */
int
dxf_hatch_pattern_get_id_code
(
        DxfHatchPattern *pattern
                /*!< a pointer to a DXF \c HATCH pattern. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (pattern->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH pattern.
 */
DxfHatchPattern *
dxf_hatch_pattern_set_id_code
(
        DxfHatchPattern *pattern,
                /*!< a pointer to a DXF \c HATCH pattern. */
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
        if (pattern == NULL)
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
        pattern->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Get the number of hatch pattern definition lines from a DXF
 * \c HATCH pattern.
 *
 * \return Number of hatch pattern definition lines.
 */
int16_t
dxf_hatch_pattern_get_number_of_def_lines
(
        DxfHatchPattern *pattern
                /*!< a pointer to a DXF \c HATCH pattern. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (pattern->number_of_def_lines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern->number_of_def_lines);
}


/*!
 * \brief Set the number of hatch pattern definition lines for a DXF
 * \c HATCH pattern.
 */
DxfHatchPattern *
dxf_hatch_pattern_set_number_of_def_lines
(
        DxfHatchPattern *pattern,
                /*!< a pointer to a DXF \c HATCH pattern. */
        int16_t number_of_def_lines
                /*!< Number of hatch pattern definition lines. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_def_lines < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        pattern->number_of_def_lines = number_of_def_lines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Get a pointer to the first definition line from a DXF \c HATCH
 * pattern.
 *
 * \return pointer a pointer to the definition line.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_get_def_lines
(
        DxfHatchPattern *pattern
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (pattern->def_lines == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternDefLine *) pattern->def_lines);
}


/*!
 * \brief Set the pointer for the first definition line for a DXF
 * \c HATCH pattern.
 */
DxfHatchPattern *
dxf_hatch_pattern_set_def_lines
(
        DxfHatchPattern *pattern,
                /*!< a pointer to a DXF \c HATCH pattern. */
        DxfHatchPatternDefLine *def_lines
                /*!< a pointer to the first definition line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (def_lines == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        pattern->def_lines = (struct DxfHatchPatternDefLine *) def_lines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Get the number of hatch pattern seed points from a DXF
 * \c HATCH pattern.
 *
 * \return Number of hatch pattern seed points.
 */
int32_t
dxf_hatch_pattern_get_number_of_seed_points
(
        DxfHatchPattern *pattern
                /*!< a pointer to a DXF \c HATCH pattern. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (pattern->number_of_seed_points < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern->number_of_seed_points);
}


/*!
 * \brief Set the number of hatch pattern seed points for a DXF
 * \c HATCH pattern.
 */
DxfHatchPattern *
dxf_hatch_pattern_set_number_of_seed_points
(
        DxfHatchPattern *pattern,
                /*!< a pointer to a DXF \c HATCH pattern. */
        int32_t number_of_seed_points
                /*!< number of hatch pattern seed points. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_seed_points < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        pattern->number_of_seed_points = number_of_seed_points;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Get a pointer to the first seed point from a DXF \c HATCH
 * pattern.
 *
 * \return pointer a pointer to the seed point.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_get_seed_points
(
        DxfHatchPattern *pattern
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (pattern->seed_points == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternSeedPoint *) pattern->seed_points);
}


/*!
 * \brief Set the pointer for the first seed point for a DXF \c HATCH
 * pattern.
 */
DxfHatchPattern *
dxf_hatch_pattern_set_seed_points
(
        DxfHatchPattern *pattern,
                /*!< a pointer to a DXF \c HATCH pattern. */
        DxfHatchPatternSeedPoint *seed_points
                /*!< a pointer to the first seed point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (seed_points == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        pattern->seed_points = (struct DxfHatchPatternSeedPoint *) seed_points;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Get the pointer to the next \c HATCH pattern from a DXF
 * \c HATCH pattern def line.
 *
 * \return pointer to the next \c HATCH pattern.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPattern *
dxf_hatch_pattern_get_next
(
        DxfHatchPattern *pattern
                /*!< a pointer to a DXF \c HATCH pattern. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (pattern->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPattern *) pattern->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH pattern for a
 * DXF \c HATCH pattern.
 */
DxfHatchPattern *
dxf_hatch_pattern_set_next
(
        DxfHatchPattern *pattern,
                /*!< a pointer to a DXF \c HATCH pattern. */
        DxfHatchPatternDefLine *next
                /*!< a pointer to the next \c HATCH pattern for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
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
        pattern->next = (struct DxfHatchPattern *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (pattern);
}


/*!
 * \brief Get the pointer to the last \c HATCH pattern from a
 * linked list of DXF \c HATCH patterns.
 *
 * \return pointer to the last \c HATCH pattern.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPattern *
dxf_hatch_pattern_get_last
(
        DxfHatchPattern *pattern
                /*!< a pointer to a DXF \c HATCH pattern. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (pattern == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (pattern->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchPattern *) pattern);
        }
        DxfHatchPattern *iter = (DxfHatchPattern *) pattern->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchPattern *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPattern *) iter);
}


/* dxf_hatch_pattern_def_line_dash functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH pattern definition line
 * dash.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchPatternDefLineDash *
dxf_hatch_pattern_def_line_dash_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchPatternDefLineDash *dash = NULL;
        size_t size;

        size = sizeof (DxfHatchPatternDefLineDash);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dash = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                dash = NULL;
        }
        else
        {
                memset (dash, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dash);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * pattern definition line dash entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchPatternDefLineDash *
dxf_hatch_pattern_def_line_dash_init
(
        DxfHatchPatternDefLineDash *dash
                /*!< DXF hatch pattern definition line dash entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (dash == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dash = dxf_hatch_pattern_def_line_dash_new ();
        }
        /* Assign initial values to members. */
        dash->length = 0.0;
        dash->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dash);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH pattern
 * definition line dash and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_def_line_dash_free
(
        DxfHatchPatternDefLineDash *dash
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * pattern definition line dash entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dash == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dash->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dash);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH pattern definition line dashes and all their data fields.
 */
void
dxf_hatch_pattern_def_line_dash_free_list
(
        DxfHatchPatternDefLineDash *dashes
                /*!< pointer to the single linked list of DXF \c HATCH
                 * pattern definition line dashes. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dashes == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (dashes != NULL)
        {
                DxfHatchPatternDefLineDash *iter = (DxfHatchPatternDefLineDash *) dashes->next;
                dxf_hatch_pattern_def_line_dash_free (dashes);
                dashes = (DxfHatchPatternDefLineDash *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the length value from a DXF \c HATCH pattern def
 * line dash.
 *
 * \return length value.
 */
double
dxf_hatch_pattern_def_line_dash_get_length
(
        DxfHatchPatternDefLineDash *dash
                /*!< a pointer to a DXF \c HATCH pattern def line dash. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dash == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dash->length);
}


/*!
 * \brief Set the length value for a DXF \c HATCH pattern def line dash.
 */
DxfHatchPatternDefLineDash *
dxf_hatch_pattern_def_line_dash_set_length
(
        DxfHatchPatternDefLineDash *dash,
                /*!< a pointer to a DXF \c HATCH pattern def line dash. */
        double length
                /*!< the length value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dash == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dash->length = length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dash);
}


/*!
 * \brief Get the pointer to the next \c HATCH pattern def line dash
 * from a DXF \c HATCH pattern def line dash.
 *
 * \return pointer to the next \c HATCH pattern def line dash.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternDefLineDash *
dxf_hatch_pattern_def_line_dash_get_next
(
        DxfHatchPatternDefLineDash *dash
                /*!< a pointer to a DXF \c HATCH pattern def line dash. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dash == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dash->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternDefLineDash *) dash->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH pattern def line dash for
 * a DXF \c HATCH pattern def line dash.
 */
DxfHatchPatternDefLineDash *
dxf_hatch_pattern_def_line_dash_set_next
(
        DxfHatchPatternDefLineDash *dash,
                /*!< a pointer to a DXF \c HATCH pattern def line dash. */
        DxfHatchPatternDefLineDash *next
                /*!< a pointer to the next \c HATCH pattern def line
                 * dash for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dash == NULL)
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
        dash->next = (struct DxfHatchPatternDefLineDash *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dash);
}


/*!
 * \brief Get the pointer to the last \c HATCH pattern def line dash
 * from a linked list of DXF \c HATCH pattern def line dashes.
 *
 * \return pointer to the last \c HATCH pattern def line dash.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternDefLineDash *
dxf_hatch_pattern_def_line_dash_get_last
(
        DxfHatchPatternDefLineDash *dash
                /*!< a pointer to a DXF \c HATCH pattern def line dash. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dash == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dash->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchPatternDefLineDash *) dash);
        }
        DxfHatchPatternDefLineDash *iter = (DxfHatchPatternDefLineDash *) dash->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchPatternDefLineDash *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternDefLineDash *) iter);
}


/* dxf_hatch_pattern_def_line functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH pattern definition line.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchPatternDefLine *line = NULL;
        size_t size;

        size = sizeof (DxfHatchPatternDefLine);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((line = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                line = NULL;
        }
        else
        {
                memset (line, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * pattern definition line entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_init
(
        DxfHatchPatternDefLine *line
                /*!< DXF hatch pattern definition line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                line = dxf_hatch_pattern_def_line_new ();
        }
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        /* Assign initial values to members. */
        line->id_code = 0;
        line->angle = 0.0;
        line->x0 = 0.0;
        line->y0 = 0.0;
        line->x1 = 0.0;
        line->y1 = 0.0;
        line->number_of_dash_items = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        line->dashes = NULL;
        line->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Write DXF output to a file for a DXF \c HATCH pattern definition
 * line.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_def_line_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHatchPatternDefLine *line
                /*!< DXF hatch pattern definition line. */
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
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, " 53\n%f\n", line->angle);
        fprintf (fp->fp, " 43\n%f\n", line->x0);
        fprintf (fp->fp, " 44\n%f\n", line->y0);
        fprintf (fp->fp, " 45\n%f\n", line->x1);
        fprintf (fp->fp, " 46\n%f\n", line->y1);
        fprintf (fp->fp, " 79\n%d\n", line->number_of_dash_items);
        if (line->number_of_dash_items > 0)
        {
                /* Draw hatch pattern definition line dash items. */
                DxfHatchPatternDefLineDash *dash;
                i = 0;
                dash = dxf_hatch_pattern_def_line_get_dashes (line);
                if (dash == NULL)
                {
                        fprintf (stderr,
                          (_("Warning in %s () no pointer to the first dash found.\n")),
                          __FUNCTION__);

                }
                while (dash != NULL)
                {
                        fprintf (fp->fp, " 49\n%f\n", dash->length);
                        i++;
                        dash = dxf_hatch_pattern_def_line_dash_get_next (dash);
                }
                if (i >= line->number_of_dash_items)
                {
                        fprintf (stderr,
                          (_("Warning in %s () more dashes found than expected.\n")),
                          __FUNCTION__);

                }
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () no dash length found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH pattern
 * definition line and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_def_line_free
(
        DxfHatchPatternDefLine *line
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * pattern definition line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (line);
        line = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH pattern definition lines and all their data fields.
 */
void
dxf_hatch_pattern_def_line_free_list
(
        DxfHatchPatternDefLine *lines
                /*!< pointer to the single linked list of DXF \c HATCH
                 * pattern definition lines. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (lines != NULL)
        {
                DxfHatchPatternDefLine *iter = (DxfHatchPatternDefLine *) lines->next;
                dxf_hatch_pattern_def_line_free (lines);
                lines = (DxfHatchPatternDefLine *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH pattern def line.
 *
 * \return ID code.
 */
int
dxf_hatch_pattern_def_line_get_id_code
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH pattern def line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_id_code
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
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
        if (line == NULL)
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
        line->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the angle from a DXF \c HATCH pattern def line.
 *
 * \return angle.
 */
double
dxf_hatch_pattern_def_line_get_angle
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /*! \todo Normalize the angle. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->angle);
}


/*!
 * \brief Set the angle for a DXF \c HATCH pattern def line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_angle
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
        double angle
                /*!< the angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Normalize the angle. */
        line->angle = angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the base point X-value from a DXF \c HATCH pattern def
 * line.
 *
 * \return base point X-value.
 */
double
dxf_hatch_pattern_def_line_get_x0
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->x0);
}


/*!
 * \brief Set the base point X-value for a DXF \c HATCH pattern def line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_x0
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
        double x0
                /*!< the base point X-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the base point Y-value from a DXF \c HATCH pattern def
 * line.
 *
 * \return base point Y-value.
 */
double
dxf_hatch_pattern_def_line_get_y0
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->y0);
}


/*!
 * \brief Set the base point Y-value for a DXF \c HATCH pattern def line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_y0
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
        double y0
                /*!< the base point Y-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the offset point X-value from a DXF \c HATCH pattern def
 * line.
 *
 * \return offset point X-value.
 */
double
dxf_hatch_pattern_def_line_get_x1
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->x1);
}


/*!
 * \brief Set the offset point X-value for a DXF \c HATCH pattern def
 * line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_x1
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
        double x1
                /*!< the offset point X-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->x1 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the offset point Y-value from a DXF \c HATCH pattern def
 * line.
 *
 * \return offset point Y-value.
 */
double
dxf_hatch_pattern_def_line_get_y1
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->y1);
}


/*!
 * \brief Set the offset point Y-value for a DXF \c HATCH pattern def
 * line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_y1
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
        double y1
                /*!< the offset point Y-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->y1 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the number of hatch pattern definition line dash items
 * from a DXF \c HATCH pattern def line.
 *
 * \return number of hatch pattern definition line dash items.
 */
int16_t
dxf_hatch_pattern_def_line_get_number_of_dash_items
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->number_of_dash_items < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->number_of_dash_items);
}


/*!
 * \brief Set the number of hatch pattern definition line dash items for
 * a DXF \c HATCH pattern def line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_number_of_dash_items
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
        int16_t number_of_dash_items
                /*!< number of hatch pattern definition line dash items. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_dash_items < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        line->number_of_dash_items = number_of_dash_items;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get a pointer to the first dash from a DXF \c HATCH pattern
 * def line.
 *
 * \return pointer to the dash.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternDefLineDash *
dxf_hatch_pattern_def_line_get_dashes
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->dashes == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternDefLineDash *) line->dashes);
}


/*!
 * \brief Set the pointer for the first dash for a DXF \c HATCH pattern
 * def line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_dashes
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
        DxfHatchPatternDefLineDash *dashes
                /*!< a pointer to the first dash. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dashes == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->dashes = (struct DxfHatchPatternDefLineDash *) dashes;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the next \c HATCH pattern def line from a
 * DXF \c HATCH pattern def line.
 *
 * \return pointer to the next \c HATCH pattern def line.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_get_next
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternDefLine *) line->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH pattern def line for a
 * DXF \c HATCH pattern def line.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_set_next
(
        DxfHatchPatternDefLine *line,
                /*!< a pointer to a DXF \c HATCH pattern def line. */
        DxfHatchPatternDefLine *next
                /*!< a pointer to the next \c HATCH pattern def line
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
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
        line->next = (struct DxfHatchPatternDefLine *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the last \c HATCH pattern def line from a
 * linked list of DXF \c HATCH pattern def lines.
 *
 * \return pointer to the last \c HATCH pattern def line.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_get_last
(
        DxfHatchPatternDefLine *line
                /*!< a pointer to a DXF \c HATCH pattern def line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchPatternDefLine *) line);
        }
        DxfHatchPatternDefLine *iter = (DxfHatchPatternDefLine *) line->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchPatternDefLine *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternDefLine *) iter);
}


/* dxf_hatch_pattern_seedpoint functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH pattern seedpoint.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchPatternSeedPoint *seedpoint = NULL;
        size_t size;

        size = sizeof (DxfHatchPatternSeedPoint);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((seedpoint = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                seedpoint = NULL;
        }
        else
        {
                memset (seedpoint, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seedpoint);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * pattern seedpoint entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_init
(
        DxfHatchPatternSeedPoint *seedpoint
                /*!< DXF hatch pattern seedpoint entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seedpoint == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                seedpoint = dxf_hatch_pattern_seedpoint_new ();
        }
        if (seedpoint == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        seedpoint->id_code = 0;
        seedpoint->x0 = 0.0;
        seedpoint->y0 = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        seedpoint->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (seedpoint);
}


/*!
 * \brief Write DXF output to a file for a DXF \c HATCH pattern seed
 * point.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_seedpoint_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHatchPatternSeedPoint *seedpoint
                /*!< DXF hatch pattern seedpoint. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seedpoint == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, " 10\n%f\n", seedpoint->x0);
        fprintf (fp->fp, " 20\n%f\n", seedpoint->y0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH pattern seedpoint
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_pattern_seedpoint_free
(
        DxfHatchPatternSeedPoint *seedpoint
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * pattern seedpoint entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (seedpoint == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (seedpoint->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (seedpoint);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH pattern seed points and all their data fields.
 */
void
dxf_hatch_pattern_seedpoint_free_list
(
        DxfHatchPatternSeedPoint *hatch_pattern_seed_points
                /*!< pointer to the single linked list of DXF \c HATCH
                 * pattern seed points. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_pattern_seed_points == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_pattern_seed_points != NULL)
        {
                DxfHatchPatternSeedPoint *iter = (DxfHatchPatternSeedPoint *) hatch_pattern_seed_points->next;
                dxf_hatch_pattern_seedpoint_free (hatch_pattern_seed_points);
                hatch_pattern_seed_points = (DxfHatchPatternSeedPoint *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH pattern seed point.
 *
 * \return ID code.
 */
int
dxf_hatch_pattern_seedpoint_get_id_code
(
        DxfHatchPatternSeedPoint *point
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH pattern seed point.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_set_id_code
(
        DxfHatchPatternSeedPoint *point,
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
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
        if (point == NULL)
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
        point->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the X-value from a DXF \c HATCH pattern seed point.
 *
 * \return X-value.
 */
double
dxf_hatch_pattern_seedpoint_get_x0
(
        DxfHatchPatternSeedPoint *point
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point->x0);
}


/*!
 * \brief Set the X-value for a DXF \c HATCH pattern seed point.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_set_x0
(
        DxfHatchPatternSeedPoint *point,
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
        double x0
                /*!< the X-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the Y-value from a DXF \c HATCH pattern seed point.
 *
 * \return Y-value.
 */
double
dxf_hatch_pattern_seedpoint_get_y0
(
        DxfHatchPatternSeedPoint *point
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point->y0);
}


/*!
 * \brief Set the Y-value for a DXF \c HATCH pattern seed point.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_set_y0
(
        DxfHatchPatternSeedPoint *point,
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
        double y0
                /*!< the Y-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the pointer to the next \c HATCH pattern seed point from a
 * DXF \c HATCH pattern seed point.
 *
 * \return pointer to the next \c HATCH pattern seed point.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_get_next
(
        DxfHatchPatternSeedPoint *point
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternSeedPoint *) point->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH pattern seed point for a
 * DXF \c HATCH pattern seed point.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_set_next
(
        DxfHatchPatternSeedPoint *point,
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
        DxfHatchPatternSeedPoint *next
                /*!< a pointer to the next \c HATCH pattern seed point
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
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
        point->next = (struct DxfHatchPatternSeedPoint *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the pointer to the last \c HATCH pattern seed point from a
 * linked list of DXF \c HATCH pattern seed points.
 *
 * \return pointer to the last \c HATCH pattern seed point.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_get_last
(
        DxfHatchPatternSeedPoint *point
                /*!< a pointer to a DXF \c HATCH pattern seed point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchPatternSeedPoint *) point);
        }
        DxfHatchPatternSeedPoint *iter = (DxfHatchPatternSeedPoint *) point->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchPatternSeedPoint *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchPatternSeedPoint *) iter);
}


/* dxf_hatch_boundary_path functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPath *path = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPath);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((path = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                path = NULL;
        }
        else
        {
                memset (path, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_init
(
        DxfHatchBoundaryPath *path
                /*!< DXF hatch boundary path entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                path = dxf_hatch_boundary_path_new ();
        }
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        path->id_code = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        path->edges = NULL;
        path->polylines = NULL;
        path->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path);
}


/*!
 * \brief Write DXF output to a file for hatch boundary entities.
 *
 * Requires AutoCAD version R14 or higher.
 */
int
dxf_hatch_boundary_path_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHatchBoundaryPath *path
                /*!< Pointer to DXF Boundary paths (loops). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolyline *iter;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        for (;;)
        {
                if (path->next == NULL)
                {
                        fprintf (stderr,
                          (_("Information from %s () last boundary path encountered.\n")),
                          __FUNCTION__);
                        break;
                }
                else
                {
                        /* Test for edge type or polylines type. */
                        if (path->edges != NULL)
                        {
                                /*! \todo Write edges data. */
                        }
                        else if (path->polylines != NULL)
                        {
                                iter = dxf_hatch_boundary_path_polyline_new ();
                                iter = (DxfHatchBoundaryPathPolyline *) path->polylines;
                                for (;;)
                                {
                                        dxf_hatch_boundary_path_polyline_write
                                        (
                                                fp,
                                                iter
                                        );
                                        iter = (DxfHatchBoundaryPathPolyline *) iter->next;
                                        if (iter == NULL)
                                        {
                                                break;
                                        }
                                }
                        }
                        else
                        {
                                fprintf (stderr,
                                  (_("Error in %s () unknown boundary path type encountered.\n")),
                                  __FUNCTION__);
                                return (EXIT_FAILURE);
                        }
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path and
 * all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_free
(
        DxfHatchBoundaryPath *path
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (path->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (path->edges);
        free (path->polylines);
        free (path);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary paths and all their data fields.
 */
void
dxf_hatch_boundary_path_free_list
(
        DxfHatchBoundaryPath *hatch_boundary_paths
                /*!< pointer to the single linked list of DXF \c HATCH
                 * boundary paths. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_paths == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_paths != NULL)
        {
                DxfHatchBoundaryPath *iter = (DxfHatchBoundaryPath *) hatch_boundary_paths->next;
                dxf_hatch_boundary_path_free (hatch_boundary_paths);
                hatch_boundary_paths = (DxfHatchBoundaryPath *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_get_id_code
(
        DxfHatchBoundaryPath *path
                /*!< a pointer to a DXF \c HATCH boundary path. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (path->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_set_id_code
(
        DxfHatchBoundaryPath *path,
                /*!< a pointer to a DXF \c HATCH boundary path. */
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
        if (path == NULL)
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
        path->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path);
}


/*!
 * \brief Get the edges from a DXF \c HATCH boundary path.
 *
 * \return a pointer to the first edge.
 *
 * \warning No low level copy is made of the series of edges.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_get_edges
(
        DxfHatchBoundaryPath *path
                /*!< a pointer to a DXF \c HATCH boundary path. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (path->edges == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdge *) path->edges);
}


/*!
 * \brief Set the edges for a DXF \c HATCH boundary path.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_set_edges
(
        DxfHatchBoundaryPath *path,
                /*!< a pointer to a DXF \c HATCH boundary path. */
        DxfHatchBoundaryPathEdge *edges
                /*!< a pointer to the first edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (edges == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        path->edges = (struct DxfHatchBoundaryPathEdge *) edges;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path);
}


/*!
 * \brief Get the polylines from a DXF \c HATCH boundary path.
 *
 * \return a pointer to the first plyline.
 *
 * \warning No low level copy is made of the series of polylines.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_get_polylines
(
        DxfHatchBoundaryPath *path
                /*!< a pointer to a DXF \c HATCH boundary path. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (path->polylines == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathPolyline *) path->polylines);
}


/*!
 * \brief Set the plylines for a DXF \c HATCH boundary path.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_set_polylines
(
        DxfHatchBoundaryPath *path,
                /*!< a pointer to a DXF \c HATCH boundary path. */
        DxfHatchBoundaryPathPolyline *polylines
                /*!< a pointer to the first polyline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polylines == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        path->polylines = (struct DxfHatchBoundaryPathPolyline *) polylines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path from a DXF
 * \c HATCH boundary path.
 *
 * \return pointer to the next \c HATCH boundary path.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_get_next
(
        DxfHatchBoundaryPath *path
                /*!< a pointer to a DXF \c HATCH boundary path. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (path->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPath *) path->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path for a DXF
 * \c HATCH boundary path.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_set_next
(
        DxfHatchBoundaryPath *path,
                /*!< a pointer to a DXF \c HATCH boundary path. */
        DxfHatchBoundaryPath *next
                /*!< a pointer to the next \c HATCH boundary path for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
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
        path->next = (struct DxfHatchBoundaryPath *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (path);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path from a
 * linked list of DXF \c HATCH boundary paths.
 *
 * \return pointer to the last \c HATCH boundary path.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_get_last
(
        DxfHatchBoundaryPath *path
                /*!< a pointer to a DXF \c HATCH boundary path. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (path == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (path->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPath *) path);
        }
        DxfHatchBoundaryPath *iter = (DxfHatchBoundaryPath *) path->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPath *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPath *) iter);
}


/* dxf_hatch_boundary_path_polyline functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path polyline.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolyline *polyline = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathPolyline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((polyline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                polyline = NULL;
        }
        else
        {
                memset (polyline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path polyline entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_init
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< DXF hatch boundary path polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                polyline = dxf_hatch_boundary_path_polyline_new ();
        }
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        polyline->id_code = 0;
        polyline->is_closed = 0;
        polyline->number_of_vertices = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        polyline->vertices = NULL;
        polyline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Write DXF output to a file for a hatch boundary path polyline.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_polyline_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfHatchBoundaryPathPolyline *polyline
                /*!< DXF hatch boundary path polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolylineVertex *iter;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        fprintf (fp->fp, " 73\n%hd\n", polyline->is_closed);
        fprintf (fp->fp, " 93\n%" PRIi32 "\n", polyline->number_of_vertices);
        /* draw hatch boundary vertices. */
        iter = dxf_hatch_boundary_path_polyline_vertex_new ();
        iter = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
        for (;;)
        {
                dxf_hatch_boundary_path_polyline_vertex_write
                (
                        fp,
                        iter
                );
                iter = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                if (iter == NULL)
                {
                        break;
                }
        }
        /* test for closed polyline: close with first vertex. */
        if (polyline->is_closed)
        {
                dxf_hatch_boundary_path_polyline_vertex_write
                (
                        fp,
                        (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices
                );
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * polyline and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_polyline_free
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (polyline->vertices);
        free (polyline);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary path polylines and all their data fields.
 */
void
dxf_hatch_boundary_path_polyline_free_list
(
        DxfHatchBoundaryPathPolyline *polylines
                /*!< pointer to the single linked list of DXF \c HATCH
                 * boundary path polylines. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polylines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (polylines != NULL)
        {
                DxfHatchBoundaryPathPolyline *iter = (DxfHatchBoundaryPathPolyline *) polylines->next;
                dxf_hatch_boundary_path_polyline_free (polylines);
                polylines = (DxfHatchBoundaryPathPolyline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path polyline.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_polyline_get_id_code
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path polyline.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_set_id_code
(
        DxfHatchBoundaryPathPolyline *polyline,
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
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
        if (polyline == NULL)
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
        polyline->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c is_closed flag value from a DXF \c HATCH boundary
 * path polyline.
 *
 * \return \c is_closed flag value.
 */
int16_t
dxf_hatch_boundary_path_polyline_get_is_closed
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->is_closed < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (polyline->is_closed > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->is_closed);
}


/*!
 * \brief Set the \c is_closed flag value for a DXF \c HATCH boundary
 * path polyline.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_set_is_closed
(
        DxfHatchBoundaryPathPolyline *polyline,
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
        int16_t is_closed
                /*!< \c is_closed flag value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (is_closed < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (is_closed > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->is_closed = is_closed;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c number_of_vertices value from a DXF \c HATCH
 * boundary path polyline.
 *
 * \return \c number_of_vertices value.
 */
int32_t
dxf_hatch_boundary_path_polyline_get_number_of_vertices
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->number_of_vertices < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->number_of_vertices);
}


/*!
 * \brief Set the \c number_of_vertices value for a DXF \c HATCH
 * boundary path polyline.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_set_number_of_vertices
(
        DxfHatchBoundaryPathPolyline *polyline,
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
        int32_t number_of_vertices
                /*!< \c number_of_vertices value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_vertices < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->number_of_vertices = number_of_vertices;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the vertices from a DXF \c HATCH boundary path polyline.
 *
 * \return a pointer to the first vertex.
 *
 * \warning No low level copy is made of the series of vertices.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_get_vertices
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * polyline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->vertices == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathPolylineVertex *) polyline->vertices);
}


/*!
 * \brief Set the vertices for a DXF \c HATCH boundary path polyline.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_set_vertices
(
        DxfHatchBoundaryPathPolyline *polyline,
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
        DxfHatchBoundaryPathPolylineVertex *vertices
                /*!< a pointer to the first vertex. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertices == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->vertices = (struct DxfHatchBoundaryPathPolylineVertex *) vertices;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Test if a hatch boundary polyline is closed and add the missing
 * vertex.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_polyline_close_polyline
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< DXF hatch boundary path polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () invalid pointer to polyline (NULL).\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->is_closed == 0)
        {
                /* iterate over all vertices until the last vertex,
                 * append a new vertex with values of the first vertex,
                 * and set the "is_closed" member to 1. */
                DxfHatchBoundaryPathPolylineVertex *first;
                DxfHatchBoundaryPathPolylineVertex *iter;
                DxfHatchBoundaryPathPolylineVertex *next;
                first = dxf_hatch_boundary_path_polyline_vertex_new ();
                iter = dxf_hatch_boundary_path_polyline_vertex_new ();
                next = dxf_hatch_boundary_path_polyline_vertex_new ();
                first = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
                iter = first;
                for (;;)
                {
                        if (iter->next == NULL)
                        {
                                next = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                                break;
                        }
                        iter = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                }
                first = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
                 /*! \todo How do we know what's the last id_code ?
                  * This should be taken from a global id_code counter. */
                next->id_code = iter->id_code + 1;
                next->x0 = first->x0;
                next->y0 = first->y0;
                next->next = NULL;
                iter->next = (struct DxfHatchBoundaryPathPolylineVertex *) next;
                polyline->is_closed = 1;
        }
        else
        {
                /* iterate over all vertices until the last vertex,
                 * test if the values of the last are identical with the
                 * first vertex, if not: append a vertex with values of
                 * the first vertex. */
                DxfHatchBoundaryPathPolylineVertex *first;
                DxfHatchBoundaryPathPolylineVertex *iter;
                DxfHatchBoundaryPathPolylineVertex *next;
                first = dxf_hatch_boundary_path_polyline_vertex_new ();
                iter = dxf_hatch_boundary_path_polyline_vertex_new ();
                next = dxf_hatch_boundary_path_polyline_vertex_new ();
                first = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
                iter = first;
                for (;;)
                {
                        if (iter->next == NULL)
                        {
                                next = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                                break;
                        }
                        iter = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                }
                first = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
                if (iter->x0 != first->x0 && iter->y0 != first->y0)
                {
                        /* the first vertex coordinates are identical to
                         * the last vertex coordinates: do nothing and
                         * leave. */
                }
                else
                {
                        /*! \todo How do we know what's the last id_code ?
                         * This should be taken from a global id_code counter. */
                        next->id_code = iter->id_code + 1;
                        next->x0 = (double) first->x0;
                        next->y0 = first->y0;
                        next->next = NULL;
                        iter->next = (struct DxfHatchBoundaryPathPolylineVertex *) next;
                }
                /*! \todo add code here ! */
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Compute if the coordinates of a point \c p lie inside or
 * outside a DXF hatch boundary path polyline \c polyline entity.
 *
 * \author Paul Bourke <http://www.paulbourke.net/geometry/insidepoly/>\n
 * Adapted for libDXF by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * A solution by Philippe Reverdy is to compute the sum of the angles
 * made between the test point and each pair of points making up the
 * polygon.\n
 * If this sum is (\f$ 2\pi \f$) then the point is an interior point,
 * if 0 then the point is an exterior point.\n
 * This also works for polygons with holes given the polygon is defined
 * with a path made up of coincident edges into and out of the hole as
 * is common practice in many CAD packages.\n
 *
 * \note For most of the "point-in-polygon" algorithms there is a
 * pathological case if the point being queries lies exactly on a
 * vertex.\n
 * The easiest way to cope with this is to test that as a separate
 * process and make your own decision as to whether you want to consider
 * them inside or outside.
 *
 * \note It is assumed that the polygon is simple (does not intersect
 * itself).
 *
 * \return \c INSIDE if an interior point, \c OUTSIDE if an exterior
 * point, or \c EXIT_FAILURE if an error occurred.
 */
int
dxf_hatch_boundary_path_polyline_point_inside_polyline
(
        DxfHatchBoundaryPathPolyline *polyline,
                /*!< DXF hatch boundary path polyline entity. */
        DxfPoint *point
                /*!< The point to be tested for. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->is_closed != 1)
        {
                fprintf (stderr,
                  (_("Error in %s () polyline is not a closed polygon.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        DxfHatchBoundaryPathPolylineVertex *p0;
        DxfHatchBoundaryPathPolylineVertex *p1;
        DxfHatchBoundaryPathPolylineVertex *iter;
        DxfHatchBoundaryPathPolylineVertex *next;
        double angle;
        p0 = dxf_hatch_boundary_path_polyline_vertex_new ();
        p1 = dxf_hatch_boundary_path_polyline_vertex_new ();
        iter = dxf_hatch_boundary_path_polyline_vertex_new ();
        next = dxf_hatch_boundary_path_polyline_vertex_new ();
        iter = (DxfHatchBoundaryPathPolylineVertex *) polyline->vertices;
        next = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
        angle = 0;
        for (;;)
        {
                if (next == NULL)
                {
                        /* iter is the last vertex, no use to continue. */
                        break;
                }
                next = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
                p0->x0 = iter->x0 - point->x0;
                p0->y0 = iter->y0 - point->y0;
                p1->x0 = next->x0 - point->x0;
                p1->y0 = next->y0 - point->y0;
                angle += dxf_hatch_boundary_path_polyline_vertex_angle (iter, next);
                iter = next;
        }
        /* clean up. */
        dxf_hatch_boundary_path_polyline_vertex_free (p0);
        dxf_hatch_boundary_path_polyline_vertex_free (p1);
        if (abs (angle) < M_PI)
                return (OUTSIDE);
        else
                return (INSIDE);
#if DEBUG
        DXF_DEBUG_END
#endif
        /*! \todo This is a dead code path. */
        return (EXIT_FAILURE);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path polyline
 * from a DXF \c HATCH boundary path polyline.
 *
 * \return pointer to the next \c HATCH boundary path polyline.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_get_next
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathPolyline *) polyline->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path polyline
 * for a DXF \c HATCH boundary path polyline.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_set_next
(
        DxfHatchBoundaryPathPolyline *polyline,
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
        DxfHatchBoundaryPathPolyline *next
                /*!< a pointer to the next \c HATCH boundary path
                 * polyline for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
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
        polyline->next = (struct DxfHatchBoundaryPathPolyline *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path polyline
 * from a linked list of DXF \c HATCH boundary path polylines.
 *
 * \return pointer to the last \c HATCH boundary path polyline.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_get_last
(
        DxfHatchBoundaryPathPolyline *polyline
                /*!< a pointer to a DXF \c HATCH boundary path polyline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (polyline->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPathPolyline *) polyline);
        }
        DxfHatchBoundaryPathPolyline *iter = (DxfHatchBoundaryPathPolyline *) polyline->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPathPolyline *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathPolyline *) iter);
}


/* dxf_hatch_boundary_path_polyline_vertex functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path polyline
 * vertex.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathPolylineVertex *vertex = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathPolylineVertex);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((vertex = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                vertex = NULL;
        }
        else
        {
                memset (vertex, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path polyline vertex entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_init
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< DXF hatch boundary path polyline vertex entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                vertex = dxf_hatch_boundary_path_polyline_vertex_new ();
        }
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Initialize new structs for members. */
        vertex->id_code = 0;
        vertex->x0 = 0.0;
        vertex->y0 = 0.0;
        vertex->bulge = 0.0;
        vertex->has_bulge = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        vertex->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Write DXF output to a file for a hatch boundary polyline
 * vertex.
 */
int
dxf_hatch_boundary_path_polyline_vertex_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< DXF hatch boundary path polyline vertex entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        fprintf (fp->fp, " 10\n%f\n", vertex->x0);
        fprintf (fp->fp, " 20\n%f\n", vertex->y0);
        fprintf (fp->fp, " 72\n%hd\n", vertex->has_bulge);
        if (vertex->has_bulge)
        {
                fprintf (fp->fp, " 42\n%f\n", vertex->bulge);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * polyline vertex and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_polyline_vertex_free
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path polyline vertex entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (vertex);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary path polyline vertices and all their data fields.
 */
void
dxf_hatch_boundary_path_polyline_vertex_free_list
(
        DxfHatchBoundaryPathPolylineVertex *hatch_boundary_path_polyline_vertices
                /*!< pointer to the single linked list of DXF \c HATCH
                 * boundary path polyline vertices. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_polyline_vertices == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_polyline_vertices != NULL)
        {
                DxfHatchBoundaryPathPolylineVertex *iter = (DxfHatchBoundaryPathPolylineVertex *) hatch_boundary_path_polyline_vertices->next;
                dxf_hatch_boundary_path_polyline_vertex_free (hatch_boundary_path_polyline_vertices);
                hatch_boundary_path_polyline_vertices = (DxfHatchBoundaryPathPolylineVertex *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path polyline
 * vertex.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_polyline_vertex_get_id_code
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path polyline
 * vertex.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_set_id_code
(
        DxfHatchBoundaryPathPolylineVertex *vertex,
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
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
        if (vertex == NULL)
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
        vertex->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the X-value of the coordinate from a DXF \c HATCH boundary
 * path polyline vertex.
 *
 * \return x0.
 */
double
dxf_hatch_boundary_path_polyline_vertex_get_x0
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->x0);
}


/*!
 * \brief Set the X-value of the coordinate for a DXF \c HATCH boundary
 * path polyline vertex.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_set_x0
(
        DxfHatchBoundaryPathPolylineVertex *vertex,
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
        double x0
                /*!< the X-value of the coordinate to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the Y-value of the coordinate from a DXF \c HATCH boundary
 * path polyline vertex.
 *
 * \return y0.
 */
double
dxf_hatch_boundary_path_polyline_vertex_get_y0
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->y0);
}


/*!
 * \brief Set the Y-value of the coordinate for a DXF \c HATCH boundary
 * path polyline vertex.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_set_y0
(
        DxfHatchBoundaryPathPolylineVertex *vertex,
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
        double y0
                /*!< the Y-value of the coordinate to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the bulge from a DXF \c HATCH boundary path polyline
 * vertex.
 *
 * \return bulge.
 */
double
dxf_hatch_boundary_path_polyline_vertex_get_bulge
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->bulge);
}


/*!
 * \brief Set the bulge value for a DXF \c HATCH boundary path polyline
 * vertex.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_set_bulge
(
        DxfHatchBoundaryPathPolylineVertex *vertex,
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
        double bulge
                /*!< the bulge value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        vertex->bulge = bulge;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the has_bulge flag value from a DXF \c HATCH boundary path
 * polyline vertex.
 *
 * \return has_bulge flag value.
 */
int16_t
dxf_hatch_boundary_path_polyline_vertex_get_has_bulge
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex->has_bulge < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (vertex->has_bulge > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex->has_bulge);
}


/*!
 * \brief Set the \c has_bulge flag value for a DXF \c HATCH boundary
 * path polyline vertex.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_set_has_bulge
(
        DxfHatchBoundaryPathPolylineVertex *vertex,
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
        int16_t has_bulge
                /*!< has_bulge flag value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (has_bulge < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (has_bulge > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        vertex->has_bulge = has_bulge;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Return the angle between two vertices on a plane (2D).
 *
 * The angle is from \c vertex_0 to \c vertex_1, positive is
 * counterclockwise (CCW).
 *
 * \return The angle value is in the range (\f$ -\pi \cdots \pi \f$) in
 * radians.
 */
double
dxf_hatch_boundary_path_polyline_vertex_angle
(
        DxfHatchBoundaryPathPolylineVertex *vertex_0,
                /*!< The first vertex (of the pair). */
        DxfHatchBoundaryPathPolylineVertex *vertex_1
                /*!< The second vertex (of the pair). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double x0;
        double y0;
        double x1;
        double y1;
        double dtheta;
        double theta0;
        double theta1;

        /* Do some basic checks. */
        if (vertex_0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (vertex_1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((vertex_0->x0 == vertex_1->x0)
          && (vertex_0->y0 == vertex_1->y0))
        {
                fprintf (stderr,
                  (_("Error in %s () identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        x0 = vertex_0->x0;
        y0 = vertex_0->y0;
        x1 = vertex_1->x0;
        y1 = vertex_1->y0;
        theta0 = atan2 (y0, x0);
        theta1 = atan2 (y1, x1);
        dtheta = theta1 - theta0;
        while (dtheta > M_PI)
                dtheta -= 2 * M_PI;
        while (dtheta < -M_PI)
        dtheta += 2 * M_PI;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dtheta);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path polyline
 * vertex from a DXF \c HATCH boundary path polyline vertex.
 *
 * \return pointer to the next \c HATCH boundary path polyline vertex.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_get_next
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathPolylineVertex *) vertex->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path polyline
 * vertex for a DXF \c HATCH boundary path polyline vertex.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_set_next
(
        DxfHatchBoundaryPathPolylineVertex *vertex,
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
        DxfHatchBoundaryPathPolylineVertex *next
                /*!< a pointer to the next \c HATCH boundary path
                 * polyline vertex for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
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
        vertex->next = (struct DxfHatchBoundaryPathPolylineVertex *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (vertex);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path polyline
 * vertex from a linked list of DXF \c HATCH boundary path polyline
 * vertices.
 *
 * \return pointer to the last \c HATCH boundary path polyline vertex.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_get_last
(
        DxfHatchBoundaryPathPolylineVertex *vertex
                /*!< a pointer to a DXF \c HATCH boundary path polyline
                 * vertex. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (vertex->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPathPolylineVertex *) vertex);
        }
        DxfHatchBoundaryPathPolylineVertex *iter = (DxfHatchBoundaryPathPolylineVertex *) vertex->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPathPolylineVertex *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathPolylineVertex *) iter);
}


/* dxf_hatch_boundary_path_edge functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdge *edge = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdge);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((edge = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                edge = NULL;
        }
        else
        {
                memset (edge, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_init
(
        DxfHatchBoundaryPathEdge *edge
                /*!< DXF hatch boundary path edge entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                edge = dxf_hatch_boundary_path_edge_new ();
        }
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        edge->id_code = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        edge->arcs = NULL;
        edge->ellipses = NULL;
        edge->lines = NULL;
        edge->splines = NULL;
        edge->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_free
(
        DxfHatchBoundaryPathEdge *edge
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (edge->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (edge->arcs);
        free (edge->ellipses);
        free (edge->lines);
        free (edge->splines);
        free (edge);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary path edges and all their data fields.
 */
void
dxf_hatch_boundary_path_edge_free_list
(
        DxfHatchBoundaryPathEdge *edges
                /*!< pointer to the single linked list of DXF
                 * \c HATCH boundary path edges. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edges == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (edges != NULL)
        {
                DxfHatchBoundaryPathEdge *iter = (DxfHatchBoundaryPathEdge *) edges->next;
                dxf_hatch_boundary_path_edge_free (edges);
                edges = (DxfHatchBoundaryPathEdge *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path edge.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_edge_get_id_code
(
        DxfHatchBoundaryPathEdge *edge
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (edge->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path edge.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_set_id_code
(
        DxfHatchBoundaryPathEdge *edge,
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
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
        if (edge == NULL)
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
        edge->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Get the pointer to the first arc of a linked list of arcs from
 * a DXF \c HATCH boundary path edge.
 *
 * \return pointer to the first arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_get_arcs
(
        DxfHatchBoundaryPathEdge *edge
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (edge->arcs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeArc *) edge->arcs);
}


/*!
 * \brief Set the pointer to the first arc of a linked list of arcs for
 * a DXF \c HATCH boundary path edge.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_set_arcs
(
        DxfHatchBoundaryPathEdge *edge,
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
        DxfHatchBoundaryPathEdgeArc *arcs
                /*!< first arc of a linked list of arcs for a DXF
                 * \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arcs == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        edge->arcs = (struct DxfHatchBoundaryPathEdgeArc *) arcs;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Get the pointer to the first ellipse of a linked list of
 * ellipses from a DXF \c HATCH boundary path edge.
 *
 * \return pointer to the first ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_get_ellipses
(
        DxfHatchBoundaryPathEdge *edge
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (edge->ellipses == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeEllipse *) edge->ellipses);
}


/*!
 * \brief Set the pointer to the first ellipse of a linked list of
 * ellipses for a DXF \c HATCH boundary path edge.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_set_ellipses
(
        DxfHatchBoundaryPathEdge *edge,
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
        DxfHatchBoundaryPathEdgeEllipse *ellipses
                /*!< first ellipse of a linked list of ellipses for a
                 * DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipses == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        edge->ellipses = (struct DxfHatchBoundaryPathEdgeEllipse *) ellipses;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Get the pointer to the first line of a linked list of lines
 * from a DXF \c HATCH boundary path edge.
 *
 * \return pointer to the first line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_get_lines
(
        DxfHatchBoundaryPathEdge *edge
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (edge->lines == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeLine *) edge->lines);
}


/*!
 * \brief Set the pointer to the first line of a linked list of lines
 * for a DXF \c HATCH boundary path edge.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_set_lines
(
        DxfHatchBoundaryPathEdge *edge,
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
        DxfHatchBoundaryPathEdgeLine *lines
                /*!< first line of a linked list of lines for a DXF
                 * \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lines == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        edge->lines = (struct DxfHatchBoundaryPathEdgeLine *) lines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Get the pointer to the first spline of a linked list of
 * splines from a DXF \c HATCH boundary path edge.
 *
 * \return pointer to the first spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_get_splines
(
        DxfHatchBoundaryPathEdge *edge
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (edge->splines == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeSpline *) edge->splines);
}


/*!
 * \brief Set the pointer to the first spline of a linked list of
 * splines for a DXF \c HATCH boundary path edge.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_set_splines
(
        DxfHatchBoundaryPathEdge *edge,
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
        DxfHatchBoundaryPathEdgeSpline *splines
                /*!< first spline of a linked list of splines for a
                 * DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (splines == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        edge->splines = (struct DxfHatchBoundaryPathEdgeSpline *) splines;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path edge from a
 * DXF \c HATCH boundary path edge.
 *
 * \return pointer to the next \c HATCH boundary path edge.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_get_next
(
        DxfHatchBoundaryPathEdge *edge
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (edge->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdge *) edge->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path edge for a
 * DXF \c HATCH boundary path edge.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_set_next
(
        DxfHatchBoundaryPathEdge *edge,
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
        DxfHatchBoundaryPathEdge *next
                /*!< a pointer to the next \c HATCH boundary path edge
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
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
        edge->next = (struct DxfHatchBoundaryPathEdge *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (edge);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path edge from a
 * linked list of DXF \c HATCH boundary path edge.
 *
 * \return pointer to the last \c HATCH boundary path edge.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_get_last
(
        DxfHatchBoundaryPathEdge *edge
                /*!< a pointer to a DXF \c HATCH boundary path edge. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (edge == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (edge->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPathEdge *) edge);
        }
        DxfHatchBoundaryPathEdge *iter = (DxfHatchBoundaryPathEdge *) edge->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPathEdge *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdge *) iter);
}


/* dxf_hatch_boundary_path_edge_arc functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge arc.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeArc *arc = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeArc);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((arc = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                arc = NULL;
        }
        else
        {
                memset (arc, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge arc entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_init
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< DXF hatch boundary path edge arc entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                arc = dxf_hatch_boundary_path_edge_arc_new ();
        }
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        arc->id_code = 0;
        arc->x0 = 0.0;
        arc->y0 = 0.0;
        arc->radius = 0.0;
        arc->start_angle = 0.0;
        arc->end_angle = 0.0;
        arc->is_ccw = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        arc->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge arc and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_arc_free
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge arc entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (arc);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary path edge arcs and all their data fields.
 */
void
dxf_hatch_boundary_path_edge_arc_free_list
(
        DxfHatchBoundaryPathEdgeArc *hatch_boundary_path_edge_arcs
                /*!< pointer to the single linked list of DXF \c HATCH
                 * boundary path edge arcs. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_arcs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_arcs != NULL)
        {
                DxfHatchBoundaryPathEdgeArc *iter = (DxfHatchBoundaryPathEdgeArc *) hatch_boundary_path_edge_arcs->next;
                dxf_hatch_boundary_path_edge_arc_free (hatch_boundary_path_edge_arcs);
                hatch_boundary_path_edge_arcs = (DxfHatchBoundaryPathEdgeArc *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path edge arc.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_edge_arc_get_id_code
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_id_code
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
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
        if (arc == NULL)
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
        arc->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the X-value of the center point coordinate from a DXF
 * \c HATCH boundary path edge arc.
 *
 * \return x0.
 */
double
dxf_hatch_boundary_path_edge_arc_get_x0
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->x0);
}


/*!
 * \brief Set the X-value of the center point coordinate for a DXF
 * \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_x0
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        double x0
                /*!< the X-value of the center point coordinate to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Y-value of the center point coordinate from a DXF
 * \c HATCH boundary path edge arc.
 *
 * \return y0.
 */
double
dxf_hatch_boundary_path_edge_arc_get_y0
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->y0);
}


/*!
 * \brief Set the Y-value of the center point coordinate for a DXF
 * \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_y0
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        double y0
                /*!< the X-value of the center point coordinate to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the center point of a DXF \c HATCH boundary path edge arc.
 *
 * \return the center point.
 */
DxfPoint *
dxf_hatch_boundary_path_edge_arc_get_center_point
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        int id_code
                /*!< Identification number for the \c DXfPoint entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = arc->x0;
        p1->y0 = arc->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Set the center point of a DXF \c HATCH boundary path edge arc.
 *
 * \return a pointer to a DXF \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_center_point
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->x0 = point->x0;
        arc->y0 = point->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the radius from a DXF \c HATCH boundary path edge arc.
 *
 * \return radius.
 */
double
dxf_hatch_boundary_path_edge_arc_get_radius
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->radius);
}


/*!
 * \brief Set the radius for a DXF \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_radius
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        double radius
                /*!< the radius to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        arc->radius = radius;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the start angle from a DXF \c HATCH boundary path edge arc.
 *
 * \return start angle.
 */
double
dxf_hatch_boundary_path_edge_arc_get_start_angle
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /*! \todo Add a test for a normalized \c start_angle.*/
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->start_angle);
}


/*!
 * \brief Set the start angle for a DXF \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_start_angle
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        double start_angle
                /*!< the start angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Add a test for a normalized \c start_angle.*/
        arc->start_angle = start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the end angle from a DXF \c HATCH boundary path edge arc.
 *
 * \return end angle.
 */
double
dxf_hatch_boundary_path_edge_arc_get_end_angle
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /*! \todo Add a test for a normalized \c end_angle.*/
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->end_angle);
}


/*!
 * \brief Set the end angle for a DXF \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_end_angle
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        double end_angle
                /*!< the end angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Add a test for a normalized \c end_angle.*/
        arc->end_angle = end_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the arc is ccw value from a DXF \c HATCH boundary path
 * edge arc.
 *
 * \return arc is ccw value.
 */
int16_t
dxf_hatch_boundary_path_edge_arc_get_is_ccw
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->is_ccw < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->is_ccw);
}


/*!
 * \brief Set the arc is ccw value for a DXF \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_is_ccw
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        int16_t is_ccw
                /*!< the arc is ccw value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (is_ccw < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        arc->is_ccw = is_ccw;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path edge arc
 * from a DXF \c HATCH boundary path edge arc.
 *
 * \return pointer to the next \c HATCH boundary path edge arc.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_get_next
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeArc *) arc->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path edge arc
 * for a DXF \c HATCH boundary path edge arc.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_set_next
(
        DxfHatchBoundaryPathEdgeArc *arc,
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
        DxfHatchBoundaryPathEdgeArc *next
                /*!< a pointer to the next \c HATCH boundary path edge
                 * arc for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->next = (struct DxfHatchBoundaryPathEdgeArc *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path edge arc
 * from a linked list of DXF \c HATCH boundary path edge arcs.
 *
 * \return pointer to the last \c HATCH boundary path edge arc.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_get_last
(
        DxfHatchBoundaryPathEdgeArc *arc
                /*!< a pointer to a DXF \c HATCH boundary path edge arc. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPathEdgeArc *) arc);
        }
        DxfHatchBoundaryPathEdgeArc *iter = (DxfHatchBoundaryPathEdgeArc *) arc->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPathEdgeArc *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeArc *) iter);
}


/* dxf_hatch_boundary_path_edge_ellipse functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge ellipse.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeEllipse *ellipse = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeEllipse);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ellipse = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                ellipse = NULL;
        }
        else
        {
                memset (ellipse, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge ellipse entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_init
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< DXF hatch boundary path edge ellipse entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ellipse = dxf_hatch_boundary_path_edge_ellipse_new ();
        }
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        ellipse->id_code = 0;
        ellipse->x0 = 0.0;
        ellipse->y0 = 0.0;
        ellipse->x1 = 0.0;
        ellipse->y1 = 0.0;
        ellipse->ratio = 0.0;
        ellipse->start_angle = 0.0;
        ellipse->end_angle = 0.0;
        ellipse->is_ccw = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        ellipse->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge ellipse and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_ellipse_free
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge ellipse entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (ellipse);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary path edge ellipses and all their data fields.
 */
void
dxf_hatch_boundary_path_edge_ellipse_free_list
(
        DxfHatchBoundaryPathEdgeEllipse *hatch_boundary_path_edge_ellipses
                /*!< pointer to the single linked list of DXF \c HATCH
                 * boundary path edge ellipses. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_ellipses == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_ellipses != NULL)
        {
                DxfHatchBoundaryPathEdgeEllipse *iter = (DxfHatchBoundaryPathEdgeEllipse *) hatch_boundary_path_edge_ellipses->next;
                dxf_hatch_boundary_path_edge_ellipse_free (hatch_boundary_path_edge_ellipses);
                hatch_boundary_path_edge_ellipses = (DxfHatchBoundaryPathEdgeEllipse *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path edge
 * ellipse.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_edge_ellipse_get_id_code
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_id_code
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
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
        if (ellipse == NULL)
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
        ellipse->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the X-value of the center point coordinate from a DXF
 * \c HATCH boundary path edge ellipse.
 *
 * \return x0.
 */
double
dxf_hatch_boundary_path_edge_ellipse_get_x0
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->x0);
}


/*!
 * \brief Set the X-value of the center point coordinate for a DXF
 * \c HATCH boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_x0
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        double x0
                /*!< the X-value of the center point coordinate to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the Y-value of the center point coordinate from a DXF
 * \c HATCH boundary path edge ellipse.
 *
 * \return y0.
 */
double
dxf_hatch_boundary_path_edge_ellipse_get_y0
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->y0);
}


/*!
 * \brief Set the Y-value of the center point coordinate for a DXF
 * \c HATCH boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_y0
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        double y0
                /*!< the Y-value of the center point coordinate to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the center point of a DXF \c HATCH boundary path edge
 * ellipse.
 *
 * \return the center point.
 */
DxfPoint *
dxf_hatch_boundary_path_edge_ellipse_get_center_point
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = ellipse->x0;
        p1->y0 = ellipse->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Set the center point of a DXF \c HATCH boundary path edge
 * ellipse.
 *
 * \return a pointer to a DXF \c HATCH boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_center_point
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->x0 = point->x0;
        ellipse->y0 = point->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the X-value of the end point coordinate coordinate of the
 * major axis from a DXF \c HATCH boundary path edge ellipse.
 *
 * \return x1.
 */
double
dxf_hatch_boundary_path_edge_ellipse_get_x1
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->x1);
}


/*!
 * \brief Set the X-value of the end point coordinate coordinate of the
 * major axis for a DXF \c HATCH boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_x1
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        double x1
                /*!< the X-value of the end point coordinate coordinate
                 * of the major axis to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->x1 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the Y-value of the end point coordinate coordinate of the
 * major axis from a DXF \c HATCH boundary path edge ellipse.
 *
 * \return y1.
 */
double
dxf_hatch_boundary_path_edge_ellipse_get_y1
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->y1);
}


/*!
 * \brief Set the Y-value of the end point coordinate coordinate of the
 * major axis for a DXF \c HATCH boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_y1
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        double y1
                /*!< the Y-value of the end point coordinate coordinate
                 * of the major axis to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ellipse->y1 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the endpoint of the major axis (relative to the center) of
 * a DXF \c HATCH boundary path edge ellipse.
 *
 * \return the end point.
 */
DxfPoint *
dxf_hatch_boundary_path_edge_ellipse_get_end_point
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = ellipse->x1;
        p1->y0 = ellipse->y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Set the endpoint of the major axis (relative to the center) of
 * a DXF \c HATCH boundary path edge ellipse.
 *
 * \return a pointer to a DXF \c HATCH boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_end_point
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->x1 = point->x0;
        ellipse->y1 = point->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the ratio of minor axis to major axis from a DXF
 * \c HATCH boundary path edge ellipse.
 *
 * \return ratio.
 */
double
dxf_hatch_boundary_path_edge_ellipse_get_ratio
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->ratio < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ellipse->ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->ratio);
}


/*!
 * \brief Set the ratio of minor axis to major axis for a DXF \c HATCH
 * boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_ratio
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        double ratio
                /*!< the ratio to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ratio < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (ratio == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        ellipse->ratio = ratio;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the start angle from a DXF \c HATCH boundary path edge
 * ellipse.
 *
 * \return start angle.
 */
double
dxf_hatch_boundary_path_edge_ellipse_get_start_angle
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /*! \todo Add a test for a normalized \c start_angle.*/
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->start_angle);
}


/*!
 * \brief Set the start angle for a DXF \c HATCH boundary path edge
 * ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_start_angle
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        double start_angle
                /*!< the start angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Add a test for a normalized \c start_angle.*/
        ellipse->start_angle = start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the end angle from a DXF \c HATCH boundary path edge
 * ellipse.
 *
 * \return end angle.
 */
double
dxf_hatch_boundary_path_edge_ellipse_get_end_angle
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /*! \todo Add a test for a normalized \c end_angle.*/
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->end_angle);
}


/*!
 * \brief Set the end angle for a DXF \c HATCH boundary path edge
 * ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_end_angle
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        double end_angle
                /*!< the end angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Add a test for a normalized \c end_angle.*/
        ellipse->end_angle = end_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the is_ccw value from a DXF \c HATCH boundary path edge
 * ellipse.
 *
 * \return is_ ccw value.
 */
int16_t
dxf_hatch_boundary_path_edge_ellipse_get_is_ccw
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ellipse->is_ccw < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse->is_ccw);
}


/*!
 * \brief Set the is_ccw value for a DXF \c HATCH boundary path edge
 * ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_is_ccw
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        int16_t is_ccw
                /*!< the is_ccw value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (is_ccw < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        ellipse->is_ccw = is_ccw;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path edge
 * ellipse from a DXF \c HATCH boundary path edge ellipse.
 *
 * \return pointer to the next \c HATCH boundary path edge ellipse.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_get_next
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeEllipse *) ellipse->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path edge
 * ellipse for a DXF \c HATCH boundary path edge ellipse.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_set_next
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
        DxfHatchBoundaryPathEdgeEllipse *next
                /*!< a pointer to the next \c HATCH boundary path edge
                 * ellipse for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
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
        ellipse->next = (struct DxfHatchBoundaryPathEdgeEllipse *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ellipse);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path edge
 * ellipse from a linked list of DXF \c HATCH boundary path edge
 * ellipse.
 *
 * \return pointer to the last \c HATCH boundary path edge ellipse.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_get_last
(
        DxfHatchBoundaryPathEdgeEllipse *ellipse
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * ellipse. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ellipse == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ellipse->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPathEdgeEllipse *) ellipse);
        }
        DxfHatchBoundaryPathEdgeEllipse *iter = (DxfHatchBoundaryPathEdgeEllipse *) ellipse->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPathEdgeEllipse *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeEllipse *) iter);
}


/* dxf_hatch_boundary_path_edge_line functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge line.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeLine *line = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeLine);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((line = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                line = NULL;
        }
        else
        {
                memset (line, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge line entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_init
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< DXF hatch boundary path edge line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                line = dxf_hatch_boundary_path_edge_line_new ();
        }
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        line->id_code = 0;
        line->x0 = 0.0;
        line->y0 = 0.0;
        line->x1 = 0.0;
        line->y1 = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        line->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge line and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_line_free
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge line entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (line);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary path edge lines and all their data fields.
 */
void
dxf_hatch_boundary_path_edge_line_free_list
(
        DxfHatchBoundaryPathEdgeLine *hatch_boundary_path_edge_lines
                /*!< pointer to the single linked list of DXF \c HATCH
                 * boundary path edge lines. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_lines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_lines != NULL)
        {
                DxfHatchBoundaryPathEdgeLine *iter = (DxfHatchBoundaryPathEdgeLine *) hatch_boundary_path_edge_lines->next;
                dxf_hatch_boundary_path_edge_line_free (hatch_boundary_path_edge_lines);
                hatch_boundary_path_edge_lines = (DxfHatchBoundaryPathEdgeLine *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path edge line.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_edge_line_get_id_code
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (line->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path edge line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_id_code
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * line. */
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
        if (line == NULL)
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
        line->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the X-value of the start point coordinate from a DXF
 * \c HATCH boundary path edge line.
 *
 * \return x0.
 */
double
dxf_hatch_boundary_path_edge_line_get_x0
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->x0);
}


/*!
 * \brief Set the X-value of the start point coordinate for a DXF
 * \c HATCH boundary path edge line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_x0
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        double x0
                /*!< the X-value of the center point coordinate to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Y-value of the start point coordinate from a DXF
 * \c HATCH boundary path edge line.
 *
 * \return y0.
 */
double
dxf_hatch_boundary_path_edge_line_get_y0
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->y0);
}


/*!
 * \brief Set the Y-value of the start point coordinate for a DXF
 * \c HATCH boundary path edge line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_y0
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        double y0
                /*!< the Y-value of the center point coordinate to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the start point of a DXF \c HATCH boundary path edge line.
 *
 * \return the start point.
 */
DxfPoint *
dxf_hatch_boundary_path_edge_line_get_start_point
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1))
        {
                fprintf (stderr,
                  (_("Error in %s () a LINE with points with identical coordinates were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = line->x0;
        p1->y0 = line->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Set the start point of a DXF \c HATCH boundary path edge line.
 *
 * \return a pointer to a DXF \c HATCH boundary path edge line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_start_point
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
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
        line->x0 = point->x0;
        line->y0 = point->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the X-value of the end point coordinate from a DXF
 * \c HATCH boundary path edge line.
 *
 * \return x1.
 */
double
dxf_hatch_boundary_path_edge_line_get_x1
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->x1);
}


/*!
 * \brief Set the X-value of the end point coordinate for a DXF
 * \c HATCH boundary path edge line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_x1
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        double x1
                /*!< the X-value of the end point coordinate to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->x1 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the Y-value of the end point coordinate from a DXF
 * \c HATCH boundary path edge line.
 *
 * \return y1.
 */
double
dxf_hatch_boundary_path_edge_line_get_y1
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line->y1);
}


/*!
 * \brief Set the Y-value of the end point coordinate for a DXF
 * \c HATCH boundary path edge line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_y1
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        double y1
                /*!< the Y-value of the end point coordinate to be set
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        line->y1 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the end point of a DXF \c HATCH boundary path edge line.
 *
 * \return the end point.
 */
DxfPoint *
dxf_hatch_boundary_path_edge_line_get_end_point
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p2 = NULL;

        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if ((line->x0 == line->x1)
          && (line->y0 == line->y1))
        {
                fprintf (stderr,
                  (_("Error in %s () a line with endpoints with identical coordinates was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p2 = dxf_point_init (p2);
        if (p2 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                __FUNCTION__);
        }
        p2->id_code = id_code;
        p2->x0 = line->x1;
        p2->y0 = line->y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p2);
}


/*!
 * \brief Set the end point of a DXF \c HATCH boundary path edge line.
 *
 * \return a pointer to a DXF \c HATCH boundary path edge line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_end_point
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
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
        line->x1 = point->x0;
        line->y1 = point->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path edge line
 * from a DXF \c HATCH boundary path edge line.
 *
 * \return pointer to the next \c HATCH boundary path edge line.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_get_next
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeLine *) line->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path edge line
 * for a DXF \c HATCH boundary path edge line.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_set_next
(
        DxfHatchBoundaryPathEdgeLine *line,
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
        DxfHatchBoundaryPathEdgeLine *next
                /*!< a pointer to the next \c HATCH boundary path edge
                 * line for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
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
        line->next = (struct DxfHatchBoundaryPathEdgeLine *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (line);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path edge line
 * from a linked list of DXF \c HATCH boundary path edge line.
 *
 * \return pointer to the last \c HATCH boundary path edge line.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_get_last
(
        DxfHatchBoundaryPathEdgeLine *line
                /*!< a pointer to a DXF \c HATCH boundary path edge line. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (line == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (line->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPathEdgeLine *) line);
        }
        DxfHatchBoundaryPathEdgeLine *iter = (DxfHatchBoundaryPathEdgeLine *) line->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPathEdgeLine *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeLine *) iter);
}


/* dxf_hatch_boundary_path_edge_spline functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge spline.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeSpline *spline = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeSpline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((spline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                spline = NULL;
        }
        else
        {
                memset (spline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge spline entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_init
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< DXF hatch boundary path edge spline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spline = dxf_hatch_boundary_path_edge_spline_new ();
        }
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        spline->id_code = 0;
        spline->degree = 0;
        spline->rational = 0;
        spline->periodic = 0;
        spline->number_of_knots = 0;
        for (i = 0; i >= DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS; i++)
        {
                spline->knots[i] = 0.0;
        }
        spline->number_of_control_points = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        spline->control_points = NULL;
        spline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge spline and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_free
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge spline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (spline->control_points);
        free (spline);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary path edge splines and all their data fields.
 */
void
dxf_hatch_boundary_path_edge_spline_free_list
(
        DxfHatchBoundaryPathEdgeSpline *hatch_boundary_path_edge_splines
                /*!< pointer to the single linked list of DXF \c HATCH
                 * boundary path edge splines. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_splines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_splines != NULL)
        {
                DxfHatchBoundaryPathEdgeSpline *iter = (DxfHatchBoundaryPathEdgeSpline *) hatch_boundary_path_edge_splines->next;
                dxf_hatch_boundary_path_edge_spline_free (hatch_boundary_path_edge_splines);
                hatch_boundary_path_edge_splines = (DxfHatchBoundaryPathEdgeSpline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path spline.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_edge_spline_get_id_code
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_id_code
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
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
        if (spline == NULL)
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
        spline->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the degree from a DXF \c HATCH boundary path spline.
 *
 * \return degree.
 */
int32_t
dxf_hatch_boundary_path_edge_spline_get_degree
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->degree < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline->degree);
}


/*!
 * \brief Set the degree for a DXF \c HATCH boundary path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_degree
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
        int32_t degree
                /*!< degree. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (degree < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        spline->degree = degree;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the rational from a DXF \c HATCH boundary path spline.
 *
 * \return rational.
 */
int16_t
dxf_hatch_boundary_path_edge_spline_get_rational
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline->rational);
}


/*!
 * \brief Set the rational for a DXF \c HATCH boundary path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_rational
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
        int16_t rational
                /*!< rational. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->rational = rational;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the periodic from a DXF \c HATCH boundary path spline.
 *
 * \return periodic.
 */
int16_t
dxf_hatch_boundary_path_edge_spline_get_periodic
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline->periodic);
}


/*!
 * \brief Set the periodic for a DXF \c HATCH boundary path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_periodic
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
        int16_t periodic
                /*!< periodic. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->periodic = periodic;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the number_of_knots from a DXF \c HATCH boundary path spline.
 *
 * \return number_of_knots.
 */
int32_t
dxf_hatch_boundary_path_edge_spline_get_number_of_knots
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_knots < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline->number_of_knots);
}


/*!
 * \brief Set the number_of_knots for a DXF \c HATCH boundary path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_number_of_knots
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
        int32_t number_of_knots
                /*!< Number of knots. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_knots < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        spline->number_of_knots = number_of_knots;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the knot values from a DXF \c HATCH boundary path spline.
 *
 * \return pointer to the knot values.
 *
 * \warning No checks are performed on the returned pointer (double).
 */
int
dxf_hatch_boundary_path_edge_spline_get_knots
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
        double knots[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]
                /*!< array of knot values. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /*! \todo Do a proper implementation of spline knots. */
        for (i = 1; i < DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS; i++)
        {
                knots[i] = spline->knots[i];
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Set the knot values for a DXF \c HATCH boundary path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_knots
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
        double knots[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]
                /*!< an array containing the additional proprietary data
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /*! \todo Do a proper implementation of spline knots. */
        for (i = 1; i < DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS; i++)
        {
                if (&knots[i] ==  NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () a NULL pointer was found.\n")),
                          __FUNCTION__);
                         fprintf (stderr,
                          (_("Knots array at element %d\n")), i);
                        return (NULL);
                }
                spline->knots[i] = knots[i];
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the number_of_control_points from a DXF \c HATCH boundary path spline.
 *
 * \return number_of_control_points.
 */
int32_t
dxf_hatch_boundary_path_edge_spline_get_number_of_control_points
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_control_points < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline->number_of_control_points);
}


/*!
 * \brief Set the number_of_control_points for a DXF \c HATCH boundary
 * path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_number_of_control_points
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
        int32_t number_of_control_points
                /*!< Number of control points. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_control_points < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        spline->number_of_control_points = number_of_control_points;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the control points from a DXF \c HATCH boundary path spline.
 *
 * \return a pointer to the first control point.
 *
 * \warning No low level copy is made of the series of control points.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_get_control_points
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->control_points == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points);
}


/*!
 * \brief Set the control_points for a DXF \c HATCH boundary
 * path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_control_points
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline. */
        DxfHatchBoundaryPathEdgeSplineCp *control_points
                /*!< a pointer to the first control point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (control_points == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) control_points;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Append a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers, both the control point is
 * appended and the \c number_of_control_points is increased by 1.\n
 * \n
 * <h3>Example:</h3>
 * Start situation: a spline with 4 control points, and the control
 * point \c control_point that is to be appended.\n
 * \n
\dot
digraph start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  control_point [shape=record,label="<f0>control_point|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 * \n
 * Finished situation: a spline with the appended fifth control point,
 * the memory for control point \c control_point is freed and set to
 * \c NULL.\n
 * \n
\dot
digraph finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  appended [shape=record,label="<f0>appended|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
  cp4:f1 -> appended:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 *
 * \warning The pointer to the control point \c control_point is freed
 * and set to NULL.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_append_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control point
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so append the first control
                 * point. */
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) control_point;
        }
        else
        {
                /* iterate through all existing pointers to control
                 * points until the pointer to the last control point
                 * containing a NULL ponter in it's "next" member is
                 * found. */
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (;;)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                        if (iter->next == NULL)
                        {
                                break;
                        }
                }
                /* "iter" now contains the pointer to the last known
                 * control point, now we can write the pointer to the
                 * control point that has to be appended in the "next"
                 * member. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                iter->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
                spline->number_of_control_points++;
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (control_point);
                control_point = NULL;
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Prepend a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers the new control point is
 * prepended and the \c number_of_control_points is increased by 1.\n
 * \n
 * <h3>Example:</h3>
 * Start situation: a spline with 4 control points, and the control
 * point \c control_point that is to be prepended.\n
 * \n
\dot
digraph start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  control_point [shape=record,label="<f0>control_point|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 * \n
 * Finished situation: a spline with the prepended control point
 * totalling 5 control points, the memory for control point
 * \c control_point is freed and set to \c NULL.\n
 * \n
\dot
digraph finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  prepended [shape=record,label="<f0>prepended|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> prepended:f0 [arrowhead="open",style="dashed",color="purple"];
  prepended:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 * \warning The pointer to the control point \c control_point is freed
 * and set to NULL.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_prepend_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control point
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so prepend the first control
                 * point. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
        }
        else
        {
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = spline->control_points;
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
        }
        spline->number_of_control_points++;
        /* clean up. */
        dxf_hatch_boundary_path_edge_spline_control_point_free (control_point);
        control_point = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers, a pointer to the requested control
 * point is returned.
 *
 * \return a pointer to the requested control point.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_get_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position
                /*!< position of the DXF \c HATCH boundary path edge
                 * spline control point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeSplineCp *control_point = NULL;
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (position < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (position == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->number_of_control_points <= position)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                /* iterate through existing pointers to control points
                 * until the pointer to the requested control point is
                 * reached. */
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                control_point = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (i = 1; i <= position; i++)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                }
                /* "iter" now contains a pointer in "iter->next" to the
                 * requested control point, now we can write the pointer
                 * to control_point and return the pointer value. */
                control_point =  (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Set a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers, the control point is set at the
 * requested position.
 *
 * \warning The pointer to the control point \c cp is freed and set to
 * \c NULL.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_set_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position,
                /*!< position of the DXF \c HATCH boundary path edge
                 * spline control point entity. */
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control
                 * point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->number_of_control_points <= position)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so set at the first control
                 * point pointer. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
        }
        else
        {
                /* iterate through existing pointers to control points
                 * until the pointer to the requested control point is
                 * reached. */
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (i = 1; i <= position; i++)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                }
                /* "iter" now contains a pointer in "iter->next" to the
                 * requested control point, now we can write the pointer
                 * to control_point and return the pointer value. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                iter->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
                dxf_hatch_boundary_path_edge_spline_control_point_free (control_point);
                control_point = NULL;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Insert a control point to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers, insert the requested control
 * point at the requested position.\n
 * \n
 * <h3>Example:</h3>
 * Start situation: a spline with 4 control points, and the control
 * point \c control_point that is to be inserted.\n
 * \n
 *
\dot
digraph start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  control_point [shape=record,label="<f0>control_point|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 * \n
 * Finished situation: a spline with the inserted control point between
 * control points cp2 and cp3, totalling 5 control points, the memory
 * for control point \c control_point is freed and set to \c NULL.\n
 * \n
\dot
digraph finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  inserted [shape=record,label="<f0>inserted|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> inserted:f0 [arrowhead="open",style="dashed",color="purple"];
  inserted:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot
 *
 * \note There are two other possible and distinct scenarios, which
 * result in inserting at the first position (see "prepending"), or
 * result in inserting at the last position (see "appending").\n
 * Both these cases are addressed in this function (see comments in the
 * source code).
 *
 * \warning The pointer to the control point \c control_point is freed
 * and set to NULL.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_insert_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position,
                /*!< position of the DXF \c HATCH boundary path edge
                 * spline control point entity. */
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control
                 * point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_control_points <= position)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so insert a copy of "cp" at
                 * the first control point pointer. */
                DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                new->id_code = control_point->id_code;
                new->x0 = control_point->x0;
                new->y0 = control_point->y0;
                new->weight = control_point->weight;
                new->next = NULL;
                spline->control_points = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
        }
        else
        {
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                DxfHatchBoundaryPathEdgeSplineCp *temp = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                temp = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                /* iterate through existing pointers to control points
                 * until the pointer to the requested control point is
                 * reached. */
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (i = 2; i <= position; i++)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                }
                /* "iter" now contains a pointer (in "iter->next") to
                 * the control point with the requested position.
                 * first we have to get a pointer to the next control
                 * point "downward" (if any) of the position of the
                 * requested control point and store this one in a
                 * temporary variable. */
                temp = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                if (temp == NULL)
                {
                        /* "iter" points to the last control point, just
                         * append a copy of "cp". */
                        DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                        new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                        new->id_code = control_point->id_code;
                        new->x0 = control_point->x0;
                        new->y0 = control_point->y0;
                        new->weight = control_point->weight;
                        new->next = NULL;
                        iter->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) new;
                }
                else
                {
                        DxfHatchBoundaryPathEdgeSplineCp *new = NULL;
                        new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                        new->id_code = control_point->id_code;
                        new->x0 = control_point->x0;
                        new->y0 = control_point->y0;
                        new->weight = control_point->weight;
                        /* the next step is to connect the "downward list" to
                         * the to be inserted "control_point->next". */
                        new->next = temp->next;
                        /* the final step is to connect the "upward list" to
                         * the to be inserted control point. */
                        temp =  new;
                }
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (control_point);
                control_point = NULL;
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Remove a control point from a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for \c NULL pointers remove the requested control
 * point.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_remove_control_point
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position
                /*!< position of the DXF \c HATCH boundary path edge
                 * spline control point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position >= DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_control_points <= position)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so there is no control point to
                 * remove. */
                fprintf (stderr,
                  (_("Error in %s () spline contins no control points.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        else
        {
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                DxfHatchBoundaryPathEdgeSplineCp *temp = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                temp = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                /* iterate through existing pointers to control points
                 * until the pointer to the requested control point is
                 * reached. */
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                for (i = 0; i <= (position - 1); i++)
                {
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                        /* "iter" now contains a pointer to the control point
                         * prior to the requested position (the requested
                         * pointer is in "iter->next"). */
                }
                /* first we have to get a pointer to the next control
                 * point in the "downward list" after the  position
                 * of the requested control point and store this one in
                 * a temporary variable. */
                temp = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                /* the next step is to connect the "downward list" to
                 * the the contol point before the requested control
                 * point (the pointer to the last control point in the
                 * "upward list" is in "iter"). */
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) temp->next;
                /* clean up. */
                dxf_hatch_boundary_path_edge_spline_control_point_free (iter);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Copy control points from a \c HATCH boundary path edge spline
 * entity into a new sinle linked list of control points.
 *
 * After testing for \c NULL pointers and size of the allocated memory,
 * a new single linked list of control points (destination) is setup by
 * copying the member values from the control points from the spline
 * (source).\n
 * For each control point in the destination list new memory is
 * allocated.\n
 * \n
 * <h3>Example:</h3>
 * Start situation: a spline with 4 control points, and the control
 * point \c control_points.\n
 * \n

\dot
digraph dxf_hatch_boundary_path_edge_spline_copy_control_points__spline_start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot

\dot
digraph dxf_hatch_boundary_path_edge_spline_copy_control_points__control_points_start
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  control_points [shape=record,label="<f0>control_points|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
}
\enddot

 * \n
 * Finished situation: the unchanged \c spline with 4 control points,
 * and a list of control points starting at \c control_points.\n
 * \n

\dot
digraph dxf_hatch_boundary_path_edge_spline_copy_control_points__spline_finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  spline [shape=record,label="<fo>spline\n|{id_code}|{degree}|{rational}|{periodic}|{number_of_knots}|{knots\[\]}|{number_of_control_points}|{<f1>control_points}"];
  cp1 [shape=record, label="<f0>cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp2 [shape=record,label="<f0>cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp3 [shape=record,label="<f0>cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  cp4 [shape=record,label="<f0>cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  spline:f1 -> cp1:f0 [arrowhead="open",style="dashed",color="purple"];
  cp1:f1 -> cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  cp2:f1 -> cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  cp3:f1 -> cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot

\dot
digraph dxf_hatch_boundary_path_edge_spline_copy_control_points__controlpoints_finish
{
  nodesep=.05;
  size = "7.5,7.5";
  rankdir=LR;
  node [shape=record,width=.05,height=.05];
  control_points [shape=record,label="<f0>control_points=new_cp1|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  new_cp2 [shape=record,label="<f0>new_cp2|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  new_cp3 [shape=record,label="<f0>new_cp3|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  new_cp4 [shape=record,label="<f0>new_cp4|{id_code}|{x0}|{y0}|{weight}|{<f1>next}"];
  control_points:f1 -> new_cp2:f0 [arrowhead="open",style="dashed",color="purple"];
  new_cp2:f1 -> new_cp3:f0 [arrowhead="open",style="dashed",color="purple"];
  new_cp3:f1 -> new_cp4:f0 [arrowhead="open",style="dashed",color="purple"];
}
\enddot

 * \todo code needs to be checked !
 *
 \return a pointer to the first of the requested control points,
 * \c NULL if no control point was found.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_copy_control_points
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< DXF \c HATCH boundary path edge spline entity
                 * (source). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeSplineCp *control_point = NULL;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sizeof (spline) < sizeof (DxfHatchBoundaryPathEdgeSpline))
        {
                spline = realloc (spline, sizeof (DxfHatchBoundaryPathEdgeSpline));
        }
        if (spline->control_points == NULL)
        {
                /* no control points yet, so there is no control point
                 * to copy. */
                fprintf (stderr,
                  (_("Error in %s () spline contains no control points.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                /* iterate through all existing pointers to control
                 * points until the pointer to the last control point
                 * containing a NULL pointer in it's "next" member is
                 * found. */
                DxfHatchBoundaryPathEdgeSplineCp *iter = NULL;
                DxfHatchBoundaryPathEdgeSplineCp *iter_new = NULL;
                iter = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) spline->control_points;
                iter_new = dxf_hatch_boundary_path_edge_spline_control_point_new ();
                control_point = iter_new;
                for (;;)
                {
                        /* copy member contents into new control point. */
                        iter_new->id_code = iter->id_code;
                        iter_new->x0 = iter->x0;
                        iter_new->y0 = iter->y0;
                        iter_new->weight = iter->weight;
                        if (iter->next == NULL)
                        {
                                /* the last control point of the spline
                                 * is reached. */
                                iter_new->next = NULL;
                                break;
                        }
                        else
                        {
                                /* create a new control point in the list. */
                                iter_new->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) dxf_hatch_boundary_path_edge_spline_control_point_new ();
                        }
                        /* set both iterators to the next control point
                         * in their list. */
                        iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
                        iter_new = (DxfHatchBoundaryPathEdgeSplineCp *) iter_new->next;
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Append a knot value to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow,
 * both the knot value is appended and the \c number_of_knots is
 * increased by 1.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_append_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        double knot_value
                /*!< knot value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((spline->number_of_knots + 1) > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (("Error in %s () a array pointer overflow occurred.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        spline->knots[spline->number_of_knots + 1] = knot_value;
        spline->number_of_knots++;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Prepend a knot value to a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, all
 * the \c knots[] values are shifted one position up, the knot value is
 * prepended and the \c number_of_knots is increased by 1.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_prepend_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        double knot_value
                /*!< knot value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((spline->number_of_knots + 1) > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = spline->number_of_knots; i > 0; i--)
        {
                spline->knots[i + 1] = spline->knots[i];
        }
        spline->knots[0] = knot_value;
        spline->number_of_knots++;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get a knot value from a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, the
 * desired knot value at \c position is returned.
 *
 * \return the knot value.
 */
double
dxf_hatch_boundary_path_edge_spline_get_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position
                /*!< position in the array of knot values [0 .. DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double knot_value;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero  was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in  %s () received a position greater than DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        knot_value = spline->knots[position];
#if DEBUG
        DXF_DEBUG_END
#endif
        return (knot_value);
}


/*!
 * \brief Set a knot value to a \c HATCH boundary path edge spline entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, the
 * desired knot value at \c position is set.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_set_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position,
                /*!< position in the array of knot values [0 .. DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]. */
        double knot_value
                /*!< knot value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () received a position greater than DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        spline->knots[position] = knot_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Insert a knot value into a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, all
 * the knot values upwards of \c knots[\c position] are shifted one
 * position,  the knot value is inserted at \c knots[\c position] and
 * the  \c number_of_knots is increased by 1.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_insert_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position,
                /*!< position in the array of knot values [0 .. DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]. */
        double knot_value
                /*!< knot value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((spline->number_of_knots + 1) > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position >= DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = spline->number_of_knots; i <= position; i--)
        {
                spline->knots[i + 1] = spline->knots[i];
        }
        spline->knots[position] = knot_value;
        spline->number_of_knots++;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Remove a knot value from a \c HATCH boundary path edge spline
 * entity.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, all
 * the knot values upwards of \c knots[\c position] are shifted one
 * position down, and the \c number_of_knots is decreased by 1.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_remove_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity. */
        int position
                /*!< position in the array of knot values [0 .. DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_knots > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if ((spline->number_of_knots - 1) < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer underflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (position >= DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = position; i >= spline->number_of_knots; i++)
        {
                spline->knots[i] = spline->knots[i + 1];
        }
        spline->number_of_knots--;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Copy knot values from a \c HATCH boundary path edge spline
 * entity into an array.
 *
 * After testing for a \c NULL pointer or an array pointer overflow, all
 * the knot values from \c spline (source) are copied into an array
 * \c knot_values (destination).
 *
 * \warning Make sure enough memory is allocated for the destination
 * array.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_copy_knot_values
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< DXF \c HATCH boundary path edge spline entity (source). */
        double *knot_values[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]
                /*!< Array of knot values (destination). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spline->number_of_knots > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = 0; i < spline->number_of_knots; i++)
        {
                *knot_values[i] = spline->knots[i];
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path edge spline
 * entity from a DXF \c HATCH boundary path edge spline entity.
 *
 * \return pointer to the next \c HATCH boundary path edge spline entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_get_next
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path edge spline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeSpline *) spline->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path spline for
 * a DXF \c HATCH boundary path spline.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_set_next
(
        DxfHatchBoundaryPathEdgeSpline *spline,
                /*!< a pointer to a DXF \c HATCH boundary path spline. */
        DxfHatchBoundaryPathEdgeSpline *next
                /*!< a pointer to the next \c HATCH boundary path spline for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
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
        spline->next = (struct DxfHatchBoundaryPathEdgeSpline *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spline);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path spline from
 * a linked list of DXF \c HATCH boundary path splines.
 *
 * \return pointer to the last \c HATCH boundary path spline.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_get_last
(
        DxfHatchBoundaryPathEdgeSpline *spline
                /*!< a pointer to a DXF \c HATCH boundary path spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPathEdgeSpline *) spline);
        }
        DxfHatchBoundaryPathEdgeSpline *iter = (DxfHatchBoundaryPathEdgeSpline *) spline->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPathEdgeSpline *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeSpline *) iter);
}


/* dxf_hatch_boundary_path_edge_splie_control_point functions. */

/*!
 * \brief Allocate memory for a DXF \c HATCH boundary path edge spline
 * control point.
 *
 * Fill the memory contents with zeros.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_control_point_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHatchBoundaryPathEdgeSplineCp *control_point = NULL;
        size_t size;

        size = sizeof (DxfHatchBoundaryPathEdgeSplineCp);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((control_point = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                control_point = NULL;
        }
        else
        {
                memset (control_point, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HATCH
 * boundary path edge spline control point entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_control_point_init
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF hatch boundary path edge spline control point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                control_point = dxf_hatch_boundary_path_edge_spline_control_point_new ();
        }
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        control_point->id_code = 0;
        control_point->x0 = 0.0;
        control_point->y0 = 0.0;
        control_point->weight = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        control_point->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Free the allocated memory for a DXF \c HATCH boundary path
 * edge spline control point and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_hatch_boundary_path_edge_spline_control_point_free
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< Pointer to the memory occupied by the DXF \c HATCH
                 * boundary path edge spline control point entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (control_point);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c HATCH boundary path edge spline control points and all their data
 * fields.
 */
void
dxf_hatch_boundary_path_edge_spline_control_point_free_list
(
        DxfHatchBoundaryPathEdgeSplineCp *hatch_boundary_path_edge_spline_control_points
                /*!< pointer to the single linked list of DXF \c HATCH
                 * boundary path edge spline control points. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (hatch_boundary_path_edge_spline_control_points == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (hatch_boundary_path_edge_spline_control_points != NULL)
        {
                DxfHatchBoundaryPathEdgeSplineCp *iter = (DxfHatchBoundaryPathEdgeSplineCp *) hatch_boundary_path_edge_spline_control_points->next;
                dxf_hatch_boundary_path_edge_spline_control_point_free (hatch_boundary_path_edge_spline_control_points);
                hatch_boundary_path_edge_spline_control_points = (DxfHatchBoundaryPathEdgeSplineCp *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HATCH boundary path spline
 * control point.
 *
 * \return ID code.
 */
int
dxf_hatch_boundary_path_edge_spline_cp_get_id_code
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * splie control point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (control_point->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c HATCH boundary path spline
 * control point.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_set_id_code
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point,
                /*!< a pointer to a DXF \c HATCH boundary path spline
                 * control point. */
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
        if (control_point == NULL)
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
        control_point->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Get the X-value of the coordinate from a DXF \c HATCH boundary
 * path edge spline control point.
 *
 * \return x0.
 */
double
dxf_hatch_boundary_path_edge_spline_cp_get_x0
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline control point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point->x0);
}


/*!
 * \brief Set the X-value of the coordinate for a DXF \c HATCH boundary
 * path edge spline control point.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_set_x0
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline control point. */
        double x0
                /*!< the X-value of the coordinate to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        control_point->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Get the Y-value of the coordinate from a DXF \c HATCH boundary
 * path edge spline control point.
 *
 * \return y0.
 */
double
dxf_hatch_boundary_path_edge_spline_cp_get_y0
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline control point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point->y0);
}


/*!
 * \brief Set the Y-value of the coordinate for a DXF \c HATCH boundary
 * path edge spline control point.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_set_y0
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline control point. */
        double y0
                /*!< the Y-value of the coordinate to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        control_point->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Get the point of a DXF \c HATCH boundary path spline control
 * point.
 *
 * \return the point.
 */
DxfPoint *
dxf_hatch_boundary_path_edge_spline_cp_get_point
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point,
                /*!< a pointer to a DXF \c HATCH boundary path spline
                 * control point. */
        int id_code
                /*!< Identification number for the \c DXfPoint entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = control_point->x0;
        p1->y0 = control_point->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Set the point of a DXF \c HATCH boundary path spline control
 * point.
 *
 * \return a pointer to a DXF \c HATCH boundary path spline control
 * point.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_set_point
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point,
                /*!< a pointer to a DXF \c HATCH boundary path spline
                 * control point. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
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
        control_point->x0 = point->x0;
        control_point->y0 = point->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Get the weight value from a \c HATCH boundary path edge spline
 * control point.
 *
 * \return the weight value.
 */
double
dxf_hatch_boundary_path_edge_spline_cp_get_weight
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< DXF \c HATCH boundary path edge spline control
                 * point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point->weight);
}


/*!
 * \brief Set the weight value to a \c HATCH boundary path edge spline
 * control point.
 *
 * \return a pointer to a DXF \c HATCH boundary path spline control
 * point, or \c NULL when an error occurred.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_set_weight
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point,
                /*!< DXF \c HATCH boundary path edge spline control
                 * point. */
        double weight
                /*!< weight value. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        control_point->weight = weight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Get the pointer to the next \c HATCH boundary path edge arc
 * from a DXF \c HATCH boundary path edge arc.
 *
 * \return pointer to the next \c HATCH boundary path edge spline
 * control point.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_get_next
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline control point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (control_point->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeSplineCp *) control_point->next);
}


/*!
 * \brief Set the pointer to the next \c HATCH boundary path edge spline
 * control point for a DXF \c HATCH boundary path edge spline control
 * point.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_set_next
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point,
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline control point. */
        DxfHatchBoundaryPathEdgeSplineCp *next
                /*!< a pointer to the next \c HATCH boundary path edge
                 * spline control point for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
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
        control_point->next = (struct DxfHatchBoundaryPathEdgeSplineCp *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (control_point);
}


/*!
 * \brief Get the pointer to the last \c HATCH boundary path edge spline
 * control point from a linked list of DXF \c HATCH boundary path edge
 * spline control points.
 *
 * \return pointer to the last \c HATCH boundary path edge spline
 * control point.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_cp_get_last
(
        DxfHatchBoundaryPathEdgeSplineCp *control_point
                /*!< a pointer to a DXF \c HATCH boundary path edge
                 * spline control point. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (control_point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (control_point->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfHatchBoundaryPathEdgeSplineCp *) control_point);
        }
        DxfHatchBoundaryPathEdgeSplineCp *iter = (DxfHatchBoundaryPathEdgeSplineCp *) control_point->next;
        while (iter->next != NULL)
        {
                iter = (DxfHatchBoundaryPathEdgeSplineCp *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfHatchBoundaryPathEdgeSplineCp *) iter);
}


/* EOF */
