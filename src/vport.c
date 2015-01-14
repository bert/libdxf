/*!
 * \file vport.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF Viewport symbol table entry (\c VPORT).
 *
 * The VPORT table is unique: it may contain several entries with the
 * same name (indicating a multiple-viewport configuration).\n
 * The entries corresponding to the active viewport configuration all
 * have the name *ACTIVE.\n
 * The first such entry describes the current viewport.
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


#include "vport.h"


/*!
 * \brief Allocate memory for a DXF \c VPORT entity.
 *
 * Fill the memory contents with zeros.
 */
DxfVPort *
dxf_vport_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfVPort *dxf_vport = NULL;
        size_t size;

        size = sizeof (DxfVPort);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_vport = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfVPort struct.\n")),
                  __FUNCTION__);
                dxf_vport = NULL;
        }
        else
        {
                memset (dxf_vport, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_vport);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c VPORT
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfVPort *
dxf_vport_init
(
        DxfVPort *dxf_vport
                /*!< DXF Viewport symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_vport == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_vport = dxf_vport_new ();
        }
        if (dxf_vport == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfVPort struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_vport->id_code = 0;
        dxf_vport->viewport_name = strdup ("");
        dxf_vport->x_min = 0.0;
        dxf_vport->y_min = 0.0;
        dxf_vport->x_max = 0.0;
        dxf_vport->y_max = 0.0;
        dxf_vport->x_center = 0.0;
        dxf_vport->y_center = 0.0;
        dxf_vport->x_snap_base = 0.0;
        dxf_vport->y_snap_base = 0.0;
        dxf_vport->x_snap_spacing = 0.0;
        dxf_vport->y_snap_spacing = 0.0;
        dxf_vport->x_grid_spacing = 0.0;
        dxf_vport->y_grid_spacing = 0.0;
        dxf_vport->x_direction = 0.0;
        dxf_vport->y_direction = 0.0;
        dxf_vport->z_direction = 0.0;
        dxf_vport->x_target = 0.0;
        dxf_vport->y_target = 0.0;
        dxf_vport->z_target = 0.0;
        dxf_vport->view_height = 0.0;
        dxf_vport->viewport_aspect_ratio = 0.0;
        dxf_vport->lens_length = 0.0;
        dxf_vport->front_plane_offset = 0.0;
        dxf_vport->back_plane_offset = 0.0;
        dxf_vport->snap_rotation_angle = 0.0;
        dxf_vport->view_twist_angle = 0.0;
        dxf_vport->status_field = 0;
        dxf_vport->id = 0;
        dxf_vport->standard_flag = 0;
        dxf_vport->view_mode = 0;
        dxf_vport->circle_zoom_percent = 0;
        dxf_vport->fast_zoom_setting = 0;
        dxf_vport->UCSICON_setting = 0;
        dxf_vport->snap_on = 0;
        dxf_vport->grid_on = 0;
        dxf_vport->snap_style = 0;
        dxf_vport->snap_isopair = 0;
        dxf_vport->dictionary_owner_soft = strdup ("");
        dxf_vport->dictionary_owner_hard = strdup ("");
        dxf_vport->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_vport);
}


/*!
 * \brief Read data from a DXF file into an \c VPORT symbol table entry.
 *
 * The last line read from file contained the string "VPORT". \n
 * Now follows some data for the \c VPORT, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c dxf_vport. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfVPort *
dxf_vport_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfVPort *dxf_vport
                /*!< DXF vport symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_vport == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_vport = dxf_vport_new ();
                dxf_vport = dxf_vport_init (dxf_vport);
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
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_vport->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a viewport
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_vport->viewport_name);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the lower-left corner of viewport. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->x_min);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the lower-left corner of viewport. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->y_min);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the upper-right corner of viewport. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->x_max);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the upper-right corner of viewport. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->y_max);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the view center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->x_center);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the view center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->y_center);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the snap base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->x_snap_base);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the snap base point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->y_snap_base);
                }
                else if (strcmp (temp_string, "14") == 0)
                {
                        /* Now follows a string containing the
                         * X value of snap spacing X and Y. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->x_snap_spacing);
                }
                else if (strcmp (temp_string, "24") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of snap spacing X and Y. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->y_snap_spacing);
                }
                else if (strcmp (temp_string, "15") == 0)
                {
                        /* Now follows a string containing the
                         * X value of grid spacing X and Y. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->x_grid_spacing);
                }
                else if (strcmp (temp_string, "25") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of grid spacing X and Y. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->y_grid_spacing);
                }
                else if (strcmp (temp_string, "16") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the view direction from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->x_direction);
                }
                else if (strcmp (temp_string, "26") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the view direction from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->y_direction);
                }
                else if (strcmp (temp_string, "36") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the view direction from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->z_direction);
                }
                else if (strcmp (temp_string, "17") == 0)
                {
                        /* Now follows a string containing the
                         * X value of the view target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->x_target);
                }
                else if (strcmp (temp_string, "27") == 0)
                {
                        /* Now follows a string containing the
                         * Y value of the view target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->y_target);
                }
                else if (strcmp (temp_string, "37") == 0)
                {
                        /* Now follows a string containing the
                         * Z value of the view target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->z_target);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the view
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->view_height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the viewport
                         * aspect ratio. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->viewport_aspect_ratio);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the lens
                         * length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->viewport_aspect_ratio);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the front
                         * clipping plane - offset from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->front_plane_offset);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the back
                         * clipping plane - offset from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->back_plane_offset);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the snap
                         * rotation angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->snap_rotation_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the view
                         * twist angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vport->view_twist_angle);
                }
                else if (strcmp (temp_string, "68") == 0)
                {
                        /* Now follows a string containing the
                         * status field value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->status_field);
                }
                else if (strcmp (temp_string, "69") == 0)
                {
                        /* Now follows a string containing the
                         * ID value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->id);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->standard_flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * view mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->view_mode);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the circle
                         * zoom percent value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->circle_zoom_percent);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the fast
                         * zoom setting value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->fast_zoom_setting);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the UCSICON
                         * setting value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->UCSICON_setting);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the snap
                         * on/off value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->snap_on);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing the grid
                         * on/off value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->grid_on);
                }
                else if (strcmp (temp_string, "77") == 0)
                {
                        /* Now follows a string containing the snap
                         * style value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->snap_style);
                }
                else if (strcmp (temp_string, "78") == 0)
                {
                        /* Now follows a string containing the snap
                         * isopair value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vport->snap_isopair);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_vport->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_vport->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }

        }
        /* Handle omitted members and/or illegal values. */
        if ((strcmp (dxf_vport->viewport_name, "") == 0)
          || (dxf_vport->viewport_name == NULL))
        {
                fprintf (stderr,
                  (_("Error in %s () empty string in viewport name found while reading from: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_vport);
}


/*!
 * \brief Free the allocated memory for a DXF \c VPORT and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_vport_free
(
        DxfVPort *dxf_vport
                /*!< Pointer to the memory occupied by the DXF \c VPORT
                 * symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_vport->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfVPort was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_vport->viewport_name);
        free (dxf_vport->dictionary_owner_soft);
        free (dxf_vport->dictionary_owner_hard);
        free (dxf_vport);
        dxf_vport = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
