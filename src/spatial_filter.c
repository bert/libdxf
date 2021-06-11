/*!
 * \file spatial_filter.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF spatial_filter object (\c SPATIAL_FILTER).
 *
 * \since The \c SPATIAL_FILTER object was introduced in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
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


#include "spatial_filter.h"


/*!
 * \brief Allocate memory for a \c DxfSpatialFilter.
 *
 * Fill the memory contents with zeros.
 */
DxfSpatialFilter *
dxf_spatial_filter_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSpatialFilter *spatial_filter = NULL;
        size_t size;

        size = sizeof (DxfSpatialFilter);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((spatial_filter = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpatialFilter struct.\n")),
                  __FUNCTION__);
                spatial_filter = NULL;
        }
        else
        {
                memset (spatial_filter, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SPATIAL_FILTER
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSpatialFilter *
dxf_spatial_filter_init
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to the DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spatial_filter = dxf_spatial_filter_new ();
        }
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpatialFilter struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->id_code = 0;
        spatial_filter->dictionary_owner_soft = strdup ("");
        spatial_filter->dictionary_owner_hard = strdup ("");
        spatial_filter->p0 = dxf_point_new ();
        spatial_filter->p0 = dxf_point_init (spatial_filter->p0);
        spatial_filter->p0->x0 = 0.0;
        spatial_filter->p0->y0 = 0.0;
        spatial_filter->p1 = dxf_point_new ();
        spatial_filter->p1 = dxf_point_init (spatial_filter->p1);
        spatial_filter->p1->x0 = 0.0;
        spatial_filter->p1->y0 = 0.0;
        spatial_filter->p1->z0 = 0.0;
        for (i = 0; i < 12; i++)
        {
                spatial_filter->inverse_block_transformation[i] = 0.0;
                spatial_filter->block_transformation[i] = 0.0;
        }
        spatial_filter->front_clipping_plane_distance = 0.0;
        spatial_filter->back_clipping_plane_distance = 0.0;
        spatial_filter->number_of_points = 0;
        spatial_filter->clip_boundary_display_flag = 0;
        spatial_filter->front_clipping_plane_flag = 0;
        spatial_filter->back_clipping_plane_flag = 0;
        spatial_filter->extr_x0 = 0.0;
        spatial_filter->extr_y0 = 0.0;
        spatial_filter->extr_z0 = 0.0;
        spatial_filter->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SPATIAL_FILTER object.
 *
 * The last line read from file contained the string "SPATIAL_FILTER". \n
 * Now follows some data for the \c SPATIAL_FILTER, to be terminated with a
 * "  0" string announcing the following object, or the end of the
 * \c OBJECTS section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c spatial_filter. \n
 *
 * \return a pointer to \c spatial_filter.
 */
DxfSpatialFilter *
dxf_spatial_filter_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to the DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int k;
        DxfPoint *iter_p0 = NULL;

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
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spatial_filter = dxf_spatial_filter_init (spatial_filter);
        }
        i = 0;
        k = 0;
        iter_p0 = (DxfPoint *) spatial_filter->p0;
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
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &spatial_filter->id_code);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the clip boundary definition point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter_p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the clip boundary definition point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter_p0->y0);
                        iter_p0->next = (struct DxfPoint *) dxf_point_init ((DxfPoint *) iter_p0->next);
                        iter_p0 = (DxfPoint *) iter_p0->next;
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the X-value
                         * of the origin used to define the local
                         * coordinate system of the clip boundary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the Y-value
                         * of the origin used to define the local
                         * coordinate system of the clip boundary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the Z-value
                         * of the origin used to define the local
                         * coordinate system of the clip boundary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->p1->z0);
                }
                else if ((strcmp (temp_string, "40") == 0)
                  && (k == 0)
                  && (spatial_filter->front_clipping_plane_flag == 1))
                {
                        /* Now follows a string containing the front
                         * clipping plane distance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->front_clipping_plane_distance);
                        k++;
                }
                else if ((strcmp (temp_string, "40") == 0)
                  && (k > 0)
                  && (k < 13)) /* k = 1 ... 12. */
                {
                        /* Now follows a string containing an element of
                         * the 4x3 inverse transformation matrix. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->inverse_block_transformation[(k - 1)]);
                        k++;
                }
                else if ((strcmp (temp_string, "40") == 0)
                  && (k >= 13)) /* k = 13 ...25. */
                {
                        /* Now follows a string containing an element of
                         * the 4x3 transformation matrix. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->block_transformation[(k - 13)]);
                        k++;
                }
                else if ((strcmp (temp_string, "41") == 0)
                  && (spatial_filter->back_clipping_plane_flag == 1))
                {
                        /* Now follows a string containing the back
                         * clipping plane distance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->back_clipping_plane_distance);
                        i++;
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * number of points. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spatial_filter->number_of_points);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the clip
                         * boundary display enabled flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spatial_filter->clip_boundary_display_flag);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the front
                         * clipping plane flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spatial_filter->front_clipping_plane_flag);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the back
                         * clipping plane flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &spatial_filter->back_clipping_plane_flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbFilter") != 0)
                          && (strcmp (temp_string, "AcDbSpatialFilter") != 0))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the X-value
                         * of the normal to the plane containing the
                         * clip boundary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the Y-value
                         * of the normal to the plane containing the
                         * clip boundary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_filter->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing the Z-value
                         * of the normal to the plane containing the
                         * clip boundary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, spatial_filter->dictionary_owner_soft);
                        i++;
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, spatial_filter->dictionary_owner_hard);
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
        return (spatial_filter);
}


/*!
 * \brief Write DXF output to a file for a DXF \c SPATIAL_FILTER object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spatial_filter_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to the DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SPATIAL_FILTER");
        int i;
        DxfPoint *iter_p0 = NULL;

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
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->number_of_points < 2)
        {
                fprintf (stderr,
                  (_("Error in %s () number of the clip boundary definition points is too small.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\tThe %s object with id-code %x is dropped from output.\n")),
                  dxf_entity_name, spatial_filter->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, spatial_filter->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (spatial_filter->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", spatial_filter->id_code);
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
        if ((strcmp (spatial_filter->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", spatial_filter->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (spatial_filter->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", spatial_filter->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbFilter\n");
                fprintf (fp->fp, "100\nAcDbSpatialFilter\n");
        }
        fprintf (fp->fp, " 70\n%d\n", spatial_filter->number_of_points);
        if (spatial_filter->p0 != NULL)
        {
                iter_p0 = (DxfPoint*) spatial_filter->p0;
                while (iter_p0 != NULL)
                {
                        fprintf (fp->fp, " 10\n%f\n", iter_p0->x0);
                        fprintf (fp->fp, " 20\n%f\n", iter_p0->y0);
                        iter_p0 = (DxfPoint*) iter_p0->next;
                }
        }
        if ((fp->acad_version_number >= AutoCAD_12)
                && (spatial_filter->extr_x0 != 0.0)
                && (spatial_filter->extr_y0 != 0.0)
                && (spatial_filter->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", spatial_filter->extr_x0);
                fprintf (fp->fp, "220\n%f\n", spatial_filter->extr_y0);
                fprintf (fp->fp, "230\n%f\n", spatial_filter->extr_z0);
        }
        fprintf (fp->fp, " 11\n%f\n", spatial_filter->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", spatial_filter->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", spatial_filter->p1->z0);
        fprintf (fp->fp, " 71\n%d\n", spatial_filter->clip_boundary_display_flag);
        fprintf (fp->fp, " 72\n%d\n", spatial_filter->front_clipping_plane_flag);
        if (spatial_filter->front_clipping_plane_flag)
        {
                fprintf (fp->fp, " 40\n%f\n", spatial_filter->front_clipping_plane_distance);
        }
        fprintf (fp->fp, " 73\n%d\n", spatial_filter->back_clipping_plane_flag);
        if (spatial_filter->back_clipping_plane_flag)
        {
                fprintf (fp->fp, " 41\n%f\n", spatial_filter->back_clipping_plane_distance);
        }
        for (i = 0; i < 12; i++)
        {
                fprintf (fp->fp, " 40\n%f\n", spatial_filter->inverse_block_transformation[i]);
        }
        for (i = 0; i < 12; i++)
        {
                fprintf (fp->fp, " 40\n%f\n", spatial_filter->block_transformation[i]);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SPATIAL_FILTER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spatial_filter_free
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to the memory occupied by the DXF
                 * \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (spatial_filter->dictionary_owner_soft);
        free (spatial_filter->dictionary_owner_hard);
        free (spatial_filter);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SPATIAL_FILTER objects and all their data fields.
 */
void
dxf_spatial_filter_free_list
(
        DxfSpatialFilter *spatial_filters
                /*!< a pointer to the single linked list of DXF
                 * \c SPATIAL_FILTER objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (spatial_filters == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (spatial_filters != NULL)
        {
                DxfSpatialFilter *iter = (DxfSpatialFilter *) spatial_filters->next;
                dxf_spatial_filter_free (spatial_filters);
                spatial_filters = (DxfSpatialFilter *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SPATIAL_FILTER object.
 *
 * \return \c id_code.
 */
int
dxf_spatial_filter_get_id_code
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_id_code
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        int id_code
                /*!< the \c id_code to be set for the object.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
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
        spatial_filter->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SPATIAL_FILTER object.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_spatial_filter_get_dictionary_owner_soft
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (spatial_filter->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_dictionary_owner_soft
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
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
        spatial_filter->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SPATIAL_FILTER object.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_spatial_filter_get_dictionary_owner_hard
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (spatial_filter->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_dictionary_owner_hard
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
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
        spatial_filter->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the clip boundary definition point \c p0 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return the clip boundary definition point \c p0.
 */
DxfPoint *
dxf_spatial_filter_get_p0
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->p0);
}


/*!
 * \brief Set the clip boundary definition point \c p0 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return a pointer to a DXF \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_p0
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
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
        spatial_filter->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the X-value of the clip boundary definition point \c x0 of
 * a DXF \c SPATIAL_FILTER object.
 *
 * \return the X-value of the clip boundary definition point \c x0.
 */
double
dxf_spatial_filter_get_x0
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->p0->x0);
}


/*!
 * \brief Set the X-value of the clip boundary definition point \c x0 of
 * a DXF \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL when an
 * error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_x0
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double x0
                /*!< the X-value of the clip boundary definition point
                 * \c x0 of a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the Y-value of the clip boundary definition point \c y0 of
 * a DXF \c SPATIAL_FILTER object.
 *
 * \return the Y-value of the clip boundary definition point \c y0.
 */
double
dxf_spatial_filter_get_y0
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->p0->y0);
}


/*!
 * \brief Set the Y-value of the clip boundary definition point \c y0 of
 * a DXF \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL
 * when an error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_y0
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double y0
                /*!< the Y-value of the clip boundary definition point
                 * \c y0 of a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the \c next clip boundary definition point \c p0 of
 * a DXF \c SPATIAL_FILTER object.
 *
 * \return the \c next clip boundary definition point \c p0.
 *
 * \todo This function can be replaced by dxf_point_get_next().
 */
DxfPoint *
dxf_spatial_filter_get_p0_next
(
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfPoint *) p0->next);
}


/*!
 * \brief Set the \c next point for a clip boundary definition point
 * \c p0 of a DXF \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c p0 when successful, or \c NULL when an error
 * occurred.
 *
 * \todo This function can be replaced by dxf_point_set_next().
 */
DxfPoint *
dxf_spatial_filter_set_p0_next
(
        DxfPoint *p0,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfPoint *next
                /*!< the \c next clip boundary definition point for a
                 * DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (p0 == NULL)
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
        p0->next = (struct DxfPoint *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p0);
}


/*!
 * \brief Get the origin used to define the local coordinate system of
 * the clip boundary \c p1 of a DXF \c SPATIAL_FILTER object.
 *
 * \return the origin point \c p1.
 */
DxfPoint *
dxf_spatial_filter_get_p1
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->p1);
}


/*!
 * \brief Set the origin used to define the local coordinate system of
 * the clip boundary \c p1 of a DXF \c SPATIAL_FILTER object.
 *
 * \return a pointer to a DXF \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_p1
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
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
        spatial_filter->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the X-value of the origin used to define the local
 * coordinate system of the clip boundary \c x1 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return the X-value of the origin used to define the local coordinate
 * system of the clip boundary \c x1.
 */
double
dxf_spatial_filter_get_x1
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->p1->x0);
}


/*!
 * \brief Set the X-value of the origin used to define the local
 * coordinate system of the clip boundary \c x1 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL when an
 * error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_x1
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double x1
                /*!< the X-value of the origin used to define the local
                 * coordinate system of the clip boundary \c x1 of a DXF
                 * \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the Y-value of the origin used to define the local
 * coordinate system of the clip boundary \c y1 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return the Y-value of the origin used to define the local coordinate
 * system of the clip boundary \c y1.
 */
double
dxf_spatial_filter_get_y1
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->p1->y0);
}


/*!
 * \brief Set the Y-value of the origin used to define the local
 * coordinate system of the clip boundary \c y1 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL when an
 * error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_y1
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double y1
                /*!< the Y-value of the origin used to define the local
                 * coordinate system of the clip boundary \c y1 of a DXF
                 * \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the Z-value of the origin used to define the local
 * coordinate system of the clip boundary \c z1 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return the Z-value of the origin used to define the local coordinate
 * system of the clip boundary \c z1.
 */
double
dxf_spatial_filter_get_z1
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->p1->z0);
}


/*!
 * \brief Set the Z-value of the origin used to define the local
 * coordinate system of the clip boundary \c z1 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL when an
 * error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_z1
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double z1
                /*!< the Z-value of the origin used to define the local
                 * coordinate system of the clip boundary \c z1 of a DXF
                 * \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \todo Add dxf_spatial_filter_get_inverse_block_transformation().
 */


/*!
 * \todo Add dxf_spatial_filter_set_inverse_block_transformation().
 */


/*!
 * \todo Add dxf_spatial_filter_get_block_transformation().
 */


/*!
 * \todo Add dxf_spatial_filter_set_block_transformation().
 */


/*!
 * \brief Get the front clipping plane distance
 * \c front_clipping_plane_distance of a DXF \c SPATIAL_FILTER object.
 *
 * \return the front clipping plane distance
 * \c front_clipping_plane_distance.
 */
double
dxf_spatial_filter_get_front_clipping_plane_distance
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->front_clipping_plane_distance);
}


/*!
 * \brief Set the front clipping plane distance
 * \c front_clipping_plane_distance of a DXF \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL
 * when an error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_front_clipping_plane_distance
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double front_clipping_plane_distance
                /*!< the front clipping plane distance
                 * \c front_clipping_plane_distance to be set for a DXF
                 * \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->front_clipping_plane_distance = front_clipping_plane_distance;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the back clipping plane distance
 * \c back_clipping_plane_distance of a DXF \c SPATIAL_FILTER object.
 *
 * \return the back clipping plane distance
 * \c fback_clipping_plane_distance.
 */
double
dxf_spatial_filter_get_back_clipping_plane_distance
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->back_clipping_plane_distance);
}


/*!
 * \brief Set the back clipping plane distance
 * \c back_clipping_plane_distance of a DXF \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL
 * when an error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_back_clipping_plane_distance
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double back_clipping_plane_distance
                /*!< the back clipping plane distance
                 * \c back_clipping_plane_distance to be set for a DXF
                 * \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->back_clipping_plane_distance = back_clipping_plane_distance;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the \c number_of_points from a DXF \c SPATIAL_FILTER
 * object.
 *
 * \return \c number_of_points.
 */
int
dxf_spatial_filter_get_number_of_points
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->number_of_points < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->number_of_points);
}


/*!
 * \brief Set the \c number_of_points for a DXF \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_number_of_points
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        int number_of_points
                /*!< the \c number_of_points to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_points < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        spatial_filter->number_of_points = number_of_points;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the \c clip_boundary_display_flag from a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return \c clip_boundary_display_flag.
 */
int
dxf_spatial_filter_get_clip_boundary_display_flag
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->clip_boundary_display_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (spatial_filter->clip_boundary_display_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->clip_boundary_display_flag);
}


/*!
 * \brief Set the \c clip_boundary_display_flag for a DXF
 * \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_clip_boundary_display_flag
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        int clip_boundary_display_flag
                /*!< the \c clip_boundary_display_flag to be set for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (clip_boundary_display_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (clip_boundary_display_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        spatial_filter->clip_boundary_display_flag = clip_boundary_display_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the \c front_clipping_plane_flag from a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return \c front_clipping_plane_flag.
 */
int
dxf_spatial_filter_get_front_clipping_plane_flag
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->front_clipping_plane_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (spatial_filter->front_clipping_plane_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->front_clipping_plane_flag);
}


/*!
 * \brief Set the \c front_clipping_plane_flag for a DXF
 * \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_front_clipping_plane_flag
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        int front_clipping_plane_flag
                /*!< the \c front_clipping_plane_flag to be set for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (front_clipping_plane_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (front_clipping_plane_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        spatial_filter->front_clipping_plane_flag = front_clipping_plane_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the \c back_clipping_plane_flag from a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return \c back_clipping_plane_flag.
 */
int
dxf_spatial_filter_get_back_clipping_plane_flag
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_filter->back_clipping_plane_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (spatial_filter->back_clipping_plane_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->back_clipping_plane_flag);
}


/*!
 * \brief Set the \c back_clipping_plane_flag for a DXF
 * \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_back_clipping_plane_flag
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        int back_clipping_plane_flag
                /*!< the \c back_clipping_plane_flag to be set for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (back_clipping_plane_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (back_clipping_plane_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        spatial_filter->back_clipping_plane_flag = back_clipping_plane_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_spatial_filter_get_extrusion_vector_as_point
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (spatial_filter == NULL)
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
        point->x0 = spatial_filter->extr_x0;
        point->y0 = spatial_filter->extr_y0;
        point->z0 = spatial_filter->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_spatial_filter_get_extr_x0
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL when an
 * error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_extr_x0
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return the Y-value of the extrusion vector \c extr_x0.
 */
double
dxf_spatial_filter_get_extr_y0
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL when an
 * error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_extr_y0
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_spatial_filter_get_extr_z0
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c SPATIAL_FILTER object.
 *
 * \return a pointer to \c spatial_filter when successful, or \c NULL when an
 * error occurred.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_extr_z0
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c SPATIAL_FILTER object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_filter->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the pointer to the next \c SPATIAL_FILTER object from a
 * DXF \c SPATIAL_FILTER object.
 *
 * \return pointer to the next \c SPATIAL_FILTER object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSpatialFilter *
dxf_spatial_filter_get_next
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSpatialFilter *) spatial_filter->next);
}


/*!
 * \brief Set the pointer to the next \c SPATIAL_FILTER object for a DXF
 * \c SPATIAL_FILTER object.
 */
DxfSpatialFilter *
dxf_spatial_filter_set_next
(
        DxfSpatialFilter *spatial_filter,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        DxfSpatialFilter *next
                /*!< a pointer to the next \c SPATIAL_FILTER object for
                 * the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
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
        spatial_filter->next = (struct DxfSpatialFilter *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_filter);
}


/*!
 * \brief Get the pointer to the last \c SPATIAL_FILTER object from a linked list
 * of DXF \c SPATIAL_FILTER objects.
 *
 * \return pointer to the last \c SPATIAL_FILTER object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSpatialFilter *
dxf_spatial_filter_get_last
(
        DxfSpatialFilter *spatial_filter
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_filter == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_filter->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfSpatialFilter *) spatial_filter);
        }
        DxfSpatialFilter *iter = (DxfSpatialFilter *) spatial_filter->next;
        while (iter->next != NULL)
        {
                iter = (DxfSpatialFilter *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSpatialFilter *) iter);
}


/* EOF*/
