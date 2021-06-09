/*!
 * \file arc.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017,
 * 2018, 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF arc entity (\c ARC).
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


#include "arc.h"


/*!
 * \brief Allocate memory for a DXF \c ARC entity.
 *
 * Fill the memory contents with zeros.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_new.png
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfArc *
dxf_arc_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfArc *arc = NULL;
        size_t size;

        size = sizeof (DxfArc);
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
 * \brief Allocate memory and initialize data fields in a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_init.png
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfArc *
dxf_arc_init
(
        DxfArc *arc
                /*!< a pointer to the DXF \c ARC entity. */
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
                arc = dxf_arc_new ();
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
        arc->linetype = strdup (DXF_DEFAULT_LINETYPE);
        arc->layer = strdup (DXF_DEFAULT_LAYER);
        arc->elevation = 0.0;
        arc->thickness = 0.0;
        arc->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        arc->visibility = DXF_DEFAULT_VISIBILITY;
        arc->color = DXF_COLOR_BYLAYER;
        arc->paperspace = DXF_MODELSPACE;
        arc->graphics_data_size = 0;
        arc->shadow_mode = 0;
        arc->dictionary_owner_soft = strdup ("");
        arc->object_owner_soft = strdup ("");
        arc->material = strdup ("");
        arc->dictionary_owner_hard = strdup ("");
        arc->lineweight = 0;
        arc->plot_style_name = strdup ("");
        arc->color_value = 0;
        arc->color_name = strdup ("");
        arc->transparency = 0;
        arc->p0->x0 = 0.0;
        arc->p0->y0 = 0.0;
        arc->p0->z0 = 0.0;
        arc->radius = 0.0;
        arc->start_angle = 0.0;
        arc->end_angle = 0.0;
        arc->extr_x0 = 0.0;
        arc->extr_y0 = 0.0;
        arc->extr_z0 = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        arc->binary_graphics_data = NULL;
        arc->p0 = NULL;
        arc->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Read data from a DXF file into a DXF \c ARC entity.
 *
 * The last line read from file contained the string "ARC". \n
 * Now follows some data for the \c ARC, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c arc. \n
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_read.png
 *
 * \return a pointer to \c arc.
 */
DxfArc *
dxf_arc_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfArc *arc
                /*!< a pointer to the DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfBinaryData *iter310 = NULL;
        int iter330;

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
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                arc = dxf_arc_init (arc);
        }
        if (arc->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                arc->binary_graphics_data = dxf_binary_data_init (arc->binary_graphics_data);
                if (arc->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                arc->p0 = dxf_point_init (arc->p0);
                if (arc->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) arc->binary_graphics_data;
        iter330 = 0;
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
                        fscanf (fp->fp, "%x\n", (uint *) &arc->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, arc->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, arc->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->p0->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->radius);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * start angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->start_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->end_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &arc->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &arc->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &arc->paperspace);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &arc->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbCircle") != 0)))
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
                        fscanf (fp->fp, "%" PRIi32 "\n", &arc->graphics_data_size);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->extr_z0);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &arc->shadow_mode);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, arc->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, arc->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, arc->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, arc->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &arc->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, arc->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &arc->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, arc->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &arc->transparency);
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
        if (strcmp (arc->linetype, "") == 0)
        {
                arc->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (arc->layer, "") == 0)
        {
                arc->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Write DXF output for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_write.png
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_arc_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfArc *arc
                /*!< a pointer to the DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ARC");

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
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (arc->start_angle == arc->end_angle)
        {
                fprintf (stderr,
                  (_("Error in %s () start angle and end angle are identical for the %s entity with id-code: %x.\n")),
                    __FUNCTION__, dxf_entity_name, arc->id_code);
                fprintf (stderr,
                  (_("\tskipping %s entity.\n")), dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (arc->start_angle > 360.0)
        {
                fprintf (stderr, "Error in %s () start angle is greater than 360 degrees for the %s entity with id-code: %x.\n",
                        __FUNCTION__, dxf_entity_name, arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (arc->start_angle < 0.0)
        {
                fprintf (stderr, "Error in %s () start angle is lesser than 0 degrees for the %s entity with id-code: %x.\n",
                        __FUNCTION__, dxf_entity_name, arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (arc->end_angle > 360.0)
        {
                fprintf (stderr, "Error in %s () end angle is greater than 360 degrees for the %s entity with id-code: %x.\n",
                        __FUNCTION__, dxf_entity_name, arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (arc->end_angle < 0.0)
        {
                fprintf (stderr, "Error in %s () end angle is lesser than 0 degrees for the %s entity with id-code: %x.\n",
                        __FUNCTION__, dxf_entity_name, arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (arc->radius == 0.0)
        {
                fprintf (stderr, "Error in %s () radius value equals 0.0 for the %s entity with id-code: %x.\n",
                        __FUNCTION__, dxf_entity_name, arc->id_code);
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (arc->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, arc->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                arc->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (arc->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, arc->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                arc->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (arc->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", arc->id_code);
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
        if ((strcmp (arc->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", arc->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (arc->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", arc->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (arc->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", arc->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (arc->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", arc->layer);
        if (strcmp (arc->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", arc->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (arc->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", arc->material);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (arc->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", arc->elevation);
        }
        if (arc->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", arc->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%hd\n", arc->lineweight);
        }
        if (arc->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", arc->linetype_scale);
        }
        if (arc->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%hd\n", arc->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", arc->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", arc->graphics_data_size);
#endif
                if (arc->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) arc->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", arc->color_value);
                fprintf (fp->fp, "430\n%s\n", arc->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", arc->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", arc->plot_style_name);
                fprintf (fp->fp, "284\n%hd\n", arc->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbCircle\n");
        }
        if (arc->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", arc->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", arc->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", arc->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", arc->p0->z0);
        fprintf (fp->fp, " 40\n%f\n", arc->radius);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbArc\n");
        }
        fprintf (fp->fp, " 50\n%f\n", arc->start_angle);
        fprintf (fp->fp, " 51\n%f\n", arc->end_angle);
        if ((fp->acad_version_number >= AutoCAD_12)
                && (arc->extr_x0 != 0.0)
                && (arc->extr_y0 != 0.0)
                && (arc->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", arc->extr_x0);
                fprintf (fp->fp, "220\n%f\n", arc->extr_y0);
                fprintf (fp->fp, "230\n%f\n", arc->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ARC entity and all it's
 * data fields.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_free.png
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_arc_free
(
        DxfArc *arc
                /*!< a pointer to the memory occupied by the DXF \c ARC
                 * entity. */
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
        free (arc->linetype);
        free (arc->layer);
        dxf_binary_data_free (arc->binary_graphics_data);
        free (arc->dictionary_owner_soft);
        free (arc->object_owner_soft);
        free (arc->material);
        free (arc->dictionary_owner_hard);
        free (arc->plot_style_name);
        free (arc->color_name);
        dxf_point_free (arc->p0);
        free (arc);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c ARC entities and all their data fields.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_free_list.png
 */
void
dxf_arc_free_list
(
        DxfArc *arcs
                /*!< a pointer to the single linked list of DXF
                 * \c ARC entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (arcs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (arcs != NULL)
        {
                DxfArc *iter = (DxfArc *) arcs->next;
                dxf_arc_free (arcs);
                arcs = (DxfArc *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_id_code.png
 *
 * \return \c id_code.
 */
int
dxf_arc_get_id_code
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
 * \brief Set the \c id_code for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_id_code.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_id_code
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
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
 * \brief Get the \c linetype from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_linetype.png
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_arc_get_linetype
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_linetype.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 *
 * \note the pointer to \c linetype is not freed.
 */
DxfArc *
dxf_arc_set_linetype
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
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
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c layer from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_layer.png
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_arc_get_layer
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_layer.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_layer
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
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
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c elevation from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_elevation.png
 *
 * \return \c elevation.
 */
double
dxf_arc_get_elevation
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        return (arc->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_elevation.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_elevation
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
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
        arc->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c thickness from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_thickness.png
 *
 * \return \c thickness.
 */
double
dxf_arc_get_thickness
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->thickness == 0.0)
        {
                fprintf (stderr,
                  (_("warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_thickness.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_thickness
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
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
        arc->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_linetype_scale.png
 *
 * \return \c linetype_scale.
 */
double
dxf_arc_get_linetype_scale
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->linetype_scale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_linetype_scale.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_linetype_scale
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
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
        arc->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c visibility from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_visibility.png
 *
 * \return \c visibility.
 */
int16_t
dxf_arc_get_visibility
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_visibility.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_visibility
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
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
        arc->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c color from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_color.png
 *
 * \return color.
 */
int16_t
dxf_arc_get_color
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->color);
}


/*!
 * \brief Set the \c color for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_color.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_color
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int16_t color
                /*!< the \c color to be set for the entity. */
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
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        arc->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_paperspace.png
 *
 * \return \c paperspace flag value.
 */
int16_t
dxf_arc_get_paperspace
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_paperspace.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_paperspace
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int16_t paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
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
        arc->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_graphics_data_size.png
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_arc_get_graphics_data_size
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_graphics_data_size.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_graphics_data_size
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
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
        arc->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_shadow_mode.png
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_arc_get_shadow_mode
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_shadow_mode.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_shadow_mode
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
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
        arc->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_binary_graphics_data.png
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_arc_get_binary_graphics_data
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) arc->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_binary_graphics_data.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_binary_graphics_data
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
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
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_dictionary_owner_soft.png
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_arc_get_dictionary_owner_soft
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_dictionary_owner_soft.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_dictionary_owner_soft
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
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
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_object_owner_soft.png
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_arc_get_object_owner_soft
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_object_owner_soft.png
 */
DxfArc *
dxf_arc_set_object_owner_soft
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
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
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_material.png
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_arc_get_material
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_material.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_material
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
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
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_dictionary_owner_hard.png
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_arc_get_dictionary_owner_hard
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_dictionary_owner_hard.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_dictionary_owner_hard
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
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
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c lineweight from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_lineweight.png
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_arc_get_lineweight
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        return (arc->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_lineweight.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_lineweight
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
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
        arc->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_plot_style_name.png
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_arc_get_plot_style_name
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_plot_style_name.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_plot_style_name
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
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
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c color_value from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_color_value.png
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_arc_get_color_value
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        return (arc->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_color_value.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_color_value
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
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
        arc->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c color_name from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_color_name.png
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_arc_get_color_name
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_color_name.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_color_name
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
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
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c transparency from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_transparency.png
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_arc_get_transparency
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        return (arc->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_transparency.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_transparency
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
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
        arc->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the center point \c p0 of a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_p0.png
 *
 * \return the center point \c p0.
 */
DxfPoint *
dxf_arc_get_p0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->p0);
}


/*!
 * \brief Set the center point \c p0 of a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_p0.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_p0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfPoint *p0
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
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the X-value of the center point \c x0 of a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_x0.png
 *
 * \return the X-value of the center point \c x0.
 */
double
dxf_arc_get_x0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
                return (EXIT_FAILURE);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->p0->x0);
}


/*!
 * \brief Set the X-value of the center point \c x0 of a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_x0.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_x0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double x0
                /*!< the X-value of the center point \c x0 of a DXF
                 * \c ARC entity. */
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
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                arc->p0 = dxf_point_init (arc->p0);
                if (arc->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        arc->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Y-value of the center point \c y0 of a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_y0.png
 *
 * \return the Y-value of the center point \c y0.
 */
double
dxf_arc_get_y0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
                return (EXIT_FAILURE);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->p0->y0);
}


/*!
 * \brief Set the Y-value of the center point \c y0 of a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_y0.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_y0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double y0
                /*!< the Y-value of the center point \c y0 of a DXF
                 * \c ARC entity. */
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
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                arc->p0 = dxf_point_init (arc->p0);
                if (arc->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        arc->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Z-value of the center point \c z0 of a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_z0.png
 *
 * \return the Z-value of the center point \c z0.
 */
double
dxf_arc_get_z0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
                return (EXIT_FAILURE);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->p0->z0);
}


/*!
 * \brief Set the Z-value of the center point \c z0 of a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_z0.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_z0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double z0
                /*!< the Z-value of the center point \c z0 of a DXF
                 * \c ARC entity. */
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
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                arc->p0 = dxf_point_init (arc->p0);
                if (arc->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        arc->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c radius from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_radius.png
 *
 * \return \c radius.
 */
double
dxf_arc_get_radius
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
 * \brief Set the \c radius for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_radius.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_radius
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double radius
                /*!< the \c radius to be set for the entity. */
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
 * \brief Get the \c start_angle from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_start_angle.png
 *
 * \return \c start_angle.
 */
double
dxf_arc_get_start_angle
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        return (arc->start_angle);
}


/*!
 * \brief Set the \c start_angle for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_start_angle.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_start_angle
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double start_angle
                /*!< the \c start_angle to be set for the entity. */
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
        arc->start_angle = start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c end_angle from a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_end_angle.png
 *
 * \return \c end_angle.
 */
double
dxf_arc_get_end_angle
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        return (arc->end_angle);
}


/*!
 * \brief Set the \c end_angle for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_end_angle.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_end_angle
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double end_angle
                /*!< the \c end_angle to be set for the entity. */
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
        arc->end_angle = end_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Calculate the \c length of a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_length.png
 *
 * \return the \c length.
 */
double
dxf_arc_get_length
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
                return (EXIT_FAILURE);
        }
        if (arc->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
        if (arc->radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->radius * ((arc->end_angle - arc->start_angle) / 360.0));
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_extrusion_vector_as_point.png
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_arc_get_extrusion_vector_as_point
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (arc == NULL)
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
        point->x0 = arc->extr_x0;
        point->y0 = arc->extr_y0;
        point->z0 = arc->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_extr_x0.png
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_arc_get_extr_x0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_extr_x0.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_extr_x0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c ARC entity. */
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
        arc->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_extr_y0.png
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_arc_get_extr_y0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_extr_y0.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_extr_y0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c ARC entity. */
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
        arc->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_extr_z0.png
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_arc_get_extr_z0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_extr_z0.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_extr_z0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c ARC entity. */
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
        arc->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_extrusion_vector_from_point.png
 */
DxfArc *
dxf_arc_set_extrusion_vector_from_point
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
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
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->extr_x0 = (double) point->x0;
        arc->extr_y0 = (double) point->y0;
        arc->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Set the extrusion vector for a DXF \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_extrusion_vector.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 */
DxfArc *
dxf_arc_set_extrusion_vector
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->extr_x0 = extr_x0;
        arc->extr_y0 = extr_y0;
        arc->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the next \c ARC entity from a DXF
 * \c ARC entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_next.png
 *
 * \return pointer to the next \c ARC entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfArc *
dxf_arc_get_next
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
        return ((DxfArc *) arc->next);
}


/*!
 * \brief Set the pointer to the next \c ARC for a DXF \c ARC
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_set_next.png
 *
 * \return a pointer to \c arc when successful, or \c NULL when an error
 * occurred.
 *
 * \note the pointer to \c next is not freed.
 */
DxfArc *
dxf_arc_set_next
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfArc *next
                /*!< a pointer to the next \c ARC for the entity. */
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
        arc->next = (struct DxfArc *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the last \c ARC entity from a linked list
 * of DXF \c ARC entities.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_arc_get_last.png
 *
 * \return pointer to the last \c ARC entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfArc *
dxf_arc_get_last
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
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
                return ((DxfArc *) arc);
        }
        DxfArc *iter = (DxfArc *) arc->next;
        while (iter->next != NULL)
        {
                iter = (DxfArc *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfArc *) iter);
}


/* EOF*/
