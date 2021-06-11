/*!
 * \file region.c
 *
 * \author Copyright (C) 2013, 2014, 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF region entity (\c REGION).
 *
 * \since The region entity was introduced in DXF version R13.\n
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#include "region.h"


/*!
 * \brief Allocate memory for a \c DxfRegion.
 *
 * Fill the memory contents with zeros.
 */
DxfRegion *
dxf_region_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfRegion *region = NULL;
        size_t size;

        size = sizeof (DxfRegion);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((region = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRegion struct.\n")),
                  __FUNCTION__);
                region = NULL;
        }
        else
        {
                memset (region, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c REGION
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfRegion *
dxf_region_init
(
        DxfRegion *region
                /*!< a pointer to the DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                region = dxf_region_new ();
        }
        if (region == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfRegion struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        region->modeler_format_version_number = 0;
        region->id_code = 0;
        region->linetype = strdup (DXF_DEFAULT_LINETYPE);
        region->layer = strdup (DXF_DEFAULT_LAYER);
        region->elevation = 0.0;
        region->thickness = 0.0;
        region->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        region->visibility = DXF_DEFAULT_VISIBILITY;
        region->color = DXF_COLOR_BYLAYER;
        region->paperspace = DXF_MODELSPACE;
        region->modeler_format_version_number = 1;
        dxf_char_new (region->proprietary_data);
        region->proprietary_data = dxf_char_init (region->proprietary_data);
        region->proprietary_data->value = strdup ("");
        region->proprietary_data->length = 0;
        region->proprietary_data->next = NULL;
        dxf_char_new (region->additional_proprietary_data);
        region->additional_proprietary_data = dxf_char_init (region->additional_proprietary_data);
        region->additional_proprietary_data->value = strdup ("");
        region->additional_proprietary_data->length = 0;
        region->additional_proprietary_data->next = NULL;
        region->dictionary_owner_soft = strdup ("");
        region->dictionary_owner_hard = strdup ("");
        region->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Read data from a DXF file into a DXF \c REGION entity.
 *
 * The last line read from file contained the string "REGION". \n
 * Now follows some data for the \c REGION, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c region. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfRegion *
dxf_region_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfRegion *region
                /*!< a pointer to the DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfChar *iter1 = NULL;
        DxfChar *iter2 = NULL;

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
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                region = dxf_region_init (region);
        }
        iter1 = (DxfChar *) region->proprietary_data;
        iter2 = (DxfChar *) region->additional_proprietary_data;
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
                else if (strcmp (temp_string, "  1") == 0)
                {
                        /* Now follows a string containing proprietary
                         * data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter1->value);
                        iter1->next = (struct DxfChar *) dxf_char_init ((DxfChar *) iter1->next);
                        iter1 = (DxfChar *) iter1->next;
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter2->value);
                        iter2->next = (struct DxfChar *) dxf_char_init ((DxfChar *) iter2->next);
                        iter2 = (DxfChar *) iter2->next;
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &region->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, region->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, region->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (region->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &region->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &region->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &region->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &region->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &region->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &region->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "70") == 0))
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &region->modeler_format_version_number);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "AcDbModelerGeometry") != 0)
                        {
                                fprintf (stderr, "Error in dxf_region_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, region->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, region->dictionary_owner_hard);
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
        if (strcmp (region->linetype, "") == 0)
        {
                region->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (region->layer, "") == 0)
        {
                region->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Write DXF output to a file for a DXF \c REGION entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_region_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfRegion *region
                /*!< a pointer to the DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("REGION");
        DxfChar *iter1 = NULL;
        DxfChar *iter2 = NULL;

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
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, region->id_code);
        }
        if (strcmp (region->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, region->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                region->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (region->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, region->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                region->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (region->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", region->id_code);
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
        if ((strcmp (region->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", region->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (region->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", region->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (region->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", region->layer);
        if (strcmp (region->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", region->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (region->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", region->elevation);
        }
        if (region->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", region->color);
        }
        if (region->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", region->linetype_scale);
        }
        if (region->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", region->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbModelerGeometry\n");
        }
        if (region->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", region->thickness);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, " 70\n%d\n", region->modeler_format_version_number);
        }
        if (region->proprietary_data != NULL)
        {
                iter1 = (DxfChar*) region->proprietary_data;
                while ((iter1 != NULL) && (iter1->value != NULL))
                {
                        fprintf (fp->fp, "  1\n%s\n", iter1->value);
                        iter1 = (DxfChar*) iter1->next;
                }
        }
        else
        {
                fprintf (fp->fp, "  1\n\n");
        }
        if (region->additional_proprietary_data != NULL)
        {
                iter2 = (DxfChar*) region->additional_proprietary_data;
                while ((iter2 != NULL) && (iter2->value != NULL))
                {
                        fprintf (fp->fp, "  3\n%s\n", iter2->value);
                        iter2 = (DxfChar*) iter2->next;
                }
        }
        else
        {
                fprintf (fp->fp, "  3\n\n");
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c REGION and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_region_free
(
        DxfRegion *region
                /*!< a pointer to the memory occupied by the DXF
                 * \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (region->linetype);
        free (region->layer);
        dxf_binary_graphics_data_free_list (region->binary_graphics_data);
        free (region->dictionary_owner_soft);
        free (region->material);
        free (region->dictionary_owner_hard);
        free (region->plot_style_name);
        free (region->color_name);
        dxf_char_free_list (region->proprietary_data);
        dxf_char_free_list (region->additional_proprietary_data);
        free (region);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c REGION entities and all their data fields.
 */
void
dxf_region_free_list
(
        DxfRegion *regions
                /*!< a pointer to the single linked list of DXF
                 * \c REGION entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (regions == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (regions != NULL)
        {
                DxfRegion *iter = (DxfRegion *) regions->next;
                dxf_region_free (regions);
                regions = (DxfRegion *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c REGION entity.
 *
 * \return \c id_code.
 */
int
dxf_region_get_id_code
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_id_code
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
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
        if (region == NULL)
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
        region->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c linetype from a DXF \c REGION entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_region_get_linetype
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (region->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_linetype
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c layer from a DXF \c REGION entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_region_get_layer
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (region->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_layer
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c elevation from a DXF \c REGION entity.
 *
 * \return \c elevation.
 */
double
dxf_region_get_elevation
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_elevation
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        region->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c thickness from a DXF \c REGION entity.
 *
 * \return \c thickness.
 */
double
dxf_region_get_thickness
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_thickness
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c REGION entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_region_get_linetype_scale
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_linetype_scale
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c visibility from a DXF \c REGION entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_region_get_visibility
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_visibility
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c color from a DXF \c REGION entity.
 *
 * \return \c color.
 */
int
dxf_region_get_color
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->color);
}


/*!
 * \brief Set the \c color for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_color
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c REGION entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_region_get_paperspace
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (region->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c REGION entity.
 */
DxfRegion *
dxf_region_set_paperspace
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c REGION
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_region_get_graphics_data_size
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (region->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_graphics_data_size
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c REGION entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_region_get_shadow_mode
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_shadow_mode
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c REGION entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_region_get_binary_graphics_data
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) region->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c REGION entity.
 */
DxfRegion *
dxf_region_set_binary_graphics_data
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c REGION entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_region_get_dictionary_owner_soft
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (region->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c REGION entity.
 */
DxfRegion *
dxf_region_set_dictionary_owner_soft
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c REGION entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_region_get_material
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (region->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_material
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c REGION entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_region_get_dictionary_owner_hard
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (region->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c REGION entity.
 */
DxfRegion *
dxf_region_set_dictionary_owner_hard
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c lineweight from a DXF \c REGION entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_region_get_lineweight
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_lineweight
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        region->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c REGION entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_region_get_plot_style_name
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (region->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_plot_style_name
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c color_value from a DXF \c REGION entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_region_get_color_value
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_color_value
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        region->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c color_name from a DXF \c REGION entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_region_get_color_name
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (region->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_color_name
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c transparency from a DXF \c REGION entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_region_get_transparency
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_transparency
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        region->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c proprietary_data from a DXF \c REGION entity.
 *
 * \return \c proprietary_data when sucessful, or \c NULL when an error
 * occurred.
 */
DxfChar *
dxf_region_get_proprietary_data
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->proprietary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->proprietary_data->value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->proprietary_data);
}


/*!
 * \brief Set the \c proprietary_data for a DXF \c REGION entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_proprietary_data
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        DxfChar *proprietary_data
                /*!< a pointer containing the \c proprietary_data for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        if (proprietary_data->value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        region->proprietary_data = proprietary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c additional_proprietary_data from a DXF \c REGION
 * entity.
 *
 * \return \c additional_proprietary_data when sucessful, or \c NULL
 * when an error occurred.
 */
DxfChar *
dxf_region_get_additional_proprietary_data
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->additional_proprietary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->additional_proprietary_data->value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->additional_proprietary_data);
}


/*!
 * \brief Set the \c additional_proprietary_data for a DXF \c REGION
 * entity.
 *
 * \return a pointer to \c region when successful, or \c NULL when an
 * error occurred.
 */
DxfRegion *
dxf_region_set_additional_proprietary_data
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        DxfChar *additional_proprietary_data
                /*!< a pointer containing the
                 * \c additional_proprietary_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (additional_proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (additional_proprietary_data->value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        region->additional_proprietary_data = additional_proprietary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the \c modeler_format_version_number from a DXF \c REGION
 * entity.
 *
 * \return \c modeler_format_version_number.
 */
int
dxf_region_get_modeler_format_version_number
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (region->modeler_format_version_number != 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region->modeler_format_version_number);
}


/*!
 * \brief Set the \c modeler_format_version_number for a DXF \c REGION
 * entity.
 */
DxfRegion *
dxf_region_set_modeler_format_version_number
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        int modeler_format_version_number
                /*!< the \c modeler_format_version_number to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (modeler_format_version_number != 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
        region->modeler_format_version_number = modeler_format_version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the pointer to the next \c REGION entity from a DXF
 * \c REGION entity.
 *
 * \return pointer to the next \c REGION entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfRegion *
dxf_region_get_next
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfRegion *) region->next);
}


/*!
 * \brief Set the pointer to the next \c REGION for a DXF \c REGION
 * entity.
 */
DxfRegion *
dxf_region_set_next
(
        DxfRegion *region,
                /*!< a pointer to a DXF \c REGION entity. */
        DxfRegion *next
                /*!< a pointer to the next \c REGION for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
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
        region->next = (struct DxfRegion *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (region);
}


/*!
 * \brief Get the pointer to the last \c REGION entity from a linked list
 * of DXF \c REGION entities.
 *
 * \return pointer to the last \c REGION entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfRegion *
dxf_region_get_last
(
        DxfRegion *region
                /*!< a pointer to a DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (region->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfRegion *) region);
        }
        DxfRegion *iter = (DxfRegion *) region->next;
        while (iter->next != NULL)
        {
                iter = (DxfRegion *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfRegion *) iter);
}


/* EOF */
