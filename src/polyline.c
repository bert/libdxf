/*!
 * \file polyline.c
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF polyline entity (\c POLYLINE).
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


#include "polyline.h"


/*!
 * \brief Allocate memory for a \c DxfPolyline.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPolyline *
dxf_polyline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPolyline *polyline = NULL;
        size_t size;

        size = sizeof (DxfPolyline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((polyline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfArc struct.\n")),
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
 * \brief Allocate memory and initialize data fields in a \c POLYLINE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPolyline *
dxf_polyline_init
(
        DxfPolyline *polyline
                /*!< a pointer to the DXF polyline entity. */
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
                polyline = dxf_polyline_new ();
        }
        if (polyline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfPolyline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        polyline->id_code = 0;
        polyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        polyline->layer = strdup (DXF_DEFAULT_LAYER);
        polyline->x0 = 0.0;
        polyline->y0 = 0.0;
        polyline->z0 = 0.0;
        polyline->elevation = 0.0;
        polyline->thickness = 0.0;
        polyline->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        polyline->visibility = DXF_DEFAULT_VISIBILITY;
        polyline->start_width = 0.0;
        polyline->end_width = 0.0;
        polyline->vertices_follow = 1;
        polyline->color = DXF_COLOR_BYLAYER;
        polyline->paperspace = DXF_MODELSPACE;
        polyline->flag = 0;
        polyline->polygon_mesh_M_vertex_count = 0;
        polyline->polygon_mesh_N_vertex_count = 0;
        polyline->smooth_M_surface_density = 0;
        polyline->smooth_N_surface_density = 0;
        polyline->surface_type = 0;
        polyline->extr_x0 = 0.0;
        polyline->extr_y0 = 0.0;
        polyline->extr_z0 = 0.0;
        polyline->dictionary_owner_soft = strdup ("");
        polyline->dictionary_owner_hard = strdup ("");
        polyline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}



/*!
 * \brief Read data from a DXF file into an \c POLYLINE entity.
 *
 * The last line read from file contained the string "POLYLINE". \n
 * Now follows some data for the \c POLYLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c polyline. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPolyline *
dxf_polyline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfPolyline *polyline
                /*!< a pointer to the DXF polyline entity. */
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
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                polyline = dxf_polyline_new ();
                polyline = dxf_polyline_init (polyline);
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
                        fscanf (fp->fp, "%x\n", &polyline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", polyline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", polyline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the primary point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the primary point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the primary point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (polyline->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * starting width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->start_width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * end width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->end_width);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &polyline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->color);
                }
                else if (strcmp (temp_string, "66") == 0)
                {
                        /* Now follows a string containing the
                         * vertces follow flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->vertices_follow);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the polygon
                         * mesh M vertex count value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->polygon_mesh_M_vertex_count);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the polygon
                         * mesh N vertex count value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->polygon_mesh_N_vertex_count);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the smooth M
                         * surface density value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->smooth_M_surface_density);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the smooth N
                         * surface density value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->smooth_M_surface_density);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the surface
                         * type value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &polyline->surface_type);
                }
                else if ((fp->acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &polyline->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", polyline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", polyline->dictionary_owner_hard);
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
        if (strcmp (polyline->linetype, "") == 0)
        {
                polyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (polyline->layer, "") == 0)
        {
                polyline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Write DXF output to fp for a polyline entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_polyline_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfPolyline *polyline
                /*!< a pointer to the DXF polyline entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("POLYLINE");
        DxfVertex *iter = NULL;

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
        if (polyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (polyline->x0 != 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () start point has an invalid X-value for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, polyline->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (polyline->y0 != 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () start point has an invalid Y-value for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, polyline->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (polyline->vertices_follow != 1)
        {
                fprintf (stderr,
                  (_("Error in %s () vertices follow flag has an invalid value for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, polyline->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (polyline->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, polyline->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                polyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (polyline->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, polyline->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                polyline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (polyline->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", polyline->id_code);
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
        if ((strcmp (polyline->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", polyline->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (polyline->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", polyline->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (polyline->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", polyline->layer);
        if (strcmp (polyline->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", polyline->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (polyline->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", polyline->elevation);
        }
        if (polyline->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", polyline->color);
        }
        if (polyline->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", polyline->linetype_scale);
        }
        if (polyline->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", polyline->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDb3dPolyline\n");
        }
        fprintf (fp->fp, " 66\n%d\n", polyline->vertices_follow);
        fprintf (fp->fp, " 10\n%f\n", polyline->x0);
        fprintf (fp->fp, " 20\n%f\n", polyline->y0);
        fprintf (fp->fp, " 30\n%f\n", polyline->z0);
        if (polyline->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", polyline->thickness);
        }
        fprintf (fp->fp, " 70\n%d\n", polyline->flag);
        if (polyline->start_width != 0.0)
        {
                fprintf (fp->fp, " 40\n%f\n", polyline->start_width);
        }
        if (polyline->end_width != 0.0)
        {
                fprintf (fp->fp, " 41\n%f\n", polyline->end_width);
        }
        fprintf (fp->fp, " 71\n%d\n", polyline->polygon_mesh_M_vertex_count);
        fprintf (fp->fp, " 72\n%d\n", polyline->polygon_mesh_N_vertex_count);
        fprintf (fp->fp, " 73\n%d\n", polyline->smooth_M_surface_density);
        fprintf (fp->fp, " 74\n%d\n", polyline->smooth_N_surface_density);
        fprintf (fp->fp, " 75\n%d\n", polyline->surface_type);
        if ((fp->acad_version_number >= AutoCAD_12)
                && (polyline->extr_x0 != 0.0)
                && (polyline->extr_y0 != 0.0)
                && (polyline->extr_z0 != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", polyline->extr_x0);
                fprintf (fp->fp, "220\n%f\n", polyline->extr_y0);
                fprintf (fp->fp, "230\n%f\n", polyline->extr_z0);
        }
        /* Start of writing (multiple) vertices. */
        iter = (DxfVertex *) polyline->vertices;
        while (iter != NULL)
        {
                dxf_vertex_write (fp, iter);
                iter = (DxfVertex *) iter->next;
        }
        dxf_vertex_free (iter);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c POLYLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_polyline_free
(
        DxfPolyline *polyline
                /*!< a pointer to the memory occupied by the DXF
                 * \c POLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (polyline->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next DxfPolyline was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (polyline->linetype);
        free (polyline->layer);
        free (polyline);
        polyline = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c POLYLINE
 * entities and all their data fields.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_polyline_free_chain
(
        DxfPolyline *polylines
                /*!< a pointer to the chain of DXF \c POLYLINE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (polylines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (polylines != NULL)
        {
                struct DxfPolyline *iter = polylines->next;
                dxf_polyline_free (polylines);
                polylines = (DxfPolyline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a libDXF \c POLYLINE entity.
 *
 * \return \c id_code.
 */
int
dxf_polyline_get_id_code
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
                  (_("Warning in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->id_code);
}


/*!
 * \brief Set the \c id_code for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_id_code
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
                  (_("Warning in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the linetype from a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c linetype when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_polyline_get_linetype
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
        if (polyline->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->linetype));
}


/*!
 * \brief Set the \c linetype for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c linetype variable is not freed by this
 * function.
 */
DxfPolyline *
dxf_polyline_set_linetype
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
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
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c layer from a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c layer when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_polyline_get_layer
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
        if (polyline->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (polyline->layer));
}


/*!
 * \brief Set the \c layer for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c layer variable is not freed by this function.
 */
DxfPolyline *
dxf_polyline_set_layer
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
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
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        polyline->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c elevation a this libDXF \c POLYLINE entity.
 *
 * \return \c elevation.
 */
double
dxf_polyline_get_elevation
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->elevation);
}


/*!
 * \brief Set the \c elevation for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_elevation
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
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
        polyline->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c thickness from a libDXF \c POLYLINE entity.
 *
 * \return \c thickness.
 */
double
dxf_polyline_get_thickness
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
        if (polyline->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->thickness);
}


/*!
 * \brief Set the \c thickness for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_thickness
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
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
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c linetype_scale from a libDXF \c POLYLINE entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_polyline_get_linetype_scale
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
        if (polyline->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the linetype_scale member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_linetype_scale
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
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
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative linetype_scale value was passed.\n")),
                  __FUNCTION__);
        }
        polyline->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c visibility from a libDXF \c POLYLINE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_polyline_get_visibility
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
        if (polyline->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (polyline->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->visibility);
}


/*!
 * \brief Set the \c visibility for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_visibility
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
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
        polyline->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c color from a libDXF \c POLYLINE entity.
 *
 * \return \c color.
 */
int
dxf_polyline_get_color
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
        if (polyline->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->color);
}


/*!
 * \brief Set the \c color for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_color
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
        int color
                /*!< the \c color to be set for the entity. */
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
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        polyline->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/*!
 * \brief Get the \c paperspace flag value from a libDXF \c POLYLINE
 * entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_polyline_get_paperspace
(
        DxfPolyline *polyline
                /*!< a pointer to a libDXF \c POLYLINE entity. */
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
        if (polyline->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (polyline->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a libDXF \c POLYLINE entity.
 *
 * \return a pointer to \c polyline when sucessful, \c NULL when an error
 * occurred.
 */
DxfPolyline *
dxf_polyline_set_paperspace
(
        DxfPolyline *polyline,
                /*!< a pointer to a libDXF \c POLYLINE entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the entity. */
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
        polyline->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (polyline);
}


/* EOF */
