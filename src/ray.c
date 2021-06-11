/*!
 * \file ray.c
 *
 * \author Copyright (C) 2013, 2014, 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF ray entity (\c RAY).
 *
 * \since The ray entity was introduced in DXF version R13.\n
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


#include "ray.h"


/*!
 * \brief Allocate memory for a \c DxfRay.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfRay *
dxf_ray_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfRay *ray = NULL;
        size_t size;

        size = sizeof (DxfRay);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ray = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRay struct.\n")),
                  __FUNCTION__);
                ray = NULL;
        }
        else
        {
                memset (ray, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Allocate memory and initialize data fields in an \c RAY entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfRay *
dxf_ray_init
(
        DxfRay *ray
                /*!< a pointer to the DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ray = dxf_ray_new ();
        }
        if (ray == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfRay struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        ray->id_code = 0;
        ray->linetype = strdup (DXF_DEFAULT_LINETYPE);
        ray->layer = strdup (DXF_DEFAULT_LAYER);
        ray->elevation = 0.0;
        ray->thickness = 0.0;
        ray->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        ray->visibility = DXF_DEFAULT_VISIBILITY;
        ray->color = DXF_COLOR_BYLAYER;
        ray->paperspace = DXF_MODELSPACE;
        ray->graphics_data_size = 0;
        ray->shadow_mode = 0;
        ray->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        ray->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) ray->binary_graphics_data);
        ray->dictionary_owner_soft = strdup ("");
        ray->material = strdup ("");
        ray->dictionary_owner_hard = strdup ("");
        ray->lineweight = 0;
        ray->plot_style_name = strdup ("");
        ray->color_value = 0;
        ray->color_name = strdup ("");
        ray->transparency = 0;
        ray->p0 = (DxfPoint *) dxf_point_new ();
        ray->p0 = dxf_point_init ((DxfPoint *) ray->p0);
        ray->p0->x0 = 0.0;
        ray->p0->y0 = 0.0;
        ray->p0->z0 = 0.0;
        ray->p1 = (DxfPoint *) dxf_point_new ();
        ray->p1 = dxf_point_init ((DxfPoint *) ray->p1);
        ray->p1->x0 = 0.0;
        ray->p1->y0 = 0.0;
        ray->p1->z0 = 0.0;
        ray->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Read data from a DXF file into an \c LINE entity.
 *
 * The last line read from file contained the string "LINE". \n
 * Now follows some data for the \c LINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c ray.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
DxfRay *
dxf_ray_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfRay *ray
                /*!< a pointer to the DXF \c RAY entity. */
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
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ray = dxf_ray_init (ray);
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
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &ray->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ray->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ray->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->p1->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (ray->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ray->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &ray->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ray->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ray->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbRay") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ray->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, ray->dictionary_owner_hard);
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
        if (strcmp (ray->linetype, "") == 0)
        {
                ray->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (ray->layer, "") == 0)
        {
                ray->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Write DXF output to fp for a line entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occured.
 */
int
dxf_ray_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfRay *ray
                /*!< a pointer to the DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("RAY");

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
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((ray->p0->x0 == ray->p1->x0)
                && (ray->p0->y0 == ray->p1->y0)
                && (ray->p0->z0 == ray->p1->z0))
        {
                fprintf (stderr,
                  (_("Error in %s () start point and end point are identical for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ray->id_code);
                dxf_entity_skip (dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (strcmp (ray->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ray->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                ray->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (ray->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ray->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                ray->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (ray->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", ray->id_code);
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
        if ((strcmp (ray->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", ray->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (ray->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", ray->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (ray->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", ray->layer);
        if (strcmp (ray->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", ray->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (ray->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", ray->elevation);
        }
        if (ray->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", ray->color);
        }
        if (ray->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", ray->linetype_scale);
        }
        if (ray->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", ray->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbRay\n");
        }
        if (ray->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", ray->thickness);
        }
        fprintf (fp->fp, " 10\n%f\n", ray->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", ray->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", ray->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", ray->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", ray->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", ray->p1->z0);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c RAY and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ray_free
(
        DxfRay *ray
                /*!< a pointer to the memory occupied by the DXF \c RAY
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (ray->linetype);
        free (ray->layer);
        free (ray->dictionary_owner_soft);
        free (ray->dictionary_owner_hard);
        dxf_point_free (ray->p0);
        dxf_point_free (ray->p1);
        free (ray);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c RAY entities and all their data fields.
 */
void
dxf_ray_free_list
(
        DxfRay *rays
                /*!< a pointer to the single linked list of DXF
                 * \c RAY entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (rays == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (rays != NULL)
        {
                DxfRay *iter = (DxfRay *) rays->next;
                dxf_ray_free (rays);
                rays = (DxfRay *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c RAY entity.
 *
 * \return \c id_code.
 */
int
dxf_ray_get_id_code
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_id_code
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
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
        if (ray == NULL)
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
        ray->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c linetype from a DXF \c RAY entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_ray_get_linetype
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ray->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_linetype
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c layer from a DXF \c RAY entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_ray_get_layer
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ray->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_layer
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c elevation from a DXF \c RAY entity.
 *
 * \return \c elevation.
 */
double
dxf_ray_get_elevation
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_elevation
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c thickness from a DXF \c RAY entity.
 *
 * \return \c thickness.
 */
double
dxf_ray_get_thickness
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_thickness
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c RAY entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_ray_get_linetype_scale
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_linetype_scale
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c visibility from a DXF \c RAY entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_ray_get_visibility
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_visibility
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c color from a DXF \c RAY entity.
 *
 * \return \c color.
 */
int
dxf_ray_get_color
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->color);
}


/*!
 * \brief Set the \c color for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_color
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c RAY entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_ray_get_paperspace
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ray->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_paperspace
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c RAY entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_ray_get_graphics_data_size
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ray->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c RAY entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_graphics_data_size
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c RAY entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_ray_get_shadow_mode
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c RAY entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_shadow_mode
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c RAY entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_ray_get_binary_graphics_data
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) ray->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c RAY entity.
 */
DxfRay *
dxf_ray_set_binary_graphics_data
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c RAY entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_ray_get_dictionary_owner_soft
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ray->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c RAY entity.
 */
DxfRay *
dxf_ray_set_dictionary_owner_soft
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c RAY entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_ray_get_material
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ray->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c RAY entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_material
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c RAY entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_ray_get_dictionary_owner_hard
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ray->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c RAY entity.
 */
DxfRay *
dxf_ray_set_dictionary_owner_hard
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c lineweight from a DXF \c RAY entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_ray_get_lineweight
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c RAY entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_lineweight
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c RAY entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_ray_get_plot_style_name
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ray->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c RAY entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_plot_style_name
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c color_value from a DXF \c RAY entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_ray_get_color_value
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c RAY entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_color_value
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c color_name from a DXF \c RAY entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_ray_get_color_name
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ray->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c RAY entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_color_name
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the \c transparency from a DXF \c RAY entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_ray_get_transparency
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c RAY entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_transparency
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the start point \c p0 of a DXF \c RAY entity.
 *
 * \return the start point \c p0.
 */
DxfPoint *
dxf_ray_get_p0
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->p0);
}


/*!
 * \brief Set the start point \c p0 of a DXF \c RAY entity.
 *
 * \return a pointer to a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_p0
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the X-value of the start point \c x0 of a DXF \c RAY
 * entity.
 *
 * \return the X-value of the start point \c x0.
 */
double
dxf_ray_get_x0
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->p0->x0);
}


/*!
 * \brief Set the X-value of the start point \c x0 of a DXF \c RAY
 * entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_x0
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double x0
                /*!< the X-value of the start point \c x0 of a DXF
                 * \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the Y-value of the start point \c y0 of a DXF \c RAY
 * entity.
 *
 * \return the Y-value of the start point \c y0.
 */
double
dxf_ray_get_y0
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->p0->y0);
}


/*!
 * \brief Set the Y-value of the start point \c y0 of a DXF \c RAY
 * entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_y0
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double y0
                /*!< the Y-value of the start point \c y0 of a DXF
                 * \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the Z-value of the start point \c z0 of a DXF \c RAY
 * entity.
 *
 * \return the Z-value of the start point \c z0.
 */
double
dxf_ray_get_z0
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->p0->z0);
}


/*!
 * \brief Set the Z-value of the start point \c z0 of a DXF \c RAY
 * entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_z0
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double z0
                /*!< the Z-value of the start point \c z0 of a DXF
                 * \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the end point \c p1 of a DXF \c RAY entity.
 *
 * \return the end point \c p0.
 */
DxfPoint *
dxf_ray_get_p1
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->p1);
}


/*!
 * \brief Set the end point \c p1 of a DXF \c RAY entity.
 *
 * \return a pointer to a DXF \c RAY entity.
 */
DxfRay *
dxf_ray_set_p1
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the X-value of the end point \c x1 of a DXF \c RAY
 * entity.
 *
 * \return the X-value of the end point \c x1.
 */
double
dxf_ray_get_x1
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->p1->x0);
}


/*!
 * \brief Set the X-value of the end point \c x1 of a DXF \c RAY
 * entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_x1
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double x1
                /*!< the X-value of the end point \c x1 of a DXF
                 * \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the Y-value of the end point \c y1 of a DXF \c RAY
 * entity.
 *
 * \return the Y-value of the end point \c y1.
 */
double
dxf_ray_get_y1
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->p1->y0);
}


/*!
 * \brief Set the Y-value of the end point \c y1 of a DXF \c RAY
 * entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_y1
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double y1
                /*!< the Y-value of the end point \c y1 of a DXF
                 * \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the Z-value of the end point \c z1 of a DXF \c RAY
 * entity.
 *
 * \return the Z-value of the end point \c z1.
 */
double
dxf_ray_get_z1
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ray->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray->p1->z0);
}


/*!
 * \brief Set the Z-value of the end point \c z1 of a DXF \c RAY
 * entity.
 *
 * \return a pointer to \c ray when successful, or \c NULL when an
 * error occurred.
 */
DxfRay *
dxf_ray_set_z1
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        double z1
                /*!< the Z-value of the end point \c z1 of a DXF
                 * \c RAY entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ray->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the pointer to the next \c RAY entity from a DXF
 * \c RAY entity.
 *
 * \return pointer to the next \c RAY entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfRay *
dxf_ray_get_next
(
        DxfRay *ray
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfRay *) ray->next);
}


/*!
 * \brief Set the pointer to the next \c RAY for a DXF \c RAY
 * entity.
 */
DxfRay *
dxf_ray_set_next
(
        DxfRay *ray,
                /*!< a pointer to a DXF \c RAY entity. */
        DxfRay *next
                /*!< a pointer to the next \c RAY for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
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
        ray->next = (struct DxfRay *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ray);
}


/*!
 * \brief Get the pointer to the last \c RAY entity from a linked list
 * of DXF \c RAY entities.
 *
 * \return pointer to the last \c RAY entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfRay *
dxf_ray_get_last
(
        DxfRay *ray
                /*!< a pointer to a DXF \c RAY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ray == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ray->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfRay *) ray);
        }
        DxfRay *iter = (DxfRay *) ray->next;
        while (iter->next != NULL)
        {
                iter = (DxfRay *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfRay *) iter);
}


/* EOF */
