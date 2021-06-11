/*!
 * \file mline.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mline entity (\c MLINE).
 *
 * \since The \c MLINE entity was introduced in DXF R13.
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


#include "mline.h"


/*!
 * \brief Allocate memory for a \c DxfMline.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMline *
dxf_mline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMline *mline = NULL;
        size_t size;

        size = sizeof (DxfMline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfMline struct.\n")),
                  __FUNCTION__);
                mline = NULL;
        }
        else
        {
                memset (mline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c MLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMline *
dxf_mline_init
(
        DxfMline *mline
                /*!< DXF mline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mline = dxf_mline_new ();
        }
        if (mline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfMline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_mline_set_id_code (mline, 0);
        dxf_mline_set_linetype (mline, strdup (DXF_DEFAULT_LINETYPE));
        dxf_mline_set_layer (mline, strdup (DXF_DEFAULT_LAYER));
        dxf_mline_set_elevation (mline, 0.0);
        dxf_mline_set_thickness (mline, 0.0);
        dxf_mline_set_linetype_scale (mline, DXF_DEFAULT_LINETYPE_SCALE);
        dxf_mline_set_visibility (mline, DXF_DEFAULT_VISIBILITY);
        dxf_mline_set_color (mline, DXF_COLOR_BYLAYER);
        dxf_mline_set_paperspace (mline, DXF_MODELSPACE);
        dxf_mline_set_graphics_data_size (mline, 0);
        dxf_mline_set_shadow_mode (mline, 0);
        dxf_mline_set_binary_graphics_data (mline, dxf_binary_graphics_data_new ());
        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) dxf_mline_get_binary_graphics_data (mline));
        dxf_mline_set_dictionary_owner_soft (mline, strdup (""));
        dxf_mline_set_material (mline, strdup (""));
        dxf_mline_set_dictionary_owner_hard (mline, strdup (""));
        dxf_mline_set_lineweight (mline, 0);
        dxf_mline_set_plot_style_name (mline, strdup (""));
        dxf_mline_set_color_value (mline, 0);
        dxf_mline_set_color_name (mline, strdup (""));
        dxf_mline_set_transparency (mline, 0);
        dxf_mline_set_style_name (mline, strdup (""));
        dxf_mline_set_p0 (mline, dxf_point_new ());
        dxf_point_init ((DxfPoint *) dxf_mline_get_p0 (mline));
        dxf_mline_set_p1 (mline, dxf_point_new ());
        dxf_point_init ((DxfPoint *) dxf_mline_get_p1 (mline));
        dxf_mline_set_p2 (mline, dxf_point_new ());
        dxf_point_init ((DxfPoint *) dxf_mline_get_p2 (mline));
        dxf_mline_set_p3 (mline, dxf_point_new ());
        dxf_point_init ((DxfPoint *) dxf_mline_get_p3 (mline));
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                mline->element_parameters[i] = 0.0;
                mline->area_fill_parameters[i] = 0.0;
        }
        dxf_mline_set_scale_factor (mline, 1.0);
        dxf_mline_set_justification (mline, 0);
        dxf_mline_set_flags (mline, 0);
        dxf_mline_set_number_of_vertices (mline, 0);
        dxf_mline_set_number_of_elements (mline, 0);
        dxf_mline_set_number_of_area_fill_parameters (mline, 0);
        dxf_mline_set_extr_x0 (mline, 0.0);
        dxf_mline_set_extr_y0 (mline, 0.0);
        dxf_mline_set_extr_z0 (mline, 1.0);
        dxf_mline_set_mlinestyle_dictionary (mline, strdup (""));
        dxf_mline_set_next (mline, NULL);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Read data from a DXF file into an \c MLINE entity.
 *
 * The last line read from file contained the string "MLINE". \n
 * Now follows some data for the \c MLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c mline.
 *
 * \return a pointer to \c mline.
 */
DxfMline *
dxf_mline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfMline *mline
                /*!< DXF mline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int j;
        int k;
        int l;
        int m;
        DxfPoint *iter_p1;
        DxfPoint *iter_p2;
        DxfPoint *iter_p3;

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
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mline = dxf_mline_init (mline);
        }
        l = 0;
        m = 0;
        i = 0; /* Number of found vertices in linked list p1. */
        iter_p1 = (DxfPoint *) mline->p1; /* Pointer to first vertex p1. */
        j = 0; /* Number of found direction vectors in linked list p2. */
        iter_p2 = (DxfPoint *) mline->p2; /* Pointer to first direction vector p2. */
        k = 0;
        iter_p3 = (DxfPoint *) mline->p3; /* Pointer to first direction vector p3. */
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
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a string of
                         * up to 32 characters with the name of the
                         * style used for this mline. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mline->style_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &mline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->p0->z0);
                }
                else if ((strcmp (temp_string, "11") == 0)
                  || (strcmp (temp_string, "21") == 0)
                  || (strcmp (temp_string, "31") == 0))
                {
                        if (strcmp (temp_string, "11") == 0)
                        {
                                /* Now follows a string containing the X-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                if (i > 0) /* Create a pointer for the next vertex. */
                                {
                                        dxf_point_init ((DxfPoint *) iter_p1->next);
                                        iter_p1 = (DxfPoint *) iter_p1->next;
                                }
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p1->x0);
                        }
                        else if (strcmp (temp_string, "21") == 0)
                        {
                                /* Now follows a string containing the Y-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p1->y0);
                        }
                        else if (strcmp (temp_string, "31") == 0)
                        {
                                /* Now follows a string containing the Z-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p1->z0);
                                i++; /* Increase the number of found vertices. */
                        }
                }
                else if ((strcmp (temp_string, "12") == 0)
                  || (strcmp (temp_string, "22") == 0)
                  || (strcmp (temp_string, "32") == 0))
                {
                        if (strcmp (temp_string, "12") == 0)
                        {
                                /* Now follows a string containing the X-value
                                 * of the Direction vector (one entry for each
                                 * vector). */
                                if (j > 0) /* Create a pointer for the next vector. */
                                {
                                        dxf_point_init ((DxfPoint *) iter_p2->next);
                                        iter_p2 = (DxfPoint *) iter_p2->next;
                                }
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p2->x0);
                        }
                        else if (strcmp (temp_string, "22") == 0)
                        {
                                /* Now follows a string containing the Y-value
                                 * of the Direction vector (one entry for each
                                 * vector). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p2->y0);
                        }
                        else if (strcmp (temp_string, "32") == 0)
                        {
                                /* Now follows a string containing the Z-value
                                 * of the Direction vector (one entry for each
                                 * vector). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p2->z0);
                                j++; /* Increase the number of found vectors. */
                        }
                }
                else if ((strcmp (temp_string, "13") == 0)
                  || (strcmp (temp_string, "23") == 0)
                  || (strcmp (temp_string, "33") == 0))
                {
                        if (strcmp (temp_string, "13") == 0)
                        {
                                /* Now follows a string containing the X-value
                                 * of the Direction vector (one entry for each
                                 * vector). */
                                if (k > 0) /* Create a pointer for the next vector. */
                                {
                                        dxf_point_init ((DxfPoint *) iter_p3->next);
                                        iter_p3 = (DxfPoint *) iter_p3->next;
                                }
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p3->x0);
                        }
                        else if (strcmp (temp_string, "23") == 0)
                        {
                                /* Now follows a string containing the Y-value
                                 * of the Direction vector (one entry for each
                                 * vector). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p3->y0);
                        }
                        else if (strcmp (temp_string, "33") == 0)
                        {
                                /* Now follows a string containing the Z-value
                                 * of the Direction vector (one entry for each
                                 * vector). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &iter_p3->z0);
                                k++; /* Increase the number of found vectors. */
                        }
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the scale
                         * factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->scale_factor);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the element
                         * parameters (repeats based on previous code 74). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->element_parameters[l]);
                        l++;
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the area fill
                         * parameters (repeats based on previous code 75). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->area_fill_parameters[m]);
                        m++;
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &mline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * justification value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->justification);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the flags
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->flags);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the number of
                         * vertices value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->number_of_vertices);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the number of
                         * elements in MLINESTYLE definition. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->number_of_elements);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the number of
                         * parameters for this element (repeats for each
                         * element in segment). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->number_of_parameters);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the number of
                         * area fill parameters for this element
                         * (repeats for each element in segment). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mline->number_of_area_fill_parameters);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbMline") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the extrusion direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the extrusion direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the extrusion direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mline->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a
                         * Pointer-handle/ID of MLINESTYLE dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mline->mlinestyle_dictionary);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mline->dictionary_owner_hard);
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
        if (strcmp (dxf_mline_get_linetype (mline), "") == 0)
        {
                dxf_mline_set_linetype (mline, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_mline_get_layer (mline), "") == 0)
        {
                dxf_mline_set_layer (mline, strdup (DXF_DEFAULT_LAYER));
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Write DXF output to fp for a mline entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occured.
 *
 * \warning This entity requires AutoCAD version R13 or higher.
 * When the \c follow_strict_version_rules flag is set to \c TRUE in the
 * \c DxfFile struct, this entity will be skipped from file.
 * When the \c follow_strict_version_rules flag is set to \c FALSE in the
 * \c DxfFile struct, libdxf will write this entity to file and report
 * with a warning message to \c stderr.
 */
int
dxf_mline_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfMline *mline
                /*!< DXF mline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("MLINE");
        int i;
        DxfPoint *iter;

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
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((fp->acad_version_number < AutoCAD_13)
          && (fp->follow_strict_version_rules))
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, mline->id_code);
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_mline_get_id_code (mline));
        }
        if (strcmp (dxf_mline_get_linetype (mline), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_mline_get_id_code (mline));
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                dxf_mline_set_linetype (mline, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_mline_get_layer (mline), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_mline_get_id_code (mline));
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                dxf_mline_set_layer (mline, strdup (DXF_DEFAULT_LAYER));
        }
        if (dxf_mline_get_number_of_parameters (mline) >= (DXF_MAX_PARAM - 1))
        {
                fprintf (stderr,
                  (_("Error in %s () too many parameters.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_mline_get_number_of_area_fill_parameters (mline) >= (DXF_MAX_PARAM - 1))
        {
                fprintf (stderr,
                  (_("Error in %s () too many area fill parameters.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_mline_get_id_code (mline) != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_mline_get_id_code (mline));
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
        if ((strcmp (mline->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_mline_get_dictionary_owner_soft (mline));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_mline_get_dictionary_owner_hard (mline), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_mline_get_dictionary_owner_hard (mline));
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_mline_get_paperspace (mline) == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_mline_get_layer (mline));
        if (strcmp (dxf_mline_get_linetype (mline), DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_mline_get_linetype (mline));
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (dxf_mline_get_material (mline), "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", dxf_mline_get_material (mline));
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_mline_get_elevation (mline) != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_mline_get_elevation (mline));
        }
        if (dxf_mline_get_color (mline) != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_mline_get_color (mline));
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", dxf_mline_get_lineweight (mline));
        }
        if (dxf_mline_get_linetype_scale (mline) != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_mline_get_linetype_scale (mline));
        }
        if (dxf_mline_get_visibility (mline) != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_mline_get_visibility (mline));
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", dxf_mline_get_graphics_data_size (mline));
#else
                fprintf (fp->fp, " 92\n%d\n", dxf_mline_get_graphics_data_size (mline));
#endif
                DxfBinaryGraphicsData *bgd_iter = (DxfBinaryGraphicsData *) dxf_mline_get_binary_graphics_data (mline);
                while (dxf_binary_graphics_data_get_data_line (bgd_iter) != NULL)
                {
                        fprintf (fp->fp, "310\n%s\n", dxf_binary_graphics_data_get_data_line (bgd_iter));
                        bgd_iter = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_get_next (bgd_iter);
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", dxf_mline_get_color_value (mline));
                fprintf (fp->fp, "430\n%s\n", dxf_mline_get_color_name (mline));
                fprintf (fp->fp, "440\n%ld\n", dxf_mline_get_transparency (mline));
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", dxf_mline_get_plot_style_name (mline));
                fprintf (fp->fp, "284\n%d\n", dxf_mline_get_shadow_mode (mline));
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbMline\n");
        }
        if (mline->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_mline_get_thickness (mline));
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_mline_get_style_name (mline));
        fprintf (fp->fp, "340\n%s\n", dxf_mline_get_mlinestyle_dictionary (mline));
        fprintf (fp->fp, " 40\n%f\n", dxf_mline_get_scale_factor (mline));
        fprintf (fp->fp, " 70\n%d\n", dxf_mline_get_justification (mline));
        fprintf (fp->fp, " 71\n%d\n", dxf_mline_get_flags (mline));
        fprintf (fp->fp, " 72\n%d\n", dxf_mline_get_number_of_vertices (mline));
        fprintf (fp->fp, " 73\n%d\n", dxf_mline_get_number_of_elements (mline));
        fprintf (fp->fp, " 10\n%f\n", dxf_mline_get_x0 (mline));
        fprintf (fp->fp, " 20\n%f\n", dxf_mline_get_y0 (mline));
        fprintf (fp->fp, " 30\n%f\n", dxf_mline_get_z0 (mline));
        if ((fp->acad_version_number >= AutoCAD_12)
                && (dxf_mline_get_extr_x0 (mline) != 0.0)
                && (dxf_mline_get_extr_y0 (mline) != 0.0)
                && (dxf_mline_get_extr_z0 (mline) != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", dxf_mline_get_extr_x0 (mline));
                fprintf (fp->fp, "220\n%f\n", dxf_mline_get_extr_y0 (mline));
                fprintf (fp->fp, "230\n%f\n", dxf_mline_get_extr_z0 (mline));
        }
        iter = (DxfPoint *) mline->p1;
        i = 1;
        while (iter->next != NULL)
        {
                fprintf (fp->fp, " 11\n%f\n", iter->x0);
                fprintf (fp->fp, " 21\n%f\n", iter->y0);
                fprintf (fp->fp, " 31\n%f\n", iter->z0);
                iter = (DxfPoint *) iter->next;
                i++;
        }
        if (i != mline->number_of_vertices)
        {
                fprintf (stderr,
                  (_("Warning in %s () actual number of vertices differs from number_of_vertices value in struct.\n")),
                  __FUNCTION__);
        }
        iter = (DxfPoint *) mline->p2;
        i = 1;
        while (iter->next != NULL)
        {
                fprintf (fp->fp, " 12\n%f\n", iter->x0);
                fprintf (fp->fp, " 22\n%f\n", iter->y0);
                fprintf (fp->fp, " 32\n%f\n", iter->z0);
                iter = (DxfPoint *) iter->next;
                i++;
        }
        if (i != mline->number_of_vertices)
        {
                fprintf (stderr,
                  (_("Warning in %s () actual number of vertices differs from number_of_vertices value in struct.\n")),
                  __FUNCTION__);
        }
        iter = (DxfPoint *) mline->p3;
        i = 1;
        while (iter->next != NULL)
        {
                fprintf (fp->fp, " 13\n%f\n", iter->x0);
                fprintf (fp->fp, " 23\n%f\n", iter->y0);
                fprintf (fp->fp, " 33\n%f\n", iter->z0);
                iter = (DxfPoint *) iter->next;
                i++;
        }
        if (i != mline->number_of_vertices)
        {
                fprintf (stderr,
                  (_("Warning in %s () actual number of vertices differs from number_of_vertices value in struct.\n")),
                  __FUNCTION__);
        }
        fprintf (fp->fp, " 74\n%d\n", mline->number_of_parameters);
        for (i = 0; i < mline->number_of_parameters; i++)
        {
                fprintf (fp->fp, " 41\n%f\n", mline->element_parameters[i]);
        }
        fprintf (fp->fp, " 75\n%d\n", mline->number_of_area_fill_parameters);
        for (i = 0; i < mline->number_of_area_fill_parameters; i++)
        {
                fprintf (fp->fp, " 42\n%f\n", mline->area_fill_parameters[i]);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c MLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mline_free
(
        DxfMline *mline
                /*!< Pointer to the memory occupied by the DXF \c MLINE
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (mline->linetype);
        free (mline->layer);
        dxf_binary_graphics_data_free_list (mline->binary_graphics_data);
        free (mline->dictionary_owner_soft);
        free (mline->material);
        free (mline->dictionary_owner_hard);
        free (mline->plot_style_name);
        free (mline->color_name);
        free (mline->style_name);
        dxf_point_free (mline->p0);
        dxf_point_free_list (mline->p1);
        dxf_point_free_list (mline->p2);
        dxf_point_free_list (mline->p3);
        free (mline->mlinestyle_dictionary);
        free (mline);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c MLINE entities and all their data fields.
 */
void
dxf_mline_free_list
(
        DxfMline *mlines
                /*!< a pointer to the single linked list of DXF \c MLINE
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (mlines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (mlines != NULL)
        {
                DxfMline *iter = (DxfMline *) mlines->next;
                dxf_mline_free (mlines);
                mlines = (DxfMline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c MLINE entity.
 *
 * \return ID code.
 */
int
dxf_mline_get_id_code
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_id_code
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
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
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the linetype from a DXF \c MLINE entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_mline_get_linetype
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_linetype
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the layer from a DXF \c MLINE entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_mline_get_layer
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->layer));
}


/*!
 * \brief Set the layer for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_layer
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c elevation from a DXF \c MLINE entity.
 *
 * \return \c elevation.
 */
double
dxf_mline_get_elevation
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_elevation
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c thickness from a DXF \c MLINE entity.
 *
 * \return \c thickness.
 */
double
dxf_mline_get_thickness
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_thickness
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c MLINE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_mline_get_linetype_scale
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_linetype_scale
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c visibility from a DXF \c MLINE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_mline_get_visibility
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_visibility
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c color from a DXF \c MLINE entity.
 *
 * \return \c color.
 */
int
dxf_mline_get_color
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->color);
}


/*!
 * \brief Set the \c color for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_color
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c MLINE entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_mline_get_paperspace
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mline->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_paperspace
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c MLINE entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_mline_get_graphics_data_size
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mline->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_graphics_data_size
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c MLINE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mline_get_shadow_mode
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_shadow_mode
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c MLINE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_mline_get_binary_graphics_data
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) mline->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c MLINE entity.
 */
DxfMline *
dxf_mline_set_binary_graphics_data
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c MLINE entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mline_get_dictionary_owner_soft
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c MLINE entity.
 */
DxfMline *
dxf_mline_set_dictionary_owner_soft
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c MLINE entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_mline_get_material
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_material
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c MLINE entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mline_get_dictionary_owner_hard
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c MLINE entity.
 */
DxfMline *
dxf_mline_set_dictionary_owner_hard
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c lineweight from a DXF \c MLINE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mline_get_lineweight
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_lineweight
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c MLINE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_mline_get_plot_style_name
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_plot_style_name
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c color_value from a DXF \c MLINE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mline_get_color_value
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_color_value
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c color_name from a DXF \c MLINE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mline_get_color_name
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_color_name
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c transparency from a DXF \c MLINE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mline_get_transparency
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_transparency
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c style_name from a DXF \c MLINE entity.
 *
 * \return \c style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mline_get_style_name
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->style_name));
}


/*!
 * \brief Set the \c style_name for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_style_name
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *style_name
                /*!< a string containing the \c style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->style_name = strdup (style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the start point \c p0 of a DXF \c MLINE entity.
 *
 * \return the start point \c p0.
 */
DxfPoint *
dxf_mline_get_p0
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p0);
}


/*!
 * \brief Set the start point \c p0 of a DXF \c MLINE entity.
 *
 * \return a pointer to a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_p0
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the X-value of the start point \c x0 of a DXF \c MLINE
 * entity.
 *
 * \return the X-value of the start point \c x0.
 */
double
dxf_mline_get_x0
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p0->x0);
}


/*!
 * \brief Set the X-value of the start point \c x0 of a DXF \c MLINE
 * entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_x0
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double x0
                /*!< the X-value of the start point \c x0 of a DXF
                 * \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Y-value of the start point \c y0 of a DXF \c MLINE
 * entity.
 *
 * \return the Y-value of the start point \c x0.
 */
double
dxf_mline_get_y0
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p0->y0);
}


/*!
 * \brief Set the Y-value of the start point \c y0 of a DXF \c MLINE
 * entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_y0
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double y0
                /*!< the Y-value of the start point \c y0 of a DXF
                 * \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Z-value of the start point \c z0 of a DXF \c MLINE
 * entity.
 *
 * \return the Z-value of the start point \c z0.
 */
double
dxf_mline_get_z0
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p0->z0);
}


/*!
 * \brief Set the Z-value of the start point \c z0 of a DXF \c MLINE
 * entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_z0
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double z0
                /*!< the Z-value of the start point \c z0 of a DXF
                 * \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the first entry of a linked list of vertices \c p1 of a
 * DXF \c MLINE entity.
 *
 * \return the first entry of a linked list of vertices \c p1.
 */
DxfPoint *
dxf_mline_get_p1
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p1);
}


/*!
 * \brief Set the first entry of a linked list of vertices \c p1 of a
 * DXF \c MLINE entity.
 *
 * \return a pointer to a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_p1
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the X-value of the first entry of a linked list of
 * vertices \c x1 of a DXF \c MLINE entity.
 *
 * \return the X-value of the first entry of a linked list of vertices
 * \c x1.
 */
double
dxf_mline_get_x1
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p1->x0);
}


/*!
 * \brief Set the X-value of the first entry of a linked list of
 * vertices \c x1 of a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_x1
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double x1
                /*!< the X-value of the first entry of a linked list of
                 * vertices \c x1 of a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Y-value of the first entry of a linked list of
 * vertices \c y1 of a DXF \c MLINE entity.
 *
 * \return the Y-value of the first entry of a linked list of vertices
 * \c y1.
 */
double
dxf_mline_get_y1
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p1->y0);
}


/*!
 * \brief Set the Y-value of the first entry of a linked list of
 * vertices \c y1 of a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_y1
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double y1
                /*!< the Y-value of the first entry of a linked list of
                 * vertices \c y1 of a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Z-value of the first entry of a linked list of
 * vertices \c z1 of a DXF \c MLINE entity.
 *
 * \return the Z-value of the first entry of a linked list of vertices
 * \c z1.
 */
double
dxf_mline_get_z1
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p1->z0);
}


/*!
 * \brief Set the Z-value of the first entry of a linked list of
 * vertices \c z1 of a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_z1
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double z1
                /*!< the Z-value of the first entry of a linked list of
                 * vertices \c z1 of a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the first entry of a linked list of direction vector
 * vertices \c p2 of a DXF \c MLINE entity.
 *
 * \return the first entry of a linked list of vertices \c p2.
 */
DxfPoint *
dxf_mline_get_p2
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p2);
}


/*!
 * \brief Set the first entry of a linked list of direction vector
 * vertices \c p2 of a DXF \c MLINE entity.
 *
 * \return a pointer to a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_p2
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        DxfPoint *p2
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->p2 = p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the X-value of the first entry of a linked list of
 * direction vector vertices \c x2 of a DXF \c MLINE entity.
 *
 * \return the X-value of the first entry of a linked list of direction
 * vector vertices \c x2.
 */
double
dxf_mline_get_x2
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p2->x0);
}


/*!
 * \brief Set the X-value of the first entry of a linked list of
 * direction vector vertices \c x2 of a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_x2
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double x2
                /*!< the X-value of the first entry of a linked list of
                 * direction vector vertices \c x2 of a DXF \c MLINE
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Y-value of the first entry of a linked list of
 * direction vector vertices \c y2 of a DXF \c MLINE entity.
 *
 * \return the X-value of the first entry of a linked list of direction
 * vector vertices \c y2.
 */
double
dxf_mline_get_y2
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p2->y0);
}


/*!
 * \brief Set the Y-value of the first entry of a linked list of
 * direction vector vertices \c y2 of a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_y2
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double y2
                /*!< the Y-value of the first entry of a linked list of
                 * direction vector vertices \c y2 of a DXF \c MLINE
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Z-value of the first entry of a linked list of
 * direction vector vertices \c z2 of a DXF \c MLINE entity.
 *
 * \return the Z-value of the first entry of a linked list of direction
 * vector vertices \c z2.
 */
double
dxf_mline_get_z2
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p2->z0);
}


/*!
 * \brief Set the Z-value of the first entry of a linked list of
 * direction vector vertices \c z2 of a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_z2
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double z2
                /*!< the Z-value of the first entry of a linked list of
                 * direction vector vertices \c z2 of a DXF \c MLINE
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the first entry of a linked list vertices of the direction
 * vector of the miter at this vertex \c p3 of a DXF \c MLINE entity.
 *
 * \return the first entry of a linked list of vertices \c p3.
 */
DxfPoint *
dxf_mline_get_p3
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p3);
}


/*!
 * \brief Set the first entry of a linked list vertices of the direction
 * vector of the miter at this vertex \c p3 of a DXF \c MLINE entity.
 *
 * \return a pointer to a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_p3
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        DxfPoint *p3
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->p3 = p3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the X-value of the first entry of a linked list of
 * vertices of the direction vector of the miter at this vertex \c x3 of
 * a DXF \c MLINE entity.
 *
 * \return the X-value of the first entry of a linked list of vertices
 * of the direction vector of the miter at this vertex \c x3.
 */
double
dxf_mline_get_x3
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p3->x0);
}


/*!
 * \brief Set the X-value of the first entry of a linked list of
 * vertices of the direction vector of the miter at this vertex \c x3 of
 * a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_x3
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double x3
                /*!< the X-value of the first entry of a linked list of
                 * vertices of the direction vector of the miter at this
                 * vertex \c x3 of a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p3->x0 = x3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Y-value of the first entry of a linked list of
 * vertices of the direction vector of the miter at this vertex \c y3 of
 * a DXF \c MLINE entity.
 *
 * \return the Y-value of the first entry of a linked list of vertices
 * of the direction vector of the miter at this vertex \c y3.
 */
double
dxf_mline_get_y3
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p3->y0);
}


/*!
 * \brief Set the Y-value of the first entry of a linked list of
 * vertices of the direction vector of the miter at this vertex \c y3 of
 * a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_y3
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double y3
                /*!< the Y-value of the first entry of a linked list of
                 * vertices of the direction vector of the miter at this
                 * vertex \c y3 of a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p3->y0 = y3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Z-value of the first entry of a linked list of
 * vertices of the direction vector of the miter at this vertex \c z3 of
 * a DXF \c MLINE entity.
 *
 * \return the Z-value of the first entry of a linked list of vertices
 * of the direction vector of the miter at this vertex \c 3.
 */
double
dxf_mline_get_z3
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->p3->z0);
}


/*!
 * \brief Set the Z-value of the first entry of a linked list of
 * vertices of the direction vector of the miter at this vertex \c z3 of
 * a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_z3
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double z3
                /*!< the Z-value of the first entry of a linked list of
                 * vertices of the direction vector of the miter at this
                 * vertex \c z3 of a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->p3->z0 = z3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c scale_factor of a DXF \c MLINE entity.
 *
 * \return \c scale_factor.
 */
double
dxf_mline_get_scale_factor
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->element_parameters == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->scale_factor);
}


/*!
 * \brief Set the \c scale_factor of a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_scale_factor
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double scale_factor
                /*!< the \c scale_factor to be set for the entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->scale_factor = scale_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c element_parameters array of a DXF \c MLINE entity.
 *
 * \return pointer to the \c element_parameters array.
 */
double
dxf_mline_get_element_parameters
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->element_parameters == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (*(mline->element_parameters));
}


/*!
 * \brief Set the pointer of \c element_parameters array of a DXF
 * \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_element_parameters
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double *element_parameters
                /*!< the pointer to the \c element_parameters array to
                 * be set for the entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (element_parameters == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        *(mline->element_parameters) = *element_parameters;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c area_fill_parameters array of a DXF \c MLINE entity.
 *
 * \return pointer to the \c area_fill_parameters array.
 */
double
dxf_mline_get_area_fill_parameters
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (*(mline->area_fill_parameters));
}


/*!
 * \brief Set the pointer of \c area_fill_parameters array of a DXF
 * \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_area_fill_parameters
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double *area_fill_parameters
                /*!< the pointer to the \c area_fill_parameters array to
                 * be set for the entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (area_fill_parameters == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        *(mline->area_fill_parameters) = *area_fill_parameters;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c justification from a DXF \c MLINE entity.
 *
 * \return \c justification.
 */
int
dxf_mline_get_justification
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->justification < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->justification > 2)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->justification);
}


/*!
 * \brief Set the \c justification for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_justification
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int justification
                /*!< the \c justification to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (justification < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (justification > 2)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->justification = justification;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c flags from a DXF \c MLINE entity.
 *
 * \return \c flags.
 */
int
dxf_mline_get_flags
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->flags < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->flags > 0x00001111)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->flags);
}


/*!
 * \brief Set the \c flags for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_flags
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int flags
                /*!< the \c flags to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flags < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flags > 0x00001111)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->flags = flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c number_of_vertices from a DXF \c MLINE entity.
 *
 * \return \c number_of_vertices.
 */
int
dxf_mline_get_number_of_vertices
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->number_of_vertices < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->number_of_vertices);
}


/*!
 * \brief Set the \c number_of_vertices for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_number_of_vertices
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int number_of_vertices
                /*!< the \c number_of_vertices to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_vertices < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->number_of_vertices = number_of_vertices;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c number_of_elements from a DXF \c MLINE entity.
 *
 * \return \c number_of_elements.
 */
int
dxf_mline_get_number_of_elements
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->number_of_elements < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->number_of_elements);
}


/*!
 * \brief Set the \c number_of_elements for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_number_of_elements
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int number_of_elements
                /*!< the \c number_of_elements to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_elements < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->number_of_elements = number_of_elements;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c number_of_parameters from a DXF \c MLINE entity.
 *
 * \return \c number_of_parameters.
 */
int
dxf_mline_get_number_of_parameters
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->number_of_parameters < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->number_of_parameters);
}


/*!
 * \brief Set the \c number_of_parameters for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_number_of_parameters
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int number_of_parameters
                /*!< the \c number_of_parameters to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_parameters < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->number_of_parameters = number_of_parameters;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c number_of_area_fill_parameters from a DXF \c MLINE
 * entity.
 *
 * \return \c number_of_area_fill_parameters.
 */
int
dxf_mline_get_number_of_area_fill_parameters
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mline->number_of_area_fill_parameters < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->number_of_area_fill_parameters);
}


/*!
 * \brief Set the \c number_of_area_fill_parameters for a DXF \c MLINE
 * entity.
 */
DxfMline *
dxf_mline_set_number_of_area_fill_parameters
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        int number_of_area_fill_parameters
                /*!< the \c number_of_area_fill_parameters to be set for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_area_fill_parameters < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->number_of_area_fill_parameters = number_of_area_fill_parameters;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c MLINE entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_mline_get_extrusion_vector_as_point
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (mline == NULL)
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
        point->x0 = mline->extr_x0;
        point->y0 = mline->extr_y0;
        point->z0 = mline->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c MLINE entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_mline_get_extr_x0
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_extr_x0
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c MLINE entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_mline_get_extr_y0
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_extr_y0
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c MLINE entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_mline_get_extr_z0
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_extr_z0
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c MLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF
 * \c MLINE entity.
 */
DxfMline *
dxf_mline_set_extrusion_vector_from_point
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->extr_x0 = (double) point->x0;
        mline->extr_y0 = (double) point->y0;
        mline->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Set the extrusion vector for a DXF \c MLINE entity.
 */
DxfMline *
dxf_mline_set_extrusion_vector
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
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
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->extr_x0 = extr_x0;
        mline->extr_y0 = extr_y0;
        mline->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the \c mlinestyle_dictionary from a DXF \c MLINE entity.
 *
 * \return \c mlinestyle_dictionary when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mline_get_mlinestyle_dictionary
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->mlinestyle_dictionary ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mline->mlinestyle_dictionary));
}


/*!
 * \brief Set the \c mlinestyle_dictionary for a DXF \c MLINE entity.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMline *
dxf_mline_set_mlinestyle_dictionary
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        char *mlinestyle_dictionary
                /*!< a string containing the \c mlinestyle_dictionary
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mlinestyle_dictionary == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mline->mlinestyle_dictionary = strdup (mlinestyle_dictionary);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the pointer to the next \c MLINE entity from a DXF 
 * \c MLINE entity.
 *
 * \return pointer to the next \c MLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMline *
dxf_mline_get_next
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMline *) mline->next);
}


/*!
 * \brief Set the pointer to the next \c MLINE for a DXF \c MLINE
 * entity.
 */
DxfMline *
dxf_mline_set_next
(
        DxfMline *mline,
                /*!< a pointer to a DXF \c MLINE entity. */
        DxfMline *next
                /*!< a pointer to the next \c MLINE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
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
        mline->next = (struct DxfMline *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mline);
}


/*!
 * \brief Get the pointer to the last \c MLINE entity from a linked list
 * of DXF \c MLINE entities.
 *
 * \return pointer to the last \c MLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMline *
dxf_mline_get_last
(
        DxfMline *mline
                /*!< a pointer to a DXF \c MLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mline->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMline *) mline);
        }
        DxfMline *iter = (DxfMline *) mline->next;
        while (iter->next != NULL)
        {
                iter = (DxfMline *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMline *) iter);
}


/* EOF */
