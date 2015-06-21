/*!
 * \file helix.c
 *
 * \author Copyright (C) 2013 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        int i;

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
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                helix->binary_graphics_data[i] = strdup ("");
        }
        helix->dictionary_owner_hard = strdup ("");
        helix->material = strdup ("");
        helix->dictionary_owner_soft = strdup ("");
        helix->lineweight = 0;
        helix->plot_style_name = strdup ("");
        helix->color_value = 0;
        helix->color_name = strdup ("");
        helix->transparency = 0;
        dxf_spline_init (&helix->spline);
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
                                                fscanf (fp->fp, "%s\n", helix->spline.linetype);
                                        }
                                        else if (strcmp (temp_string, "8") == 0)
                                        {
                                                /* Now follows a string containing a layer name. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%s\n", helix->spline.layer);
                                        }
                                        else if (strcmp (temp_string, "10") == 0)
                                        {
                                                /* Now follows a string containing the
                                                 * X-value of the control point coordinate
                                                 * (multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline.x0[i_x0]);
                                                i_x0++;
                                        }
                                        else if (strcmp (temp_string, "20") == 0)
                                        {
                                                /* Now follows a string containing the
                                                 * Y-coordinate of control point coordinate
                                                 * (multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline.y0[i_y0]);
                                                i_y0++;
                                        }
                                        else if (strcmp (temp_string, "30") == 0)
                                        {
                                                /* Now follows a string containing the
                                                 * Z-coordinate of the control point coordinate
                                                 * (multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline.z0[i_z0]);
                                                i_z0++;
                                        }
                                        else if (strcmp (temp_string, "40") == 0)
                                        {
                                                /* Now follows a knot value (one entry per knot, multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline.knot_value[i_knot_value]);
                                                i_knot_value++;
                                        }
                                        else if (strcmp (temp_string, "41") == 0)
                                        {
                                                /* Now follows a weight value (one entry per knot, multiple entries). */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline.weight_value[i_weight_value]);
                                                i_weight_value++;
                }
                                        else if (strcmp (temp_string, "42") == 0)
                                        {
                                                /* Now follows a knot tolerance value. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline.knot_tolerance);
                                                i_knot_value++;
                                        }
                                        else if (strcmp (temp_string, "43") == 0)
                                        {
                                                /* Now follows a control point tolerance value. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline.control_point_tolerance);
                                        }
                                        else if (strcmp (temp_string, "44") == 0)
                                        {
                                                /* Now follows a fit point tolerance value. */
                                                (fp->line_number)++;
                                                fscanf (fp->fp, "%lf\n", &helix->spline.fit_tolerance);
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
                        fscanf (fp->fp, "%s\n", helix->binary_graphics_data[i]);
                        i++;
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
        i = 0;
        while (strlen (helix->binary_graphics_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", helix->binary_graphics_data[i]);
                i++;
        }
        fprintf (fp->fp, "370\n%d\n", helix->lineweight);
        fprintf (fp->fp, "420\n%ld\n", helix->color_value);
        fprintf (fp->fp, "430\n%s\n", helix->color_name);
        fprintf (fp->fp, "440\n%ld\n", helix->transparency);
        fprintf (fp->fp, "390\n%s\n", helix->plot_style_name);
        fprintf (fp->fp, "284\n%d\n", helix->shadow_mode);
        /* Create a helix shaped spline and write to a DxfFile. */
        /*! \todo Add code for creating a helix shaped spline. */
        dxf_spline_init (&helix->spline);
        helix->spline.flag = 0;
        helix->spline.degree = 3;
        /*! \todo Add code for writing a helix shaped spline to a DxfFile. */
        fprintf (fp->fp, "100\nAcDbSpline\n");
        fprintf (fp->fp, " 70\n%d\n", helix->spline.flag);
        fprintf (fp->fp, " 71\n%d\n", helix->spline.degree);
        fprintf (fp->fp, " 72\n%d\n", helix->spline.number_of_knots);
        fprintf (fp->fp, " 73\n%d\n", helix->spline.number_of_control_points);
        fprintf (fp->fp, " 74\n%d\n", helix->spline.number_of_fit_points);
        fprintf (fp->fp, " 42\n%f\n", helix->spline.knot_tolerance);
        fprintf (fp->fp, " 43\n%f\n", helix->spline.control_point_tolerance);
        fprintf (fp->fp, " 12\n%f\n", helix->spline.x2);
        fprintf (fp->fp, " 22\n%f\n", helix->spline.y2);
        fprintf (fp->fp, " 32\n%f\n", helix->spline.z2);
        fprintf (fp->fp, " 13\n%f\n", helix->spline.x3);
        fprintf (fp->fp, " 23\n%f\n", helix->spline.y3);
        fprintf (fp->fp, " 33\n%f\n", helix->spline.z3);
        for (i = 0; i < helix->spline.number_of_knots; i++)
        {
                fprintf (fp->fp, " 40\n%f\n", helix->spline.knot_value[i]);
        }
        if (helix->spline.number_of_fit_points != 0)
        {
        for (i = 0; i < helix->spline.number_of_fit_points; i++)
                {
                        fprintf (fp->fp, " 41\n%f\n", helix->spline.weight_value[i]);
                }
        }
        for (i = 0; i < helix->spline.number_of_control_points; i++)
        {
                fprintf (fp->fp, " 10\n%f\n", helix->spline.x0[i]);
                fprintf (fp->fp, " 20\n%f\n", helix->spline.y0[i]);
                fprintf (fp->fp, " 30\n%f\n", helix->spline.z0[i]);
        }
        for (i = 0; i < helix->spline.number_of_fit_points; i++)
        {
                fprintf (fp->fp, " 11\n%f\n", helix->spline.x1[i]);
                fprintf (fp->fp, " 21\n%f\n", helix->spline.y1[i]);
                fprintf (fp->fp, " 31\n%f\n", helix->spline.z1[i]);
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
        int i;

        if (helix->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfHelix was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (helix->linetype);
        free (helix->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (helix->binary_graphics_data[i]);
        }
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


/* EOF*/
