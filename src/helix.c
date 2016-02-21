/*!
 * \file helix.c
 *
 * \author Copyright (C) 2013 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF helix entity (\c HELIX).
 *
 * \warning The \c HELIX entity requires AutoCAD version 2007 or higher.\n
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


#include "helix.h"


/*!
 * \brief Allocate memory for a DXF \c HELIX.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHelix *
dxf_helix_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHelix *helix = NULL;
        size_t size;

        size = sizeof (DxfHelix);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((helix = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfHelix struct.\n")),
                  __FUNCTION__);
                helix = NULL;
        }
        else
        {
                memset (helix, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c HELIX
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfHelix *
dxf_helix_init
(
        DxfHelix *helix
                /*!< DXF helix entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                helix = dxf_helix_new ();
        }
        if (helix == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfHelix struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        helix->id_code = 0;
        helix->linetype = strdup (DXF_DEFAULT_LINETYPE);
        helix->layer = strdup (DXF_DEFAULT_LAYER);
        helix->x0 = 0.0;
        helix->y0 = 0.0;
        helix->z0 = 0.0;
        helix->x1 = 0.0;
        helix->y1 = 0.0;
        helix->z1 = 0.0;
        helix->x2 = 0.0;
        helix->y2 = 0.0;
        helix->z2 = 0.0;
        helix->thickness = 0.0;
        helix->radius = 0.0;
        helix->number_of_turns = 0.0;
        helix->turn_height = 0.0;
        helix->linetype_scale = 0.0;
        helix->visibility = 0;
        helix->color = DXF_COLOR_BYLAYER;
        helix->paperspace = DXF_MODELSPACE;
        helix->major_release_number = 0;
        helix->maintainance_release_number = 0;
        helix->graphics_data_size = 0;
        helix->constraint_type = 0;
        helix->shadow_mode = 0;
        helix->handedness = 0;
        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) helix->binary_graphics_data);
        helix->dictionary_owner_hard = strdup ("");
        helix->material = strdup ("");
        helix->dictionary_owner_soft = strdup ("");
        helix->lineweight = 0;
        helix->plot_style_name = strdup ("");
        helix->color_value = 0;
        helix->color_name = strdup ("");
        helix->transparency = 0;
        dxf_spline_init (helix->spline);
        helix->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Read data from a DXF file into a DXF \c HELIX entity.
 *
 * The last line read from file contained the string "HELIX". \n
 * Now follows some data for the \c HELIX, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c helix. \n
 *
 * \return a pointer to \c helix.
 */
DxfHelix *
dxf_helix_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfHelix *helix
                /*!< DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int i_x0;
        int i_y0;
        int i_z0;
        int i_x1;
        int i_y1;
        int i_z1;
        int i_knot_value;
        int i_weight_value;

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
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                helix = dxf_helix_new ();
                helix = dxf_helix_init (helix);
        }
        i = 0;
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
                        fscanf (fp->fp, "%x\n", &helix->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", helix->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", helix->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the axis base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the start point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the axis vector point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the axis vector point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the axis vector point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->z2);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->radius);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the number of
                         * turns. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->number_of_turns);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the turn
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->turn_height);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &helix->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &helix->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &helix->paperspace);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing a major
                         * release number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &helix->major_release_number);
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing a maintenance
                         * release number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &helix->maintainance_release_number);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &helix->graphics_data_size);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbSpline") == 0))
                        {
                                /*! \todo Parse the helix spline. */
                                i_x0 = 0;
                                i_y0 = 0;
                                i_z0 = 0;
                                i_x1 = 0;
                                i_y1 = 0;
                                i_z1 = 0;
                                i_knot_value = 0;
                                i_weight_value = 0;
                                (fp->line_number)++;
                                fscanf (fp->fp, "%[^\n]", temp_string);
                                while (strcmp (temp_string, "0") != 0)
                                {
                                        if (strcmp (temp_string, "6") == 0)
                                        {
                                                /* Now follows a string containing a linetype
                                                 * name. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%s\n", helix->spline->linetype);
                                        }
                                        else if (strcmp (temp_string, "8") == 0)
                                        {
                                                /* Now follows a string containing a layer name. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%s\n", helix->spline->layer);
                                        }
                                        else if (strcmp (temp_string, "10") == 0)
                                        {
                                                /* Now follows a string containing the
                                                 * X-value of the control point coordinate
                                                 * (multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline->x0[i_x0]);
                                                i_x0++;
                                        }
                                        else if (strcmp (temp_string, "20") == 0)
                                        {
                                                /* Now follows a string containing the
                                                 * Y-coordinate of control point coordinate
                                                 * (multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline->y0[i_y0]);
                                                i_y0++;
                                        }
                                        else if (strcmp (temp_string, "30") == 0)
                                        {
                                                /* Now follows a string containing the
                                                 * Z-coordinate of the control point coordinate
                                                 * (multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline->z0[i_z0]);
                                                i_z0++;
                                        }
                                        else if (strcmp (temp_string, "40") == 0)
                                        {
                                                /* Now follows a knot value (one entry per knot, multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline->knot_value[i_knot_value]);
                                                i_knot_value++;
                                        }
                                        else if (strcmp (temp_string, "41") == 0)
                                        {
                                                /* Now follows a weight value (one entry per knot, multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline->weight_value[i_weight_value]);
                                                i_weight_value++;
                }
                                        else if (strcmp (temp_string, "42") == 0)
                                        {
                                                /* Now follows a knot tolerance value. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline->knot_tolerance);
                                                i_knot_value++;
                                        }
                                        else if (strcmp (temp_string, "43") == 0)
                                        {
                                                /* Now follows a control point tolerance value. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline->control_point_tolerance);
                                        }
                                        else if (strcmp (temp_string, "44") == 0)
                                        {
                                                /* Now follows a fit point tolerance value. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline->fit_tolerance);
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
                                                fprintf (stderr, "Warning: in dxf_spline_read () unknown string tag found while reading from: %s in line: %d.\n",
                                                        fp->filename, fp->line_number);
                                        }
                                }
                        }
                        else if ((strcmp (temp_string, "AcDbEntity") != 0)
                                && ((strcmp (temp_string, "AcDbHelix") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &helix->graphics_data_size);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing a constraint
                         * type value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &helix->constraint_type);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->shadow_mode);
                }
                else if (strcmp (temp_string, "290") == 0)
                {
                        /* Now follows a string containing a handedness
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &helix->handedness);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        /*! \todo parse binary graphics data. */
/*
                        fscanf (fp->fp, "%s\n", helix->binary_graphics_data);
 */
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing a
                         * soft-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", helix->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", helix->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", helix->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &helix->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", helix->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &helix->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", helix->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &helix->transparency);
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
        if (strcmp (helix->linetype, "") == 0)
        {
                helix->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (helix->layer, "") == 0)
        {
                helix->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Write DXF output for a DXF \c HELIX entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_helix_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHelix *helix
                /*!< DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("HELIX");
        int i;
        DxfBinaryGraphicsData *data = NULL;

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
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (helix->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () radius value equals 0.0 for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, helix->id_code);
                fprintf (stderr, "    skipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_2007)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (strcmp (helix->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, helix->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                helix->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (helix->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, helix->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to default layer.\n")),
                  dxf_entity_name);
                helix->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (helix->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", helix->id_code);
        }
        fprintf (fp->fp, "330\n%s\n", helix->dictionary_owner_soft);
        fprintf (fp->fp, "100\nAcDbEntity\n");
        if (helix->paperspace != DXF_MODELSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", helix->layer);
        if (strcmp (helix->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", helix->linetype);
        }
        if (strcmp (helix->material, "") != 0)
        {
                fprintf (fp->fp, "347\n%s\n", helix->material);
        }
        if (helix->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", helix->color);
        }
        if (helix->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", helix->thickness);
        }
        fprintf (fp->fp, " 48\n%f\n", helix->linetype_scale);
        if (helix->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", helix->visibility);
        }
        fprintf (fp->fp, " 92\n%d\n", helix->graphics_data_size);
        data = (DxfBinaryGraphicsData *) helix->binary_graphics_data;
        while (data != NULL)
        {
                fprintf (fp->fp, "310\n%s\n", data->data_line);
                data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_get_next (data);
        }
        fprintf (fp->fp, "370\n%d\n", helix->lineweight);
        fprintf (fp->fp, "420\n%ld\n", helix->color_value);
        fprintf (fp->fp, "430\n%s\n", helix->color_name);
        fprintf (fp->fp, "440\n%ld\n", helix->transparency);
        fprintf (fp->fp, "390\n%s\n", helix->plot_style_name);
        fprintf (fp->fp, "284\n%d\n", helix->shadow_mode);
        /* Create a helix shaped spline and write to a DxfFile. */
        /*! \todo Add code for creating a helix shaped spline. */
        dxf_spline_init (helix->spline);
        helix->spline->flag = 0;
        helix->spline->degree = 3;
        /*! \todo Add code for writing a helix shaped spline to a DxfFile. */
        fprintf (fp->fp, "100\nAcDbSpline\n");
        fprintf (fp->fp, " 70\n%d\n", helix->spline->flag);
        fprintf (fp->fp, " 71\n%d\n", helix->spline->degree);
        fprintf (fp->fp, " 72\n%d\n", helix->spline->number_of_knots);
        fprintf (fp->fp, " 73\n%d\n", helix->spline->number_of_control_points);
        fprintf (fp->fp, " 74\n%d\n", helix->spline->number_of_fit_points);
        fprintf (fp->fp, " 42\n%f\n", helix->spline->knot_tolerance);
        fprintf (fp->fp, " 43\n%f\n", helix->spline->control_point_tolerance);
        fprintf (fp->fp, " 12\n%f\n", helix->spline->x2);
        fprintf (fp->fp, " 22\n%f\n", helix->spline->y2);
        fprintf (fp->fp, " 32\n%f\n", helix->spline->z2);
        fprintf (fp->fp, " 13\n%f\n", helix->spline->x3);
        fprintf (fp->fp, " 23\n%f\n", helix->spline->y3);
        fprintf (fp->fp, " 33\n%f\n", helix->spline->z3);
        for (i = 0; i < helix->spline->number_of_knots; i++)
        {
                fprintf (fp->fp, " 40\n%f\n", helix->spline->knot_value[i]);
        }
        if (helix->spline->number_of_fit_points != 0)
        {
        for (i = 0; i < helix->spline->number_of_fit_points; i++)
                {
                        fprintf (fp->fp, " 41\n%f\n", helix->spline->weight_value[i]);
                }
        }
        for (i = 0; i < helix->spline->number_of_control_points; i++)
        {
                fprintf (fp->fp, " 10\n%f\n", helix->spline->x0[i]);
                fprintf (fp->fp, " 20\n%f\n", helix->spline->y0[i]);
                fprintf (fp->fp, " 30\n%f\n", helix->spline->z0[i]);
        }
        for (i = 0; i < helix->spline->number_of_fit_points; i++)
        {
                fprintf (fp->fp, " 11\n%f\n", helix->spline->x1[i]);
                fprintf (fp->fp, " 21\n%f\n", helix->spline->y1[i]);
                fprintf (fp->fp, " 31\n%f\n", helix->spline->z1[i]);
        }
        /* Continue writing helix entity parameters. */
        fprintf (fp->fp, "100\nAcDbHelix\n");
        fprintf (fp->fp, " 90\n%ld\n", helix->major_release_number);
        fprintf (fp->fp, " 91\n%ld\n", helix->maintainance_release_number);
        fprintf (fp->fp, " 10\n%f\n", helix->x0);
        fprintf (fp->fp, " 20\n%f\n", helix->y0);
        fprintf (fp->fp, " 30\n%f\n", helix->z0);
        fprintf (fp->fp, " 11\n%f\n", helix->x1);
        fprintf (fp->fp, " 21\n%f\n", helix->y1);
        fprintf (fp->fp, " 31\n%f\n", helix->z1);
        fprintf (fp->fp, " 12\n%f\n", helix->x2);
        fprintf (fp->fp, " 22\n%f\n", helix->y2);
        fprintf (fp->fp, " 32\n%f\n", helix->z2);
        fprintf (fp->fp, " 40\n%f\n", helix->radius);
        fprintf (fp->fp, " 41\n%f\n", helix->number_of_turns);
        fprintf (fp->fp, " 42\n%f\n", helix->turn_height);
        fprintf (fp->fp, "290\n%d\n", helix->handedness);
        fprintf (fp->fp, "280\n%d\n", helix->constraint_type);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c HELIX and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_helix_free
(
        DxfHelix *helix
                /*!< Pointer to the memory occupied by the DXF \c HELIX
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (helix->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfHelix was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (helix->linetype);
        free (helix->layer);
        dxf_binary_graphics_data_free_chain ((DxfBinaryGraphicsData *) helix->binary_graphics_data);
        free (helix->dictionary_owner_hard);
        free (helix->material);
        free (helix->dictionary_owner_soft);
        free (helix->plot_style_name);
        free (helix->color_name);
        free (helix);
        helix = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c HELIX
 * entities and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2007.
 */
void
dxf_helix_free_chain
(
        DxfHelix *helices
                /*!< pointer to the chain of DXF \c HELIX entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (helices == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (helices != NULL)
        {
                struct DxfHelix *iter = helices->next;
                dxf_helix_free (helices);
                helices = (DxfHelix *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c HELIX.
 *
 * \return ID code.
 */
int
dxf_helix_get_id_code
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id_code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_id_code
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
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
        if (helix == NULL)
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
        helix->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the linetype from a DXF \c HHELIX entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_helix_get_linetype
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (helix->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_linetype
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the layer from a DXF \c HELIX entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_helix_get_layer
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (helix->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the layer for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_layer
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the thickness from a DXF \c HELIX entity.
 *
 * \return thickness.
 */
double
dxf_helix_get_thickness
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
        }
        result = helix->thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the thickness for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_thickness
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
        }
        helix->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the linetype scale from a DXF \c HELIX entity.
 *
 * \return linetype scale.
 */
double
dxf_helix_get_linetype_scale
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype scale for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_linetype_scale
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the visibility from a DXF \c HELIX entity.
 *
 * \return visibility.
 */
int16_t
dxf_helix_get_visibility
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the visibility for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_visibility
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the color from a DXF \c HELIX entity.
 *
 * \return color.
 */
int
dxf_helix_get_color
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = helix->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_color
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        helix->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c HELIX entity.
 *
 * \return paperspace flag value.
 */
int
dxf_helix_get_paperspace
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (helix->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = helix->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the paperspace flag for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_paperspace
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the graphics data size value from a DXF \c HELIX entity.
 *
 * \return graphics data size flag value.
 */
int
dxf_helix_get_graphics_data_size
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        if (helix->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found in the graphics_data_size member.\n")),
                  __FUNCTION__);
        }
        result = helix->graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the graphics data size value for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_graphics_data_size
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int graphics_data_size
                /*!< the graphics data size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a zero graphics_data_size value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the shadow mode from a DXF \c HELIX entity.
 *
 * \return shadow mode.
 */
int16_t
dxf_helix_get_shadow_mode
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the shadow_mode member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the shadow mode for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_shadow_mode
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range shadow_mode value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c HELIX entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_helix_get_dictionary_owner_soft
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (helix->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_dictionary_owner_soft
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the visibility from a DXF \c HELIX entity.
 *
 * \return lineweight.
 */
int16_t
dxf_helix_get_lineweight
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the lineweight for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_lineweight
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        int16_t lineweight
                /*!< the lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the plot_style_name from a DXF \c HELIX entity.
 *
 * \return plot_style_name when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_helix_get_plot_style_name
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the plot_style_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (helix->plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the plot_style_name for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_plot_style_name
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *plot_style_name
                /*!< a string containing the plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the color_value from a DXF \c HELIX entity.
 *
 * \return color_value.
 */
long
dxf_helix_get_color_value
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        long result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color_value for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_color_value
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        long color_value
                /*!< the color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the color_name from a DXF \c HELIX entity.
 *
 * \return color_name when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_helix_get_color_name
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the color_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (helix->color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color_name for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_color_name
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        char *color_name
                /*!< a string containing the color_name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
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
        helix->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the transparency from a DXF \c HELIX entity.
 *
 * \return transparency.
 */
long
dxf_helix_get_transparency
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        long result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the transparency for a DXF \c HELIX entity.
 */
DxfHelix *
dxf_helix_set_transparency
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX entity. */
        long transparency
                /*!< the transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis base point X-value from a DXF \c HELIX.
 *
 * \return axis base point X-value.
 */
double
dxf_helix_get_x0
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the axis base point X-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_x0
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double x0
                /*!< the axis base point X-value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis base point Y-value from a DXF \c HELIX.
 *
 * \return axis base point Y-value.
 */
double
dxf_helix_get_y0
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the axis base point Y-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_y0
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double y0
                /*!< the axis base point Y-value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis base point Z-value from a DXF \c HELIX.
 *
 * \return axis base point Z-value.
 */
double
dxf_helix_get_z0
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the axis base point Z-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_z0
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double z0
                /*!< the axis base point Z-value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the start point X-value from a DXF \c HELIX.
 *
 * \return start point X-value.
 */
double
dxf_helix_get_x1
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the start point X-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_x1
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double x1
                /*!< the start point X-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->x1 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the start point Y-value from a DXF \c HELIX.
 *
 * \return start point Y-value.
 */
double
dxf_helix_get_y1
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the start point Y-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_y1
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double y1
                /*!< the start point Y-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->y1 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the start point Z-value from a DXF \c HELIX.
 *
 * \return start point Z-value.
 */
double
dxf_helix_get_z1
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the start point Z-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_z1
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double z1
                /*!< the start point Z-value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->z1 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis vector point X-value from a DXF \c HELIX.
 *
 * \return axis vector point X-value.
 */
double
dxf_helix_get_x2
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the axis vector point X-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_x2
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double x2
                /*!< the axis vector point X-value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->x2 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis vector point Y-value from a DXF \c HELIX.
 *
 * \return axis vector point Y-value.
 */
double
dxf_helix_get_y2
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the axis vector point Y-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_y2
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double y2
                /*!< the axis vector point Y-value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->y2 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the axis vector point Z-value from a DXF \c HELIX.
 *
 * \return axis vector point Z-value.
 */
double
dxf_helix_get_z2
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the axis vector point Z-value for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_z2
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double z2
                /*!< the axis vector point Z-value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->z2 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the radius from a DXF \c HELIX entity.
 *
 * \return radius.
 */
double
dxf_helix_get_radius
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->radius;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the radius for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_radius
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double radius
                /*!< the radius to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->radius = radius;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the number_of_turns from a DXF \c HELIX entity.
 *
 * \return number_of_turns.
 */
double
dxf_helix_get_number_of_turns
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->number_of_turns;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the number_of_turns for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_number_of_turns
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double number_of_turns
                /*!< the number_of_turns to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->number_of_turns = number_of_turns;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the turn_height from a DXF \c HELIX entity.
 *
 * \return turn_height.
 */
double
dxf_helix_get_turn_height
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->turn_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the turn_height for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_turn_height
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        double turn_height
                /*!< the turn_height to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->turn_height = turn_height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the major_release_number from a DXF \c HELIX entity.
 *
 * \return major_release_number.
 */
long
dxf_helix_get_major_release_number
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        long result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->major_release_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the major_release_number for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_major_release_number
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        long major_release_number
                /*!< the major_release_number to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->major_release_number = major_release_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the maintainance_release_number from a DXF \c HELIX entity.
 *
 * \return maintainance_release_number.
 */
long
dxf_helix_get_maintainance_release_number
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        long result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->maintainance_release_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the maintainance_release_number for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_maintainance_release_number
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        long maintainance_release_number
                /*!< the maintainance_release_number to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->maintainance_release_number = maintainance_release_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the constraint_type from a DXF \c HELIX.
 *
 * \return constraint_type.
 */
int
dxf_helix_get_constraint_type
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->constraint_type < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the constraint_type member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->constraint_type > 2)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the constraint_type member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->constraint_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the constraint_type for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_constraint_type
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        int constraint_type
                /*!< constraint_type. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (constraint_type < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative constraint_type value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (constraint_type > 2)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid constraint_type value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->constraint_type = constraint_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c handedness from a DXF \c HELIX.
 *
 * \return \c handedness.
 */
int
dxf_helix_get_handedness
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->handedness < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the handedness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (helix->handedness > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the handedness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = helix->handedness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c handedness for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_handedness
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        int handedness
                /*!< \c handedness. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (handedness < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative handedness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (handedness > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid handedness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->handedness = handedness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the \c spline from a DXF \c HELIX.
 *
 * \return \c spline.
 */
DxfSpline *
dxf_helix_get_spline
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSpline *result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfSpline *) helix->spline;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c spline for a DXF \c HELIX.
 */
DxfHelix *
dxf_helix_set_spline
(
        DxfHelix *helix,
                /*!< a pointer to a DXF \c HELIX. */
        DxfSpline *spline
                /*!< \c spline. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        helix->spline = (DxfSpline *) spline;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (helix);
}


/*!
 * \brief Get the pointer to the next \c HELIX entity from a DXF 
 * \c HELIX entity.
 *
 * \return pointer to the next \c HELIX entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfHelix *
dxf_helix_get_next
(
        DxfHelix *helix
                /*!< a pointer to a DXF \c HELIX entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHelix *result;

        /* Do some basic checks. */
        if (helix == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (helix->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfHelix *) helix->next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF*/
